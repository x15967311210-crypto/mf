#!/usr/bin/env bash
# Protected CI gate (BUILD-004).
#
# This is the gate for a private/self-hosted runner that can see the baserom,
# the pinned agbcc/ARM toolchain, a restored extracted-data cache, and (when
# the headless step is enabled) the BIOS and movie.  Nothing here may run on a
# hosted public runner.
#
# Required environment:
#   MF_BASEROM     path to mf_us_baserom.gba (or place it at ./mf_us_baserom.gba)
#   TOOLCHAIN      ARM binutils prefix, e.g. /opt/arm/bin/arm-none-eabi-
#   HEADLESS_BIOS  path to gba_bios.bin       (only when HEADLESS != 0)
#   HEADLESS_MOVIE path to the .bk2 movie     (only when HEADLESS != 0)
#
# Optional:
#   HEADLESS=0                 skip the headless parity step (default: 1)
#   HEADLESS_TIER=smoke        smoke | early | full (default: smoke)
#   HEADLESS_SHIFT_BUILD=0     forwarded to tools/headless/ci_gate.sh
#   JOBS=20                    parallel make width (default: 20)
#   SYMBOLS=0                  skip symbols collection (default: collect)
#   OUT_DIR=...                symbols output dir (default: tools/ci/out/symbols)
#
# Usage:
#   bash tools/ci/protected_gate.sh
#   make protected-gate
#
# On success it prints exactly `PROTECTED-CI: PASS`.
set -euo pipefail

usage() {
    cat <<'EOF'
usage: bash tools/ci/protected_gate.sh

Run the private-runner CI gate.  Requires MF_BASEROM (or ./mf_us_baserom.gba)
and TOOLCHAIN.  The headless step is on by default and additionally requires
HEADLESS_BIOS and HEADLESS_MOVIE; set HEADLESS=0 to skip it.

The extracted data/ tree must already match tools/data-manifest.json (restore
a CI cache keyed by `make data-cache-key`).  This script never regenerates
data silently.
EOF
}

case "${1:-}" in
    -h|--help)
        usage
        exit 0
        ;;
    "")
        ;;
    *)
        usage >&2
        exit 2
        ;;
esac

HERE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd -- "$HERE/../.." && pwd)"
cd "$ROOT"

export PYTHONDONTWRITEBYTECODE=1
export LC_ALL=C

EXPECTED_NORMAL_SHA=ca33f4348c2c05dd330d37b97e2c5a69531dfe87
CREATED_BASEROM_LINK=0

cleanup() {
    status=$?
    if [ "$CREATED_BASEROM_LINK" = 1 ]; then
        rm -f "$ROOT/mf_us_baserom.gba"
    fi
    if [ "$status" -ne 0 ]; then
        echo "PROTECTED-CI: FAIL (status $status)" >&2
    fi
}
trap cleanup EXIT

die() {
    echo "PROTECTED-CI: error: $*" >&2
    exit 1
}

step() {
    printf '\n==> %s\n' "$*"
    "$@"
}

# --- required inputs -------------------------------------------------------

if [ -z "${MF_BASEROM:-}" ]; then
    if [ -f "$ROOT/mf_us_baserom.gba" ]; then
        MF_BASEROM="$ROOT/mf_us_baserom.gba"
    else
        die "MF_BASEROM is not set and $ROOT/mf_us_baserom.gba does not exist"
    fi
fi
[ -f "$MF_BASEROM" ] || die "MF_BASEROM does not exist: $MF_BASEROM"

if [ -z "${TOOLCHAIN:-}" ]; then
    die "TOOLCHAIN is not set (use the arm-none-eabi- prefix, e.g. /opt/arm/bin/arm-none-eabi-)"
fi
export TOOLCHAIN

HEADLESS="${HEADLESS:-1}"
HEADLESS_TIER="${HEADLESS_TIER:-smoke}"
HEADLESS_SHIFT_BUILD="${HEADLESS_SHIFT_BUILD:-0}"
if [ "$HEADLESS" != 0 ]; then
    for var in HEADLESS_BIOS HEADLESS_MOVIE; do
        value="${!var:-}"
        [ -n "$value" ] || die "$var is not set (set HEADLESS=0 to skip the headless step)"
        [ -f "$value" ] || die "$var does not exist: $value"
    done
    case "$HEADLESS_TIER" in
        smoke|early|full) ;;
        *) die "HEADLESS_TIER must be smoke, early or full (got '$HEADLESS_TIER')" ;;
    esac
fi

# The Makefile/doctor look for ./mf_us_baserom.gba.  Link the private asset in
# for the duration of the gate, then remove the link in cleanup.
if [ "$MF_BASEROM" != "$ROOT/mf_us_baserom.gba" ] && \
   [ ! -e "$ROOT/mf_us_baserom.gba" ] && [ ! -L "$ROOT/mf_us_baserom.gba" ]; then
    abs_baserom="$(cd -- "$(dirname -- "$MF_BASEROM")" && pwd)/$(basename -- "$MF_BASEROM")"
    ln -s "$abs_baserom" "$ROOT/mf_us_baserom.gba"
    CREATED_BASEROM_LINK=1
fi

echo "PROTECTED-CI: private-runner gate in $ROOT"
echo "PROTECTED-CI: baserom=$MF_BASEROM toolchain=$TOOLCHAIN headless=$HEADLESS tier=$HEADLESS_TIER"

# --- gate steps ------------------------------------------------------------

step make doctor

# The data cache must already match BUILD-003's text manifest.  Never run the
# extractor implicitly: a stale cache must fail loudly, not silently change
# the build inputs.
if ! make data-verify; then
    cat >&2 <<'EOF'

PROTECTED-CI: data-verify failed.
The extracted data/ tree does not match tools/data-manifest.json (missing,
extra, resized or changed files).  The CI cache must restore a tree matching
the manifest; this gate does not regenerate data silently.

To rebuild the data locally from the baserom, run exactly:

    python3 tools/extractor.py

Then rerun this gate (and, if the extraction was legitimate, refresh the text
manifest with `make data-manifest` in a separate reviewed change).
EOF
    exit 1
fi

step make -j"${JOBS:-20}" check

actual_sha="$(sha1sum "$ROOT/mf_us.gba" | awk '{print $1}')"
if [ "$actual_sha" != "$EXPECTED_NORMAL_SHA" ]; then
    die "normal ROM SHA1 is $actual_sha, expected $EXPECTED_NORMAL_SHA"
fi
echo "PROTECTED-CI: normal SHA1 $actual_sha"

step make check-relocs-strict
step make host-test
step make postlink-scan

if [ "$HEADLESS" != 0 ]; then
    printf '\n==> HEADLESS_TIER=%s HEADLESS_SHIFT_BUILD=%s bash tools/headless/ci_gate.sh\n' \
        "$HEADLESS_TIER" "$HEADLESS_SHIFT_BUILD"
    HEADLESS_TIER="$HEADLESS_TIER" \
    HEADLESS_SHIFT_BUILD="$HEADLESS_SHIFT_BUILD" \
    HEADLESS_ROM="${HEADLESS_ROM:-$ROOT/mf_us.gba}" \
    HEADLESS_BIOS="$HEADLESS_BIOS" \
    HEADLESS_MOVIE="$HEADLESS_MOVIE" \
        bash "$ROOT/tools/headless/ci_gate.sh"
else
    echo "PROTECTED-CI: headless step skipped (HEADLESS=0)"
fi

if [ "${SYMBOLS:-1}" != 0 ]; then
    # Make sure work/shift/symbols.json exists even on a fresh cache; the
    # collector includes it and work/shift/abs_refs.json when present.
    step make symbols
    step env OUT_DIR="${OUT_DIR:-tools/ci/out/symbols}" \
        bash "$ROOT/tools/ci/collect_symbols.sh"
else
    echo "PROTECTED-CI: symbols collection skipped (SYMBOLS=0)"
fi

echo
echo "PROTECTED-CI: PASS"
