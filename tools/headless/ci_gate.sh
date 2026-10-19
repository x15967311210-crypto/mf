#!/usr/bin/env bash
# CI gate: build the movie-native 0.6 runner, run a tier, verify golden hashes.
#
# Required environment:
#   HEADLESS_BIOS=/path/to/gba_bios.bin
#   HEADLESS_MOVIE=/path/to/reserenv2-metroidfusion-100.bk2
# Optional:
#   HEADLESS_ROM  (default: <repo>/mf_us.gba)
#   HEADLESS_TIER smoke|early|full (default: smoke)
#   HEADLESS_OUT  (default: tools/headless/out/<tier>)
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
ROM="${HEADLESS_ROM:-$ROOT/mf_us.gba}"
BIOS="${HEADLESS_BIOS:-}"
MOVIE="${HEADLESS_MOVIE:-}"
TIER="${HEADLESS_TIER:-smoke}"

if [ -z "$BIOS" ] || [ -z "$MOVIE" ]; then
    echo "error: set HEADLESS_BIOS and HEADLESS_MOVIE" >&2
    exit 2
fi

case "$TIER" in
    smoke) FRAMES=4000;  CPS=300,600,900,1059,4000 ;;
    early) FRAMES=30000; CPS=300,600,900,1059,4000,30000 ;;
    full)  FRAMES=339001; CPS=300,600,900,1059,4000,30000,339001 ;;
    *) echo "error: HEADLESS_TIER must be smoke, early, or full" >&2; exit 2 ;;
esac

OUT="${HEADLESS_OUT:-$HERE/out/$TIER}"
rm -rf "$OUT"
mkdir -p "$OUT"

"$HERE/build06.sh"
BUILD="${BUILD06_DIR:-$HERE/build06}"

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
