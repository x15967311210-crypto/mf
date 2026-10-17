#!/usr/bin/env bash
# Build the headless mGBA harness against an existing mGBA source/build tree.
#
#   MGBA_SRC=/path/to/mgba-src MGBA_BUILD=/path/to/mgba-build \
#     tests/emulator/build_harness.sh [output]
#
# The build tree must contain CMakeFiles/mgba.dir/flags.make (the shared
# library target).  Nothing is downloaded and no ROM is read.
set -eu

src=${MGBA_SRC:?set MGBA_SRC to the mGBA source directory}
build=${MGBA_BUILD:?set MGBA_BUILD to the mGBA build directory}
out=${1:-tests/emulator/bin/mgba-harness}

flags="$build/CMakeFiles/mgba.dir/flags.make"
if [ ! -f "$flags" ]; then
    echo "error: $flags not found; build mGBA's shared library target first" >&2
    exit 2
fi

defs=$(sed -n 's/^C_DEFINES = //p' "$flags")
incs=$(sed -n 's/^C_INCLUDES = //p' "$flags")
mkdir -p "$(dirname "$out")"

# shellcheck disable=SC2086
gcc -O2 $defs $incs tests/emulator/harness.c \
    -L"$build" -lmgba -Wl,-rpath,"$build" -o "$out"

echo "built $out"
