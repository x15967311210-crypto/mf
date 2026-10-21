# How to add a room (and its doors)

This walks through the current `HACK=1` pipeline using the five Test Area 1
rooms as the worked example. No `src/data` edits are involved: rooms are
authored in Tiled, converted into ignored `hack/gen/`, and linked by the HACK
overlay.

## 1. Reserve IDs

Add the room (and any doors) to `hack/content/ids.yaml`; every new room/door
needs an ID before use (D-009):

```sh
python3 tools/content/gen_ids.py --write   # regenerates hack/include/hack/ids.h + docs/content-tracker.md
python3 tools/content/gen_ids.py --check
```

Doors must be reciprocal: each entry names its `link` partner with the opposite
direction. Door indices are global inside `sTest1Doors`; a pair such as 0/1 must
have `dstDoor` 1/0.

## 2. Author the Tiled map

- `hack/content/tiled/<room>.tmj` — orthogonal map, 16x16 blocks, layers
  `bg1`, `bg2`, `collision`/`clipdata`, and a `spawns`/`doors` object layer.
- `hack/content/tiled/<room>.room.json` — `mf-hack.room-manifest/v1`; see
  `docs/content-pipeline.md` for the full schema (tileset, layers, tile_mapping,
  spritesets, room_entry, camera.scrolls).
- Use `hack/content/tiled/build_rooms.py` when a room is generated from the
  blockout layout; after editing it run `python3 hack/content/tiled/build_rooms.py --write`
  and `--check`. If you hand-edit a `.tmj`/`.room.json`, keep them consistent
  with `build_rooms.py`.

## 3. Convert and generate

```sh
python3 tools/content/tiled_to_room.py \
  --map hack/content/tiled/<room>.tmj \
  --manifest hack/content/tiled/<room>.room.json \
  --out hack/gen/rooms/<room> --force

python3 tools/content/gen_content_tables.py \
  --room-dir hack/gen/rooms/<room> \
  --out hack/gen/content_tables.h --write
```

`gen_content_tables.py` emits `content_tables.h`, `scroll_tables.h` and
`sprite_tables.h`; `gen_tileset.py` emits `tileset_tables.h`; both are
ignored. In practice use the make targets instead of calling them by hand:

```sh
make content-tables          # converts every HACK_ROOMS room + all generated headers
make content-tables-check    # fails if any generated header is stale
make content-check
```

`mk/hack.mk` defines `HACK_ROOMS` (default: `entry_ledge silent_atrium
resonance_chamber hidden_conduit choir_nest`), `HACK_ACTIVE_DOORS ?= 1`, and
`HACK_ROOM_DIRS`. Add the new room name to `HACK_ROOMS` (and its index to the
manifest set) so the default build includes it.

## 4. Wire the overlay

The generated tables are selected by narrow `#ifdef HACK` blocks:

- `src/room.c` — `HACK_AREA_TEST_1_DOORS` / `HACK_AREA_TEST_1_ROOM_ENTRIES`
  for `sAreaDoorPointers`/`sAreaRoomEntryPointers`, and
  `HackTest1TilesetEntry` in `RoomLoadTileset`;
- `src/scroll.c` — `HACK_AREA_TEST_1_SCROLLS`;
- `src/sprite.c` — `HACK_AREA_TEST_1_DEFAULT_SPRITESETS`.

A room entry points at its background/graphics/spriteset data in the generated
header; the room index is the array index. Do not add hack tables to
`src/data`.

## 5. Doors and transitions

- Converter output `doors.bin` records are 9 bytes; the C `struct Door` is
  12 bytes on agbcc. Never index one with the other's stride.
- Active doors are only emitted when every `dstDoor` target is present;
  `gen_content_tables.py` validates reciprocal pairs, contiguous global
  indices, no self-loop and a `DOOR_TYPE_NONE` terminator.
- The five-room table is 12 records + terminator = `0x9C` bytes in the ELF.
- `hack-room-check` stops before the first door transition on purpose; a
  dedicated door-transition scenario is still `HACK-004a2b`.

## 6. Validate

```sh
make content-tables-check content-check
make hack-build
make hack-smoke
make hack-room-check        # entry warp: area=7 room=0
make hack-liveness-check    # spriteset + four spawns at the 28450 prefix
```

If a room fails to convert, the error names the manifest field (tileset,
tile_mapping, clipdata capacity, spawn encoding, scroll bounds). Fix the
content, not the generated file.

## Pitfalls

- `src/data` is baseline-owned; generated `hack/gen` is ignored.
- Clipdata is capped at 1024 blocks (`gDecompClipdataMap`).
- RLE block IDs index the *hack tileset* (`gen_tileset.py`), not vanilla
  tileset 0; the authored palette uses bank 4 (see `add-enemy.md`/tileset
  notes) because rows 1..3 are cleared by the first-load HUD/fade path.
- `HACK_ROOMS` and the room manifest indices must stay contiguous from 0.
- Save/load and cross-room transition persistence are not covered by
  `hack-room-check`; that is `HACK-004a2b`.
