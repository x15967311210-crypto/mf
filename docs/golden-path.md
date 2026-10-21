# Golden path — HACK-008d Entry Ledge

The first playable hack slice: one room, loaded by a HACK-only entry warp from
the first file load.  This page is the shortest path from a clean checkout to a
running ROM, what to look at, and the checks that gate it.

## Build and run

```sh
make hack-build            # builds work/hack/mf_us_hack.gba (+ .elf/.map)
mgba work/hack/mf_us_hack.gba
```

`make hack-build` regenerates the one-room headers under `hack/gen/` first
(`content-tables`), then links the same engine and baseline data with
`-DHACK`/`--defsym HACK=1` into a private object tree, so the baseline
`mf_us.gba` is never replaced.  `make hack-sha1` additionally writes
`work/hack/mf_us_hack.sha1`.

## Entry warp

`InitAndLoadGenerics()` in `src/in_game.c` has a `#ifdef HACK` block before
`RoomLoad()`: when `gUnk_3000be3 == 0` (first file load, cleared by
`Sram_CheckLoadSaveFile`) it sets `gCurrentArea = AREA_TEST_1`, `gLastDoorUsed =
0` and spawns Samus at block (11,8).  That is why a New Game / empty-slot load
lands in Entry Ledge (area 7, room 0) instead of the baseline start room.  Door
transitions clear `gUnk_3000be3` afterwards, so they keep the baseline
destination; in this build doors are suppressed anyway.

## Controls

Vanilla Metroid Fusion bindings, unmodified: D-pad moves, **A** jumps, **B**
fires, **L/R** aim, **Start** pauses.  There are no hack-specific inputs yet.

## What to see

The room is a synthetic blockout (no ROM art).  From the spawn at block (11,8):

- **Entry Ledge** — the 15x10 block room, area 7 room 0.
- **Save pad** at the far left (block 3,7): stand on it and press **A** to save.
- **Data pad** just left of the spawn (block 9,7): a red data-pad sprite; no
  log text is wired yet.
- **Banner text** above/left (block 6,4): `ENTRY LEDGE` / `THE SIGNAL IS WEAK`.
- **Echo Hunter** to the right of the spawn: a Hornoad (`PSPRITE_HORNOAD`
  0x12) data clone standing in for the Echo Hunter sprite.
- Doors at the left and right edges are inert (see limits).

## Checks

```sh
make hack-smoke            # static ROM checks + 600-frame boot smoke
make hack-room-check       # 30k-frame replay; require area=7 room=0, in-game
make hack-liveness-check   # 28450-frame replay; assert the spriteset + 4 spawns
make content-check         # content validators and ID registry
```

`hack-liveness-check` rebuilds a deterministic input prefix in
`work/emulator/`, dumps IWRAM through the headless harness, and asserts fixed
D-002 addresses: `gSpritesetSpriteIds[0..6] == 1F 1E 12 41 62 21 CF`, gfx slots
`0..6`, `struct SpriteData` stride `0x38`, and live entries 0..3 with
(status, id, roomSlot) `0003/1F/0`, `0003/1E/1`, `0013/21/2`, `8003/12/3`;
the banner keeps its authored message id 2 (BUG-022), so it draws the hack text.
All three emulator targets exit **77** (skip) when no headless harness is
installed; they never pass falsely.

## Known limits

- **Doors are suppressed until HACK-004a2.**  The entry warp is the only way
  into Entry Ledge and there is no routed way back out; reciprocal door records
  and the 12-entry `sTest1Doors` shape land with HACK-004a2.
- **The enemy is a data clone until HACK-004b.**  The Echo Hunter spawns as
  `PSPRITE_HORNOAD`; behaviour, damage and the Resonance Pulse are later work.
- **Automated save/load is QA-030.**  There is no SaveRAM fixture or TAS save
  sequence yet, so save/load is a manual step below.
- No music or banner-timing assertion is automated; the liveness check asserts
  the banner sprite's live entry only.

## Manual save/load playtest

1. `make hack-build`, then open `work/hack/mf_us_hack.gba` in mGBA.
2. Start a **New Game** (or an empty slot) and confirm you land in Entry
   Ledge — banner text visible, save pad at the far left.
3. Walk to the save pad, stand on it and press **A**; accept the save.  The
   save prompt/message must appear and the game must return to gameplay.
4. Reset the emulator (`Ctrl+R` in mGBA) and choose **Continue** on the same
   file slot.
5. Expected: you return to Entry Ledge (area 7 room 0) with the banner, save
   pad, data pad and Echo Hunter clone all present, and no crash or black
   screen.  Actual: record frame/room in the bug if it differs.
