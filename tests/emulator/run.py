#!/usr/bin/env python3
"""Behavior runner.

Static mode always works.  Dynamic mode uses mGBA's Lua interface; if no
emulator is installed it exits 77 (skip), never a false pass.
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCENARIO_DIR = Path(__file__).resolve().parent

# The harness prints one of these only when its own assertions passed.  A
# stale harness (one built before the scenario existed) cannot fake the marker.
PASS_MARKERS = {
    "boot_smoke": "PASS: boot smoke",
    "start": "PASS: start/file-select",
}
DEFAULT_FRAMES = {
    "boot_smoke": 600,
    "start": 1200,
}


def harness_command(harness: str, rom: Path, scenario: str, frames: int) -> list[str]:
    """Build the harness argv, preserving the legacy boot-smoke invocation."""
    if scenario == "boot_smoke":
        return [harness, str(rom), str(frames)]
    return [harness, str(rom), "--scenario", scenario, "--frames", str(frames)]


def find_mgba() -> str | None:
    env = os.environ.get("MGBA_BIN")
    if env:
        return env
    for name in ("mgba", "mgba-sdl", "mgba-qt"):
        found = shutil.which(name)
        if found:
            return found
    return None


def find_harness() -> str | None:
    env = os.environ.get("MF_MGBA_HARNESS")
    if env:
        return env
    local = SCENARIO_DIR / "bin" / "mgba-harness"
    if local.exists():
        return str(local)
    return None


def run_static(rom: Path, expect_sha1: str | None) -> int:
    cmd = [sys.executable, str(SCENARIO_DIR / "rom_smoke.py"), "--rom", str(rom)]
    if expect_sha1:
        cmd += ["--expect-sha1", expect_sha1]
    return subprocess.call(cmd)


def run_dynamic(rom: Path, scenario: str, frames: int) -> int:
    harness = find_harness()
    if harness:
        cmd = harness_command(harness, rom, scenario, frames)
        print("RUN:", " ".join(cmd))
        try:
            proc = subprocess.run(
                cmd,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=180,
            )
        except subprocess.TimeoutExpired:
            print("FAIL: harness timed out")
            return 1
        output = proc.stdout
        # mGBA's default logger is noisy; keep only the harness's own lines.
        lines = [
            line
            for line in output.splitlines()
            if not line.startswith(("GBA ", "GBA:", "GBA BIOS", "GBA DMA", "GBA Memory"))
        ]
        for line in lines[-12:]:
            print(line)
        if proc.returncode != 0:
            print(f"FAIL: harness exited {proc.returncode}")
            return 1
        marker = PASS_MARKERS.get(scenario, "PASS:")
        if marker not in output:
            print(f"FAIL: harness did not print {marker!r}")
            return 1
        print(f"PASS: {scenario}")
        return 0

    mgba = find_mgba()
    if not mgba:
        print(
            "SKIP: no headless harness and no mGBA "
            "(install mgba-sdl or build tests/emulator/bin/mgba-harness)"
        )
        return 77

    source = SCENARIO_DIR / f"{scenario}.lua"
    if not source.exists():
        print(f"FAIL: missing scenario {source}")
        return 1

    work = ROOT / "work" / "emulator"
    work.mkdir(parents=True, exist_ok=True)
    generated = work / f"{scenario}.generated.lua"
    text = source.read_text()
    text = re.sub(
        r"local FRAMES = \d+", f"local FRAMES = {frames}", text, count=1
    )
    generated.write_text(text)

    env = os.environ.copy()
    env.setdefault("SDL_VIDEODRIVER", "dummy")
    env.setdefault("SDL_AUDIODRIVER", "dummy")
    cmd = [mgba, "-l", str(generated), str(rom)]
    print("RUN:", " ".join(cmd))
    try:
        proc = subprocess.run(
            cmd,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=180,
        )
    except subprocess.TimeoutExpired:
        print("FAIL: emulator timed out")
        return 1
    print(proc.stdout)
    if proc.returncode != 0:
        print(f"FAIL: emulator exited {proc.returncode}")
        return 1
    marker = PASS_MARKERS.get(scenario, "PASS:")
    if marker not in proc.stdout:
        print(f"FAIL: scenario did not print {marker!r}")
        return 1
    print(f"PASS: {scenario}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rom", default="mf_us.gba")
    ap.add_argument("--baserom", default="mf_us_baserom.gba")
    ap.add_argument("--scenario", default="boot_smoke")
    ap.add_argument("--frames", type=int, default=None)
    ap.add_argument("--static", action="store_true", help="only static ROM checks")
    ap.add_argument("--expect-sha1", default=None)
    args = ap.parse_args()

    rom = Path(args.rom)
    if not rom.is_absolute():
        rom = ROOT / rom
    frames = args.frames
    if frames is None:
        frames = DEFAULT_FRAMES.get(args.scenario, 600)
    static_code = run_static(rom, args.expect_sha1)
    if static_code != 0 or args.static:
        return static_code
    return run_dynamic(rom, args.scenario, frames)


if __name__ == "__main__":
    raise SystemExit(main())
