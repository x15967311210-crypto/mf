# Host-side unit tests

Fast, deterministic tests that compile real engine C with the host compiler.
They need no GBA toolchain, no baserom, no `data/` directory, and no emulator.

```sh
make host-test
```

The target compiles `tests/host/room_rle_test.c` together with the real
`src/room.c`, and `tests/host/sprite_spawn_test.c` together with the real
`src/sprite.c`, linking both with `-ffunction-sections -fdata-sections
-Wl,--gc-sections`.  The linker drops every unrelated engine function (and its
GBA/global references), so only the tested functions end up in each binary.
The implementations are never copied or re-implemented here.

The binaries are written to `tests/host/bin/` (git-ignored) and run
immediately.  A successful run exits 0 and prints both suites plus a final
pass line:

```
host-test: N/N passed
sprite-spawn-test: N/N passed
host-test: all suites passed
```

## Coverage

`room_rle_test.c` covers `RoomRleDecompress` with synthetic vectors only:

- type 0 size codes (`0 -> 0x800`, `1/2 -> 0x1000`, other -> `0x2000`);
- type 1: no header, two interleaved passes;
- type >1: two source bytes become a 4-byte header before the passes;
- 8-bit pass mode: literal and run controls with the `0x00` terminator;
- 16-bit pass mode: big-endian literal/run controls with `0x0000`;
- pass 2 starts at `dstStart + 1`;
- a combined run/literal regression vector.

`sprite_spawn_test.c` defines only the fixture globals (`gSpriteData`,
`gSpriteDrawOrder`, `gSpritesetSpriteIds`, `gSpritesetSpriteGfxSlots`) and
links the real spawn functions from `src/sprite.c`:

- `SpriteSpawnPrimary`: exact field initialization, `statusToAdd` bits, a
  high `spritesetSlot` stored verbatim, first-free scan, and full table
  returning `UCHAR_MAX`;
- `SpriteInitPrimary`: the spriteset-slot decoding the spawn cases describe
  (low slot -> `spriteId = slot - 1`, `0x80` -> `SPRITE_STATUS_HIDDEN`, and
  slots `> 0x10` indexing `gSpritesetSpriteIds`/`GfxSlots`), plus the
  block-to-sub-pixel position offsets;
- `SpriteSpawnSecondary`: status/property bits, ram slot, direct position and
  field copies, first-free scan, and full table returning `UCHAR_MAX`;
- a mixed primary/secondary sequence that checks sequential slots and that
  earlier sprites are not clobbered.

Note: the engine's `SpriteSpawnPrimary` takes an explicit `spriteId`/`gfxRow`
and stores them; the spriteset lookup lives in `SpriteInitPrimary`.  Both are
covered so the tests exercise the function that really implements each rule.

## Scope

This is a quick pre-check for pure algorithms, not a replacement for the
emulator/behavior suite (`make -f Makefile.shift smoke`, `test`, `audit`).
Tests must stay synthetic: do not add GBA I/O, globals, ROM addresses, or
copyrighted data.

## Adding a test

1. Include `test.h` and the real engine header (for example `room.h`).
2. Use `CHECK_TRUE`, `CHECK_EQ`, or `CHECK_MEMEQ`; failures report
   `file:line` and the expression.
3. Call the check functions from `main` and return `host_test_finish()`.
4. If the test needs another engine file, extend the `host-test` recipe in the
   top-level `Makefile` rather than copying engine code.
