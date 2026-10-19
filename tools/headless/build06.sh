#!/usr/bin/env bash
# Build the movie-native mGBA 0.6 headless runner on Linux/WSL.
#
# The source is pinned to the BizHawk 2.3.1 mgba submodule commit
# (TASVideos/mgba, branch bizhawk-0.6). The watchpoint patch is optional for
# normal parity runs but is part of the build by default.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
COMMIT="db0041340ff260424f38772df4f286fc3907c1c8"
CACHE="${MGBA06_CACHE:-$HERE/.cache}"
SRC="${MGBA06_SRC:-$CACHE/mgba-0.6-bizhawk}"
BUILD="${BUILD06_DIR:-$HERE/build06}"
CORE_BUILD="$BUILD/core"
CC="${CC:-cc}"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"

mkdir -p "$CACHE" "$BUILD"

if [ ! -d "$SRC/.git" ]; then
    git clone --filter=blob:none https://github.com/TASVideos/mgba.git "$SRC"
fi
if [ "$(git -C "$SRC" rev-parse HEAD 2>/dev/null || true)" != "$COMMIT" ]; then
    git -C "$SRC" fetch --depth 1 origin "$COMMIT"
    git -C "$SRC" checkout -q FETCH_HEAD
fi

if [ ! -f "$SRC/include/mgba/internal/gba/mf_watch.h" ]; then
    # The upstream checkout may use CRLF depending on git config; the patch
    # is LF-only, so normalize the files it touches first.
    for f in src/gba/memory.c src/platform/bizhawk/bizinterface.c \
             src/platform/bizhawk/mingw/Makefile; do
        sed -i 's/\r$//' "$SRC/$f"
    done
    git -C "$SRC" apply "$HERE/mgba06_watch.patch"
fi

cmake -S "$SRC" -B "$CORE_BUILD" -G Ninja \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5.0 \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_FLAGS=-DCOLOR_16_BIT \
    -DBUILD_STATIC=ON -DBUILD_SHARED=OFF \
    -DBUILD_PERF=OFF -DBUILD_TEST=OFF -DBUILD_SUITE=OFF \
    -DBUILD_QT=OFF -DBUILD_SDL=OFF \
    -DUSE_FFMPEG=OFF -DUSE_PNG=OFF -DUSE_ZLIB=OFF -DUSE_LIBZIP=OFF \
    -DUSE_SQLITE3=OFF -DUSE_ELF=OFF -DUSE_MAGICK=OFF -DUSE_LZMA=OFF \
    -DUSE_DEBUGGERS=OFF -DUSE_GDB_STUB=OFF -DUSE_EDITLINE=OFF \
    -DBUILD_GL=OFF -DBUILD_GLES2=OFF
cmake --build "$CORE_BUILD" --target mgba -- -j "$JOBS"

"$CC" -O2 -std=gnu99 -fgnu89-inline -DCOLOR_16_BIT -DFALSE=0 -DTRUE=1 \
    -I "$SRC/include" -I "$SRC/src" -I "$SRC" \
    -c "$SRC/src/platform/bizhawk/bizinterface.c" -o "$BUILD/bizinterface06.o"
"$CC" -O2 -std=gnu99 -DCOLOR_16_BIT \
    -I "$SRC/include" -I "$SRC/src" -I "$SRC" \
    -c "$SRC/src/gba/mf_watch.c" -o "$BUILD/mf_watch06.o"

"$CC" -O2 -std=gnu99 \
    -I "$HERE/linux_shim" -I "$SRC/include" -I "$SRC/src" -I "$SRC" \
    -o "$BUILD/mf_bizhawk_linux" \
    "$HERE/mf_bizhawk_dll.c" \
    "$BUILD/bizinterface06.o" "$BUILD/mf_watch06.o" \
    "$CORE_BUILD/libmgba.a" "$HERE/linux_shim/linux_shim.c" \
    -lz -lm -lpthread

echo "built: $BUILD/mf_bizhawk_linux"
