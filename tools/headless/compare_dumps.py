#!/usr/bin/env python3
"""Compare a headless replay dump against a BizHawk parity dump.

Example:
  python tools/headless/compare_dumps.py \
      --ours out/headless --ref work/playtest/.../tas/bizhawk_parity \
      --prefix normal

By default it compares the checkpoint log plus OAM, palette, VRAM, I/O and
EWRAM. Those regions cover the game's visible state and map/event state.

IWRAM is not compared by default because the music engine keeps rolling
sample/track buffers there (gMusicInfo / gTrackData5) and those differ between
a sound-enabled headless run and a BizHawk parity run captured with
client.SetSoundOn(false). Pass --iwram to compare the full IWRAM too.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

DEFAULT_SUFFIXES = ("oam.bin", "pal.bin", "vram.bin", "io.bin", "ewram.bin")


def read_log(path: Path) -> dict[int, str]:
    result: dict[int, str] = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split()
        if len(parts) >= 9:
            result[int(parts[0])] = " ".join(parts)
    return result


def compare_bytes(a: Path, b: Path, mask: range | None = None) -> tuple[bool, str]:
    if not a.exists():
        return False, f"missing {a}"
    if not b.exists():
        return False, f"missing {b}"
    da = bytearray(a.read_bytes())
    db = bytearray(b.read_bytes())
    if len(da) != len(db):
        return False, f"size {len(da)} != {len(db)}"
    if mask is not None:
        for i in mask:
            if i < len(da):
                da[i] = db[i] = 0
    if da == db:
        return True, ""
    for i, (x, y) in enumerate(zip(da, db)):
        if x != y:
            return False, f"first diff at +0x{i:05X}: {x:02X} != {y:02X}"
    return False, "differs"


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ours", required=True, type=Path)
    parser.add_argument("--ref", required=True, type=Path)
    parser.add_argument("--prefix", default="normal")
    parser.add_argument("--checkpoints", default="", help="comma separated; default: ref log")
    parser.add_argument("--iwram", action="store_true", help="also compare full IWRAM")
    parser.add_argument("--io-sound", action="store_true",
                        help="compare sound registers 0x04000060-0x040000AF too")
    parser.add_argument("--suffixes", default=",".join(DEFAULT_SUFFIXES))
    args = parser.parse_args(argv)

    suffixes = [s.strip() for s in args.suffixes.split(",") if s.strip()]
    if args.iwram and "iwram.bin" not in suffixes:
        suffixes.append("iwram.bin")

    ref_log_path = args.ref / f"{args.prefix}_log.txt"
    our_log_path = args.ours / f"{args.prefix}_log.txt"
    if not ref_log_path.exists() or not our_log_path.exists():
        print(f"FAIL: missing log: {ref_log_path} / {our_log_path}")
        return 1
    ref_log = read_log(ref_log_path)
    our_log = read_log(our_log_path)
    if args.checkpoints:
        frames = [int(x) for x in args.checkpoints.split(",") if x.strip()]
    else:
        frames = sorted(set(ref_log) & set(our_log))
        if not frames:
            print("FAIL: no common checkpoint frames")
            return 1

    failed = False
    for frame in frames:
        if our_log.get(frame) != ref_log.get(frame):
            print(f"LOGDIF frame {frame}: ours={our_log.get(frame)} ref={ref_log.get(frame)}")
            failed = True
        for suffix in suffixes:
            ours = args.ours / f"{args.prefix}_{frame:06d}_{suffix}"
            ref = args.ref / f"{args.prefix}_{frame:06d}_{suffix}"
            mask = None
            if suffix == "io.bin" and not args.io_sound:
                mask = range(0x60, 0xB0)
            ok, detail = compare_bytes(ours, ref, mask)
            if not ok:
                print(f"DIFF frame {frame} {suffix}: {detail}")
                failed = True

    if failed:
        print("PARITY: FAIL")
        return 1
    print(f"PARITY: PASS ({len(frames)} checkpoints, {len(suffixes)} regions each)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
