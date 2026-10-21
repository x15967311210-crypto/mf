# Sector Null blockout assets (HACK-004a1)

Source assets for the five-room **First Echo** blockout, authored against
`docs/design/vertical-slice.md`, `docs/design/level-layout.md` and
`docs/design/content-ids.md`.  This directory contains source only; it does not
integrate the rooms into `src/`.  HACK-004a2 owns the engine/C integration.

Everything here is synthetic: the tileset is flat 16x16 geometry drawn from a
16-colour palette, and the Tiled maps contain no ROM art, extracted tiles,
text, audio or copyrighted material.

## Files

| File | Purpose |
|---|---|
| `blockout_tileset.png` | 64x64 indexed PNG, 4x4 grid of 16x16 block tiles, palette index 0 transparent |
| `make_blockout_tileset.py` | deterministic generator / staleness check for the PNG |
| `build_rooms.py` | deterministic generator / staleness check for the five `.tmj` + `.room.json` pairs |
| `entry_ledge.tmj`, `.room.json` | room 0 source |
| `silent_atrium.tmj`, `.room.json` | room 1 source |
| `resonance_chamber.tmj`, `.room.json` | room 2 source |
| `hidden_conduit.tmj`, `.room.json` | room 3 source |
| `choir_nest.tmj`, `.room.json` | room 4 source |
| `check_blockout.py` | validates the generated `hack/gen/rooms/<room>/` directories |

The Tiled files are committed source assets.  `build_rooms.py` is kept so the
geometry, door table and spawn table can be regenerated consistently; the
converter consumes the `.tmj` / `.room.json` pair, not the generator.

## Room IDs

All rooms use **`AREA_TEST_1` (area index 7)**.  No new `AREA_*` is allocated.

| Room | Name | Tiled size | Blocks | Map x,y | Doors | Spawns | Scrolls |
|---|---|---|---|---|---|---|---|
| 0 | Entry Ledge | 15x10 | 150 | 0,2 | 0, 11 | 2 | 1 |
| 1 | Silent Atrium | 15x30 | 450 | 1,0 | 1, 2, 9 | 3 | 1 |
| 2 | Resonance Chamber | 30x10 | 300 | 2,0 | 3, 4 | 2 | 2 |
| 3 | Hidden Conduit | 45x10 | 450 | 4,0 | 5, 6, 8 | 2 | 1 |
| 4 | Choir Nest | 15x20 | 300 | 7,0 | 7, 10 | 3 | 2 |

Every room is at most 450 blocks, below the 1024-block
`gDecompClipdataMap` limit enforced by HACK-003a.

The map coordinates form the intended minimap layout:

```text
y=0   [ Silent Atrium ][ Resonance ][ Hidden Conduit ][ Choir Nest ]
      x=1                x=2..3       x=4..6             x=7
y=2   [ Entry Ledge ]
      x=0
```

## Door table

Door indices 0-9 are the provisional mapping in `docs/design/content-ids.md`.
Indices **10/11 are a blockout-only post-boss return pair** appended after that
map.  They are required to give Entry Ledge and Choir Nest a second physical
door and to close the slice loop after the Cantor; they are **not yet in
`content-ids.md`** and need design/ID sign-off before HACK-004a2 commits a
13-entry door table.  If the design rejects them, Entry Ledge and Choir Nest
fall back to one door each.

| Door | Room | Object id | Geometry (blocks) | dst | Type | Notes |
|---|---|---|---|---|---|---|
| 0 | 0 Entry | 1 | x=14, y=6..7 | 1 | normal / no hatch | right exit to Atrium |
| 1 | 1 Atrium | 2 | x=0, y=26..27 | 0 | normal / no hatch | lower-left entry |
| 2 | 1 Atrium | 3 | x=14, y=2..3 | 3 | normal / hatch-can-lock | top-right exit to Resonance |
| 3 | 2 Resonance | 4 | x=0, y=6..7 | 2 | normal / hatch-can-lock | left entry from Atrium |
| 4 | 2 Resonance | 5 | x=29, y=6..7 | 5 | normal / hatch-can-lock | sealed right exit to Conduit |
| 5 | 3 Conduit | 6 | x=0, y=6..7 | 4 | normal / hatch-can-lock | left entry from Resonance |
| 6 | 3 Conduit | 7 | x=44, y=6..7 | 7 | normal / hatch-can-lock | right exit to Choir |
| 7 | 4 Choir | 8 | x=0, y=16..17 | 6 | normal / hatch-can-lock | arena entrance |
| 8 | 3 Conduit | 9 | x=15..16, y=0 | 9 | normal / no hatch | ceiling shortcut to Atrium |
| 9 | 1 Atrium | 10 | x=14, y=12..13 | 8 | normal / hatch-can-lock | shortcut landing |
| 10 | 4 Choir | 11 | x=14, y=16..17 | 11 | normal / hatch-can-lock | post-boss exit to Entry |
| 11 | 0 Entry | 12 | x=0, y=6..7 | 10 | normal / hatch-can-lock | post-boss return |

The converter writes one `doors.bin` record per door in each room, sorted by
Tiled object id.  **The object id is global door index + 1**, so HACK-004a2 must
use `record.id - 1` when filling `sTest1Doors[]`; do not concatenate the five
`doors.bin` files, because the global table is ordered by door index, not by
room.  Door 0 must not keep the baseline self-loop.

Door 8 is a 2x1 horizontal ceiling door (the baseline horizontal doors use
`DOOR_TYPE_NO_HATCH`); all other doors are 1x2 vertical doors.

## Spawn / entity placeholders

There are no invented sprite IDs.  Every room uses the same default spriteset
table so HACK-004a2 can load one six-entry `gSpritesetSpriteIds` table:

| Slot | Sprite | ID | Placeholder for |
|---|---|---|---|
| 0 | `PSPRITE_SAVE_PAD` | 31 | Entry Ledge save pad |
| 1 | `PSPRITE_DATA_PAD` | 30 | logs, pulse pedestal, data core |
| 2 | `PSPRITE_HORNOAD` | 18 | Echo Hunter AI placeholder in Atrium/Conduit |
| 3 | `PSPRITE_GERON_MISSILE_1` | 65 | Atrium missile tank |
| 4 | `PSPRITE_BOX` | 98 | Cantor body placeholder |
| 5 | `PSPRITE_MESSAGE_BANNER` | 33 | Resonance scripted reveal |

All spawns use `SSP_UNINFECTED_OR_BOSS` so the record byte is table-indexed
(`0x11`..`0x16`).  Positions are block coordinates; the converter floors the
Tiled point and the engine applies its own half-block offsets.

| Room | Spawn | Sprite | x,y | Purpose |
|---|---|---|---|---|
| 0 | `save_pad` | save pad 31 | 3,7 | only save pad in the slice |
| 0 | `log_deck_07` | data pad 30 | 9,7 | "Deck 07 sealed" log |
| 1 | `atrium_log` | data pad 30 | 3,3 | optional archaeology log on pulse ledge |
| 1 | `atrium_missile` | missile 65 | 4,3 | optional missile tank |
| 1 | `echo_hunter` | Hornoad 18 | 9,27 | lower-half Hunter patrol |
| 2 | `pulse_pedestal` | data pad 30 | 15,6 | Resonance Pulse pickup placeholder |
| 2 | `pulse_reveal_banner` | message banner 33 | 15,2 | scripted first-pulse reveal |
| 3 | `conduit_log` | data pad 30 | 39,4 | hidden Cantor-origin log |
| 3 | `conduit_hunter` | Hornoad 18 | 26,7 | mid-shaft Hunter nest |
| 4 | `cantor_body` | Box 98 | 7,14 | Cantor body placeholder |
| 4 | `data_core` | data pad 30 | 7,2 | data core / slice-complete |
| 4 | `final_log` | data pad 30 | 2,17 | final log |

## Camera scrolls

| Room | Records |
|---|---|
| Entry Ledge | x 0..14, y 0..9 |
| Silent Atrium | x 0..14, y 0..29 (one record; the room is three screens tall and `gCurrentScrolls` has two slots) |
| Resonance Chamber | x 0..14, y 0..9; x 15..29, y 0..9 |
| Hidden Conduit | x 0..44, y 0..9 (one record; three screens wide) |
| Choir Nest | x 0..14, y 0..9; x 0..14, y 10..19 |

## Generate and validate

From the repository root:

```sh
# Verify the committed synthetic sources are current (no writes).
python3 hack/content/tiled/make_blockout_tileset.py --check
python3 hack/content/tiled/build_rooms.py --check

# Convert all five rooms into the generated output directory.
set -e
for room in entry_ledge silent_atrium resonance_chamber hidden_conduit choir_nest; do
  python3 tools/content/tiled_to_room.py \
    --map "hack/content/tiled/$room.tmj" \
    --manifest "hack/content/tiled/$room.room.json" \
    --out "hack/gen/rooms/$room" \
    --force
done

# Check directories, files, room IDs, clipdata limits, door reciprocity,
# spawn encoding and camera bounds.
python3 hack/content/tiled/check_blockout.py

# Pipeline self-check (fixture + invalid-input cases).
make -f Makefile.shift content-check
```

To regenerate the committed sources after editing the room builder or the
tileset generator:

```sh
python3 hack/content/tiled/make_blockout_tileset.py --write
python3 hack/content/tiled/build_rooms.py --write
```

`hack/gen/` is generated output and is not committed.  The generated file set
per room is:

```text
room.json
bg1.rle
bg2.rle
clipdata.rle
scrolls.bin
doors.bin
spriteset_default.bin
spriteset_first.bin
spriteset_second.bin
```

## HACK-004a2 integration checklist

1. **Confirm the two appended door IDs.**  If 10/11 are rejected, remove the
   post-boss door pair and accept one door in Entry Ledge and Choir Nest.
   Otherwise update `docs/design/content-ids.md` first; this directory must not
   silently become the ID source of truth.
2. **Rooms:** extend `sTest1RoomEntries` from 4 to 5 entries (indices 0-4; the
   array has no terminator) and update the extern in
   `include/data/rooms_data.h`.  `sAreaRoomEntryPointers[AREA_TEST_1]` already
   points at the array.
3. **Doors:** build `sTest1Doors[13]` (12 active records + one
   `DOOR_TYPE_NONE` terminator) and update the extern.  Place records by global
   index from `room.json` `doors.records[].id - 1`; `srcRoom` is the room index
   and `dstDoor` is the reciprocal global index.  The baseline `sTest1Doors[0]`
   self-loop must go away.
4. **Room entries:** for each room emit `RoomEntryRom` with:
   - `tileset = 0` (authoring placeholder; see item 6);
   - `bg0Prop = BG_PROP_NONE`, `pBg0Data = empty`;
   - `bg1Prop`/`bg2Prop = BG_PROP_RLE_COMPRESSED` and the `.rle` blobs;
   - `bg3Prop = BG_PROP_NONE`, `pBg3Data = empty`;
   - `pClipData = clipdata.rle` (the stream includes width/height);
   - `pDefaultSpriteData = spriteset_default.bin`,
     `defaultSpriteset = 255`, empty first/second sets;
   - `pScrollData = scrolls.bin`, `mapX/mapY` from the manifest,
     `musicTrack = MUSIC_NONE`, `transparency = 0`, `effect = EFFECT_NONE`.
5. **Sprites:** load the six-entry default table into
   `gSpritesetSpriteIds` exactly as listed above.  Do not renumber slots; the
   `.bin` record bytes depend on them.
6. **Tileset:** `room.tileset.number = 0` is an authoring placeholder.  For M1,
   keep the vanilla Test 1 tileset or add a reviewed `TilesetEntry` for the
   synthetic blockout; do not ship `blockout_tileset.png` as final art.  The PNG
   is a source/reference image only.  `tile_mapping` maps GIDs to block IDs
   0..15; the C-side tileset must map those block IDs consistently.
7. **Dark room:** the pipeline emits only RLE BG0 and cannot represent
   `BG_PROP_DARK_ROOM` (0x43, LZ77 BG0).  The rooms are visually dark through
   tiles, but the engine dark/dim flag is a HACK-004a2 decision: extend the
   pipeline to LZ77 BG0 or add a reviewed room-effect exception.  Do not put
   0x43 in `bg1Prop`; the RLE decoder will not handle it.
8. **Event-check blocker:** fix the broad `>= EVENT_ORBIT_CHANGE_IMPLEMENTED`
   checks listed in `docs/design/content-ids.md` §2 before the save pad,
   navigation/recharge pads or BG3 direction can be trusted after event 0x6F.
9. **Events:** add `0x6E`-`0x77`, set `EVENT_END = 0x78`, and update
   `sEventLocationAndNavigationInfo` and `sPauseDebugEventNames`.
10. **Entry warp / scenario:** add the Test Area 1 entry path and the M1
    boot/scene gate.  The intended entry is room 0; the save pad is at block
    (3,7).  Test Area 1 room 0 should not inherit the old debug-room geometry.
11. **Build gates:** normal, shifted and reordered builds; `content-check`,
    `smoke` and the M1 room scenario.  No ROMs or generated `hack/gen/` files
    belong in Git.

## HACK-008c2 generated table (Entry Ledge room 0)

`make content-tables` is the one reproducible step from this directory to the
HACK overlay:

```sh
make content-tables
make content-tables-check
make hack-build
```

It writes `hack/gen/rooms/entry_ledge/` and `hack/gen/content_tables.h` (both
ignored).  The generated table currently contains:

- room 0 (Entry Ledge), 15x10 blocks, tileset 0, mapX/mapY from the manifest;
- bg1/bg2/clipdata RLE and the default spriteset records;
- a safe empty bg3 record (`BG_PROP_NONE` still requires a loadable pointer);
- one `DOOR_TYPE_NONE` terminator, not the two authored doors.

The two authored doors are intentionally suppressed until the destination
rooms exist.  HACK-008d adds the first dialogue/enemy/event path; HACK-004a2
adds the full five-room blockout and the reciprocal door records.  Scrolls,
text, events, music, animated tiles and LZ77 bg0 remain out of this table.

Do not hand-edit `hack/gen` or copy generated tables into `src/data`.

## Known blockout gaps

- The Resonance Chamber one-way drop back to the Atrium is marked with a grate
  and route marker at x=18..20, y=7..8, but `content-ids.md` has no door ID for
  it.  It stays decorative until HACK-004a2/design allocates a transition.
- Pulse-only platforms and the Conduit hidden wall are authored as
  non-solid `PULSE` tiles (`clipdata = AIR`) so an M1 playtest cannot soft-lock
  on an unimplemented pulse gate.  HACK-004b/d must add the event-gated
  collision/visibility.
- Boss organs and the Cantor body are placeholders; HACK-004c owns their
  entities, health, phases and arena lock.
- Logs are re-readable placeholders; HACK-004d owns the text and the final
  data-core/exit events.
- `bg3`, animated tiles, palettes and audio are not emitted by the current
  pipeline.  Music is `MUSIC_NONE` (0) for the blockout.
