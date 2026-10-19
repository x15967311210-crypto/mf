#!/usr/bin/env python3
"""Verify headless dumps against tools/headless/golden_manifest.json."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


def sha1(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--dir", required=True, type=Path)
    parser.add_argument("--prefix", default="normal")
    parser.add_argument("--manifest", type=Path,
                        default=Path(__file__).with_name("golden_manifest.json"))
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--bios", type=Path)
    parser.add_argument("--movie", type=Path)
    parser.add_argument("--checkpoints", default="",
                        help="comma separated; default: all in manifest")
    args = parser.parse_args()

    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    failed = False

    for label, path, key in (("ROM", args.rom, "rom_sha1"),
                             ("BIOS", args.bios, "bios_sha1"),
                             ("movie", args.movie, "movie_sha1")):
        if path is not None:
            got = sha1(path)
            if got != manifest[key]:
                print(f"INPUT DIFF {label}: {got} != {manifest[key]}")
                failed = True
            else:
                print(f"input {label}: OK")

    if args.checkpoints:
        frames = [int(x) for x in args.checkpoints.split(",") if x.strip()]
    else:
        frames = [int(x) for x in manifest["checkpoints"]]

    log_path = args.dir / f"{args.prefix}_log.txt"
    log_lines = {}
    if log_path.exists():
        for line in log_path.read_text(encoding="utf-8", errors="replace").splitlines():
            if line and not line.startswith("#"):
                log_lines[line.split()[0]] = line

    for frame in frames:
        expected = manifest["checkpoints"].get(str(frame))
        if expected is None:
            print(f"GOLDEN MISSING frame {frame}")
            failed = True
            continue
        for region in manifest["regions"]:
            path = args.dir / f"{args.prefix}_{frame:06d}_{region}.bin"
            if not path.exists():
                print(f"MISSING frame {frame} {region}: {path}")
                failed = True
                continue
            got = sha1(path)
            if got != expected[region]:
                print(f"DIFF frame {frame} {region}: {got} != {expected[region]}")
                failed = True
        want_line = manifest.get("log_lines", {}).get(str(frame))
        if want_line is not None and log_lines.get(str(frame)) != want_line:
            print(f"LOGDIFF frame {frame}: ours={log_lines.get(str(frame))} ref={want_line}")
            failed = True

    print("HEADLESS GOLDEN: " + ("FAIL" if failed else "PASS"))
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
