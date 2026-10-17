#!/usr/bin/env python3
"""Tiled/PNG -> room data scaffold for mf-hack content.

The tool is deliberately an *intermediate* pipeline.  It converts Tiled JSON
tile layers into the engine's existing RLE room-block format and writes the
side data (doors, spritesets, scroll bounds) as deterministic little records.
It does not modify the engine, emit C, or convert tileset graphics.

Schema and decomp citations live in ``docs/content-pipeline.md``.  The compact
fixture is in ``tools/content/fixtures/``.

Examples
--------

::

    python3 tools/content/tiled_to_room.py --self-check

    python3 tools/content/tiled_to_room.py \
        --map hack/content/tiled/entry_ledge.tmj \
        --manifest hack/content/rooms/entry_ledge.room.json \
        --out hack/gen/rooms/entry_ledge

Output is deterministic: sorted JSON keys, fixed filenames, no timestamps,
and no absolute source paths or ROM addresses.
"""

from __future__ import annotations

import argparse
import base64
import contextlib
import gzip
import io
import json
import re
import struct
import sys
import tempfile
import zlib
from pathlib import Path
from typing import Any, Iterable, Sequence

import pngio


MANIFEST_SCHEMA = "mf-hack.room-manifest/v1"
ROOM_SCHEMA = "mf-hack.room/v1"

PIXEL_PER_BLOCK = 16
MAX_ROOM_BLOCKS = 6144  # gDecompClipdataMap / gDecompBg*Map regions are 0x3000 bytes
MAX_TILESET_ENTRIES = 98  # include/data/rooms_data.h: sTilesetEntries[98]
MAX_CLIPDATA = 176  # include/constants/clipdata.h: CLIPDATA_COUNT
MAX_SPRITE_ID_FALLBACK = 255

ROOM_SPRITE_DATA_TERMINATOR = b"\xff\xff\xff"

# Small, reviewed copies of plain enums used in manifests.  Symbolic clipdata
# and sprite IDs are loaded from the headers when the checkout is available.
AREA_NAMES = {
    "AREA_MAIN_DECK": 0,
    "AREA_SECTOR_1": 1,
    "AREA_SECTOR_2": 2,
    "AREA_SECTOR_3": 3,
    "AREA_SECTOR_4": 4,
    "AREA_SECTOR_5": 5,
    "AREA_SECTOR_6": 6,
    "AREA_TEST_1": 7,
    "AREA_TEST_2": 8,
    "AREA_TEST_3": 9,
}

BG_PROP_NAMES = {
    "BG_PROP_NONE": 0,
    "BG_PROP_RLE_COMPRESSED": 0x10,
    "BG_PROP_LZ77_COMPRESSED": 0x40,
    "BG_PROP_11": 0x11,
    "BG_PROP_DISABLE_TRANSPARENCY": 0x12,
    "BG_PROP_13": 0x13,
    "BG_PROP_14": 0x14,
    "BG_PROP_NIGHTMARE_ROOM": 0x41,
    "BG_PROP_DARK_ROOM": 0x43,
    "BG_PROP_SA_X_ROOM": 0x44,
    "BG_PROP_DIM_ROOM": 0x45,
    "BG_PROP_WATER_DRAIN_ROOM": 0x46,
    "BG_PROP_FOG": 0x47,
    "BG_PROP_MELTDOWN": 0x48,
    "BG_PROP_NIGHTMARE_SHADOW": 0x49,
    "BG_PROP_SR388": 0x4A,
}

EFFECT_NAMES = {
    "EFFECT_NONE": 0,
    "EFFECT_WATER": 1,
    "EFFECT_LAVA": 2,
    "EFFECT_LAVA_HEAT_HAZE": 3,
    "EFFECT_ACID": 4,
    "EFFECT_SNOWFLAKES_COLD_KNOCKBACK": 5,
    "EFFECT_SNOWFLAKES_COLD": 6,
    "EFFECT_HEAT_BG3_HAZE": 7,
    "EFFECT_HEAT_BG2_BG3_HAZE": 8,
    "EFFECT_BG3_GRADIENT": 9,
    "EFFECT_BG2_GRADIENT": 10,
    "EFFECT_HAZE_BG1_BG2_BG3": 11,
}

DOOR_TYPE_NAMES = {
    "DOOR_TYPE_NONE": 0,
    "DOOR_TYPE_AREA_CONNECTION": 1,
    "DOOR_TYPE_NO_HATCH": 2,
    "DOOR_TYPE_OPEN_HATCH": 3,
    "DOOR_TYPE_HATCH_CAN_LOCK": 4,
    "DOOR_TYPE_NO_FLAGS": 0xF,
    "DOOR_TYPE_NORMAL": 0x10,
    "DOOR_TYPE_LOAD_EVENT_BASED_ROOM": 0x20,
    "DOOR_TYPE_DISPLAY_LOCATION_NAME": 0x40,
}

SPRITE_PROPERTY_NAMES = {
    "SP_ALWAYS_ACTIVE": 0x01,
    "SP_CAN_ABSORB_X": 0x02,
    "SP_KILL_OFF_SCREEN": 0x04,
    "SP_SOLID_FOR_PROJECTILES": 0x08,
    "SP_DESTROYED": 0x10,
    "SP_ABSOLUTE_POSITION": 0x20,
    "SP_IMMUNE_TO_PROJECTILES": 0x40,
    "SP_SECONDARY_SPRITE": 0x80,
}

SPRITESET_PROPERTY_NAMES = {
    "SSP_UNINFECTED_OR_BOSS": 0x10,
    "SSP_X_ABSORBABLE_BY_SAMUS": 0x20,
    "SSP_X_UNABSORBABLE_BY_SAMUS": 0x30,
    "SSP_UNKNOWN_40": 0x40,
    "SSP_HIDDEN_ON_ROOM_LOAD": 0x80,
}

REPO_ROOT = Path(__file__).resolve().parents[2]
FIXTURES = Path(__file__).resolve().parent / "fixtures"

MANIFEST_KEYS = {"schema", "room"}
ROOM_KEYS = {
    "name",
    "area",
    "index",
    "tileset",
    "layers",
    "room_entry",
    "tile_mapping",
    "camera",
}
TILESET_KEYS = {
    "number",
    "image",
    "tile_pixels",
    "block_pixels",
    "colors_per_tile",
    "transparent_index",
}
LAYER_KEYS = {"bg0", "bg1", "bg2", "clip"}
ROOM_ENTRY_KEYS = {
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
}
CAMERA_KEYS = {"scrolls"}
SCROLL_KEYS = {
    "x_start",
    "x_end",
    "y_start",
    "y_end",
    "breakable_x",
    "breakable_y",
    "extended_direction",
    "extended_value",
}
DOOR_PROPERTY_KEYS = {"type", "src_room", "dst_door", "x_exit", "y_exit"}
SPAWN_PROPERTY_KEYS = {"sprite_id", "spriteset", "slot", "properties"}


class ContentError(Exception):
    """A user-facing content validation error."""


# ---------------------------------------------------------------------------
# JSON and small helpers


def _reject_duplicate_keys(pairs: list[tuple[str, Any]]) -> dict[str, Any]:
    result: dict[str, Any] = {}
    for key, value in pairs:
        if key in result:
            raise ContentError(f"duplicate JSON key {key!r}")
        result[key] = value
    return result


def load_json(path: str | Path, label: str) -> Any:
    path = Path(path)
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise ContentError(f"cannot read {label} {path}: {exc}") from exc
    try:
        return json.loads(text, object_pairs_hook=_reject_duplicate_keys)
    except ContentError:
        raise
    except json.JSONDecodeError as exc:
        raise ContentError(f"{label} {path}: invalid JSON: {exc}") from exc


def expect_object(value: Any, path: str) -> dict[str, Any]:
    if not isinstance(value, dict):
        raise ContentError(f"{path}: expected a JSON object")
    return value


def expect_keys(
    obj: dict[str, Any], allowed: set[str], required: set[str], path: str
) -> None:
    missing = sorted(required - set(obj))
    if missing:
        raise ContentError(f"{path}: missing required key(s): {', '.join(missing)}")
    unknown = sorted(set(obj) - allowed)
    if unknown:
        raise ContentError(f"{path}: unknown key(s): {', '.join(unknown)}")


def as_int(value: Any, path: str, minimum: int, maximum: int) -> int:
    if isinstance(value, bool) or not isinstance(value, int):
        raise ContentError(f"{path}: expected an integer in {minimum}..{maximum}")
    if not minimum <= value <= maximum:
        raise ContentError(
            f"{path}: {value} is outside the allowed range {minimum}..{maximum}"
        )
    return value


def as_positive_int(value: Any, path: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value <= 0:
        raise ContentError(f"{path}: expected a positive integer")
    return value


def as_size_pair(value: Any, path: str) -> tuple[int, int]:
    if isinstance(value, int) and not isinstance(value, bool):
        width = height = as_positive_int(value, path)
        return width, height
    if (
        isinstance(value, list)
        and len(value) == 2
        and all(isinstance(v, int) and not isinstance(v, bool) and v > 0 for v in value)
    ):
        return value[0], value[1]
    raise ContentError(f"{path}: expected a positive integer or [width, height]")


def as_relative_path(value: Any, path: str) -> str:
    if not isinstance(value, str) or not value:
        raise ContentError(f"{path}: expected a relative file path")
    candidate = Path(value)
    if candidate.is_absolute() or ".." in candidate.parts:
        raise ContentError(
            f"{path}: expected a path relative to the manifest directory "
            "without '..' components"
        )
    return candidate.as_posix()


def resolve_symbol(value: Any, table: dict[str, int], path: str) -> int:
    if isinstance(value, bool):
        raise ContentError(f"{path}: expected an integer or symbolic name")
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        text = value.strip()
        if text in table:
            return table[text]
        try:
            return int(text, 0)
        except ValueError:
            pass
    raise ContentError(
        f"{path}: unknown symbol {value!r}; known names: {', '.join(sorted(table))}"
    )


def resolve_flags(value: Any, table: dict[str, int], path: str) -> int:
    if isinstance(value, int) and not isinstance(value, bool):
        return value
    if not isinstance(value, str):
        raise ContentError(f"{path}: expected an integer or a '|'-joined symbol list")
    total = 0
    for piece in value.split("|"):
        piece = piece.strip()
        if not piece:
            raise ContentError(f"{path}: empty component in symbol list {value!r}")
        total |= resolve_symbol(piece, table, path)
    return total


def parse_c_enum(header: Path, start_pattern: str) -> dict[str, int]:
    """Parse a plain sequential C enum from a project header.

    The parser understands ``NAME`` and ``NAME = <integer>`` items.  It is used
    only for large, stable lists (clipdata values, primary sprite IDs) where a
    hand copy would rot.  Missing headers simply disable symbolic names.
    """

    try:
        text = header.read_text(encoding="utf-8")
    except OSError:
        return {}
    match = re.search(start_pattern + r"\s*\{(.*?)\n\};", text, re.S)
    if not match:
        return {}
    body = re.sub(r"/\*.*?\*/", "", match.group(1), flags=re.S)
    body = re.sub(r"//[^\n]*", "", body)
    values: dict[str, int] = {}
    current = 0
    for item in body.split(","):
        item = item.strip()
        if not item:
            continue
        if "=" in item:
            name, expr = [part.strip() for part in item.split("=", 1)]
            try:
                current = int(expr, 0)
            except ValueError:
                # Expressions such as MUSIC_COUNT are not needed here.
                break
        else:
            name = item
        name = name.strip()
        if not re.fullmatch(r"[A-Z][A-Z0-9_]*", name):
            continue
        values[name] = current
        current += 1
    return values


def load_clipdata_names() -> dict[str, int]:
    table = parse_c_enum(
        REPO_ROOT / "include/constants/clipdata.h",
        r"MAKE_ENUM\(u16, Clipdata\)",
    )
    table.setdefault("CLIPDATA_AIR", 0)
    table.setdefault("CLIPDATA_SOLID", 16)
    table.setdefault("CLIPDATA_DOOR_TRANSITION", 32)
    return table


def load_sprite_ids() -> dict[str, int]:
    return parse_c_enum(
        REPO_ROOT / "include/constants/sprite.h",
        r"enum PrimarySpriteId",
    )


# ---------------------------------------------------------------------------
# Engine RLE


def encode_rle_pass(data: bytes) -> bytes:
    """Encode one byte plane in the mode-1 (8-bit counts) RLE form."""

    out = bytearray([0x01])
    index = 0
    length = len(data)
    while index < length:
        run = 1
        while (
            index + run < length
            and data[index + run] == data[index]
            and run < 0x7F
        ):
            run += 1
        if run >= 2:
            out.append(0x80 | run)
            out.append(data[index])
            index += run
            continue

        start = index
        index += 1
        while index < length and index - start < 0x7F:
            if index + 1 < length and data[index] == data[index + 1]:
                break
            index += 1
        out.append(index - start)
        out.extend(data[start:index])

    out.append(0x00)
    return bytes(out)


def encode_rle_u16(values: Sequence[int], width: int, height: int) -> bytes:
    """Return width, height, then a `RoomRleDecompress` stream for u16 blocks."""

    if len(values) != width * height:
        raise ContentError("internal error: RLE value count does not match dimensions")
    for value in values:
        if not 0 <= value <= 0xFFFF:
            raise ContentError(f"internal error: block value {value} is not u16")

    low = bytes(value & 0xFF for value in values)
    high = bytes(value >> 8 for value in values)
    return bytes([width, height]) + encode_rle_pass(low) + encode_rle_pass(high)


def decode_rle_u16(data: bytes) -> tuple[int, int, list[int]]:
    """Mirror of ``RoomRleDecompress`` for self-checks.

    Supports the 8-bit mode produced by this tool and the 16-bit mode used by
    some vanilla streams.
    """

    if len(data) < 2:
        raise ContentError("internal error: RLE stream has no header")
    width, height = data[0], data[1]
    if width == 0 or height == 0:
        raise ContentError("internal error: RLE stream has zero dimension")
    count = width * height
    output = bytearray(count * 2)
    pos = 2

    for pass_index in range(2):
        dst = pass_index
        if pos >= len(data):
            raise ContentError("internal error: truncated RLE stream")
        mode = data[pos]
        pos += 1
        if mode == 1:
            while True:
                if pos >= len(data):
                    raise ContentError("internal error: truncated RLE run count")
                run = data[pos]
                pos += 1
                if run == 0:
                    break
                if run & 0x80:
                    run &= 0x7F
                    if pos >= len(data):
                        raise ContentError("internal error: truncated RLE repeated byte")
                    value = data[pos]
                    pos += 1
                    for _ in range(run):
                        output[dst] = value
                        dst += 2
                else:
                    if pos + run > len(data):
                        raise ContentError("internal error: truncated RLE literal")
                    for _ in range(run):
                        output[dst] = data[pos]
                        pos += 1
                        dst += 2
        else:
            high = mode
            if pos >= len(data):
                raise ContentError("internal error: truncated RLE 16-bit count")
            run = (high << 8) | data[pos]
            pos += 1
            while run != 0:
                if run & 0x8000:
                    run &= 0x7FFF
                    if pos >= len(data):
                        raise ContentError("internal error: truncated RLE 16-bit repeat")
                    value = data[pos]
                    pos += 1
                    for _ in range(run):
                        output[dst] = value
                        dst += 2
                else:
                    if pos + run > len(data):
                        raise ContentError("internal error: truncated RLE 16-bit literal")
                    for _ in range(run):
                        output[dst] = data[pos]
                        pos += 1
                        dst += 2
                if pos + 2 > len(data):
                    raise ContentError("internal error: truncated RLE 16-bit run count")
                run = (data[pos] << 8) | data[pos + 1]
                pos += 2
        if dst != count * 2 + pass_index:
            raise ContentError(
                "internal error: RLE pass %d wrote to %d, expected %d"
                % (pass_index, dst, count * 2 + pass_index)
            )

    if pos != len(data):
        raise ContentError("internal error: trailing bytes in RLE stream")

    values = [
        output[i * 2] | (output[i * 2 + 1] << 8)
        for i in range(count)
    ]
    return width, height, values


# ---------------------------------------------------------------------------
# Manifest


def parse_manifest(path: str | Path) -> dict[str, Any]:
    manifest_path = Path(path)
    manifest = expect_object(load_json(manifest_path, "room manifest"), "$")
    expect_keys(manifest, MANIFEST_KEYS, MANIFEST_KEYS, "$")
    if manifest["schema"] != MANIFEST_SCHEMA:
        raise ContentError(
            f"$.schema: expected {MANIFEST_SCHEMA!r}, got {manifest['schema']!r}"
        )

    room = expect_object(manifest["room"], "$.room")
    expect_keys(room, ROOM_KEYS, {"name", "area", "index", "tileset", "layers", "room_entry"}, "$.room")

    name = room["name"]
    if not isinstance(name, str) or not re.fullmatch(r"[A-Za-z0-9_.-]+", name):
        raise ContentError("$.room.name: expected a filename-safe name")
    area = room["area"]
    if not isinstance(area, str) or area not in AREA_NAMES:
        raise ContentError(
            "$.room.area: expected one of: " + ", ".join(sorted(AREA_NAMES))
        )
    index = as_int(room["index"], "$.room.index", 0, 254)

    tileset = expect_object(room["tileset"], "$.room.tileset")
    expect_keys(
        tileset,
        TILESET_KEYS,
        {"number", "image", "tile_pixels", "block_pixels", "colors_per_tile"},
        "$.room.tileset",
    )
    tileset_number = as_int(
        tileset["number"], "$.room.tileset.number", 0, MAX_TILESET_ENTRIES - 1
    )
    image = as_relative_path(tileset["image"], "$.room.tileset.image")
    tile_pixels = as_size_pair(tileset["tile_pixels"], "$.room.tileset.tile_pixels")
    block_pixels = as_size_pair(tileset["block_pixels"], "$.room.tileset.block_pixels")
    if block_pixels != (PIXEL_PER_BLOCK, PIXEL_PER_BLOCK):
        raise ContentError(
            "$.room.tileset.block_pixels: the engine block size is 16x16 "
            "(PIXEL_PER_BLOCK)"
        )
    colors_per_tile = as_int(
        tileset["colors_per_tile"], "$.room.tileset.colors_per_tile", 1, 16
    )
    transparent_index = tileset.get("transparent_index")
    if transparent_index is not None:
        transparent_index = as_int(
            transparent_index, "$.room.tileset.transparent_index", 0, 255
        )

    layers = expect_object(room["layers"], "$.room.layers")
    expect_keys(layers, LAYER_KEYS, {"bg1", "clip"}, "$.room.layers")
    for role, layer_name in layers.items():
        if layer_name is not None and (
            not isinstance(layer_name, str) or not layer_name
        ):
            raise ContentError(
                f"$.room.layers.{role}: expected a Tiled layer name or null"
            )
    if layers.get("bg0") is not None and layers["bg0"] == layers["bg1"]:
        raise ContentError("$.room.layers: bg0 and bg1 cannot use the same layer")

    mapping = room.get("tile_mapping", {})
    mapping = expect_object(mapping, "$.room.tile_mapping")
    unknown_roles = sorted(set(mapping) - LAYER_KEYS)
    if unknown_roles:
        raise ContentError(
            "$.room.tile_mapping: unknown layer role(s): " + ", ".join(unknown_roles)
        )
    normalised_mapping: dict[str, dict[int, int]] = {}
    for role, entries in mapping.items():
        if layers.get(role) is None:
            raise ContentError(
                f"$.room.tile_mapping.{role}: layer is not configured in $.room.layers"
            )
        entries = expect_object(entries, f"$.room.tile_mapping.{role}")
        resolved: dict[int, int] = {}
        for key, value in entries.items():
            try:
                gid = int(key, 0)
            except (TypeError, ValueError):
                raise ContentError(
                    f"$.room.tile_mapping.{role}: key {key!r} is not a tile GID"
                ) from None
            if gid < 0:
                raise ContentError(
                    f"$.room.tile_mapping.{role}: GID {gid} cannot be negative"
                )
            resolved[gid] = value
        normalised_mapping[role] = resolved

    entry = expect_object(room["room_entry"], "$.room.room_entry")
    expect_keys(
        entry,
        ROOM_ENTRY_KEYS,
        {"bg0_prop", "bg1_prop", "bg2_prop", "bg3_prop", "effect"},
        "$.room.room_entry",
    )

    room_entry: dict[str, Any] = {
        "tileset": tileset_number,
        "bg0_prop": resolve_flags(entry["bg0_prop"], BG_PROP_NAMES, "$.room.room_entry.bg0_prop"),
        "bg1_prop": resolve_flags(entry["bg1_prop"], BG_PROP_NAMES, "$.room.room_entry.bg1_prop"),
        "bg2_prop": resolve_flags(entry["bg2_prop"], BG_PROP_NAMES, "$.room.room_entry.bg2_prop"),
        "bg3_prop": resolve_flags(entry["bg3_prop"], BG_PROP_NAMES, "$.room.room_entry.bg3_prop"),
        "bg3_scrolling": as_int(entry.get("bg3_scrolling", 0), "$.room.room_entry.bg3_scrolling", 0, 255),
        "transparency": as_int(entry.get("transparency", 0), "$.room.room_entry.transparency", 0, 255),
        "effect": resolve_symbol(entry["effect"], EFFECT_NAMES, "$.room.room_entry.effect"),
        "effect_y": as_int(entry.get("effect_y", 255), "$.room.room_entry.effect_y", 0, 255),
        "music_track": as_int(entry.get("music_track", 0), "$.room.room_entry.music_track", 0, 0xFFFF),
        "map_x": as_int(entry.get("map_x", 0), "$.room.room_entry.map_x", 0, 255),
        "map_y": as_int(entry.get("map_y", 0), "$.room.room_entry.map_y", 0, 255),
        "first_spriteset_event": as_int(
            entry.get("first_spriteset_event", 0),
            "$.room.room_entry.first_spriteset_event", 0, 255,
        ),
        "second_spriteset_event": as_int(
            entry.get("second_spriteset_event", 0),
            "$.room.room_entry.second_spriteset_event", 0, 255,
        ),
        "default_spriteset": as_int(
            entry.get("default_spriteset", 255),
            "$.room.room_entry.default_spriteset", 0, 255,
        ),
        "first_spriteset": as_int(
            entry.get("first_spriteset", 255),
            "$.room.room_entry.first_spriteset", 0, 255,
        ),
        "second_spriteset": as_int(
            entry.get("second_spriteset", 255),
            "$.room.room_entry.second_spriteset", 0, 255,
        ),
    }
    if room_entry["effect"] < 0 or room_entry["effect"] > 0xFF:
        raise ContentError("$.room.room_entry.effect: value is outside 0..255")
    for field in ("bg0_prop", "bg1_prop", "bg2_prop", "bg3_prop"):
        if not 0 <= room_entry[field] <= 0xFF:
            raise ContentError(f"$.room.room_entry.{field}: value is outside 0..255")

    for role in ("bg0", "bg1", "bg2"):
        active = layers.get(role) is not None
        prop = room_entry[f"{role}_prop"]
        if active and not (prop & 0x10):
            raise ContentError(
                f"$.room.room_entry.{role}_prop: a generated {role} layer "
                "requires BG_PROP_RLE_COMPRESSED"
            )
        if not active and prop != 0:
            raise ContentError(
                f"$.room.room_entry.{role}_prop: {role} is not configured, "
                "so the property must be BG_PROP_NONE"
            )

    if room_entry["bg0_prop"] not in (0, 0x10):
        raise ContentError(
            "$.room.room_entry.bg0_prop: this scaffold only writes RLE bg0 "
            "layers or no bg0 layer"
        )

    camera = room.get("camera")
    scrolls: list[dict[str, int]] = []
    if camera is not None:
        camera = expect_object(camera, "$.room.camera")
        expect_keys(camera, CAMERA_KEYS, {"scrolls"}, "$.room.camera")
        raw_scrolls = camera["scrolls"]
        if not isinstance(raw_scrolls, list) or not 1 <= len(raw_scrolls) <= 2:
            raise ContentError(
                "$.room.camera.scrolls: expected 1 or 2 scroll records "
                "(gCurrentScrolls has two slots)"
            )
        for i, raw_scroll in enumerate(raw_scrolls):
            path = f"$.room.camera.scrolls[{i}]"
            raw_scroll = expect_object(raw_scroll, path)
            expect_keys(
                raw_scroll,
                SCROLL_KEYS,
                {"x_start", "x_end", "y_start", "y_end"},
                path,
            )
            scroll = {
                "x_start": as_int(raw_scroll["x_start"], path + ".x_start", 0, 254),
                "x_end": as_int(raw_scroll["x_end"], path + ".x_end", 0, 254),
                "y_start": as_int(raw_scroll["y_start"], path + ".y_start", 0, 254),
                "y_end": as_int(raw_scroll["y_end"], path + ".y_end", 0, 254),
                "breakable_x": as_int(raw_scroll.get("breakable_x", 255), path + ".breakable_x", 0, 255),
                "breakable_y": as_int(raw_scroll.get("breakable_y", 255), path + ".breakable_y", 0, 255),
                "extended_direction": as_int(raw_scroll.get("extended_direction", 255), path + ".extended_direction", 0, 255),
                "extended_value": as_int(raw_scroll.get("extended_value", 255), path + ".extended_value", 0, 255),
            }
            if scroll["x_start"] > scroll["x_end"]:
                raise ContentError(f"{path}: x_start must not exceed x_end")
            if scroll["y_start"] > scroll["y_end"]:
                raise ContentError(f"{path}: y_start must not exceed y_end")
            if scroll["extended_direction"] not in (0, 1, 2, 3, 255):
                raise ContentError(
                    f"{path}.extended_direction: expected 0..3 or 255"
                )
            scrolls.append(scroll)

    return {
        "path": manifest_path,
        "room": {
            "name": name,
            "area_name": area,
            "area": AREA_NAMES[area],
            "index": index,
        },
        "tileset": {
            "number": tileset_number,
            "image": image,
            "tile_pixels": tile_pixels,
            "block_pixels": block_pixels,
            "colors_per_tile": colors_per_tile,
            "transparent_index": transparent_index,
        },
        "layers": layers,
        "tile_mapping": normalised_mapping,
        "room_entry": room_entry,
        "scrolls": scrolls,
    }


# ---------------------------------------------------------------------------
# Tiled map


def decode_tile_data(layer: dict[str, Any], path: str) -> list[int]:
    data = layer.get("data")
    if data is None:
        raise ContentError(f"{path}: missing tile data (infinite/chunked maps are unsupported)")
    if isinstance(data, list):
        values = data
    elif isinstance(data, str):
        encoding = layer.get("encoding")
        if encoding != "base64":
            raise ContentError(f"{path}: unsupported tile encoding {encoding!r}")
        try:
            raw = base64.b64decode(data, validate=True)
        except (ValueError, base64.binascii.Error) as exc:
            raise ContentError(f"{path}: invalid base64 tile data: {exc}") from exc
        compression = layer.get("compression", "")
        try:
            if compression == "zlib":
                raw = zlib.decompress(raw)
            elif compression == "gzip":
                raw = gzip.decompress(raw)
            elif compression:
                raise ContentError(
                    f"{path}: unsupported tile compression {compression!r}"
                )
        except (zlib.error, OSError) as exc:
            raise ContentError(f"{path}: invalid compressed tile data: {exc}") from exc
        if len(raw) % 4 != 0:
            raise ContentError(f"{path}: base64 tile data is not a whole u32 array")
        values = list(struct.unpack("<%dI" % (len(raw) // 4), raw))
    else:
        raise ContentError(f"{path}: tile data must be an array or base64 string")

    return values


def parse_scroll_default(width: int, height: int) -> list[dict[str, int]]:
    return [{
        "x_start": 0,
        "x_end": width - 1,
        "y_start": 0,
        "y_end": height - 1,
        "breakable_x": 255,
        "breakable_y": 255,
        "extended_direction": 255,
        "extended_value": 255,
    }]


def parse_tiled_map(
    map_path: str | Path,
    manifest: dict[str, Any],
    png: pngio.PngImage,
    *,
    tile_count: int,
    block_count: int,
) -> dict[str, Any]:
    map_path = Path(map_path)
    data = expect_object(load_json(map_path, "Tiled map"), "$map")
    if data.get("orientation") != "orthogonal":
        raise ContentError("$map.orientation: only orthogonal maps are supported")
    if data.get("infinite"):
        raise ContentError("$map.infinite: infinite maps are unsupported; use a fixed map")
    width = as_positive_int(data.get("width"), "$map.width")
    height = as_positive_int(data.get("height"), "$map.height")
    if width > 255 or height > 255:
        raise ContentError(
            f"$map: room dimensions {width}x{height} exceed the one-byte "
            "RLE header limit (255x255)"
        )
    if width * height > MAX_ROOM_BLOCKS:
        raise ContentError(
            f"$map: {width * height} blocks exceed the {MAX_ROOM_BLOCKS}-entry "
            "decompression buffer"
        )
    block_width, block_height = manifest["tileset"]["block_pixels"]
    if (
        data.get("tilewidth") != block_width
        or data.get("tileheight") != block_height
    ):
        raise ContentError(
            f"$map: tile size {data.get('tilewidth')}x{data.get('tileheight')} "
            f"does not match the {block_width}x{block_height} engine block size"
        )

    layers = data.get("layers")
    if not isinstance(layers, list):
        raise ContentError("$map.layers: expected a list")

    tile_layers: dict[str, dict[str, Any]] = {}
    object_layers: dict[str, dict[str, Any]] = {}
    for index, layer in enumerate(layers):
        path = f"$map.layers[{index}]"
        layer = expect_object(layer, path)
        name = layer.get("name")
        if not isinstance(name, str) or not name:
            raise ContentError(f"{path}.name: expected a non-empty layer name")
        if name in tile_layers or name in object_layers:
            raise ContentError(
                f"$map.layers: duplicate layer name {name!r}; layer names must be unique"
            )
        layer_type = layer.get("type")
        if layer_type == "tilelayer":
            tile_layers[name] = layer
        elif layer_type == "objectgroup":
            object_layers[name] = layer
        else:
            raise ContentError(
                f"{path}: unsupported layer type {layer_type!r} "
                "(expected tilelayer or objectgroup)"
            )

    configured = {
        role: name
        for role, name in manifest["layers"].items()
        if name is not None
    }
    missing = sorted(set(configured.values()) - set(tile_layers))
    if missing:
        raise ContentError(
            "missing required tile layer(s): " + ", ".join(missing)
        )
    extra = sorted(set(tile_layers) - set(configured.values()))
    if extra:
        raise ContentError(
            "unmapped tile layer(s): "
            + ", ".join(extra)
            + " (add them to $.room.layers or remove them from the map)"
        )

    warnings: set[str] = set()
    layer_blocks: dict[str, list[int]] = {}
    clip_names = load_clipdata_names()

    for role in ("bg0", "bg1", "bg2", "clip"):
        layer_name = manifest["layers"].get(role)
        if layer_name is None:
            continue
        layer = tile_layers[layer_name]
        path = f"$map.layers[{layer_name!r}]"
        if layer.get("width") != width or layer.get("height") != height:
            raise ContentError(
                f"{path}: dimensions {layer.get('width')}x{layer.get('height')} "
                f"do not match the map {width}x{height}"
            )
        if layer.get("x", 0) != 0 or layer.get("y", 0) != 0:
            raise ContentError(f"{path}: layer offsets are unsupported")
        if layer.get("visible") is False:
            warnings.add(f"mapped layer {layer_name!r} is hidden in Tiled; its data is still used")
        if layer.get("opacity", 1) != 1:
            warnings.add(f"mapped layer {layer_name!r} has opacity {layer.get('opacity')}; ignored")
        raw = decode_tile_data(layer, path)
        if len(raw) != width * height:
            raise ContentError(
                f"{path}: has {len(raw)} tiles, expected {width * height} "
                f"for {width}x{height}"
            )
        mapping = manifest["tile_mapping"].get(role, {})
        used_mapping: set[int] = set()
        values: list[int] = []
        for index, gid in enumerate(raw):
            if isinstance(gid, bool) or not isinstance(gid, int):
                raise ContentError(f"{path}.data[{index}]: tile GID must be an integer")
            if gid < 0:
                raise ContentError(f"{path}.data[{index}]: negative tile GID {gid}")
            flags = gid & 0xF0000000
            if flags:
                raise ContentError(
                    f"{path}.data[{index}]: flipped/rotated GID 0x{gid:08X} "
                    "is unsupported; author unflipped tiles"
                )
            if gid > tile_count:
                raise ContentError(
                    f"{path}.data[{index}]: GID {gid} is outside the "
                    f"{tile_count}-tile PNG tileset"
                )
            if gid in mapping:
                value = mapping[gid]
                used_mapping.add(gid)
                if role == "clip":
                    value = resolve_symbol(
                        value, clip_names, f"$.room.tile_mapping.clip[{gid!r}]"
                    )
                    if not 0 <= value < MAX_CLIPDATA:
                        raise ContentError(
                            f"$.room.tile_mapping.clip[{gid!r}]: {value} is "
                            f"outside CLIPDATA_COUNT ({MAX_CLIPDATA})"
                        )
                else:
                    if isinstance(value, bool) or not isinstance(value, int):
                        raise ContentError(
                            f"$.room.tile_mapping.{role}[{gid!r}]: expected an "
                            "integer block ID or symbolic CLIPDATA name for clip"
                        )
                    if not 0 <= value <= 0xFFFF:
                        raise ContentError(
                            f"$.room.tile_mapping.{role}[{gid!r}]: block ID "
                            f"{value} is outside 0..65535"
                        )
                values.append(value)
            elif gid == 0:
                values.append(0)
            else:
                raise ContentError(
                    f"{path}.data[{index}]: unmapped tile GID {gid}; add a "
                    f"$.room.tile_mapping.{role} entry"
                )

        for gid in sorted(set(mapping) - used_mapping):
            if gid > tile_count:
                raise ContentError(
                    f"$.room.tile_mapping.{role}: GID {gid} is outside the "
                    f"{tile_count}-tile PNG tileset"
                )
            warnings.add(f"tile_mapping.{role} entry {gid} is unused")
        layer_blocks[role] = values

    doors: list[dict[str, Any]] = []
    spawns: list[dict[str, Any]] = []
    known_object_layers = {"doors", "spawns"}
    for name in sorted(set(object_layers) - known_object_layers):
        warnings.add(f"object group {name!r} is not used by the pipeline")

    sprite_ids = load_sprite_ids()
    max_sprite_id = max(sprite_ids.values()) if sprite_ids else MAX_SPRITE_ID_FALLBACK

    if "doors" in object_layers:
        objects = object_layers["doors"].get("objects", [])
        if not isinstance(objects, list):
            raise ContentError("$map.layers['doors'].objects: expected a list")
        ids: set[int] = set()
        for i, raw in enumerate(objects):
            path = f"$map.layers['doors'].objects[{i}]"
            raw = expect_object(raw, path)
            object_id = as_positive_int(raw.get("id"), path + ".id")
            if object_id in ids:
                raise ContentError(f"{path}.id: duplicate object id {object_id}")
            ids.add(object_id)
            if raw.get("rotation", 0) not in (0, None):
                raise ContentError(f"{path}.rotation: rotated doors are unsupported")
            if raw.get("point") is True:
                raise ContentError(
                    f"{path}: doors must be rectangle objects, not points"
                )
            x = raw.get("x")
            y = raw.get("y")
            w = raw.get("width")
            h = raw.get("height")
            if not all(isinstance(v, (int, float)) for v in (x, y, w, h)):
                raise ContentError(f"{path}: door rectangle needs numeric x, y, width, height")
            if x < 0 or y < 0 or w <= 0 or h <= 0:
                raise ContentError(f"{path}: door rectangle is outside the room")
            if (x % block_width) or (y % block_height) or (w % block_width) or (h % block_height):
                raise ContentError(
                    f"{path}: door rectangle must align to {block_width}x{block_height} blocks"
                )
            if x + w > width * block_width or y + h > height * block_height:
                raise ContentError(f"{path}: door rectangle extends outside the room")
            x_start = x // block_width
            x_end = (x + w) // block_width - 1
            y_start = y // block_height
            y_end = (y + h) // block_height - 1
            props = parse_object_properties(raw, path, DOOR_PROPERTY_KEYS)
            if "dst_door" not in props:
                raise ContentError(f"{path}: missing property 'dst_door'")
            door_type = resolve_flags(
                props.get("type", "DOOR_TYPE_NORMAL"),
                DOOR_TYPE_NAMES,
                path + ".properties.type",
            )
            src_room = as_int(
                props.get("src_room", manifest["room"]["index"]),
                path + ".properties.src_room", 0, 255,
            )
            dst_door = as_int(
                props["dst_door"], path + ".properties.dst_door", 0, 255
            )
            x_exit = as_int(
                props.get("x_exit", 0), path + ".properties.x_exit", -128, 127
            )
            y_exit = as_int(
                props.get("y_exit", 0), path + ".properties.y_exit", -128, 127
            )
            if not 0 <= door_type <= 0xFF:
                raise ContentError(f"{path}.properties.type: value is outside 0..255")
            doors.append({
                "id": object_id,
                "name": raw.get("name", ""),
                "type": door_type,
                "src_room": src_room,
                "x_start": x_start,
                "x_end": x_end,
                "y_start": y_start,
                "y_end": y_end,
                "dst_door": dst_door,
                "x_exit": x_exit,
                "y_exit": y_exit,
            })
        doors.sort(key=lambda door: door["id"])

    if "spawns" in object_layers:
        objects = object_layers["spawns"].get("objects", [])
        if not isinstance(objects, list):
            raise ContentError("$map.layers['spawns'].objects: expected a list")
        ids = set()
        for i, raw in enumerate(objects):
            path = f"$map.layers['spawns'].objects[{i}]"
            raw = expect_object(raw, path)
            object_id = as_positive_int(raw.get("id"), path + ".id")
            if object_id in ids:
                raise ContentError(f"{path}.id: duplicate object id {object_id}")
            ids.add(object_id)
            if raw.get("point") is not True:
                raise ContentError(f"{path}: spawns must be point objects")
            x = raw.get("x")
            y = raw.get("y")
            if not isinstance(x, (int, float)) or not isinstance(y, (int, float)):
                raise ContentError(f"{path}: spawn needs numeric x and y")
            if not (0 <= x < width * block_width and 0 <= y < height * block_height):
                raise ContentError(f"{path}: spawn point is outside the room")
            props = parse_object_properties(raw, path, SPAWN_PROPERTY_KEYS)
            if "sprite_id" not in props:
                raise ContentError(f"{path}: missing property 'sprite_id'")
            sprite_id = resolve_symbol(
                props["sprite_id"], sprite_ids, path + ".properties.sprite_id"
            )
            if not 0 <= sprite_id <= max_sprite_id:
                raise ContentError(
                    f"{path}.properties.sprite_id: {sprite_id} is outside "
                    f"0..{max_sprite_id}"
                )
            spriteset = props.get("spriteset", "default")
            if isinstance(spriteset, str):
                if spriteset not in ("default", "first", "second"):
                    raise ContentError(
                        f"{path}.properties.spriteset: expected default, first or second"
                    )
            elif spriteset in (0, 1, 2) and not isinstance(spriteset, bool):
                spriteset = {0: "default", 1: "first", 2: "second"}[spriteset]
            else:
                raise ContentError(
                    f"{path}.properties.spriteset: expected default, first or second"
                )
            slot = as_int(
                props.get("slot", 0), path + ".properties.slot", 0, 14
            )
            properties = resolve_flags(
                props.get("properties", 0),
                SPRITESET_PROPERTY_NAMES,
                path + ".properties.properties",
            )
            if not 0 <= properties <= 0xFF:
                raise ContentError(f"{path}.properties.properties: value is outside 0..255")
            spawns.append({
                "id": object_id,
                "name": raw.get("name", ""),
                "spriteset": spriteset,
                "y": y // block_height,
                "x": x // block_width,
                "sprite_id": sprite_id,
                "slot": slot,
                "properties": properties,
            })
        spawns.sort(key=lambda spawn: spawn["id"])

    scrolls = manifest["scrolls"]
    if not scrolls:
        scrolls = parse_scroll_default(width, height)
    for i, scroll in enumerate(scrolls):
        if scroll["x_end"] >= width or scroll["y_end"] >= height:
            raise ContentError(
                f"$.room.camera.scrolls[{i}]: bounds extend past the "
                f"{width}x{height} room"
            )

    first_sprites = sum(1 for spawn in spawns if spawn["spriteset"] == "first")
    second_sprites = sum(1 for spawn in spawns if spawn["spriteset"] == "second")
    if first_sprites and manifest["room_entry"]["first_spriteset_event"] == 0:
        raise ContentError(
            "$.room.room_entry.first_spriteset_event: first-spriteset spawns "
            "require a non-zero event"
        )
    if second_sprites and manifest["room_entry"]["second_spriteset_event"] == 0:
        raise ContentError(
            "$.room.room_entry.second_spriteset_event: second-spriteset spawns "
            "require a non-zero event"
        )
    if not first_sprites and manifest["room_entry"]["first_spriteset_event"]:
        warnings.add("first_spriteset_event is set but spriteset_first is empty")
    if not second_sprites and manifest["room_entry"]["second_spriteset_event"]:
        warnings.add("second_spriteset_event is set but spriteset_second is empty")

    return {
        "width": width,
        "height": height,
        "layers": layer_blocks,
        "doors": doors,
        "spawns": spawns,
        "scrolls": scrolls,
        "warnings": sorted(warnings),
    }


def parse_object_properties(
    obj: dict[str, Any], path: str, allowed: set[str]
) -> dict[str, Any]:
    raw_props = obj.get("properties", [])
    if raw_props is None:
        raw_props = []
    if not isinstance(raw_props, list):
        raise ContentError(f"{path}.properties: expected a list")
    props: dict[str, Any] = {}
    for i, item in enumerate(raw_props):
        item_path = f"{path}.properties[{i}]"
        item = expect_object(item, item_path)
        if set(item) != {"name", "type", "value"}:
            raise ContentError(
                f"{item_path}: expected exactly name, type and value"
            )
        name = item["name"]
        if not isinstance(name, str) or not name:
            raise ContentError(f"{item_path}.name: expected a non-empty string")
        if name in props:
            raise ContentError(f"{path}.properties: duplicate property {name!r}")
        if name not in allowed:
            raise ContentError(
                f"{path}.properties: unknown property {name!r}; allowed: "
                + ", ".join(sorted(allowed))
            )
        props[name] = item["value"]
    return props


# ---------------------------------------------------------------------------
# Output


def _json_bytes(value: Any) -> bytes:
    return (
        json.dumps(value, sort_keys=True, indent=2, ensure_ascii=True)
        + "\n"
    ).encode("ascii")


def _write_file(path: Path, data: bytes) -> None:
    try:
        path.write_bytes(data)
    except OSError as exc:
        raise ContentError(f"cannot write {path}: {exc}") from exc


def prepare_output_dir(out: Path, force: bool) -> None:
    if out.exists() and not out.is_dir():
        raise ContentError(f"output path {out} exists and is not a directory")
    if out.exists() and any(out.iterdir()):
        if not force:
            raise ContentError(
                f"output directory {out} is not empty; pass --force to overwrite "
                "the pipeline's own files"
            )
        for name in OUTPUT_FILENAMES:
            candidate = out / name
            if candidate.is_dir():
                raise ContentError(f"refusing to remove directory {candidate}")
            if candidate.exists():
                candidate.unlink()
    out.mkdir(parents=True, exist_ok=True)


OUTPUT_FILENAMES = (
    "room.json",
    "bg0.rle",
    "bg1.rle",
    "bg2.rle",
    "clipdata.rle",
    "scrolls.bin",
    "doors.bin",
    "spriteset_default.bin",
    "spriteset_first.bin",
    "spriteset_second.bin",
)


def pack_door(door: dict[str, Any]) -> bytes:
    head = bytes([
        door["type"],
        door["src_room"],
        door["x_start"],
        door["x_end"],
        door["y_start"],
        door["y_end"],
        door["dst_door"],
    ])
    try:
        return head + struct.pack("<bb", door["x_exit"], door["y_exit"])
    except struct.error as exc:
        raise ContentError(f"internal error: door cannot be packed: {exc}") from exc


def pack_spriteset(spawns: list[dict[str, Any]]) -> bytes:
    result = bytearray()
    for spawn in spawns:
        third = (spawn["properties"] & 0xF0) | ((spawn["slot"] + 1) & 0x0F)
        result.extend((spawn["y"], spawn["x"], third))
    result.extend(ROOM_SPRITE_DATA_TERMINATOR)
    return bytes(result)


def pack_scrolls(room_index: int, scrolls: list[dict[str, Any]]) -> bytes:
    if not 1 <= len(scrolls) <= 2:
        raise ContentError("internal error: expected 1 or 2 scroll records")
    result = bytearray([room_index, len(scrolls)])
    for scroll in scrolls:
        result.extend([
            scroll["x_start"],
            scroll["x_end"],
            scroll["y_start"],
            scroll["y_end"],
            scroll["breakable_x"],
            scroll["breakable_y"],
            scroll["extended_direction"],
            scroll["extended_value"],
        ])
    return bytes(result)


def _layer_output_key(role: str) -> str:
    return "clipdata" if role == "clip" else role


def write_outputs(
    out: Path,
    *,
    manifest: dict[str, Any],
    map_data: dict[str, Any],
    png: pngio.PngImage,
    tile_count: int,
    block_count: int,
    force: bool,
) -> dict[str, Any]:
    prepare_output_dir(out, force)

    width = map_data["width"]
    height = map_data["height"]
    room_entry = dict(manifest["room_entry"])
    role_for_file = {"bg0": "bg0", "bg1": "bg1", "bg2": "bg2", "clip": "clipdata"}

    output_info: dict[str, Any] = {}
    layer_json: dict[str, Any] = {}
    for role in ("bg0", "bg1", "bg2", "clip"):
        layer_name = manifest["layers"].get(role)
        if layer_name is None:
            continue
        values = map_data["layers"][role]
        rle = encode_rle_u16(values, width, height)
        output_key = role_for_file[role]
        filename = f"{output_key}.rle"
        _write_file(out / filename, rle)
        decoded_width, decoded_height, decoded = decode_rle_u16(rle)
        if (decoded_width, decoded_height, decoded) != (width, height, values):
            raise ContentError(f"internal error: {filename} does not round-trip")
        output_info[output_key] = {"file": filename, "bytes": len(rle)}
        layer_json[role] = {
            "tiled_layer": layer_name,
            "width": width,
            "height": height,
            "values": values,
            "rle_file": filename,
            "rle_bytes": len(rle),
        }

    scrolls = map_data["scrolls"]
    scroll_bytes = pack_scrolls(manifest["room"]["index"], scrolls)
    _write_file(out / "scrolls.bin", scroll_bytes)
    output_info["scrolls"] = {"file": "scrolls.bin", "bytes": len(scroll_bytes)}

    doors = map_data["doors"]
    door_bytes = b"".join(pack_door(door) for door in doors)
    _write_file(out / "doors.bin", door_bytes)
    output_info["doors"] = {"file": "doors.bin", "bytes": len(door_bytes), "count": len(doors)}

    spritesets: dict[str, Any] = {}
    for set_name in ("default", "first", "second"):
        members = [spawn for spawn in map_data["spawns"] if spawn["spriteset"] == set_name]
        bytes_for_set = pack_spriteset(members)
        filename = f"spriteset_{set_name}.bin"
        _write_file(out / filename, bytes_for_set)
        spritesets[set_name] = {
            "file": filename,
            "bytes": len(bytes_for_set),
            "count": len(members),
            "records": [
                {
                    "id": spawn["id"],
                    "name": spawn["name"],
                    "y": spawn["y"],
                    "x": spawn["x"],
                    "sprite_id": spawn["sprite_id"],
                    "slot": spawn["slot"],
                    "properties": spawn["properties"],
                }
                for spawn in members
            ],
        }
        output_info[f"spriteset_{set_name}"] = {
            "file": filename, "bytes": len(bytes_for_set), "count": len(members)
        }

    result = {
        "schema": ROOM_SCHEMA,
        "room": manifest["room"],
        "dimensions": {
            "width_blocks": width,
            "height_blocks": height,
            "block_width": manifest["tileset"]["block_pixels"][0],
            "block_height": manifest["tileset"]["block_pixels"][1],
            "width_pixels": width * manifest["tileset"]["block_pixels"][0],
            "height_pixels": height * manifest["tileset"]["block_pixels"][1],
        },
        "tileset": {
            "number": manifest["tileset"]["number"],
            "image": Path(manifest["tileset"]["image"]).name,
            "tile_width": manifest["tileset"]["tile_pixels"][0],
            "tile_height": manifest["tileset"]["tile_pixels"][1],
            "block_width": manifest["tileset"]["block_pixels"][0],
            "block_height": manifest["tileset"]["block_pixels"][1],
            "tile_count": tile_count,
            "block_count": block_count,
            "colors": len(png.palette) if png.color_type == 3 else png.color_type_name,
            "transparent_index": manifest["tileset"]["transparent_index"],
        },
        "room_entry": room_entry,
        "layers": layer_json,
        "scrolls": {"file": "scrolls.bin", "records": scrolls},
        "doors": {
            "file": "doors.bin",
            "count": len(doors),
            "records": doors,
        },
        "spritesets": spritesets,
        "outputs": output_info,
        "warnings": map_data["warnings"],
    }
    _write_file(out / "room.json", _json_bytes(result))
    return result


# ---------------------------------------------------------------------------
# Driver


def run_pipeline(
    map_path: str | Path,
    manifest_path: str | Path,
    out: str | Path,
    *,
    tileset_override: str | Path | None = None,
    force: bool = False,
) -> dict[str, Any]:
    manifest = parse_manifest(manifest_path)

    image_path = (
        Path(tileset_override)
        if tileset_override is not None
        else Path(manifest_path).resolve().parent / manifest["tileset"]["image"]
    )
    try:
        png = pngio.read_png(image_path)
    except pngio.PngError as exc:
        raise ContentError(f"tileset PNG: {exc}") from exc

    tile_width, tile_height = manifest["tileset"]["tile_pixels"]
    block_width, block_height = manifest["tileset"]["block_pixels"]
    try:
        tile_count, block_count = pngio.validate_tileset_image(
            png,
            tile_width=tile_width,
            tile_height=tile_height,
            block_width=block_width,
            block_height=block_height,
            colors_per_tile=manifest["tileset"]["colors_per_tile"],
            transparent_index=manifest["tileset"]["transparent_index"],
        )
    except pngio.PngError as exc:
        raise ContentError(f"tileset PNG: {exc}") from exc

    map_data = parse_tiled_map(
        map_path, manifest, png, tile_count=tile_count, block_count=block_count
    )
    return write_outputs(
        Path(out),
        manifest=manifest,
        map_data=map_data,
        png=png,
        tile_count=tile_count,
        block_count=block_count,
        force=force,
    )


def summary(result: dict[str, Any]) -> list[str]:
    room = result["room"]
    dimensions = result["dimensions"]
    lines = [
        f"room: {room['name']} ({room['area_name']} #{room['index']}) "
        f"{dimensions['width_blocks']}x{dimensions['height_blocks']} blocks",
        "layers: " + ", ".join(
            f"{role}={len(layer['values'])}"
            for role, layer in result["layers"].items()
        ),
        f"doors: {result['doors']['count']}, "
        f"sprites: {sum(s['count'] for s in result['spritesets'].values())}, "
        f"scrolls: {len(result['scrolls']['records'])}",
    ]
    for warning in result["warnings"]:
        lines.append(f"warning: {warning}")
    lines.append("CONTENT: PASS")
    return lines


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Convert a Tiled JSON room + PNG tileset into room data."
    )
    parser.add_argument("--map", help="Tiled JSON map (.tmj/.json)")
    parser.add_argument("--manifest", help="room manifest JSON")
    parser.add_argument("--out", help="output directory")
    parser.add_argument(
        "--tileset",
        help="override tileset PNG (default: the manifest's image path)",
    )
    parser.add_argument(
        "--force",
        action="store_true",
        help="overwrite the pipeline's own output files in a non-empty directory",
    )
    parser.add_argument(
        "--self-check",
        action="store_true",
        help="run the synthetic fixture round-trip and invalid-input tests",
    )
    args = parser.parse_args(argv)

    if args.self_check:
        if args.map or args.manifest or args.out:
            parser.error("--self-check does not accept --map/--manifest/--out")
        return self_check()

    missing = [
        flag
        for flag, value in (
            ("--map", args.map),
            ("--manifest", args.manifest),
            ("--out", args.out),
        )
        if not value
    ]
    if missing:
        parser.error("missing required argument(s): " + ", ".join(missing))

    try:
        result = run_pipeline(
            args.map,
            args.manifest,
            args.out,
            tileset_override=args.tileset,
            force=args.force,
        )
    except ContentError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2
    except OSError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2

    print(f"wrote {len(result['outputs']) + 1} files to {Path(args.out)}")
    for line in summary(result):
        print(line)
    return 0


# ---------------------------------------------------------------------------
# Self-check


def _mutate_json(value: Any, mutate) -> Any:
    clone = json.loads(json.dumps(value))
    mutate(clone)
    return clone


def _write_json(path: Path, value: Any) -> None:
    path.write_bytes(_json_bytes(value))


def _expect_failure(args: list[str], needle: str, label: str) -> None:
    stderr = io.StringIO()
    with contextlib.redirect_stderr(stderr):
        code = main(args)
    if code != 2:
        raise AssertionError(f"{label}: expected exit 2, got {code}")
    message = stderr.getvalue()
    if needle not in message:
        raise AssertionError(
            f"{label}: expected error containing {needle!r}, got {message!r}"
        )


def self_check() -> int:
    fixture_map = FIXTURES / "fixture_room.tmj"
    fixture_manifest = FIXTURES / "fixture_room.room.json"
    fixture_png = FIXTURES / "fixture_tileset.png"

    try:
        for path in (fixture_map, fixture_manifest, fixture_png):
            if not path.exists():
                raise AssertionError(f"missing fixture {path}")

        with tempfile.TemporaryDirectory(prefix="mf-content-check-") as tmp:
            tmp_path = Path(tmp)
            out_a = tmp_path / "a"
            out_b = tmp_path / "b"
            stdout = io.StringIO()
            with contextlib.redirect_stdout(stdout):
                code = main([
                    "--map", str(fixture_map),
                    "--manifest", str(fixture_manifest),
                    "--out", str(out_a),
                ])
            if code != 0:
                raise AssertionError(f"fixture run failed:\n{stdout.getvalue()}")
            with contextlib.redirect_stdout(io.StringIO()):
                code = main([
                    "--map", str(fixture_map),
                    "--manifest", str(fixture_manifest),
                    "--out", str(out_b),
                ])
            if code != 0:
                raise AssertionError("second fixture run failed")

            files_a = sorted(p.relative_to(out_a) for p in out_a.rglob("*") if p.is_file())
            files_b = sorted(p.relative_to(out_b) for p in out_b.rglob("*") if p.is_file())
            if files_a != files_b:
                raise AssertionError(f"output file sets differ: {files_a} vs {files_b}")
            for relative in files_a:
                if (out_a / relative).read_bytes() != (out_b / relative).read_bytes():
                    raise AssertionError(f"non-deterministic output: {relative}")

            result = json.loads((out_a / "room.json").read_text(encoding="utf-8"))
            if result["dimensions"]["width_blocks"] != 8:
                raise AssertionError("fixture width changed")
            if result["dimensions"]["height_blocks"] != 6:
                raise AssertionError("fixture height changed")
            if result["doors"]["count"] != 2:
                raise AssertionError("fixture door count changed")
            if len((out_a / "doors.bin").read_bytes()) != 18:
                raise AssertionError("fixture door bytes changed")
            if len((out_a / "spriteset_default.bin").read_bytes()) != 6:
                raise AssertionError("fixture default spriteset bytes changed")
            if len((out_a / "spriteset_first.bin").read_bytes()) != 6:
                raise AssertionError("fixture first spriteset bytes changed")
            if len((out_a / "scrolls.bin").read_bytes()) != 10:
                raise AssertionError("fixture scroll bytes changed")

            for role in ("bg1", "bg2", "clip"):
                layer = result["layers"][role]
                rle = (out_a / layer["rle_file"]).read_bytes()
                width, height, values = decode_rle_u16(rle)
                if (width, height) != (8, 6) or values != layer["values"]:
                    raise AssertionError(f"{role} RLE round-trip failed")

            map_data = load_json(fixture_map, "fixture map")
            manifest_data = load_json(fixture_manifest, "fixture manifest")
            invalid_cases = 0

            def add_case(label: str, needle: str, map_value=None, manifest_value=None) -> None:
                nonlocal invalid_cases
                map_path = fixture_map
                manifest_path = fixture_manifest
                extra: list[str] = []
                if map_value is not None:
                    map_path = tmp_path / f"bad_map_{invalid_cases}.tmj"
                    _write_json(map_path, map_value)
                if manifest_value is not None:
                    manifest_path = tmp_path / f"bad_manifest_{invalid_cases}.json"
                    _write_json(manifest_path, manifest_value)
                    extra = ["--tileset", str(fixture_png)]
                _expect_failure(
                    [
                        "--map", str(map_path),
                        "--manifest", str(manifest_path),
                        "--out", str(tmp_path / f"bad_out_{invalid_cases}"),
                        *extra,
                    ],
                    needle,
                    label,
                )
                invalid_cases += 1

            def drop_collision(value: dict[str, Any]) -> None:
                value["layers"] = [
                    layer for layer in value["layers"] if layer["name"] != "collision"
                ]

            add_case(
                "missing layer",
                "missing required tile layer",
                map_value=_mutate_json(map_data, drop_collision),
            )

            def bad_gid(value: dict[str, Any]) -> None:
                for layer in value["layers"]:
                    if layer["name"] == "bg1":
                        layer["data"][0] = 99
                        return

            add_case(
                "GID out of bounds",
                "outside the 8-tile PNG tileset",
                map_value=_mutate_json(map_data, bad_gid),
            )

            def wrong_tile_size(value: dict[str, Any]) -> None:
                value["tilewidth"] = 8

            add_case(
                "wrong tile size",
                "does not match the 16x16 engine block size",
                map_value=_mutate_json(map_data, wrong_tile_size),
            )

            def wrong_layer_width(value: dict[str, Any]) -> None:
                for layer in value["layers"]:
                    if layer["name"] == "bg1":
                        layer["width"] = 7
                        return

            add_case(
                "layer dimension mismatch",
                "do not match the map",
                map_value=_mutate_json(map_data, wrong_layer_width),
            )

            def bad_clip_value(value: dict[str, Any]) -> None:
                value["room"]["tile_mapping"]["clip"]["1"] = 999

            add_case(
                "clipdata out of range",
                "outside CLIPDATA_COUNT",
                manifest_value=_mutate_json(manifest_data, bad_clip_value),
            )

            def missing_door_property(value: dict[str, Any]) -> None:
                for layer in value["layers"]:
                    if layer["name"] == "doors":
                        layer["objects"][0]["properties"] = [
                            prop for prop in layer["objects"][0]["properties"]
                            if prop["name"] != "dst_door"
                        ]
                        return

            add_case(
                "missing door property",
                "missing property 'dst_door'",
                map_value=_mutate_json(map_data, missing_door_property),
            )

            def duplicate_door_property(value: dict[str, Any]) -> None:
                for layer in value["layers"]:
                    if layer["name"] == "doors":
                        layer["objects"][0]["properties"].append(
                            {"name": "dst_door", "type": "int", "value": 1}
                        )
                        return

            add_case(
                "duplicate door property",
                "duplicate property 'dst_door'",
                map_value=_mutate_json(map_data, duplicate_door_property),
            )

            # Duplicate JSON keys are rejected before schema validation.
            duplicate_key_manifest = tmp_path / "duplicate_key.json"
            duplicate_key_manifest.write_text(
                '{"schema": "%s", "schema": "%s", "room": {}}\n'
                % (MANIFEST_SCHEMA, MANIFEST_SCHEMA),
                encoding="utf-8",
            )
            _expect_failure(
                [
                    "--map", str(fixture_map),
                    "--manifest", str(duplicate_key_manifest),
                    "--out", str(tmp_path / "duplicate_key_out"),
                    "--tileset", str(fixture_png),
                ],
                "duplicate JSON key",
                "duplicate manifest key",
            )
            invalid_cases += 1

            # A 4bpp palette overflow in one 8x8 tile must be rejected.
            bad_png = tmp_path / "bad_palette.png"
            palette = [(i, i, i) for i in range(17)]
            # The first 8x8 GBA tile contains all 17 indices, so it exceeds
            # the 16-colour 4bpp budget while the image itself is still valid.
            pixels = [[(y * 8 + x) % 17 for x in range(16)] for y in range(16)]
            pngio.write_indexed_png(bad_png, 16, 16, palette, pixels)
            bad_png_manifest = tmp_path / "bad_png_manifest.json"
            manifest_clone = json.loads(json.dumps(manifest_data))
            manifest_clone["room"]["tileset"]["image"] = bad_png.name
            _write_json(bad_png_manifest, manifest_clone)
            _expect_failure(
                [
                    "--map", str(fixture_map),
                    "--manifest", str(bad_png_manifest),
                    "--out", str(tmp_path / "bad_png_out"),
                    "--tileset", str(bad_png),
                ],
                "budget is 16",
                "palette budget",
            )
            invalid_cases += 1

            # Non-empty output needs --force, and --force stays deterministic.
            _expect_failure(
                [
                    "--map", str(fixture_map),
                    "--manifest", str(fixture_manifest),
                    "--out", str(out_a),
                ],
                "is not empty",
                "non-empty output directory",
            )
            invalid_cases += 1
            with contextlib.redirect_stdout(io.StringIO()):
                code = main([
                    "--map", str(fixture_map),
                    "--manifest", str(fixture_manifest),
                    "--out", str(out_a),
                    "--force",
                ])
            if code != 0:
                raise AssertionError("--force run failed")
            for relative in files_a:
                reference = out_b / relative
                if (out_a / relative).read_bytes() != reference.read_bytes():
                    raise AssertionError(f"--force changed output: {relative}")

        print(
            "CONTENT-CHECK: PASS "
            f"(determinism + {invalid_cases} invalid-input cases)"
        )
        return 0
    except AssertionError as exc:
        print(f"CONTENT-CHECK: FAIL: {exc}", file=sys.stderr)
        return 1
    except ContentError as exc:
        print(f"CONTENT-CHECK: FAIL: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
