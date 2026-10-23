#!/usr/bin/env bash
# setup.sh -- one-time bootstrap for the decomp-permuter adapter (TECH-007).
#
# What it does, idempotently:
#   1. clones decomp-permuter at the pinned commit into work/tools/decomp-permuter
#      (skipped when the checkout is already there and at the pin);
#   2. creates a private venv at work/tools/permuter-venv and installs `toml`;
#      when `python3 -m venv` cannot bootstrap pip (Debian/Ubuntu without
#      python3-venv), it falls back to `venv --without-pip` + get-pip.py;
#   3. checks cpp, agbcc, timeout and the $HOME/.local/bin ARM binutils
#      (arm-none-eabi-as / arm-none-eabi-objdump) and fails with a clear
#      message when any is missing.
#
# Everything is written under work/ (git-ignored).  Nothing is committed.
#
# Network: the clone, `pip install toml` and the get-pip.py fallback all need
# network access the first time.  After setup succeeds, run.sh is offline.
#
# Usage:
#   tools/decomp/permuter/setup.sh              # bootstrap / verify
#   tools/decomp/permuter/setup.sh --check      # verify only, change nothing
#   tools/decomp/permuter/setup.sh --force      # recreate the venv, re-fetch pin
#
# Environment overrides:
#   DECOMP_PERMUTER_URL   clone URL (default: the pinned upstream repository)
#   GET_PIP_URL           get-pip.py URL (default: bootstrap.pypa.io)
#   PYTHON                interpreter used for the venv (default: python3)
#   ARM_BINUTILS_DIR      directory holding arm-none-eabi-* (default: ~/.local/bin)

set -euo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd -- "$SCRIPT_DIR/../../.." && pwd)

PERMUTER_PIN=8556c81d80d1c1af98a858c8f4dc951357f29139
PERMUTER_URL=${DECOMP_PERMUTER_URL:-https://github.com/simonlindholm/decomp-permuter}
PERMUTER_DIR="$ROOT/work/tools/decomp-permuter"
VENV_DIR="$ROOT/work/tools/permuter-venv"
GET_PIP_URL=${GET_PIP_URL:-https://bootstrap.pypa.io/get-pip.py}
GET_PIP="$ROOT/work/tools/get-pip.py"
PYTHON=${PYTHON:-python3}
ARM_BINUTILS_DIR=${ARM_BINUTILS_DIR:-$HOME/.local/bin}

CHECK_ONLY=0
FORCE=0

msg()  { printf 'permuter-setup: %s\n' "$*"; }
warn() { printf 'permuter-setup: WARNING: %s\n' "$*" >&2; }
die()  { printf 'permuter-setup: ERROR: %s\n' "$*" >&2; exit 1; }

usage() {
    cat <<'EOF'
Usage: tools/decomp/permuter/setup.sh [--check] [--force]

  --check   verify the pinned checkout, venv, toml and toolchain; make no change
  --force   recreate the venv and re-checkout the pinned permuter commit
  -h, --help
EOF
}

for arg in "$@"; do
    case "$arg" in
        --check) CHECK_ONLY=1 ;;
        --force) FORCE=1 ;;
        -h|--help) usage; exit 0 ;;
        *) usage >&2; die "unknown argument: $arg" ;;
    esac
done

# ---------------------------------------------------------------------------
# 1. Host toolchain
# ---------------------------------------------------------------------------

# The ARM binutils normally live in ~/.local/bin (see docs/howto/c-port-scratch.md).
if [ -d "$ARM_BINUTILS_DIR" ] && ! command -v arm-none-eabi-as >/dev/null 2>&1; then
    PATH="$ARM_BINUTILS_DIR:$PATH"
    export PATH
fi

require_tool() {
    local tool=$1 hint=$2
    command -v "$tool" >/dev/null 2>&1 && return 0
    if [ -x "$ARM_BINUTILS_DIR/$tool" ]; then
        die "$tool is not on PATH but exists in $ARM_BINUTILS_DIR; add this to your shell:
    export PATH=\"$ARM_BINUTILS_DIR:\$PATH\""
    fi
    die "missing $tool ($hint)"
}

require_tool cpp            "host C preprocessor; install gcc"
require_tool git            "needed to clone the pinned permuter"
require_tool timeout        "coreutils; needed for the bounded search"
require_tool arm-none-eabi-as       "install binutils-arm-none-eabi or put it in $ARM_BINUTILS_DIR"
require_tool arm-none-eabi-objdump  "install binutils-arm-none-eabi or put it in $ARM_BINUTILS_DIR"

AGBCC="$ROOT/tools/agbcc/bin/agbcc"
if [ ! -x "$AGBCC" ]; then
    die "missing $AGBCC; run tools/setup_agbcc.sh (or make setup-agbcc) first"
fi

"$PYTHON" -c 'import sys; sys.exit(0 if sys.version_info >= (3, 8) else 1)' \
    || die "$PYTHON is too old; decomp-permuter needs Python >= 3.8"

# ---------------------------------------------------------------------------
# 2. Pinned decomp-permuter checkout
# ---------------------------------------------------------------------------

permuter_head() {
    git -C "$PERMUTER_DIR" rev-parse HEAD 2>/dev/null || true
}

checkout_pin() {
    git -C "$PERMUTER_DIR" fetch --quiet origin "$PERMUTER_PIN" 2>/dev/null || \
        git -C "$PERMUTER_DIR" fetch --quiet origin
    git -C "$PERMUTER_DIR" checkout --quiet --detach "$PERMUTER_PIN"
}

if [ -e "$PERMUTER_DIR" ] && [ ! -d "$PERMUTER_DIR/.git" ]; then
    if [ "$FORCE" = 1 ]; then
        rm -rf "$PERMUTER_DIR"
    else
        die "$PERMUTER_DIR exists but is not a git checkout; re-run with --force to replace it"
    fi
fi

if [ ! -d "$PERMUTER_DIR/.git" ]; then
    if [ "$CHECK_ONLY" = 1 ]; then
        die "decomp-permuter is not set up at $PERMUTER_DIR; run setup.sh once"
    fi
    msg "cloning $PERMUTER_URL -> $PERMUTER_DIR"
    mkdir -p "$(dirname "$PERMUTER_DIR")"
    git clone --quiet "$PERMUTER_URL" "$PERMUTER_DIR"
    checkout_pin
fi

HEAD=$(permuter_head)
if [ "$HEAD" != "$PERMUTER_PIN" ]; then
    if [ "$FORCE" = 1 ] && [ "$CHECK_ONLY" = 0 ]; then
        msg "checkout is ${HEAD:-unknown}, wanted $PERMUTER_PIN; re-fetching"
        checkout_pin
        HEAD=$(permuter_head)
    fi
    if [ "$HEAD" != "$PERMUTER_PIN" ]; then
        die "decomp-permuter is at ${HEAD:-<not a checkout>}, expected the pinned $PERMUTER_PIN
    fix with: tools/decomp/permuter/setup.sh --force
    (never commit this checkout; work/ is ignored)"
    fi
fi
msg "decomp-permuter at $PERMUTER_PIN"

# ---------------------------------------------------------------------------
# 3. Private venv with `toml`
# ---------------------------------------------------------------------------

venv_python() { printf '%s/bin/python' "$VENV_DIR"; }
venv_has_toml() { "$(venv_python)" -c 'import toml' >/dev/null 2>&1; }

download_get_pip() {
    if [ -f "$GET_PIP" ]; then
        return 0
    fi
    msg "downloading get-pip.py from $GET_PIP_URL (network required)"
    if command -v curl >/dev/null 2>&1; then
        curl -fsSL "$GET_PIP_URL" -o "$GET_PIP"
    elif command -v wget >/dev/null 2>&1; then
        wget -q "$GET_PIP_URL" -O "$GET_PIP"
    else
        die "neither curl nor wget is available; install python3-venv (with ensurepip) or curl"
    fi
}

bootstrap_venv() {
    if [ "$CHECK_ONLY" = 1 ]; then
        die "venv at $VENV_DIR is missing or has no toml; run setup.sh once"
    fi
    rm -rf "$VENV_DIR"
    mkdir -p "$(dirname "$VENV_DIR")"

    if "$PYTHON" -m venv "$VENV_DIR" 2>"$ROOT/work/tools/venv.err"; then
        msg "created venv at $VENV_DIR"
    else
        warn "python3 -m venv failed (ensurepip/python3-venv missing?)"
        warn "falling back to: $PYTHON -m venv --without-pip + get-pip.py"
        warn "this fallback needs network access"
        rm -rf "$VENV_DIR"
        "$PYTHON" -m venv --without-pip "$VENV_DIR" \
            || die "$PYTHON -m venv --without-pip failed; install python3-venv"
        download_get_pip
        "$(venv_python)" "$GET_PIP" --no-warn-script-location \
            || die "get-pip.py failed; install python3-venv or bootstrap pip manually"
    fi

    if ! "$(venv_python)" -m pip --version >/dev/null 2>&1; then
        download_get_pip
        "$(venv_python)" "$GET_PIP" --no-warn-script-location \
            || die "pip bootstrap failed in $VENV_DIR"
    fi

    msg "installing toml into $VENV_DIR (network or pip cache required)"
    "$(venv_python)" -m pip install --quiet --disable-pip-version-check --no-input toml \
        || die "could not install toml; check network or pip cache"
}

if [ -x "$(venv_python)" ] && venv_has_toml; then
    msg "venv ready at $VENV_DIR"
elif [ "$CHECK_ONLY" = 1 ]; then
    if [ ! -x "$(venv_python)" ]; then
        die "venv is missing at $VENV_DIR; run setup.sh once"
    fi
    die "venv at $VENV_DIR has no toml; run setup.sh once"
else
    bootstrap_venv
fi

venv_has_toml || die "toml is still not importable from $(venv_python)"
msg "toml importable from $(venv_python)"

# ---------------------------------------------------------------------------
# 4. Done
# ---------------------------------------------------------------------------

msg "OK: pin=$PERMUTER_PIN"
msg "OK: venv=$VENV_DIR"
msg "OK: next: tools/decomp/permuter/run.sh --seed <seed.c> --target <target.s|.o>"
