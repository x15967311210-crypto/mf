# mf-hack — Metroid Fusion: shiftable C engine + Sector Null hack

This repository is two things in one tree:

- a **decompilation baseline** of Metroid Fusion (USA) — **3212/3607 functions
  (89.05%, 395 left)** in C and **0x5c2ff0/0x6f9d24 bytes of data outside blobs
  (82.59%, 0x136d34 left)** — a clean-room decompilation derived from
  [metroidret/mf](https://github.com/metroidret/mf); the code is MIT-licensed
  (see [LICENSE](LICENSE)) and contributions follow
  [CONTRIBUTING.md](CONTRIBUTING.md);
- a **shiftable C engine** built on that baseline — code and ROM data may change
  size and order while the game still boots and behaves the same — plus the
  **Sector Null** hack overlay, which is only linked when `HACK=1`.

Baseline progress is tracked in the
[decompilation spreadsheet](https://docs.google.com/spreadsheets/d/1HvJ-jynb-4P9tfEBVJmkQFpIg6mJRDRUBvDIBiLxQIo/).

A normal build produces `mf_us.gba`; the shift targets write padded and
reordered artifacts under `work/shift/`, and the hack build writes
`work/hack/mf_us_hack.gba`. Only `make` replaces `mf_us.gba`.

## Quick start

```sh
# One-time: pinned agbcc, extracted data, baserom check.
make setup-agbcc                # or `make setup` (setup-agbcc + doctor)
python3 tools/extractor.py      # data/ from mf_us_baserom.gba (ignored by Git)

make -j                         # mf_us.gba
make check                      # baseline SHA1 check

make shift-build                # padded-layout build (relocation gate)
make shift-test                 # padded build + behavior scenario
make shift-reorder              # .rodata reorder test
make hack-build                 # HACK=1 overlay -> work/hack/mf_us_hack.gba
make hack-smoke                 # hack build + static/600-frame boot smoke
make test                       # static + headless boot + 4k input replay
make -f Makefile.shift test     # legacy wrapper; `make test` is the same run
make content-check              # content pipeline + D-009 ID registry
make jira-check                 # validate jira.md
make dashboard                  # regenerate docs/dashboard.md
make help                       # every normal, shift, hack and PM target
```

Targets that need the emulator/harness report **SKIP (77)** instead of a pass
when it is not installed; they never pass falsely.

## Where to look

| Path | Contents |
|---|---|
| [docs/roadmap.md](docs/roadmap.md) | phases S0–S4, gates, current status |
| [docs/golden-path.md](docs/golden-path.md) | shortest path to a playable hack slice (Entry Ledge) |
| [docs/content-pipeline.md](docs/content-pipeline.md) | Tiled/PNG → room data, spritesets, scrolls, text, ID registry |
| [docs/playtest.md](docs/playtest.md) | human playtest protocol and milestone gates |
| [docs/style.md](docs/style.md) | C format contract (`make format`, `make format-check`) |
| [docs/architecture/](docs/architecture/) | engine architecture overview (DOC-003, landing in the current docs phase) |
| [docs/howto/](docs/howto/) | add a room/door, dialogue, enemy behaviour (DOC-004…006, landing) |
| [jira.md](jira.md) | backlog and task status (source of truth) |
| [docs/dashboard.md](docs/dashboard.md) | generated project summary |
| [AGENTS.md](AGENTS.md) | house rules for humans and agents |

## Status

- **M0 shiftable-boot gate: PASS (2026-10-21).** Normal, padded
  (`. += 0x1000`) and `.rodata`-reordered builds all complete the native
  339001-frame TAS with the same final state
  (`DISPCNT=1900 main=9 s1=2 s2=0100 event=109 area=0 room=63`), and the native
  Any% run passes at 259176 frames for all three. `check-relocs-strict` passes.
- **M1 blockout: built, not signed off.** The `HACK=1` overlay links five
  Test Area 1 rooms, 12 reciprocal doors, a generated blockout tileset and a
  HACK-only entry warp into `work/hack/mf_us_hack.gba`. The human playtest
  failed on rendering, and M1 rendering is paused at the human's request:
  **BUG-024** (player sprite invisible), **BUG-025** (room tile colours) and
  **BUG-026** (HUD/minimap textures). M1 stays failed/blocked, so `HACK-004b`
  (Resonance Pulse) and M2 do not start.
- **Next:** documentation/readability work (`DOC-*`), then M1 rendering when
  the human reopens it. The remaining engine gates (S3a hack-critical C, S3b
  full C engine) are in [docs/roadmap.md](docs/roadmap.md); the backlog in
  [jira.md](jira.md) is the only schedule.

## Regions, dependencies and setup

ROMs are named `mf_{region}.gba` (or `mf_{region}_debug.gba`). Only `us` is
supported (`sha1: ca33f4348c2c05dd330d37b97e2c5a69531dfe87`); `eu`, `jp`, `cn`
and `eu_beta` are **not yet supported**. The default build is `mf_us.gba`, and
debug builds are **not supported yet**.

Requirements: [agbcc](https://github.com/pret/agbcc) (pinned in
`tools/agbcc-version`), `binutils-arm-none-eabi`, `python3`, `make`, a host C
compiler (`g++`/`cc`), and a baserom (`mf_us_baserom.gba`). The baserom is
copyrighted and is **never** committed.

- **Windows only:** install [WSL](https://docs.microsoft.com/en-us/windows/wsl/install).
- Install host tools: `sudo apt-get install binutils-arm-none-eabi git make`.
- Build agbcc (`git clone https://github.com/pret/agbcc && cd agbcc &&
  ./build.sh`) and either install it into this tree (`./install.sh <repo>`) or
  put it on `PATH`. `make setup-agbcc` does the pinned version for you.

The toolchain and baserom are checked without building the ROM:

```sh
make doctor-source   # Python, host tools, and tool self-checks (no baserom)
make setup-agbcc     # clone/build the pinned agbcc into tools/agbcc
make doctor          # full check: ARM binutils, agbcc, and baserom SHA1
```

`make setup` runs `setup-agbcc` then `doctor`. `doctor` and the build resolve
`as`/`ld`/`objcopy` through `TOOLCHAIN`; when `arm-none-eabi-*` is not on
`PATH`, `make` auto-detects `$HOME/.local/bin/arm-none-eabi-`, so
non-interactive shells and CI work without sourcing a profile. An explicit
`TOOLCHAIN` always wins:

```sh
make check TOOLCHAIN=$HOME/.local/bin/arm-none-eabi-
```

The baserom check compares `mf_us_baserom.gba` with `tools/baserom.sha1`; for a
machine-readable report run `python3 tools/doctor.py --json-out
work/doctor.json`.

## Build

1. `make clean` if needed (`make clean DATA=1` also removes the extracted data).
2. `python3 tools/extractor.py` (once per baserom; `-r <region>` selects a
   region, `-d` extracts US-beta debug data).
3. `make -j`.

Pick another configuration with `make us_debug`, or with the flags `REGION`
(default `us`) and `DEBUG` (default `0`). `python3 tools/extractor.py &&
make -j` is the combined form.

### Shift, audit and test

`make audit`, `audit-*`, `check-relocs[-strict]`, `check-linker`,
`postlink-scan[-strict]`, `smoke`, `content-check`, `test`, `shift-build`,
`shift-test`, `shift-check`, `shift-screen`, `oam-diff`, `event-diff`,
`shift-reorder` and `shift-check-all` live in `mk/shift.mk` and are exported
from the single entry point; `make help` lists them all and `make shift-help`
lists only this group. `make -f Makefile.shift <target>` stays as a thin
compatibility wrapper for existing scripts, but new work should use `make
<target>`. Audit targets that read extracted blobs take `DATA_ROOT=<path>`
(default `data`); the map comes from a normal `make` build unless `MAP=<path>`
is given.

### Hack overlay (`HACK=1`, D-013)

```sh
make content-tables        # hack/content -> hack/gen/*.h (ignored)
make hack-build            # work/hack/mf_us_hack.gba (+ .elf/.map)
make hack-sha1             # hack-build + work/hack/mf_us_hack.sha1
make hack-smoke            # hack-build + static smoke + boot smoke
make hack-room-check       # 29500-frame replay: require Entry Ledge (area 7 room 0)
make hack-liveness-check   # 28450-frame replay: spriteset + four live spawns
```

The hack build compiles the same engine and baseline data with `-DHACK` /
`--defsym HACK=1` into a private `work/hack/obj` tree and its own linker
script, so it never overwrites `mf_us.gba` or the baseline objects. Hack-owned
content must not go into `src/data`; see
[docs/content-pipeline.md](docs/content-pipeline.md).

### Extracted data manifest and cache key

`data/` and `sound/direct_sound_samples/` are generated by the extractor and
ignored by Git. To make them cacheable and verifiable without committing
ROM-derived bytes:

```sh
make data-manifest     # write tools/data-manifest.json (paths, sizes, SHA256)
make data-verify       # exit 1 on missing, extra, resized or changed files
make data-cache-key    # <baserom-sha1>-<manifest-sha256>, one line
```

The committed manifest is text-only, uses repository-relative POSIX paths, and
is deterministic (sorted, no timestamps). `python3 tools/data_manifest.py
--self-check` covers write/verify, mutation, missing/extra, symlinked-root and
cache-key cases. `data-verify` is deliberately not part of `make all` or
`make check`.

## CI and contributing

Public (no baserom) and protected (private runner) CI layers, plus the symbols
artifact they publish, are documented in [tools/ci/README.md](tools/ci/README.md).

See [CONTRIBUTING.md](CONTRIBUTING.md) for the clean-room rule and change
process, [AGENTS.md](AGENTS.md) for the agent house rules and path ownership,
and [docs/style.md](docs/style.md) for the C format contract. Never commit a
ROM, extracted blobs, savestates or emulator screenshots of original graphics;
release artifacts are BPS patches.
