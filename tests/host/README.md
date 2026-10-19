# Host-side unit tests

Fast, deterministic tests that compile real engine C with the host compiler.
They need no GBA toolchain, no baserom, no `data/` directory, and no emulator.

```sh
make host-test
```

The target compiles each suite's test file together with the real engine source
it covers and links with `-ffunction-sections -fdata-sections
-Wl,--gc-sections`:

- `tests/host/room_rle_test.c` + `src/room.c`
- `tests/host/sprite_spawn_test.c` + `src/sprite.c`
- `tests/host/timer_test.c` + `src/in_game_timer.c`
- `tests/host/fixed_point_test.c` + `src/fixed_point.c`

The linker drops every unrelated engine function (and its GBA/global
references), so only the tested functions end up in each binary.  The
implementations are never copied or re-implemented here.

The binaries are written to `tests/host/bin/` (git-ignored) and run
immediately.  A successful run exits 0 and prints both suites plus a final
pass line:

```
host-test: N/N passed
sprite-spawn-test: N/N passed
timer-test: N/N passed
fixed-point-test: N/N passed
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

`timer_test.c` defines only `gInGameTimer` and `gMaxInGameTimeFlag` and links
the real `InGameTimerUpdate`:

- `gMaxInGameTimeFlag = TRUE` freezes every timer field;
- frame increment and the 63 -> 64 frame/second carry;
- seconds, minutes, and the 99-hour cap (sets the flag and clamps to
  `99:59:59:59`);
- a 100,000-tick sequence checked against a total-frames `/` and `%` model
  (kept below one hour, so it does not cross the engine's extra hour-rollover
  frame); and
- repeated calls after the cap do not wrap.

The engine's minute-rollover path performs one extra `frames++` while
carrying into hours, so `00:59:59:63` becomes `01:00:00:01`; the test asserts
that real carry rather than the ideal `01:00:00:00`.

`fixed_point_test.c` links the real Q8.8 helpers from `src/fixed_point.c` and
checks them against `Q_8_8` expectations from `include/macros.h`:

- `FixedMultiplication`: identity, exact fractional products, negative
  operands, and integer truncation (`0x1 * 0x80 -> 0`);
- `FixedDivision`: identity, reciprocal divisors, fractions, negative
  numerator/denominator, and truncation;
- `FixedInverse`: `1.0`, `0.5`, `2.0`, `0.25`, negative values, and
  truncation.

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
