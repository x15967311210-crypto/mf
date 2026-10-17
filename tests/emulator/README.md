# Emulator behavior tests

The C engine is gated by behavior, not SHA1 (D-003).  This directory holds the
runner, scenarios and the fixed IWRAM addresses the scenarios read.

## Without an emulator

```sh
make -f Makefile.shift smoke
```

This runs `rom_smoke.py`: GBA header, entry branch, checksum, title/game code,
size and optional SHA1.  It is enough to catch a broken build.

## With mGBA

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

## Current scenario

`boot_smoke.lua` runs 600 frames and checks:

- mGBA advanced the requested frames;
- `gFrameCounter16Bit` (`0x03000002`) advanced;
- `gWrittenToDispcnt` (`0x03000008`) was initialized.

Those two IWRAM addresses come from `linker.ld` and are intentionally fixed
(D-002), so the scenario survives the ROM shift refactor.

## Next scenarios

- title/file-select input path;
- new game → first room → pause/status;
- save → load → state equality;
- navigation conversation;
- room sweep with a telemetry mailbox;
- intro/ending/game-over playback;
- differential vanilla vs C engine at checkpoints.

Do not commit savestates, screenshots with original graphics, or ROM-derived
fixtures.  Scenarios are source (Lua/YAML) and semantic assertions.
