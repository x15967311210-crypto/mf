# How to add an enemy / primary sprite

Adding a primary sprite means adding an ID, loading its graphics/palette, and
dispatching an AI. In this decomp the primary tables are sized by
`PSPRITE_END` (0xCF) and are baseline-owned, so **do not append to them** —
that shifts later symbols and changes the baseline SHA. Use the HACK overlay
proxy pattern instead.

## 1. ID and data

- Add a `sprites` entry to `hack/content/ids.yaml` with `kind: primary`, then
  run `python3 tools/content/gen_ids.py --write` and `--check`.
- The ID is a `u8` (`SpriteData.spriteId`). `SPRITE_ECHO_HUNTER = 0xCF` is the
  working example (reserved, outside `PSPRITE_END`).
- Declare the id in the hack registry, not in `include/constants/sprite.h`.

## 2. Spriteset and spawn record

- Add the sprite to the room manifest's `spritesets.default` table
  (`"6": "SPRITE_ECHO_HUNTER"`), then add a spawn object with
  `sprite_id: SPRITE_ECHO_HUNTER`, the same `spriteset` and `slot`.
- `build_rooms.py --write` / `tiled_to_room.py` encodes the spawn record; the
  spawn order is the roomSlot.
- The generated `hack/gen/sprite_tables.h` carries the `(spriteId, gfxSlot)`
  table selected by `SpriteLoadSpriteset` for `AREA_TEST_1`.

## 3. Runtime proxy

The engine's arrays are `sPrimarySpritesAiPointers[PSPRITE_END]`,
`sPrimarySpriteStats[PSPRITE_END][7]`, `sSpritesGraphicsPointers[PSPRITE_END-0x10]`,
`sSpritesPalettePointers[PSPRITE_END-0x10]` and
`sSpritesGraphicsLength[PSPRITE_END-0x10]`. `0xCF` would index past all of
them. The HACK hooks in `src/sprite.c` handle it:

- `SpriteHackProxyId()` maps `SPRITE_ECHO_HUNTER -> PSPRITE_HORNOAD` in
  `SpriteLoadSpriteset` (gfx/palette), `SpriteLoadGfx`, `SpriteLoadPal`;
- `SpriteInitPrimary` rewrites the stored `gSpriteData[].spriteId` to the proxy
  after resolving it from `gSpritesetSpriteIds`, so AI, stats, health/damage
  macros and projectiles all read the baseline Hornoad entries;
- the generated spriteset/spawn data still carry `0xCF`, so content stays
  correct.

To reuse a different baseline behaviour, change the proxy target (and keep the
gfx/palette proxy consistent). Do not edit the `PSPRITE_END` tables.

## 4. Custom AI (current limitation)

`hack/*.c` is **not compiled**: the Makefile's `CSRC` comes from `src/**`, and
`hack/include` is only an include path. A truly custom AI therefore needs one
of:

- a new `src/sprites_AI/<name>.c` compiled in both builds (changes baseline
  code/ROM — requires a decision and baseline SHA review), or
- a dispatch hook in `src/sprite.c` that points the proxy id at a
  HACK-only function, with the function compiled somewhere baseline already
  builds, or
- a later build-boundary change (ADR) that adds `hack/*.c` to the HACK link.

For the golden path the Echo Hunter is a Hornoad data clone; custom AI/art is
HACK-004b.

## 5. Validate

```sh
make content-tables-check content-check
make hack-build
make hack-smoke
make hack-room-check        # area=7 room=0, live counter
make hack-liveness-check    # 7-entry spriteset + 4 live spawns
```

`hack-liveness-check` asserts `gSpritesetSpriteIds[0..6]` and the live
`gSpriteData` entries (status/id/roomSlot), so a proxy or gfx-slot mistake shows
up there, not only in a screenshot.

## Pitfalls

- `0xCF` is one past `PSPRITE_END`; never index a baseline array with it.
- roomSlot (spawn index) vs spriteset slot vs gfx slot are different numbers.
- The sprite must be on-screen (or use `SP_ALWAYS_ACTIVE`) for some AI paths.
- Do not append to `sPrimarySpritesAiPointers`/stats/gfx/palette/length arrays;
  baseline SHA must stay `ca33f434…`.
- Custom tilesets use palette bank 4 because rows 1..3 are cleared by the
  first-load HUD/fade path (see `docs/architecture/overview.md`).
