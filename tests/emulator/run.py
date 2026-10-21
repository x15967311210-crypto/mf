#!/usr/bin/env python3
"""Behavior runner.

Static mode always works.  Dynamic mode uses mGBA's Lua interface; if no
emulator is installed it exits 77 (skip), never a false pass.

Input replays can opt into an end-state assertion with ``--expect-event``.
That passes ``--final`` to the harness and requires the final `FINAL_EVENT`
line to report the expected area/room, the `INPUT_FINAL` line to report
``main=1`` (in-game) and a live frame counter.  Without the option the
harness invocation and markers are unchanged.
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
    "input": "PASS: input replay",
}
DEFAULT_FRAMES = {
    "boot_smoke": 600,
    "start": 1200,
}

# Input replay is only implemented by the C harness.  A full TAS file can run
# for minutes, so give it a larger default than the fixed scenarios.
DEFAULT_TIMEOUT = 180
INPUT_TIMEOUT = 1800

# `--expect-event` accepts either the harness spelling or AREA:ROOM.
EXPECT_EVENT_RE = re.compile(r"^(?:area=(\d+)\s+room=(\d+)|(\d+):(\d+))$")
FINAL_EVENT_RE = re.compile(
    r"^FINAL_EVENT frame=(\d+) counter=(\d+) area=(\d+) room=(\d+) nav=(\d+)$",
    re.MULTILINE,
)
INPUT_FINAL_RE = re.compile(
    r"^INPUT_FINAL frames=(\d+) frame_counter=(\d+) keys=\d+ "
    r"disp=0x[0-9A-Fa-f]+ main=(\d+)\b",
    re.MULTILINE,
)
# How far the emulator's frame counter may trail the input length before the
# replay is considered frozen.
FRAME_COUNTER_SLACK = 200


def parse_expect_event(value: str) -> tuple[int, int]:
    """Parse ``area=N room=N`` or ``N:N`` into (area, room)."""
    match = EXPECT_EVENT_RE.match(value.strip())
    if not match:
        raise ValueError(
            f"invalid --expect-event {value!r} "
            "(expected 'area=N room=N' or 'AREA:ROOM')"
        )
    if match.group(1) is not None:
        return int(match.group(1)), int(match.group(2))
    return int(match.group(3)), int(match.group(4))


def check_expected_event(output: str, expected: tuple[int, int]) -> bool:
    """Validate the harness end-state lines for an --expect-event run."""
    area, room = expected

    final_event = FINAL_EVENT_RE.search(output)
    if not final_event:
        print("FAIL: --expect-event: harness printed no FINAL_EVENT line")
        return False
    got_area = int(final_event.group(3))
    got_room = int(final_event.group(4))
    if (got_area, got_room) != (area, room):
        print(
            "FAIL: --expect-event: expected area="
            f"{area} room={room}, harness ended at "
            f"area={got_area} room={got_room}"
        )
        return False

    input_final = INPUT_FINAL_RE.search(output)
    if not input_final:
        print("FAIL: --expect-event: harness printed no INPUT_FINAL line")
        return False
    frames = int(input_final.group(1))
    frame_counter = int(input_final.group(2))
    main = int(input_final.group(3))
    if main != 1:
        print(
            "FAIL: --expect-event: expected main=1 (in-game), "
            f"harness reported main={main}"
        )
        return False
    if frame_counter < frames - FRAME_COUNTER_SLACK:
        print(
            "FAIL: --expect-event: replay stalled at "
            f"frame_counter={frame_counter}, expected at least "
            f"{frames - FRAME_COUNTER_SLACK} for a {frames}-frame input"
        )
        return False
    return True


def harness_command(
    harness: str,
    rom: Path,
    scenario: str,
    frames: int | None,
    input_path: str | None = None,
    expect_path: str | None = None,
    screen: bool = False,
    expect_event: tuple[int, int] | None = None,
) -> list[str]:
    """Build the harness argv, preserving the legacy boot-smoke invocation."""
    if scenario == "boot_smoke":
        return [harness, str(rom), str(frames)]
    cmd = [harness, str(rom), "--scenario", scenario]
    if scenario == "input":
        if not input_path:
            raise ValueError("input scenario needs --input FILE")
        cmd += ["--input", input_path]
        if expect_path:
            cmd += ["--expect", expect_path]
        if screen:
            cmd += ["--screen"]
        if expect_event is not None:
            cmd += ["--final"]
    if frames is not None:
        cmd += ["--frames", str(frames)]
    return cmd


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


def run_dynamic(
    rom: Path,
    scenario: str,
    frames: int | None,
    input_path: str | None = None,
    expect_path: str | None = None,
    timeout: int | None = None,
    screen: bool = False,
    expect_event: tuple[int, int] | None = None,
) -> int:
    harness = find_harness()
    if harness:
        cmd = harness_command(
            harness,
            rom,
            scenario,
            frames,
            input_path,
            expect_path,
            screen,
            expect_event,
        )
        print("RUN:", " ".join(cmd))
        if timeout is None:
            timeout = INPUT_TIMEOUT if scenario == "input" else DEFAULT_TIMEOUT
        try:
            proc = subprocess.run(
                cmd,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=timeout,
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
        # Fixed scenarios print a short summary.  Input replay keeps every
        # checkpoint line so a full run's early checkpoints are not truncated.
        shown = lines if scenario == "input" else lines[-12:]
        for line in shown:
            print(line)
        if proc.returncode != 0:
            print(f"FAIL: harness exited {proc.returncode}")
            return 1
        marker = PASS_MARKERS.get(scenario, "PASS:")
        if marker not in output:
            print(f"FAIL: harness did not print {marker!r}")
            return 1
        if expect_event is not None:
            if not check_expected_event(output, expect_event):
                return 1
            print(
                f"PASS: expected event area={expect_event[0]} "
                f"room={expect_event[1]} (in-game, live)"
            )
        print(f"PASS: {scenario}")
        return 0

    if scenario == "input":
        print(
            "SKIP: input replay needs the headless harness "
            "(build tests/emulator/bin/mgba-harness or set MF_MGBA_HARNESS)"
        )
        return 77

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
    ap.add_argument(
        "--input",
        default=None,
        help="`frame keys` file to replay (implies --scenario input)",
    )
    ap.add_argument(
        "--expect",
        default=None,
        help="expected `frame disp main s1 s2` checkpoints for --input",
    )
    ap.add_argument(
        "--screen",
        action="store_true",
        help="hash the framebuffer at input checkpoints (requires --input)",
    )
    ap.add_argument(
        "--expect-event",
        default=None,
        metavar="AREA:ROOM",
        help="require the input replay to end in area/room, in-game and "
        "live (e.g. 'area=7 room=0' or '7:0'); implies --final",
    )
    ap.add_argument(
        "--timeout",
        type=int,
        default=None,
        help=f"harness timeout in seconds (default: {DEFAULT_TIMEOUT}, "
        f"{INPUT_TIMEOUT} for input replay)",
    )
    ap.add_argument("--static", action="store_true", help="only static ROM checks")
    ap.add_argument("--expect-sha1", default=None)
    args = ap.parse_args()

    if args.input and args.scenario not in ("input", "boot_smoke"):
        ap.error("--input implies the input scenario; do not combine it with "
                 f"--scenario {args.scenario}")
    if args.expect and not args.input:
        ap.error("--expect requires --input FILE")
    if args.screen and not args.input:
        ap.error("--screen requires --input FILE")
    if args.expect_event and not args.input:
        ap.error("--expect-event requires --input FILE")
    expect_event = None
    if args.expect_event:
        try:
            expect_event = parse_expect_event(args.expect_event)
        except ValueError as exc:
            ap.error(str(exc))
    scenario = "input" if args.input else args.scenario
    if scenario == "input" and not args.input:
        ap.error("--scenario input requires --input FILE")

    rom = Path(args.rom)
    if not rom.is_absolute():
        rom = ROOT / rom
    frames = args.frames
    if frames is None and scenario != "input":
        frames = DEFAULT_FRAMES.get(scenario, 600)
    static_code = run_static(rom, args.expect_sha1)
    if static_code != 0 or args.static:
        return static_code
    return run_dynamic(
        rom,
        scenario,
        frames,
        args.input,
        args.expect,
        args.timeout,
        args.screen,
        expect_event,
    )


if __name__ == "__main__":
    raise SystemExit(main())
