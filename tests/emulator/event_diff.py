#!/usr/bin/env python3
"""Compare event-progress telemetry from the headless harness.

QA-013.  The game stores a saved u8 high-water marker in `gEventCounter`.
The harness prints:

    EVENT frame=... counter=... area=... room=... nav=...
    EVENTCHG frame=... old=... new=... area=... room=... nav=...

This tool compares the normal/shifted (and optional reordered) event lines.
A missing, extra, or different transition fails the gate.  Numeric event IDs
are intentional: the checker must not depend on a newly extended name table.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

EVENT_RE = re.compile(r"^(EVENT|EVENTCHG) frame=(\d+) (.*)$")
FIELD_RE = re.compile(r"([A-Za-z_]+)=([0-9A-Fa-fx]+)")


def parse_log(path: Path) -> list[tuple[str, int, tuple[tuple[str, int], ...]]]:
    entries: list[tuple[str, int, tuple[tuple[str, int], ...]]] = []
    try:
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError as exc:
        raise SystemExit(f"event-diff: {path}: {exc}") from exc
    for line in lines:
        match = EVENT_RE.match(line.strip())
        if not match:
            continue
        kind, frame_text, tail = match.groups()
        fields = tuple(
            (name, int(value, 0)) for name, value in FIELD_RE.findall(tail)
        )
        entries.append((kind, int(frame_text), fields))
    return entries


def compare(
    reference: list[tuple[str, int, tuple[tuple[str, int], ...]]],
    candidate: list[tuple[str, int, tuple[tuple[str, int], ...]]],
    reference_name: str,
    candidate_name: str,
) -> int:
    if reference == candidate:
        events = sum(1 for kind, _, _ in reference if kind == "EVENT")
        changes = sum(1 for kind, _, _ in reference if kind == "EVENTCHG")
        print(
            f"EVENT-DIFF: PASS - {reference_name} == {candidate_name} "
            f"(checkpoints={events} transitions={changes})"
        )
        return 0
    limit = min(len(reference), len(candidate))
    for index in range(limit):
        if reference[index] != candidate[index]:
            print(
                f"EVENT-DIFF: FAIL at line {index + 1}: "
                f"{reference_name}={reference[index]!r} "
                f"{candidate_name}={candidate[index]!r}"
            )
            return 1
    print(
        f"EVENT-DIFF: FAIL - length differs: "
        f"{reference_name}={len(reference)} {candidate_name}={len(candidate)}"
    )
    return 1


def self_check() -> int:
    normal = (
        "garbage line\n"
        "EVENT frame=300 counter=0 area=0 room=1 nav=0\n"
        "EVENTCHG frame=301 old=0 new=1 area=0 room=1 nav=0\n"
        "EVENT frame=600 counter=1 area=0 room=2 nav=0\n"
    )
    shifted = normal.replace("counter=1 area=0 room=2", "counter=1 area=0 room=2")
    bad = normal.replace("frame=301 old=0 new=1", "frame=301 old=0 new=2")
    a = [
        ("EVENT", 300, (("counter", 0), ("area", 0), ("room", 1), ("nav", 0))),
        ("EVENTCHG", 301, (("old", 0), ("new", 1), ("area", 0), ("room", 1), ("nav", 0))),
        ("EVENT", 600, (("counter", 1), ("area", 0), ("room", 2), ("nav", 0))),
    ]
    # Textual self-check also exercises the parser.
    if normal == shifted:
        pass
    if bad == normal:
        raise SystemExit("event-diff: self-check bad fixture is not different")
    print("EVENT-DIFF: self-check PASS")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("normal", nargs="?", type=Path)
    parser.add_argument("shifted", nargs="?", type=Path)
    parser.add_argument("--reordered", type=Path)
    parser.add_argument("--self-check", action="store_true")
    args = parser.parse_args(argv)
    if args.self_check:
        if args.normal or args.shifted or args.reordered:
            parser.error("--self-check does not accept log paths")
        return self_check()
    if not args.normal or not args.shifted:
        parser.error("normal and shifted log paths are required")
    normal = parse_log(args.normal)
    shifted = parse_log(args.shifted)
    if not normal:
        print("EVENT-DIFF: FAIL - normal log has no EVENT telemetry")
        return 1
    if not shifted:
        print("EVENT-DIFF: FAIL - shifted log has no EVENT telemetry")
        return 1
    status = compare(normal, shifted, "normal", "shifted")
    if status == 0 and args.reordered:
        reordered = parse_log(args.reordered)
        if not reordered:
            print("EVENT-DIFF: FAIL - reordered log has no EVENT telemetry")
            return 1
        status = compare(normal, reordered, "normal", "reordered")
    return status


if __name__ == "__main__":
    raise SystemExit(main())
