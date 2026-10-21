#!/usr/bin/env python3
"""Attach symbol names to ROM addresses that appear in source comments.

The shipped disassembly keeps the original target of every `ldr` literal in an
`@` comment::

    ldr r3, _080a568c @ =0x080A568C

Those comments are reference-only (they do not assemble), but they are the map
from an instruction to the data it reads.  Rewriting the raw address to a
symbol makes the comment auditable and stable when the link moves::

    ldr r3, _080a568c @ =0x080A568C (sBlob_a5710_a8cdc+0x0B7C)

This tool is comment-only.  It never edits an instruction, a directive, or a
literal operand; it inserts a parenthetical label immediately after the
address token.  It is idempotent: a line that already carries the right label
is left byte-for-byte alone, and a second run reports it as `already`.

Scope
-----
ROM addresses are `0x08000000..0x09FFFFFF` (the GBA cartridge window).  The
default scope, `references`, annotates every ROM address in a comment except a
label definition such as ``GunshipEndInit: @ 0x08056278`` -- that line already
states its own symbol.  `--scope ldr` restricts the edit to lines whose code
part contains `ldr`; `--scope all` includes label definitions and prose.

Resolution policy
-----------------
An address is annotated only when it resolves to **one** symbol:

* an exact symbol wins over a containing one;
* otherwise the innermost containing symbol (the nearest preceding symbol
  whose assigned size covers the address) is used, with `+0xOFFSET`;
* aliases at the same address (two different non-auto names) are ambiguous and
  are reported as `unknown`, not guessed;
* names that only encode the address -- assembler locals such as
  `_08056300`, and `unk_475C` / `sub_08056300` -- are not semantic, so they are
  skipped (`auto_name`).  Established anchors such as `sBlob_...`,
  `sUnk_...` and ordinary `g...`/`s...` names are used as-is.  No name is
  invented: an address with no symbol stays unannotated.

Files
-----
With no positional paths the tool asks Git for tracked `asm/**/*.s` and
`src/**/*.c`, so ignored generated sources (`src/*.s`, `hack/gen`, `work`) are
never scanned.  Positional paths or `--files` may point at individual files or
directories; unsupported suffixes and object files are ignored.

Usage
-----
    python3 tools/shift/label_comments.py --check --json
    python3 tools/shift/label_comments.py --check --files asm
    python3 tools/shift/label_comments.py --write --limit 100
    python3 tools/shift/label_comments.py --self-check

`--check` is the default and never writes.  `--write` rewrites only lines that
need a label, caps at `--limit` pending edits (deterministically ordered by
file/line/column), and reports the rest as `deferred`.  `--strict` turns a
non-empty `--check` into exit status 1; it is deliberately not wired into the
relocation gate.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable, Optional

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_symbols import SymbolMap  # noqa: E402

ROM_START = 0x08000000
ROM_END = 0x0A000000

# Eight hex digits are the canonical ROM spelling; 1-8 are accepted so the
# short `0x80a5710` form used by the audio headers is covered too.  Whether a
# token is a ROM address is decided by value, not width (see `is_rom`).
ADDR_RE = re.compile(r"\b0x([0-9a-fA-F]{1,8})\b")
# The label this tool writes: `(Symbol)` or `(Symbol+0xOFF)`.
LABEL_RE = re.compile(
    r"[ \t]*\(([A-Za-z_.$][\w.$@]*)(?:\+0x[0-9A-Fa-f]+)?\)"
)
LABEL_DECL_RE = re.compile(r"^\s*[A-Za-z_.$][\w.$@]*:\s*@")
LDR_RE = re.compile(r"(?:^|[\s,])ldr[a-z]*(?:[\s,]|$)")
# Address-only names: not worth attaching because the reader already has the
# address.  This is a naming policy, not a claim that the symbol is unused.
AUTO_NAME_RE = re.compile(r"^(?:_[0-9A-Fa-f]{4,8}|(?:unk|sub)_[0-9A-Fa-f]{1,8})$")

ASM_SUFFIXES = {".s"}
C_SUFFIXES = {".c", ".h"}
SKIP_DIRS = {".git", "work", "build", "obj", "gen", "__pycache__"}


def is_rom(addr: int) -> bool:
    return ROM_START <= addr < ROM_END


def is_auto_name(name: str) -> bool:
    return bool(AUTO_NAME_RE.match(name))


def format_label(symbol: str, offset: int) -> str:
    return symbol if offset == 0 else f"{symbol}+0x{offset:X}"


@dataclass(frozen=True)
class Resolved:
    symbol: str
    offset: int


def resolve_entries(
    entries: Iterable[tuple[int, int, str]], addr: int
) -> Optional[Resolved]:
    """Resolve `addr` in a list of `(start, end, name)` entries.

    Exact symbols win.  Otherwise the innermost entry (`max(start)`) whose
    half-open range contains the address is used.  Multiple distinct names at
    the winning start are ambiguous; return None instead of guessing.
    ``end`` is 0 for symbols without a known size and never contains an
    address.
    """
    exact = sorted({name for start, _end, name in entries if start == addr})
    if len(exact) == 1:
        return Resolved(exact[0], 0)
    if len(exact) > 1:
        return None

    containing = [
        (start, name) for start, end, name in entries if start <= addr < end
    ]
    if not containing:
        return None
    nearest = max(start for start, _name in containing)
    names = sorted({name for start, name in containing if start == nearest})
    if len(names) != 1:
        return None
    return Resolved(names[0], addr - nearest)


class MapSymbolDb:
    """Resolver backed by `map_symbols.SymbolMap` (map + optional ELF)."""

    def __init__(self, sm: SymbolMap) -> None:
        self.sm = sm
        self.raw_entries = [(sym.addr, sym.end, sym.name) for sym in sm.symbols]
        self.entries = [
            (addr, end, name)
            for addr, end, name in self.raw_entries
            if not is_auto_name(name)
        ]

    def resolve(self, addr: int) -> Optional[Resolved]:
        if not is_rom(addr):
            return None
        return resolve_entries(self.entries, addr)

    def raw_resolve(self, addr: int) -> Optional[Resolved]:
        if not is_rom(addr):
            return None
        return resolve_entries(self.raw_entries, addr)


# ---------------------------------------------------------------------------
# Comment scanning
# ---------------------------------------------------------------------------


def _asm_comment_span(line: str) -> tuple[int, int] | None:
    """GAS ARM uses `@` for a line comment; the first one starts the span."""
    idx = line.find("@")
    if idx < 0:
        return None
    return idx, len(line)


def _c_comment_spans(
    line: str, in_block: bool
) -> tuple[list[tuple[int, int]], bool]:
    """Return C/C++ comment spans and the block-comment state after `line`.

    Strings and character literals are skipped so `//` inside a string is not
    mistaken for a comment.  A block comment may span lines.
    """
    spans: list[tuple[int, int]] = []
    i = 0
    n = len(line)
    while i < n:
        if in_block:
            end = line.find("*/", i)
            if end < 0:
                spans.append((i, n))
                return spans, True
            spans.append((i, end + 2))
            in_block = False
            i = end + 2
            continue
        ch = line[i]
        if ch in {'"', "'"}:
            quote = ch
            i += 1
            while i < n:
                if line[i] == "\\":
                    i += 2
                    continue
                if line[i] == quote:
                    i += 1
                    break
                i += 1
            continue
        if line.startswith("//", i):
            spans.append((i, n))
            return spans, False
        if line.startswith("/*", i):
            in_block = True
            i += 2
            continue
        i += 1
    return spans, in_block


def comment_spans(
    line: str, suffix: str, in_block: bool = False
) -> tuple[list[tuple[int, int]], bool]:
    if suffix in ASM_SUFFIXES:
        span = _asm_comment_span(line)
        return ([span] if span else []), False
    return _c_comment_spans(line, in_block)


# ---------------------------------------------------------------------------
# Annotation
# ---------------------------------------------------------------------------


@dataclass
class Occurrence:
    file: str
    line: int
    column: int
    address: int
    token: str
    status: str
    scope: str
    symbol: Optional[str] = None
    offset: Optional[int] = None
    label: Optional[str] = None
    annotation: Optional[str] = None
    before: str = ""
    after: str = ""

    def to_dict(self) -> dict:
        return {
            "file": self.file,
            "line": self.line,
            "column": self.column,
            "address": f"0x{self.address:08X}",
            "token": self.token,
            "status": self.status,
            "symbol": self.symbol,
            "offset": self.offset,
            "label": self.label,
            "annotation": self.annotation,
            "before": self.before,
            "after": self.after,
        }


def annotate_line(
    line: str,
    path: str,
    lineno: int,
    suffix: str,
    scope: str,
    db,
    in_block: bool = False,
) -> tuple[str, list[Occurrence], bool]:
    """Annotate ROM addresses in one line.

    Returns the new line, per-address occurrences, and the C block-comment
    state after the line.  The line is returned unchanged unless at least one
    address is newly labelled.
    """
    spans, new_block = comment_spans(line, suffix, in_block)
    if not spans:
        return line, [], new_block

    occurrences: list[Occurrence] = []
    code = line[: spans[0][0]]
    is_label = bool(LABEL_DECL_RE.match(line)) and suffix in ASM_SUFFIXES
    has_ldr = bool(LDR_RE.search(code))

    for span_start, span_end in spans:
        for match in ADDR_RE.finditer(line, span_start, span_end):
            digits = match.group(1)
            value = int(digits, 16)
            if not is_rom(value):
                # RAM/MMIO constants and short prose offsets are not ROM
                # references; leave them alone and do not report them.
                continue
            token = match.group(0)
            occurrence = Occurrence(
                file=path,
                line=lineno,
                column=match.start() + 1,
                address=value,
                token=token,
                status="pending",
                scope=scope,
                before=line.rstrip("\r\n"),
            )

            if scope == "ldr" and not has_ldr:
                occurrence.status = "skipped_scope"
                occurrence.after = occurrence.before
                occurrences.append(occurrence)
                continue
            if scope == "references" and is_label:
                occurrence.status = "skipped_label"
                occurrence.after = occurrence.before
                occurrences.append(occurrence)
                continue

            rest = line[match.end() :]
            existing = LABEL_RE.match(rest)
            resolved = db.resolve(value)
            if resolved is None:
                occurrence.status = "auto_name" if _resolves_to_auto(db, value) else "unknown"
                occurrence.after = occurrence.before
                occurrences.append(occurrence)
                continue

            label = format_label(resolved.symbol, resolved.offset)
            occurrence.symbol = resolved.symbol
            occurrence.offset = resolved.offset
            occurrence.label = label
            occurrence.annotation = f"({label})"

            if existing is not None:
                if existing.group(0).strip() == f"({label})":
                    occurrence.status = "already"
                else:
                    # A different label is stale.  Leave it for a human; never
                    # silently overwrite information this tool did not write.
                    occurrence.status = "stale"
                occurrence.after = occurrence.before
                occurrences.append(occurrence)
                continue

            occurrence.status = "labelled"
            occurrence.after = occurrence.before
            occurrences.append(occurrence)

    pending = [o for o in occurrences if o.status == "labelled"]
    if not pending:
        return line, occurrences, new_block

    # Insert right-to-left so earlier columns stay valid.  Each address is a
    # distinct match; the label is inserted immediately after the token.
    new_line = line
    for occurrence in sorted(pending, key=lambda o: o.column, reverse=True):
        end = occurrence.column - 1 + len(occurrence.token)
        new_line = new_line[:end] + f" ({occurrence.label})" + new_line[end:]
    for occurrence in occurrences:
        occurrence.after = new_line.rstrip("\r\n")
    return new_line, occurrences, new_block


def _resolves_to_auto(db, addr: int) -> bool:
    """True when the only symbol at/around `addr` is an address-derived name.

    `MapSymbolDb` filters those names out, so this is a diagnostic only.  The
    fixture resolver exposes `raw_resolve` when self-check needs it.
    """
    raw = getattr(db, "raw_resolve", None)
    if raw is None:
        return False
    result = raw(addr)
    return result is not None and is_auto_name(result.symbol)


# ---------------------------------------------------------------------------
# File discovery and IO
# ---------------------------------------------------------------------------


def _tracked_files(root: Path) -> list[Path]:
    try:
        proc = subprocess.run(
            ["git", "-C", str(root), "ls-files", "-z", "--", "asm", "src"],
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
        )
    except (OSError, subprocess.CalledProcessError):
        return []
    names = [n for n in proc.stdout.decode("utf-8", "replace").split("\0") if n]
    paths: list[Path] = []
    for name in names:
        path = Path(name)
        if path.suffix in ASM_SUFFIXES | C_SUFFIXES:
            paths.append(root / path if not path.is_absolute() else path)
    return paths


def discover_files(root: Path, explicit: list[str]) -> list[Path]:
    if explicit:
        candidates: list[Path] = []
        for item in explicit:
            path = Path(item)
            if not path.is_absolute():
                path = root / path
            if path.is_dir():
                candidates.extend(
                    p
                    for p in sorted(path.rglob("*"))
                    if p.suffix in ASM_SUFFIXES | C_SUFFIXES
                )
            else:
                candidates.append(path)
    else:
        candidates = _tracked_files(root)
        if not candidates:
            # Outside a Git checkout, fall back to the documented defaults.
            candidates = []
            for base in ("asm", "src"):
                directory = root / base
                if directory.is_dir():
                    candidates.extend(
                        p
                        for p in sorted(directory.rglob("*"))
                        if p.suffix in ASM_SUFFIXES | C_SUFFIXES
                    )

    kept: list[Path] = []
    for path in candidates:
        if path.suffix not in ASM_SUFFIXES | C_SUFFIXES:
            continue
        rel = _relative(path, root)
        parts = Path(rel).parts
        if any(part in SKIP_DIRS for part in parts):
            continue
        if "/hack/gen/" in f"/{rel}/":
            continue
        kept.append(path)
    # De-duplicate while preserving sorted order.
    unique = sorted({p.resolve(): p for p in kept}.values(), key=lambda p: _relative(p, root))
    return unique


def _relative(path: Path, root: Path) -> str:
    try:
        return path.resolve().relative_to(root.resolve()).as_posix()
    except ValueError:
        return path.as_posix()


def read_source(path: Path) -> str:
    # Bytes -> str -> bytes preserves CRLF exactly; `splitlines(keepends=True)`
    # keeps each line ending with its line.
    return path.read_bytes().decode("utf-8", "surrogateescape")


def write_source(path: Path, text: str) -> None:
    path.write_bytes(text.encode("utf-8", "surrogateescape"))


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------


def scan_file(
    path: Path,
    rel: str,
    scope: str,
    db,
) -> tuple[list[str], list[Occurrence]]:
    text = read_source(path)
    lines = text.splitlines(keepends=True)
    out: list[str] = []
    occurrences: list[Occurrence] = []
    in_block = False
    for lineno, line in enumerate(lines, 1):
        stripped = line.rstrip("\r\n")
        new_line, found, in_block = annotate_line(
            stripped, rel, lineno, path.suffix, scope, db, in_block
        )
        occurrences.extend(found)
        out.append(new_line + line[len(stripped) :])
    return out, occurrences


def summarize(occurrences: list[Occurrence], mode: str) -> dict:
    by_status: dict[str, int] = {}
    by_file: dict[str, int] = {}
    for occ in occurrences:
        by_status[occ.status] = by_status.get(occ.status, 0) + 1
        if occ.status in {"labelled", "deferred", "unknown", "stale", "auto_name"}:
            by_file[occ.file] = by_file.get(occ.file, 0) + 1
    candidates = [
        o
        for o in occurrences
        if o.status
        not in {"skipped_label", "skipped_scope"}
    ]
    labelled = by_status.get("labelled", 0)
    deferred = by_status.get("deferred", 0)
    return {
        "mode": mode,
        "occurrences": len(occurrences),
        "in_scope": len(candidates),
        "by_status": dict(sorted(by_status.items())),
        "by_file": dict(sorted(by_file.items())),
        # In check mode `pending` is the work a --write run would do.  In
        # write mode it is what the --limit left behind.
        "pending": deferred if mode == "write" else labelled,
        "would_label": labelled,
        "written": labelled if mode == "write" else 0,
        "already": by_status.get("already", 0),
        "unknown": by_status.get("unknown", 0),
        "stale": by_status.get("stale", 0),
        "auto_name": by_status.get("auto_name", 0),
        "deferred": deferred,
    }


def print_human(summary: dict, occurrences: list[Occurrence], sample: int = 8) -> None:
    print(
        f"label-comments: {summary['occurrences']} ROM comment address(es), "
        f"{summary['in_scope']} in scope ({summary['mode']})"
    )
    print(f"  by status: {summary['by_status']}")
    print(
        f"  labels: {summary['written'] or summary['pending']} pending/written, "
        f"{summary['already']} already, {summary['unknown']} unknown, "
        f"{summary['stale']} stale, {summary['auto_name']} auto-name, "
        f"{summary['deferred']} deferred"
    )
    files = summary["by_file"]
    if files:
        print("  files:")
        for name, count in list(files.items())[:15]:
            print(f"    {count:5d}  {name}")
        if len(files) > 15:
            print(f"    ... {len(files) - 15} more file(s)")
    if sample:
        shown = [o for o in occurrences if o.status in {"labelled", "deferred"}][:sample]
        if shown:
            print("  sample:")
            for occ in shown:
                print(f"    {occ.file}:{occ.line}: {occ.after.strip()}")


def write_report(path: Path, summary: dict, occurrences: list[Occurrence]) -> None:
    lines = [
        "# ROM address comment labels",
        "",
        f"- mode: `{summary['mode']}`",
        f"- occurrences: {summary['occurrences']}",
        f"- in scope: {summary['in_scope']}",
        f"- would label: {summary['would_label']}",
        f"- written: {summary['written']}",
        f"- remaining: {summary['pending']}",
        f"- already labelled: {summary['already']}",
        f"- unknown: {summary['unknown']}",
        f"- stale: {summary['stale']}",
        f"- auto-name (skipped): {summary['auto_name']}",
        f"- deferred: {summary['deferred']}",
        "",
        "| File | Line | Address | Label | Status |",
        "|---|---:|---|---|---|",
    ]
    for occ in occurrences:
        if occ.status in {"skipped_label", "skipped_scope"}:
            continue
        label = occ.label or ""
        lines.append(
            f"| `{occ.file}` | {occ.line} | `{occ.token}` | `{label}` | "
            f"{occ.status} |"
        )
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines) + "\n")


# ---------------------------------------------------------------------------
# Self-check
# ---------------------------------------------------------------------------


@dataclass
class FixtureDb:
    entries: list[tuple[int, int, str]] = field(
        default_factory=lambda: [
            (0x08012344, 0x08012364, "Target"),
            (0x08012400, 0x08012420, "sData"),
            (0x08012500, 0x08012510, "_08012500"),
            (0x08012600, 0x08012610, "AliasA"),
            (0x08012600, 0x08012610, "AliasB"),
        ]
    )

    def resolve(self, addr: int) -> Optional[Resolved]:
        if not is_rom(addr):
            return None
        return resolve_entries(
            [e for e in self.entries if not is_auto_name(e[2])], addr
        )

    def raw_resolve(self, addr: int) -> Optional[Resolved]:
        return resolve_entries(self.entries, addr)


def self_check() -> int:
    db = FixtureDb()
    cases: list[tuple[str, str, str, str, str, str]] = [
        (
            "exact symbol",
            "\tldr r0, _08012344 @ =0x08012344",
            ".s",
            "references",
            "\tldr r0, _08012344 @ =0x08012344 (Target)",
            "labelled",
        ),
        (
            "containing symbol + offset",
            "\tldr r0, _08012348 @ =0x08012348",
            ".s",
            "references",
            "\tldr r0, _08012348 @ =0x08012348 (Target+0x4)",
            "labelled",
        ),
        (
            "unknown address stays raw",
            "\tldr r0, _08020000 @ =0x08020000",
            ".s",
            "references",
            "\tldr r0, _08020000 @ =0x08020000",
            "unknown",
        ),
        (
            "already labelled",
            "\tldr r0, _08012344 @ =0x08012344 (Target)",
            ".s",
            "references",
            "\tldr r0, _08012344 @ =0x08012344 (Target)",
            "already",
        ),
        (
            "stale label is not overwritten",
            "\tldr r0, _08012344 @ =0x08012344 (OldName)",
            ".s",
            "references",
            "\tldr r0, _08012344 @ =0x08012344 (OldName)",
            "stale",
        ),
        (
            "non-ROM comment address is ignored",
            "\tldr r0, _04000000 @ =0x04000000",
            ".s",
            "references",
            "\tldr r0, _04000000 @ =0x04000000",
            "none",
        ),
        (
            "label definition is already semantic",
            "Foo: @ 0x08012344",
            ".s",
            "references",
            "Foo: @ 0x08012344",
            "skipped_label",
        ),
        (
            "ldr scope ignores computed-address annotation",
            "\tadd lr, pc, #0x0 @ =0x08012344",
            ".s",
            "ldr",
            "\tadd lr, pc, #0x0 @ =0x08012344",
            "skipped_scope",
        ),
        (
            "C line comment",
            "    // Baseline word is 0x08012344.",
            ".c",
            "references",
            "    // Baseline word is 0x08012344 (Target).",
            "labelled",
        ),
        (
            "C block comment + offset",
            "/* 0x08012404 */",
            ".c",
            "references",
            "/* 0x08012404 (sData+0x4) */",
            "labelled",
        ),
        (
            "auto name is not semantic",
            "\tldr r0, _08012500 @ =0x08012500",
            ".s",
            "references",
            "\tldr r0, _08012500 @ =0x08012500",
            "auto_name",
        ),
        (
            "ambiguous alias is not guessed",
            "\tldr r0, _08012600 @ =0x08012600",
            ".s",
            "references",
            "\tldr r0, _08012600 @ =0x08012600",
            "unknown",
        ),
        (
            "two addresses on one line",
            "\tldr r0, x @ =0x08012344 / 0x08012404",
            ".s",
            "references",
            "\tldr r0, x @ =0x08012344 (Target) / 0x08012404 (sData+0x4)",
            "labelled",
        ),
        (
            "scope all annotates a label definition",
            "Foo: @ 0x08012344",
            ".s",
            "all",
            "Foo: @ 0x08012344 (Target)",
            "labelled",
        ),
    ]

    failed = 0
    total = 0
    for name, line, suffix, scope, expected, expected_status in cases:
        total += 1
        new_line, found, _state = annotate_line(
            line, "<self-check>", 1, suffix, scope, db
        )
        got_status = found[0].status if found else "none"
        if new_line != expected or got_status != expected_status:
            failed += 1
            print(
                f"  FAIL {name}: expected {expected!r} [{expected_status}], "
                f"got {new_line!r} [{got_status}]"
            )
        else:
            print(f"  ok   {name}")

    # Idempotence: a second pass over every labelled case must change nothing
    # and report `already`.
    for name, line, suffix, scope, expected, expected_status in cases:
        if expected_status != "labelled":
            continue
        total += 1
        again, found, _state = annotate_line(
            expected, "<self-check>", 1, suffix, scope, db
        )
        if again != expected or not found or found[0].status != "already":
            failed += 1
            print(
                f"  FAIL idempotent {name}: got {again!r} "
                f"[{found[0].status if found else 'none'}]"
            )
        else:
            print(f"  ok   idempotent {name}")

    # Block comments are stateful across lines.
    total += 1
    first, found, state1 = annotate_line(
        "/* 0x08012344", "<self-check>", 1, ".c", "references", db
    )
    second, found2, state2 = annotate_line(
        "   more 0x08012404 */", "<self-check>", 2, ".c", "references", db, state1
    )
    if (
        state1 is not True
        or state2 is not False
        or first != "/* 0x08012344 (Target)"
        or second != "   more 0x08012404 (sData+0x4) */"
    ):
        failed += 1
        print(f"  FAIL multi-line block comment: {first!r} {second!r}")
    else:
        print("  ok   multi-line block comment")

    if failed:
        print(f"self-check: {failed}/{total} failed")
        return 1
    print(f"self-check: {total}/{total} passed")
    return 0


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------


def main(argv: Optional[list[str]] = None) -> int:
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    ap.add_argument("--map", default="mf_us.map", help="linker map (default: mf_us.map)")
    ap.add_argument("--elf", default="mf_us.elf", help="ELF for local symbols (default: mf_us.elf)")
    ap.add_argument("--root", default=".", help="tree root for default file discovery")
    ap.add_argument(
        "--files",
        nargs="+",
        action="append",
        default=[],
        help="files/directories to scan (default: tracked asm/**/*.s and src/**/*.c)",
    )
    ap.add_argument("paths", nargs="*", help="positional file/directory paths")
    ap.add_argument(
        "--scope",
        choices=["references", "ldr", "all"],
        default="references",
        help="references (default), ldr-only, or every comment address",
    )
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument("--check", action="store_true", help="report only (default)")
    mode.add_argument("--write", action="store_true", help="rewrite comments")
    ap.add_argument("--limit", type=int, default=0, help="cap pending edits (0 = no cap)")
    ap.add_argument("--json", action="store_true", help="print machine-readable JSON")
    ap.add_argument("--json-out", default="", help="also write JSON to this path")
    ap.add_argument("--report", default="", help="write a Markdown table to this path")
    ap.add_argument("--strict", action="store_true", help="--check exits 1 when work remains")
    ap.add_argument("--self-check", action="store_true", help="run synthetic fixture checks")
    args = ap.parse_args(argv)

    if args.self_check:
        return self_check()

    root = Path(args.root)
    explicit = [p for group in args.files for p in group] + args.paths
    files = discover_files(root, explicit)
    if not files:
        print("label-comments: no source files found", file=sys.stderr)
        return 1

    map_path = Path(args.map)
    if not map_path.is_absolute():
        map_path = root / map_path
    if not map_path.exists():
        print(f"label-comments: missing map {map_path}", file=sys.stderr)
        return 1
    elf_path = Path(args.elf)
    if not elf_path.is_absolute():
        elf_path = root / elf_path
    if not elf_path.exists():
        elf_path = None  # type: ignore[assignment]

    sm = SymbolMap.load(map_path, elf_path)
    db = MapSymbolDb(sm)
    mode_name = "write" if args.write else "check"

    all_occurrences: list[Occurrence] = []
    pending_files: list[tuple[Path, str, list[str]]] = []

    for path in files:
        rel = _relative(path, root)
        if not path.exists():
            print(f"label-comments: missing file {rel}", file=sys.stderr)
            continue
        out_lines, occurrences = scan_file(path, rel, args.scope, db)
        all_occurrences.extend(occurrences)
        pending_files.append((path, rel, out_lines))

    all_occurrences.sort(key=lambda o: (o.file, o.line, o.column))

    if args.write:
        # Deterministic cap: keep the first N pending edits, defer the rest.
        editable = [o for o in all_occurrences if o.status == "labelled"]
        keep = editable[: args.limit] if args.limit > 0 else editable
        keep_ids = {id(o) for o in keep}
        for occ in editable:
            if id(occ) not in keep_ids:
                occ.status = "deferred"

        # Rebuild each file from the original plus only the kept insertions.
        changed: list[str] = []
        for path, rel, _lines in pending_files:
            original = read_source(path)
            orig_lines = original.splitlines(keepends=True)
            kept_for_file = [o for o in keep if o.file == rel]
            if not kept_for_file:
                continue
            by_line: dict[int, list[Occurrence]] = {}
            for occ in kept_for_file:
                by_line.setdefault(occ.line, []).append(occ)
            new_lines: list[str] = []
            for lineno, line in enumerate(orig_lines, 1):
                stripped = line.rstrip("\r\n")
                ending = line[len(stripped) :]
                insertions = by_line.get(lineno, [])
                if not insertions:
                    new_lines.append(line)
                    continue
                new_stripped = stripped
                for occ in sorted(insertions, key=lambda o: o.column, reverse=True):
                    end = occ.column - 1 + len(occ.token)
                    new_stripped = (
                        new_stripped[:end]
                        + f" ({occ.label})"
                        + new_stripped[end:]
                    )
                new_lines.append(new_stripped + ending)
            new_text = "".join(new_lines)
            if new_text != original:
                write_source(path, new_text)
                changed.append(rel)

        summary = summarize(all_occurrences, mode_name)
        result = {
            "tool": "label_comments",
            "map": _relative(map_path, root),
            "elf": _relative(elf_path, root) if elf_path else None,
            "scope": args.scope,
            "limit": args.limit,
            "files_scanned": len(pending_files),
            "changed_files": changed,
            "summary": summary,
            "records": [o.to_dict() for o in all_occurrences],
        }
        if args.json:
            print(json.dumps(result, indent=2))
        else:
            print_human(summary, all_occurrences)
            print(f"  changed files: {len(changed)}")
            for name in changed:
                print(f"    {name}")
    else:
        summary = summarize(all_occurrences, mode_name)
        result = {
            "tool": "label_comments",
            "map": _relative(map_path, root),
            "elf": _relative(elf_path, root) if elf_path else None,
            "scope": args.scope,
            "limit": args.limit,
            "files_scanned": len(pending_files),
            "changed_files": [],
            "summary": summary,
            "records": [o.to_dict() for o in all_occurrences],
        }
        if args.json:
            print(json.dumps(result, indent=2))
        else:
            print_human(summary, all_occurrences)

    if args.json_out:
        out = Path(args.json_out)
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(result, indent=2) + "\n")
    if args.report:
        write_report(Path(args.report), summary, all_occurrences)

    if args.strict and not args.write and summary["pending"] > 0:
        print(f"FAIL: {summary['pending']} ROM comment address(es) still unlabelled")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
