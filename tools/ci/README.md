# CI layers

Two independent gates and one artifact:

| Layer | Entry point | Runner | Baserom/toolchain | Data |
|---|---|---|---|---|
| Public | `bash tools/ci/public_gate.sh` (.github/workflows/public.yml) | GitHub-hosted `ubuntu-latest` | none | none |
| Protected | `bash tools/ci/protected_gate.sh` | private/self-hosted runner | baserom, ARM binutils, agbcc | restores `data/` from cache and verifies it |

`.github/workflows/headless.yml` remains the self-hosted full parity job. It is
independent of the layers here; `public.yml` never calls it.

## Public gate

`tools/ci/public_gate.sh` runs on a clean checkout with **no** baserom, no
extracted `data/`, no `agbcc`, no ARM toolchain, and no
`mf_us.gba`/`mf_us.map`/`mf_us.elf`. It needs only bash, GNU make, a host C
compiler and Python 3. It makes no network calls and uses no secrets.

Steps (stop on first failure):

```text
make doctor-source
make host-test
make content-check
python3 tools/doctor.py --self-check
python3 tools/data_manifest.py --self-check
python3 tools/shift/check_relocs.py --self-check
python3 tools/shift/audit_asm.py --self-check
python3 tools/shift/audit_blobs.py --self-check
python3 tools/shift/postlink_pointer_scan.py --self-check
```

It prints `PUBLIC-CI: PASS` on success. Run it locally with either:

```sh
bash tools/ci/public_gate.sh
make public-gate
```

`.github/workflows/public.yml` runs the same script on `pull_request`, pushes
to `main`/`master`/`hack`, and `workflow_dispatch`, using Python 3.12.

## Protected gate

`tools/ci/protected_gate.sh` is for a runner that can see the copyrighted
assets. It does not build or fetch those assets itself.

Required environment:

```text
MF_BASEROM       path to mf_us_baserom.gba (or place it at ./mf_us_baserom.gba)
TOOLCHAIN        ARM binutils prefix, e.g. /opt/arm/bin/arm-none-eabi-
HEADLESS_BIOS    path to gba_bios.bin       (when HEADLESS != 0)
HEADLESS_MOVIE   path to the .bk2 movie     (when HEADLESS != 0)
```

Optional:

```text
HEADLESS=0                 skip headless parity (default: 1)
HEADLESS_TIER=smoke        smoke | early | full (default: smoke)
HEADLESS_SHIFT_BUILD=0     forwarded to tools/headless/ci_gate.sh
JOBS=20                    make -j width (default: 20)
SYMBOLS=0                  skip symbols collection
OUT_DIR=...                symbols output (default: tools/ci/out/symbols)
```

Steps:

```text
make doctor
make data-verify          # required; stale/missing data fails the gate
make -j20 check           # normal SHA1 ca33f4348c2c05dd330d37b97e2c5a69531dfe87
make check-relocs-strict
make host-test
make postlink-scan        # report mode
bash tools/headless/ci_gate.sh   (HEADLESS != 0; tier defaults to smoke)
make symbols && tools/ci/collect_symbols.sh   (unless SYMBOLS=0)
```

Exact local invocation:

```sh
export MF_BASEROM=/opt/mf-assets/mf_us_baserom.gba
export TOOLCHAIN=/opt/arm/bin/arm-none-eabi-
export HEADLESS_BIOS=/opt/mf-assets/gba_bios.bin
export HEADLESS_MOVIE=/opt/mf-assets/reserenv2-metroidfusion-100.bk2
export HEADLESS_TIER=smoke
bash tools/ci/protected_gate.sh
```

On success it prints `PROTECTED-CI: PASS`. If `make data-verify` fails it
prints the exact local fix, `python3 tools/extractor.py`, and exits 1. Data is
never regenerated silently: the CI cache must restore a tree matching
`tools/data-manifest.json`.

### Data cache

`make data-cache-key` prints `<baserom-sha1>-<manifest-sha256>` on one line.
Use that as the cache key and cache both `data/` and
`sound/direct_sound_samples/`. On a cache miss, extract on the private runner
and only then refresh the text manifest in a reviewed change.

## Symbols artifact

`tools/ci/collect_symbols.sh` requires the normal build's `mf_us.map` and exits
nonzero without it. It copies text only:

```text
mf_us.map
symbols.json       from work/shift/symbols.json, when present
abs_refs.json      from work/shift/abs_refs.json, when present
BUILD.txt          normal SHA1 (mf_us.sha1), git commit/branch, UTC date
SHA256SUMS         covers every file except itself
README.md
```

`OUT_DIR` defaults to `tools/ci/out/symbols` and may be set by environment or
`--out`. The protected job uploads this directory as its symbols artifact; a
future symbols branch can publish the same directory. It never contains the
ROM, ELF, savestates or extracted blobs.

```sh
bash tools/ci/collect_symbols.sh --help
OUT_DIR=work/symbols-artifact bash tools/ci/collect_symbols.sh
make collect-symbols
```

## Make targets

These are convenience wrappers; the scripts are the source of truth:

```text
make public-gate        # bash tools/ci/public_gate.sh
make protected-gate     # bash tools/ci/protected_gate.sh
make collect-symbols    # bash tools/ci/collect_symbols.sh
```

The existing `make symbols` target still generates `work/shift/symbols.json`
and is used by `make audit`; `collect-symbols` only packages the artifact.
