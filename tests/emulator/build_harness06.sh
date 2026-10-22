#!/usr/bin/env bash
# Build the headless behavior harness against the canonical mGBA 0.6 core
# (the BizHawk 2.3.0.1 `bizhawk-0.6` tree, pinned by tools/headless/build06.sh).
#
#   tests/emulator/build_harness06.sh [output]
#
# Defaults, all overridable:
#   MGBA06_SRC    tools/headless/.cache/mgba-0.6-bizhawk (headers + patched src)
#   MGBA06_BUILD  tools/headless/build06                (build06.sh output dir)
#   MGBA06_LIB    <MGBA06_BUILD>/core/libmgba.a         (static, COLOR_16_BIT)
#   CC            cc
#
# If the worktree has no 0.6 tree (it is ignored build output), the script
# falls back to the repository's main worktree, where `tools/headless/
# build06.sh` puts it.  The library is linked statically, so the resulting
# binary has no libmgba.so dependency and works without a system mGBA install.
#
# A missing 0.6 tree or libmgba.a is an error (exit 2), never a silent skip:
# callers of run.py still see "no harness" as SKIP (77), not as a pass.
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/../.." && pwd)
OUT=${1:-$HERE/bin/mgba-harness}

# The main worktree holds the ignored tools/headless/.cache and build06 trees
# when this script runs from a linked worktree.
MAIN_ROOT=""
common_dir=$(git -C "$ROOT" rev-parse --path-format=absolute --git-common-dir 2>/dev/null || true)
if [ -n "$common_dir" ]; then
    MAIN_ROOT=$(dirname "$common_dir")
fi

# Find a repo-relative path in this worktree first, then in the main worktree.
find_tree() {
    local rel=$1
    local base
    for base in "$ROOT" "$MAIN_ROOT"; do
        [ -n "$base" ] || continue
        if [ -e "$base/$rel" ]; then
            printf '%s\n' "$base/$rel"
            return 0
        fi
    done
    return 1
}

if [ -n "${MGBA06_SRC:-}" ]; then
    SRC=$MGBA06_SRC
else
    SRC=$(find_tree tools/headless/.cache/mgba-0.6-bizhawk || true)
fi

if [ -z "$SRC" ] || [ ! -f "$SRC/include/mgba/core/core.h" ] \
        || [ ! -f "$SRC/include/mgba/internal/gba/memory.h" ]; then
    echo "error: mGBA 0.6 source tree not found" >&2
    echo "       MGBA06_SRC=${MGBA06_SRC:-<unset>}" >&2
    echo "       tried $ROOT/tools/headless/.cache/mgba-0.6-bizhawk" >&2
    [ -n "$MAIN_ROOT" ] && echo "       tried $MAIN_ROOT/tools/headless/.cache/mgba-0.6-bizhawk" >&2
    echo "       run tools/headless/build06.sh in the main tree first" >&2
    exit 2
fi

if [ -n "${MGBA06_LIB:-}" ]; then
    LIB=$MGBA06_LIB
else
    if [ -n "${MGBA06_BUILD:-}" ]; then
        BUILD=$MGBA06_BUILD
    else
        BUILD=$(find_tree tools/headless/build06 || true)
    fi
    LIB=${BUILD:+$BUILD/core/libmgba.a}
fi

if [ -z "${LIB:-}" ] || [ ! -f "$LIB" ]; then
    echo "error: static mGBA 0.6 library not found (need libmgba.a built with -DCOLOR_16_BIT)" >&2
    echo "       MGBA06_LIB=${MGBA06_LIB:-<unset>}" >&2
    [ -n "${BUILD:-}" ] && echo "       tried $BUILD/core/libmgba.a" >&2
    echo "       run tools/headless/build06.sh in the main tree first" >&2
    exit 2
fi

CC=${CC:-cc}
mkdir -p "$(dirname "$OUT")"

# The defines and include roots mirror tools/headless/build06.sh so the
# harness sees the same struct layouts as libmgba.a (COLOR_16_BIT changes
# color_t and therefore mColor/the framebuffer size).
# shellcheck disable=SC2086
"$CC" -O2 -std=gnu99 -DCOLOR_16_BIT -DFALSE=0 -DTRUE=1 \
    -I "$SRC/include" -I "$SRC/src" -I "$SRC" \
    "$HERE/harness.c" \
    "$LIB" -lz -lm -lpthread \
    -o "$OUT"

echo "built $OUT (static mGBA 0.6: $LIB)"
