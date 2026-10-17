#!/usr/bin/env python3
"""Scan extracted data blobs for pointer-like values.

Some blobs are graphics/audio (raw bytes with accidental pointer-looking
words); others are real pointer tables.  This separates the two with a density
and target-validity heuristic, and writes samples for human review.
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_symbols import SymbolMap, category  # noqa: E402

POINTER_CATEGORIES = {"rom", "ewram", "iwram"}


def blob_entries(database: Path, data_root: Path) -> list[dict]:
    entries = json.loads(database.read_text())
    out = []
    for entry in entries:
        path = entry.get("path", "")
        if not path.startswith("Blob"):
            continue
        addr = entry.get("addr", {})
        if isinstance(addr, dict):
            addr = addr.get("us")
        out.append(
            {
                "path": path,
                "addr": addr,
                "size": entry.get("size"),
                "file": data_root / path,
            }
        )
    return out


def scan_blob(entry: dict, sm: SymbolMap) -> dict:
    path = entry["file"]
    if not path.exists():
        return {
            "path": entry["path"],
            "missing": True,
            "hits": 0,
            "density": 0.0,
            "classification": "missing",
        }

    data = path.read_bytes()
    hits = []
    target_counter: Counter[str] = Counter()
    section_counter: Counter[str] = Counter()

    for off in range(0, len(data) - 3, 4):
        value = struct.unpack_from("<I", data, off)[0]
        cat = category(value)
        if cat not in POINTER_CATEGORIES:
            continue
        target = sm.resolve(value)
        key = f"{target.get('symbol') or '?'}+{target.get('offset')}"
        target_counter[key] += 1
        section_counter[target.get("section") or "unknown"] += 1
        if len(hits) < 16:
            hits.append(
                {
                    "offset": off,
                    "value": f"0x{value:08X}",
                    "category": cat,
                    "target": target,
                }
            )

    words = max(1, len(data) // 4)
    unique_targets = len(target_counter)
    # The first 16 hits are only for display; use the full counters for the
    # decision, so a table larger than 16 entries is not misclassified.
    all_hits = sum(target_counter.values())
    density = all_hits / words

    if all_hits >= 8 and density >= 0.15 and unique_targets >= 4:
        classification = "pointer_table"
    elif all_hits >= 4 and density >= 0.02:
        classification = "possible_pointer_table"
    else:
        classification = "data"

    return {
        "path": entry["path"],
        "addr": entry["addr"],
        "bytes": len(data),
        "hits": all_hits,
        "density": round(density, 4),
        "unique_targets": unique_targets,
        "target_sections": dict(section_counter.most_common()),
        "classification": classification,
        "samples": hits,
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--database", default="database.json")
    ap.add_argument("--data-root", default="data")
    ap.add_argument("--map", default="mf_us.map")
    ap.add_argument("--out", default="work/shift/blob_scan.json")
    args = ap.parse_args()

    sm = SymbolMap.load(Path(args.map))
    entries = blob_entries(Path(args.database), Path(args.data_root))
    results = [scan_blob(e, sm) for e in entries]

    summary = Counter(r["classification"] for r in results)
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(
        json.dumps({"summary": dict(summary), "blobs": results}, indent=2) + "\n"
    )

    print(f"blob audit: {len(results)} blobs -> {out}")
    print(f"  classification: {dict(summary)}")
    print("  candidates:")
    for r in sorted(
        results,
        key=lambda x: (x.get("density", 0), x.get("hits", 0)),
        reverse=True,
    ):
        if r.get("classification") in {"pointer_table", "possible_pointer_table"}:
            print(
                f"    {r['classification']:22s} hits={r['hits']:5d} "
                f"density={r['density']:.3f} targets={r['unique_targets']:4d} "
                f"{r['path']}"
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
