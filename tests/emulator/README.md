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

The canonical harness is built against the project's pinned **mGBA 0.6**
(BizHawk 2.3.0.1, `TASVideos/mgba` `bizhawk-0.6`), the same core used by
`tools/headless`. Build that core once, then build the harness:

```sh
tools/headless/build06.sh                 # produces build06/core/libmgba.a
tests/emulator/build_harness06.sh tests/emulator/bin/mgba-harness
```

`build_harness06.sh` compiles `harness.c` with the 0.6 headers and links the
static `libmgba.a` (`-DCOLOR_16_BIT`, `-lz -lm -lpthread`). `harness.c` stays
compatible with newer mGBA through `harness_compat06.h`; the old shared-library
flow (`build_harness.sh` with `MGBA_SRC`/`MGBA_BUILD`) still exists for a 0.11
tree if one is available, but 0.6 is the supported default.

Then:

```sh
make -f Makefile.shift test
```

`run.py` prefers `tests/emulator/bin/mgba-harness` (or `MF_MGBA_HARNESS`);
it runs the ROM without a window and reports the fixed IWRAM values. If neither
the 0.6 `libmgba.a` nor the harness is available the dynamic leg is a
**SKIP (77)**, never a pass.

Note: the 0.6 harness has no `mCoreLoadSaveFile`; `--save` goes through
`core->loadSave`, and `--state` only accepts 0.6-format savestates.

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
BizHawk.  Committed button/frame fixtures are the 4,000-frame prefix at
`tests/emulator/inputs/baseline_first4000.input` (QA-002) and the 30,000-frame
prefix at `tests/emulator/inputs/baseline_first30000.input` (QA-006); no ROM,
savestate or screenshot is committed.

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
s2=...` line after 300, 600, 900, 1059, 4000 and 30000 completed frames (the
BizHawk frame-count convention), then `INPUT_FINAL ...`.  Every checkpoint also
prints an `OAM frame=... count=... hash=... stage=...` telemetry line (QA-008).
The verdict covers parse success, the requested frame count, and a
`gFrameCounter16Bit` liveness floor.  The input gate captures the counter
before the first replayed frame and compares the modulo-65536 delta against
`(frames % 65536) * 3 / 4`, because the 16-bit counter wraps: a 259,176-frame
TAS expects at least 46,926 counter ticks, not 3/4 of the raw frame count.
Short replays keep the old floor (4,000 -> 3,000), so an early stall still
fails.  An exact multiple of 65,536 frames leaves a zero floor, so liveness
across a full wrap is left to the checkpoint/screen guards rather than this
counter.  `INPUT_FINAL` still reports the raw wrapped counter.

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
manual run (the runner allows `--timeout`); the 4k and 30k prefixes are
automatic.

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

### 30k input parity (QA-006)

```sh
make -f Makefile.shift shift-input-30k
```

builds the padded shifted ROM through `shift_test.py --build`, runs the normal
ROM against `baseline_first30000.input` with
`baseline_first30000.expected`, then runs the shifted ROM over the same 30,000
frames.  It compares the `INPUT frame=30000` checkpoint and the `INPUT_FINAL`
state fields `frame_counter`, `disp`, `main`, `s1` and `s2`, and reports
`SHIFT-INPUT-30K: PASS|FAIL|SKIP (77)`; a missing harness is a skip, never a
pass.

The normal leg must pass its expected checkpoint (`0x1A00 1 3 256` at frame
30000).  While BUG-004 is open the shifted build is expected to fail this
target: it reaches `frame_counter=24469 disp=0x1800 main=7 s1=11 s2=1` against
normal `frame_counter=29857 disp=0x1A00 main=1 s1=3 s2=256`.  This is the
intended red gate for the 4k-green/30k-divergent regression; do not fold it
into `shift-check` until BUG-004 is fixed.

### OAM parity telemetry (QA-008)

Every input checkpoint also prints one stable OAM line:

```text
OAM frame=30000 count=8 hash=ca3eeeb636fa7fc2 stage=ca3eeeb636fa7fc2
```

- `count` is `gNextOamSlot` (`0x030011EE`), the slots the game filled.
- `hash` is FNV-1a 64 over all 128 hardware OAM entries at `0x07000000`.
- `stage` is the same hash over the `gOamData` shadow buffer at `0x03000DE8`.
- Checkpoints are 300, 600, 900, 1059, 4000 and 30000, when reached.

```sh
make -f Makefile.shift oam-diff
```

replays `baseline_first30000.input` on the normal and padded-shift builds and
compares every checkpoint.  It reports `OAM-DIFF: PASS|FAIL|SKIP (77)`; a count
or hardware-OAM hash mismatch at a shared checkpoint fails, and a missing
harness is a skip, never a pass.  The `stage` hash is telemetry: stale free
slots in `gOamData` do not fail an otherwise identical frame.  The normal and
shifted builds currently match at every checkpoint (frame 30000 reports
`count=8` in both).  A worktree missing the generated `data/Blob_*` inputs can
build a shifted ROM with zero-filled carved tables and produce a false
state/OAM mismatch; rebuild both artifacts with the full `data/` tree before
treating a difference as a parity finding.
`python3 tests/emulator/oam_diff.py --self-check` runs the parser/comparison
checks without an emulator.

Savestate-based OAM comparison of the Navigation Room objective page stays
**local-only** under `work/playtest`: savestates are never committed, and no
`.state` file is part of this gate or of Git.

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

## Event-progress telemetry (QA-013)

The input harness prints a saved high-water event marker at every checkpoint
and on every sampled transition:

```text
EVENT frame=300 counter=0 area=0 room=0 nav=0
EVENTCHG frame=1234 old=0 new=1 area=0 room=5 nav=0
```

`gEventCounter` is a monotonic u8 progress marker, not a per-event flag set.
`event_diff.py` compares the normal/shifted (and optional reordered) sequences;
`make -f Makefile.shift event-diff` runs the committed 30k fixture and checks
the event sequence.  The full 259k local input can be checked with the same
parser by saving the harness `EVENT`/`EVENTCHG` lines:

```sh
tests/emulator/bin/mgba-harness <rom> --scenario input \
  --input work/playtest/.../baseline.input --frames 259176 \
  2>/dev/null | grep -E '^(EVENT|EVENTCHG)' > /tmp/events.log
python3 tests/emulator/event_diff.py normal.log shifted.log
```

The 30k fixture only reaches area 3 and may have no event transitions; the
full input exercises later event progression.

### Story-route state/save replay (QA-013a)

The input scenario also accepts:

```text
--state FILE   mGBA savestate to load after reset
--save FILE    SaveRAM to load before reset
```

Use `--state` for the common Nintendo-Presents start point and the
`*_from<frame>.input` fixture; `--state` is per-build (do not load a normal
state into the shifted ROM).  Event frames are relative to the state, so offset
absolute reference logs by the state frame before comparing.

### Final checkpoint/dump (QA-012)

`--final` prints `FINAL_EVENT`, `FINAL_OAM` and (with `--screen`)
`FINAL_SCREEN` after the last replayed frame.  `--dump-prefix P` writes
`P_{oam,pal,vram,io,iwram,ewram}.bin` and, with `--screen`, `P_screen.ppm`.
The input and states remain local-only.  This makes end-of-route UI parity
comparable without relying on Windows recorder artifacts.
