#!/usr/bin/env python3
"""Suggest relocatable replacements for hardcoded ROM literals.

This does not edit assembly.  It turns `abs_refs.json` into a reviewable list of
`0x0839EC68` -> `Data_39EC68` (or `symbol+offset`) proposals, grouped by file.
"""

from __future__ import annotations

import argparse
import json
from collections import Counter, defaultdict
from pathlib import Path


def replacement(record: dict) -> str:
    target = record.get("target") or {}
    symbol = target.get("symbol")
    offset = target.get("offset") or 0
    if symbol and offset:
        return f"{symbol}+0x{offset:X}"
    if symbol:
        return symbol
    section = target.get("section")
    if section:
        return f"<label in {section}+0x{offset:X}>"
    return "<unknown>"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--refs", default="work/shift/abs_refs.json")
    ap.add_argument("--out", default="work/shift/rewrite_suggestions.md")
    args = ap.parse_args()

    ledger = json.loads(Path(args.refs).read_text())
    literals = [
        r
        for r in ledger["records"]
        if r["category"] == "rom" and r["kind"] == "literal"
    ]

    by_file: dict[str, list[dict]] = defaultdict(list)
    for r in literals:
        by_file[r["file"]].append(r)

    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    lines = [
        "# ROM literal rewrite suggestions",
        "",
        "Generated from `work/shift/abs_refs.json`.  Review each line before",
        "editing; `symbol+offset` proposals are mechanical, not semantic.",
        "",
        f"Total literals: **{len(literals)}**",
        "",
    ]

    for file in sorted(by_file):
        items = by_file[file]
        lines.append(f"## `{file}` ({len(items)})")
        lines.append("")
        lines.append("| Line | Current | Proposed | Target section |")
        lines.append("|---:|---|---|---|")
        for r in items:
            target = r.get("target") or {}
            lines.append(
                f"| {r['line']} | `{r['value']}` | "
                f"`{replacement(r)}` | `{target.get('section') or '?'}` |"
            )
        lines.append("")

    out.write_text("\n".join(lines) + "\n")
    print(f"rewrite suggestions: {len(literals)} literals -> {out}")

    # A short console summary helps decide whether to start with the big file
    # or the small external-asm leftovers.
    per_file = Counter(r["file"] for r in literals)
    for name, count in per_file.most_common():
        print(f"  {count:4d}  {name}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
