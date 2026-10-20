#!/usr/bin/env python3
"""Gate: no unclassified hardcoded ROM address may survive the shift refactor.

Two evidence sources are combined:

* ``work/shift/abs_refs.json`` -- the relocation ledger.  Every ROM literal
  and bare ``ldr rX, =0x...`` pseudo-literal starts ``open``; strict mode
  fails while an ``open``/``unknown`` record or a ROM literal in C survives.
  The ``ldr rX, _label @ =0x...`` annotation form is reference-only.
* ``work/shift/blob_scan.json`` -- the extracted-data classification.  A
  ``pointer_table``/``possible_pointer_table`` blob is only a gate failure
  while it is **still included raw** (``INCBIN``).  Converted tables (SHIFT-006a
  and the completed SHIFT-006b blobs) are reported as ``converted``; the
  remaining SHIFT-006b blobs still use ``INCBIN`` and fail strict mode until
  they are modelled.  A blob that is no longer included cannot leave absolute
  pointer words in the ROM image, and its replacement C is caught by the
  literal/C scan.

The C scan accepts 1-8 hex-digit literals and normalizes them to eight digits,
because the C sources write ROM addresses in the short seven-digit form
(``0x8017bd9`` is ``0x08017BD9``).  It scans ``.c`` and ``.h`` files and masks
comments and string/char literals first, so a ROM-looking value in a comment or
a string is not a reference.  The ``ROM_BASE`` definition in
``include/gba/memory.h`` is a hardware constant and stays whitelisted.

Report mode is informative and always exits 0 once the ledger is readable.
``--strict`` exits 1 when any check fails, including an unreadable or
incomplete blob scan: the gate must not pass when it cannot see the evidence.
"""

from __future__ import annotations

import argparse
import json
import re
from collections import Counter
from pathlib import Path

ROM_START = 0x08000000
ROM_END = 0x0A000000
# 1-8 hex digits, not part of a longer token.  The parsed value is range-checked
# below, so short constants such as 0x20 cannot become ROM references.
C_LITERAL_RE = re.compile(
    r"(?<![0-9A-Za-z_])0[xX]([0-9A-Fa-f]{1,8})(?![0-9A-Fa-f])"
)
C_SOURCE_SUFFIXES = (".c", ".h")
INCBIN_RE = re.compile(r'\b_?INCBIN\w*\s*\(\s*"([^"]+)"')
POINTER_CLASSES = {"pointer_table", "possible_pointer_table"}

# The entry point and header live at fixed ROM addresses by hardware contract.
WHITELIST = {
    0x08000000,  # ROM header
    0x080000C0,  # ARM entry point / crt0
}


def mask_c(text: str, mask_strings: bool = True) -> str:
    """Blank comments (and optionally strings) without changing offsets.

    A character-by-character state machine is used instead of a regular
    expression so block comments can span lines and so a wrong quote cannot
    silently hide the rest of a file.  Newlines are always preserved, which
    keeps line numbers and columns aligned with the original source.
    """
    out = list(text)
    state = "code"
    i = 0
    n = len(text)
    while i < n:
        c = text[i]
        if state == "code":
            if c == "/" and i + 1 < n and text[i + 1] == "/":
                out[i] = out[i + 1] = " "
                i += 2
                state = "line"
                continue
            if c == "/" and i + 1 < n and text[i + 1] == "*":
                out[i] = out[i + 1] = " "
                i += 2
                state = "block"
                continue
            if c == '"' or c == "'":
                if mask_strings:
                    out[i] = " "
                state = "string" if c == '"' else "char"
                i += 1
                continue
            i += 1
            continue
        if state == "line":
            if c == "\n":
                state = "code"
            else:
                out[i] = " "
            i += 1
            continue
        if state == "block":
            if c == "*" and i + 1 < n and text[i + 1] == "/":
                out[i] = out[i + 1] = " "
                i += 2
                state = "code"
                continue
            if c != "\n":
                out[i] = " "
            i += 1
            continue

        quote = '"' if state == "string" else "'"
        if c == "\\" and i + 1 < n:
            if mask_strings:
                out[i] = " "
                if text[i + 1] != "\n":
                    out[i + 1] = " "
            i += 2
            continue
        if c == quote:
            if mask_strings:
                out[i] = " "
            state = "code"
            i += 1
            continue
        if c == "\n":
            # Unterminated literal: recover at the line break.
            state = "code"
            i += 1
            continue
        if mask_strings:
            out[i] = " "
        i += 1
    return "".join(out)


def strip_comments(text: str) -> str:
    """Remove C comments but keep string literals (used by INCBIN parsing)."""
    return mask_c(text, mask_strings=False)


def scan_c_text(name: str, text: str) -> list[dict]:
    """Return every ROM literal in *text*, ignoring comments and strings."""
    masked = mask_c(text)
    refs: list[dict] = []
    for lineno, (line, masked_line) in enumerate(
        zip(text.split("\n"), masked.split("\n")), 1
    ):
        body = line[:-1] if line.endswith("\r") else line
        for match in C_LITERAL_RE.finditer(masked_line):
            value = int(match.group(1), 16)
            if not ROM_START <= value < ROM_END:
                continue
            refs.append(
                {
                    "file": name,
                    "line": lineno,
                    "column": match.start(),
                    "literal": match.group(0),
                    "hex_digits": len(match.group(1)),
                    "value": f"0x{value:08X}",
                    "text": body.strip(),
                    "line_text": body,
                }
            )
    return refs


def c_source_files(paths: list[Path]) -> list[Path]:
    """Expand roots to a deterministic list of .c/.h files."""
    files: set[Path] = set()
    for root in paths:
        if root.is_file():
            files.add(root)
        elif root.exists():
            for suffix in C_SOURCE_SUFFIXES:
                files.update(root.rglob(f"*{suffix}"))
    return sorted(files, key=lambda path: path.as_posix())


def scan_c(paths: list[Path]) -> list[dict]:
    refs: list[dict] = []
    for path in c_source_files(paths):
        refs.extend(
            scan_c_text(path.as_posix(), path.read_text(errors="replace"))
        )
    return refs


_GENERATED_RANGES: dict[str, list[tuple[int, int]]] = {}


def generated_block_ranges(path: str) -> list[tuple[int, int]]:
    """Line ranges of reviewed generated sparse-pointer blocks.

    ``sBlob_6131c8_63a19c`` is mostly cutscene text/graphics.  Its outside
    ROM-looking words are data, not pointers; the generator emits them as
    literals and only turns inside-blob words into ``sBlob+offset``
    expressions.  Treat that reviewed block as data while strict mode still
    checks every other C literal.
    """
    cached = _GENERATED_RANGES.get(path)
    if cached is not None:
        return cached
    ranges: list[tuple[int, int]] = []
    try:
        lines = Path(path).read_text(errors="replace").splitlines()
    except OSError:
        _GENERATED_RANGES[path] = ranges
        return ranges
    begin = None
    for lineno, line in enumerate(lines, 1):
        if (
            "BEGIN GENERATED by tools/shift/gen_blob_tables.py" in line
            and "sBlob_6131c8_63a19c" in line
        ):
            begin = lineno
        elif begin is not None and "END GENERATED: sBlob_6131c8_63a19c" in line:
            ranges.append((begin, lineno))
            begin = None
    _GENERATED_RANGES[path] = ranges
    return ranges


def is_whitelisted(ref: dict) -> bool:
    """True for ROM_BASE in memory.h and reviewed generated data blocks."""
    if (
        ref["file"].endswith("include/gba/memory.h")
        and "ROM_BASE" in ref["text"]
    ):
        return True
    return any(
        start <= ref["line"] <= end
        for start, end in generated_block_ranges(ref["file"])
    )


def filter_c_refs(refs: list[dict]) -> list[dict]:
    return [ref for ref in refs if not is_whitelisted(ref)]


def c_counts_by_file(refs: list[dict]) -> list[tuple[str, int]]:
    counts = Counter(ref["file"] for ref in refs)
    return sorted(counts.items(), key=lambda item: (-item[1], item[0]))


def parse_incbin_names(text: str) -> set[str]:
    """Blob filenames still included verbatim by a C INCBIN macro."""
    return {
        Path(m.group(1)).name
        for m in INCBIN_RE.finditer(strip_comments(text))
    }


def incbin_uses(paths: list[Path]) -> dict[str, set[str]]:
    """Map raw blob filename -> C sources that still include it."""
    uses: dict[str, set[str]] = {}
    for root in paths:
        if not root.exists():
            continue
        for path in sorted(root.rglob("*.c")):
            for name in parse_incbin_names(
                path.read_text(errors="replace")
            ):
                uses.setdefault(name, set()).add(path.as_posix())
    return uses


def load_blob_scan(path: Path) -> tuple[dict | None, str | None]:
    if not path.exists():
        return None, f"missing {path}"
    try:
        scan = json.loads(path.read_text())
    except (OSError, json.JSONDecodeError) as exc:
        return None, f"{path}: {exc}"
    if not isinstance(scan.get("blobs"), list):
        return None, f"{path}: no 'blobs' list"
    return scan, None


def blob_status(scan: dict, raw_names: set[str]) -> dict:
    """Split pointer-like blobs into converted and still-raw groups.

    ``raw_names`` is the set of blob filenames still present in an ``INCBIN``
    macro.  A pointer-like blob outside that set was replaced by source (or
    dropped from the link), so it no longer puts absolute words in the ROM.
    """
    blobs = scan.get("blobs", [])
    pointer = [
        b for b in blobs if b.get("classification") in POINTER_CLASSES
    ]
    remaining = [
        b for b in pointer if Path(b.get("path", "")).name in raw_names
    ]
    remaining_names = {b.get("path") for b in remaining}
    converted = [b for b in pointer if b.get("path") not in remaining_names]
    missing = [
        b
        for b in blobs
        if b.get("missing") or b.get("classification") == "missing"
    ]
    return {
        "total": len(blobs),
        "pointer": pointer,
        "remaining": remaining,
        "converted": converted,
        "missing": missing,
        "missing_count": max(
            int(scan.get("missing", 0) or 0), len(missing)
        ),
    }


def print_blob_report(
    scan_path: Path,
    scan_error: str | None,
    status: dict | None,
    uses: dict[str, set[str]],
) -> None:
    if scan_error:
        print(f"  blob scan:     {scan_error}")
        return
    assert status is not None
    print(
        f"  blob scan:     {scan_path}: {status['total']} blobs, "
        f"{len(status['pointer'])} pointer-like "
        f"({len(status['converted'])} converted, "
        f"{len(status['remaining'])} still raw)"
    )
    if status["missing_count"]:
        print(
            f"  unclassified:  {status['missing_count']} blob(s) missing "
            f"extracted bytes; pass --data-root to audit_blobs.py"
        )
    for blob in status["converted"]:
        print(f"    converted          {blob['path']}")
    for blob in status["remaining"]:
        sources = ", ".join(sorted(uses.get(Path(blob["path"]).name, ())))
        metrics = (
            f"hits={blob.get('hits', '?')} "
            f"density={blob.get('density', '?')} "
            f"run={blob.get('longest_run', '?')}"
        )
        print(
            f"    REMAINING RAW      {blob['path']} ({metrics})"
        )
        if sources:
            print(f"      included by:     {sources}")
        print(f"      reason:          {blob.get('reason', '?')}")


def self_check() -> int:
    """Deterministic checks for the C scan, INCBIN detection and grouping."""
    cases = [
        (
            "plain INCBIN_U8",
            'static u8 sBlob[] = INCBIN_U8("data/Blob_aa_bb.bin");',
            {"Blob_aa_bb.bin"},
        ),
        (
            "sized INCBIN",
            'static u8 sBlob[] = INCBIN_U16("data/Blob_cc_dd.bin");',
            {"Blob_cc_dd.bin"},
        ),
        (
            "private _INCBIN macro",
            'static u8 sBlob[] = _INCBIN_U32("data/Blob_ee_ff.bin");',
            {"Blob_ee_ff.bin"},
        ),
        (
            "commented-out INCBIN",
            '// INCBIN_U8("data/Blob_commented.bin")',
            set(),
        ),
        ("no include", "static const u32 sTable[] = { 1, 2 };", set()),
    ]
    failed = 0
    for name, text, expected in cases:
        got = parse_incbin_names(text)
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected}, got {got}")
        else:
            print(f"  ok   {name}: {sorted(got)}")

    scan = {
        "missing": 1,
        "blobs": [
            {
                "path": "Blob_1111_2222.bin",
                "classification": "pointer_table",
                "reason": "flat pointer run",
            },
            {
                "path": "Blob_3333_4444.bin",
                "classification": "possible_pointer_table",
                "reason": "pointer field at struct stride",
            },
            {
                "path": "Blob_5555_6666.bin",
                "classification": "data",
                "reason": "no pointer-like words",
            },
            {
                "path": "Blob_7777_8888.bin",
                "classification": "missing",
                "missing": True,
                "reason": "file not found under --data-root",
            },
        ],
    }
    status = blob_status(scan, {"Blob_3333_4444.bin", "Blob_5555_6666.bin"})
    checks = [
        (
            "converted pointer table",
            [b["path"] for b in status["converted"]],
            ["Blob_1111_2222.bin"],
        ),
        (
            "only raw possible table remains",
            [b["path"] for b in status["remaining"]],
            ["Blob_3333_4444.bin"],
        ),
        ("missing blobs count", status["missing_count"], 1),
    ]
    for name, got, expected in checks:
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected}, got {got}")
        else:
            print(f"  ok   {name}: {got}")

    # C literal scanning: short ROM forms, comments/strings, token boundaries
    # and the memory.h ROM_BASE exception.
    c_cases = [
        (
            "7-digit C ROM literal",
            "src/a.c",
            "\t[PSPRITE_X] = (Func_T)0x8017bd9,",
            ["0x08017BD9"],
        ),
        (
            "8-digit C ROM literal",
            "src/a.c",
            "p = (const u16*)0x08017bd9;",
            ["0x08017BD9"],
        ),
        (
            "uppercase 0X literal",
            "src/a.c",
            "p = (u8*)0X8017BD9;",
            ["0x08017BD9"],
        ),
        (
            "line-comment literal",
            "src/a.c",
            "// p = (u8*)0x8017bd9;",
            [],
        ),
        (
            "block-comment literal",
            "src/a.c",
            "/* 0x8017bd9\n   0x8017bda */\nint x;",
            [],
        ),
        (
            "string literal",
            "src/a.c",
            'const char* s = "0x8017bd9";',
            [],
        ),
        (
            "non-ROM constant",
            "src/a.c",
            "value = 0x1234567;",
            [],
        ),
        (
            "too many digits",
            "src/a.c",
            "value = 0x080000000;",
            [],
        ),
        (
            "identifier prefix",
            "src/a.c",
            "value = foo0x8017bd9;",
            [],
        ),
        (
            "0x09 ROM literal",
            "src/a.c",
            "p = (u8*)0x09abcdef;",
            ["0x09ABCDEF"],
        ),
    ]
    for name, path, text, expected in c_cases:
        got = [ref["value"] for ref in scan_c_text(path, text)]
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected}, got {got}")
        else:
            print(f"  ok   {name}: {got}")

    whitelist_ref = {
        "file": "include/gba/memory.h",
        "text": "#define ROM_BASE (void *)0x08000000",
    }
    ordinary_ref = {
        "file": "src/a.c",
        "text": "(void *)0x08000000",
    }
    filter_checks = [
        (
            "ROM_BASE whitelisted",
            is_whitelisted(whitelist_ref),
            True,
        ),
        (
            "ordinary ROM literal not whitelisted",
            is_whitelisted(ordinary_ref),
            False,
        ),
        (
            "whitelist removes only ROM_BASE",
            [r["file"] for r in filter_c_refs([whitelist_ref, ordinary_ref])],
            ["src/a.c"],
        ),
    ]
    for name, got, expected in filter_checks:
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected}, got {got}")
        else:
            print(f"  ok   {name}: {got}")

    total = len(cases) + len(checks) + len(c_cases) + len(filter_checks)
    if failed:
        print(f"self-check: {failed}/{total} failed")
        return 1
    print(f"self-check: {total}/{total} passed")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--refs", default="work/shift/abs_refs.json")
    ap.add_argument("--blob-scan", default="work/shift/blob_scan.json")
    ap.add_argument("--c-root", action="append", default=[])
    ap.add_argument("--strict", action="store_true")
    ap.add_argument(
        "--self-check",
        action="store_true",
        help="run the C-scan/INCBIN/blob grouping checks and exit",
    )
    args = ap.parse_args()

    if args.self_check:
        return self_check()

    c_roots = [Path(p) for p in (args.c_root or ["src", "include", "hack"])]
    refs_path = Path(args.refs)
    if not refs_path.exists():
        print(f"FAIL: missing relocation ledger {refs_path}")
        print("      run: make -f Makefile.shift audit-asm")
        return 1

    ledger = json.loads(refs_path.read_text())
    records = ledger["records"]
    rom = [r for r in records if r["category"] == "rom"]

    open_literals = [
        r
        for r in rom
        if r["kind"] in {"literal", "ldr_literal"} and r["status"] == "open"
    ]
    open_ldr_literals = [
        r for r in rom if r["kind"] == "ldr_literal" and r["status"] == "open"
    ]
    unknown = [r for r in rom if r["status"] == "unknown"]
    references = [r for r in rom if r["kind"] == "ldr"]
    whitelisted = [r for r in rom if int(r["value"], 16) in WHITELIST]

    c_refs = filter_c_refs(scan_c(c_roots))

    scan_path = Path(args.blob_scan)
    scan, scan_error = load_blob_scan(scan_path)
    uses = incbin_uses(c_roots)
    status = blob_status(scan, set(uses)) if scan else None

    print(f"check_relocs: {len(rom)} ROM refs in ledger")
    print(f"  open literals: {len(open_literals)}")
    print(
        f"  ldr pseudo-literals: {len(open_ldr_literals)} "
        f"(must be 0 in strict)"
    )
    print(f"  unknown:       {len(unknown)}")
    print(f"  ldr comments:  {len(references)} (reference-only)")
    print(f"  whitelisted:   {len(whitelisted)}")
    print(f"  C ROM refs:    {len(c_refs)}")
    if c_refs:
        file_counts = c_counts_by_file(c_refs)
        print(f"  C refs by file ({len(file_counts)} file(s)):")
        for name, count in file_counts:
            print(f"    {count:5d}  {name}")
    print_blob_report(scan_path, scan_error, status, uses)

    if open_literals:
        print("  first open literals:")
        for r in open_literals[:10]:
            target = r.get("target") or {}
            print(
                f"    {r['file']}:{r['line']} {r['value']} "
                f"-> {target.get('symbol') or '?'}+{target.get('offset')}"
            )
    if c_refs:
        print("  first C refs:")
        for r in c_refs[:10]:
            print(f"    {r['file']}:{r['line']} {r['value']}  {r['text']}")

    # Everything a strict gate must reject.  Keep the reasons separate so the
    # failure output says which evidence is missing versus which ref survives.
    strict_errors: list[str] = []
    if open_literals:
        strict_errors.append(
            f"{len(open_literals)} open ROM literal(s) remain"
        )
    if unknown:
        strict_errors.append(f"{len(unknown)} unclassified ROM ref(s) remain")
    if c_refs:
        strict_errors.append(f"{len(c_refs)} hardcoded ROM ref(s) in C")
    if scan_error:
        strict_errors.append(
            f"blob scan unavailable ({scan_error}); cannot verify raw blobs"
        )
    elif status is not None:
        if status["missing_count"]:
            strict_errors.append(
                f"{status['missing_count']} blob(s) were not classified "
                "(missing extracted bytes)"
            )
        if status["remaining"]:
            names = ", ".join(
                b["path"] for b in status["remaining"]
            )
            strict_errors.append(
                f"{len(status['remaining'])} pointer-like blob(s) still "
                f"included raw: {names}"
            )

    if args.strict:
        if strict_errors:
            for reason in strict_errors:
                print(f"FAIL: {reason}")
            return 1
        print(
            "PASS: strict relocation gate (no open literals, no C ROM refs, "
            "no raw pointer-like blobs)"
        )
        return 0

    if strict_errors:
        print(
            f"REPORT: {len(strict_errors)} issue(s) would fail --strict:"
        )
        for reason in strict_errors:
            print(f"  - {reason}")
    else:
        print("PASS: no unclassified ROM references (report mode)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
