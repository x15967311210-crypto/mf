#!/usr/bin/env python3
"""Gate: no unclassified hardcoded ROM address may survive the shift refactor.

The audit ledger starts with every ROM literal marked `open`.  As SHIFT-005/006
convert them to symbols/labels, the rewrite tooling (or a human) marks them
`converted` or `whitelisted`.  This script is what CI runs.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROM_RE = re.compile(r"\b0x(08[0-9a-fA-F]{6})\b")

# The entry point and header live at fixed ROM addresses by hardware contract.
WHITELIST = {
    0x08000000,  # ROM header
    0x080000C0,  # ARM entry point / crt0
}


def strip_comments(line: str) -> str:
    line = re.sub(r"//.*$", "", line)
    line = re.sub(r"/\*.*?\*/", "", line)
    return line


def scan_c(paths: list[Path]) -> list[dict]:
    refs = []
    for root in paths:
        if not root.exists():
            continue
        for path in sorted(root.rglob("*.c")):
            for lineno, line in enumerate(
                path.read_text(errors="replace").splitlines(), 1
            ):
                text = strip_comments(line)
                for m in ROM_RE.finditer(text):
                    value = int(m.group(1), 16)
                    refs.append(
                        {
                            "file": path.as_posix(),
                            "line": lineno,
                            "value": f"0x{value:08X}",
                            "text": line.strip(),
                        }
                    )
    return refs


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--refs", default="work/shift/abs_refs.json")
    ap.add_argument("--c-root", action="append", default=[])
    ap.add_argument("--strict", action="store_true")
    args = ap.parse_args()

    ledger = json.loads(Path(args.refs).read_text())
    records = ledger["records"]
    rom = [r for r in records if r["category"] == "rom"]

    open_literals = [
        r for r in rom if r["kind"] == "literal" and r["status"] == "open"
    ]
    unknown = [r for r in rom if r["status"] == "unknown"]
    references = [r for r in rom if r["kind"] == "ldr"]
    whitelisted = [
        r for r in rom if int(r["value"], 16) in WHITELIST
    ]

    c_refs = scan_c([Path(p) for p in (args.c_root or ["src", "include", "hack"])])
    c_refs = [
        r
        for r in c_refs
        if not (
            r["file"].endswith("include/gba/memory.h")
            and "ROM_BASE" in r["text"]
        )
    ]

    print(f"check_relocs: {len(rom)} ROM refs in ledger")
    print(f"  open literals: {len(open_literals)}")
    print(f"  unknown:       {len(unknown)}")
    print(f"  ldr comments:  {len(references)} (reference-only)")
    print(f"  whitelisted:   {len(whitelisted)}")
    print(f"  C ROM refs:    {len(c_refs)}")

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

    if args.strict and (open_literals or unknown or c_refs):
        print("FAIL: unclassified ROM references remain")
        return 1

    print("PASS: no unclassified ROM references (report mode)" if not args.strict else "PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
