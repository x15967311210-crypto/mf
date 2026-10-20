# Metroid Fusion Decomp

This is a work in progress decompilation of Metroid Fusion.

3212/3607 functions decompiled (89.05%, 395 left)

0x5c2ff0/0x6f9d24 bytes of data not in blobs (82.59%, 0x136d34 left)

Progress can be seen here: https://docs.google.com/spreadsheets/d/1HvJ-jynb-4P9tfEBVJmkQFpIg6mJRDRUBvDIBiLxQIo/

**This decomp is not shiftable, don't use it as a base to work on anything**

This repository can be used to build multiple ROMs. The ROMs are named like this: `mf_{region}.gba` (or `mf_{region}_debug.gba`)

Region indicates which region the ROM targets:
- us: USA, North America `sha1: ca33f4348c2c05dd330d37b97e2c5a69531dfe87`
- eu: Europe **(Not yet supported)**
- jp: Japan **(Not yet supported)**
- cn: China **(Not yet supported)**
- eu_beta: Europe beta version **(Not yet supported)**

Debug simply indicates whether the ROM contains the debug features, it is optional.

**Debug is not supported yet**

The default built ROM is mf_us.gba

**Discords**:
- https://discord.gg/2MGB9Xbr9y Metroidret
- https://discord.gg/WtekHKb MAGConst

## Dependencies

- [agbcc](https://github.com/pret/agbcc)
- `binutils-arm-none-eabi`
- A baserom for each ROM desired to be built (i.e.`mf_us_baserom.gba` if you wish to build `mf_us.gba`).
- `python3`
- `g++`

## Setup

- **WINDOWS ONLY**: Install and setup [WSL](https://docs.microsoft.com/en-us/windows/wsl/install)
- Run `sudo apt update` just in case
- Install `binutils-arm-none-eabi` by running this command: `sudo apt-get install binutils-arm-none-eabi`
- Install `git` by running this command: `sudo apt-get install git`
- Install `make` by running this command: `sudo apt-get install make`

- Clone [agbcc](https://github.com/pret/agbcc) by running this command: `git clone https://github.com/pret/agbcc`
- Enter the agbcc folder (run `cd agbcc`) and build it (run `./build.sh`)
- Add agbcc to your path (`export PATH="<agbcc_path>:$PATH"`, where `<agbcc_path>` is the full path to the agbcc directory)
- Either:
  - Install agbcc into this project (by using its `./install.sh <path>` script, where `<path>` is the path to the root of this repository), or
  - Add agbcc to your path (`export PATH="<agbcc_path>:$PATH"`, where `<agbcc_path>` is the full path to the agbcc directory)

## Toolchain and environment checks

The pinned toolchain and baserom are checked without building the ROM:

```sh
make doctor-source   # Python, host tools, and tool self-checks (no baserom)
make setup-agbcc     # clone/build the pinned agbcc into tools/agbcc
make doctor          # full check: ARM binutils, agbcc, and baserom SHA1
```

The agbcc commit is pinned in `tools/agbcc-version` and built from
<https://github.com/pret/agbcc>. The setup script is idempotent and keeps its
scratch checkout in `${TMPDIR:-/tmp}/opencode/agbcc-src` (override with
`AGBCC_SRC`, or run `tools/setup_agbcc.sh --check-only` to verify an install
without building). `make setup` runs `setup-agbcc` followed by `doctor`.

`doctor` resolves `as`/`ld`/`objcopy` through `TOOLCHAIN` (default
`arm-none-eabi-`). If binutils is installed in `~/.local/bin`, export:

```sh
export TOOLCHAIN=$HOME/.local/bin/arm-none-eabi-
```

The baserom check compares `mf_us_baserom.gba` with `tools/baserom.sha1`; the
baserom is copyrighted and is never committed. For a machine-readable report,
run `python3 tools/doctor.py --json-out work/doctor.json`; the doctor's own
parsing/comparison helpers have a synthetic `--self-check`.

## Build

- Run `make clean` if necessary
  - Use `make clean DATA=1` to remove data as well
- Run the data extractor if necessary: `python3 tools/extractor.py`
  - Use the `-r` flag to specify a region other than `us` (ex: `-r jp`)
  - Use the `-d` flag to extract only debug data from the US beta ROM (required for building a ROM with debug features)
- Run `make` (using the `-j` option is recommended to speed up the process)
- To build another version of the ROM you can do either of the following:
  - Specify it directly (ex: `make us_debug` for the US ROM with debug features)
  - Specify the flags, REGION (takes the region name, defaults to `us`) and DEBUG (takes 0 or 1, defaults to 0)
- Optionally, you can combine the commands to make it easier: `python3 tools/extractor.py && make -j`

### Shift, audit and test targets

The shiftability and behavior-harness targets are now part of the same build
entry point:

```sh
make audit                 # regenerate symbols/relocation audit/blobs/report
make smoke                 # static ROM/header checks (no emulator)
make check-relocs-strict   # gate: hardcoded ROM refs and raw pointer blobs
make host-test             # host-compiler unit tests (no toolchain/baserom)
make shift-build           # padded-layout build (TOOLCHAIN=... if not on PATH)
make help                  # every normal and shift target
```

`make shift-help` lists only the shift/audit/test targets. `make -f
Makefile.shift <target>` remains a thin compatibility wrapper for existing
scripts; new work should use `make <target>`. Audit targets that read extracted
blobs take `DATA_ROOT=<path>` (default `data`), and the map comes from a normal
`make` build unless `MAP=<path>` is given.

### Extracted data manifest and cache key

`data/` and `sound/direct_sound_samples/` are generated by
`tools/extractor.py` and ignored by Git. To make them cacheable and verifiable
without committing any ROM-derived bytes:

```sh
make data-manifest     # write tools/data-manifest.json (paths, sizes, SHA256)
make data-verify       # exit 1 on missing, extra, resized or changed files
make data-cache-key    # <baserom-sha1>-<manifest-sha256>, one line
```

The committed manifest is text-only and uses repository-relative POSIX paths
such as `data/Blob_....bin` and `sound/direct_sound_samples/....bin`. It is
deterministic (sorted, no timestamps), so a clean extraction from the same
baserom produces an identical file. `python3 tools/data_manifest.py
--self-check` exercises write/verify, same-size mutation, missing, extra,
symlinked-root and cache-key determinism in temporary directories; `--json`
emits machine-readable reports. `data-verify` is deliberately not part of
`make all` or `make check`.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)
