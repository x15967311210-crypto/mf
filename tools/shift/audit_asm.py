#!/usr/bin/env python3
"""Find hardcoded addresses in assembly and classify them.

The first shiftability question is simple: which 32-bit values in the shipped
assembly are ROM addresses that will break when the link moves?  This script
answers that, maps each target to a symbol where possible, and writes a JSON
ledger the rewrite/gate tools consume.

Literal operands may omit leading zeros: `sound/tracks/track_1.s` writes
`.word 0x80a5710` for the address `0x080A5710`.  One to eight hex digits are
accepted and normalized to the canonical eight-digit `value` in the ledger;
`text` keeps the original line so the rewrite tools can reproduce it.

Two `ldr` forms are distinguished:

* `ldr r3, =0x80a568c` is a **bare pseudo-literal**.  GAS emits the address in
  the literal pool, so it is a real absolute ROM reference (`ldr_literal`) that
  must be rewritten to `=symbol+offset`.  It is `open` until then.
* `ldr r3, _080a568c @ =0x080A568C` is the disassembly's annotation form.  The
  `@` makes the address a comment, so the record is reference-only (`ldr`) and
  is not a rewrite target.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from collections.abc import Iterable
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_symbols import SymbolMap, category  # noqa: E402

# 1-8 hex digits: the audio track headers use the 7-digit form 0x80a5710.
LITERAL_RE = re.compile(
    r"^\s*(?:[A-Za-z_.$][\w.$@]*:\s*)?\.(?:4byte|word)\s+0x([0-9a-fA-F]{1,8})\b"
)
# A bare numeric pseudo-literal is assembled by GAS and becomes a real ROM
# address in the literal pool.
LDR_LITERAL_RE = re.compile(
    r"^\s*(?:[A-Za-z_.$][\w.$@]*:\s*)?"
    r"ldr[a-z]*\s+\w+\s*,\s*=\s*0x([0-9a-fA-F]{1,8})\b",
    re.IGNORECASE,
)
# Disassembly annotations keep the address in a `@` comment, so they are
# references to the word rather than the literal itself.  This also covers the
# `@ =0x08000200` annotation on non-ldr instructions.
LDR_RE = re.compile(r"=\s*0x([0-9a-fA-F]{1,8})\b")
ANY_ROM_RE = re.compile(r"\b0x(08[0-9a-fA-F]{6})\b")


def scan_lines(path: Path, lines: Iterable[str], sm: SymbolMap) -> list[dict]:
    records: list[dict] = []
    seen: set[tuple[int, int, str]] = set()

    for lineno, line in enumerate(lines, 1):
        found: list[tuple[str, int]] = []

        m = LITERAL_RE.search(line)
        if m:
            found.append(("literal", int(m.group(1), 16)))
        ldr_literal_match = LDR_LITERAL_RE.search(line)
        if ldr_literal_match:
            found.append(("ldr_literal", int(ldr_literal_match.group(1), 16)))
        # A bare pseudo-literal is the literal itself; the `@` annotation form
        # (and annotations on other instructions) stays reference-only.
        m = LDR_RE.search(line)
        if m and ldr_literal_match is None:
            found.append(("ldr", int(m.group(1), 16)))
        # Generic operands are useful for catches like `ldr r0, =0x...` without
        # the comment form, but label declarations and `@ 0x...` annotations
        # are not references.  Literal/ldr hits above are authoritative.
        if "@" not in line and not re.match(r"^\s*[A-Za-z_.$][\w.$@]*:", line):
            for m in ANY_ROM_RE.finditer(line):
                found.append(("operand", int(m.group(1), 16)))

        # A .4byte/ldr line also matches the generic operand pattern; keep the
        # specific kind and drop the duplicate generic hit on the same line.
        specific = {v for k, v in found if k in {"literal", "ldr_literal", "ldr"}}
        found = [
            (k, v)
            for (k, v) in found
            if k != "operand" or v not in specific
        ]

        for kind, value in found:
            key = (lineno, value, kind)
            if key in seen:
                continue
            seen.add(key)

            cat = category(value)
            target = sm.resolve(value) if cat == "rom" else None
            if cat != "rom":
                status = "fixed"
            elif kind == "ldr":
                status = "reference"
            elif target and target["known"]:
                status = "open"
            else:
                status = "unknown"

            records.append(
                {
                    "file": path.as_posix(),
                    "line": lineno,
                    "kind": kind,
                    "value": f"0x{value:08X}",
                    "category": cat,
                    "status": status,
                    "text": line.strip(),
                    "target": target,
                }
            )
    return records


def scan_file(path: Path, sm: SymbolMap) -> list[dict]:
    return scan_lines(path, path.read_text(errors="replace").splitlines(), sm)


class _StubSymbolMap:
    """Stand-in resolver for --self-check: every ROM address is mapped."""

    def resolve(self, addr: int) -> dict:
        return {
            "addr": f"0x{addr:08X}",
            "symbol": "sTarget",
            "offset": 0,
            "section": ".rodata",
            "object": "self-check.o",
            "exact": True,
            "known": True,
        }


# (name, source line, expected [(kind, value, category, status), ...])
SELF_CHECK_CASES: list[tuple[str, str, list[tuple[str, str, str, str]]]] = [
    (
        "8-digit literal is not double-counted as operand",
        "\t.4byte 0x080A5710",
        [("literal", "0x080A5710", "rom", "open")],
    ),
    (
        "bare 8-digit ldr pseudo-literal is a real open literal",
        "\tldr r3, =0x080A568C",
        [("ldr_literal", "0x080A568C", "rom", "open")],
    ),
    (
        "bare 7-digit ldr pseudo-literal is zero-padded",
        "\tldr r12, =0x80a5690",
        [("ldr_literal", "0x080A5690", "rom", "open")],
    ),
    (
        "bare 6-digit ldr pseudo-literal is zero-padded",
        "\tldr r0, =0x123456",
        [("ldr_literal", "0x00123456", "other", "fixed")],
    ),
    (
        "bare 1-digit ldr pseudo-literal is zero-padded",
        "\tldr r0, =0x1",
        [("ldr_literal", "0x00000001", "other", "fixed")],
    ),
    (
        "ldr @ annotation stays reference-only",
        "\tldr r3, _080a568c @ =0x080A568C",
        [("ldr", "0x080A568C", "rom", "reference")],
    ),
    (
        "7-digit ldr @ annotation is normalized and reference-only",
        "\tldr r3, _080a568c @ =0x80a568c",
        [("ldr", "0x080A568C", "rom", "reference")],
    ),
    (
        "symbol ldr pseudo-literal is not a literal",
        "\tldr r0, =sDma1ControlPointer",
        [],
    ),
    (
        "7-digit ROM literal is zero-padded",
        "\t.word 0x80a5710",
        [("literal", "0x080A5710", "rom", "open")],
    ),
    (
        "6-digit literal is zero-padded",
        "\t.word 0x123456",
        [("literal", "0x00123456", "other", "fixed")],
    ),
    (
        "1-digit literal is zero-padded",
        "\t.word 0x1",
        [("literal", "0x00000001", "other", "fixed")],
    ),
    (
        "non-ROM constant",
        "\t.word 0x04000000",
        [("literal", "0x04000000", "mmio", "fixed")],
    ),
    (
        "symbol+offset is not a literal",
        "\t.word track_1_lbl+4",
        [],
    ),
    (
        "symbol is not a literal",
        "\t.word sMusicTrackDataRom",
        [],
    ),
    (
        "label-prefixed literal keeps its directive",
        "_rc: .4byte 0x03007E60",
        [("literal", "0x03007E60", "iwram", "fixed")],
    ),
]


def self_check() -> int:
    """Deterministic checks for literal width, normalization and dedup."""
    path = Path("<self-check>")
    sm = _StubSymbolMap()
    failed = 0
    for name, text, expected in SELF_CHECK_CASES:
        got = [
            (r["kind"], r["value"], r["category"], r["status"])
            for r in scan_lines(path, [text], sm)
        ]
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected}, got {got}")
        else:
            print(f"  ok   {name}: {got}")
    total = len(SELF_CHECK_CASES)
    if failed:
        print(f"self-check: {failed}/{total} failed")
        return 1
    print(f"self-check: {total}/{total} passed")
    return 0


def build_summary(records: list[dict]) -> dict:
    rom = [r for r in records if r["category"] == "rom"]
    literals = [r for r in rom if r["kind"] == "literal"]
    ldr_literals = [r for r in rom if r["kind"] == "ldr_literal"]
    open_literals = [
        r
        for r in rom
        if r["kind"] in {"literal", "ldr_literal"} and r["status"] == "open"
    ]
    by_file = Counter(r["file"] for r in rom)
    by_status = Counter(r["status"] for r in rom)
    by_section = Counter(
        (r["target"] or {}).get("section") or "unknown"
        for r in literals + ldr_literals
    )
    by_kind = Counter(r["kind"] for r in records)
    by_category = Counter(r["category"] for r in records)
    unique_rom = sorted({r["value"] for r in rom})
    unknown = [r for r in rom if r["status"] == "unknown"]

    return {
        "records": len(records),
        "unique_values": len({r["value"] for r in records}),
        "by_kind": dict(by_kind),
        "by_category": dict(by_category),
        "rom": {
            "records": len(rom),
            "literals": len(literals),
            "ldr_literals": len(ldr_literals),
            "open_literals": len(open_literals),
            "unique_values": len(unique_rom),
            "status": dict(by_status),
            "by_file": dict(by_file.most_common()),
            "literal_target_sections": dict(by_section.most_common()),
            "unknown": len(unknown),
        },
        "unknown_samples": unknown[:20],
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--asm-dir", action="append", default=[])
    ap.add_argument("--map", default="mf_us.map")
    ap.add_argument("--symbols", default=None, help="pre-built symbols JSON")
    ap.add_argument("--out", default="work/shift/abs_refs.json")
    ap.add_argument("--strict", action="store_true")
    ap.add_argument(
        "--self-check",
        action="store_true",
        help="run literal width/normalization checks and exit (no map needed)",
    )
    args = ap.parse_args()

    if args.self_check:
        return self_check()

    asm_dirs = [Path(d) for d in (args.asm_dir or ["asm", "sound"])]
    if args.symbols:
        data = json.loads(Path(args.symbols).read_text())
        # Rebuilding from the map is cheaper than reconstructing the object;
        # the JSON is a cache, not the source of truth.
        sm = SymbolMap.load(Path(args.map))
        _ = data
    else:
        sm = SymbolMap.load(Path(args.map))

    records: list[dict] = []
    for d in asm_dirs:
        if not d.exists():
            continue
        for path in sorted(d.rglob("*.s")):
            records.extend(scan_file(path, sm))

    summary = build_summary(records)
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(
        json.dumps({"summary": summary, "records": records}, indent=2) + "\n"
    )

    print(f"asm audit: {summary['records']} refs -> {out}")
    print(f"  categories: {summary['by_category']}")
    print(
        f"  ROM refs: {summary['rom']['records']} "
        f"({summary['rom']['literals']} literals, "
        f"{summary['rom']['ldr_literals']} ldr pseudo-literals)"
    )
    print(f"  ROM unique: {summary['rom']['unique_values']}")
    print(f"  ROM status: {summary['rom']['status']}")
    print(f"  ROM target sections: {summary['rom']['literal_target_sections']}")
    print("  top files:")
    for name, count in list(summary["rom"]["by_file"].items())[:10]:
        print(f"    {count:5d}  {name}")

    if args.strict and summary["rom"]["unknown"]:
        print(f"FAIL: {summary['rom']['unknown']} ROM refs have no symbol/section")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
