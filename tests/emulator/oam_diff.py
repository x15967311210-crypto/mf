#!/usr/bin/env python3
"""Compare QA-008 OAM checkpoint telemetry from two input-replay logs.

`tests/emulator/harness.c` prints one stable line per input checkpoint:

    OAM frame=300 count=0 hash=a3fc73c7a870e39f stage=a3fc73c7a870e39f

`count` is `gNextOamSlot` (0x030011EE); `hash` is FNV-1a 64 over all 128
hardware OAM entries at 0x07000000; `stage` is the same hash over the
`gOamData` shadow buffer at 0x03000DE8.  The hardware OAM hash and the count
decide pass/fail.  The stage hash is telemetry: a stale unused slot in the
shadow buffer must not fail an otherwise identical frame.

This tool is standard-library only and never reads a ROM.  It exits 0 on a
match, 1 on a missing/mismatched checkpoint, and 2 on an unreadable or
malformed log.  `--self-check` exercises the parser and comparison rules
without an emulator.
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path

DEFAULT_CHECKPOINTS = (300, 600, 900, 1059, 4000, 30000)

OAM_RE = re.compile(
    r"^OAM frame=(?P<frame>\d+) count=(?P<count>\d+) "
    r"hash=(?P<hash>[0-9a-fA-F]+)"
    r"(?: stage=(?P<stage>[0-9a-fA-F]+))?$"
)


@dataclass(frozen=True)
class OamSample:
    frame: int
    count: int
    hash: str
    stage: str | None


@dataclass
class Comparison:
    rows: list[str]
    errors: list[str]
    matched: int = 0
    stage_mismatched: int = 0
    missing: int = 0


def parse_lines(lines, source: str = "<log>") -> dict[int, OamSample]:
    samples: dict[int, OamSample] = {}
    for number, raw in enumerate(lines, 1):
        line = raw.rstrip("\r\n")
        if not line.startswith("OAM "):
            continue
        match = OAM_RE.match(line)
        if not match:
            raise ValueError(f"{source}:{number}: malformed OAM line: {line!r}")
        frame = int(match.group("frame"))
        if frame in samples:
            raise ValueError(
                f"{source}:{number}: duplicate OAM frame={frame}"
            )
        hash_value = match.group("hash").lower()
        stage_value = match.group("stage")
        samples[frame] = OamSample(
            frame=frame,
            count=int(match.group("count")),
            hash=hash_value,
            stage=stage_value.lower() if stage_value else None,
        )
    return samples


def parse_log(path: Path) -> dict[int, OamSample]:
    try:
        text = path.read_text()
    except OSError as exc:
        raise ValueError(f"{path}: {exc}") from exc
    return parse_lines(text.splitlines(), str(path))


def compare(
    normal: dict[int, OamSample],
    shifted: dict[int, OamSample],
    checkpoints,
) -> Comparison:
    result = Comparison(rows=[], errors=[])
    for frame in checkpoints:
        normal_sample = normal.get(frame)
        shifted_sample = shifted.get(frame)
        if normal_sample is None or shifted_sample is None:
            result.missing += 1
            absent = []
            if normal_sample is None:
                absent.append("normal")
            if shifted_sample is None:
                absent.append("shifted")
            result.rows.append(
                f"OAM-DIFF frame={frame} status=missing "
                f"absent={','.join(absent)}"
            )
            result.errors.append(
                f"missing {','.join(absent)} OAM checkpoint at frame {frame}"
            )
            continue

        count_match = normal_sample.count == shifted_sample.count
        hash_match = normal_sample.hash == shifted_sample.hash
        stage_match = normal_sample.stage == shifted_sample.stage
        ok = count_match and hash_match
        if ok:
            result.matched += 1
        else:
            result.errors.append(
                f"count/hash mismatch at frame {frame}"
            )
        if not stage_match:
            result.stage_mismatched += 1
        result.rows.append(
            f"OAM-DIFF frame={frame} "
            f"normal_count={normal_sample.count} "
            f"normal_hash={normal_sample.hash} "
            f"shifted_count={shifted_sample.count} "
            f"shifted_hash={shifted_sample.hash} "
            f"status={'match' if ok else 'mismatch'} "
            f"stage={'match' if stage_match else 'different'}"
        )
    return result


def print_comparison(normal, shifted, checkpoints) -> int:
    result = compare(normal, shifted, checkpoints)
    for row in result.rows:
        print(row)
    print(
        f"OAM-DIFF summary checkpoints={len(checkpoints)} "
        f"matched={result.matched} "
        f"mismatched={len(result.errors) - result.missing} "
        f"missing={result.missing} "
        f"stage_different={result.stage_mismatched}"
    )
    if result.errors:
        for error in result.errors:
            print(f"OAM-DIFF: FAIL - {error}")
        return 1
    print("OAM-DIFF: PASS - normal and shifted OAM checkpoints match")
    return 0


def self_check() -> int:
    base = [
        "OAM frame=300 count=0 hash=aaaaaaaaaaaaaaaa stage=aaaaaaaaaaaaaaaa",
        "OAM frame=600 count=8 hash=bbbbbbbbbbbbbbbb stage=cccccccccccccccc",
        "not an OAM line",
    ]
    normal = parse_lines(base, "normal")
    shifted = parse_lines(base, "shifted")
    checkpoints = (300, 600)
    if compare(normal, shifted, checkpoints).errors:
        print("OAM-DIFF: SELF-CHECK FAIL - identical samples diverged")
        return 1

    count_changed = parse_lines(
        [
            "OAM frame=300 count=0 hash=aaaaaaaaaaaaaaaa",
            "OAM frame=600 count=7 hash=bbbbbbbbbbbbbbbb",
        ],
        "count",
    )
    if not compare(normal, count_changed, checkpoints).errors:
        print("OAM-DIFF: SELF-CHECK FAIL - count mismatch was not detected")
        return 1

    hash_changed = parse_lines(
        [
            "OAM frame=300 count=0 hash=aaaaaaaaaaaaaaaa",
            "OAM frame=600 count=8 hash=dddddddddddddddd",
        ],
        "hash",
    )
    if not compare(normal, hash_changed, checkpoints).errors:
        print("OAM-DIFF: SELF-CHECK FAIL - hash mismatch was not detected")
        return 1

    missing = parse_lines(base[:1], "missing")
    if not compare(normal, missing, checkpoints).errors:
        print("OAM-DIFF: SELF-CHECK FAIL - missing checkpoint was not detected")
        return 1

    stage_only = parse_lines(
        [
            "OAM frame=300 count=0 hash=aaaaaaaaaaaaaaaa stage=eeeeeeeeeeeeeeee",
            "OAM frame=600 count=8 hash=bbbbbbbbbbbbbbbb stage=cccccccccccccccc",
        ],
        "stage",
    )
    stage_result = compare(normal, stage_only, checkpoints)
    if stage_result.errors or stage_result.stage_mismatched != 1:
        print("OAM-DIFF: SELF-CHECK FAIL - gOamData stage is not telemetry-only")
        return 1

    try:
        parse_lines(["OAM frame=bad"], "malformed")
    except ValueError:
        pass
    else:
        print("OAM-DIFF: SELF-CHECK FAIL - malformed line was accepted")
        return 1

    print("OAM-DIFF: SELF-CHECK PASS")
    return 0


def parse_checkpoints(text: str) -> tuple[int, ...]:
    frames = []
    for token in text.replace(",", " ").split():
        try:
            frame = int(token, 0)
        except ValueError as exc:
            raise ValueError(f"invalid checkpoint {token!r}") from exc
        if frame <= 0:
            raise ValueError(f"checkpoint must be positive: {token!r}")
        frames.append(frame)
    if not frames:
        raise ValueError("no checkpoints supplied")
    for first, second in zip(frames, frames[1:]):
        if second <= first:
            raise ValueError("checkpoints must increase")
    return tuple(frames)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--normal", type=Path, help="normal-ROM replay log")
    ap.add_argument("--shifted", type=Path, help="shifted-ROM replay log")
    ap.add_argument(
        "--checkpoints",
        default=" ".join(str(f) for f in DEFAULT_CHECKPOINTS),
        help="space/comma-separated checkpoint frames",
    )
    ap.add_argument(
        "--self-check",
        action="store_true",
        help="exercise the parser/comparison rules without a log",
    )
    args = ap.parse_args()

    if args.self_check:
        return self_check()
    if not args.normal or not args.shifted:
        ap.error("--normal and --shifted are required without --self-check")
    try:
        checkpoints = parse_checkpoints(args.checkpoints)
        normal = parse_log(args.normal)
        shifted = parse_log(args.shifted)
    except ValueError as exc:
        print(f"OAM-DIFF: FAIL - {exc}")
        return 2
    return print_comparison(normal, shifted, checkpoints)


if __name__ == "__main__":
    sys.exit(main())
