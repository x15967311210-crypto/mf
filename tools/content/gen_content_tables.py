#!/usr/bin/env python3
"""Generate the HACK=1 AREA_TEST_1 room/door tables from room output.

HACK-008c2 is the first golden-path table: one room (Entry Ledge, room 0) is
converted by ``tools/content/tiled_to_room.py`` into ``hack/gen/rooms/...`` and
this tool turns that deterministic output into ``hack/gen/content_tables.h``.
``src/room.c`` includes the header through ``hack/include/hack/content_tables.h``
under ``#ifdef HACK``, so the baseline tables in ``src/data`` are never touched.

The generated headers contain:

* in ``content_tables.h``: ``static const u8`` blobs for bg1/bg2/clipdata and
  the default spriteset; an empty bg0 blob (no bg0 layer yet) and the vanilla
  ``sBg3_TestRoom`` LZ77 blue-grid backdrop with ``bg3Scrolling = 1`` (the
  engine always LZ77-decompresses ``pBg3Data + 4``); ``HackTest1Doors`` -- a
  one-entry ``DOOR_TYPE_NONE`` terminator for 008c2 because the authored Entry
  Ledge doors target rooms outside this one-room table, replaced by the real
  pair in HACK-008d; ``HackTest1RoomEntries`` with one ``RoomEntryRom`` at
  index 0;
* in the sibling ``scroll_tables.h``: HACK-008d1's one
  ``HackTest1Room<N>Scrolls[SCROLL_DATA_SIZE(n)]`` per room (byte-exact with
  the converter's ``scrolls.bin``), the generated ``HackAreaScrollEnd``
  terminator, the ``HackTest1ScrollPointers`` scan list and the
  ``HACK_AREA_TEST_1_SCROLLS`` macro that ``src/scroll.c`` selects.

The split matters: ``src/room.c`` includes only ``content_tables.h`` and
``src/scroll.c`` includes only ``scroll_tables.h``, so every generated object is
defined in exactly one translation unit.  A single shared header would emit
duplicate ``static const`` copies in both objects.

The generator validates the converter output instead of trusting it:

* every declared file exists and its size matches the recorded byte count;
* RLE streams are mode 1, have the room's dimensions and consume every byte;
* door records match ``room.json``, stay inside the room and point at emitted
  doors when active doors are requested;
* spriteset records match their ``.bin`` payload, including the FF FF FF
  terminator;
* the scroll block is ``2 + 8*n`` bytes, its first byte is the room index, and
  every record matches the converter manifest's ``camera.scrolls`` values
  copied into ``room.json`` (bounds, breakable block, extended bound);
* room indices are contiguous from 0 and every emitted C constant exists in a
  project header.

Usage::

    python3 tools/content/gen_content_tables.py --write
    python3 tools/content/gen_content_tables.py --check
    python3 tools/content/gen_content_tables.py --self-check

``--write``/``--check`` default to ``hack/gen/rooms/entry_ledge`` and
``hack/gen/content_tables.h``; the scroll-only sibling
``hack/gen/scroll_tables.h`` is always derived from ``--out``.  ``--room-dir``
may be repeated; the default door mode suppresses active doors.
``--active-doors`` is the HACK-008d path and is exercised by ``--self-check``
only.

The tool is standard-library Python only, deterministic and free of timestamps,
absolute paths and hardcoded ROM addresses.
"""

from __future__ import annotations

import argparse
import json
import re
import shutil
import struct
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable, Iterable, Sequence

# The blockout tileset is read through the sibling standard-library PNG reader.
_CONTENT_DIR = str(Path(__file__).resolve().parent)
if _CONTENT_DIR not in sys.path:
    sys.path.insert(0, _CONTENT_DIR)

import pngio


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_ROOM_DIRS = ("hack/gen/rooms/entry_ledge",)
DEFAULT_OUT = "hack/gen/content_tables.h"

ROOM_SCHEMA = "mf-hack.room/v1"
AREA_TEST_1 = 7
AREA_TEST_1_NAME = "AREA_TEST_1"
PIXEL_PER_BLOCK = 16

# BUG-021: the hack-owned blockout tileset.  The source is a 64x64 indexed PNG
# (4x4 grid of 16x16 blocks, 16 colours, index 0 transparent) authored by
# hack/content/tiled/make_blockout_tileset.py.  The generator packs block B from
# PNG block B into 4bpp 8x8 tiles in the order RoomSetInitialTilemap writes them
# (dst[0], dst[1], dst[32], dst[33] = TL, TR, BL, BR).
TILESET_SOURCE = "hack/content/tiled/blockout_tileset.png"
TILESET_IMAGE_SIZE = 64
TILESET_BLOCK_SIZE = 16
TILESET_TILE_SIZE = 8
TILESET_BLOCK_COUNT = 16
TILESET_TILES_PER_BLOCK = 4
TILESET_GFX_BYTES = TILESET_BLOCK_COUNT * TILESET_TILES_PER_BLOCK * 32
TILESET_PALETTE_ROW_SIZE = 16
TILESET_PALETTE_ROWS = 14
# RoomLoadTileset DMA-copies the 14-row tileset palette to global PALRAM row 2,
# so pPalette row 2 lands in global row 4.  The HUD/fade path clears global
# rows 1..3 before the first playable frame but leaves rows 4..15 alone, so the
# authored 16 colours live in pPalette row 2 and the tilemap selects bank 4.
TILESET_PALETTE_ROW = 2
TILESET_PALETTE_BANK = 4
TILESET_TILEMAP_HEADER = 0x0002
TILESET_TILE_BASE = 0xC0
LZ77_LITERAL_HEADER = 0x10
LZ77_EMPTY_STREAM = b"\x10\x00\x00\x00"
DOOR_RECORD_SIZE = 9
SPRITESET_TERMINATOR = b"\xff\xff\xff"
SPRITESET_RECORD_SIZE = 3
# struct Scroll packs four u8 bounds plus four u8 breakable/extended fields.
SCROLL_SUB_DATA_COUNT = 8
SCROLL_TERMINATOR = b"\xff"

# C constants this generator may emit.  A numeric value that is not in one of
# these tables is an "unknown constant" and fails rather than being written as
# a bare number (D-009: content must use named IDs/constants).
BG_PROP_SYMBOLS = {
    0x00: "BG_PROP_NONE",
    0x10: "BG_PROP_RLE_COMPRESSED",
    0x11: "BG_PROP_11",
    0x12: "BG_PROP_DISABLE_TRANSPARENCY",
    0x13: "BG_PROP_13",
    0x14: "BG_PROP_14",
    0x40: "BG_PROP_LZ77_COMPRESSED",
    0x41: "BG_PROP_NIGHTMARE_ROOM",
    0x43: "BG_PROP_DARK_ROOM",
    0x44: "BG_PROP_SA_X_ROOM",
    0x45: "BG_PROP_DIM_ROOM",
    0x46: "BG_PROP_WATER_DRAIN_ROOM",
    0x47: "BG_PROP_FOG",
    0x48: "BG_PROP_MELTDOWN",
    0x49: "BG_PROP_NIGHTMARE_SHADOW",
    0x4A: "BG_PROP_SR388",
}

EFFECT_SYMBOLS = {
    0: "EFFECT_NONE",
    1: "EFFECT_WATER",
    2: "EFFECT_LAVA",
    3: "EFFECT_LAVA_HEAT_HAZE",
    4: "EFFECT_ACID",
    5: "EFFECT_SNOWFLAKES_COLD_KNOCKBACK",
    6: "EFFECT_SNOWFLAKES_COLD",
    7: "EFFECT_HEAT_BG3_HAZE",
    8: "EFFECT_HEAT_BG2_BG3_HAZE",
    9: "EFFECT_BG3_GRADIENT",
    10: "EFFECT_BG2_GRADIENT",
    11: "EFFECT_HAZE_BG1_BG2_BG3",
}

MUSIC_SYMBOLS = {
    0: "MUSIC_NONE",
}

# enum DoorType (include/constants/connection.h).
DOOR_LOW_SYMBOLS = {
    0x1: "DOOR_TYPE_AREA_CONNECTION",
    0x2: "DOOR_TYPE_NO_HATCH",
    0x3: "DOOR_TYPE_OPEN_HATCH",
    0x4: "DOOR_TYPE_HATCH_CAN_LOCK",
    0xF: "DOOR_TYPE_NO_FLAGS",
}
DOOR_HIGH_SYMBOLS = {
    0x10: "DOOR_TYPE_NORMAL",
    0x20: "DOOR_TYPE_LOAD_EVENT_BASED_ROOM",
    0x40: "DOOR_TYPE_DISPLAY_LOCATION_NAME",
}

HEADER_GUARD = "HACK_GEN_CONTENT_TABLES_H"
SCROLL_HEADER_GUARD = "HACK_GEN_SCROLL_TABLES_H"
SCROLL_HEADER_NAME = "scroll_tables.h"
SPRITE_HEADER_GUARD = "HACK_GEN_SPRITE_TABLES_H"
SPRITE_HEADER_NAME = "sprite_tables.h"
# HACK-008d3: gSpritesetSpriteGfxSlots masks the table slot with 7 and the
# spriteset graphics loader uses gfxSlot * 2048 bytes, so only slots 0..7
# exist.  Sprite ID 0x00 is PSPRITE_TARGET_CIRCLES, the table terminator.
SPRITESET_GFX_SLOT_MAX = 7
SPRITE_ID_MAX = 0xCF  # SPRITE_ECHO_HUNTER (hack/include/hack/ids.h)
SPRITE_ID_TERMINATOR = 0x00
ARRAY_BYTES_PER_LINE = 12


class ContentError(Exception):
    """A user-facing content table validation error."""


# ---------------------------------------------------------------------------
# Small JSON/validation helpers


def _reject_duplicate_keys(pairs: list[tuple[str, Any]]) -> dict[str, Any]:
    result: dict[str, Any] = {}
    for key, value in pairs:
        if key in result:
            raise ContentError(f"duplicate JSON key {key!r}")
        result[key] = value
    return result


def load_json(path: Path, label: str) -> Any:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise ContentError(f"cannot read {label} {display_path(path)}: {exc}") from exc
    try:
        return json.loads(text, object_pairs_hook=_reject_duplicate_keys)
    except ContentError:
        raise
    except json.JSONDecodeError as exc:
        raise ContentError(
            f"{label} {display_path(path)}: invalid JSON: {exc}"
        ) from exc


def expect_object(value: Any, path: str) -> dict[str, Any]:
    if not isinstance(value, dict):
        raise ContentError(f"{path}: expected a JSON object")
    return value


def require_keys(obj: dict[str, Any], keys: Iterable[str], path: str) -> None:
    missing = sorted(set(keys) - set(obj))
    if missing:
        raise ContentError(f"{path}: missing required key(s): {', '.join(missing)}")


def as_int(value: Any, path: str, minimum: int, maximum: int) -> int:
    if isinstance(value, bool) or not isinstance(value, int):
        raise ContentError(f"{path}: expected an integer in {minimum}..{maximum}")
    if not minimum <= value <= maximum:
        raise ContentError(
            f"{path}: {value} is outside the allowed range {minimum}..{maximum}"
        )
    return value


def as_relative_file(value: Any, path: str) -> str:
    if not isinstance(value, str) or not value:
        raise ContentError(f"{path}: expected a file name")
    candidate = Path(value)
    if candidate.is_absolute() or len(candidate.parts) != 1 or candidate.name != value:
        raise ContentError(f"{path}: expected a bare file name, got {value!r}")
    return value


def display_path(path: Path) -> str:
    """Return a repo-relative path; never leak an absolute path into output."""

    try:
        return path.resolve().relative_to(REPO_ROOT).as_posix()
    except (OSError, ValueError):
        return path.name


def read_blob(
    directory: Path,
    filename: str,
    expected_bytes: int | None,
    label: str,
) -> bytes:
    path = directory / filename
    try:
        data = path.read_bytes()
    except FileNotFoundError as exc:
        raise ContentError(f"{label}: missing file {display_path(path)}") from exc
    except OSError as exc:
        raise ContentError(f"{label}: cannot read {display_path(path)}: {exc}") from exc
    if expected_bytes is not None and len(data) != expected_bytes:
        raise ContentError(
            f"{label}: bad counter for {display_path(path)}: "
            f"room.json records {expected_bytes} bytes, file has {len(data)}"
        )
    return data


# ---------------------------------------------------------------------------
# RLE validation (mirror of the mode-1 encoder used by tiled_to_room.py)


def validate_rle(data: bytes, width: int, height: int, label: str) -> None:
    if len(data) < 2:
        raise ContentError(f"{label}: truncated RLE stream")
    if data[0] != width or data[1] != height:
        raise ContentError(
            f"{label}: RLE dimensions {data[0]}x{data[1]} do not match the "
            f"room {width}x{height}"
        )

    count = width * height
    pos = 2
    for plane in range(2):
        if pos >= len(data):
            raise ContentError(f"{label}: truncated RLE plane {plane}")
        mode = data[pos]
        pos += 1
        if mode != 1:
            raise ContentError(
                f"{label}: RLE plane {plane} uses mode 0x{mode:02X}; the "
                "content pipeline emits 8-bit mode 1 only"
            )
        written = 0
        while True:
            if pos >= len(data):
                raise ContentError(f"{label}: truncated RLE run count")
            run = data[pos]
            pos += 1
            if run == 0:
                break
            if run & 0x80:
                run &= 0x7F
                if run == 0 or pos >= len(data):
                    raise ContentError(f"{label}: truncated RLE repeat run")
                pos += 1
            else:
                if run == 0 or pos + run > len(data):
                    raise ContentError(f"{label}: truncated RLE literal run")
                pos += run
            written += run
            if written > count:
                raise ContentError(
                    f"{label}: RLE plane {plane} writes more than {count} blocks"
                )
        if written != count:
            raise ContentError(
                f"{label}: RLE plane {plane} decodes to {written} blocks, "
                f"expected {count}"
            )
    if pos != len(data):
        raise ContentError(f"{label}: {len(data) - pos} trailing byte(s)")


# ---------------------------------------------------------------------------
# Room output model


@dataclass(frozen=True)
class DoorRecord:
    index: int  # global door index: Tiled object id - 1
    type: int
    src_room: int
    x_start: int
    x_end: int
    y_start: int
    y_end: int
    dst_door: int
    x_exit: int
    y_exit: int


@dataclass
class RoomData:
    directory: Path
    directory_label: str
    name: str
    index: int
    width: int
    height: int
    tileset: int
    entry: dict[str, int]
    layers: dict[str, bytes] = field(default_factory=dict)
    doors: list[DoorRecord] = field(default_factory=list)
    spritesets: dict[str, bytes] = field(default_factory=dict)
    spriteset_tables: dict[str, dict[int, int]] = field(default_factory=dict)
    scrolls: bytes = b""


def _int_field(
    obj: dict[str, Any], key: str, path: str, minimum: int, maximum: int
) -> int:
    if key not in obj:
        raise ContentError(f"{path}: missing required key {key!r}")
    return as_int(obj[key], f"{path}.{key}", minimum, maximum)


def _load_layers(
    directory: Path, doc: dict[str, Any], width: int, height: int
) -> dict[str, bytes]:
    raw_layers = expect_object(doc.get("layers"), "$.layers")
    outputs = expect_object(doc.get("outputs"), "$.outputs")
    result: dict[str, bytes] = {}
    for role in ("bg0", "bg1", "bg2", "clip"):
        if role not in raw_layers:
            continue
        info = expect_object(raw_layers[role], f"$.layers.{role}")
        require_keys(info, ("rle_file",), f"$.layers.{role}")
        filename = as_relative_file(info["rle_file"], f"$.layers.{role}.rle_file")
        recorded = as_int(
            info.get("rle_bytes", -1), f"$.layers.{role}.rle_bytes", 0, 0x7FFFFFFF
        )
        if info.get("width") != width or info.get("height") != height:
            raise ContentError(
                f"$.layers.{role}: dimensions {info.get('width')}x"
                f"{info.get('height')} do not match the room {width}x{height}"
            )
        output_key = "clipdata" if role == "clip" else role
        out_info = expect_object(
            outputs.get(output_key), f"$.outputs.{output_key}"
        )
        out_file = as_relative_file(
            out_info.get("file"), f"$.outputs.{output_key}.file"
        )
        if out_file != filename:
            raise ContentError(
                f"$.layers.{role}: rle_file {filename!r} does not match "
                f"$.outputs.{output_key}.file {out_file!r}"
            )
        out_bytes = as_int(
            out_info.get("bytes", -1),
            f"$.outputs.{output_key}.bytes",
            0,
            0x7FFFFFFF,
        )
        if out_bytes != recorded:
            raise ContentError(
                f"$.layers.{role}: rle_bytes {recorded} does not match "
                f"$.outputs.{output_key}.bytes {out_bytes}"
            )
        data = read_blob(directory, filename, recorded, f"$.layers.{role}")
        validate_rle(data, width, height, f"$.layers.{role}")
        result[role] = data
    return result


def _load_spriteset_table(
    info: dict[str, Any] | None, name: str
) -> dict[int, int]:
    """Parse one ``spritesets.<name>.table`` slot -> sprite-ID map.

    HACK-008d3 emits the default table as ``(spriteId, gfxSlot)`` pairs for
    ``SpriteLoadSpriteset``; the engine indexes ``gSpritesetSpriteIds`` by pair
    order, so the slots must be contiguous from 0.  Only graphics slots 0..7
    exist in the sprite graphics loader.
    """

    if info is None:
        return {}
    raw = expect_object(info.get("table", {}), f"$.spritesets.{name}.table")
    table: dict[int, int] = {}
    for key, value in raw.items():
        path = f"$.spritesets.{name}.table[{key!r}]"
        try:
            slot = int(key, 0)
        except (TypeError, ValueError):
            raise ContentError(f"{path}: slot key is not an integer") from None
        if not 0 <= slot <= SPRITESET_GFX_SLOT_MAX:
            raise ContentError(
                f"{path}: gfx slot {slot} is outside 0..{SPRITESET_GFX_SLOT_MAX} "
                "(SpriteLoadSpriteset addresses eight 2048-byte gfx slots)"
            )
        if slot in table:
            raise ContentError(f"{path}: duplicate gfx slot {slot}")
        sprite_id = as_int(value, path, 1, SPRITE_ID_MAX)
        table[slot] = sprite_id
    ordered = sorted(table)
    if ordered != list(range(len(ordered))):
        raise ContentError(
            f"$.spritesets.{name}.table: gfx slots must be contiguous from 0 "
            f"because the engine reads the pairs in order; got {ordered}"
        )
    return {slot: table[slot] for slot in ordered}


def _load_spritesets(
    directory: Path, doc: dict[str, Any], width: int, height: int
) -> tuple[dict[str, bytes], dict[str, dict[int, int]]]:
    outputs = expect_object(doc.get("outputs"), "$.outputs")
    raw = doc.get("spritesets", {})
    raw = expect_object(raw, "$.spritesets")
    result: dict[str, bytes] = {}
    tables: dict[str, dict[int, int]] = {}
    for name in ("default", "first", "second"):
        info = raw.get(name)
        out_info = outputs.get(f"spriteset_{name}")
        if info is None and out_info is None:
            if name == "default":
                raise ContentError(
                    "$.spritesets.default: the default spriteset is required"
                )
            # The converter normally writes an empty FF FF FF set.  Accept a
            # missing empty set and synthesize the same terminator.
            result[name] = SPRITESET_TERMINATOR
            tables[name] = {}
            continue
        if info is not None:
            info = expect_object(info, f"$.spritesets.{name}")
        tables[name] = _load_spriteset_table(info, name)
        out_info = (
            expect_object(out_info, f"$.outputs.spriteset_{name}")
            if out_info is not None
            else None
        )
        filename = (
            (info or {}).get("file")
            or (out_info or {}).get("file")
            or f"spriteset_{name}.bin"
        )
        filename = as_relative_file(filename, f"$.spritesets.{name}.file")
        recorded = None
        if info is not None and "bytes" in info:
            recorded = as_int(
                info["bytes"], f"$.spritesets.{name}.bytes", 0, 0x7FFFFFFF
            )
        if out_info is not None and "bytes" in out_info:
            out_bytes = as_int(
                out_info["bytes"], f"$.outputs.spriteset_{name}.bytes", 0, 0x7FFFFFFF
            )
            if recorded is not None and out_bytes != recorded:
                raise ContentError(
                    f"$.spritesets.{name}: bytes {recorded} does not match "
                    f"$.outputs.spriteset_{name}.bytes {out_bytes}"
                )
            recorded = out_bytes
        data = read_blob(
            directory, filename, recorded, f"$.spritesets.{name}"
        )
        if len(data) < len(SPRITESET_TERMINATOR) or not data.endswith(
            SPRITESET_TERMINATOR
        ):
            raise ContentError(
                f"$.spritesets.{name}: {filename} does not end with the "
                "FF FF FF terminator"
            )
        if (len(data) - len(SPRITESET_TERMINATOR)) % SPRITESET_RECORD_SIZE:
            raise ContentError(
                f"$.spritesets.{name}: {filename} is not whole sprite records "
                "plus the terminator"
            )
        count = (len(data) - len(SPRITESET_TERMINATOR)) // SPRITESET_RECORD_SIZE
        for source, label in ((info, f"$.spritesets.{name}"), (out_info, None)):
            if source is None:
                continue
            if "count" in source:
                recorded_count = as_int(
                    source["count"], f"{label}.count", 0, 0x7FFFFFFF
                )
                if recorded_count != count:
                    raise ContentError(
                        f"{label}: bad counter: room.json records "
                        f"{recorded_count} sprite(s), file has {count}"
                    )
        records = info.get("records", []) if info is not None else []
        if not isinstance(records, list):
            raise ContentError(f"$.spritesets.{name}.records: expected a list")
        if len(records) != count:
            raise ContentError(
                f"$.spritesets.{name}: bad counter: room.json records "
                f"{len(records)} sprite record(s), file has {count}"
            )
        for i, record in enumerate(records):
            record = expect_object(record, f"$.spritesets.{name}.records[{i}]")
            y, x, byte = data[
                i * SPRITESET_RECORD_SIZE : (i + 1) * SPRITESET_RECORD_SIZE
            ]
            for key, actual in (("x", x), ("y", y), ("record_byte", byte)):
                if record.get(key) != actual:
                    raise ContentError(
                        f"$.spritesets.{name}.records[{i}].{key}: room.json "
                        f"records {record.get(key)!r}, {filename} has {actual}"
                    )
            as_int(x, f"$.spritesets.{name}.records[{i}].x", 0, width - 1)
            as_int(y, f"$.spritesets.{name}.records[{i}].y", 0, height - 1)
            # A table-indexed record resolves through gSpritesetSpriteIds, so
            # the emitted table and the record must agree.  Direct records
            # (no table-index property bits) carry their sprite ID in byte 2.
            if byte & 0x70:
                path = f"$.spritesets.{name}.records[{i}]"
                slot = as_int(record.get("slot"), f"{path}.slot", 0, 0x7F)
                sprite_id = as_int(
                    record.get("sprite_id"), f"{path}.sprite_id", 1, SPRITE_ID_MAX
                )
                if slot not in tables[name]:
                    raise ContentError(
                        f"{path}.slot: slot {slot} is not declared in "
                        f"$.spritesets.{name}.table"
                    )
                if tables[name][slot] != sprite_id:
                    raise ContentError(
                        f"{path}.sprite_id: {sprite_id} does not match "
                        f"$.spritesets.{name}.table slot {slot} "
                        f"({tables[name][slot]})"
                    )
        result[name] = data
    return result, tables


def _load_doors(
    directory: Path, doc: dict[str, Any], width: int, height: int, room_index: int
) -> list[DoorRecord]:
    info = expect_object(doc.get("doors"), "$.doors")
    outputs = expect_object(doc.get("outputs"), "$.outputs")
    out_info = expect_object(outputs.get("doors"), "$.outputs.doors")
    filename = as_relative_file(info.get("file", "doors.bin"), "$.doors.file")
    out_file = as_relative_file(out_info.get("file"), "$.outputs.doors.file")
    if out_file != filename:
        raise ContentError(
            f"$.doors.file: {filename!r} does not match "
            f"$.outputs.doors.file {out_file!r}"
        )
    recorded = as_int(
        out_info.get("bytes", info.get("bytes")),
        "$.outputs.doors.bytes",
        0,
        0x7FFFFFFF,
    )
    if "bytes" in info and info["bytes"] != recorded:
        raise ContentError(
            f"$.doors.bytes: {info['bytes']} does not match "
            f"$.outputs.doors.bytes {recorded}"
        )
    data = read_blob(directory, filename, recorded, "$.doors")
    if len(data) % DOOR_RECORD_SIZE:
        raise ContentError(
            f"$.doors: {filename} is {len(data)} bytes; door records are "
            f"{DOOR_RECORD_SIZE} bytes"
        )
    count = len(data) // DOOR_RECORD_SIZE
    for source, label in ((info, "$.doors"), (out_info, "$.outputs.doors")):
        if "count" in source:
            recorded_count = as_int(source["count"], f"{label}.count", 0, 255)
            if recorded_count != count:
                raise ContentError(
                    f"{label}: bad counter: room.json records "
                    f"{recorded_count} door(s), file has {count}"
                )
    records = info.get("records", [])
    if not isinstance(records, list):
        raise ContentError("$.doors.records: expected a list")
    if len(records) != count:
        raise ContentError(
            f"$.doors: bad counter: room.json records {len(records)} "
            f"door record(s), file has {count}"
        )

    result: list[DoorRecord] = []
    for i, record in enumerate(records):
        path = f"$.doors.records[{i}]"
        record = expect_object(record, path)
        fields = struct.unpack_from("<BBBBBBBbb", data, i * DOOR_RECORD_SIZE)
        packed = {
            "type": fields[0],
            "src_room": fields[1],
            "x_start": fields[2],
            "x_end": fields[3],
            "y_start": fields[4],
            "y_end": fields[5],
            "dst_door": fields[6],
            "x_exit": fields[7],
            "y_exit": fields[8],
        }
        for key, actual in packed.items():
            if record.get(key) != actual:
                raise ContentError(
                    f"{path}.{key}: room.json records {record.get(key)!r}, "
                    f"{filename} has {actual}"
                )
        object_id = as_int(record.get("id"), f"{path}.id", 1, 255)
        if object_id - 1 < 0:
            raise ContentError(f"{path}.id: object id must be positive")
        if packed["src_room"] != room_index:
            raise ContentError(
                f"{path}.src_room: {packed['src_room']} is not the source "
                f"room {room_index}"
            )
        if packed["type"] == 0:
            raise ContentError(
                f"{path}.type: an active door cannot be DOOR_TYPE_NONE"
            )
        _door_type_symbols(packed["type"], f"{path}.type")
        as_int(packed["x_start"], f"{path}.x_start", 0, width - 1)
        as_int(packed["x_end"], f"{path}.x_end", 0, width - 1)
        as_int(packed["y_start"], f"{path}.y_start", 0, height - 1)
        as_int(packed["y_end"], f"{path}.y_end", 0, height - 1)
        if packed["x_start"] > packed["x_end"]:
            raise ContentError(f"{path}: x_start is greater than x_end")
        if packed["y_start"] > packed["y_end"]:
            raise ContentError(f"{path}: y_start is greater than y_end")
        result.append(
            DoorRecord(
                index=object_id - 1,
                type=packed["type"],
                src_room=packed["src_room"],
                x_start=packed["x_start"],
                x_end=packed["x_end"],
                y_start=packed["y_start"],
                y_end=packed["y_end"],
                dst_door=packed["dst_door"],
                x_exit=packed["x_exit"],
                y_exit=packed["y_exit"],
            )
        )
    return result


def _load_scrolls(
    directory: Path, doc: dict[str, Any], width: int, height: int, room_index: int
) -> bytes:
    info = expect_object(doc.get("scrolls"), "$.scrolls")
    outputs = expect_object(doc.get("outputs"), "$.outputs")
    out_info = expect_object(outputs.get("scrolls"), "$.outputs.scrolls")
    filename = as_relative_file(info.get("file", "scrolls.bin"), "$.scrolls.file")
    out_file = as_relative_file(out_info.get("file"), "$.outputs.scrolls.file")
    if out_file != filename:
        raise ContentError(
            f"$.scrolls.file: {filename!r} does not match "
            f"$.outputs.scrolls.file {out_file!r}"
        )
    recorded = as_int(
        out_info.get("bytes", info.get("bytes")),
        "$.outputs.scrolls.bytes",
        0,
        0x7FFFFFFF,
    )
    if "bytes" in info and info["bytes"] != recorded:
        raise ContentError(
            f"$.scrolls.bytes: {info['bytes']} does not match "
            f"$.outputs.scrolls.bytes {recorded}"
        )
    data = read_blob(directory, filename, recorded, "$.scrolls")
    if len(data) < 2:
        raise ContentError(f"$.scrolls: {filename} has no record header")
    if data[0] != room_index:
        raise ContentError(
            f"$.scrolls: room index {data[0]} does not match room {room_index}"
        )
    count = data[1]
    if not 1 <= count <= 2:
        raise ContentError(
            f"$.scrolls: {count} record(s); gCurrentScrolls has two slots"
        )
    if len(data) != 2 + SCROLL_SUB_DATA_COUNT * count:
        raise ContentError(
            f"$.scrolls: bad counter: {len(data)} bytes for {count} record(s)"
        )
    records = info.get("records", [])
    if not isinstance(records, list) or len(records) != count:
        raise ContentError(
            f"$.scrolls: bad counter: room.json records "
            f"{len(records) if isinstance(records, list) else '?'} scroll "
            f"record(s), {filename} has {count}"
        )
    for i, record in enumerate(records):
        path = f"$.scrolls.records[{i}]"
        record = expect_object(record, path)
        x_start = as_int(record.get("x_start"), f"{path}.x_start", 0, width - 1)
        x_end = as_int(record.get("x_end"), f"{path}.x_end", 0, width - 1)
        y_start = as_int(record.get("y_start"), f"{path}.y_start", 0, height - 1)
        y_end = as_int(record.get("y_end"), f"{path}.y_end", 0, height - 1)
        if x_start > x_end or y_start > y_end:
            raise ContentError(f"{path}: reversed scroll bounds")
        offset = 2 + i * SCROLL_SUB_DATA_COUNT
        packed = list(data[offset : offset + 8])
        expected = [
            x_start,
            x_end,
            y_start,
            y_end,
            record.get("breakable_x", 255),
            record.get("breakable_y", 255),
            record.get("extended_direction", 255),
            record.get("extended_value", 255),
        ]
        if packed != expected:
            raise ContentError(
                f"{path}: room.json camera.scrolls values do not match {filename}"
            )
    return data


def _load_room_entry(
    doc: dict[str, Any], room_index: int, tileset: int, width: int, height: int
) -> dict[str, int]:
    entry = expect_object(doc.get("room_entry"), "$.room_entry")
    required = (
        "tileset",
        "bg0_prop",
        "bg1_prop",
        "bg2_prop",
        "bg3_prop",
        "bg3_scrolling",
        "transparency",
        "effect",
        "effect_y",
        "music_track",
        "map_x",
        "map_y",
        "first_spriteset_event",
        "second_spriteset_event",
        "default_spriteset",
        "first_spriteset",
        "second_spriteset",
    )
    require_keys(entry, required, "$.room_entry")
    values = {
        key: _int_field(entry, key, "$.room_entry", 0, 0xFFFF)
        for key in required
    }
    values["tileset"] = _int_field(entry, "tileset", "$.room_entry", 0, 255)
    for key in (
        "bg0_prop",
        "bg1_prop",
        "bg2_prop",
        "bg3_prop",
        "bg3_scrolling",
        "transparency",
        "effect",
        "effect_y",
        "map_x",
        "map_y",
        "first_spriteset_event",
        "second_spriteset_event",
        "default_spriteset",
        "first_spriteset",
        "second_spriteset",
    ):
        values[key] = _int_field(entry, key, "$.room_entry", 0, 255)
    values["music_track"] = _int_field(
        entry, "music_track", "$.room_entry", 0, 0xFFFF
    )
    if values["tileset"] != tileset:
        raise ContentError(
            f"$.room_entry.tileset {values['tileset']} does not match "
            f"$.tileset.number {tileset}"
        )
    if values["first_spriteset_event"] != 0 or values["second_spriteset_event"] != 0:
        raise ContentError(
            "$.room_entry: first/second spriteset events are not emitted by "
            "HACK-008c2; keep them EVENT_NONE (0) until HACK-008d"
        )
    if values["effect"] not in EFFECT_SYMBOLS:
        raise ContentError(
            f"$.room_entry.effect: {values['effect']} has no known C constant"
        )
    if values["music_track"] not in MUSIC_SYMBOLS:
        raise ContentError(
            f"$.room_entry.music_track: {values['music_track']} has no known "
            "C constant (the golden path uses MUSIC_NONE)"
        )
    for key in ("bg0_prop", "bg1_prop", "bg2_prop", "bg3_prop"):
        if values[key] not in BG_PROP_SYMBOLS:
            raise ContentError(
                f"$.room_entry.{key}: {values[key]} has no known C constant"
            )
    # RoomLoadBackgrounds unconditionally LZ77-decompresses pBg3Data + 4, even
    # for BG_PROP_NONE; an "empty" blob therefore corrupts gDecompBg3Map.  The
    # golden path reuses the vanilla Test Area 1 blue-grid backdrop
    # (sBg3_TestRoom), whose property is BG_PROP_LZ77_COMPRESSED.
    if values["bg3_prop"] != 0x40:
        raise ContentError(
            "$.room_entry.bg3_prop: generated rooms require "
            "BG_PROP_LZ77_COMPRESSED because RoomLoadBackgrounds always "
            "LZ77-decompresses pBg3Data + 4"
        )
    if values["bg0_prop"] not in (0, 0x10):
        raise ContentError(
            "$.room_entry.bg0_prop: only BG_PROP_NONE or "
            "BG_PROP_RLE_COMPRESSED is supported"
        )
    return values


def load_room(directory: Path) -> RoomData:
    directory = Path(directory)
    label = display_path(directory)
    doc = load_json(directory / "room.json", "room.json")
    doc = expect_object(doc, "$")
    if doc.get("schema") != ROOM_SCHEMA:
        raise ContentError(
            f"$.schema: expected {ROOM_SCHEMA!r}, got {doc.get('schema')!r}"
        )
    room = expect_object(doc.get("room"), "$.room")
    name = room.get("name")
    if not isinstance(name, str) or not re.fullmatch(r"[A-Za-z0-9_.-]+", name):
        raise ContentError("$.room.name: expected a filename-safe name")
    index = as_int(room.get("index"), "$.room.index", 0, 255)
    if room.get("area_name") != AREA_TEST_1_NAME or room.get("area") != AREA_TEST_1:
        raise ContentError(
            "$.room.area: HACK-008c2 only builds AREA_TEST_1 (area 7) tables"
        )

    dimensions = expect_object(doc.get("dimensions"), "$.dimensions")
    width = as_int(
        dimensions.get("width_blocks"), "$.dimensions.width_blocks", 1, 255
    )
    height = as_int(
        dimensions.get("height_blocks"), "$.dimensions.height_blocks", 1, 255
    )
    if (
        dimensions.get("block_width") != PIXEL_PER_BLOCK
        or dimensions.get("block_height") != PIXEL_PER_BLOCK
    ):
        raise ContentError(
            "$.dimensions: engine blocks are 16x16 (PIXEL_PER_BLOCK)"
        )

    tileset_doc = expect_object(doc.get("tileset"), "$.tileset")
    tileset = as_int(tileset_doc.get("number"), "$.tileset.number", 0, 254)

    entry = _load_room_entry(doc, index, tileset, width, height)
    layers = _load_layers(directory, doc, width, height)
    spritesets, spriteset_tables = _load_spritesets(directory, doc, width, height)
    doors = _load_doors(directory, doc, width, height, index)
    scrolls = _load_scrolls(directory, doc, width, height, index)

    if "bg1" not in layers or "bg2" not in layers or "clip" not in layers:
        raise ContentError(
            "$.layers: bg1, bg2 and clip are required for an AREA_TEST_1 room"
        )
    if entry["bg1_prop"] != 0x10 or entry["bg2_prop"] != 0x10:
        raise ContentError(
            "$.room_entry: a generated bg1/bg2 layer requires "
            "BG_PROP_RLE_COMPRESSED"
        )
    if "bg0" in layers:
        if entry["bg0_prop"] != 0x10:
            raise ContentError(
                "$.room_entry.bg0_prop: a generated bg0 layer requires "
                "BG_PROP_RLE_COMPRESSED"
            )
    elif entry["bg0_prop"] != 0:
        raise ContentError(
            "$.room_entry.bg0_prop: no bg0 layer is present, so it must be "
            "BG_PROP_NONE"
        )

    return RoomData(
        directory=directory,
        directory_label=label,
        name=name,
        index=index,
        width=width,
        height=height,
        tileset=tileset,
        entry=entry,
        layers=layers,
        doors=doors,
        spritesets=spritesets,
        spriteset_tables=spriteset_tables,
        scrolls=scrolls,
    )


# ---------------------------------------------------------------------------
# Cross-room reference checks


def validate_room_set(rooms: Sequence[RoomData]) -> None:
    if not rooms:
        raise ContentError("no room directories were provided")
    names: set[str] = set()
    indices: dict[int, RoomData] = {}
    for room in rooms:
        if room.index in indices:
            raise ContentError(
                f"dangling room reference: room index {room.index} is used by "
                f"{indices[room.index].directory_label} and {room.directory_label}"
            )
        if room.name in names:
            raise ContentError(f"duplicate room name {room.name!r}")
        names.add(room.name)
        indices[room.index] = room
    expected = set(range(len(rooms)))
    missing = sorted(expected - set(indices))
    extra = sorted(set(indices) - expected)
    if missing or extra:
        raise ContentError(
            "room indices must be contiguous from 0: "
            f"missing {missing or 'none'}, unexpected {extra or 'none'}"
        )


def collect_active_doors(rooms: Sequence[RoomData]) -> list[DoorRecord]:
    by_index: dict[int, DoorRecord] = {}
    for room in rooms:
        for door in room.doors:
            if door.index in by_index:
                raise ContentError(
                    f"dangling door reference: global door index {door.index} "
                    f"appears twice ({by_index[door.index].src_room} and "
                    f"{door.src_room})"
                )
            if door.src_room not in {candidate.index for candidate in rooms}:
                raise ContentError(
                    f"dangling door reference: door {door.index} has src_room "
                    f"{door.src_room}, which is not in the emitted room table"
                )
            by_index[door.index] = door
    if not by_index:
        raise ContentError(
            "active door mode requires at least one source door; use the "
            "default (no active doors) for a room-only table"
        )
    expected = set(range(len(by_index)))
    missing = sorted(expected - set(by_index))
    extra = sorted(set(by_index) - expected)
    if missing or extra:
        raise ContentError(
            "dangling door reference: global door indices must be contiguous "
            f"from 0 (missing {missing or 'none'}, extra {extra or 'none'})"
        )
    table = [by_index[i] for i in range(len(by_index))]
    for door in table:
        if door.dst_door not in by_index:
            raise ContentError(
                f"dangling door reference: door {door.index} targets "
                f"dstDoor {door.dst_door}, outside 0..{len(table) - 1}"
            )
        if door.dst_door == door.index:
            raise ContentError(
                f"dangling door reference: door {door.index} is a self-loop"
            )
    return table


def _door_type_symbols(value: int, path: str) -> list[str]:
    if not 0 <= value <= 0xFF:
        raise ContentError(f"{path}: door type {value} is not a u8")
    low = value & 0x0F
    high = value & 0xF0
    if low not in DOOR_LOW_SYMBOLS:
        raise ContentError(f"{path}: door type 0x{value:02X} has no known low nibble")
    # Match the baseline src/data spelling: high flags first, low nibble last.
    symbols: list[str] = []
    for bit, symbol in DOOR_HIGH_SYMBOLS.items():
        if high & bit:
            symbols.append(symbol)
            high &= ~bit
    if high:
        raise ContentError(
            f"{path}: door type 0x{value:02X} has unknown high flags 0x{high:02X}"
        )
    symbols.append(DOOR_LOW_SYMBOLS[low])
    return symbols


# ---------------------------------------------------------------------------
# Header rendering


def _format_array(lines: list[str], name: str, data: bytes, comment: str) -> None:
    payload = data if data else b"\x00"
    lines.append(f"/* {comment} */")
    lines.append(f"static const u8 {name}[{len(payload)}] = {{")
    for offset in range(0, len(payload), ARRAY_BYTES_PER_LINE):
        chunk = payload[offset : offset + ARRAY_BYTES_PER_LINE]
        body = ", ".join(f"0x{value:02X}" for value in chunk)
        lines.append(f"    {body},")
    lines.append("};")
    lines.append("")


def _format_scroll_array(
    lines: list[str], name: str, data: bytes, count: int, comment: str
) -> None:
    if len(data) != 2 + SCROLL_SUB_DATA_COUNT * count:
        raise ContentError(
            f"internal error: {name} is {len(data)} bytes for {count} scroll(s)"
        )
    lines.append(f"/* {comment} */")
    lines.append(
        f"static const u8 {name}[SCROLL_DATA_SIZE({count})] = {{"
    )
    for offset in range(0, len(data), ARRAY_BYTES_PER_LINE):
        chunk = data[offset : offset + ARRAY_BYTES_PER_LINE]
        body = ", ".join(f"0x{value:02X}" for value in chunk)
        lines.append(f"    {body},")
    lines.append("};")
    lines.append("")


def _format_u32_array(lines: list[str], name: str, values: Sequence[int], comment: str) -> None:
    lines.append(f"/* {comment} */")
    lines.append(f"static const u32 {name}[{len(values)}] = {{")
    for value in values:
        lines.append(f"    0x{value:08X},")
    lines.append("};")
    lines.append("")


def _symbol_for(value: int, table: dict[int, str], path: str) -> str:
    if value not in table:
        raise ContentError(f"{path}: {value} has no known C constant")
    return table[value]


def render_header(rooms: Sequence[RoomData], active_doors: bool) -> str:
    rooms = sorted(rooms, key=lambda room: room.index)
    doors = collect_active_doors(rooms) if active_doors else []
    used_symbols: set[str] = set()

    lines: list[str] = []
    lines.append("/*")
    lines.append(" * hack/gen/content_tables.h -- generated AREA_TEST_1 overlay.")
    lines.append(" *")
    lines.append(" * Generated by tools/content/gen_content_tables.py.  DO NOT EDIT.")
    lines.append(" *")
    lines.append(" * HACK-008c2/HACK-008d1 golden-path tables:")
    for room in rooms:
        lines.append(
            f" *   room {room.index} {room.name!r}: {room.width}x{room.height} "
            f"blocks, tileset {room.tileset}, source {room.directory_label}"
        )
    lines.append(
        " *   HACK-008c2 room/door/spriteset tables only; scrolls live in the"
    )
    lines.append(" *   sibling generated scroll_tables.h (HACK-008d1).")
    if active_doors:
        lines.append(
            f" *   doors: {len(doors)} active record(s) + DOOR_TYPE_NONE terminator"
        )
    else:
        counts = sum(len(room.doors) for room in rooms)
        if counts:
            indices = sorted(door.index for room in rooms for door in room.doors)
            targets = sorted(door.dst_door for room in rooms for door in room.doors)
            lines.append(
                f" *   source doors.bin: {counts} record(s) at global index "
                f"{_join_ints(indices)} (dstDoor {_join_ints(targets)}); "
                "suppressed"
            )
            lines.append(
                " *   because this one-room table has no destination records."
            )
        else:
            lines.append(" *   source doors.bin: none")
        lines.append(
            " *   Doors are a single DOOR_TYPE_NONE terminator; HACK-008d adds "
            "the real pair."
        )
    lines.append(" *")
    lines.append(" * The generated file is ignored by Git; `make content-tables`")
    lines.append(" * (a prerequisite of `make hack-build` and `make content-check`)")
    lines.append(" * regenerates and checks it.")
    lines.append(" */")
    lines.append(f"#ifndef {HEADER_GUARD}")
    lines.append(f"#define {HEADER_GUARD}")
    lines.append("")
    lines.append('#include "types.h"')
    lines.append('#include "constants/audio.h"')
    lines.append('#include "constants/connection.h"')
    lines.append('#include "constants/event.h"')
    lines.append('#include "constants/room.h"')
    lines.append('#include "structs/connection.h"')
    lines.append('#include "structs/room.h"')
    lines.append('#include "structs/scroll.h"')
    lines.append("")
    if any(room.entry["bg3_prop"] == 0x40 for room in rooms):
        # Vanilla Test Area 1 blue-grid backdrop; declared in
        # include/data/rooms/test_rooms_data.h and defined in
        # src/data/rooms/test_rooms_data.c, so a non-static extern is safe.
        lines.append("extern const u32 sBg3_TestRoom[224];")
        lines.append("")

    # Payload arrays.
    for room in rooms:
        prefix = f"HackTest1Room{room.index}"
        bg0 = room.layers.get("bg0")
        _format_array(
            lines,
            f"{prefix}Bg0Empty",
            bg0 if bg0 is not None else b"",
            f"Room {room.index} bg0 "
            + ("RLE plane (wired by the generated room entry)." if bg0 else "is unused."),
        )
        _format_array(
            lines,
            f"{prefix}Bg1Data",
            room.layers["bg1"],
            f"Room {room.index} bg1 RLE plane.",
        )
        _format_array(
            lines,
            f"{prefix}Bg2Data",
            room.layers["bg2"],
            f"Room {room.index} bg2 RLE plane.",
        )
        _format_array(
            lines,
            f"{prefix}ClipData",
            room.layers["clip"],
            f"Room {room.index} clipdata RLE plane.",
        )
        _format_array(
            lines,
            f"{prefix}DefaultSpriteData",
            room.spritesets["default"],
            f"Room {room.index} default spriteset records.",
        )
        _format_array(
            lines,
            f"{prefix}FirstSpriteData",
            room.spritesets["first"],
            f"Room {room.index} first spriteset records (empty terminator).",
        )
        _format_array(
            lines,
            f"{prefix}SecondSpriteData",
            room.spritesets["second"],
            f"Room {room.index} second spriteset records (empty terminator).",
        )
        # Rooms with BG_PROP_LZ77_COMPRESSED point at the vanilla
        # sBg3_TestRoom backdrop, so no per-room payload is emitted for them.
        # The fallback keeps only for a future non-LZ77 room; it is dead today
        # because the loader rejects every other bg3_prop.
        if room.entry["bg3_prop"] != 0x40:
            _format_u32_array(
                lines,
                f"{prefix}Bg3Empty",
                (0x00000000, 0x00000000),
                f"Room {room.index} bg3: BGCNT_SIZE_256x256 + empty LZ77 stream.",
            )

    # Door table.
    if active_doors:
        lines.append("/* AREA_TEST_1 door table; DOOR_TYPE_NONE ends the scan. */")
        lines.append("static const struct Door HackTest1Doors[] = {")
        for door in doors:
            symbols = _door_type_symbols(door.type, f"door {door.index}.type")
            used_symbols.update(symbols)
            expression = " | ".join(symbols)
            lines.append("    {")
            lines.append(f"        .type = {expression},")
            lines.append(f"        .srcRoom = {door.src_room},")
            lines.append(f"        .xStart = {door.x_start},")
            lines.append(f"        .xEnd = {door.x_end},")
            lines.append(f"        .yStart = {door.y_start},")
            lines.append(f"        .yEnd = {door.y_end},")
            lines.append(f"        .dstDoor = {door.dst_door},")
            lines.append(f"        .xExit = {door.x_exit},")
            lines.append(f"        .yExit = {door.y_exit},")
            lines.append("    },")
        lines.append("    { .type = DOOR_TYPE_NONE },")
        used_symbols.add("DOOR_TYPE_NONE")
        lines.append("};")
        lines.append("")
    else:
        lines.append(
            "/* HACK-008c2 emits no active doors (see the header comment). */"
        )
        lines.append("static const struct Door HackTest1Doors[] = {")
        lines.append("    { .type = DOOR_TYPE_NONE },")
        lines.append("};")
        lines.append("")
        used_symbols.add("DOOR_TYPE_NONE")

    # Room entries.
    lines.append(
        "/* AREA_TEST_1 room entries indexed by room number; no terminator. */"
    )
    lines.append(
        "static const struct RoomEntryRom HackTest1RoomEntries[] = {"
    )
    for room in rooms:
        prefix = f"HackTest1Room{room.index}"
        entry = room.entry
        bg0_prop = _symbol_for(entry["bg0_prop"], BG_PROP_SYMBOLS, "$.room_entry.bg0_prop")
        bg1_prop = _symbol_for(entry["bg1_prop"], BG_PROP_SYMBOLS, "$.room_entry.bg1_prop")
        bg2_prop = _symbol_for(entry["bg2_prop"], BG_PROP_SYMBOLS, "$.room_entry.bg2_prop")
        bg3_prop = _symbol_for(entry["bg3_prop"], BG_PROP_SYMBOLS, "$.room_entry.bg3_prop")
        effect = _symbol_for(entry["effect"], EFFECT_SYMBOLS, "$.room_entry.effect")
        music = _symbol_for(entry["music_track"], MUSIC_SYMBOLS, "$.room_entry.music_track")
        used_symbols.update((bg0_prop, bg1_prop, bg2_prop, bg3_prop, effect, music))
        used_symbols.add("EVENT_NONE")
        lines.append(f"    [{room.index}] = {{")
        lines.append(f"        .tileset = {room.tileset},")
        lines.append(f"        .bg0Prop = {bg0_prop},")
        lines.append(f"        .bg1Prop = {bg1_prop},")
        lines.append(f"        .bg2Prop = {bg2_prop},")
        lines.append(f"        .bg3Prop = {bg3_prop},")
        lines.append(f"        .pBg0Data = {prefix}Bg0Empty,")
        lines.append(f"        .pBg1Data = {prefix}Bg1Data,")
        lines.append(f"        .pBg2Data = {prefix}Bg2Data,")
        lines.append(f"        .pClipData = {prefix}ClipData,")
        bg3_data = (
            "sBg3_TestRoom"
            if entry["bg3_prop"] == 0x40
            else f"{prefix}Bg3Empty"
        )
        lines.append(f"        .pBg3Data = {bg3_data},")
        lines.append(f"        .bg3Scrolling = {entry['bg3_scrolling']},")
        lines.append(f"        .transparency = {entry['transparency']},")
        lines.append(f"        .pDefaultSpriteData = {prefix}DefaultSpriteData,")
        lines.append(f"        .defaultSpriteset = {entry['default_spriteset']},")
        lines.append(f"        .firstSpritesetEvent = EVENT_NONE,")
        lines.append(f"        .pFirstSpriteData = {prefix}FirstSpriteData,")
        lines.append(f"        .firstSpriteset = {entry['first_spriteset']},")
        lines.append(f"        .secondSpritesetEvent = EVENT_NONE,")
        lines.append(f"        .pSecondSpriteData = {prefix}SecondSpriteData,")
        lines.append(f"        .secondSpriteset = {entry['second_spriteset']},")
        lines.append(f"        .mapX = {entry['map_x']},")
        lines.append(f"        .mapY = {entry['map_y']},")
        lines.append(f"        .effect = {effect},")
        lines.append(f"        .effectY = {entry['effect_y']},")
        lines.append(f"        .musicTrack = {music},")
        lines.append("    },")
    lines.append("};")
    lines.append("")
    lines.append(f"#endif /* {HEADER_GUARD} */")
    lines.append("")

    _verify_header_symbols(used_symbols)
    return "\n".join(lines)


def render_scroll_header(rooms: Sequence[RoomData]) -> str:
    """Render the scroll-only sibling header.

    HACK-008d1 splits scrolls out of ``content_tables.h`` so that every
    generated object is defined in exactly one translation unit: ``src/room.c``
    includes the room/door/spriteset header and ``src/scroll.c`` includes this
    one.  The two headers carry independent guards and never include each
    other.
    """

    rooms = sorted(rooms, key=lambda room: room.index)

    lines: list[str] = []
    lines.append("/*")
    lines.append(" * hack/gen/scroll_tables.h -- generated AREA_TEST_1 scroll overlay.")
    lines.append(" *")
    lines.append(" * Generated by tools/content/gen_content_tables.py.  DO NOT EDIT.")
    lines.append(" *")
    lines.append(" * HACK-008d1: scroll material only, included by src/scroll.c.")
    lines.append(" * Keeping it out of content_tables.h means src/room.c and")
    lines.append(" * src/scroll.c each define their own generated objects exactly once.")
    lines.append(" *")
    for room in rooms:
        lines.append(
            f" *   room {room.index} {room.name!r}: {room.scrolls[1]} scroll "
            f"record(s), source {room.directory_label}"
        )
    lines.append(" *")
    lines.append(" * The generated file is ignored by Git; `make content-tables`")
    lines.append(" * (a prerequisite of `make hack-build` and `make content-check`)")
    lines.append(" * regenerates and checks it.")
    lines.append(" */")
    lines.append(f"#ifndef {SCROLL_HEADER_GUARD}")
    lines.append(f"#define {SCROLL_HEADER_GUARD}")
    lines.append("")
    lines.append('#include "types.h"')
    lines.append('#include "structs/scroll.h"')
    lines.append("")

    for room in rooms:
        prefix = f"HackTest1Room{room.index}"
        _format_scroll_array(
            lines,
            f"{prefix}Scrolls",
            room.scrolls,
            room.scrolls[1],
            f"Room {room.index} scrolls: byte-for-byte scrolls.bin "
            f"({room.scrolls[1]} record(s)).",
        )

    # ScrollLoad scans this list with **ppSrc, comparing the first byte with
    # gCurrentRoom and stopping at a 0xFF block.  The terminator is generated
    # here because sScroll_Empty is static in src/scroll.c.
    _format_array(
        lines,
        "HackAreaScrollEnd",
        SCROLL_TERMINATOR,
        "Scroll list terminator; first byte UCHAR_MAX.",
    )
    lines.append(
        "/* AREA_TEST_1 scroll scan list; ScrollLoad stops at HackAreaScrollEnd. */"
    )
    lines.append("static const u8* HackTest1ScrollPointers[] = {")
    for room in rooms:
        lines.append(f"    HackTest1Room{room.index}Scrolls,")
    lines.append("    HackAreaScrollEnd,")
    lines.append("};")
    lines.append("")
    lines.append("#define HACK_AREA_TEST_1_SCROLLS HackTest1ScrollPointers")
    lines.append("")
    lines.append(f"#endif /* {SCROLL_HEADER_GUARD} */")
    lines.append("")

    return "\n".join(lines)


def render_sprite_header(rooms: Sequence[RoomData]) -> str:
    """Render the spriteset-only sibling header.

    HACK-008d3: the room entry's ``defaultSpriteset`` is an index into the
    vanilla ``sSpritesetPointers`` and cannot name a generated table.  This
    header carries the hack-owned ``(spriteId, gfxSlot)`` pair tables instead;
    ``src/sprite.c`` selects them under ``#ifdef HACK`` for AREA_TEST_1 so the
    spawn records resolve to the ids declared in the room manifest.
    """

    rooms = sorted(rooms, key=lambda room: room.index)

    lines: list[str] = []
    lines.append("/*")
    lines.append(" * hack/gen/sprite_tables.h -- generated AREA_TEST_1 spritesets.")
    lines.append(" *")
    lines.append(" * Generated by tools/content/gen_content_tables.py.  DO NOT EDIT.")
    lines.append(" *")
    lines.append(" * HACK-008d3: per-room default spriteset tables, included by")
    lines.append(" * src/sprite.c.  Each table is (spriteId, gfxSlot) byte pairs")
    lines.append(" * terminated by 0x00 0x00 (PSPRITE_TARGET_CIRCLES), exactly the")
    lines.append(" * shape SpriteLoadSpriteset reads from sSpritesetPointers.")
    lines.append(" *")
    for room in rooms:
        table = room.spriteset_tables.get("default", {})
        lines.append(
            f" *   room {room.index} {room.name!r}: {len(table)} sprite(s), "
            f"gfx slots 0..{max(table) if table else 0}"
        )
    lines.append(" *")
    lines.append(" * The generated file is ignored by Git; `make content-tables`")
    lines.append(" * (a prerequisite of `make hack-build` and `make content-check`)")
    lines.append(" * regenerates and checks it.")
    lines.append(" */")
    lines.append(f"#ifndef {SPRITE_HEADER_GUARD}")
    lines.append(f"#define {SPRITE_HEADER_GUARD}")
    lines.append("")
    lines.append('#include "types.h"')
    lines.append("")

    for room in rooms:
        table = room.spriteset_tables.get("default", {})
        prefix = f"HackTest1Room{room.index}"
        lines.append(
            f"/* Room {room.index} default spriteset: (spriteId, gfxSlot) pairs. */"
        )
        lines.append(
            f"static const u8 {prefix}DefaultSpriteset"
            f"[{2 * (len(table) + 1)}] = {{"
        )
        pairs: list[int] = []
        for slot in sorted(table):
            pairs.extend((table[slot], slot))
        pairs.extend((SPRITE_ID_TERMINATOR, SPRITE_ID_TERMINATOR))
        for offset in range(0, len(pairs), 12):
            body = ", ".join(f"0x{value:02X}" for value in pairs[offset : offset + 12])
            lines.append(f"    {body},")
        lines.append("};")
        lines.append("")

    lines.append("/* AREA_TEST_1 room -> default spriteset table. */")
    lines.append(
        "static const u8* const HackTest1DefaultSpritesets[] = {"
    )
    for room in rooms:
        lines.append(f"    HackTest1Room{room.index}DefaultSpriteset,")
    lines.append("};")
    lines.append("")
    lines.append("#define HACK_AREA_TEST_1_ROOM_COUNT "
                 f"{len(rooms)}")
    lines.append(
        "#define HACK_AREA_TEST_1_DEFAULT_SPRITESETS HackTest1DefaultSpritesets"
    )
    lines.append("")
    lines.append(f"#endif /* {SPRITE_HEADER_GUARD} */")
    lines.append("")
    return "\n".join(lines)


def _join_ints(values: Sequence[int]) -> str:
    if not values:
        return "none"
    return ", ".join(str(value) for value in values)


_SYMBOL_HEADERS = {
    "BG_PROP_": "include/constants/room.h",
    "EFFECT_": "include/constants/room.h",
    "DOOR_TYPE_": "include/constants/connection.h",
    "MUSIC_": "include/constants/audio.h",
    "EVENT_": "include/constants/event.h",
}


def _verify_header_symbols(symbols: Iterable[str]) -> None:
    cache: dict[str, str] = {}
    for symbol in sorted(set(symbols)):
        header = None
        for prefix, candidate in _SYMBOL_HEADERS.items():
            if symbol.startswith(prefix):
                header = candidate
                break
        if header is None:
            raise ContentError(f"unknown constant {symbol!r} has no header mapping")
        text = cache.get(header)
        if text is None:
            try:
                text = (REPO_ROOT / header).read_text(encoding="utf-8")
            except OSError as exc:
                raise ContentError(
                    f"unknown constant {symbol!r}: cannot read {header}: {exc}"
                ) from exc
            cache[header] = text
        if not re.search(r"\b" + re.escape(symbol) + r"\b", text):
            raise ContentError(
                f"unknown constant {symbol!r}: not found in {header}"
            )


def _load_rooms(room_dirs: Sequence[Path]) -> list[RoomData]:
    rooms = [load_room(Path(directory)) for directory in room_dirs]
    validate_room_set(rooms)
    return rooms


def build_tables(
    room_dirs: Sequence[Path], active_doors: bool
) -> tuple[str, str, str]:
    rooms = _load_rooms(room_dirs)
    return (
        render_header(rooms, active_doors),
        render_scroll_header(rooms),
        render_sprite_header(rooms),
    )


def build_header(room_dirs: Sequence[Path], active_doors: bool) -> str:
    return build_tables(room_dirs, active_doors)[0]


def build_scroll_header(room_dirs: Sequence[Path], active_doors: bool) -> str:
    return build_tables(room_dirs, active_doors)[1]


def build_sprite_header(room_dirs: Sequence[Path], active_doors: bool) -> str:
    return build_tables(room_dirs, active_doors)[2]


# ---------------------------------------------------------------------------
# Write/check


def write_header(path: Path, content: str) -> bool:
    try:
        if path.exists() and path.read_text(encoding="utf-8") == content:
            return False
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8")
    except OSError as exc:
        raise ContentError(f"cannot write {display_path(path)}: {exc}") from exc
    return True


def check_header(path: Path, content: str) -> None:
    if not path.exists():
        raise ContentError(
            f"{display_path(path)} is missing; run "
            "`make content-tables` (or `make hack-build`)"
        )
    try:
        actual = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise ContentError(f"cannot read {display_path(path)}: {exc}") from exc
    if actual != content:
        raise ContentError(
            f"{display_path(path)} is stale; run `make content-tables`"
        )


# ---------------------------------------------------------------------------
# Self-check


def _write_json(path: Path, value: Any) -> None:
    path.write_text(
        json.dumps(value, sort_keys=True, indent=2) + "\n", encoding="utf-8"
    )


def _synthetic_rle() -> bytes:
    # 2x2, mode 1, all four blocks distinct.
    return bytes(
        [
            0x02,
            0x02,
            0x01,
            0x04,
            0x01,
            0x02,
            0x03,
            0x04,
            0x00,
            0x01,
            0x04,
            0x05,
            0x06,
            0x07,
            0x08,
            0x00,
        ]
    )


def _synthetic_room(
    root: Path,
    *,
    index: int = 0,
    name: str = "synthetic",
    door: tuple[int, int, int] | None = (1, 0, 1),
    bg1_prop: int = 0x10,
    bg3_prop: int = 0x40,
    door_type: int = 0x12,
    missing_bg1: bool = False,
    bad_counter: bool = False,
) -> Path:
    directory = root / f"room_{index}_{name}"
    directory.mkdir(parents=True)
    rle = _synthetic_rle()
    files = {"bg1.rle": rle, "bg2.rle": rle, "clipdata.rle": rle}
    for filename, data in files.items():
        if missing_bg1 and filename == "bg1.rle":
            continue
        (directory / filename).write_bytes(data)

    door_records = []
    door_bytes = b""
    if door is not None:
        object_id, src_room, dst_door = door
        fields = (door_type, src_room, 1, 1, 0, 1, dst_door, 0, 0)
        door_bytes = struct.pack("<BBBBBBBbb", *fields)
        door_records.append(
            {
                "id": object_id,
                "type": door_type,
                "src_room": src_room,
                "x_start": 1,
                "x_end": 1,
                "y_start": 0,
                "y_end": 1,
                "dst_door": dst_door,
                "x_exit": 0,
                "y_exit": 0,
            }
        )
    (directory / "doors.bin").write_bytes(door_bytes)

    default_sprites = bytes([1, 1, 0x11]) + SPRITESET_TERMINATOR
    first_sprites = SPRITESET_TERMINATOR
    second_sprites = SPRITESET_TERMINATOR
    (directory / "spriteset_default.bin").write_bytes(default_sprites)
    (directory / "spriteset_first.bin").write_bytes(first_sprites)
    (directory / "spriteset_second.bin").write_bytes(second_sprites)

    scrolls = bytes([index, 1, 0, 1, 0, 1, 255, 255, 255, 255])
    (directory / "scrolls.bin").write_bytes(scrolls)

    def counter(size: int) -> int:
        return size + 1 if bad_counter else size

    doc = {
        "schema": ROOM_SCHEMA,
        "room": {
            "name": name,
            "area_name": AREA_TEST_1_NAME,
            "area": AREA_TEST_1,
            "index": index,
        },
        "dimensions": {
            "width_blocks": 2,
            "height_blocks": 2,
            "block_width": PIXEL_PER_BLOCK,
            "block_height": PIXEL_PER_BLOCK,
            "width_pixels": 32,
            "height_pixels": 32,
        },
        "tileset": {
            "number": 0,
            "block_width": PIXEL_PER_BLOCK,
            "block_height": PIXEL_PER_BLOCK,
        },
        "room_entry": {
            "tileset": 0,
            "bg0_prop": 0,
            "bg1_prop": bg1_prop,
            "bg2_prop": 0x10,
            "bg3_prop": bg3_prop,
            "bg3_scrolling": 1,
            "transparency": 0,
            "effect": 0,
            "effect_y": 255,
            "music_track": 0,
            "map_x": index,
            "map_y": 2,
            "first_spriteset_event": 0,
            "second_spriteset_event": 0,
            "default_spriteset": 255,
            "first_spriteset": 255,
            "second_spriteset": 255,
        },
        "layers": {
            role: {
                "rle_file": filename,
                "rle_bytes": counter(len(files[filename])),
                "width": 2,
                "height": 2,
            }
            for role, filename in (
                ("bg1", "bg1.rle"),
                ("bg2", "bg2.rle"),
                ("clip", "clipdata.rle"),
            )
        },
        "outputs": {
            "bg1": {"file": "bg1.rle", "bytes": counter(len(rle))},
            "bg2": {"file": "bg2.rle", "bytes": counter(len(rle))},
            "clipdata": {"file": "clipdata.rle", "bytes": counter(len(rle))},
            "doors": {
                "file": "doors.bin",
                "bytes": len(door_bytes),
                "count": len(door_records),
            },
            "scrolls": {"file": "scrolls.bin", "bytes": len(scrolls)},
            "spriteset_default": {
                "file": "spriteset_default.bin",
                "bytes": len(default_sprites),
                "count": 1,
            },
            "spriteset_first": {
                "file": "spriteset_first.bin",
                "bytes": len(first_sprites),
                "count": 0,
            },
            "spriteset_second": {
                "file": "spriteset_second.bin",
                "bytes": len(second_sprites),
                "count": 0,
            },
        },
        "doors": {
            "file": "doors.bin",
            "bytes": len(door_bytes),
            "count": len(door_records),
            "records": door_records,
        },
        "scrolls": {
            "file": "scrolls.bin",
            "bytes": len(scrolls),
            "records": [
                {
                    "x_start": 0,
                    "x_end": 1,
                    "y_start": 0,
                    "y_end": 1,
                    "breakable_x": 255,
                    "breakable_y": 255,
                    "extended_direction": 255,
                    "extended_value": 255,
                }
            ],
        },
        "spritesets": {
            "default": {
                "file": "spriteset_default.bin",
                "bytes": len(default_sprites),
                "count": 1,
                "table": {"0": 1},
                "records": [
                    {
                        "id": 1,
                        "name": "synthetic_spawn",
                        "x": 1,
                        "y": 1,
                        "record_byte": 0x11,
                        "sprite_id": 1,
                        "slot": 0,
                        "properties": 0x10,
                    }
                ],
            },
            "first": {
                "file": "spriteset_first.bin",
                "bytes": len(first_sprites),
                "count": 0,
                "records": [],
            },
            "second": {
                "file": "spriteset_second.bin",
                "bytes": len(second_sprites),
                "count": 0,
                "records": [],
            },
        },
    }
    _write_json(directory / "room.json", doc)
    return directory


def _expect_error(callback: Callable[[], Any], needle: str) -> None:
    try:
        callback()
    except ContentError as exc:
        if needle not in str(exc):
            raise ContentError(
                f"self-check: expected error containing {needle!r}, got {exc}"
            ) from exc
        return
    raise ContentError(f"self-check: expected an error containing {needle!r}")


def _rewrite_scrolls(directory: Path, data: bytes) -> None:
    """Replace scrolls.bin and keep the manifest byte count in sync."""

    (directory / "scrolls.bin").write_bytes(data)
    doc = load_json(directory / "room.json", "room.json")
    doc["outputs"]["scrolls"]["bytes"] = len(data)
    if "bytes" in doc.get("scrolls", {}):
        doc["scrolls"]["bytes"] = len(data)
    _write_json(directory / "room.json", doc)


def _generated_array_bytes(header: str, name: str) -> bytes:
    pattern = re.compile(
        r"static const u8 " + re.escape(name) + r"\[[^\]]*\] = \{\n(.*?)\n\};",
        re.DOTALL,
    )
    match = pattern.search(header)
    if match is None:
        raise ContentError(f"self-check: generated header lacks array {name!r}")
    return bytes(int(value, 16) for value in re.findall(r"0x([0-9A-F]{2})", match.group(1)))


def self_check() -> None:
    with tempfile.TemporaryDirectory(prefix="mf-content-tables-") as temp:
        root = Path(temp)
        room0 = _synthetic_room(root)
        room1 = _synthetic_room(
            root, index=1, name="synthetic_next", door=(2, 1, 0)
        )

        # Deterministic single-room no-door output, for both headers.
        first, first_scrolls, first_sprites = build_tables(
            [room0], active_doors=False
        )
        second, second_scrolls, second_sprites = build_tables(
            [room0], active_doors=False
        )
        if (first, first_scrolls, first_sprites) != (
            second,
            second_scrolls,
            second_sprites,
        ):
            raise ContentError("self-check: generation is not deterministic")
        for needle in (
            "HackTest1Doors",
            "HackTest1RoomEntries",
            "{ .type = DOOR_TYPE_NONE },",
            ".mapY = 2,",
            "extern const u32 sBg3_TestRoom[224];",
            ".pBg3Data = sBg3_TestRoom,",
            ".bg3Scrolling = 1,",
        ):
            if needle not in first:
                raise ContentError(f"self-check: generated header lacks {needle!r}")
        if "Bg3Empty" in first:
            raise ContentError(
                "self-check: generated header emits an unused Bg3Empty payload"
            )
        for needle in (
            "HackTest1Room0Scrolls",
            "SCROLL_DATA_SIZE(1)",
            "HackAreaScrollEnd",
            "HackTest1ScrollPointers",
            "#define HACK_AREA_TEST_1_SCROLLS HackTest1ScrollPointers",
        ):
            if needle not in first_scrolls:
                raise ContentError(
                    f"self-check: scroll header lacks {needle!r}"
                )
        # The split must be complete: scroll objects may not appear twice.
        for symbol in (
            "HackTest1Room0Scrolls",
            "HackAreaScrollEnd",
            "HackTest1ScrollPointers",
        ):
            if symbol in first:
                raise ContentError(
                    f"self-check: content header still defines {symbol!r}"
                )
        if _generated_array_bytes(first_scrolls, "HackTest1Room0Scrolls") != (
            room0 / "scrolls.bin"
        ).read_bytes():
            raise ContentError(
                "self-check: HackTest1Room0Scrolls is not byte-exact with scrolls.bin"
            )
        if _generated_array_bytes(first_scrolls, "HackAreaScrollEnd") != SCROLL_TERMINATOR:
            raise ContentError("self-check: the generated scroll terminator is not FF")

        # HACK-008d3: the spriteset header carries (spriteId, gfxSlot) pairs.
        for needle in (
            "HackTest1Room0DefaultSpriteset",
            "HackTest1DefaultSpritesets",
            "#define HACK_AREA_TEST_1_ROOM_COUNT 1",
            "#define HACK_AREA_TEST_1_DEFAULT_SPRITESETS HackTest1DefaultSpritesets",
        ):
            if needle not in first_sprites:
                raise ContentError(
                    f"self-check: sprite header lacks {needle!r}"
                )
        if _generated_array_bytes(
            first_sprites, "HackTest1Room0DefaultSpriteset"
        ) != bytes((1, 0, 0, 0)):
            raise ContentError(
                "self-check: default spriteset is not the expected id/slot pairs"
            )
        for symbol in (
            "HackTest1Room0DefaultSpriteset",
            "HackTest1DefaultSpritesets",
        ):
            if symbol in first:
                raise ContentError(
                    f"self-check: content header still defines {symbol!r}"
                )

        # Active-door path (HACK-008d shape): two rooms, reciprocal doors.
        active, active_scrolls, _ = build_tables(
            [room0, room1], active_doors=True
        )
        for needle in (
            ".dstDoor = 1,",
            ".dstDoor = 0,",
            "DOOR_TYPE_NORMAL | DOOR_TYPE_NO_HATCH",
            "[1] = {",
        ):
            if needle not in active:
                raise ContentError(
                    f"self-check: active door header lacks {needle!r}"
                )
        if (
            "    HackTest1Room0Scrolls,\n    HackTest1Room1Scrolls,\n"
            "    HackAreaScrollEnd,\n"
        ) not in active_scrolls:
            raise ContentError(
                "self-check: scroll pointer list is not in room-index order"
            )

        # Freshness check: both files must be written and checked independently.
        header_path = root / "content_tables.h"
        scroll_path = root / SCROLL_HEADER_NAME
        sprite_path = root / SPRITE_HEADER_NAME
        if not write_header(header_path, first):
            raise ContentError("self-check: first write reported no change")
        if not write_header(scroll_path, first_scrolls):
            raise ContentError("self-check: first scroll write reported no change")
        if not write_header(sprite_path, first_sprites):
            raise ContentError("self-check: first sprite write reported no change")
        check_header(header_path, first)
        check_header(scroll_path, first_scrolls)
        check_header(sprite_path, first_sprites)
        if write_header(header_path, first):
            raise ContentError("self-check: identical write rewrote the file")
        if write_header(scroll_path, first_scrolls):
            raise ContentError("self-check: identical write rewrote the scroll file")
        if write_header(sprite_path, first_sprites):
            raise ContentError("self-check: identical write rewrote the sprite file")
        header_path.write_text(first + "\n", encoding="utf-8")
        _expect_error(lambda: check_header(header_path, first), "stale")
        check_header(scroll_path, first_scrolls)
        check_header(sprite_path, first_sprites)
        header_path.write_text(first, encoding="utf-8")
        scroll_path.write_text(first_scrolls + "\n", encoding="utf-8")
        _expect_error(lambda: check_header(scroll_path, first_scrolls), "stale")
        scroll_path.write_text(first_scrolls, encoding="utf-8")
        sprite_path.write_text(first_sprites + "\n", encoding="utf-8")
        _expect_error(lambda: check_header(sprite_path, first_sprites), "stale")
        sprite_path.unlink()
        _expect_error(
            lambda: check_header(sprite_path, first_sprites), "missing"
        )

        # Missing file.
        missing_root = root / "missing"
        missing_root.mkdir()
        missing_room = _synthetic_room(missing_root, missing_bg1=True)
        _expect_error(
            lambda: build_header([missing_room], active_doors=False),
            "missing file",
        )

        # Unknown constant.
        unknown_root = root / "unknown"
        unknown_root.mkdir()
        unknown_room = _synthetic_room(unknown_root, bg1_prop=0x99)
        _expect_error(
            lambda: build_header([unknown_room], active_doors=False),
            "has no known C constant",
        )

        # bg3 must be LZ77: RoomLoadBackgrounds always decompresses + 4.
        bg3_root = root / "bg3"
        bg3_root.mkdir()
        bg3_room = _synthetic_room(bg3_root, bg3_prop=0)
        _expect_error(
            lambda: build_header([bg3_room], active_doors=False),
            "BG_PROP_LZ77_COMPRESSED",
        )

        # Bad counters.
        counter_root = root / "counter"
        counter_root.mkdir()
        counter_room = _synthetic_room(counter_root, bad_counter=True)
        _expect_error(
            lambda: build_header([counter_room], active_doors=False),
            "bad counter",
        )

        # Bad scroll record count: byte 1 says two records, length says one.
        scroll_count_root = root / "scroll_count"
        scroll_count_root.mkdir()
        scroll_count_room = _synthetic_room(scroll_count_root)
        scroll_data = bytearray((scroll_count_room / "scrolls.bin").read_bytes())
        scroll_data[1] = 2
        _rewrite_scrolls(scroll_count_room, bytes(scroll_data))
        _expect_error(
            lambda: build_header([scroll_count_room], active_doors=False),
            "10 bytes for 2 record(s)",
        )

        # Bad scroll block length: one trailing byte with the manifest updated.
        scroll_length_root = root / "scroll_length"
        scroll_length_root.mkdir()
        scroll_length_room = _synthetic_room(scroll_length_root)
        scroll_data = (scroll_length_room / "scrolls.bin").read_bytes() + b"\x00"
        _rewrite_scrolls(scroll_length_room, scroll_data)
        _expect_error(
            lambda: build_header([scroll_length_room], active_doors=False),
            "11 bytes for 1 record(s)",
        )

        # Bad scroll field: the .bin x_end no longer matches camera.scrolls.
        scroll_field_root = root / "scroll_field"
        scroll_field_root.mkdir()
        scroll_field_room = _synthetic_room(scroll_field_root)
        scroll_data = bytearray((scroll_field_room / "scrolls.bin").read_bytes())
        scroll_data[3] = 0
        _rewrite_scrolls(scroll_field_room, bytes(scroll_data))
        _expect_error(
            lambda: build_header([scroll_field_room], active_doors=False),
            "camera.scrolls values do not match",
        )

        # Bad room-id byte in the scroll block.
        scroll_room_root = root / "scroll_room"
        scroll_room_root.mkdir()
        scroll_room_room = _synthetic_room(scroll_room_root)
        scroll_data = bytearray((scroll_room_room / "scrolls.bin").read_bytes())
        scroll_data[0] = 9
        _rewrite_scrolls(scroll_room_room, bytes(scroll_data))
        _expect_error(
            lambda: build_header([scroll_room_room], active_doors=False),
            "room index 9 does not match room 0",
        )

        # Dangling room reference: index must be contiguous from 0.
        _expect_error(
            lambda: build_header([room1], active_doors=False),
            "room indices must be contiguous",
        )

        # Dangling door reference: destination outside the emitted table.
        dangling_root = root / "dangling"
        dangling_root.mkdir()
        dangling = _synthetic_room(dangling_root, door=(1, 0, 9))
        _expect_error(
            lambda: build_header([dangling], active_doors=True),
            "dangling door reference",
        )

        # Unknown door type constant.
        type_root = root / "type"
        type_root.mkdir()
        bad_type = _synthetic_room(type_root, door_type=0x81)
        _expect_error(
            lambda: build_header([bad_type], active_doors=True),
            "unknown high flags",
        )

        # Duplicate global door index.
        duplicate_root = root / "duplicate"
        duplicate_root.mkdir()
        duplicate0 = _synthetic_room(duplicate_root, index=0, door=(1, 0, 1))
        duplicate1 = _synthetic_room(
            duplicate_root, index=1, name="dup", door=(1, 1, 0)
        )
        _expect_error(
            lambda: build_header([duplicate0, duplicate1], active_doors=True),
            "appears twice",
        )

        # Truncated spriteset terminator.
        sprite_root = root / "sprite"
        sprite_root.mkdir()
        sprite_room = _synthetic_room(sprite_root)
        # Same size and record count, but the FF FF FF terminator is corrupt.
        (sprite_room / "spriteset_default.bin").write_bytes(b"\x01\x01\x11\xff\xff\x00")
        _expect_error(
            lambda: build_header([sprite_room], active_doors=False),
            "terminator",
        )

        # HACK-008d3: a gfx slot outside 0..7 is rejected (the engine only
        # addresses eight 2048-byte slots).
        slot_root = root / "sprite_slot"
        slot_root.mkdir()
        slot_room = _synthetic_room(slot_root)
        slot_doc = load_json(slot_room / "room.json", "room.json")
        slot_doc["spritesets"]["default"]["table"] = {"0": 1, "8": 1}
        _write_json(slot_room / "room.json", slot_doc)
        _expect_error(
            lambda: build_header([slot_room], active_doors=False),
            "outside 0..7",
        )

        # The emitted table and the table-indexed spawn record must agree.
        mismatch_root = root / "sprite_mismatch"
        mismatch_root.mkdir()
        mismatch_room = _synthetic_room(mismatch_root)
        mismatch_doc = load_json(mismatch_room / "room.json", "room.json")
        mismatch_doc["spritesets"]["default"]["table"] = {"0": 2}
        _write_json(mismatch_room / "room.json", mismatch_doc)
        _expect_error(
            lambda: build_header([mismatch_room], active_doors=False),
            "does not match",
        )

    print("CONTENT-TABLES: PASS (self-check)")


# ---------------------------------------------------------------------------
# Driver


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Generate hack/gen/content_tables.h and its scroll-only sibling "
            "hack/gen/scroll_tables.h from converted rooms."
        )
    )
    parser.add_argument(
        "--room-dir",
        action="append",
        default=None,
        help="converted room directory (repeatable; default %s)"
        % DEFAULT_ROOM_DIRS[0],
    )
    parser.add_argument(
        "--out",
        default=DEFAULT_OUT,
        help=(
            f"generated room/door/spriteset header path (default {DEFAULT_OUT}); "
            f"the scroll-only sibling {SCROLL_HEADER_NAME} and the spriteset "
            f"sibling {SPRITE_HEADER_NAME} are written beside it"
        ),
    )
    parser.add_argument(
        "--active-doors",
        action="store_true",
        help="emit active door records (HACK-008d); default is a terminator only",
    )
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--write", action="store_true", help="write both headers")
    mode.add_argument("--check", action="store_true", help="fail if either is stale")
    mode.add_argument("--self-check", action="store_true", help="run the tool suite")
    args = parser.parse_args(argv)

    if args.self_check:
        try:
            self_check()
        except ContentError as exc:
            print(f"ERROR: {exc}", file=sys.stderr)
            return 2
        return 0

    room_dirs = [Path(path) for path in (args.room_dir or DEFAULT_ROOM_DIRS)]
    out = Path(args.out)
    scroll_out = out.with_name(SCROLL_HEADER_NAME)
    sprite_out = out.with_name(SPRITE_HEADER_NAME)
    try:
        content, scrolls, sprites = build_tables(room_dirs, args.active_doors)
        if args.write:
            for path, text in (
                (out, content),
                (scroll_out, scrolls),
                (sprite_out, sprites),
            ):
                changed = write_header(path, text)
                state = "wrote" if changed else "unchanged"
                print(f"CONTENT-TABLES: {state} {display_path(path)}")
            print("CONTENT-TABLES: PASS")
        else:
            for path, text in (
                (out, content),
                (scroll_out, scrolls),
                (sprite_out, sprites),
            ):
                check_header(path, text)
            print(
                f"CONTENT-TABLES: PASS ({display_path(out)}, "
                f"{display_path(scroll_out)} and {display_path(sprite_out)} "
                "are fresh)"
            )
    except ContentError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
