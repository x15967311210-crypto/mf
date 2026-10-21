# Content pipeline — Tiled/PNG to room data

Status: **scaffold accepted for M1**; see “Known gaps” before using it for
arbitrary rooms.

The pipeline is an intermediate converter.  It turns Tiled JSON tile layers and
a synthetic/derived PNG tileset into the engine’s existing RLE block format plus
side records for doors, sprites and scroll bounds.  It does **not** modify the
engine, emit C tables, or convert final tileset graphics yet.  All generated
output is deterministic: sorted JSON, fixed filenames, no paths, timestamps or
ROM addresses.

The D-009 content ID registry is a separate source file, `hack/content/ids.yaml`;
it is checked by the same `content-check` target and generates
`hack/include/hack/ids.h` plus `docs/content-tracker.md`.  See “ID registry”
below.

## Quick check

```sh
python3 tools/content/fixtures/generate_fixture.py --check
python3 tools/content/tiled_to_room.py --self-check
python3 tools/content/gen_ids.py --self-check
python3 tools/content/gen_ids.py --check
```

The self-check runs the synthetic fixture twice, diffs the output, and covers
ten invalid-input cases (including the 4bpp palette budget).  It needs no ROM
or emulator.

## ID registry

**Decision:** `docs/decisions.md` D-009 requires every new room, door,
sprite/enemy, event, text block, music track and saved field to have an ID
before use.  `hack/content/ids.yaml` is the source of truth; two committed
files are generated from it and must not be hand-edited:

| File | Purpose |
|---|---|
| `hack/include/hack/ids.h` | C enums with `<CATEGORY>_<NAME>` constants |
| `docs/content-tracker.md` | allocation tables with owner/area, status and notes |

Workflow:

```sh
# after editing ids.yaml
python3 tools/content/gen_ids.py --write

# gate: validates ids.yaml and fails if either generated file is stale
python3 tools/content/gen_ids.py --check

# tool regression suite; no ROM or emulator
python3 tools/content/gen_ids.py --self-check
```

Schema (`schema_version: 1`): a top-level `areas` allowlist and a fixed,
ordered list of seven categories — `rooms`, `doors`, `sprites`, `events`,
`text`, `music`, `save_fields`.  Each category declares a C `prefix`, an
inclusive `min_id`/`max_id`, a `radix` (`decimal` or `hex`), an optional note,
and either `entries` or a typed `reserved_note`.  Each entry has `name`,
integer `id`, `note`, optional `owner`/`status`, and optional references.
Rooms require `area`; doors require `room` and a reciprocal `link`; sprites
require `kind` (`primary`/`secondary`).  Optional `room`, `door`, `event`,
`text` and `sprite` keys are cross-references.

The checker enforces:

- unique category names, prefixes, entry names and full C constants;
- integer IDs within the category range and unique within the category;
- canonical order (categories, entries by `(id, name)`, reserved ranges);
- non-overlapping reserved ranges, with no entry inside a reserved range;
- reciprocal door links and existing room/door/event/text/sprite references;
- every category either has entries or an explicit `reserved_note`.

Text, music and save-field IDs are deliberately **reserved placeholders** in
schema 1:

- baseline text is pointer-addressed, so there is no numeric text-block table
  to extend; HACK-008b must define that space;
- there is no free music ID: `0x00..0x63` are vanilla tracks and `0x64` is
  `SOUND_64`, the first SFX, because `unk_3bd4` tests `sound < MUSIC_COUNT`;
- M1 adds no saved field: it rides the existing `gEventCounter` at save `+0x21`,
  and `SaveFile`/the `0x6E00..0x6FFF` gap stay unchanged.

Adding an ID: choose the next free value in the category (not a reserved
range), add the entry and its references, run `--write`, and commit
`hack/content/ids.yaml` together with both generated files.

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

`mf-hack.room-manifest/v1` is a strict JSON object.  The checked-in
`tools/content/fixtures/fixture_room.room.json` is the canonical example; it
contains the current `room.tileset`, `room.layers`, `room.tile_mapping`,
`room.spritesets`, `room.room_entry` and `room.camera.scrolls` sections.  Unknown
and missing keys are errors.

The optional `room.spritesets` maps a spriteset name (`default`, `first`,
`second`) to a slot -> sprite-ID table.  A spawn with a table-indexed property
(`SSP_UNINFECTED_OR_BOSS`, `SSP_X_*`, `SSP_UNKNOWN_40`) must declare a table and
a slot that maps to its `sprite_id`.  A spawn without those property bits uses
the direct-ID encoding and is limited to sprite IDs 0..15.

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
round-trip.  Spawn record byte 2 is encoded with `SPRITESET_IDX(slot)` and
`sprite_id` is round-tripped through `decode_spawn_record()` in the self-check.

## HACK-004a integration

HACK-004a should consume the output directory, not the Tiled file directly:

1. Generate each of the five `AREA_TEST_1` rooms into `work/content/<room>/`.
2. Extend `sTest1RoomEntries` to five active rooms and extend the door table
   (see `docs/design/content-ids.md`; `src/data` is baseline-owned, so this is
   an ADR/build-data change).
3. Add the room/door C data and a Test Area 1 entry warp.
4. Use `ROOM_*`, `DOOR_*` and `EVENT_*` from `hack/include/hack/ids.h`; do not
   add numeric IDs to generated or engine code.
5. Rebuild normal/shifted/reordered and run the M1 boot/scene gates.

The exact room IDs and provisional door indices are in
`docs/design/content-ids.md`; they are not duplicated here.

## Known gaps

- **Clipdata capacity:** fixed in HACK-003a; rooms with a clip layer are
  rejected above 1024 blocks (`gDecompClipdataMap` is 1024 u16).
- **Sprite encoding:** fixed in HACK-003a; table-indexed records validate the
  declared slot/table, direct records are limited to IDs 0..15, and the
  self-check round-trips the encoded record byte.
- **bg3:** properties/scroll are parsed but no bg3 payload is emitted; the
  engine uses a different LZ77 path for bg3.
- **Animated tilesets/palettes:** `TilesetEntry`/`RoomEntry` fields exist but
  the manifest does not model animation, and the PNG palette is validated but
  not emitted.
- **Composition/room lists:** no `sAreaRoomEntryPointers`, room-entry, door,
  tileset or scroll C-table emission; HACK-004a does that integration.
- **Scripts/events:** no puzzle, event, lock, text, music or transition
  scripting; doors are static records only.
- **ID allocation:** rooms, doors and the slice event block are seeded;
  `SPRITE_ECHO_HUNTER` reserves the first free primary sprite ID. Text, music
  and save-field categories are typed reserved placeholders because no safe
  numeric space exists yet (see “ID registry”).
- **Sub-block placement:** point spawns are floored to block coordinates; the
  engine applies its own `BLOCK_SIZE`/half-block offsets.
- **RLE scope:** only the mode-1 8-bit-count stream is emitted; the decoder
  also supports the engine’s 16-bit mode, but the fixture does not exercise it.
