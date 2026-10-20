# Headless mGBA 0.6 parity (WSL / CI)

This directory builds a **movie-native** headless runner from the mGBA 0.6
source used by BizHawk 2.3.0.1. It does not load a Windows DLL on Linux.

Pinned source:

```text
TASVideos/mgba
commit db0041340ff260424f38772df4f286fc3907c1c8
branch bizhawk-0.6
mGBA 0.6.1
```

The reference binary is BizHawk 2.3.0.1 `mgba.dll`
`4109E16135B2F44A4E8EF046ACD99EAB8600AC4A` (mGBA 0.6). The `.bk2` says
`emuVersion Version 2.3.0`.

## Build

```bash
tools/headless/build06.sh
```

The first run clones the pinned source into `tools/headless/.cache/`, applies
`mgba06_watch.patch`, builds `libmgba.a` with `-DCOLOR_16_BIT`, and links
`tools/headless/build06/mf_bizhawk_linux`.

Overrides:

```bash
MGBA06_SRC=/path/to/mgba-0.6-bizhawk BUILD06_DIR=/tmp/build06 tools/headless/build06.sh
```

## Run a tier

Assets are not in the repository:

```text
HEADLESS_BIOS   gba_bios.bin  (SHA1 300C20DF...)
HEADLESS_MOVIE  reserenv2-metroidfusion-100.bk2
HEADLESS_ROM    default: <repo>/mf_us.gba
```

```bash
HEADLESS_BIOS=/path/gba_bios.bin \
HEADLESS_MOVIE=/path/reserenv2-metroidfusion-100.bk2 \
HEADLESS_TIER=smoke \
bash tools/headless/ci_gate.sh
```

Tiers:

| Tier | Frames | Checkpoints |
|---|---:|---|
| `smoke` | 4,000 | 300,600,900,1059,4000 |
| `early` | 30,000 | +30000 |
| `full` | 339,001 | +339001 |

The runner dumps OAM/PAL/VRAM/IO/IWRAM/EWRAM at each checkpoint. The verifier
compares SHA1s against `golden_manifest.json` and also compares the checkpoint
log lines and input hashes.

```text
HEADLESS GOLDEN: PASS
```

The full tier takes about 5 minutes on WSL (measured 298.9 s, ~1,134 fps); the
smoke tier takes about 2-3 s after the build is cached.

## Checkpoint states (`--state-in` / `--state-out`)

A long movie run can be resumed from a saved core state instead of replaying
every frame. The state is mGBA's own `SAVESTATE_SAVEDATA` blob, taken through
the same `BizStartGetState` / `BizFinishGetState` / `BizPutState` entry points
BizHawk uses. It therefore round-trips exactly between runs of the same core
build.

| Option | Meaning |
|---|---|
| `--state-in FILE` | load the A/normal savestate before the movie loop |
| `--diff-state-in FILE` | load the B/candidate savestate before the movie loop (`--diff` only) |
| `--state-out FILE` | save the A/normal savestate after the final frame |
| `--diff-state-out FILE` | save the B/candidate savestate after the final frame (`--diff` only) |
| `--start-frame N` | skip the first N movie input entries; the first processed input is index N (frame N+1) |

`--frames` is a **count from `--start-frame`**, not an absolute end frame:
`--start-frame 115000 --frames 3000` processes movie inputs 115000..117999,
i.e. frames 115001..118000.

`--start-frame` defaults to 0 and `--frames` defaults to "all remaining movie
inputs". A `--frames` value past the end of the movie is clamped with a warning,
and a `--start-frame` past the end of the movie is an error.

State load happens after `BizCreate` / `BizReset` / `BizPutSaveRam` and before
the first `BizAdvance`. State save happens after the last `BizAdvance`, before
the cores are destroyed, and the log line names the frame it was taken at:

```text
saved A/normal state at frame 115000: /tmp/n_115000.state (430112 bytes)
```

The RTC value and checkpoint numbers are derived from the absolute frame
number, so a resumed run sees exactly the same timeline as an uninterrupted one.

### Resume workflow (diff gate)

Run 0..115000 once and keep both cores' states:

```bash
tools/headless/build06/mf_bizhawk_linux \
  --dll mgba.dll \
  --rom mf_us.gba --diff-rom ../work/shift/mf_us_shift.gba \
  --bios gba_bios.bin --movie reserenv2-metroidfusion-100.bk2 \
  --diff --diff-regions OAM,PAL,VRAM,EWRAM --frames 115000 \
  --state-out /tmp/n_115000.state \
  --diff-state-out /tmp/s_115000.state
```

`--diff-regions OAM,PAL,VRAM,EWRAM` is the same set `ci_gate.sh` uses. IO is
excluded because relocated ROM pointers and in-flight DMA source addresses
differ by design (for example `DMA3SAD` at IO offset `0xD5` differs by one
`PAD_BYTES` step during boot); the default `--diff` set includes IO, so a raw
`--diff` run reports that expected difference at frame 295.

Then resume at the checkpoint. `--diff` requires **both** state inputs; passing
only one is an error, because a normal state loaded into the shifted core would
compare two unrelated timelines. Resuming mid-movie with no states is accepted
with a warning, but both cores then start from reset.

```bash
tools/headless/build06/mf_bizhawk_linux \
  --dll mgba.dll \
  --rom mf_us.gba --diff-rom ../work/shift/mf_us_shift.gba \
  --bios gba_bios.bin --movie reserenv2-metroidfusion-100.bk2 \
  --diff --diff-regions OAM,PAL,VRAM,EWRAM \
  --start-frame 115000 --frames 3000 \
  --state-in /tmp/n_115000.state \
  --diff-state-in /tmp/s_115000.state
```

This reproduces the known BUG-017 first diff (`frame=117234`, EWRAM
`offset=0x0 a=FF b=00`) in a few seconds instead of re-running 117k frames.

Single-core use is the same minus the `--diff*` variants: `--state-out` after
one run, then `--state-in FILE --start-frame N`. `--state-in` without
`--start-frame` is accepted but prints a warning: the movie timeline is not
shifted to match the loaded state, so the run is only meaningful if the state
was taken at frame 0.

Errors are fatal and explicit: missing file, empty file, and a state the core
rejects (wrong version, different BIOS, or truncated) all print an `error:` line
and exit non-zero.

State files are local scratch data (`/tmp`). They contain game RAM, so they are
never committed; `.gitignore` does not need to cover them because they live
outside the repository.

## Watchpoint (optional)

The 0.6 build includes `mgba06_watch.patch`:

```text
PAL / VRAM / OAM / gOamData / gNextOamSlot writes
```

Environment:

```text
MF_WATCH_TRACE      output path
MF_WATCH_FRAME_MIN  first frame
MF_WATCH_FRAME_MAX  last frame
```

Each line:

```text
frame vcount cycle pc lr sp cpsr addr value size performingDMA activeDMA
```

`performingDMA=7` means DMA3; `0` means a CPU write.

## GitHub Actions

`tools/headless/ci_gate.sh` is the gate. The workflow is
`.github/workflows/headless.yml` (source: `tools/headless/ci_workflow.yml`).

It is designed for a **self-hosted Linux runner** because the baserom, BIOS and
movie cannot be committed. Configure repository variables with absolute paths
on the runner:

```text
MF_BASEROM      /opt/mf-assets/mf_us_baserom.gba
HEADLESS_BIOS   /opt/mf-assets/gba_bios.bin
HEADLESS_MOVIE  /opt/mf-assets/reserenv2-metroidfusion-100.bk2
MF_TOOLCHAIN    /opt/arm/bin                    # ARM binutils dir or prefix
HEADLESS_SHIFT_FRAMES 339001                    # full tier shift/reorder frames
```

The runner needs host `cmake`, `ninja`, `gcc`, `make`, `python3`, zlib headers,
and ARM binutils (`arm-none-eabi-as`, `arm-none-eabi-ld`,
`arm-none-eabi-objcopy`).  It does **not** need `arm-none-eabi-gcc`: the game
C code is built with the pinned `agbcc`, which the workflow installs with
`make setup-agbcc`.  The workflow also runs `make data-verify` against the
committed `tools/data-manifest.json` before building.

Tiers:

- pull request / feature-branch push: `smoke`
  - normal golden at 4k
  - shifted + reordered lockstep diff at 4k
- push to `main`/`master`/`hack`: `early`
  - normal golden at 30k
  - shifted + reordered lockstep diff at 30k
- nightly schedule: `full`
  - normal golden at 339,001
  - shifted + reordered lockstep diff at `HEADLESS_SHIFT_FRAMES`
    (set the repository variable to `339001`; the script default is 100k)
- `workflow_dispatch`: choose `smoke` / `early` / `full`

The shifted/reordered gate is strict: `--diff-regions OAM,PAL,VRAM,EWRAM`
must report `PARITY: PASS`. IWRAM/IO are intentionally excluded because
relocated pointers and DMA addresses differ by design.

`hack` passes shifted/reordered at 4k, 30k and 100k, but a true 339001 run
currently fails at shifted frame **114671** (BUG-016); the full tier must not
be reported as PASS until that table is converted.

`actions/cache` caches `tools/headless/.cache` and `tools/headless/build06`,
keyed on the watchpoint patch, harness, build script and `linux_shim`.

On failure, `tools/headless/out` is uploaded as an artifact.

The workflow refuses to run fork pull requests on the self-hosted runner
(`github.event.pull_request.head.repo.full_name` guard). If you need fork PRs,
use a disposable runner or a separate hosted job.

Do not commit the ROM, BIOS, baserom, or movie.
