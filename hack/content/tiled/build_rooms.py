#!/usr/bin/env python3
"""Build the five Sector Null blockout Tiled maps and room manifests.

The generated files are committed source assets: a Tiled JSON map (``.tmj``)
and an ``mf-hack.room-manifest/v1`` manifest for each room.  The Tiled files
are produced by this script so the room geometry, door table and spawn table
stay consistent; the converter still consumes the committed Tiled/manifest
pair, never this script.

Usage::

    python3 hack/content/tiled/build_rooms.py --check
    python3 hack/content/tiled/build_rooms.py --write

All geometry is synthetic blockout geometry.  No ROM art, text or audio is
encoded.
"""

from __future__ import annotations

import argparse
import json
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any


HERE = Path(__file__).resolve().parent
TILE = 16
TILESET_IMAGE = "blockout_tileset.png"

# Tileset GIDs.  The PNG is a 4x4 grid of 16x16 tiles; block IDs are GID - 1.
EMPTY = 1
SOLID = 2
FLOOR = 3
PLATFORM = 4
DARK = 5
LIGHT = 6
DOOR_TILE = 7
CONSOLE = 8
PIPE = 9
HAZARD = 10
PULSE = 11
GRATE = 12
CABLE = 13
RUBBLE = 14
MARKER = 15
MIST = 16

# Collision-layer GIDs.  The manifest maps these to symbolic clipdata values.
CLIP_SOLID = 1
CLIP_AIR = 2
CLIP_DOOR = 3

# Role -> block index in the generated blockout tileset.  ``gen_tileset.py``
# packs the PNG's 4x4 grid row-major, so PNG block B becomes tileset block B:
# RoomLoadTileset reads ``(u16*)tileset.pTilemap + 1``, the generated tilemap
# has four TL/TR/BL/BR entries per block, and block B selects tiles
# ``0xC0 + B*4 .. 0xC0 + B*4 + 3`` with palette bank 4.  Every authored role
# therefore maps to its own readable synthetic tile; the blockout no longer
# borrows vanilla Test Area 1 blocks.  The synthetic PNG GIDs remain the
# authoring key and are never written to the ROM.
#
#   block 0  - EMPTY     transparent void
#   block 1  - SOLID     room shell / solid wall
#   block 2  - FLOOR     floor surface band
#   block 3  - PLATFORM  ledge / platform
#   block 4  - DARK      dark background panel
#   block 5  - LIGHT     working light
#   block 6  - DOOR_TILE door frame
#   block 7  - CONSOLE   terminal
#   block 8  - PIPE      pipe run
#   block 9  - HAZARD    hazard stripe
#   block 10 - PULSE     pulse-only geometry (non-solid)
#   block 11 - GRATE     grate
#   block 12 - CABLE     cable
#   block 13 - RUBBLE    rubble
#   block 14 - MARKER    marker
#   block 15 - MIST      haze / mist
BLOCK_BY_GID: dict[int, int] = {
    EMPTY: 0,
    SOLID: 1,
    FLOOR: 2,
    PLATFORM: 3,
    DARK: 4,
    LIGHT: 5,
    DOOR_TILE: 6,
    CONSOLE: 7,
    PIPE: 8,
    HAZARD: 9,
    PULSE: 10,
    GRATE: 11,
    CABLE: 12,
    RUBBLE: 13,
    MARKER: 14,
    MIST: 15,
}

# Vanilla Test Area 1 rooms use the LZ77-compressed sBg3_TestRoom backdrop (a
# blue-grid 256x256 map) with bg3Scrolling 1; sBg3_TestRoom is declared in
# include/data/rooms/test_rooms_data.h.
BG3_PROP = "BG_PROP_LZ77_COMPRESSED"
BG3_SCROLLING = 1

NO_HATCH = "DOOR_TYPE_NORMAL | DOOR_TYPE_NO_HATCH"
HATCH = "DOOR_TYPE_NORMAL | DOOR_TYPE_HATCH_CAN_LOCK"

# One canonical default-spriteset table for every room.  HACK-004a2 can load
# this table once into gSpritesetSpriteIds instead of maintaining per-room
# copies.  Slot 0 must remain the save pad (the fixture uses the same slot).
SPRITE_SLOTS: dict[int, str] = {
    0: "PSPRITE_SAVE_PAD",
    1: "PSPRITE_DATA_PAD",
    2: "PSPRITE_HORNOAD",
    3: "PSPRITE_GERON_MISSILE_1",
    4: "PSPRITE_BOX",
    5: "PSPRITE_MESSAGE_BANNER",
    6: "SPRITE_ECHO_HUNTER",
}
SPRITE_SLOT_BY_NAME = {name: slot for slot, name in SPRITE_SLOTS.items()}


@dataclass
class Door:
    index: int
    room: int
    dst: int
    x: int
    y: int
    w: int
    h: int
    x_exit: int
    y_exit: int
    kind: str
    note: str = ""


@dataclass
class Spawn:
    name: str
    sprite: str
    x: int
    y: int
    note: str = ""


@dataclass
class Room:
    name: str
    index: int
    width: int
    height: int
    floor_y: int
    map_x: int
    map_y: int
    bg1: list[list[int]] = field(init=False)
    bg2: list[list[int]] = field(init=False)
    clip: list[list[int]] = field(init=False)
    doors: list[int] = field(default_factory=list)
    spawns: list[Spawn] = field(default_factory=list)
    scrolls: list[dict[str, int]] = field(default_factory=list)
    notes: list[str] = field(default_factory=list)

    def __post_init__(self) -> None:
        self.bg1 = [[0] * self.width for _ in range(self.height)]
        self.bg2 = [[0] * self.width for _ in range(self.height)]
        self.clip = [[CLIP_AIR] * self.width for _ in range(self.height)]

    def rect(self, grid: list[list[int]], x: int, y: int, w: int, h: int, value: int) -> None:
        assert w > 0 and h > 0, (self.name, x, y, w, h)
        assert 0 <= x <= self.width - w, (self.name, "rect x", x, w, self.width)
        assert 0 <= y <= self.height - h, (self.name, "rect y", y, h, self.height)
        for yy in range(y, y + h):
            for xx in range(x, x + w):
                grid[yy][xx] = value

    def shell(self) -> None:
        # Background fill, then the solid room shell.
        self.rect(self.bg1, 1, 1, self.width - 2, self.floor_y - 1, DARK)
        self.rect(self.bg1, 0, 0, self.width, 1, SOLID)
        self.rect(self.bg1, 0, self.floor_y, self.width, self.height - self.floor_y, SOLID)
        self.rect(self.bg1, 0, 0, 1, self.height, SOLID)
        self.rect(self.bg1, self.width - 1, 0, 1, self.height, SOLID)

        self.rect(self.clip, 0, 0, self.width, 1, CLIP_SOLID)
        self.rect(self.clip, 0, self.floor_y, self.width, self.height - self.floor_y, CLIP_SOLID)
        self.rect(self.clip, 0, 0, 1, self.height, CLIP_SOLID)
        self.rect(self.clip, self.width - 1, 0, 1, self.height, CLIP_SOLID)

    def floor_edge(self) -> None:
        self.rect(self.bg2, 1, self.floor_y, self.width - 2, 1, FLOOR)

    def platform(self, x: int, y: int, w: int) -> None:
        self.rect(self.bg2, x, y, w, 1, PLATFORM)
        self.rect(self.clip, x, y, w, 1, CLIP_SOLID)

    def pulse_platform(self, x: int, y: int, w: int) -> None:
        # Pulse-only geometry is non-solid in the blockout so optional routes
        # can never soft-lock an M1 playtest.  HACK-004b/d replaces the clip
        # with an event-gated collision change.
        self.rect(self.bg2, x, y, w, 1, PULSE)

    def pulse_block(self, x: int, y: int, w: int, h: int) -> None:
        self.rect(self.bg2, x, y, w, h, PULSE)

    def door(self, index: int, x: int, y: int, w: int, h: int) -> None:
        self.rect(self.bg2, x, y, w, h, DOOR_TILE)
        self.rect(self.clip, x, y, w, h, CLIP_DOOR)
        self.doors.append(index)

    def prop(self, x: int, y: int, value: int, w: int = 1, h: int = 1) -> None:
        self.rect(self.bg2, x, y, w, h, value)

    def bg_prop(self, x: int, y: int, value: int, w: int = 1, h: int = 1) -> None:
        self.rect(self.bg1, x, y, w, h, value)

    def spawn(self, name: str, sprite: str, x: int, y: int, note: str = "") -> None:
        assert 0 <= x < self.width and 0 <= y < self.height, (self.name, name, x, y)
        assert sprite in SPRITE_SLOT_BY_NAME, (self.name, name, sprite)
        self.spawns.append(Spawn(name, sprite, x, y, note))

    def scroll(self, x0: int, x1: int, y0: int, y1: int) -> None:
        self.scrolls.append({
            "x_start": x0,
            "x_end": x1,
            "y_start": y0,
            "y_end": y1,
            "breakable_x": 255,
            "breakable_y": 255,
            "extended_direction": 255,
            "extended_value": 255,
        })


DOORS: dict[int, Door] = {}


def add_door(
    index: int,
    room: Room,
    dst: int,
    x: int,
    y: int,
    w: int,
    h: int,
    x_exit: int,
    y_exit: int,
    kind: str,
    note: str = "",
) -> None:
    assert index not in DOORS, f"duplicate door index {index}"
    assert 0 <= x <= room.width - w and 0 <= y <= room.height - h, (room.name, index)
    assert w in (1, 2) and h in (1, 2), (room.name, index, w, h)
    DOORS[index] = Door(index, room.index, dst, x, y, w, h, x_exit, y_exit, kind, note)
    room.door(index, x, y, w, h)


def build_rooms() -> list[Room]:
    DOORS.clear()

    # ------------------------------------------------------------------
    # Room 0: Entry Ledge — 1x1 screen, save pad, no combat.
    entry = Room("entry_ledge", 0, 15, 10, 8, 0, 2)
    entry.shell()
    entry.floor_edge()
    add_door(0, entry, 1, 14, 6, 1, 2, -TILE, 0, NO_HATCH, "right exit to Silent Atrium")
    # Blockout-only return pair: appended after the provisional 0-9 map so the
    # five-room set satisfies the two-door-per-room constraint and closes the
    # slice loop after the Cantor.  Requires design/ID sign-off in HACK-004a2.
    add_door(11, entry, 10, 0, 6, 1, 2, TILE, 0, HATCH, "post-boss return from Choir Nest")
    entry.prop(6, 1, LIGHT)
    entry.prop(10, 1, RUBBLE)
    entry.prop(10, 2, RUBBLE)
    entry.prop(12, 7, RUBBLE)
    entry.bg_prop(3, 3, PIPE, 2, 1)
    entry.bg_prop(9, 4, CABLE)
    entry.spawn("save_pad", "PSPRITE_SAVE_PAD", 3, 7, "only save pad in the slice")
    entry.spawn("log_deck_07", "PSPRITE_DATA_PAD", 9, 7, "Deck 07 sealed log placeholder")
    # Third spawn record = in-area message_id 2 (HACK-008d2); keep it third.
    entry.spawn("signal_banner", "PSPRITE_MESSAGE_BANNER", 6, 4, "scripted signal banner placeholder")
    entry.spawn("echo_hunter", "SPRITE_ECHO_HUNTER", 12, 8, "Echo Hunter proxy spawn")
    entry.scroll(0, 14, 0, 9)
    entry.notes.append("dark room look is authored in tiles; engine dark-room flag is a HACK-004a2 todo")

    # ------------------------------------------------------------------
    # Room 1: Silent Atrium — 1x3 screens, vertical set-piece.
    atrium = Room("silent_atrium", 1, 15, 30, 28, 1, 0)
    atrium.shell()
    atrium.floor_edge()
    add_door(1, atrium, 0, 0, 26, 1, 2, TILE, 0, NO_HATCH, "lower-left entry from Entry Ledge")
    add_door(2, atrium, 3, 14, 2, 1, 2, -TILE, 0, HATCH, "top-right exit to Resonance Chamber")
    add_door(9, atrium, 8, 14, 12, 1, 2, -TILE, 0, HATCH, "two-way Conduit shortcut landing")

    # Main climb.  Three-block vertical gaps; two-block headroom under each
    # ledge so the lower route remains walkable.
    atrium.platform(2, 25, 5)
    atrium.platform(8, 22, 5)
    atrium.platform(2, 19, 5)
    atrium.platform(8, 17, 5)
    atrium.platform(9, 14, 5)   # landing outside the Conduit shortcut door
    atrium.platform(2, 13, 5)
    atrium.platform(8, 10, 5)
    atrium.platform(2, 7, 5)
    atrium.platform(8, 4, 6)    # reaches the top-right door landing

    # Hidden upper-left route: pulse-only ledge + optional log/missile.
    atrium.pulse_platform(1, 4, 5)
    atrium.spawn("atrium_log", "PSPRITE_DATA_PAD", 3, 3, "optional archaeology log placeholder")
    atrium.spawn("atrium_missile", "PSPRITE_GERON_MISSILE_1", 4, 3, "optional missile tank placeholder")
    atrium.spawn("echo_hunter", "PSPRITE_HORNOAD", 9, 27, "Echo Hunter AI placeholder")

    atrium.prop(7, 1, LIGHT)
    atrium.prop(3, 15, RUBBLE)
    atrium.prop(4, 15, RUBBLE)
    atrium.prop(12, 20, GRATE, 1, 2)
    atrium.prop(1, 22, PIPE, 1, 4)
    atrium.bg_prop(10, 6, CABLE, 1, 3)
    atrium.bg_prop(3, 12, MIST, 3, 2)
    atrium.bg_prop(11, 24, MIST, 2, 2)
    atrium.scroll(0, 14, 0, 29)
    atrium.notes.append("single full-room scroll: gCurrentScrolls has two slots and this room is three screens tall")

    # ------------------------------------------------------------------
    # Room 2: Resonance Chamber — 2x1 screens, pulse pickup.
    resonance = Room("resonance_chamber", 2, 30, 10, 8, 2, 0)
    resonance.shell()
    resonance.floor_edge()
    add_door(3, resonance, 2, 0, 6, 1, 2, TILE, 0, HATCH, "left entry from Silent Atrium")
    add_door(4, resonance, 5, 29, 6, 1, 2, -TILE, 0, HATCH, "sealed right exit to Hidden Conduit")

    resonance.platform(14, 7, 3)
    resonance.spawn("pulse_pedestal", "PSPRITE_DATA_PAD", 15, 6, "Resonance Pulse pickup placeholder")
    resonance.spawn("pulse_reveal_banner", "PSPRITE_MESSAGE_BANNER", 15, 2, "scripted reveal placeholder")
    resonance.prop(8, 1, LIGHT)
    resonance.prop(22, 1, LIGHT)
    resonance.prop(22, 2, RUBBLE)
    resonance.prop(12, 7, CONSOLE, 2, 1)
    resonance.prop(17, 7, CONSOLE, 2, 1)
    resonance.prop(18, 8, GRATE, 3, 1)
    resonance.prop(19, 7, MARKER)
    resonance.bg_prop(1, 2, PIPE, 7, 1)
    resonance.bg_prop(23, 2, PIPE, 4, 1)
    resonance.bg_prop(26, 3, CABLE, 1, 4)
    resonance.scroll(0, 14, 0, 9)
    resonance.scroll(15, 29, 0, 9)
    resonance.notes.append("one-way drop to Atrium is marked but has no content-ids door ID; HACK-004a2/design must allocate it")

    # ------------------------------------------------------------------
    # Room 3: Hidden Conduit — 3x1 screens, pulse/stealth combination.
    conduit = Room("hidden_conduit", 3, 45, 10, 8, 4, 0)
    conduit.shell()
    conduit.floor_edge()
    add_door(5, conduit, 4, 0, 6, 1, 2, TILE, 0, HATCH, "left entry from Resonance Chamber")
    add_door(6, conduit, 7, 44, 6, 1, 2, -TILE, 0, HATCH, "right exit to Choir Nest")
    add_door(8, conduit, 9, 15, 0, 2, 1, 0, TILE, NO_HATCH, "ceiling shortcut to Silent Atrium")

    # Shortcut shaft: P1/P2 leave the y=6..7 corridor clear.
    conduit.platform(14, 5, 4)
    conduit.platform(14, 2, 4)

    # Hidden log nook behind a pulse-only wall.
    conduit.platform(36, 5, 5)
    conduit.pulse_block(37, 3, 1, 2)
    conduit.spawn("conduit_log", "PSPRITE_DATA_PAD", 39, 4, "hidden Cantor-origin log placeholder")
    conduit.spawn("conduit_hunter", "PSPRITE_HORNOAD", 26, 7, "Echo Hunter nest placeholder")

    conduit.prop(8, 1, LIGHT)
    conduit.prop(30, 1, LIGHT)
    conduit.prop(41, 1, LIGHT)
    conduit.prop(10, 7, HAZARD, 3, 1)
    conduit.prop(20, 2, PIPE, 6, 1)
    conduit.prop(33, 2, PIPE, 5, 1)
    conduit.prop(1, 3, CABLE, 1, 4)
    conduit.prop(24, 6, GRATE, 2, 1)
    conduit.prop(43, 2, RUBBLE, 1, 2)
    conduit.bg_prop(5, 4, MIST, 4, 2)
    conduit.bg_prop(28, 4, MIST, 5, 2)
    conduit.scroll(0, 44, 0, 9)
    conduit.notes.append("single full-room scroll: three screens wide, gCurrentScrolls has two slots")

    # ------------------------------------------------------------------
    # Room 4: Choir Nest — 1x2 screens, Cantor arena.
    choir = Room("choir_nest", 4, 15, 20, 18, 7, 0)
    choir.shell()
    choir.floor_edge()
    add_door(7, choir, 6, 0, 16, 1, 2, TILE, 0, HATCH, "arena entrance from Hidden Conduit")
    add_door(10, choir, 11, 14, 16, 1, 2, -TILE, 0, HATCH, "post-boss exit to Entry Ledge")

    # Arena dais and two low steps.
    choir.platform(5, 15, 5)
    choir.platform(4, 17, 2)
    choir.platform(9, 17, 2)

    # Climb to the data-core pedestal.  Three-row spacing leaves two blocks
    # of headroom for a 2-block-tall player at every landing.
    choir.platform(2, 12, 3)
    choir.platform(6, 12, 3)
    choir.platform(2, 9, 3)
    choir.platform(6, 9, 3)
    choir.platform(2, 6, 3)
    choir.platform(6, 6, 3)
    choir.platform(6, 3, 3)     # data-core pedestal

    # Three pulse-revealed organs (visual placeholders; HACK-004c owns health
    # and the event gating).
    choir.pulse_block(1, 3, 2, 3)
    choir.pulse_block(12, 4, 2, 3)
    choir.pulse_block(6, 1, 3, 1)

    choir.spawn("cantor_body", "PSPRITE_BOX", 7, 14, "Cantor body placeholder")
    choir.spawn("data_core", "PSPRITE_DATA_PAD", 7, 2, "data core / slice-complete placeholder")
    choir.spawn("final_log", "PSPRITE_DATA_PAD", 2, 17, "final log placeholder")

    choir.prop(3, 5, LIGHT)
    choir.prop(11, 5, LIGHT)
    choir.prop(1, 17, RUBBLE)
    choir.prop(13, 2, PIPE, 1, 5)
    choir.prop(1, 2, CABLE, 1, 6)
    choir.prop(10, 17, RUBBLE)
    choir.bg_prop(5, 9, MIST, 5, 2)
    choir.bg_prop(9, 2, CABLE, 1, 4)
    choir.scroll(0, 14, 0, 9)
    choir.scroll(0, 14, 10, 19)
    choir.notes.append("two vertical scroll regions; arena doors are authored as hatch-can-lock")

    rooms = [entry, atrium, resonance, conduit, choir]
    validate_rooms(rooms)
    return rooms


def validate_rooms(rooms: list[Room]) -> None:
    assert [r.index for r in rooms] == list(range(5))
    assert len(DOORS) == 12, len(DOORS)
    for room in rooms:
        assert len(room.doors) >= 2, (room.name, room.doors)
        assert room.spawns, room.name
        assert room.width * room.height <= 1024, room.name
        assert room.scrolls, room.name
        for door_index in room.doors:
            door = DOORS[door_index]
            assert door.room == room.index, (room.name, door_index)
            assert 0 <= door.dst < len(DOORS), (room.name, door_index, door.dst)
            assert door.dst != door.index, (room.name, door_index)
            assert DOORS[door.dst].dst == door.index, (door_index, door.dst)
        for spawn in room.spawns:
            assert spawn.sprite in SPRITE_SLOT_BY_NAME, spawn


def tiled_map(room: Room) -> dict[str, Any]:
    def tile_layer(layer_id: int, name: str, data: list[list[int]]) -> dict[str, Any]:
        return {
            "id": layer_id,
            "name": name,
            "type": "tilelayer",
            "width": room.width,
            "height": room.height,
            "visible": True,
            "opacity": 1,
            "x": 0,
            "y": 0,
            "data": [value for row in data for value in row],
        }

    door_objects = []
    for door_index in sorted(room.doors):
        door = DOORS[door_index]
        door_objects.append({
            "id": door.index + 1,
            "name": f"door_{door.index}",
            "type": "",
            "x": door.x * TILE,
            "y": door.y * TILE,
            "width": door.w * TILE,
            "height": door.h * TILE,
            "rotation": 0,
            "visible": True,
            "properties": [
                {"name": "type", "type": "string", "value": door.kind},
                {"name": "src_room", "type": "int", "value": door.room},
                {"name": "dst_door", "type": "int", "value": door.dst},
                {"name": "x_exit", "type": "int", "value": door.x_exit},
                {"name": "y_exit", "type": "int", "value": door.y_exit},
            ],
        })

    spawn_objects = []
    for i, spawn in enumerate(room.spawns):
        spawn_objects.append({
            "id": 100 + i,
            "name": spawn.name,
            "type": "",
            "point": True,
            "x": spawn.x * TILE,
            "y": spawn.y * TILE,
            "rotation": 0,
            "visible": True,
            "properties": [
                {"name": "sprite_id", "type": "string", "value": spawn.sprite},
                {"name": "spriteset", "type": "string", "value": "default"},
                {"name": "slot", "type": "int", "value": SPRITE_SLOT_BY_NAME[spawn.sprite]},
                {"name": "properties", "type": "string", "value": "SSP_UNINFECTED_OR_BOSS"},
            ],
        })

    next_object_id = max(
        [door.index + 1 for door in DOORS.values()]
        + [100 + len(room.spawns)]
        + [1]
    ) + 1

    return {
        "type": "map",
        "version": "1.10",
        "tiledversion": "1.10.2",
        "orientation": "orthogonal",
        "renderorder": "right-down",
        "infinite": False,
        "width": room.width,
        "height": room.height,
        "tilewidth": TILE,
        "tileheight": TILE,
        "nextlayerid": 6,
        "nextobjectid": next_object_id,
        "tilesets": [{
            "firstgid": 1,
            "name": "blockout_tileset",
            "image": TILESET_IMAGE,
            "imagewidth": 64,
            "imageheight": 64,
            "tilewidth": TILE,
            "tileheight": TILE,
            "tilecount": 16,
            "columns": 4,
        }],
        "layers": [
            tile_layer(1, "bg1", room.bg1),
            tile_layer(2, "bg2", room.bg2),
            tile_layer(3, "collision", room.clip),
            {
                "id": 4,
                "name": "doors",
                "type": "objectgroup",
                "visible": True,
                "opacity": 1,
                "x": 0,
                "y": 0,
                "objects": door_objects,
            },
            {
                "id": 5,
                "name": "spawns",
                "type": "objectgroup",
                "visible": True,
                "opacity": 1,
                "x": 0,
                "y": 0,
                "objects": spawn_objects,
            },
        ],
    }


def room_manifest(room: Room) -> dict[str, Any]:
    clip_names = {
        CLIP_SOLID: "CLIPDATA_SOLID",
        CLIP_AIR: "CLIPDATA_AIR",
        CLIP_DOOR: "CLIPDATA_DOOR_TRANSITION",
    }

    used_bg1 = sorted({value for row in room.bg1 for value in row if value})
    used_bg2 = sorted({value for row in room.bg2 for value in row if value})
    used_clip = sorted({value for row in room.clip for value in row if value})
    assert set(used_clip) <= set(clip_names), (room.name, used_clip)
    unknown_bg1 = set(used_bg1) - set(BLOCK_BY_GID)
    unknown_bg2 = set(used_bg2) - set(BLOCK_BY_GID)
    assert not unknown_bg1, (room.name, "bg1", sorted(unknown_bg1))
    assert not unknown_bg2, (room.name, "bg2", sorted(unknown_bg2))

    return {
        "schema": "mf-hack.room-manifest/v1",
        "room": {
            "name": room.name,
            "area": "AREA_TEST_1",
            "index": room.index,
            "tileset": {
                "number": 0,
                "image": TILESET_IMAGE,
                "tile_pixels": [TILE, TILE],
                "block_pixels": [TILE, TILE],
                "colors_per_tile": 16,
                "transparent_index": 0,
            },
            "layers": {
                "bg0": None,
                "bg1": "bg1",
                "bg2": "bg2",
                "clip": "collision",
            },
            "tile_mapping": {
                "bg1": {str(gid): BLOCK_BY_GID[gid] for gid in used_bg1},
                "bg2": {str(gid): BLOCK_BY_GID[gid] for gid in used_bg2},
                "clip": {str(gid): clip_names[gid] for gid in used_clip},
            },
            "spritesets": {
                "default": {str(slot): name for slot, name in sorted(SPRITE_SLOTS.items())},
            },
            "room_entry": {
                "bg0_prop": "BG_PROP_NONE",
                "bg1_prop": "BG_PROP_RLE_COMPRESSED",
                "bg2_prop": "BG_PROP_RLE_COMPRESSED",
                "bg3_prop": BG3_PROP,
                "bg3_scrolling": BG3_SCROLLING,
                "transparency": 0,
                "effect": "EFFECT_NONE",
                "effect_y": 255,
                "music_track": 0,
                "map_x": room.map_x,
                "map_y": room.map_y,
                "first_spriteset_event": 0,
                "second_spriteset_event": 0,
                "default_spriteset": 255,
                "first_spriteset": 255,
                "second_spriteset": 255,
            },
            "camera": {"scrolls": room.scrolls},
        },
    }


def render(rooms: list[Room]) -> dict[Path, bytes]:
    files: dict[Path, bytes] = {}
    for room in rooms:
        map_bytes = (
            json.dumps(tiled_map(room), indent=2, ensure_ascii=True) + "\n"
        ).encode("ascii")
        manifest_bytes = (
            json.dumps(room_manifest(room), indent=2, ensure_ascii=True) + "\n"
        ).encode("ascii")
        files[HERE / f"{room.name}.tmj"] = map_bytes
        files[HERE / f"{room.name}.room.json"] = manifest_bytes
    return files


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--check", action="store_true", help="verify committed source assets")
    group.add_argument("--write", action="store_true", help="regenerate maps and manifests")
    args = parser.parse_args(argv)

    rooms = build_rooms()
    files = render(rooms)

    if args.write:
        for path, payload in sorted(files.items()):
            path.write_bytes(payload)
            print(f"wrote {path.relative_to(HERE.parents[2])} ({len(payload)} bytes)")
        return 0

    stale = []
    for path, payload in sorted(files.items()):
        if not path.exists():
            stale.append(f"missing {path.name}")
        elif path.read_bytes() != payload:
            stale.append(f"stale {path.name}")
    if stale:
        print("ROOMS: FAIL: " + "; ".join(stale), file=sys.stderr)
        print("run build_rooms.py --write", file=sys.stderr)
        return 1

    print("ROOMS: PASS: 5 Tiled maps + manifests are current")
    for room in rooms:
        print(
            f"  {room.index} {room.name}: {room.width}x{room.height} "
            f"({room.width * room.height} blocks), {len(room.doors)} doors, "
            f"{len(room.spawns)} spawns, {len(room.scrolls)} scroll(s)"
        )
    return 0


if __name__ == "__main__":
    sys.exit(main())
