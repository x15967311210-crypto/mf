#!/usr/bin/env python3
"""Behavior runner.

Static mode always works.  Dynamic mode uses mGBA's Lua interface; if no
emulator is installed it exits 77 (skip), never a false pass.
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCENARIO_DIR = Path(__file__).resolve().parent


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
        cmd = [harness, str(rom), str(frames)]
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
        if "PASS:" not in output:
            print("FAIL: harness did not print PASS")
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
    if "local FRAMES =" in text:
        text = text.replace("local FRAMES = 600", f"local FRAMES = {frames}")
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
    if "PASS:" not in proc.stdout:
        print("FAIL: scenario did not print PASS")
        return 1
    print(f"PASS: {scenario}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rom", default="mf_us.gba")
    ap.add_argument("--baserom", default="mf_us_baserom.gba")
    ap.add_argument("--scenario", default="boot_smoke")
    ap.add_argument("--frames", type=int, default=600)
    ap.add_argument("--static", action="store_true", help="only static ROM checks")
    ap.add_argument("--expect-sha1", default=None)
    args = ap.parse_args()

    rom = Path(args.rom)
    if not rom.is_absolute():
        rom = ROOT / rom
    static_code = run_static(rom, args.expect_sha1)
    if static_code != 0 or args.static:
        return static_code
    return run_dynamic(rom, args.scenario, args.frames)


if __name__ == "__main__":
    raise SystemExit(main())
