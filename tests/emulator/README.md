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

### `input` (QA-002)

`harness.c --scenario input --input FILE` replays a `frame keys` file without
BizHawk.  A 4,000-frame prefix is committed as a button/frame fixture at
`tests/emulator/inputs/baseline_first4000.input`; no ROM, savestate or
screenshot is committed.

The automatic tier runs the normal ROM, the fixture, and the expected
checkpoints:

```sh
make -f Makefile.shift test-input
```

`make -f Makefile.shift test` runs the existing boot/`SCENARIO` leg and then
`test-input`.  If the harness is absent the input leg exits **77** (skip), and
`test` reports 77 rather than a pass.  To replay another file without the
normal-fixture assertion, use the explicit target:

```sh
make -f Makefile.shift input-smoke \
  INPUT=work/playtest/m0-2026-10-17/tas/baseline_first4000.input INPUT_FRAMES=4000
```

Direct harness / runner equivalents:

```sh
tests/emulator/bin/mgba-harness mf_us.gba \
  --input tests/emulator/inputs/baseline_first4000.input \
  --expect tests/emulator/inputs/baseline_first4000.expected
python3 tests/emulator/run.py --rom mf_us.gba \
  --input tests/emulator/inputs/baseline_first4000.input \
  --expect tests/emulator/inputs/baseline_first4000.expected --frames 4000
```

Input format:

```text
# comments and `# frames=N` metadata are ignored
frame keys
```

`keys` is the GBA key bitmask: `1=A, 2=B, 4=Select, 8=Start, 16=Right,
32=Left, 64=Up, 128=Down, 256=R, 512=L`.  Each data line is one emulated
frame; the harness calls `core->setKeys()` **before** `core->runFrame()`.
`--frames N` caps the replay at N lines; without it every parsed line runs.
Frame numbers must increase, so a truncated or spliced file fails at parse
time.

The harness prints one `INPUT frame=... keys=... disp=... main=... s1=...
s2=...` line after 300, 600, 900 and 4000 completed frames (the BizHawk
frame-count convention), then `INPUT_FINAL ...`.  The verdict covers parse
success, the requested frame count, and the same `gFrameCounter16Bit`
liveness floor as `boot_smoke`.

`--expect FILE` adds one `frame disp main s1 s2` line per checkpoint and
prints `INPUT_CHECK frame=... status=pass|fail` plus a summary.  The committed
expected file asserts the **normal headless mGBA** values only; it is not
BizHawk parity, and shifted/reordered replays are run without it.  Without
`--expect`, checkpoint values are reported but never fail the replay.

Caveat: this tree's harness uses mGBA with its HLE BIOS, while the reference
`.bk2` was recorded by BizHawk with a real BIOS.  The timelines are *not*
frame-identical, so compare state transitions and divergence points rather
than exact checkpoint equality.  The replay is still deterministic across
normal/shifted/reordered builds of the same harness, which is what makes it a
fast differential pre-gate before a BizHawk run.  A full 259k-frame input is a
manual run (the runner allows `--timeout`); only the 4k prefix is automatic.

### Screenshot parity (QA-005)

`harness.c --input FILE --screen` hashes the emulated 240x160 framebuffer at
the input checkpoints.  The capture buffer is attached with `setVideoBuffer()`
**before** `core->reset()`; mGBA only wires its software renderer at reset time,
so attaching later would leave an all-zero buffer.  `--screen` is valid only
with `--input` and does not change the boot/start/input state semantics.

The harness prints one line per checkpoint:

```text
SCREEN_START width=240 height=160 stride=240 pixel_bytes=4 hash=fnv1a64
SCREEN frame=600 hash=1abaa6c524bad2e7 uniform=0 nonblack=1
SCREEN_GUARD samples=4 varied=4 nonblack=4 status=pass
```

`hash` is FNV-1a 64 over the native `mColor` pixels in memory order.  `stride`
is in pixels, not bytes.  The guard fails the replay if no checkpoint produced
a varied, non-black frame, so a disconnected buffer cannot be mistaken for a
passing screenshot gate.

Run the normal, padded-shift and data-reorder builds against the committed 4k
fixture:

```sh
make -f Makefile.shift shift-screen
```

It reports `SCREEN-DIFF: PASS|FAIL|SKIP (77)`, comparing frames 600 and 900.
A missing harness is a skip (77), never a pass.  Reordered data must match the
normal framebuffer; the padded build currently differs at 600/900, which is
BUG-003 (the shifted boot still reaches the same state checkpoints).  State
assertions remain in `test` and `shift-input`; `shift-screen` fails only on a
missing/mismatched screen checkpoint or a failed replay.

### Shifted `input` gate (QA-003)

```sh
make -f Makefile.shift shift-input
```

builds the padded shifted ROM through the same `shift_test.py --build` path as
`shift-check`, then replays the committed 4k fixture against
`work/shift/mf_us_shift.gba` with the same `--expect` checkpoint file.  It
reports `SHIFT-INPUT: PASS|FAIL|SKIP (77)`; a missing harness is a skip, never
a pass.  The shifted build must match the normal headless checkpoints and the
same `gFrameCounter16Bit` liveness floor.  A shifted-only stall fails at the
checkpoint and liveness assertions (BUG-002: divergence at frame 900, final
`frame_counter=792` against the 3,000-frame floor).  The target stays separate
from `shift-check` so the behavior regression is visible without changing the
padding/boot gate.

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
