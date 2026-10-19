#!/usr/bin/env python3
"""Post-link scan for remaining raw ROM pointer words in data sections.

The shift audits find hardcoded pointer literals in source files.  This tool
finds the pointers that only become visible *after* linking: a partially
converted table may leave some raw ``0x08xxxxxx`` words in ``.rodata`` or
``.data`` while the surrounding entries are relocations.  Such a word survives
a repositioned link as a stale absolute address and is exactly the BUG-009 /
BUG-013 failure class.

The scan is deliberately conservative:

* only allocated PROGBITS sections in ROM that are not executable are read
  (``.rodata`` and ``.data``; never code bytes);
* a word covered by any relocation is already position-independent and is
  ignored;
* a single pointer-like word is not a finding (graphics data contains ~21k
  isolated coincidences);
* only structured runs at the measured table strides fail:
  ``0x4``/8, ``0x8``/6, ``0xC``/4, ``0x18``/4, ``0x24``/4;
* a run must have distinct targets (>= 0.75) and its targets must resolve to
  known ELF sections (>= 0.90); data targets must be 2-byte aligned and Thumb
  code targets must have bit 0 set (an exact symbol is also accepted for an
  even ARM-state code target).

The ELF must have been linked with ``--emit-relocs``.  A normal link has no
relocation sections and cannot distinguish converted pointers from raw ones;
strict mode fails closed in that case.

Examples::

    python3 tools/shift/postlink_pointer_scan.py --self-check
    python3 tools/shift/postlink_pointer_scan.py --elf mf_us.elf --map mf_us.map
    python3 tools/shift/postlink_pointer_scan.py --elf mf_us.elf --map mf_us.map \
        --strict --json-out work/shift/postlink_scan.json

A whitelist is a JSON list of inclusive ROM address ranges::

    [{"start": "0x0865BB98", "end": "0x0865BCF0", "reason": "known table"}]

``--write-whitelist FILE`` writes the current findings in that format for human
review; it never changes the exit status and does not auto-accept anything.
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_symbols import SymbolMap  # noqa: E402

ROM_START = 0x08000000
ROM_END = 0x0A000000
HEADER_END = 0x080000C0

SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_RELA = 4
SHT_NOBITS = 8
SHT_REL = 9

SHF_ALLOC = 0x2
SHF_EXECINSTR = 0x4

ET_REL = 1
ET_EXEC = 2

# (stride, minimum entries).  These are the only shapes that survive on the
# measured tree; see docs/roadmap.md and the BUG-013 triage notes.
STRIDES = ((0x4, 8), (0x8, 6), (0xC, 4), (0x18, 4), (0x24, 4))

UNIQUE_MIN = 0.75
KNOWN_MIN = 0.90
ALIGNED_MIN = 0.90

TARGET_DETAIL = 4
TARGET_JSON_DETAIL = 16


class ScanError(Exception):
    """The input cannot be scanned safely."""


@dataclass(frozen=True)
class ElfSection:
    index: int
    name: str
    sh_type: int
    flags: int
    addr: int
    offset: int
    size: int
    link: int
    info: int
    align: int
    entsize: int

    @property
    def allocated(self) -> bool:
        return bool(self.flags & SHF_ALLOC)

    @property
    def executable(self) -> bool:
        return bool(self.flags & SHF_EXECINSTR)

    @property
    def in_rom(self) -> bool:
        return ROM_START <= self.addr < ROM_END

    @property
    def end(self) -> int:
        return self.addr + self.size


@dataclass(frozen=True)
class TargetInfo:
    address: int
    section: str | None
    code: bool
    exact_symbol: str | None
    symbol: str | None
    symbol_offset: int | None

    @property
    def known(self) -> bool:
        return self.section is not None

    @property
    def aligned(self) -> bool:
        if self.section is None:
            return False
        if self.code:
            # GBA Thumb function pointers have bit 0 set.  An exact symbol also
            # makes an even address a legitimate ARM-state code target.
            return bool(self.address & 1) or bool(self.exact_symbol)
        # Data pointers are at least halfword aligned.
        return (self.address & 1) == 0


@dataclass
class PointerRun:
    section: str
    section_index: int
    start: int
    end: int
    stride: int
    addresses: list[int]
    targets: list[int]
    target_infos: list[TargetInfo]
    unique_ratio: float
    known_ratio: float
    aligned_ratio: float
    source_symbol: str | None
    source_offset: int | None
    target_sections: list[tuple[str, int]]

    @property
    def count(self) -> int:
        return len(self.addresses)


class ElfImage:
    """Minimal ELF32 little-endian reader with relocation coverage."""

    def __init__(
        self,
        path: Path,
        data: bytes,
        e_type: int,
        sections: list[ElfSection],
        relocations_by_section: dict[int, set[int]],
        relocation_entries: int,
        relocation_sections: int,
    ) -> None:
        self.path = path
        self.data = data
        self.e_type = e_type
        self.sections = sections
        self.relocations_by_section = relocations_by_section
        self.relocation_entries = relocation_entries
        self.relocation_sections = relocation_sections

    @classmethod
    def load(cls, path: Path) -> "ElfImage":
        try:
            data = path.read_bytes()
        except OSError as exc:
            raise ScanError(f"{path}: {exc}") from exc
        if len(data) < 0x34 or data[:4] != b"\x7fELF":
            raise ScanError(f"{path}: not an ELF file")
        if data[4] != 1 or data[5] != 1:
            raise ScanError(f"{path}: not a little-endian ELF32 file")

        e_type, _machine = struct.unpack_from("<HH", data, 0x10)
        e_shoff = struct.unpack_from("<I", data, 0x20)[0]
        e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
        e_shnum = struct.unpack_from("<H", data, 0x30)[0]
        e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
        if not e_shoff or not e_shnum or e_shentsize < 40:
            raise ScanError(f"{path}: missing or truncated section headers")
        if e_shstrndx >= e_shnum:
            raise ScanError(f"{path}: bad section-name table index")

        raw_sections: list[tuple[int, ...]] = []
        for i in range(e_shnum):
            off = e_shoff + i * e_shentsize
            if off + 40 > len(data):
                raise ScanError(f"{path}: truncated section table")
            raw_sections.append(struct.unpack_from("<IIIIIIIIII", data, off))

        def cstring(offset: int) -> str:
            if offset < 0 or offset >= len(data):
                return ""
            end = data.find(b"\x00", offset)
            if end < 0:
                return ""
            return data[offset:end].decode("ascii", "replace")

        shstr = raw_sections[e_shstrndx]
        names = [cstring(shstr[4] + raw[0]) for raw in raw_sections]
        sections = [
            ElfSection(
                index=i,
                name=names[i],
                sh_type=raw[1],
                flags=raw[2],
                addr=raw[3],
                offset=raw[4],
                size=raw[5],
                link=raw[6],
                info=raw[7],
                align=raw[8],
                entsize=raw[9],
            )
            for i, raw in enumerate(raw_sections)
        ]

        relocations_by_section: dict[int, set[int]] = {}
        relocation_entries = 0
        relocation_sections = 0
        for sec in sections:
            if sec.sh_type not in (SHT_REL, SHT_RELA):
                continue
            if not (0 <= sec.info < len(sections)):
                continue
            target = sections[sec.info]
            entry_size = sec.entsize or (8 if sec.sh_type == SHT_REL else 12)
            if entry_size < 8:
                raise ScanError(f"{path}: bad relocation entry size in {sec.name}")
            if sec.offset + sec.size > len(data):
                raise ScanError(f"{path}: relocation section {sec.name} is truncated")
            covered = relocations_by_section.setdefault(target.index, set())
            for off in range(sec.offset, sec.offset + sec.size, entry_size):
                if off + 8 > len(data):
                    break
                r_offset = struct.unpack_from("<I", data, off)[0]
                # ET_REL stores an offset within the target section.  Linked
                # ELFs (the intended input) store the final address already.
                if e_type == ET_REL:
                    r_offset += target.addr
                covered.add(r_offset)
                relocation_entries += 1
            relocation_sections += 1

        return cls(
            path,
            data,
            e_type,
            sections,
            relocations_by_section,
            relocation_entries,
            relocation_sections,
        )

    def section_at(self, addr: int) -> ElfSection | None:
        candidates = [
            sec
            for sec in self.sections
            if sec.allocated
            and sec.size
            and sec.sh_type in (SHT_PROGBITS, SHT_NOBITS)
            and sec.addr <= addr < sec.end
        ]
        if not candidates:
            return None
        return min(candidates, key=lambda sec: (sec.size, sec.addr))

    def words(self, section: ElfSection) -> dict[int, int]:
        if section.sh_type != SHT_PROGBITS:
            return {}
        if section.offset + section.size > len(self.data):
            raise ScanError(f"{self.path}: section {section.name} is truncated")
        end = section.offset + section.size
        return {
            section.addr + delta: struct.unpack_from("<I", self.data, section.offset + delta)[0]
            for delta in range(0, section.size - 3, 4)
        }


@dataclass(frozen=True)
class WhitelistRange:
    start: int
    end: int
    reason: str

    def contains(self, addr: int) -> bool:
        return self.start <= addr <= self.end


def parse_address(value: object, what: str) -> int:
    if isinstance(value, bool):
        raise ScanError(f"whitelist {what}: expected an address, got a boolean")
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        text = value.strip()
        try:
            return int(text, 0)
        except ValueError as exc:
            raise ScanError(f"whitelist {what}: bad address {value!r}") from exc
    raise ScanError(f"whitelist {what}: expected int or hex string, got {type(value).__name__}")


def load_whitelist(path: Path | None) -> list[WhitelistRange]:
    if path is None:
        return []
    try:
        raw = json.loads(path.read_text())
    except OSError as exc:
        raise ScanError(f"{path}: {exc}") from exc
    except json.JSONDecodeError as exc:
        raise ScanError(f"{path}: invalid JSON: {exc}") from exc
    if not isinstance(raw, list):
        raise ScanError(f"{path}: whitelist must be a JSON list")
    ranges: list[WhitelistRange] = []
    for i, item in enumerate(raw):
        if not isinstance(item, dict):
            raise ScanError(f"{path}: entry {i} must be an object")
        if "start" not in item or "end" not in item or "reason" not in item:
            raise ScanError(f"{path}: entry {i} needs start, end and reason")
        start = parse_address(item["start"], f"entry {i} start")
        end = parse_address(item["end"], f"entry {i} end")
        if start > end:
            raise ScanError(f"{path}: entry {i} has start > end")
        if not (ROM_START <= start < ROM_END and ROM_START <= end < ROM_END):
            raise ScanError(f"{path}: entry {i} is not in the ROM window")
        reason = str(item["reason"])
        ranges.append(WhitelistRange(start, end, reason))
    ranges.sort(key=lambda r: (r.start, r.end))
    return ranges


def whitelisted(addr: int, whitelist: list[WhitelistRange]) -> bool:
    return any(r.contains(addr) for r in whitelist)


def collect_candidates(
    section: ElfSection,
    words: dict[int, int],
    relocated: set[int],
    whitelist: list[WhitelistRange],
) -> dict[int, int]:
    """Return address -> value for unrelocated ROM-pointer words."""
    candidates: dict[int, int] = {}
    for addr in sorted(words):
        if addr < HEADER_END:
            continue
        value = words[addr]
        if not (ROM_START <= value < ROM_END):
            continue
        if addr in relocated:
            continue
        if whitelisted(addr, whitelist):
            continue
        candidates[addr] = value
    return candidates


def detect_runs(
    section: ElfSection,
    candidates: dict[int, int],
    resolve_target,
) -> list[PointerRun]:
    """Find structured pointer runs in one section.

    ``resolve_target`` maps a target address to :class:`TargetInfo`.  Keeping it
    as a callback makes the detection logic testable without an ELF file.
    """
    if not candidates:
        return []
    found: list[PointerRun] = []
    for stride, minimum in STRIDES:
        address_set = set(candidates)
        for start in sorted(address_set):
            if start - stride in address_set:
                continue
            addresses: list[int] = []
            current = start
            while current in address_set:
                addresses.append(current)
                current += stride
            if len(addresses) < minimum:
                continue

            targets = [candidates[addr] for addr in addresses]
            unique_ratio = len(set(targets)) / len(targets)
            target_infos = [resolve_target(target) for target in targets]
            known_ratio = sum(1 for info in target_infos if info.known) / len(target_infos)
            aligned_ratio = sum(1 for info in target_infos if info.aligned) / len(target_infos)
            if unique_ratio < UNIQUE_MIN:
                continue
            if known_ratio < KNOWN_MIN:
                continue
            if aligned_ratio < ALIGNED_MIN:
                continue

            section_counts: dict[str, int] = {}
            for info in target_infos:
                name = info.section or "unknown"
                section_counts[name] = section_counts.get(name, 0) + 1
            target_sections = sorted(
                section_counts.items(), key=lambda pair: (-pair[1], pair[0])
            )
            found.append(
                PointerRun(
                    section=section.name,
                    section_index=section.index,
                    start=addresses[0],
                    end=addresses[-1],
                    stride=stride,
                    addresses=addresses,
                    targets=targets,
                    target_infos=target_infos,
                    unique_ratio=unique_ratio,
                    known_ratio=known_ratio,
                    aligned_ratio=aligned_ratio,
                    source_symbol=None,
                    source_offset=None,
                    target_sections=target_sections,
                )
            )
    return found


def self_check() -> int:
    """Synthetic run-detection checks; no ELF or map needed."""
    checks: list[tuple[str, bool]] = []

    def section() -> ElfSection:
        return ElfSection(
            index=7,
            name=".rodata",
            sh_type=SHT_PROGBITS,
            flags=SHF_ALLOC,
            addr=0x08100000,
            offset=0,
            size=0x1000,
            link=0,
            info=0,
            align=4,
            entsize=0,
        )

    def resolver(addr: int) -> TargetInfo:
        # Data window covers the synthetic table targets; code window exercises
        # the Thumb-bit rule.
        if 0x08080000 <= addr < 0x08110000:
            return TargetInfo(addr, ".rodata", False, None, "data", addr - 0x08080000)
        if 0x08001000 <= addr < 0x0800F000:
            exact = "thumb_func" if addr & 1 else None
            return TargetInfo(addr, "rom", True, exact, "code", addr - 0x08001000)
        return TargetInfo(addr, None, False, None, None, None)

    # 1. An unrelocated 8-byte-stride run is found.
    words: dict[int, int] = {}
    for i in range(8):
        words[0x08100100 + i * 8] = 0x08090000 + i * 4
    candidates = collect_candidates(section(), words, set(), [])
    runs = detect_runs(section(), candidates, resolver)
    checks.append(
        (
            "8-byte-stride unrelocated run found",
            any(run.stride == 0x8 and run.count == 8 for run in runs),
        )
    )

    # 2. A run whose entries all point at the same word is coincidental noise.
    repeated: dict[int, int] = {}
    for i in range(8):
        repeated[0x08100200 + i * 8] = 0x08090000
    candidates = collect_candidates(section(), repeated, set(), [])
    runs = detect_runs(section(), candidates, resolver)
    checks.append(("repeated-target run rejected", not runs))

    # 3. Relocation-covered words are not candidates at all.
    relocated_words: dict[int, int] = {}
    for i in range(8):
        relocated_words[0x08100300 + i * 8] = 0x08090000 + i * 4
    candidates = collect_candidates(
        section(), relocated_words, set(relocated_words), []
    )
    runs = detect_runs(section(), candidates, resolver)
    checks.append(("relocated run not reported", not candidates and not runs))

    # 4. A whitelisted run is suppressed before detection.
    allowed = [WhitelistRange(0x08100100, 0x08100138, "self-check")]
    candidates = collect_candidates(section(), words, set(), allowed)
    runs = detect_runs(section(), candidates, resolver)
    checks.append(("whitelisted run suppressed", not runs))

    passed = sum(1 for _name, ok in checks if ok)
    for name, ok in checks:
        print(f"self-check: {'PASS' if ok else 'FAIL'}: {name}")
    print(f"self-check: {passed}/{len(checks)} passed")
    return 0 if passed == len(checks) else 1


def run_scan(
    image: ElfImage,
    symbols: SymbolMap,
    whitelist: list[WhitelistRange],
) -> tuple[list[PointerRun], list[dict[str, int | str]]]:
    scanned = [
        sec
        for sec in image.sections
        if sec.sh_type == SHT_PROGBITS
        and sec.allocated
        and sec.in_rom
        and not sec.executable
        and sec.size
    ]
    if not scanned:
        raise ScanError("no allocated non-executable PROGBITS section in ROM")

    def resolve_target(addr: int) -> TargetInfo:
        sec = image.section_at(addr)
        resolved = symbols.resolve(addr)
        return TargetInfo(
            address=addr,
            section=sec.name if sec else None,
            code=bool(sec and sec.executable),
            exact_symbol=resolved["symbol"] if resolved["exact"] else None,
            symbol=resolved["symbol"],
            symbol_offset=resolved["offset"],
        )

    summary: list[dict[str, int | str]] = []
    runs: list[PointerRun] = []
    for sec in scanned:
        words = image.words(sec)
        relocated = image.relocations_by_section.get(sec.index, set())
        candidates = collect_candidates(sec, words, relocated, whitelist)
        section_runs = detect_runs(sec, candidates, resolve_target)
        for run in section_runs:
            resolved_source = symbols.resolve(run.start)
            run.source_symbol = resolved_source["symbol"]
            run.source_offset = resolved_source["offset"]
        runs.extend(section_runs)
        summary.append(
            {
                "section": sec.name,
                "start": sec.addr,
                "end": sec.end,
                "words": len(words),
                "relocated": len(relocated),
                "candidates": len(candidates),
            }
        )

    runs.sort(key=lambda run: (-run.count, run.stride, run.start, run.section))
    return runs, summary


def run_to_dict(run: PointerRun) -> dict:
    detail = min(len(run.targets), TARGET_JSON_DETAIL)
    targets = []
    for i in range(detail):
        info = run.target_infos[i]
        targets.append(
            {
                "address": f"0x{info.address:08X}",
                "section": info.section,
                "code": info.code,
                "symbol": info.symbol,
                "offset": info.symbol_offset,
            }
        )
    return {
        "section": run.section,
        "start": f"0x{run.start:08X}",
        "end": f"0x{run.end:08X}",
        "stride": f"0x{run.stride:X}",
        "count": run.count,
        "unique_ratio": round(run.unique_ratio, 4),
        "known_ratio": round(run.known_ratio, 4),
        "aligned_ratio": round(run.aligned_ratio, 4),
        "source_symbol": run.source_symbol,
        "source_offset": run.source_offset,
        "target_sections": [
            {"section": name, "count": count} for name, count in run.target_sections
        ],
        "targets": targets,
        "targets_truncated": len(run.targets) > detail,
    }


def target_text(info: TargetInfo) -> str:
    symbol = ""
    if info.symbol is not None:
        offset = info.symbol_offset or 0
        symbol = f" {info.symbol}" + (f"+0x{offset:X}" if offset else "")
    section = info.section or "unknown"
    return f"0x{info.address:08X} [{section}]{symbol}"


def print_report(
    image: ElfImage,
    map_path: Path,
    whitelist: list[WhitelistRange],
    runs: list[PointerRun],
    summary: list[dict[str, int | str]],
    strict: bool,
) -> None:
    print("# Post-link pointer scan")
    print()
    print(f"- elf: `{image.path}`")
    print(f"- map: `{map_path}`")
    print(
        f"- relocations: {image.relocation_sections} section(s), "
        f"{image.relocation_entries} word(s)"
    )
    for item in summary:
        print(
            f"- scan `{item['section']}` 0x{item['start']:08X}..0x{item['end']:08X}: "
            f"{item['words']} words, {item['relocated']} relocated, "
            f"{item['candidates']} candidates"
        )
    if whitelist:
        print(f"- whitelist: {len(whitelist)} range(s)")
        for item in whitelist:
            print(
                f"  - 0x{item.start:08X}..0x{item.end:08X} ({item.reason})"
            )
    else:
        print("- whitelist: none")
    print(f"- findings: {len(runs)}")
    print()
    if not runs:
        print("No structured pointer runs found.")
        print()
        print("RESULT: PASS — no structured pointer runs")
        return

    print(
        "| # | count | stride | unique | section | start..end | source | "
        "target sections | first targets |"
    )
    print("|---:|---:|---:|---:|---|---|---|---|---|")
    for i, run in enumerate(runs, 1):
        source = run.source_symbol or "unknown"
        if run.source_offset:
            source += f"+0x{run.source_offset:X}"
        first = "<br>".join(
            target_text(info)
            for info in run.target_infos[:TARGET_DETAIL]
        )
        sections = ", ".join(
            f"{name}:{count}" for name, count in run.target_sections
        )
        print(
            f"| {i} | {run.count} | 0x{run.stride:X} | {run.unique_ratio:.2f} | "
            f"{run.section} | 0x{run.start:08X}..0x{run.end:08X} | "
            f"`{source}` | {sections} | {first} |"
        )
    print()
    verdict = "FAIL" if strict else "REPORT"
    print(f"RESULT: {verdict} — {len(runs)} structured pointer run(s)")
    if not strict:
        print("(report mode: exit 0; use --strict to fail on these runs)")


def write_whitelist(path: Path, runs: list[PointerRun]) -> None:
    entries = []
    for run in runs:
        source = run.source_symbol or "unknown"
        if run.source_offset:
            source += f"+0x{run.source_offset:X}"
        entries.append(
            {
                "start": f"0x{run.start:08X}",
                "end": f"0x{run.end:08X}",
                "reason": (
                    f"{run.section} stride 0x{run.stride:X} count {run.count} "
                    f"source {source}"
                ),
            }
        )
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(entries, indent=2) + "\n")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Scan a linked --emit-relocs ELF for raw ROM pointer tables."
    )
    parser.add_argument("--elf", default="mf_us.elf", help="linked ELF (default: mf_us.elf)")
    parser.add_argument("--map", default="mf_us.map", help="linker map (default: mf_us.map)")
    parser.add_argument("--whitelist", help="JSON list of accepted address ranges")
    parser.add_argument("--json-out", help="write machine-readable findings to this path")
    parser.add_argument(
        "--write-whitelist",
        metavar="FILE",
        help="write current runs as a reviewable whitelist (does not accept them)",
    )
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--strict", action="store_true", help="exit 1 on any finding")
    mode.add_argument("--report", action="store_true", help="report only (default)")
    parser.add_argument("--self-check", action="store_true", help="run synthetic detection checks")
    args = parser.parse_args(argv)

    if args.self_check:
        return self_check()

    strict = bool(args.strict)
    elf_path = Path(args.elf)
    map_path = Path(args.map)

    try:
        whitelist = load_whitelist(Path(args.whitelist) if args.whitelist else None)
        image = ElfImage.load(elf_path)
        if image.relocation_sections == 0:
            message = (
                f"{elf_path}: no relocation sections; relink with --emit-relocs"
            )
            if strict:
                raise ScanError(message)
            print(f"warning: {message}", file=sys.stderr)
        if not map_path.exists():
            raise ScanError(f"{map_path}: map file not found")
        symbols = SymbolMap.load(map_path, elf_path)
        runs, summary = run_scan(image, symbols, whitelist)
    except ScanError as exc:
        print(f"postlink-pointer-scan: error: {exc}", file=sys.stderr)
        return 2

    print_report(image, map_path, whitelist, runs, summary, strict)

    if args.write_whitelist:
        out = Path(args.write_whitelist)
        write_whitelist(out, runs)
        print(f"whitelist written: {out} ({len(runs)} range(s); review before use)")

    if args.json_out:
        payload = {
            "elf": str(elf_path),
            "map": str(map_path),
            "strict": strict,
            "relocations": {
                "sections": image.relocation_sections,
                "words": image.relocation_entries,
            },
            "scanned_sections": summary,
            "whitelist": [
                {
                    "start": f"0x{item.start:08X}",
                    "end": f"0x{item.end:08X}",
                    "reason": item.reason,
                }
                for item in whitelist
            ],
            "finding_count": len(runs),
            "runs": [run_to_dict(run) for run in runs],
        }
        out = Path(args.json_out)
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(payload, indent=2) + "\n")
        print(f"json: {out}")

    if strict and runs:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
