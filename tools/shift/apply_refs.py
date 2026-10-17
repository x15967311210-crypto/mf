#!/usr/bin/env python3
"""Apply relocatable symbol expressions to hardcoded ROM literals in asm.

The audit ledger (`work/shift/abs_refs.json`) records every `.4byte`/`.word`
ROM address literal and every bare `ldr rX, =0x...` pseudo-literal, together
with the symbol that covers it.  This tool rewrites the numeric operand to a
symbol expression:

    0x0839EC68        ->  sBlob_39aa34_39f4b0+0x4234
    0x080A8CDC        ->  sMusicTrackDataRom
    ldr r3, =0x80a568c -> ldr r3, =sDma1ControlPointer

It is deliberately conservative: a record is only rewritten when the target is
known, the line still has the expected label (and directive/mnemonic/register),
and the current operand still equals the recorded value.  Numeric operands may
use 1-8 hex digits (`0x80a5710` is zero-padded to `0x080A5710` in the ledger),
but the parsed value must match exactly.  Every planned rewrite is re-parsed
and checked before it is written, so `--dry-run` cannot show a line the real
run would reject.  Running it twice is a no-op.

Static (`STB_LOCAL`) symbols from C data files are not visible to the linker
from another object.  For those targets the tool emits an equivalent global
anchor in the same final ELF output section, e.g.

    sBlob_39aa34_39f4b0 (local, 0x0839AA34)
        -> sOmegaMetroidPartOam_LeftLeg_Swiping+0x30

The anchor and the target share the final ELF output section, so padding or
reordering that section keeps the expression correct.  Pass `--elf` to point
at the baseline ELF used for that lookup.

Examples:

    python3 tools/shift/apply_refs.py --dry-run asm/audio_internal.s
    python3 tools/shift/apply_refs.py --dry-run --check
    python3 tools/shift/apply_refs.py asm/disasm_*.s asm/intr_main.s
    python3 tools/shift/apply_refs.py --check
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

SYMBOL_RE = re.compile(r"^[A-Za-z_.$][\w.$@]*$")
LITERAL_RE = re.compile(
    r"^(?P<indent>[ \t]*)"
    r"(?P<label>(?:[A-Za-z_.$][\w.$@]*:[ \t]*)?)"
    r"\.(?P<directive>4byte|word)"
    r"(?P<sep>[ \t]+)"
    r"(?P<operand>\S+)"
    r"(?P<suffix>.*)$"
)
LABEL_RE = re.compile(r"^\s*([A-Za-z_.$][\w.$@]*):")
# A bare `ldr rX, =0x...` pseudo-literal; the mnemonic/register are part of the
# captured line so a changed instruction is rejected instead of rewritten.
LDR_LITERAL_RE = re.compile(
    r"^(?P<indent>[ \t]*)"
    r"(?P<label>(?:[A-Za-z_.$][\w.$@]*:[ \t]*)?)"
    r"(?P<mnemonic>ldr[a-z]*)"
    r"(?P<sep>[ \t]+)"
    r"(?P<reg>\w+)"
    r"(?P<comma>[ \t]*,[ \t]*)"
    r"=(?P<operand>[^ \t@]+)"
    r"(?P<suffix>.*)$",
    re.IGNORECASE,
)
LDR_HEAD_RE = re.compile(
    r"^\s*(?:[A-Za-z_.$][\w.$@]*:\s*)?(ldr[a-z]*)\s+(\w+)\s*,\s*=",
    re.IGNORECASE,
)
# 1-8 hex digits: the audio track headers use the 7-digit form 0x80a5710.
# The parsed value is still compared exactly against the ledger's canonical
# zero-padded value, so a short operand cannot match a different address.
NUMERIC_RE = re.compile(r"^0x([0-9A-Fa-f]{1,8})$")

BINDING_LOCAL = 0
BINDING_GLOBAL = 1
BINDING_WEAK = 2
SYMBOL_TYPES = {0, 1}  # NOTYPE, OBJECT; functions are not data anchors.
ROM_SECTIONS = {".rodata", ".data"}


class RefError(Exception):
    """A ledger record cannot be applied safely."""


@dataclass(frozen=True)
class ElfSymbol:
    name: str
    value: int
    binding: int
    section: str


class ElfSymbols:
    """Minimal final-ELF symbol reader for link-visibility and anchors."""

    def __init__(self, bindings: dict[tuple[str, int], int], globals_by_section: dict[str, list[ElfSymbol]]):
        self._bindings = bindings
        self._globals_by_section = globals_by_section

    @classmethod
    def load(cls, path: Path) -> "ElfSymbols":
        data = path.read_bytes()
        if len(data) < 0x34 or data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
            raise RefError(f"{path}: not a little-endian ELF32 file")

        e_shoff = struct.unpack_from("<I", data, 0x20)[0]
        e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
        e_shnum = struct.unpack_from("<H", data, 0x30)[0]
        e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
        if not e_shoff or not e_shnum or e_shentsize < 40:
            raise RefError(f"{path}: missing section headers")

        sections: list[tuple[int, int, int, int, int, int]] = []
        for i in range(e_shnum):
            off = e_shoff + i * e_shentsize
            if off + 40 > len(data):
                raise RefError(f"{path}: truncated section table")
            sections.append(struct.unpack_from("<IIIIIIIIII", data, off))

        if e_shstrndx >= len(sections):
            raise RefError(f"{path}: bad section-name table index")

        def cstring(offset: int) -> str:
            if offset < 0 or offset >= len(data):
                return ""
            end = data.find(b"\x00", offset)
            if end < 0:
                return ""
            return data[offset:end].decode("ascii", "replace")

        shstr = sections[e_shstrndx]
        section_names = {
            i: cstring(shstr[4] + sec[0]) for i, sec in enumerate(sections)
        }

        symtab = None
        for i, sec in enumerate(sections):
            if sec[1] == 2 and sec[9]:  # SHT_SYMTAB
                symtab = (i, sec)
                break
        if symtab is None:
            raise RefError(f"{path}: no symbol table")

        _, sec = symtab
        sym_off, sym_size, strtab_idx, entsize = sec[4], sec[5], sec[6], sec[9]
        if strtab_idx >= len(sections) or not entsize:
            raise RefError(f"{path}: bad symbol table")
        strtab = sections[strtab_idx]

        bindings: dict[tuple[str, int], int] = {}
        globals_by_section: dict[str, list[ElfSymbol]] = {}
        for off in range(sym_off, min(sym_off + sym_size, len(data)), entsize):
            if off + 16 > len(data):
                break
            st_name, st_value, _st_size, st_info, _st_other, st_shndx = (
                struct.unpack_from("<IIIBBH", data, off)
            )
            name = cstring(strtab[4] + st_name)
            if not name:
                continue
            binding = st_info >> 4
            sym_type = st_info & 0xF
            section = section_names.get(st_shndx, "")
            if section not in ROM_SECTIONS:
                continue
            bindings[(name, st_value)] = binding
            if (
                binding in (BINDING_GLOBAL, BINDING_WEAK)
                and sym_type in SYMBOL_TYPES
                and SYMBOL_RE.match(name)
            ):
                globals_by_section.setdefault(section, []).append(
                    ElfSymbol(name, st_value, binding, section)
                )

        for symbols in globals_by_section.values():
            symbols.sort(key=lambda s: (s.value, s.name))

        return cls(bindings, globals_by_section)

    def binding(self, name: str, value: int) -> int | None:
        return self._bindings.get((name, value))

    def anchor(self, addr: int, section: str) -> ElfSymbol | None:
        """Return the nearest global anchor in *section* for *addr*."""
        candidates = self._globals_by_section.get(section)
        if not candidates:
            return None
        preceding = [s for s in candidates if s.value <= addr]
        if preceding:
            return max(preceding, key=lambda s: (s.value, s.name))
        return min(candidates, key=lambda s: (s.value, s.name))


def format_expression(symbol: str, offset: int) -> str:
    if offset == 0:
        return symbol
    if offset > 0:
        return f"{symbol}+0x{offset:X}"
    return f"{symbol}-0x{-offset:X}"


def target_expression(record: dict, elf: ElfSymbols | None) -> str:
    target = record.get("target") or {}
    if not target.get("known"):
        raise RefError("target address is not mapped to a symbol")
    symbol = target.get("symbol")
    if not symbol or not SYMBOL_RE.match(symbol):
        raise RefError("target has no usable symbol")

    offset = target.get("offset") or 0
    addr = int(target["addr"], 16)

    # A global/weak symbol is directly link-visible.  A local (static) symbol
    # is not, so use an equivalent global anchor in the same output section.
    if elf is not None:
        binding = elf.binding(symbol, addr - offset)
        if binding == BINDING_LOCAL:
            section = target.get("section") or ""
            anchor = elf.anchor(addr, section)
            if anchor is None:
                raise RefError(
                    f"local symbol {symbol} has no global anchor in {section or '?'}"
                )
            return format_expression(anchor.name, addr - anchor.value)

    return format_expression(symbol, offset)


def expected_line_parts(record: dict) -> tuple[str | None, str | None]:
    text = record.get("text", "")
    label_match = LABEL_RE.match(text)
    directive_match = re.search(r"\.(4byte|word)\b", text)
    return (
        label_match.group(1) if label_match else None,
        directive_match.group(1) if directive_match else None,
    )


def expected_ldr_parts(record: dict) -> tuple[str | None, str | None]:
    """Return the recorded mnemonic and register of a pseudo-literal line."""
    match = LDR_HEAD_RE.match(record.get("text", ""))
    if match is None:
        return None, None
    return match.group(1), match.group(2)


def load_records(path: Path) -> list[dict]:
    if not path.exists():
        raise RefError(f"missing ledger {path}; run `make -f Makefile.shift audit`")
    ledger = json.loads(path.read_text())
    return [
        r
        for r in ledger.get("records", [])
        if r.get("category") == "rom"
        and r.get("kind") in {"literal", "ldr_literal"}
    ]


def path_key(path: str | Path) -> Path:
    return Path(path).resolve()


def plan_file(path: Path, records: list[dict], elf: ElfSymbols | None) -> tuple[list[dict], list[str]]:
    changes: list[dict] = []
    errors: list[str] = []

    try:
        with path.open("r", encoding="utf-8", newline="") as handle:
            lines = handle.readlines()
    except OSError as exc:
        return changes, [f"{path}: cannot read: {exc}"]

    # Duplicate records on one line cannot be resolved deterministically.
    seen: dict[int, str] = {}
    for record in records:
        expr = target_expression(record, elf)
        previous = seen.get(record["line"])
        if previous is not None and previous != expr:
            errors.append(
                f"{path}:{record['line']}: conflicting target expressions "
                f"{previous} and {expr}"
            )
        seen[record["line"]] = expr

    for record in sorted(records, key=lambda r: r["line"]):
        lineno = record["line"]
        if lineno < 1 or lineno > len(lines):
            errors.append(f"{path}:{lineno}: line no longer exists")
            continue

        raw_line = lines[lineno - 1]
        ending = raw_line[len(raw_line.rstrip("\r\n")) :]
        body = raw_line[: len(raw_line) - len(ending)]
        kind = record.get("kind", "literal")

        expected_label, expected_directive = expected_line_parts(record)
        current_label_match = LABEL_RE.match(body)
        current_label = current_label_match.group(1) if current_label_match else None
        if expected_label is not None and current_label != expected_label:
            errors.append(
                f"{path}:{lineno}: label changed "
                f"({expected_label!r} -> {current_label!r})"
            )
            continue

        expr = seen[lineno]

        if kind == "ldr_literal":
            match = LDR_LITERAL_RE.match(body)
            if match is None:
                errors.append(
                    f"{path}:{lineno}: expected ldr rX, =0x... pseudo-literal, "
                    f"found {body.strip()!r}"
                )
                continue

            expected_mnemonic, expected_reg = expected_ldr_parts(record)
            if (
                expected_mnemonic is not None
                and match.group("mnemonic").lower() != expected_mnemonic.lower()
            ):
                errors.append(
                    f"{path}:{lineno}: mnemonic changed "
                    f"({expected_mnemonic!r} -> {match.group('mnemonic')!r})"
                )
                continue
            if (
                expected_reg is not None
                and match.group("reg").lower() != expected_reg.lower()
            ):
                errors.append(
                    f"{path}:{lineno}: register changed "
                    f"({expected_reg!r} -> {match.group('reg')!r})"
                )
                continue

            operand = match.group("operand")
            numeric = NUMERIC_RE.match(operand)
            if numeric:
                current_value = int(numeric.group(1), 16)
                expected_value = int(record["value"], 16)
                if current_value != expected_value:
                    errors.append(
                        f"{path}:{lineno}: operand changed "
                        f"({record['value']} -> {operand})"
                    )
                    continue
                new_body = (
                    match.group("indent")
                    + match.group("label")
                    + match.group("mnemonic")
                    + match.group("sep")
                    + match.group("reg")
                    + match.group("comma")
                    + "="
                    + expr
                    + match.group("suffix")
                )
                changes.append(
                    {
                        "file": path.as_posix(),
                        "line": lineno,
                        "kind": "ldr_literal",
                        "old": operand,
                        "new": expr,
                        "line_text": new_body + ending,
                    }
                )
            elif operand == expr:
                # Already applied, keep the file byte-identical.
                continue
            else:
                errors.append(
                    f"{path}:{lineno}: operand is {operand!r}, expected "
                    f"{record['value']} or {expr}"
                )
            continue

        match = LITERAL_RE.match(body)
        if match is None:
            errors.append(
                f"{path}:{lineno}: expected .4byte/.word literal, found {body.strip()!r}"
            )
            continue

        directive = match.group("directive")
        if expected_directive is not None and directive != expected_directive:
            errors.append(
                f"{path}:{lineno}: directive changed "
                f"(.{expected_directive} -> .{directive})"
            )
            continue

        operand = match.group("operand")
        numeric = NUMERIC_RE.match(operand)
        if numeric:
            current_value = int(numeric.group(1), 16)
            expected_value = int(record["value"], 16)
            if current_value != expected_value:
                errors.append(
                    f"{path}:{lineno}: operand changed "
                    f"({record['value']} -> {operand})"
                )
                continue
            new_body = (
                match.group("indent")
                + match.group("label")
                + "."
                + directive
                + match.group("sep")
                + expr
                + match.group("suffix")
            )
            changes.append(
                {
                    "file": path.as_posix(),
                    "line": lineno,
                    "kind": "literal",
                    "old": operand,
                    "new": expr,
                    "line_text": new_body + ending,
                }
            )
        elif operand == expr:
            # Already applied, keep the file byte-identical.
            continue
        else:
            errors.append(
                f"{path}:{lineno}: operand is {operand!r}, expected "
                f"{record['value']} or {expr}"
            )

    return changes, errors


def verify_change(change: dict) -> str | None:
    """Re-parse a planned line; the dry run must show a real rewrite."""
    body = change["line_text"].rstrip("\r\n")
    if change.get("kind") == "ldr_literal":
        match = LDR_LITERAL_RE.match(body)
        expected = "ldr pseudo-literal"
    else:
        match = LITERAL_RE.match(body)
        expected = ".4byte/.word literal"
    if match is None:
        return (
            f"{change['file']}:{change['line']}: planned rewrite no longer "
            f"parses as a {expected}"
        )
    if match.group("operand") != change["new"]:
        return (
            f"{change['file']}:{change['line']}: planned rewrite has operand "
            f"{match.group('operand')!r}, expected {change['new']!r}"
        )
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument(
        "files",
        nargs="*",
        help="explicit assembly files to process (default: every file in the ledger)",
    )
    ap.add_argument("--refs", default="work/shift/abs_refs.json", help="audit ledger")
    ap.add_argument("--elf", default="mf_us.elf", help="baseline ELF for symbol bindings/anchors")
    ap.add_argument("--dry-run", action="store_true", help="show replacements without writing")
    ap.add_argument("--check", action="store_true", help="fail if any literal still needs rewriting")
    args = ap.parse_args()

    try:
        records = load_records(Path(args.refs))
    except (OSError, json.JSONDecodeError, RefError) as exc:
        print(f"apply_refs: {exc}", file=sys.stderr)
        return 1

    elf = None
    elf_path = Path(args.elf)
    if elf_path.exists():
        try:
            elf = ElfSymbols.load(elf_path)
        except (OSError, RefError) as exc:
            print(f"apply_refs: {exc}", file=sys.stderr)
            return 1
    elif records:
        print(
            f"apply_refs: warning: {elf_path} not found; "
            "local symbols cannot be detected",
            file=sys.stderr,
        )

    ledger_files = {path_key(r["file"]) for r in records}
    requested: set[Path] | None = None
    if args.files:
        requested = {path_key(f) for f in args.files}
        missing = sorted(str(p) for p in requested if not p.exists())
        if missing:
            for name in missing:
                print(f"apply_refs: missing input file {name}", file=sys.stderr)
            return 1

    selected: dict[Path, list[dict]] = {}
    for record in records:
        key = path_key(record["file"])
        if requested is not None and key not in requested:
            continue
        selected.setdefault(key, []).append(record)

    if requested is not None:
        empty = requested - set(selected)
        for path in sorted(empty):
            print(f"apply_refs: no ROM literals in {path}")

    all_changes: list[dict] = []
    all_errors: list[str] = []
    for path, file_records in sorted(selected.items(), key=lambda item: str(item[0])):
        changes, errors = plan_file(path, file_records, elf)
        all_changes.extend(changes)
        all_errors.extend(errors)

    # Dry-run safety: re-parse every planned line and confirm it now carries
    # exactly the expected symbol expression.  A bad plan is refused in every
    # mode, before anything is written.
    if not all_errors:
        for change in all_changes:
            problem = verify_change(change)
            if problem is not None:
                all_errors.append(problem)

    if all_errors:
        for message in all_errors:
            print(f"apply_refs: ERROR: {message}", file=sys.stderr)
        print(
            f"apply_refs: refusing to apply ({len(all_errors)} error(s))",
            file=sys.stderr,
        )
        return 1

    total = len(records) if requested is None else sum(len(v) for v in selected.values())
    applied = total - len(all_changes)

    if args.check:
        if all_changes:
            for change in all_changes:
                print(
                    f"  {change['file']}:{change['line']}: "
                    f"{change['old']} -> {change['new']}"
                )
            print(
                f"FAIL: {len(all_changes)} of {total} ROM literals still need rewriting"
            )
            return 1
        print(f"PASS: {total} ROM literals already rewritten")
        return 0

    if args.dry_run:
        for change in all_changes:
            print(
                f"  {change['file']}:{change['line']}: "
                f"{change['old']} -> {change['new']}"
            )
        print(f"dry-run: {len(all_changes)} to rewrite, {applied} already applied")
        return 0

    by_file: dict[str, list[dict]] = {}
    for change in all_changes:
        by_file.setdefault(change["file"], []).append(change)
    for name, changes in by_file.items():
        path = Path(name)
        with path.open("r", encoding="utf-8", newline="") as handle:
            lines = handle.readlines()
        for change in changes:
            lines[change["line"] - 1] = change["line_text"]
        with path.open("w", encoding="utf-8", newline="") as handle:
            handle.writelines(lines)

    print(
        f"apply_refs: {len(all_changes)} rewritten, {applied} already applied, "
        f"{len(selected)} file(s)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
