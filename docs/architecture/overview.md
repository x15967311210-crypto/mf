# Engine architecture overview

This is the map for the decompiled Metroid Fusion engine and the `HACK=1`
Sector Null overlay. It is written for contributors who need to change
behaviour without reading the whole tree (or the git log) first. Symbols and
paths below are the current ones; where the decompilation is still a stub the
doc says so instead of guessing.

## Reading map

| System | Start here |
|---|---|
| Boot / main loop / modes | `src/agbmain.c`, `src/init_game.c`, `include/constants/game_mode.h` |
| Interrupts / VBlank | `asm/intr_main.s`, `src/callbacks.c`, `src/in_game.c` (`InGameSetVblank`, `VBlankCodeInGame*`) |
| In-game state machine | `src/in_game.c` (`InGameHandler`, `InitAndLoadGenerics`) |
| Room load | `src/room.c` (`RoomLoad` and its steps), `include/structs/room.h` |
| Backgrounds / clipdata / scroll | `src/room.c`, `src/scroll.c`, `src/clipdata.c` |
| Sprites / OAM | `src/sprite.c`, `src/sprites_AI/`, `include/structs/sprite.h` |
| Text | `src/text.c`, `src/sprites_AI/message_banner.c`, `src/new_file_intro.c` |
| Audio | `src/audio_wrappers.c`, `src/music_wrappers.c`, `src/audio.c`, `asm/audio_internal.s` |
| Save / SRAM | `asm/disasm_0x0807e678.s` (`Sram_*`), `include/structs/save_file.h` |
| HACK overlay | `mk/hack.mk`, `hack/`, `docs/decisions.md` D-013 |

## Boot and the main loop

`AgbMain` (`src/agbmain.c`) calls `InitializeGame` (`src/init_game.c`) and then
runs one loop:

```
UpdateAudio -> UpdateInput -> SoftresetCheck -> frame counters ->
switch (gMainGameMode) -> wait for gVBlankRequestFlag & 1 (SYSCALL(2))
```

The VBlank ISR does **not** advance the frame counters. `CallbackCallVblank`
(`src/callbacks.c`) only sets `gVBlankRequestFlag`; `AgbMain` increments
`gFrameCounter8Bit` (`0x03000be5`) and `gFrameCounter16Bit` (`0x03000002`) in
the main loop. Treat them as main-loop iteration counters, not ISR ticks — this
matters for liveness assertions in the headless scenarios.

Interrupt entry is `InterruptCode` (`asm/intr_main.s`). The handler dispatch
table is `sBlob_a5224_a5258` (`src/data/generic_data.c`) with
`CallbackCallVblank`, `CallbackCallHBlank` and `CallbackCallVCount`. The active
VBlank callback is the linker-pinned IWRAM symbol `gVBlankCallback`
(`linker.ld`, `0x030019c4`).

Game modes (`gMainGameMode`) select the top-level handlers; `GAME_MODE_IN_GAME`
enters `InGameHandler` (`src/in_game.c`). `InGameSetVblank` picks
`VBlankCodeInGameLoad` during a file/room load and `VBlankCodeInGame` once
playing.

## File load and the in-game state machine

`InitAndLoadGenerics` (`src/in_game.c`) is the "enter gameplay" path:

```
RoomLoad(); ... SamusInit(); SpriteLoadAllData();
ProjectileCallLoadGraphicsAndClearProjectiles();
RoomEffectSetupCurrentEventBased(); ColorFadingTransferPaletteOnTransition();
gUnk_3000be3 = 1; gIsLoadingFile = FALSE; CallbackSetVBlank(VBlankCodeInGameLoad);
```

`gIsLoadingFile` is set by the SRAM load path (`Sram_CheckLoadSaveFile`,
`asm/disasm_0x0807e678.s`) and cleared here. `gUnk_3000be3` is zero until the
first room has loaded; that is why the HACK entry warp uses
`gUnk_3000be3 == 0` rather than `gIsLoadingFile` (the latter is already zero on
the New Game path and is cleared by `SramRead_WorldData`).

The HACK-only warp is a `#ifdef HACK` block in `InitAndLoadGenerics` just before
`RoomLoad()`: it sets `gCurrentArea = AREA_TEST_1`, `gLastDoorUsed = 0` and a
Samus spawn for the first file load. Door transitions keep the baseline
destination because `gUnk_3000be3` is 1 afterwards.

## Room load pipeline

`RoomLoad` (`src/room.c`) runs:

1. `ClipdataSetupCode`
2. `RoomReset` (per-room globals, fade type on first load)
3. `RoomLoadEntry` — copies the `RoomEntryRom` for
   `sAreaRoomEntryPointers[gCurrentArea][gCurrentRoom]` into `gCurrentRoomEntry`,
   picks the spriteset/event variant, stores the room-entry fields and sets the
   initial scroll flag
4. `RoomLoadTileset` — loads `sTilesetEntries[tilesetNumber]` (or the HACK
   tileset entry for `AREA_TEST_1`), decompresses tile graphics, copies the
   tileset and common palettes, sets `gTilemapAndClipPointers.pTilemap`
5. `RoomLoadScrollsAndEventBasedEffects`
6. `RoomLoadBackgrounds` — decompresses bg0/bg1/bg2 RLE planes, bg3 LZ77 and
   clipdata, and sets `gBackgroundsData.backgrounds[*].width/height`
7. `RoomRemoveNeverReformBlocksAndCollectedTanks`
8. door/effect/scroll setup, `RoomLoadDoors`
9. `RoomSetInitialTilemap(0..2)` — builds the visible 21x16 block window per BG
10. `RoomUpdateBackgroundPositions`, `BlockRedrawBrokenBlocks`,
    `MinimapCheckOnTransition`, `RoomEffectCheckSetCurrentEventBased`

`struct RoomEntryRom` and `struct RoomEntry` are in `include/structs/room.h`;
the runtime copy is `gCurrentRoomEntry`.

### Backgrounds, tilesets and clipdata

- `RoomRleDecompress` (`src/room.c`) decodes the RLE block planes. Type 0 is a
  size code, type 1 is 8-bit counts, other types are 16-bit; two passes are
  interleaved. The decompressed map is `u16` block IDs with a common-tile
  escape (`0x8000`).
- `RoomSetInitialTilemap` reads a 21x16 window, clamps it to the map
  width/height, and writes four tilemap entries per 16x16 block
  (`dst[0], dst[1], dst[32], dst[33]`).
- `struct TilesetEntry` (`include/structs/room.h`) holds `pTileGraphics`,
  `pPalette`, `pBackgroundGraphics`, `pTilemap`, animation flags. Tile
  graphics are LZ77-decompressed to `VRAM_BASE + 0x5800`; the palette is
  copied to PALRAM rows 2..15 and the common palette to rows 0..2.
- `gTilemapAndClipPointers.pTilemap` is the active tilemap; block IDs index it
  four entries at a time.
- Clipdata uses `gDecompClipdataMap` (`u16[1024]`) and the Test Area collision
  tables (`sClipdataCollisionTypes_Test`, `sClipdataBehaviorTypes_Test`).
- Scroll data is per room (`ScrollLoad` in `src/scroll.c`): byte 0 is the room
  id, byte 1 the count, then 8-byte records.

## Sprites and OAM

`SpriteLoadAllData` (`src/sprite.c`) runs after `RoomLoad`:

```
SpriteClearData -> SpriteLoadSpriteset -> EscapeCheckReloadGraphics ->
SpriteUtilInitLocationText -> SpriteLoadRoomSprites
```

- `SpriteLoadSpriteset` walks a `(spriteId, gfxSlot)` pair table. Vanilla areas
  use `sSpritesetPointers[gSpritesetNumber]`; the HACK overlay uses
  `HACK_AREA_TEST_1_DEFAULT_SPRITESETS[gCurrentRoom]`.
- `SpriteLoadRoomSprites` reads the room's `pEnemyRoomData` records
  `(y, x, spritesetSlot)` and calls `SpriteInitPrimary(slot, y, x, i)`, where
  `i` becomes the sprite's **roomSlot**.
- `struct SpriteData` (`include/structs/sprite.h`) is 0x38 bytes on GBA;
  `spriteId` is at +0x1D, `roomSlot` at +0x1E, status at +0x00.
- `SpriteUpdate` copies `gSpriteData[i]` into `gCurrentSprite`, updates RNG,
  stun and then dispatches `sPrimarySpritesAiPointers[spriteId]()` or the
  secondary table; the result is copied back.
- Drawing is split into `unk_eb04` (before Samus) and `unk_ec38` (after) plus
  `SpriteDrawAll`; OAM is built in `gOamData` and transferred in the VBlank
  handler.
- Room slot, spriteset slot and gfx slot are three different numbers. The
  message banner uses roomSlot as its message id; treating it as a spriteset
  slot caused BUG-022.

The HACK sprite proxy (`SpriteHackProxyId`, `src/sprite.c`) maps
`SPRITE_ECHO_HUNTER` (0xCF, outside `PSPRITE_END`) to `PSPRITE_HORNOAD` for
AI/stats/gfx/palette, while the generated spriteset and spawn data keep 0xCF.
This avoids appending to the baseline `PSPRITE_END`-sized tables (which would
shift symbols and change the baseline SHA).

## Text

`TextDrawMessageBanner` (`src/text.c`) handles the message banner sprite:
for stages 4/5 it clamps `messageId` to 21, adds 21 and indexes
`sMessageTextPointers[gLanguage]` (`src/new_file_intro.c`). The HACK branch is
gated on `gCurrentArea == AREA_TEST_1` and `messageId < 22` and uses
`HackAreaTest1Text[messageId]`.

`MessageBannerInit` (`src/sprites_AI/message_banner.c`) used to overwrite an
offscreen banner's `roomSlot` with `UCHAR_MAX`; the HACK branch now preserves
it for `AREA_TEST_1` so the authored message id survives (BUG-022). See
`docs/howto/add-dialogue.md` for the content workflow.

## Audio

Thin wrappers live in `src/audio_wrappers.c` (`SoundPlay`, `InitializeAudio`)
and `src/music_wrappers.c` (`PlayMusic`, `FadeMusic`,
`CheckSetNewMusicTrack`); `src/audio.c` is the M4A-style command interpreter
(`UpdateMusic`, `UpdatePsgSounds`, `UpdateTrack`, `AudioCommand_*`).
`UpdateAudio` itself is still assembly at `asm/audio_internal.s`
(0x080047A8, declared in `include/audio/track_internal.h`). Treat audio timing
as unverified until a behavior scenario covers it.

## SRAM and save layout

`Sram_CheckLoadSaveFile` is still assembly (`asm/disasm_0x0807e678.s`,
0x08080664). It reads the selected slot's state byte, sets `gIsLoadingFile`,
calls `Sram_InitSaveFile` for an empty slot or `SramLoad_CurrentSave` for an
existing one, and clears `gUnk_3000be3`, `gPauseScreenFlag`,
`gSkipDoorTransition` and related flags.

`struct SaveFile` (`include/structs/save_file.h`) is still a `u8 todo[0x1200]`
stub — a real decomp gap. Known facts (from `docs/design/content-ids.md`):
slots start at `0x200 + 0x1200*n`, `gEventCounter` is at `+0x21`, equipment at
`+0xB4`, and the checksum span is 0x900 bytes. Do not invent a field layout
here; add it to the struct when the asm is decompiled.

## HACK overlay boundary (D-013)

Baseline `src/data` is vanilla-owned. Hack content lives in `hack/content`
(ids/Tiled/text), is generated into ignored `hack/gen`, and is linked by
`make hack-build` with `-DHACK` and a private object tree. Tracked shims in
`hack/include/hack/` keep the injection points stable. The baseline hooks are
narrow `#ifdef HACK` blocks in:

- `src/room.c` — `AREA_TEST_1` door/room tables and the generated tileset;
- `src/scroll.c` — `AREA_TEST_1` scroll table;
- `src/sprite.c` — spriteset table and the Echo Hunter proxy;
- `src/text.c` — `AREA_TEST_1` message text;
- `src/sprites_AI/message_banner.c` — roomSlot preservation;
- `src/in_game.c` — first-load entry warp.

Non-HACK builds must stay token-identical where possible; an added local
variable in a baseline function can change codegen and the baseline SHA.

## Gates

| Command | Covers |
|---|---|
| `make` | baseline ROM, SHA `ca33f434…` |
| `make shift-test` | shifted layout/build + boot, SHA `5888a563…` |
| `make shift-reorder` | section-reordered build + audit, SHA `9dac0a4b…` |
| `make -f Makefile.shift test` | headless boot + 4k input replay |
| `make -f Makefile.shift audit` / `check_relocs.py` | relocations, 0 open/unknown |
| `make content-check` | converter/ID/text/table validators |
| `make hack-build` / `hack-smoke` | HACK overlay build + static/boot smoke |
| `make hack-room-check` | entry warp/room load (`area=7 room=0`) |
| `make hack-liveness-check` | spriteset + four live spawns at the 28450 prefix |
| `make jira-check` / `make dashboard` | backlog integrity + status dashboard |

`docs/golden-path.md` is the shortest path to a running hack ROM; `jira.md` and
`docs/dashboard.md` are the live status.

## Decompilation gaps worth knowing

- `struct SaveFile` has no field layout; the SRAM functions are still asm.
- `UpdateAudio` is still asm; audio timing is unverified.
- Six large `asm/disasm_*.s` files remain; `disasm_0x0808F5C4.s` alone holds
  335 ROM references.
- 697 `ldr` comments still carry raw ROM addresses; use
  `tools/shift/map_symbols.py` and the audit ledger to name them.
- The generated `hack/gen/content_tables.h` banner comment and the top comment
  in `mk/hack.mk` describe the old empty-overlay state and should be refreshed.
