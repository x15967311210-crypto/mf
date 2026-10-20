#!/usr/bin/env bash
# CI gate: normal golden parity + shifted/reordered lockstep diff.
#
# Required environment:
#   HEADLESS_BIOS=/path/to/gba_bios.bin
#   HEADLESS_MOVIE=/path/to/reserenv2-metroidfusion-100.bk2
# Optional:
#   HEADLESS_ROM          (default: <repo>/mf_us.gba)
#   HEADLESS_TIER         smoke|early|full (default: smoke)
#   HEADLESS_OUT          (default: tools/headless/out/<tier>)
#   HEADLESS_SHIFT        1|0 (default: 1)
#   HEADLESS_SHIFT_BUILD  1|0 build shifted/reordered ROMs (default: 1)
#   HEADLESS_SHIFT_FRAMES shifted/reorder frames for full (default: 100000)
#   MF_TOOLCHAIN          arm-none-eabi prefix or bin directory
#   PAD_BYTES             shifted build padding (default: 0x1000)
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
ROM="${HEADLESS_ROM:-$ROOT/mf_us.gba}"
BIOS="${HEADLESS_BIOS:-}"
MOVIE="${HEADLESS_MOVIE:-}"
TIER="${HEADLESS_TIER:-smoke}"
SHIFT="${HEADLESS_SHIFT:-1}"
SHIFT_BUILD="${HEADLESS_SHIFT_BUILD:-1}"
TOOLCHAIN="${MF_TOOLCHAIN:-}"
PAD_BYTES="${PAD_BYTES:-0x1000}"

if [ -z "$BIOS" ] || [ -z "$MOVIE" ]; then
    echo "error: set HEADLESS_BIOS and HEADLESS_MOVIE" >&2
    exit 2
fi

case "$TIER" in
    smoke)
        FRAMES=4000
        CPS=300,600,900,1059,4000
        SHIFT_FRAMES=4000
        ;;
    early)
        FRAMES=30000
        CPS=300,600,900,1059,4000,30000
        SHIFT_FRAMES=30000
        ;;
    full)
        FRAMES=339001
        CPS=300,600,900,1059,4000,30000,339001
        SHIFT_FRAMES="${HEADLESS_SHIFT_FRAMES:-100000}"
        ;;
    *)
        echo "error: HEADLESS_TIER must be smoke, early, or full" >&2
        exit 2
        ;;
esac

OUT="${HEADLESS_OUT:-$HERE/out/$TIER}"
rm -rf "$OUT"
mkdir -p "$OUT"

bash "$HERE/build06.sh"
BUILD="${BUILD06_DIR:-$HERE/build06}"

echo "== normal golden parity ($FRAMES frames) =="
"$BUILD/mf_bizhawk_linux" \
    --dll none \
    --rom "$ROM" \
    --bios "$BIOS" \
    --movie "$MOVIE" \
    --frames "$FRAMES" \
    --checkpoint "$CPS" \
    --dump-dir "$OUT" \
    --prefix normal

python3 "$HERE/verify_golden.py" \
    --dir "$OUT" --prefix normal \
    --manifest "$HERE/golden_manifest.json" \
    --rom "$ROM" --bios "$BIOS" --movie "$MOVIE" \
    --checkpoints "$CPS"

if [ "$SHIFT" != "1" ]; then
    echo "shifted/reordered gate disabled (HEADLESS_SHIFT=$SHIFT)"
    exit 0
fi

cd "$ROOT"
if [ "$SHIFT_BUILD" = "1" ]; then
    echo "== building shifted/reordered ROMs =="
    python3 tools/shift/shift_test.py --build --pad-bytes "$PAD_BYTES" \
        --toolchain "$TOOLCHAIN"
    python3 tools/shift/shift_test.py --reorder --build --pad-bytes "$PAD_BYTES" \
        --toolchain "$TOOLCHAIN"
else
    echo "== reusing existing shifted/reordered ROMs =="
fi

for variant in shift reorder; do
    candidate="$ROOT/work/shift/mf_us_$variant.gba"
    if [ ! -f "$candidate" ]; then
        echo "error: missing $candidate" >&2
        exit 1
    fi
    echo "== $variant lockstep diff ($SHIFT_FRAMES frames) =="
    "$BUILD/mf_bizhawk_linux" \
        --dll none \
        --rom "$ROM" \
        --diff-rom "$candidate" \
        --bios "$BIOS" \
        --movie "$MOVIE" \
        --diff \
        --diff-regions OAM,PAL,VRAM,EWRAM \
        --frames "$SHIFT_FRAMES" \
        --dump-dir "$OUT/diff_$variant" \
        --prefix "$variant"
done

echo "HEADLESS SHIFT/REORDER: PASS ($SHIFT_FRAMES frames each)"
