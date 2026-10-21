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
python3 tools/content/gen_text_tables.py --self-check
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

Music and save-field IDs are deliberately **reserved placeholders** in schema
1; text now has one active entry:

- `TEXT_*` IDs name one hack-owned `u16` text block each.  The in-area
  message index is separate (`message_id` in `hack/content/text/messages.json`);
  see “Text tables (HACK-008d2)”;
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

`doors.bin` is a **9-byte** file record (`type, srcRoom, xStart, xEnd, yStart,
yEnd, dstDoor, xExit, yExit`).  The generated C table stores the same fields as
`struct Door`, which agbcc pads to **12 bytes**, so door N is
`HackTest1Doors + 12*N` in the ROM and `doors.bin + 9*N` on disk.  Never index
one with the other's stride; the generator converts the records and both sides
use the same table order.

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

HACK-004a2a implements steps 1–3 for all five Test Area 1 rooms (see “Five-room
generation and reciprocal doors”); the baseline, shifted and reordered SHAs stay
unchanged because the tables are ROM-relocatable and only linked into `HACK=1`.

## Hack build boundary (HACK-008c1 / D-013)

D-013 splits baseline parity builds from hack content: `src/data` stays
vanilla-owned, and a `HACK=1` build links an overlay that the baseline builds
never see.  HACK-008c1 adds that build boundary with an **empty** overlay.

```sh
make content-tables      # hack/content -> hack/gen/rooms/<room> + content_tables.h + scroll_tables.h + sprite_tables.h + text_tables.h
make content-tables-check
make hack-build          # work/hack/mf_us_hack.gba (+ .elf, .map)
make hack-sha1           # hack-build, then work/hack/mf_us_hack.sha1
make hack-smoke          # hack-build + static smoke + boot_smoke (77 if no harness)
```

The target runs one sub-make with:

| Channel | Value |
|---|---|
| C preprocessor | `CPPFLAGS += -DHACK -Ihack/include` |
| assembler | `ASFLAGS += --defsym HACK=1` |
| artifact | `ROM_STEM=work/hack/mf_us_hack` |
| objects | `OBJ_DIR=work/hack/obj` |
| linker script | `LD_SCRIPT=work/hack/linker.ld.pp` |

Both artefact and intermediates live under the ignored `work/hack/`, so a hack
build never replaces `mf_us.gba`/`mf_us.elf`/`mf_us.map`, and the baseline
objects that a later `make` would relink are untouched.  `make`, `make
shift-build` and `make shift-reorder` keep their normal flags and SHAs.

The overlay has three narrow baseline hooks, one per generated header.
`src/room.c` includes `hack/include/hack/content_tables.h` and uses
`HACK_AREA_TEST_1_DOORS` / `HACK_AREA_TEST_1_ROOM_ENTRIES` for the
`AREA_TEST_1` entries of `sAreaDoorPointers` / `sAreaRoomEntryPointers`.
`src/scroll.c` includes `hack/include/hack/scroll_tables.h` and uses
`HACK_AREA_TEST_1_SCROLLS` for the `AREA_TEST_1` entry of
`sAreaScrollPointers` (HACK-008d1, below).  `src/text.c` includes
`hack/include/hack/text_tables.h` and uses `HackAreaTest1Text` for the
`AREA_TEST_1` message-banner slots (HACK-008d2, below).  For 008c1 the content
header maps both room macros to `sTest1Doors` / `sTest1RoomEntries`, so the
hack ROM is byte-identical to the baseline and boots through the baseline Test
Area 1 tables.

HACK-008c2 replaces those two defaults with the generated Entry Ledge room 0
table under the ignored `hack/gen/`.  `make content-tables` runs
`tools/content/tiled_to_room.py` and `tools/content/gen_content_tables.py`; the
generated header contains the room's bg1/bg2/clipdata RLE, default spriteset
records, one `RoomEntryRom`, and a single `DOOR_TYPE_NONE` terminator because
the one-room table has no destination doors yet.  The source room has two
authored doors; HACK-008d/HACK-004a2 adds the reciprocal room/door records
before those doors become active.

The hack linker script is generated from the same `linker.ld`, then rewritten
by `tools/shift/prefix_linker_objects.py` so every input object lives under
`work/hack/obj`.  This matters because `linker.ld` names input objects
explicitly: without the rewrite GNU ld would load baseline `src/*.o` even
though `hack-build` compiles private objects.  The normal/shifted/reordered
builds use the unmodified object paths and keep their SHAs.

The current overlay selects hack-owned room/door, scroll, spriteset and
message-banner tables, plus the HACK-only entry warp described below.  Events,
enemy AI/art and the authored event block remain future work
(HACK-004a2b/004b); see “Five-room generation and reciprocal doors” for the
current five-room state.  Do not add hack content directly to `src/data`, and
do not commit generated tables.

### Scroll tables (HACK-008d1)

`make content-tables` now writes **two** generated headers under the ignored
`hack/gen/` tree:

| Header | Consumer | Contents |
|---|---|---|
| `content_tables.h` | `src/room.c` | bg1/bg2/clipdata RLE, spritesets, `RoomEntryRom`, doors |
| `scroll_tables.h` | `src/scroll.c` | scroll blocks, `HackAreaScrollEnd`, `HackTest1ScrollPointers` |

The split is deliberate.  Both baseline hooks would otherwise include the same
header, and every `static const` blob in it would be emitted once per
translation unit.  `src/room.c` includes only `content_tables.h`; `src/scroll.c`
includes only `scroll_tables.h`, so each generated object is defined exactly
once.  The tracked shims `hack/include/hack/content_tables.h` and
`hack/include/hack/scroll_tables.h` keep the `#ifdef HACK` injection points
stable and fail the build with an `#error` if the generated file is missing.

The generated scroll block is byte-for-byte the converter's `scrolls.bin`:
byte 0 is the room index, byte 1 is the record count, then `count` records of
8 bytes in `x_start, x_end, y_start, y_end, breakable_x, breakable_y,
extended_direction, extended_value` order.  The declaration uses
`SCROLL_DATA_SIZE(n)` (`2 + 8*n`).  `HackTest1ScrollPointers` lists one block
per room and ends with `HackAreaScrollEnd` (`0xFF`), matching the
`ScrollLoad()` scan (`**ppSrc == gCurrentRoom`, stop on `UCHAR_MAX`).

`tools/content/gen_content_tables.py` validates before emitting: the file
length is exactly `2 + 8*count`, the room-id byte equals the room index, and
every field equals the converter manifest's `camera.scrolls` values copied into
`room.json`.  `--write` writes both headers, `--check` fails if either is
stale or missing, and `--self-check` exercises bad count, bad length, bad field
and bad room-id cases plus byte-exact scroll output.

Still missing for the golden path: events, enemy sprites, active
door/room records and the entry warp.  This table only makes `ScrollLoad()`
find hack-owned data for AREA_TEST_1; room-load/save behaviour is not proven by
this work.

### Text tables (HACK-008d2)

Hack-owned message-banner text has two separate identifiers:

| Layer | Identifier | Meaning |
|---|---|---|
| Content registry | `TEXT_*` (`hack/include/hack/ids.h`) | one generated `u16` text block |
| In-area message table | `message_id` 0..21 | the banner spawn's record index in the room |

`TextDrawMessageBanner` clamps `messageId` at 21 and adds 21 to index the
vanilla `sMessageTextPointers`, so `message_id` is a per-area slot, not a
global text ID.  The message-banner sprite passes its `roomSlot`, which
`SpriteInitPrimary` sets to the spawn record index in the room's enemy data
(`SpriteInitPrimary(slot, y, x, i)`), not the spriteset slot.  Entry Ledge's
third spawn record (Tiled object `102`, `signal_banner`, spriteset slot 5) is
therefore `message_id: 2` in `AREA_TEST_1`; adding or reordering spawns changes
this index, so `messages.json` must be updated with the room content.

`hack/content/text/messages.json` (`mf-hack.text-messages/v1`) maps them:

```json
{"schema": "mf-hack.text-messages/v1",
 "areas": [{"area": "AREA_TEST_1", "messages": [
   {"text_id": "TEXT_ENTRY_LEDGE_SIGNAL", "message_id": 2,
    "source": "golden_path.c", "literal": 0}]}]}
```

`source` is relative to `hack/content/text/` and `literal` selects one
`INCTEXT` block in that file.  The generator reuses
`tools/content/text_roundtrip.py`, so the words are produced by the real
`tools/preproc`/`charmap.txt` path and round-trip checked; it does not contain
a second encoder.

`tools/content/gen_text_tables.py` validates the area against the `Area` enum,
the `TEXT_*` ID against `hack/content/ids.yaml`, unique `message_id`/`text_id`
values, the 0..21 range, the source path and literal index, then writes the
ignored `hack/gen/text_tables.h` with one
`HackText<Id>[]` block, `HACK_AREA_TEST_1_TEXT_COUNT 22` and
`HackAreaTest1Text[22]`.  The tracked shim
`hack/include/hack/text_tables.h` is the only injection point; `src/text.c`
includes it under `#ifdef HACK` and uses the hack slot only when
`gCurrentArea == AREA_TEST_1` and the entry is non-NULL.  Every other area,
slot and stage falls through to the unchanged vanilla index math.
`TextDisplayMessage` (event/ability messages) is not modified.

`make content-tables` writes the table, `make content-tables-check` fails if it
is stale or missing, and `python3 tools/content/gen_text_tables.py
--self-check` covers the generator without a ROM.  This proves the linked
table.  HACK-008d4a now makes Entry Ledge reachable (below), but no scenario
yet proves that the banner actually pops up and draws the hack text in game.

### Hack entry warp (HACK-008d4a)

The HACK build redirects the **first** room load after starting or continuing a
file into `AREA_TEST_1` room 0 (Entry Ledge), so the overlay is reachable
without a vanilla door.  It is one narrow `#ifdef HACK` block in
`InitAndLoadGenerics()` (`src/in_game.c`) immediately before `RoomLoad()`:

- it is gated on `gUnk_3000be3 == 0`, which is true only until the first room
  has loaded (`Sram_CheckLoadSaveFile` clears it; the end of the same function
  sets it), so later door transitions keep their baseline destination;
- it sets `gCurrentArea = AREA_TEST_1`, `gLastDoorUsed = 0` and a valid Samus
  position, because `RoomLoadEntry()`'s file-load branch returns without
  placing Samus outside Main Deck room 0;
- `RoomLoad()` then takes the room from door 0 of the generated
  `HackTest1Doors`; door 0's `srcRoom` is 0, so a fresh file still lands in
  Entry Ledge (before HACK-004a2a the one-entry table's `DOOR_TYPE_NONE`
  terminator supplied the room number).

`make hack-room-check` replays a **29500-frame prefix** of the committed
`tests/emulator/inputs/baseline_first30000.input` against the hack ROM and
requires the final state to report `area=7 room=0`, `main=1` and a live frame
counter.  The prefix is generated deterministically into the ignored
`work/emulator/` tree by `mk/hack.mk`:

```sh
awk '/^#/ || ($1+0)<=29500' tests/emulator/inputs/baseline_first30000.input \
  > work/emulator/hack_room_prefix_29500.input
```

`HACK_ROOM_PREFIX` names that file, `HACK_ROOM_INPUT` defaults to it and
`HACK_ROOM_FRAME` (default 29500) controls the cut, so the target depends on a
rule whose prerequisite is the committed fixture.  The full 30k fixture is
**not** a valid entry-warp assertion any more: HACK-004a2a makes the 12 doors
live, and the replay walks through Entry Ledge's door 0 at about frame 29657,
legitimately ending in a different Test Area 1 room.  `hack-room-check` proves
the HACK-008d4a entry warp/room load, not door chaining; the prefix ends before
that transition (frame 29500 still reports room 0).  `hack-liveness-check` is
unaffected because its own 28450-frame prefix is earlier still.  The assertion
lives in `tests/emulator/run.py --expect-event`; the harness binary is
unchanged.  `make hack-smoke` stays a fast static + 600-frame boot check.

Known limits: the warp is HACK-only and applies to a fresh file load; normal
door transitions, save/load persistence and the route back into Entry Ledge are
still baseline behaviour.

### Spritesets and Echo Hunter (HACK-008d3)

The room entry's `defaultSpriteset` is an index into the vanilla
`sSpritesetPointers` array, not a pointer, so the manifest's `spritesets` table
never reached the engine: an invalid index fell back to
`sSpritesetPointers[129]`, an empty table, and every spawn slot resolved to
`PSPRITE_UNUSED_16` (0x10).  HACK-008d3 fixes this with one more generated
sibling, `hack/gen/sprite_tables.h`:

| Table | Contents |
|---|---|
| `HackTest1Room<N>DefaultSpriteset` | `(spriteId, gfxSlot)` byte pairs, `0x00 0x00` terminator |
| `HackTest1DefaultSpritesets[]` | room-indexed pointers |
| `HACK_AREA_TEST_1_DEFAULT_SPRITESETS` | selection macro for `src/sprite.c` |

`SpriteLoadSpriteset()` uses the generated table under `#ifdef HACK` when
`gCurrentArea == AREA_TEST_1`; all other areas keep `sSpritesetPointers`.  This
also makes the save pad, data pad and message banner spawn with their real ids
instead of 0x10 placeholders.

`SPRITE_ECHO_HUNTER = 0xCF` sits one past the vanilla `PSPRITE_END`, so the
baseline `sPrimarySpritesAiPointers`, `sPrimarySpriteStats` and gfx/pal/length
arrays must not be extended (that would move symbols and change the baseline
SHA).  Instead:

- the content converter resolves `SPRITE_ECHO_HUNTER` from
  `hack/include/hack/ids.h` and allows it in a spriteset table/record;
- `SpriteInitPrimary()` keeps the id in `gSpritesetSpriteIds`/spawn data but
  rewrites the stored `gSpriteData[].spriteId` to `PSPRITE_HORNOAD`, so AI,
  stats, damage/weakness macros and projectiles use Hornoad data;
- the spriteset graphics load and `SpriteLoadGfx`/`SpriteLoadPal` proxy 0xCF to
  `PSPRITE_HORNOAD` before subtracting 0x10.

The result is a Hornoad data clone with the Echo Hunter's id in the content
tables.  Custom AI, animation and art are HACK-004b work, not part of this
golden path.

### Five-room generation and reciprocal doors (HACK-004a2a)

The content-tables and hack-build path now converts and links **all five**
authored Test Area 1 rooms instead of one.  The defaults in `mk/hack.mk` are:

```make
HACK_ROOMS        ?= entry_ledge silent_atrium resonance_chamber hidden_conduit choir_nest
HACK_ROOMS_DIR    ?= hack/gen/rooms
HACK_ACTIVE_DOORS ?= 1
HACK_DOOR_FLAGS   ?= $(if $(filter 0,$(HACK_ACTIVE_DOORS)),,--active-doors)
```

`content-tables` runs `tiled_to_room.py` once per name (output
`hack/gen/rooms/<room>/`, `--force`), then a single `gen_content_tables.py`
with one `--room-dir` per room.  `HACK_ROOM`/`HACK_ROOM_DIR` remain the
single-room debugging selection; a subset that has no destinations can pass
`HACK_ACTIVE_DOORS=0`, which drops `--active-doors` and emits the one-entry
`DOOR_TYPE_NONE` table again.  The manifest index of each room (0..4, in
`HACK_ROOMS` order) is the engine room number and matches the `ROOM_*` IDs in
`hack/content/ids.yaml`.

Every room gets its own blobs in the three generated headers:

| Header | Per-room tables | Room-indexed table |
|---|---|---|
| `content_tables.h` | `HackTest1Room<N>{Bg1Data,Bg2Data,ClipData}`, `HackTest1Room<N>{Default,First,Second}SpriteData`, `HackTest1Room<N>Bg3Empty` | `HackTest1RoomEntries[5]` (`RoomEntryRom`) |
| `content_tables.h` | — | `HackTest1Doors[12]` + `DOOR_TYPE_NONE` |
| `scroll_tables.h` | `HackTest1Room<N>Scrolls[SCROLL_DATA_SIZE(n)]` | `HackTest1ScrollPointers[5]` + `HackAreaScrollEnd` |
| `sprite_tables.h` | `HackTest1Room<N>DefaultSpriteset` | `HackTest1DefaultSpritesets[5]` |

The 12 authored doors are six **reciprocal pairs** — table indices `0/1`,
`2/3`, `4/5`, `6/7`, `8/9`, `10/11`.  The index is the position in
`HackTest1Doors`; `dstDoor` is another index in that same table, and the room
number is `srcRoom` (the generated table is already room-filtered by
`RoomLoadDoors`).  `--active-doors` makes the generator validate each pair:
the destination index must be in range, point back to the source door and land
in the room the manifest names.  A `DOOR_TYPE_NONE` terminator ends the scan,
so the table is 13 records in C.

The file record and the C record do **not** have the same stride.  `doors.bin`
stores 9 bytes (`struct Door` fields in order); agbcc pads the same
`struct Door` to **12 bytes**, and the linked table is `13 * 12 = 0x9C` bytes
(`nm -S`).  Door `N` is `doors.bin + 9*N` but `HackTest1Doors + 12*N`; the
generator is the only place that translates between them.

`src/room.c` consumes the generated tables through the existing narrow
`#ifdef HACK` selectors (`HACK_AREA_TEST_1_ROOM_ENTRIES`,
`HACK_AREA_TEST_1_DOORS`), so the five rooms and their door chaining are still
linked only in `HACK=1`; `src/data` is untouched and the baseline/shifted/
reordered SHAs are unchanged.

Gates for this work: `make content-tables-check`, `make content-check`,
`make hack-build`, `make hack-smoke`, `make hack-room-check` (29500-frame
entry-warp prefix, above) and `make hack-liveness-check` (unchanged 28450-frame
prefix: 7-entry Entry Ledge spriteset, four live spawns).

**Still missing (HACK-004a2b and later):**

- **Event block:** the authored `AREA_TEST_1` events `0x6E..0x77`
  (`EVENT_END = 0x78`) are not emitted; the entry warp is still the HACK-only
  `InitAndLoadGenerics()` block, not an event.  Reserve/IDs are in
  `docs/design/content-ids.md`.
- **Broad event checks:** vanilla code that compares
  `event >= EVENT_ORBIT_CHANGE_IMPLEMENTED` (0x67) still treats the new range as
  late-game, which disables the save/navigation/recharge pads.  Those checks
  must be narrowed before M1; this patch deliberately does not touch them.
- **Door-transition/save-load scenario:** `hack-room-check` stops before the
  first door on purpose, so `xExit`/`yExit` placement, hatch/lock state, the
  return route and save/load persistence across the five rooms are **not**
  proven.  HACK-004a2b adds that dedicated scenario.
- **Echo Hunter AI:** still a Hornoad data clone (HACK-008d3); custom AI,
  animation and art are HACK-004b.


## Text pipeline (HACK-008b)

Text uses the repository `charmap.txt` through `tools/preproc`'s **C
`INCTEXT`** path.  The assembly `.string` reader in this tree is a stub; do not
use it for content.

```c
#include "constants/text.h"
const u16 sGoldenPathText[] = INCTEXT(
    "ENTRY LEDGE{NEW_LINE}"
    "THE SIGNAL IS WEAK"
);
```

Compile/check it with:

```sh
make -C tools/preproc
python3 tools/content/text_roundtrip.py --self-check
python3 tools/content/text_roundtrip.py --file hack/content/text/golden_path.c
```

Proven mappings (US text blob, low-byte glyph codes):

| Source | Word | Meaning |
|---|---:|---|
| `A..Z` | `0x00C1..0x00DA` | uppercase glyphs |
| `a..z` | `0x00E1..0x00FA` | lowercase glyphs |
| space | `0x0040` | space |
| `{NEW_LINE}` | `0xFE00` | line break |
| `{WIDTH(n)}` | `0x80NN` | width escape |
| `{INDENT(n)}` | `0x83NN` | indent escape |
| terminator | `0xFF00` | end of text |

Unknown characters, including unproven digits and punctuation, are **hard
errors**.  Do not add guessed mappings; prove them against the text blob or
glyph atlas first.  The alternate `0x81..0x9A` uppercase/small-caps set is
documented but intentionally unmapped.

HACK-008d2 now allocates the first `TEXT_*` ID and emits the hack-owned
message table described above; this section only proves the compile/round-trip
path.  Width/line wrapping still needs its own proof, and the in-game message
banner is not exercised until HACK-008d4 adds the Entry Ledge entry warp.

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
- **Composition/room lists:** HACK-004a2a now emits room entries, doors,
  spritesets and scrolls for the five Test Area 1 rooms; other areas and
  tileset/palette tables still come from baseline `src/data`.
- **Scripts/events:** no puzzle, lock, music or event scripting; the 12 doors
  are static reciprocal records with working room transitions, but the authored
  `0x6E..0x77` event block and the broad `>= EVENT_ORBIT_CHANGE_IMPLEMENTED`
  fixes are HACK-004a2b (see “Five-room generation and reciprocal doors”).
- **ID allocation:** rooms, doors and the slice event block are seeded;
  `SPRITE_ECHO_HUNTER=0xCF` is reserved for HACK-008d and requires extending
  `PSPRITE_END`/primary tables before use. Text now has one active
  `TEXT_*` entry and a generated per-area message table (HACK-008d2); music
  and save-field categories remain typed reserved placeholders because no safe
  numeric space exists yet (see “ID registry” and “Text pipeline”).
- **Sub-block placement:** point spawns are floored to block coordinates; the
  engine applies its own `BLOCK_SIZE`/half-block offsets.
- **RLE scope:** only the mode-1 8-bit-count stream is emitted; the decoder
  also supports the engine’s 16-bit mode, but the fixture does not exercise it.
