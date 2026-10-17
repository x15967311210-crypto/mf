#!/usr/bin/env python3
"""Scan extracted data blobs for pointer-like values and classify them.

Some blobs are graphics/audio (raw bytes with accidental pointer-looking
words); others are real pointer tables or struct arrays with a pointer field.
This tool separates those cases with a structural heuristic and writes samples
for human review.

The original SHIFT-002 rule (density >= 15% and four distinct targets) is kept
as `baseline_classification` for comparison, but it over-counts 16-bit data:
palettes, tilemaps and sprite frames commonly contain a high halfword in the
`0x08xx` / `0x03xx` range, which makes a pair of 16-bit samples look like a ROM
or IWRAM pointer.  The SHIFT-004 rule therefore adds three structural tests:

* **contiguous runs** -- a flat pointer table is a run of adjacent pointer
  words.  Requiring a run of at least 8 entries rejects scattered 16-bit
  false positives (longest run there is 1-5).
* **run coverage** -- at least half of the pointer-like words must sit in such
  runs.  Audio/struct data with an isolated pointer every 12 bytes fails this.
* **target validity** -- at least 90% of the candidate targets must resolve
  into a mapped section.  A 16-bit pair whose fake target lands in unallocated
  ROM space is not a pointer.

A blob is a `pointer_table` only when it is mostly pointers (density >= 50%).
A blob that passes the density/target tests but is mixed (a pointer run inside
glyph/tile data, or pointer fields at a regular struct stride) is reported as
`possible_pointer_table` and needs manual review.
"""

from __future__ import annotations

import argparse
import json
import statistics
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from map_symbols import SymbolMap, category  # noqa: E402

POINTER_CATEGORIES = {"rom", "ewram", "iwram"}

# Structural thresholds.  Keep them named and documented so the report can
# quote the rule rather than a bare magic number.
MIN_HITS = 8
MIN_DENSITY = 0.15
MIN_KNOWN_RATIO = 0.9
MIN_TABLE_DENSITY = 0.5
MIN_RUN = 8
MIN_RUN_COVERAGE = 0.5
MIN_STRIDE = 2
MIN_STRIDE_COVERAGE = 0.5


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


def _runs(offsets: list[int]) -> list[tuple[int, int]]:
    """Maximal runs of pointer words, as (byte offset, word count)."""
    runs: list[tuple[int, int]] = []
    i = 0
    while i < len(offsets):
        j = i
        while j + 1 < len(offsets) and offsets[j + 1] == offsets[j] + 4:
            j += 1
        runs.append((offsets[i], j - i + 1))
        i = j + 1
    return runs


def _stride(offsets: list[int]) -> tuple[int, float]:
    """Most common non-contiguous gap between hits, and its coverage.

    A flat table has gap 1 (contiguous), so only gaps >= 2 are considered
    here.  A regular 12-byte struct with a pointer field yields stride 3.
    """
    gaps = Counter((b - a) // 4 for a, b in zip(offsets, offsets[1:]))
    structural = {gap: count for gap, count in gaps.items() if gap >= MIN_STRIDE}
    if not structural:
        return 0, 0.0
    stride, _count = min(
        structural.items(), key=lambda item: (-item[1], item[0])
    )
    hit_set = set(offsets)
    covered = sum(
        1
        for off in offsets
        if off - 4 * stride in hit_set or off + 4 * stride in hit_set
    )
    return stride, covered / len(offsets)


def classify(metrics: dict) -> tuple[str, str]:
    """Return (classification, one-line reason) from structural metrics."""
    hits = metrics["hits"]
    density = metrics["density"]
    known = metrics["known_ratio"]
    longest = metrics["longest_run"]
    run_coverage = metrics["run_coverage"]
    stride = metrics["stride"]
    stride_coverage = metrics["stride_coverage"]

    if hits == 0:
        return "data", "no pointer-like words"

    if hits >= MIN_HITS and density >= MIN_DENSITY and known >= MIN_KNOWN_RATIO:
        if (
            density >= MIN_TABLE_DENSITY
            and longest >= MIN_RUN
            and run_coverage >= MIN_RUN_COVERAGE
        ):
            return (
                "pointer_table",
                f"flat {longest}-word pointer run; "
                f"{density:.0%} of words are pointers; targets mapped",
            )
        if longest >= MIN_RUN:
            return (
                "possible_pointer_table",
                f"{longest}-word pointer run inside non-pointer data; "
                "mixed blob",
            )
        if stride >= MIN_STRIDE and stride_coverage >= MIN_STRIDE_COVERAGE:
            return (
                "possible_pointer_table",
                f"pointers recur at a {stride}-word struct stride; "
                "embedded pointer field",
            )
        return (
            "data",
            f"pointer-like words are scattered "
            f"(density {density:.1%}, longest run {longest})",
        )

    if known < MIN_KNOWN_RATIO and density >= MIN_DENSITY:
        return (
            "data",
            f"{known:.0%} of candidates resolve to mapped sections; "
            "16-bit data artifacts",
        )
    return (
        "data",
        f"below table threshold (density {density:.1%}, "
        f"longest run {longest}, mapped {known:.0%})",
    )


def baseline_classify(hits: int, density: float, unique_targets: int) -> str:
    """The SHIFT-002 rule, retained for before/after comparison."""
    if hits >= 8 and density >= 0.15 and unique_targets >= 4:
        return "pointer_table"
    if hits >= 4 and density >= 0.02:
        return "possible_pointer_table"
    return "data"


def confidence(classification: str, baseline: str, hits: int, density: float) -> str:
    if classification == "pointer_table":
        return "high"
    if classification == "possible_pointer_table":
        return "medium"
    if baseline != "data" or (hits >= MIN_HITS and density >= 0.02):
        return "medium"
    return "high"


def scan_blob(entry: dict, sm: SymbolMap) -> dict:
    path = entry["file"]
    if not path.exists():
        # Fail safe: `make audit` runs without a data root in trees that do not
        # keep extracted blobs, so every key consumed by the summary must exist.
        return {
            "path": entry["path"],
            "addr": entry["addr"],
            "missing": True,
            "bytes": 0,
            "hits": 0,
            "density": 0.0,
            "unique_targets": 0,
            "target_sections": {},
            "known_ratio": 0.0,
            "longest_run": 0,
            "longest_run_offset": 0,
            "run_coverage": 0.0,
            "stride": 0,
            "stride_coverage": 0.0,
            "median_target_delta": 0,
            "baseline_classification": "missing",
            "classification": "missing",
            "confidence": "low",
            "reason": "file not found under --data-root",
            "samples": [],
        }

    data = path.read_bytes()
    hit_offsets: list[int] = []
    hit_addresses: list[int] = []
    target_counter: Counter[str] = Counter()
    section_counter: Counter[str] = Counter()
    samples: list[dict] = []
    known = 0

    for off in range(0, len(data) - 3, 4):
        value = struct.unpack_from("<I", data, off)[0]
        cat = category(value)
        if cat not in POINTER_CATEGORIES:
            continue
        target = sm.resolve(value)
        key = f"{target.get('symbol') or '?'}+{target.get('offset')}"
        target_counter[key] += 1
        section = target.get("section") or "unknown"
        section_counter[section] += 1
        if section != "unknown":
            known += 1
        hit_offsets.append(off)
        hit_addresses.append(value)
        if len(samples) < 16:
            samples.append(
                {
                    "offset": off,
                    "value": f"0x{value:08X}",
                    "category": cat,
                    "target": target,
                }
            )

    words = max(1, len(data) // 4)
    hits = len(hit_offsets)
    density = hits / words
    unique_targets = len(target_counter)
    known_ratio = known / hits if hits else 0.0

    runs = _runs(hit_offsets) if hit_offsets else []
    longest_run_offset, longest_run = (
        max(runs, key=lambda r: r[1]) if runs else (0, 0)
    )
    run_coverage = (
        sum(length for _off, length in runs if length >= MIN_RUN) / hits
        if hits
        else 0.0
    )
    stride, stride_coverage = _stride(hit_offsets) if hits else (0, 0.0)

    unique_addr_values = sorted(set(hit_addresses))
    deltas = [b - a for a, b in zip(unique_addr_values, unique_addr_values[1:])]
    median_target_delta = statistics.median(deltas) if deltas else 0

    metrics = {
        "hits": hits,
        "density": density,
        "unique_targets": unique_targets,
        "known_ratio": known_ratio,
        "longest_run": longest_run,
        "run_coverage": run_coverage,
        "stride": stride,
        "stride_coverage": stride_coverage,
    }
    classification, reason = classify(metrics)
    baseline = baseline_classify(hits, density, unique_targets)

    return {
        "path": entry["path"],
        "addr": entry["addr"],
        "bytes": len(data),
        "hits": hits,
        "density": round(density, 4),
        "unique_targets": unique_targets,
        "target_sections": dict(section_counter.most_common()),
        "known_ratio": round(known_ratio, 4),
        "longest_run": longest_run,
        "longest_run_offset": longest_run_offset,
        "run_coverage": round(run_coverage, 4),
        "stride": stride,
        "stride_coverage": round(stride_coverage, 4),
        "median_target_delta": median_target_delta,
        "baseline_classification": baseline,
        "classification": classification,
        "confidence": confidence(classification, baseline, hits, density),
        "reason": reason,
        "samples": samples,
    }


def self_check() -> int:
    """Deterministic checks for the classification rule."""
    cases = [
        (
            "flat pointer table",
            {
                "hits": 64,
                "density": 1.0,
                "unique_targets": 64,
                "known_ratio": 1.0,
                "longest_run": 64,
                "run_coverage": 1.0,
                "stride": 0,
                "stride_coverage": 0.0,
            },
            "pointer_table",
        ),
        (
            "palette (16-bit false positives)",
            {
                "hits": 40,
                "density": 0.031,
                "unique_targets": 17,
                "known_ratio": 0.3,
                "longest_run": 1,
                "run_coverage": 0.0,
                "stride": 8,
                "stride_coverage": 0.6,
            },
            "data",
        ),
        (
            "16-bit sprite data",
            {
                "hits": 47,
                "density": 0.157,
                "unique_targets": 32,
                "known_ratio": 0.72,
                "longest_run": 2,
                "run_coverage": 0.0,
                "stride": 2,
                "stride_coverage": 0.32,
            },
            "data",
        ),
        (
            "struct array with a pointer field",
            {
                "hits": 210,
                "density": 0.333,
                "unique_targets": 207,
                "known_ratio": 1.0,
                "longest_run": 1,
                "run_coverage": 0.0,
                "stride": 3,
                "stride_coverage": 1.0,
            },
            "possible_pointer_table",
        ),
        (
            "mixed glyph data + pointer run",
            {
                "hits": 25,
                "density": 0.373,
                "unique_targets": 22,
                "known_ratio": 1.0,
                "longest_run": 21,
                "run_coverage": 0.84,
                "stride": 3,
                "stride_coverage": 0.88,
            },
            "possible_pointer_table",
        ),
        (
            "empty data",
            {
                "hits": 0,
                "density": 0.0,
                "unique_targets": 0,
                "known_ratio": 0.0,
                "longest_run": 0,
                "run_coverage": 0.0,
                "stride": 0,
                "stride_coverage": 0.0,
            },
            "data",
        ),
    ]
    failed = 0
    for name, metrics, expected in cases:
        got, reason = classify(metrics)
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected}, got {got} ({reason})")
        else:
            print(f"  ok   {name}: {got}")
    if failed:
        print(f"self-check: {failed}/{len(cases)} failed")
        return 1
    print(f"self-check: {len(cases)}/{len(cases)} passed")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--database", default="database.json")
    ap.add_argument("--data-root", default="data")
    ap.add_argument("--map", default="mf_us.map")
    ap.add_argument("--out", default="work/shift/blob_scan.json")
    ap.add_argument(
        "--self-check",
        action="store_true",
        help="run the classifier unit checks and exit (no files needed)",
    )
    args = ap.parse_args()

    if args.self_check:
        return self_check()

    sm = SymbolMap.load(Path(args.map))
    entries = blob_entries(Path(args.database), Path(args.data_root))
    results = [scan_blob(e, sm) for e in entries]

    # `missing` is not a data class; keep it out of the 7/3/37 counts.
    summary = Counter(
        r["classification"]
        for r in results
        if r["classification"] != "missing"
    )
    baseline = Counter(
        r["baseline_classification"]
        for r in results
        if r["baseline_classification"] != "missing"
    )
    missing = sum(1 for r in results if r.get("missing"))
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(
        json.dumps(
            {
                "rules": {
                    "min_hits": MIN_HITS,
                    "min_density": MIN_DENSITY,
                    "min_known_ratio": MIN_KNOWN_RATIO,
                    "min_table_density": MIN_TABLE_DENSITY,
                    "min_run": MIN_RUN,
                    "min_run_coverage": MIN_RUN_COVERAGE,
                    "min_stride": MIN_STRIDE,
                    "min_stride_coverage": MIN_STRIDE_COVERAGE,
                },
                "summary": dict(summary),
                "missing": missing,
                "baseline_summary": dict(baseline),
                "blobs": results,
            },
            indent=2,
        )
        + "\n"
    )

    print(f"blob audit: {len(results)} blobs -> {out}")
    print(f"  classification: {dict(summary)}")
    if missing:
        print(
            f"  missing: {missing} (no extracted bytes under "
            f"{args.data_root}; pass --data-root to classify)"
        )
    print(f"  baseline (SHIFT-002) rule: {dict(baseline)}")
    print("  candidates:")
    for r in sorted(
        results,
        key=lambda x: (x.get("density", 0), x.get("hits", 0)),
        reverse=True,
    ):
        if r.get("classification") in {
            "pointer_table",
            "possible_pointer_table",
        }:
            print(
                f"    {r['classification']:22s} hits={r['hits']:5d} "
                f"density={r['density']:.3f} run={r['longest_run']:4d} "
                f"targets={r['unique_targets']:4d} {r['path']}"
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
