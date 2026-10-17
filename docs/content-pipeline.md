# Content pipeline — Tiled/PNG to room data

Status: **scaffold accepted for M1**; see “Known gaps” before using it for
arbitrary rooms.

The pipeline is an intermediate converter.  It turns Tiled JSON tile layers and
a synthetic/derived PNG tileset into the engine’s existing RLE block format plus
side records for doors, sprites and scroll bounds.  It does **not** modify the
engine, emit C tables, or convert final tileset graphics yet.  All generated
output is deterministic: sorted JSON, fixed filenames, no paths, timestamps or
ROM addresses.

## Quick check

```sh
python3 tools/content/fixtures/generate_fixture.py --check
python3 tools/content/tiled_to_room.py --self-check
```

The self-check runs the synthetic fixture twice, diffs the output, and covers
ten invalid-input cases (including the 4bpp palette budget).  It needs no ROM
or emulator.

## Convert a room

```sh
python3 tools/content/tiled_to_room.py \
  --map   hack/content/tiled/entry_ledge.tmj \
  --manifest hack/content/tiled/entry_ledge.room.json \
  --out   work/content/entry_ledge

# or a one-off deterministic fixture run
python3 tools/content/tiled_to_room.py \
  --map   tools/content/fixtures/fixture_room.tmj \
  --manifest tools/content/fixtures/fixture_room.room.json \
  --out   /tmp/hack003-room
```

`--force` replaces an existing output directory.  Without `--force`, a
non-empty output directory is an error.

## Manifest schema

`mf-hack.room-manifest/v1` is a strict JSON object; unknown and missing keys are
errors.  The current fields are:

```json
{
  "schema": "mf-hack.room-manifest/v1",
  "area": "AREA_TEST_1",
  "room_id": 0,
  "room_name": "Entry Ledge",
  "width_blocks": 8,
  "height_blocks": 6,
  "tileset": "fixture",
  "tileset_png": "fixture_tileset.png",
  "tile_size": 16,
  "bg0_properties": "BG_PROP_0",
  "bg1_properties": "BG_PROP_1",
  "bg2_properties": "BG_PROP_2",
  "effect": "EFFECT_NONE",
  "clipdata": "CLIPDATA_AIR",
  "spriteset_default": "default",
  "spriteset_first": "first",
  "spriteset_second": "second"
}
```

Tiled JSON requirements:

- orthogonal, non-infinite map;
- layer names/roles: `bg1` (background), `bg2` (foreground), `collision`/
  `clipdata` (block properties), objects layer for doors/spawns;
- no GID flip flags; a GID must be a valid tile in the PNG tileset;
- width/height in blocks, matching the manifest;
- door rectangles and point spawns carry typed properties;
- symbolic names for `BG_PROP_*`, `EFFECT_*`, `DOOR_TYPE_*`, `SSP_*`,
  clipdata values and `PSPRITE_*` are resolved from the headers.

## Output files

```text
room.json              normalized room metadata + parsed objects
bg1.rle                room RLE block plane
bg2.rle                room RLE block plane
clipdata.rle           clipdata RLE plane
scrolls.bin            SCROLL_DATA_SIZE(n) scroll records
doors.bin              struct Door records (9 bytes each)
spriteset_default.bin  [y, x, properties|slot+1] + FF FF FF
spriteset_first.bin
spriteset_second.bin
```

Engine references checked while implementing:

| Item | Location |
|---|---|
| `RoomEntryRom` | `include/structs/room.h` |
| `struct Door` | `include/structs/connection.h` |
| `SCROLL_DATA_SIZE(n)` = `2 + 8*n` | `include/structs/scroll.h` |
| `RoomRleDecompress` | `src/room.c` |
| `SPRITESET_IDX(idx)` = `idx + 1` | `include/constants/sprite.h` |
| `sTilesetEntries[98]` | `include/data/rooms_data.h` |
| `gDecompBg0/1/2Map` = `u16[6144]` (`0x3000` bytes) | `include/structs/room.h` |
| `gDecompClipdataMap` = `u16[1024]` (`0x800` bytes) | `include/structs/room.h` |

The RLE encoder emits the same two one-byte planes consumed by
`RoomRleDecompress`; the self-check decodes both planes and compares the
round-trip.

## HACK-004a integration

HACK-004a should consume the output directory, not the Tiled file directly:

1. Generate each of the five `AREA_TEST_1` rooms into `work/content/<room>/`.
2. Extend `sTest1RoomEntries` to five active rooms and extend the door table
   (see `docs/design/content-ids.md`; `src/data` is baseline-owned, so this is
   an ADR/build-data change).
3. Add the room/door C data and a Test Area 1 entry warp.
4. Rebuild normal/shifted/reordered and run the M1 boot/scene gates.

The exact room IDs and provisional door indices are in
`docs/design/content-ids.md`; they are not duplicated here.

## Known gaps

- **Clipdata capacity:** `gDecompClipdataMap` is 1024 u16 entries (`0x800`
  bytes), while the BG maps are 6144.  The current validator caps room blocks
  at 6144; it must reject rooms above 1024 blocks or the engine clipdata buffer
  can overrun.  M1 rooms are expected to be well below this, but fix the
  validator before arbitrary content.
- **Sprite encoding:** spawn records currently write the spriteset slot/property
  byte, while `sprite_id` is metadata only.  Vanilla records interpret byte 2
  through `SPRITESET_IDX`/`gSpritesetSpriteIds`; arbitrary sprite IDs can be
  silently dropped.  Either map IDs through the spriteset table or reject
  unrepresentable IDs before HACK-004a relies on them.
- **bg3:** properties/scroll are parsed but no bg3 payload is emitted; the
  engine uses a different LZ77 path for bg3.
- **Animated tilesets/palettes:** `TilesetEntry`/`RoomEntry` fields exist but
  the manifest does not model animation, and the PNG palette is validated but
  not emitted.
- **Composition/room lists:** no `sAreaRoomEntryPointers`, room-entry, door,
  tileset or scroll C-table emission; HACK-004a does that integration.
- **Scripts/events:** no puzzle, event, lock, text, music or transition
  scripting; doors are static records only.
- **Sub-block placement:** point spawns are floored to block coordinates; the
  engine applies its own `BLOCK_SIZE`/half-block offsets.
- **RLE scope:** only the mode-1 8-bit-count stream is emitted; the decoder
  also supports the engine’s 16-bit mode, but the fixture does not exercise it.
