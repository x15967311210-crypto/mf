#!/bin/sh
# Build and install the pinned agbcc into tools/agbcc.
#
# The pin lives in tools/agbcc-version (one lowercase hex commit).  The script
# is idempotent: when tools/agbcc/bin/agbcc exists and the stamp file
# tools/agbcc/.agbcc-commit matches the pin, it prints OK and exits 0.
#
# Usage:
#   tools/setup_agbcc.sh                 # clone/fetch, build, install
#   tools/setup_agbcc.sh --check-only    # verify the local install, no build
#   AGBCC_CHECK_ONLY=1 tools/setup_agbcc.sh
#   AGBCC_SRC=/path/to/scratch tools/setup_agbcc.sh
#
# The scratch checkout defaults to ${TMPDIR:-/tmp}/opencode/agbcc-src.  Both
# tools/agbcc and tools/agbcc-src are ignored by Git; never commit either.

set -eu

UPSTREAM_URL="${AGBCC_URL:-https://github.com/pret/agbcc.git}"

REPO_ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
PIN_FILE="$REPO_ROOT/tools/agbcc-version"
INSTALL_DIR="$REPO_ROOT/tools/agbcc"
STAMP="$INSTALL_DIR/.agbcc-commit"
SRC_DIR="${AGBCC_SRC:-${TMPDIR:-/tmp}/opencode/agbcc-src}"
CHECK_ONLY="${AGBCC_CHECK_ONLY:-0}"

usage() {
    cat <<EOF
Usage: tools/setup_agbcc.sh [--check-only]

Clone, build and install the agbcc commit pinned in tools/agbcc-version into
tools/agbcc.  The build happens in AGBCC_SRC (default:
\${TMPDIR:-/tmp}/opencode/agbcc-src) and nothing is committed.

Options:
  --check-only       only verify the existing tools/agbcc install; do not
                     clone or build (also AGBCC_CHECK_ONLY=1)
  -h, --help         show this message

Environment:
  AGBCC_SRC          scratch checkout directory
  AGBCC_URL          upstream repository (default: pret/agbcc)
  AGBCC_CHECK_ONLY   1 is the same as --check-only
  TOOLCHAIN          ARM binutils prefix or directory, used to find
                     arm-none-eabi-as/ar while building agbcc
EOF
}

for arg in "$@"; do
    case "$arg" in
        --check-only) CHECK_ONLY=1 ;;
        -h|--help) usage; exit 0 ;;
        *)
            echo "error: unknown argument: $arg" >&2
            usage >&2
            exit 2
            ;;
    esac
done

if [ ! -f "$PIN_FILE" ]; then
    echo "error: missing pin file: $PIN_FILE" >&2
    exit 1
fi

PIN=$(tr -d '[:space:]' < "$PIN_FILE" | tr 'A-F' 'a-f')
case "$PIN" in
    ''|*[!0-9a-f]*)
        echo "error: $PIN_FILE must contain one lowercase hex commit" >&2
        exit 1
        ;;
esac
if [ "${#PIN}" -ne 40 ]; then
    echo "error: $PIN_FILE must contain a full 40-character commit (got ${#PIN})" >&2
    exit 1
fi

read_stamp() {
    [ -f "$STAMP" ] || return 1
    tr -d '[:space:]' < "$STAMP" | tr 'A-F' 'a-f'
}

installed_ok() {
    [ -f "$INSTALL_DIR/bin/agbcc" ] || return 1
    have=$(read_stamp) || return 1
    [ "$have" = "$PIN" ]
}

if installed_ok; then
    echo "OK: agbcc $PIN is already installed in tools/agbcc"
    exit 0
fi

if [ "$CHECK_ONLY" = "1" ]; then
    echo "check-only: agbcc is not installed at the pinned commit" >&2
    if [ ! -f "$INSTALL_DIR/bin/agbcc" ]; then
        echo "check-only: missing tools/agbcc/bin/agbcc" >&2
    fi
    if [ ! -f "$STAMP" ]; then
        echo "check-only: missing tools/agbcc/.agbcc-commit" >&2
    else
        have=$(read_stamp 2>/dev/null || true)
        if [ "$have" != "$PIN" ]; then
            echo "check-only: stamp mismatch (expected $PIN, found $have)" >&2
        fi
    fi
    echo "check-only: run 'make setup-agbcc' to build the pinned toolchain" >&2
    exit 1
fi

# agbcc's build.sh insists on arm-none-eabi-as/ar on PATH.  Honour TOOLCHAIN
# (a prefix such as /path/arm-none-eabi- or a directory holding the tools) and
# the per-user bin directory used by this project's environment.
add_path_dir() {
    [ -d "$1" ] || return 0
    case ":$PATH:" in
        *":$1:"*) ;;
        *) PATH="$1:$PATH" ;;
    esac
}

add_path_dir "${HOME:-}/.local/bin"
if [ -n "${TOOLCHAIN:-}" ]; then
    if [ -d "$TOOLCHAIN" ]; then
        add_path_dir "$TOOLCHAIN"
    else
        case "$TOOLCHAIN" in
            */arm-none-eabi-) add_path_dir "${TOOLCHAIN%/arm-none-eabi-}" ;;
            */*) add_path_dir "$(dirname -- "$TOOLCHAIN")" ;;
        esac
    fi
fi
export PATH

for cmd in git make cc arm-none-eabi-as arm-none-eabi-ar; do
    if ! command -v "$cmd" >/dev/null 2>&1; then
        echo "error: required build command not found: $cmd" >&2
        if [ "$cmd" = "arm-none-eabi-as" ] || [ "$cmd" = "arm-none-eabi-ar" ]; then
            echo "hint: export TOOLCHAIN=\$HOME/.local/bin/arm-none-eabi-" >&2
            echo "hint: or install binutils-arm-none-eabi" >&2
        fi
        exit 1
    fi
done

mkdir -p "$(dirname -- "$SRC_DIR")"

if [ -e "$SRC_DIR" ] && [ ! -d "$SRC_DIR/.git" ]; then
    echo "error: AGBCC_SRC exists but is not a git checkout: $SRC_DIR" >&2
    echo "hint: remove it or set AGBCC_SRC to another directory" >&2
    exit 1
fi

if [ ! -d "$SRC_DIR/.git" ]; then
    echo "Cloning agbcc into $SRC_DIR"
    git init -q "$SRC_DIR"
    git -C "$SRC_DIR" remote add origin "$UPSTREAM_URL"
else
    if git -C "$SRC_DIR" remote get-url origin >/dev/null 2>&1; then
        git -C "$SRC_DIR" remote set-url origin "$UPSTREAM_URL"
    else
        git -C "$SRC_DIR" remote add origin "$UPSTREAM_URL"
    fi
fi

current=$(git -C "$SRC_DIR" rev-parse --verify HEAD 2>/dev/null || true)
checkout_changed=0
if [ "$current" != "$PIN" ]; then
    echo "Fetching agbcc $PIN"
    git -C "$SRC_DIR" fetch --quiet --depth 1 origin "$PIN"
    git -C "$SRC_DIR" checkout -q --detach FETCH_HEAD
    checkout_changed=1
fi

current=$(git -C "$SRC_DIR" rev-parse HEAD)
if [ "$current" != "$PIN" ]; then
    echo "error: checkout is $current, expected pin $PIN" >&2
    exit 1
fi

need_build=1
if [ "$checkout_changed" = "0" ] && [ -x "$SRC_DIR/agbcc" ] && [ -f "$SRC_DIR/old_agbcc" ] \
        && [ -f "$SRC_DIR/agbcc_arm" ] && [ -f "$SRC_DIR/libgcc.a" ] \
        && [ -f "$SRC_DIR/libc.a" ]; then
    need_build=0
fi

if [ "$need_build" = "1" ]; then
    echo "Building agbcc $PIN (upstream builds serially; this takes a few minutes)"
    ( cd "$SRC_DIR" && ./build.sh )
else
    echo "Using existing agbcc build in $SRC_DIR"
fi

echo "Installing agbcc into tools/agbcc"
( cd "$SRC_DIR" && ./install.sh "$REPO_ROOT" )

if [ ! -f "$INSTALL_DIR/bin/agbcc" ]; then
    echo "error: install finished but tools/agbcc/bin/agbcc is missing" >&2
    exit 1
fi

mkdir -p "$INSTALL_DIR"
printf '%s\n' "$PIN" > "$STAMP"
echo "OK: installed agbcc $PIN into tools/agbcc"
