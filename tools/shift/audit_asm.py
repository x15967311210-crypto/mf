#!/usr/bin/env python3
"""Find hardcoded addresses in assembly and classify them.

The first shiftability question is simple: which 32-bit values in the shipped
assembly are ROM addresses that will break when the link moves?  This script
answers that, maps each target to a symbol where possible, and writes a JSON
ledger the rewrite/gate tools consume.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_symbols import SymbolMap, category  # noqa: E402

LITERAL_RE = re.compile(
    r"^\s*(?:[A-Za-z_.$][\w.$@]*:\s*)?\.(?:4byte|word)\s+0x([0-9a-fA-F]{8})\b"
)
LDR_RE = re.compile(r"=\s*0x([0-9a-fA-F]{8})\b")
ANY_ROM_RE = re.compile(r"\b0x(08[0-9a-fA-F]{6})\b")


def scan_file(path: Path, sm: SymbolMap) -> list[dict]:
    records: list[dict] = []
    seen: set[tuple[int, int, str]] = set()

    for lineno, line in enumerate(path.read_text(errors="replace").splitlines(), 1):
        found: list[tuple[str, int]] = []

        m = LITERAL_RE.search(line)
        if m:
            found.append(("literal", int(m.group(1), 16)))
        m = LDR_RE.search(line)
        if m:
            found.append(("ldr", int(m.group(1), 16)))
        # Generic operands are useful for catches like `ldr r0, =0x...` without
        # the comment form, but label declarations and `@ 0x...` annotations
        # are not references.  Literal/ldr hits above are authoritative.
        if "@" not in line and not re.match(r"^\s*[A-Za-z_.$][\w.$@]*:", line):
            for m in ANY_ROM_RE.finditer(line):
                found.append(("operand", int(m.group(1), 16)))

        # A .4byte/ldr line also matches the generic operand pattern; keep the
        # specific kind and drop the duplicate generic hit on the same line.
        specific = {v for k, v in found if k in {"literal", "ldr"}}
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


def build_summary(records: list[dict]) -> dict:
    rom = [r for r in records if r["category"] == "rom"]
    literals = [r for r in rom if r["kind"] == "literal"]
    by_file = Counter(r["file"] for r in rom)
    by_status = Counter(r["status"] for r in rom)
    by_section = Counter(
        (r["target"] or {}).get("section") or "unknown" for r in literals
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
    args = ap.parse_args()

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
    print(f"  ROM refs: {summary['rom']['records']} ({summary['rom']['literals']} literals)")
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
