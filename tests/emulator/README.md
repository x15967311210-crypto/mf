# Emulator behavior tests

The C engine is gated by behavior, not SHA1 (D-003).  This directory holds the
runner, scenarios and the fixed IWRAM addresses the scenarios read.

## Without an emulator

```sh
make -f Makefile.shift smoke
```

This runs `rom_smoke.py`: GBA header, entry branch, checksum, title/game code,
size and optional SHA1.  It is enough to catch a broken build.

## With the headless harness (preferred)

Build mGBA's shared library once, then build the tiny harness:

```sh
git clone --depth 1 https://github.com/mgba-emu/mgba.git
cmake -S mgba -B mgba-build -DBUILD_QT=OFF -DBUILD_SDL=OFF \
  -DBUILD_LIBRETRO=OFF -DBUILD_GL=OFF -DENABLE_SCRIPTING=OFF \
  -DUSE_LIBZIP=OFF -DUSE_LUA=OFF -DCMAKE_BUILD_TYPE=Release
cmake --build mgba-build -j4 --target mgba

MGBA_SRC=$PWD/mgba MGBA_BUILD=$PWD/mgba-build \
  tests/emulator/build_harness.sh tests/emulator/bin/mgba-harness
```

Then:

```sh
make -f Makefile.shift test
```

`run.py` prefers `tests/emulator/bin/mgba-harness` (or `MF_MGBA_HARNESS`);
it runs the ROM without a window and reports the fixed IWRAM values.

## With the mGBA frontend

Install the SDL frontend (Ubuntu):

```sh
sudo apt install mgba-sdl
```

Then:

```sh
make -f Makefile.shift test
```

The runner sets `SDL_VIDEODRIVER=dummy` and `SDL_AUDIODRIVER=dummy`, generates
`work/emulator/boot_smoke.generated.lua`, and runs:

```sh
mgba -l work/emulator/boot_smoke.generated.lua mf_us.gba
```

If no emulator is found the runner exits **77** (skip), never 0.

## Scenarios

### `boot_smoke`

`boot_smoke.lua` runs 600 frames and checks:

- mGBA advanced the requested frames;
- `gFrameCounter16Bit` (`0x03000002`) reached at least 75% of the requested
  frames (450/600), not merely a nonzero value.  A ROM that crashes early and
  leaves the counter at 3 must fail the smoke.

Those two IWRAM addresses come from `linker.ld` and are intentionally fixed
(D-002), so the scenario survives the ROM shift refactor.

### `start` (QA-001)

`start.lua` / `harness.c --scenario start` drives the title -> file-select
transition:

- hold Start for 6 frames every 60 frames starting at frame 600;
- run to 1200 frames (the harness and runner default to 1200 for this
  scenario);
- latch success at the first frame after the first Start where
  `DISPCNT` (`0x04000000`) is nonzero, `gMainGameMode` (`0x03000BDE`) is 7 and
  `gSubGameMode1` (`0x03000BE0`) is at least 1;
- print the final `DISPCNT`/mode values even when the verdict is a failure.

The verdict latches because a healthy run has a transient `DISPCNT=0000`
during a later mode change (frame 1020 in the reference); requiring the final
frame to be lit would falsely fail it.  The shifted build never latches:
`DISPCNT` stays `0000` with `main=7` and `sub1=0` (BUG-001).

Run the shifted gate with:

```sh
make -f Makefile.shift shift-start
```

It builds the padded ROM through the same `shift_test.py --build` path as
`shift-check` and reports `SHIFT-START: PASS|FAIL|SKIP (77)`.  It is not folded
into `shift-check` while BUG-001 is open, so a shifted boot regression is
visible without breaking the existing padding gate.

## Next scenarios

- new game → first room → pause/status;
- save → load → state equality;
- navigation conversation;
- room sweep with a telemetry mailbox;
- intro/ending/game-over playback;
- differential vanilla vs C engine at checkpoints.

Do not commit savestates, screenshots with original graphics, or ROM-derived
fixtures.  Scenarios are source (Lua/YAML) and semantic assertions.
