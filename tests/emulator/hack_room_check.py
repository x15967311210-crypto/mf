#!/usr/bin/env python3
"""HACK-008d4b: sprite-liveness check for the hack Entry Ledge room.

Replays a fixed prefix of the committed baseline input (frame 28450, verified
stable across runs), dumps IWRAM through the headless harness, and asserts the
generated spriteset table and the live sprite-table entries that the room build
spawns.  Everything is read from fixed IWRAM addresses (D-002), never from a
screenshot.

The prefix is rebuilt deterministically from the committed input fixture, so
this check needs no extra data in Git.  It exits 77 (skip) when the headless
harness is unavailable, mirroring ``run.py``.

The ``--expect-table`` / ``--expect-live`` options exist only to exercise the
failure path without editing the committed constants; the defaults are the
assertions that gate the build.
"""

from __future__ import annotations

import argparse
import hashlib
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCENARIO_DIR = Path(__file__).resolve().parent

HACK_ROM = ROOT / "work" / "hack" / "mf_us_hack.gba"
HACK_ELF = ROOT / "work" / "hack" / "mf_us_hack.elf"
INPUT_FIXTURE = ROOT / "tests" / "emulator" / "inputs" / "baseline_first30000.input"
WORK_DIR = ROOT / "work" / "emulator"
PREFIX_PATH = WORK_DIR / "hack_room_prefix.input"
DUMP_PREFIX = WORK_DIR / "hack_room"

# Keep every frame <= this index (28451 frames: 0..28450).  At this point the
# entry-warp room is loaded, the banner is up and the Echo Hunter has spawned.
PREFIX_FRAME = 28450
PREFIX_FRAMES = PREFIX_FRAME + 1

# IWRAM symbols are baseline addresses fixed by docs/decisions.md D-002.  `nm`
# is the source of truth; these are the last-resort fallback if no nm exists.
SYMBOL_FALLBACK = {
    "gSpriteData": 0x03000140,
    "gSpritesetSpriteIds": 0x03000680,
    "gSpritesetSpriteGfxSlots": 0x0300068F,
}
IWRAM_BASE = 0x03000000
IWRAM_BYTES = 0x8000

# SpriteData is 24 entries between gSpriteData and gSpritesetSpriteIds; the
# derived stride must be 0x38.  Fields used here: status u16 at +0, spriteId
# u8 at +0x1D, roomSlot u8 at +0x1E.
SPRITE_COUNT = 24
EXPECTED_STRIDE = 0x38
OFFSET_STATUS = 0x00
OFFSET_SPRITE_ID = 0x1D
OFFSET_ROOM_SLOT = 0x1E

# Generated per-room spriteset and the spawns live at this prefix.  The banner
# keeps its authored message id (spawn record index 2, BUG-022) instead of the
# vanilla UCHAR_MAX overwrite, so TextDrawMessageBanner draws the HACK-008d2
# Entry Ledge text; the Echo Hunter is a Hornoad data clone.
DEFAULT_TABLE = "1F,1E,12,41,62,21,CF"
DEFAULT_GFX_SLOTS = "0,1,2,3,4,5,6"
DEFAULT_LIVE = [
    (0x0003, 0x1F, 0),
    (0x0003, 0x1E, 1),
    (0x0013, 0x21, 2),
    (0x8003, 0x12, 3),
]

FINAL_EVENT_RE = re.compile(
    r"^FINAL_EVENT frame=(\d+) counter=(\d+) area=(\d+) room=(\d+) nav=(\d+)$",
    re.MULTILINE,
)
INPUT_FINAL_RE = re.compile(
    r"^INPUT_FINAL frames=(\d+) frame_counter=(\d+) keys=\d+ "
    r"disp=0x[0-9A-Fa-f]+ main=(\d+)\b",
    re.MULTILINE,
)
FRAME_COUNTER_SLACK = 200
INPUT_TIMEOUT = 1800

EXPECTED_AREA = 7
EXPECTED_ROOM = 0


class CheckError(Exception):
    """A precise, user-facing assertion failure."""


def find_harness() -> str | None:
    env = os.environ.get("MF_MGBA_HARNESS")
    if env:
        return env
    local = SCENARIO_DIR / "bin" / "mgba-harness"
    if local.exists():
        return str(local)
    return None


def find_nm() -> str | None:
    found = shutil.which("arm-none-eabi-nm")
    if found:
        return found
    for candidate in ("/home/x1596/.local/bin/arm-none-eabi-nm",):
        if Path(candidate).exists():
            return candidate
    return None


def resolve_symbols(elf: Path) -> dict[str, int]:
    """Read the three IWRAM addresses from `nm`, falling back to D-002."""
    nm = find_nm()
    if nm is None:
        print(
            "NOTE: no arm-none-eabi-nm found; using D-002 fallback addresses",
            file=sys.stderr,
        )
        return dict(SYMBOL_FALLBACK)
    try:
        proc = subprocess.run(
            [nm, "-n", str(elf)],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=60,
        )
    except subprocess.TimeoutExpired:
        raise CheckError(f"nm timed out reading {elf}")
    if proc.returncode != 0:
        raise CheckError(f"nm exited {proc.returncode} reading {elf}:\n{proc.stdout}")
    symbols: dict[str, int] = {}
    for line in proc.stdout.splitlines():
        parts = line.split()
        if len(parts) < 3:
            continue
        name = parts[-1]
        if name in SYMBOL_FALLBACK and name not in symbols:
            try:
                symbols[name] = int(parts[0], 16)
            except ValueError:
                continue
    missing = [name for name in SYMBOL_FALLBACK if name not in symbols]
    if missing:
        raise CheckError(
            "nm did not resolve " + ", ".join(missing) + f" in {elf}"
        )
    for name, addr in symbols.items():
        if not IWRAM_BASE <= addr < IWRAM_BASE + IWRAM_BYTES:
            raise CheckError(
                f"{name} resolved to 0x{addr:08X}, outside IWRAM "
                f"(0x{IWRAM_BASE:08X}+0x{IWRAM_BYTES:X})"
            )
    return symbols


def build_prefix() -> int:
    """Write work/emulator/hack_room_prefix.input; return the frame count."""
    if not INPUT_FIXTURE.exists():
        raise CheckError(f"missing input fixture {INPUT_FIXTURE}")
    kept: list[str] = []
    frames = 0
    for raw in INPUT_FIXTURE.read_text().splitlines():
        line = raw.strip()
        if not line:
            continue
        if line.startswith("#"):
            kept.append(line)
            continue
        fields = line.split()
        try:
            frame = int(fields[0])
        except (ValueError, IndexError):
            raise CheckError(
                f"malformed input line in {INPUT_FIXTURE}: {raw!r}"
            )
        if frame <= PREFIX_FRAME:
            kept.append(line)
            frames += 1
    if frames != PREFIX_FRAMES:
        raise CheckError(
            f"input fixture yielded {frames} frames for prefix <={PREFIX_FRAME}, "
            f"expected {PREFIX_FRAMES}"
        )
    WORK_DIR.mkdir(parents=True, exist_ok=True)
    PREFIX_PATH.write_text("\n".join(kept) + "\n")
    return frames


def run_harness(harness: str, rom: Path, timeout: int) -> str:
    cmd = [
        harness,
        str(rom),
        "--scenario",
        "input",
        "--input",
        str(PREFIX_PATH),
        "--final",
        "--dump-prefix",
        str(DUMP_PREFIX),
    ]
    print("RUN:", " ".join(cmd))
    try:
        proc = subprocess.run(
            cmd,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
        )
    except subprocess.TimeoutExpired:
        raise CheckError(f"harness timed out after {timeout}s")
    output = proc.stdout or ""
    lines = [
        line
        for line in output.splitlines()
        if not line.startswith(
            ("GBA ", "GBA:", "GBA BIOS", "GBA DMA", "GBA Memory")
        )
    ]
    for line in lines:
        print(line)
    if proc.returncode != 0:
        raise CheckError(f"harness exited {proc.returncode}")
    return output


def check_end_state(output: str) -> tuple[int, int]:
    final_event = FINAL_EVENT_RE.search(output)
    if not final_event:
        raise CheckError("harness printed no FINAL_EVENT line")
    frame = int(final_event.group(1))
    area = int(final_event.group(3))
    room = int(final_event.group(4))
    if (area, room) != (EXPECTED_AREA, EXPECTED_ROOM):
        raise CheckError(
            f"expected area={EXPECTED_AREA} room={EXPECTED_ROOM}, "
            f"harness ended at area={area} room={room}"
        )

    input_final = INPUT_FINAL_RE.search(output)
    if not input_final:
        raise CheckError("harness printed no INPUT_FINAL line")
    frames = int(input_final.group(1))
    frame_counter = int(input_final.group(2))
    main = int(input_final.group(3))
    if main != 1:
        raise CheckError(f"expected main=1 (in-game), harness reported main={main}")
    if frame_counter < frames - FRAME_COUNTER_SLACK:
        raise CheckError(
            f"replay stalled at frame_counter={frame_counter}, expected at "
            f"least {frames - FRAME_COUNTER_SLACK} for a {frames}-frame input"
        )
    print(
        f"END: frame={frame} frames={frames} frame_counter={frame_counter} "
        f"area={area} room={room}"
    )
    return area, room


def parse_table(spec: str, what: str) -> list[int]:
    values: list[int] = []
    for item in spec.split(","):
        item = item.strip()
        if not item:
            continue
        try:
            values.append(int(item, 16))
        except ValueError:
            raise CheckError(f"invalid hex value {item!r} in {what}")
    return values


def parse_live(spec: str) -> list[tuple[int, int, int]]:
    entries: list[tuple[int, int, int]] = []
    for item in spec.split(";"):
        item = item.strip()
        if not item:
            continue
        parts = [part.strip() for part in item.split(":")]
        if len(parts) != 3:
            raise CheckError(
                f"invalid live entry {item!r} (expected status:id:roomSlot)"
            )
        status_s, id_s, slot_s = parts
        try:
            status = int(status_s, 16)
            sprite_id = int(id_s, 16)
            slot = int(slot_s, 16) if slot_s.lower().startswith("0x") else int(slot_s, 10)
        except ValueError:
            raise CheckError(f"invalid live entry {item!r}")
        entries.append((status, sprite_id, slot))
    return entries


def check_iwram(
    symbols: dict[str, int],
    expect_table: list[int],
    expect_gfx: list[int],
    expect_live: list[tuple[int, int, int]],
) -> None:
    path = Path(f"{DUMP_PREFIX}_iwram.bin")
    if not path.exists():
        raise CheckError(f"harness wrote no IWRAM dump at {path}")
    data = path.read_bytes()
    if len(data) != IWRAM_BYTES:
        raise CheckError(
            f"{path} is {len(data)} bytes, expected 0x{IWRAM_BYTES:X}"
        )
    print(f"IWRAM: {path} sha256={hashlib.sha256(data).hexdigest()}")

    def addr_of(name: str) -> int:
        return symbols[name] - IWRAM_BASE

    sprite_base = addr_of("gSpriteData")
    ids_base = addr_of("gSpritesetSpriteIds")
    gfx_base = addr_of("gSpritesetSpriteGfxSlots")

    stride = (ids_base - sprite_base) // SPRITE_COUNT
    if (ids_base - sprite_base) % SPRITE_COUNT != 0:
        raise CheckError(
            f"gSpritesetSpriteIds - gSpriteData = 0x{ids_base - sprite_base:X} "
            f"is not divisible by {SPRITE_COUNT}"
        )
    if stride != EXPECTED_STRIDE:
        raise CheckError(
            f"struct SpriteData stride is 0x{stride:X}, expected "
            f"0x{EXPECTED_STRIDE:X}"
        )

    if ids_base + len(expect_table) > len(data):
        raise CheckError("expected spriteset table runs past the IWRAM dump")
    table = list(data[ids_base : ids_base + len(expect_table)])
    if table != expect_table:
        raise CheckError(
            "gSpritesetSpriteIds[0..%d] = %s, expected %s"
            % (
                len(expect_table) - 1,
                " ".join(f"0x{value:02X}" for value in table),
                " ".join(f"0x{value:02X}" for value in expect_table),
            )
        )

    if gfx_base + len(expect_gfx) > len(data):
        raise CheckError("expected gfx-slot table runs past the IWRAM dump")
    gfx = list(data[gfx_base : gfx_base + len(expect_gfx)])
    if gfx != expect_gfx:
        raise CheckError(
            f"gSpritesetSpriteGfxSlots[0..{len(expect_gfx) - 1}] = {gfx}, "
            f"expected {expect_gfx}"
        )

    for index, (want_status, want_id, want_slot) in enumerate(expect_live):
        base = sprite_base + index * stride
        if base + OFFSET_ROOM_SLOT + 1 > len(data):
            raise CheckError(f"sprite entry {index} runs past the IWRAM dump")
        status = int.from_bytes(
            data[base + OFFSET_STATUS : base + OFFSET_STATUS + 2], "little"
        )
        sprite_id = data[base + OFFSET_SPRITE_ID]
        room_slot = data[base + OFFSET_ROOM_SLOT]
        got = (status, sprite_id, room_slot)
        want = (want_status, want_id, want_slot)
        if got != want:
            raise CheckError(
                f"sprite entry {index}: status=0x{status:04X} "
                f"id=0x{sprite_id:02X} roomSlot=0x{room_slot:02X}, expected "
                f"status=0x{want_status:04X} id=0x{want_id:02X} "
                f"roomSlot=0x{want_slot:02X}"
            )
        print(
            f"SPRITE[{index}]: status=0x{status:04X} id=0x{sprite_id:02X} "
            f"roomSlot=0x{room_slot:02X}"
        )


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rom", default=str(HACK_ROM))
    ap.add_argument("--elf", default=str(HACK_ELF))
    ap.add_argument("--harness", default=None)
    ap.add_argument("--timeout", type=int, default=INPUT_TIMEOUT)
    ap.add_argument(
        "--expect-table",
        default=DEFAULT_TABLE,
        help="internal: comma-separated hex sprite ids (default is the gate)",
    )
    ap.add_argument(
        "--expect-gfx",
        default=DEFAULT_GFX_SLOTS,
        help="internal: comma-separated hex/decimal gfx slots (default is the gate)",
    )
    ap.add_argument(
        "--expect-live",
        default=";".join(
            f"{status:04X}:{sprite_id:02X}:{slot}"
            for status, sprite_id, slot in DEFAULT_LIVE
        ),
        help="internal: status:id:roomSlot entries separated by ';'",
    )
    args = ap.parse_args()

    rom = Path(args.rom)
    elf = Path(args.elf)
    harness = args.harness or find_harness()
    if not harness:
        print(
            "SKIP: sprite-liveness check needs the headless harness "
            "(build tests/emulator/bin/mgba-harness or set MF_MGBA_HARNESS)"
        )
        return 77
    if not rom.exists():
        print(f"FAIL: missing hack ROM {rom}; run `make hack-build`")
        return 1
    if not elf.exists():
        print(f"FAIL: missing hack ELF {elf}; run `make hack-build`")
        return 1

    try:
        expect_table = parse_table(args.expect_table, "--expect-table")
        expect_gfx = parse_table(args.expect_gfx, "--expect-gfx")
        expect_live = parse_live(args.expect_live)
        if not expect_table:
            raise CheckError("--expect-table resolved to no entries")
        frames = build_prefix()
        print(f"PREFIX: {PREFIX_PATH} frames={frames}")
        output = run_harness(harness, rom, args.timeout)
        area, room = check_end_state(output)
        symbols = resolve_symbols(elf)
        print(
            "SYMBOLS: "
            + " ".join(
                f"{name}=0x{addr:08X}" for name, addr in symbols.items()
            )
        )
        check_iwram(symbols, expect_table, expect_gfx, expect_live)
    except CheckError as exc:
        print(f"FAIL: {exc}")
        return 1

    print(
        f"PASS: hack room sprites (area={EXPECTED_AREA} room={EXPECTED_ROOM}, "
        f"{len(expect_table)}-entry spriteset, {len(expect_live)} spawns)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
