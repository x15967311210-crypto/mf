#!/usr/bin/env python3
"""Validate the generated Sector Null blockout room directories.

This is the content-side acceptance check for HACK-004a1.  It expects the five
rooms to have been converted into ``hack/gen/rooms/<room>/`` first (see the
README), then verifies:

* the five output directories and their files exist;
* room IDs, dimensions and clipdata limits match the source manifests;
* every RLE plane decodes to the declared dimensions;
* every room has at least two doors and one spawn;
* the 0-11 door records are reciprocal and do not self-loop;
* the Entry Ledge save pad is present;
* scroll records are inside the room.

No ROM, emulator or engine source is read.
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

HACK_ROOT = Path(__file__).resolve().parents[2]
REPO_ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(REPO_ROOT / "tools" / "content"))

import tiled_to_room  # noqa: E402


ROOMS = (
    ("entry_ledge", 0, 15, 10),
    ("silent_atrium", 1, 15, 30),
    ("resonance_chamber", 2, 30, 10),
    ("hidden_conduit", 3, 45, 10),
    ("choir_nest", 4, 15, 20),
)

EXPECTED_DOORS = {
    0: 1, 1: 0,
    2: 3, 3: 2,
    4: 5, 5: 4,
    6: 7, 7: 6,
    8: 9, 9: 8,
    10: 11, 11: 10,
}

REQUIRED_FILES = (
    "room.json",
    "bg1.rle",
    "bg2.rle",
    "clipdata.rle",
    "scrolls.bin",
    "doors.bin",
    "spriteset_default.bin",
    "spriteset_first.bin",
    "spriteset_second.bin",
)


class CheckError(Exception):
    pass


def fail(message: str) -> None:
    raise CheckError(message)


def load_json(path: Path) -> dict:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except OSError as exc:
        fail(f"cannot read {path}: {exc}")
    except json.JSONDecodeError as exc:
        fail(f"{path}: invalid JSON: {exc}")


def check_rle(path: Path, width: int, height: int) -> None:
    data = path.read_bytes()
    try:
        decoded_width, decoded_height, values = tiled_to_room.decode_rle_u16(data)
    except tiled_to_room.ContentError as exc:
        fail(f"{path.name}: {exc}")
    if (decoded_width, decoded_height) != (width, height):
        fail(
            f"{path.name}: RLE header {decoded_width}x{decoded_height}, "
            f"expected {width}x{height}"
        )
    if len(values) != width * height:
        fail(f"{path.name}: decoded {len(values)} blocks, expected {width * height}")


def check_bounds(record: dict, width: int, height: int, label: str) -> None:
    for key, limit in (("x_start", width), ("x_end", width), ("y_start", height), ("y_end", height)):
        value = record.get(key)
        if not isinstance(value, int) or isinstance(value, bool) or not 0 <= value < limit:
            fail(f"{label}: {key}={value!r} is outside 0..{limit - 1}")
    if record["x_start"] > record["x_end"] or record["y_start"] > record["y_end"]:
        fail(f"{label}: inverted rectangle {record}")


def check_room(name: str, index: int, width: int, height: int) -> dict:
    out = HACK_ROOT / "gen" / "rooms" / name
    if not out.is_dir():
        fail(f"missing generated room directory {out}")
    missing = [filename for filename in REQUIRED_FILES if not (out / filename).is_file()]
    if missing:
        fail(f"{name}: missing output file(s): {', '.join(missing)}")

    room = load_json(out / "room.json")
    if room.get("schema") != "mf-hack.room/v1":
        fail(f"{name}: unexpected room.json schema {room.get('schema')!r}")
    room_info = room["room"]
    if room_info.get("area_name") != "AREA_TEST_1" or room_info.get("area") != 7:
        fail(f"{name}: not an AREA_TEST_1 room: {room_info}")
    if room_info.get("index") != index or room_info.get("name") != name:
        fail(f"{name}: room id mismatch: {room_info}")
    dimensions = room["dimensions"]
    if (dimensions["width_blocks"], dimensions["height_blocks"]) != (width, height):
        fail(f"{name}: dimensions {dimensions['width_blocks']}x{dimensions['height_blocks']}")
    blocks = width * height
    if blocks > tiled_to_room.MAX_CLIPDATA_BLOCKS:
        fail(f"{name}: {blocks} blocks exceed the clipdata limit")
    if not isinstance(room.get("warnings"), list):
        fail(f"{name}: warnings must be a list")

    for layer in ("bg1", "bg2", "clipdata"):
        filename = f"{layer}.rle"
        if not (out / filename).is_file():
            fail(f"{name}: missing {filename}")
    check_rle(out / "bg1.rle", width, height)
    check_rle(out / "bg2.rle", width, height)
    check_rle(out / "clipdata.rle", width, height)

    doors = room["doors"]
    if doors["count"] < 2:
        fail(f"{name}: needs at least two doors, has {doors['count']}")
    if len(doors["records"]) != doors["count"]:
        fail(f"{name}: door count/record mismatch")
    if (out / "doors.bin").stat().st_size != doors["count"] * 9:
        fail(f"{name}: doors.bin size does not match {doors['count']} 9-byte records")
    for record in doors["records"]:
        check_bounds(record, width, height, f"{name} door {record['id']}")
        if record["src_room"] != index:
            fail(f"{name} door {record['id']}: src_room={record['src_room']}, expected {index}")
        if record["dst_door"] not in EXPECTED_DOORS:
            fail(f"{name} door {record['id']}: dst_door={record['dst_door']} is not 0..11")
        if (record["x_end"] - record["x_start"] + 1) not in (1, 2):
            fail(f"{name} door {record['id']}: unexpected width")
        if (record["y_end"] - record["y_start"] + 1) not in (1, 2):
            fail(f"{name} door {record['id']}: unexpected height")

    spawns = room["spritesets"]
    default = spawns["default"]
    if default["count"] < 1:
        fail(f"{name}: needs at least one spawn")
    default_bytes = (out / "spriteset_default.bin").read_bytes()
    if len(default_bytes) != default["count"] * 3 + 3:
        fail(f"{name}: spriteset_default.bin has the wrong length")
    if default_bytes[-3:] != b"\xff\xff\xff":
        fail(f"{name}: spriteset_default.bin is not terminated")
    for set_name in ("first", "second"):
        if (out / f"spriteset_{set_name}.bin").read_bytes() != b"\xff\xff\xff":
            fail(f"{name}: spriteset_{set_name}.bin should be empty")
    table = {int(slot): sprite for slot, sprite in default["table"].items()}
    for record in default["records"]:
        if table.get(record["slot"]) != record["sprite_id"]:
            fail(f"{name}: spawn {record['name']} does not round-trip through its table")

    scrolls = room["scrolls"]["records"]
    if not 1 <= len(scrolls) <= 2:
        fail(f"{name}: expected 1 or 2 scroll records")
    if (out / "scrolls.bin").stat().st_size != 2 + 8 * len(scrolls):
        fail(f"{name}: scrolls.bin has the wrong length")
    for i, scroll in enumerate(scrolls):
        if not 0 <= scroll["x_start"] <= scroll["x_end"] < width:
            fail(f"{name}: scroll {i} x bounds are invalid")
        if not 0 <= scroll["y_start"] <= scroll["y_end"] < height:
            fail(f"{name}: scroll {i} y bounds are invalid")

    return room


def main() -> int:
    try:
        rooms: dict[str, dict] = {}
        all_doors: dict[int, tuple[str, dict]] = {}
        for name, index, width, height in ROOMS:
            room = check_room(name, index, width, height)
            rooms[name] = room
            for record in room["doors"]["records"]:
                door_index = record["id"] - 1
                if door_index in all_doors:
                    fail(f"duplicate global door index {door_index}")
                all_doors[door_index] = (name, record)

        if set(all_doors) != set(EXPECTED_DOORS):
            fail(f"door indices {sorted(all_doors)} != {sorted(EXPECTED_DOORS)}")
        for door_index, expected_dst in EXPECTED_DOORS.items():
            name, record = all_doors[door_index]
            if record["dst_door"] != expected_dst:
                fail(
                    f"door {door_index} in {name}: dst_door={record['dst_door']}, "
                    f"expected {expected_dst}"
                )
            if expected_dst not in all_doors:
                fail(f"door {door_index}: destination {expected_dst} is not in the set")
            if all_doors[expected_dst][1]["dst_door"] != door_index:
                fail(f"door {door_index} <-> {expected_dst} is not reciprocal")

        entry_spawns = rooms["entry_ledge"]["spritesets"]["default"]["records"]
        if not any(record["sprite_id"] == 31 for record in entry_spawns):
            fail("entry_ledge: missing save pad (PSPRITE_SAVE_PAD, id 31)")

        print("BLOCKOUT: PASS")
        for name, index, width, height in ROOMS:
            room = rooms[name]
            print(
                f"  {index} {name}: {width}x{height} ({width * height} blocks), "
                f"{room['doors']['count']} doors, "
                f"{room['spritesets']['default']['count']} spawns, "
                f"{len(room['scrolls']['records'])} scroll(s)"
            )
        total_doors = sum(room["doors"]["count"] for room in rooms.values())
        total_spawns = sum(room["spritesets"]["default"]["count"] for room in rooms.values())
        print(f"  12/12 reciprocal doors, {total_doors} records, {total_spawns} spawns")
        return 0
    except CheckError as exc:
        print(f"BLOCKOUT: FAIL: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
