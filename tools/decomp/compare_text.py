#!/usr/bin/env python3
"""Compare one symbol's code bytes between two ELFs (TECH-003a).

The C-port scratch loop builds a candidate tree in ``/tmp`` and needs a cheap,
deterministic answer to "did this function change?".  This tool:

* reads the symbol address and size with ``arm-none-eabi-nm -S -P``;
* reads the code bytes straight out of the ELF section that contains the
  symbol (no temporary files, no ``objcopy``);
* reports size, first differing byte offset and the number of differing bytes;
* optionally prints a normalized ``objdump -d`` diff (``--disasm``).

Exit status is the contract used by the scratch loop and by ``make``:

* ``0`` -- the two byte ranges are identical;
* ``1`` -- they differ (including a size mismatch);
* ``2`` -- usage error, missing tool, unreadable ELF or unknown symbol.

Comparison mode writes nothing except stdout/stderr.  ``--self-check`` builds
a two-function fixture ELF in a temporary directory, verifies PASS/FAIL and
the size/offset accounting, then removes it.  It needs no candidate build, so
the tool can be audited in a clean worktree with only the baseline ELF.

Examples::

    python3 tools/decomp/compare_text.py --self-check

    python3 tools/decomp/compare_text.py \\
        --baseline /path/to/clean-tree/mf_us.elf \\
        --candidate /tmp/mf-cport/mf_us.elf \\
        --symbol RoomLoad --disasm

    python3 tools/decomp/compare_text.py --json \\
        --baseline a.elf --candidate b.elf --symbol Sram_WriteFileInfo
"""

from __future__ import annotations

import argparse
import difflib
import json
import re
import shutil
import subprocess
import struct
import sys
import tempfile
from pathlib import Path

EXIT_SAME = 0
EXIT_DIFF = 1
EXIT_TOOL = 2

SCHEMA = "compare-text/1"

# ELF constants (32-bit, little-endian ARM is the only target).
ELFCLASS32 = 1
ELFDATA2LSB = 1
SHT_PROGBITS = 1
SHT_NOBITS = 8
SHF_ALLOC = 0x2
SHF_EXECINSTR = 0x4

# nm type letters that denote text code.  Uppercase means global/weak, which
# is the only safe "next function" boundary for size inference (the assembler
# also emits lowercase ``_08xxxxxx`` local labels inside a function).
TEXT_TYPES = set("TtWw")

INSTRUCTION_RE = re.compile(r"^\s*([0-9a-fA-F]+):\s*(.*\S)\s*$")
ANNOTATED_HEX_RE = re.compile(
    r"\b(?:0[xX])?([0-9a-fA-F]{7,8})\s*<([^>]+)>"
)
BARE_HEX_RE = re.compile(r"\b(?:0[xX])?([0-9a-fA-F]{7,8})\b")


class ToolError(Exception):
    """A usage/tool/input failure, mapped to exit status 2."""


class Section:
    __slots__ = ("index", "name", "type", "flags", "addr", "offset", "size")

    def __init__(self, index, name, type_, flags, addr, offset, size):
        self.index = index
        self.name = name
        self.type = type_
        self.flags = flags
        self.addr = addr
        self.offset = offset
        self.size = size


class Symbol:
    __slots__ = ("name", "type", "value", "size")

    def __init__(self, name, type_, value, size):
        self.name = name
        self.type = type_
        self.value = value
        self.size = size

    @property
    def is_text(self):
        return self.type in TEXT_TYPES

    @property
    def is_global_text(self):
        return self.type in ("T", "W")


def _u16(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def _u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


# ---------------------------------------------------------------------------
# ELF inspection


def read_elf(path):
    try:
        data = Path(path).read_bytes()
    except OSError as exc:
        raise ToolError(f"cannot read ELF {path!r}: {exc}") from exc
    if len(data) < 0x34 or data[:4] != b"\x7fELF":
        raise ToolError(f"{path!r} is not an ELF file")
    if data[4] != ELFCLASS32 or data[5] != ELFDATA2LSB:
        raise ToolError(
            f"{path!r} is not a 32-bit little-endian ELF "
            f"(class={data[4]}, data={data[5]})"
        )
    return data


def parse_sections(path, data=None):
    if data is None:
        data = read_elf(path)
    e_shoff = _u32(data, 0x20)
    e_shentsize = _u16(data, 0x2E)
    e_shnum = _u16(data, 0x30)
    e_shstrndx = _u16(data, 0x32)
    if e_shoff == 0 or e_shnum == 0 or e_shentsize < 40:
        raise ToolError(f"{path!r} has no usable section header table")
    if e_shoff + e_shnum * e_shentsize > len(data):
        raise ToolError(f"{path!r} has a truncated section header table")

    raw = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        raw.append(
            {
                "name": _u32(data, off),
                "type": _u32(data, off + 4),
                "flags": _u32(data, off + 8),
                "addr": _u32(data, off + 12),
                "offset": _u32(data, off + 16),
                "size": _u32(data, off + 20),
            }
        )

    names = b""
    if 0 <= e_shstrndx < len(raw):
        str_sec = raw[e_shstrndx]
        names = data[str_sec["offset"] : str_sec["offset"] + str_sec["size"]]

    sections = []
    for i, sh in enumerate(raw):
        name_off = sh["name"]
        end = names.find(b"\0", name_off)
        if name_off < len(names) and end >= 0:
            name = names[name_off:end].decode("latin-1")
        else:
            name = f"<section {i}>"
        sections.append(
            Section(
                i,
                name,
                sh["type"],
                sh["flags"],
                sh["addr"],
                sh["offset"],
                sh["size"],
            )
        )
    return sections


def section_for_address(sections, addr):
    """Return the best section containing *addr* (prefer executable contents)."""
    candidates = [
        s
        for s in sections
        if s.size and s.addr <= addr < s.addr + s.size and s.type != SHT_NOBITS
    ]
    if not candidates:
        return None
    candidates.sort(
        key=lambda s: (
            0 if s.flags & SHF_EXECINSTR else 1,
            0 if s.flags & SHF_ALLOC else 1,
            0 if s.type == SHT_PROGBITS else 1,
            -s.size,
        )
    )
    return candidates[0]


def code_bytes(path, data, sections, symbol, size):
    section = section_for_address(sections, symbol.value)
    if section is None:
        raise ToolError(
            f"symbol {symbol.name!r} at 0x{symbol.value:08x} is not in a "
            f"section with file contents"
        )
    start = section.offset + (symbol.value - section.addr)
    end = start + size
    section_end = section.offset + section.size
    if end > section_end:
        raise ToolError(
            f"symbol {symbol.name!r} (0x{symbol.value:08x}, size 0x{size:x}) "
            f"runs past section {section.name!r}"
        )
    if end > len(data):
        raise ToolError(
            f"symbol {symbol.name!r} bytes extend past the end of {path!r}"
        )
    return data[start:end]


# ---------------------------------------------------------------------------
# Toolchain discovery


def _search_tool(name, explicit=None):
    if explicit:
        return explicit
    found = shutil.which(name)
    if found:
        return found
    home_tool = Path.home() / ".local" / "bin" / name
    if home_tool.is_file():
        return str(home_tool)
    return None


def resolve_tools(args):
    nm = _search_tool("arm-none-eabi-nm", args.nm) or _search_tool("nm")
    if not nm:
        raise ToolError(
            "cannot find arm-none-eabi-nm (install the ARM binutils or pass --nm)"
        )
    objdump = _search_tool("arm-none-eabi-objdump", args.objdump) or _search_tool(
        "objdump"
    )
    if not objdump:
        raise ToolError(
            "cannot find arm-none-eabi-objdump "
            "(install the ARM binutils or pass --objdump)"
        )
    return {"nm": nm, "objdump": objdump}


def _sibling_tool(reference, suffix):
    """Derive ``arm-none-eabi-<suffix>`` next to the discovered nm binary."""
    ref = Path(reference)
    name = ref.name
    if "arm-none-eabi-" in name:
        return str(ref.with_name(name.replace("nm", suffix, 1)))
    return None


def resolve_fixture_tools(args, nm):
    as_tool = args.asm or _sibling_tool(nm, "as") or shutil.which("arm-none-eabi-as")
    ld_tool = args.ld or _sibling_tool(nm, "ld") or shutil.which("arm-none-eabi-ld")
    if not as_tool and (Path.home() / ".local" / "bin" / "arm-none-eabi-as").is_file():
        as_tool = str(Path.home() / ".local" / "bin" / "arm-none-eabi-as")
    if not ld_tool and (Path.home() / ".local" / "bin" / "arm-none-eabi-ld").is_file():
        ld_tool = str(Path.home() / ".local" / "bin" / "arm-none-eabi-ld")
    if not as_tool or not ld_tool:
        raise ToolError(
            "--self-check needs arm-none-eabi-as and arm-none-eabi-ld "
            "(pass --asm/--ld or set PATH)"
        )
    return as_tool, ld_tool


def _run(cmd, what):
    try:
        proc = subprocess.run(
            cmd,
            check=False,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
    except OSError as exc:
        raise ToolError(f"failed to run {what}: {exc}") from exc
    if proc.returncode != 0:
        detail = (proc.stderr or proc.stdout).strip().splitlines()
        tail = f": {detail[-1]}" if detail else ""
        raise ToolError(f"{what} failed (exit {proc.returncode}){tail}")
    return proc.stdout


# ---------------------------------------------------------------------------
# Symbols


def load_symbols(elf, nm):
    out = _run([nm, "-S", "-P", "--defined-only", str(elf)], f"{nm} on {elf}")
    symbols = []
    for line in out.splitlines():
        line = line.strip()
        if not line:
            continue
        parts = line.split(None, 3)
        if len(parts) < 3:
            continue
        name, type_, value_text = parts[0], parts[1], parts[2]
        size_text = parts[3].strip() if len(parts) > 3 else ""
        try:
            value = int(value_text, 16)
        except ValueError:
            continue
        try:
            size = int(size_text, 16) if size_text else 0
        except ValueError:
            size = 0
        symbols.append(Symbol(name, type_, value, size))
    if not symbols:
        raise ToolError(f"nm reported no defined symbols for {elf!r}")
    return symbols


def find_symbol(symbols, name):
    matches = [s for s in symbols if s.name == name]
    if not matches:
        raise ToolError(f"symbol {name!r} not found (is it defined and linked?)")
    # A name can appear as both a mapping symbol and a function; prefer text.
    matches.sort(key=lambda s: (0 if s.is_text else 1, 0 if s.size else 1))
    return matches[0]


def resolve_size(symbol, symbols, sections, override):
    if override is not None:
        if override <= 0:
            raise ToolError("--size/--candidate-size must be positive")
        return override, "override"
    if symbol.size:
        return symbol.size, "nm"
    section = section_for_address(sections, symbol.value)
    if section is None:
        raise ToolError(
            f"cannot infer a size for {symbol.name!r}: address is not backed "
            f"by a section; pass --size"
        )
    section_end = section.addr + section.size
    next_global = min(
        (
            s.value
            for s in symbols
            if s.is_global_text and symbol.value < s.value < section_end
        ),
        default=section_end,
    )
    if next_global <= symbol.value:
        raise ToolError(f"invalid symbol range for {symbol.name!r}")
    source = "next-global" if next_global < section_end else "section-end"
    return next_global - symbol.value, source


# ---------------------------------------------------------------------------
# Disassembly normalization


def _hex_token(value, symbol_index):
    """Resolve an absolute address to ``Symbol+0xoff`` for a stable diff."""
    for addr, name in symbol_index:
        if addr == value:
            return name
    best = None
    for addr, name in symbol_index:
        if addr <= value and value - addr <= 0x10000:
            if best is None or addr > best[0]:
                best = (addr, name)
    if best is not None:
        offset = value - best[0]
        return best[1] if offset == 0 else f"{best[1]}+0x{offset:x}"
    return f"0x{value:08x}"


def normalize_disassembly(lines, symbols):
    # Global names win at equal addresses.
    dedup = {}
    for s in symbols:
        if not s.is_text or s.name.startswith("$"):
            continue
        preferred = dedup.get(s.value)
        if preferred is None or (s.is_global_text and not preferred[1]):
            dedup[s.value] = (s.name, s.is_global_text)
    index = sorted((addr, name) for addr, (name, _) in dedup.items())

    normalized = []
    for line in lines:
        match = INSTRUCTION_RE.match(line)
        if not match:
            continue
        text = " ".join(match.group(2).split())

        def _annotated(m):
            return m.group(2)

        text = ANNOTATED_HEX_RE.sub(_annotated, text)
        text = BARE_HEX_RE.sub(
            lambda m: _hex_token(int(m.group(1), 16), index), text
        )
        normalized.append(" ".join(text.split()))
    return normalized


def disassembly_lines(objdump, elf, address, size):
    out = _run(
        [
            objdump,
            "-d",
            "--no-show-raw-insn",
            f"--start-address=0x{address:x}",
            f"--stop-address=0x{address + size:x}",
            str(elf),
        ],
        f"{objdump} on {elf}",
    )
    return out.splitlines()


# ---------------------------------------------------------------------------
# Comparison


def compare_elfs(
    baseline,
    candidate,
    baseline_symbol_name,
    candidate_symbol_name,
    *,
    tools,
    baseline_size=None,
    candidate_size=None,
    with_disasm=False,
):
    base_data = read_elf(baseline)
    cand_data = read_elf(candidate)
    base_sections = parse_sections(baseline, base_data)
    cand_sections = parse_sections(candidate, cand_data)
    base_symbols = load_symbols(baseline, tools["nm"])
    cand_symbols = load_symbols(candidate, tools["nm"])

    base_symbol = find_symbol(base_symbols, baseline_symbol_name)
    cand_symbol = find_symbol(cand_symbols, candidate_symbol_name)

    base_len, base_size_source = resolve_size(
        base_symbol, base_symbols, base_sections, baseline_size
    )
    cand_len, cand_size_source = resolve_size(
        cand_symbol, cand_symbols, cand_sections, candidate_size
    )

    base_bytes = code_bytes(baseline, base_data, base_sections, base_symbol, base_len)
    cand_bytes = code_bytes(candidate, cand_data, cand_sections, cand_symbol, cand_len)

    compared = max(len(base_bytes), len(cand_bytes))
    first_diff = None
    base_byte = None
    cand_byte = None
    differing = 0
    for i in range(compared):
        left = base_bytes[i] if i < len(base_bytes) else None
        right = cand_bytes[i] if i < len(cand_bytes) else None
        if left != right:
            differing += 1
            if first_diff is None:
                first_diff = i
                base_byte = left
                cand_byte = right

    identical = differing == 0 and len(base_bytes) == len(cand_bytes)

    result = {
        "schema": SCHEMA,
        "symbol": baseline_symbol_name,
        "baseline_symbol": baseline_symbol_name,
        "candidate_symbol": candidate_symbol_name,
        "baseline": {
            "elf": str(baseline),
            "symbol": baseline_symbol_name,
            "address": base_symbol.value,
            "size": len(base_bytes),
            "size_source": base_size_source,
            "section": (
                section_for_address(base_sections, base_symbol.value).name
                if section_for_address(base_sections, base_symbol.value)
                else None
            ),
        },
        "candidate": {
            "elf": str(candidate),
            "symbol": candidate_symbol_name,
            "address": cand_symbol.value,
            "size": len(cand_bytes),
            "size_source": cand_size_source,
            "section": (
                section_for_address(cand_sections, cand_symbol.value).name
                if section_for_address(cand_sections, cand_symbol.value)
                else None
            ),
        },
        "identical": identical,
        "size_match": len(base_bytes) == len(cand_bytes),
        "compared_bytes": compared,
        "differing_bytes": differing,
        "first_diff_offset": first_diff,
        "first_diff_baseline_byte": base_byte,
        "first_diff_candidate_byte": cand_byte,
        "disasm_diff": None,
    }

    if with_disasm:
        base_lines = normalize_disassembly(
            disassembly_lines(
                tools["objdump"], baseline, base_symbol.value, len(base_bytes)
            ),
            base_symbols,
        )
        cand_lines = normalize_disassembly(
            disassembly_lines(
                tools["objdump"], candidate, cand_symbol.value, len(cand_bytes)
            ),
            cand_symbols,
        )
        result["disasm_diff"] = list(
            difflib.unified_diff(
                base_lines,
                cand_lines,
                fromfile=f"baseline:{baseline_symbol_name}",
                tofile=f"candidate:{candidate_symbol_name}",
                lineterm="",
                n=2,
            )
        )
        result["disasm_normalized_lines"] = {
            "baseline": len(base_lines),
            "candidate": len(cand_lines),
        }

    return result


def result_exit_code(result):
    return EXIT_SAME if result["identical"] else EXIT_DIFF


# ---------------------------------------------------------------------------
# Renderers


def _fmt_size(value):
    return f"0x{value:x} ({value})"


def _fmt_byte(value):
    return f"0x{value:02x}" if value is not None else "EOF"


def render_human(result):
    lines = [f"compare_text: {result['baseline_symbol']}"]
    base = result["baseline"]
    cand = result["candidate"]
    lines.append(
        f"  baseline   {base['elf']}  {base['symbol']} @ 0x{base['address']:08x}  "
        f"size {_fmt_size(base['size'])} [{base['size_source']}]"
    )
    lines.append(
        f"  candidate  {cand['elf']}  {cand['symbol']} @ 0x{cand['address']:08x}  "
        f"size {_fmt_size(cand['size'])} [{cand['size_source']}]"
    )
    if result["identical"]:
        lines.append(
            f"  status     PASS - {result['compared_bytes']} bytes identical"
        )
    else:
        first = result["first_diff_offset"]
        if not result["size_match"]:
            lines.append(
                "  size       MISMATCH - baseline "
                f"{_fmt_size(base['size'])}, candidate {_fmt_size(cand['size'])}"
            )
        lines.append(
            f"  status     FAIL - first difference at +0x{first:x} "
            f"(baseline {_fmt_byte(result['first_diff_baseline_byte'])} vs "
            f"candidate {_fmt_byte(result['first_diff_candidate_byte'])})"
        )
        lines.append(
            f"             {result['differing_bytes']} of "
            f"{result['compared_bytes']} compared bytes differ"
        )
    disasm = result.get("disasm_diff")
    if disasm is not None:
        lines.append("  disassembly diff (normalized):")
        if not disasm:
            lines.append("    (no differences)")
        else:
            lines.extend(f"    {line}" for line in disasm)
    return "\n".join(lines)


def render_json(result, pretty):
    if pretty:
        return json.dumps(result, indent=2, sort_keys=True)
    return json.dumps(result, sort_keys=True)


# ---------------------------------------------------------------------------
# Self-check


FIXTURE_ASM = """\
    .syntax unified
    .thumb
    .text
    .global fixture_a
    .thumb_func
    .type fixture_a, %function
fixture_a:
    movs r0, #1
    adds r0, #2
    bx lr
    .size fixture_a, .-fixture_a

    .global fixture_b
    .thumb_func
    .type fixture_b, %function
fixture_b:
    movs r0, #1
    adds r0, #3
    movs r1, #4
    bx lr
    .size fixture_b, .-fixture_b
"""


def _fixture_compare(args, tools, elf, base_symbol, cand_symbol, **kwargs):
    return compare_elfs(
        elf,
        elf,
        base_symbol,
        cand_symbol,
        tools=tools,
        with_disasm=kwargs.pop("with_disasm", False),
        **kwargs,
    )


def self_check(args):
    tools = resolve_tools(args)
    as_tool, ld_tool = resolve_fixture_tools(args, tools["nm"])
    checks = []

    with tempfile.TemporaryDirectory(prefix="compare-text-selfcheck-") as tmp:
        tmp = Path(tmp)
        source = tmp / "fixture.s"
        obj = tmp / "fixture.o"
        elf = tmp / "fixture.elf"
        source.write_text(FIXTURE_ASM, encoding="utf-8")
        _run([as_tool, "-o", str(obj), str(source)], "arm-none-eabi-as")
        _run(
            [ld_tool, "-Ttext=0x08000000", "-o", str(elf), str(obj)],
            "arm-none-eabi-ld",
        )

        same = _fixture_compare(args, tools, elf, "fixture_a", "fixture_a")
        checks.append(
            (
                "identical symbol -> PASS (exit 0)",
                same["identical"] and result_exit_code(same) == EXIT_SAME,
                f"identical={same['identical']} exit={result_exit_code(same)}",
            )
        )

        modified = _fixture_compare(args, tools, elf, "fixture_a", "fixture_b")
        checks.append(
            (
                "modified symbol -> FAIL (exit 1) at first changed byte",
                (not modified["identical"])
                and result_exit_code(modified) == EXIT_DIFF
                and modified["first_diff_offset"] == 2
                and modified["differing_bytes"] >= 1,
                f"identical={modified['identical']} "
                f"first=+0x{modified['first_diff_offset']:x} "
                f"diff={modified['differing_bytes']} "
                f"exit={result_exit_code(modified)}",
            )
        )

        truncated = _fixture_compare(
            args,
            tools,
            elf,
            "fixture_a",
            "fixture_a",
            candidate_size=5,
        )
        checks.append(
            (
                "truncated candidate -> FAIL with size mismatch",
                (not truncated["identical"])
                and (not truncated["size_match"])
                and truncated["first_diff_offset"] == 5,
                f"size_match={truncated['size_match']} "
                f"first=+0x{truncated['first_diff_offset']:x}",
            )
        )

        same_disasm = _fixture_compare(
            args, tools, elf, "fixture_a", "fixture_a", with_disasm=True
        )
        checks.append(
            (
                "normalized disassembly of identical code has no diff",
                same_disasm["disasm_diff"] == [],
                f"diff_lines={len(same_disasm['disasm_diff'] or [])}",
            )
        )

        modified_disasm = _fixture_compare(
            args, tools, elf, "fixture_a", "fixture_b", with_disasm=True
        )
        checks.append(
            (
                "normalized disassembly of modified code shows a diff",
                bool(modified_disasm["disasm_diff"]),
                f"diff_lines={len(modified_disasm['disasm_diff'] or [])}",
            )
        )

    failures = 0
    print("compare_text self-check")
    print(f"  nm       {tools['nm']}")
    print(f"  objdump  {tools['objdump']}")
    print(f"  as       {as_tool}")
    print(f"  ld       {ld_tool}")
    for label, ok, detail in checks:
        print(f"  [{'PASS' if ok else 'FAIL'}] {label}: {detail}")
        if not ok:
            failures += 1
    if failures:
        print(f"self-check: FAIL ({failures} check(s))")
        return EXIT_DIFF
    print(f"self-check: PASS ({len(checks)} checks)")
    return EXIT_SAME


# ---------------------------------------------------------------------------
# CLI


def build_parser():
    parser = argparse.ArgumentParser(
        description=(
            "Compare one symbol's code bytes between a baseline ELF and a "
            "candidate ELF; exits 0 identical, 1 different, 2 tool/usage error."
        )
    )
    parser.add_argument("--baseline", help="baseline ELF (e.g. mf_us.elf)")
    parser.add_argument("--candidate", help="candidate ELF (scratch build)")
    parser.add_argument("--symbol", help="symbol name in both ELFs")
    parser.add_argument(
        "--baseline-symbol", help="symbol name in the baseline ELF (default: --symbol)"
    )
    parser.add_argument(
        "--candidate-symbol",
        help="symbol name in the candidate ELF (default: --symbol)",
    )
    parser.add_argument(
        "--size",
        type=lambda s: int(s, 0),
        help="override the baseline symbol size (bytes)",
    )
    parser.add_argument(
        "--candidate-size",
        type=lambda s: int(s, 0),
        help="override the candidate symbol size (bytes)",
    )
    parser.add_argument(
        "--disasm",
        action="store_true",
        help="include a normalized objdump disassembly diff",
    )
    parser.add_argument(
        "--json", action="store_true", help="emit a machine-readable JSON report"
    )
    parser.add_argument(
        "--pretty", action="store_true", help="indent JSON (implies --json)"
    )
    parser.add_argument(
        "--self-check",
        action="store_true",
        help="build a fixture ELF and verify the comparison semantics",
    )
    parser.add_argument("--nm", help="path to arm-none-eabi-nm")
    parser.add_argument("--objdump", help="path to arm-none-eabi-objdump")
    parser.add_argument("--asm", help="path to arm-none-eabi-as (self-check only)")
    parser.add_argument("--ld", help="path to arm-none-eabi-ld (self-check only)")
    return parser


def main(argv=None):
    parser = build_parser()
    args = parser.parse_args(argv)

    try:
        if args.self_check:
            return self_check(args)

        if not args.baseline or not args.candidate:
            parser.error("--baseline and --candidate are required")

        baseline_symbol = args.baseline_symbol or args.symbol
        candidate_symbol = args.candidate_symbol or args.symbol
        if not baseline_symbol or not candidate_symbol:
            parser.error("--symbol (or both --baseline-symbol/--candidate-symbol) required")

        tools = resolve_tools(args)
        result = compare_elfs(
            args.baseline,
            args.candidate,
            baseline_symbol,
            candidate_symbol,
            tools=tools,
            baseline_size=args.size,
            candidate_size=args.candidate_size,
            with_disasm=args.disasm,
        )

        if args.json or args.pretty:
            print(render_json(result, pretty=args.pretty))
        else:
            print(render_human(result))
        return result_exit_code(result)
    except ToolError as exc:
        print(f"compare_text: error: {exc}", file=sys.stderr)
        return EXIT_TOOL


if __name__ == "__main__":
    sys.exit(main())
