#!/usr/bin/env bash
# setup.sh -- one-time bootstrap for the m2c decompiler adapter (TECH-009).
#
# What it does, idempotently:
#   1. clones m2c at the pinned commit into work/tools/m2c (skipped when that
#      checkout is already there and at the pin);
#   2. creates a private venv at work/tools/m2c-venv and `pip install -e`s the
#      pinned clone, which pulls the only runtime dependency, `graphviz`;
#      when `python3 -m venv` cannot bootstrap pip (Debian/Ubuntu without
#      python3-venv) it falls back to `venv --without-pip` + get-pip.py;
#   3. verifies `import graphviz` and the `m2c` console script in that venv.
#
# m2c is GPL-3.0-only and is NOT vendored: the clone lives under work/, which is
# git-ignored.  Nothing here is committed and nothing here is a build gate.
#
# Network: the clone, `pip install -e .` (build backend + graphviz) and the
# get-pip.py fallback need network (or a warm pip cache) the first time.
# After setup succeeds, run.sh is offline.
#
# Usage:
#   tools/decomp/m2c/setup.sh            # bootstrap / verify
#   tools/decomp/m2c/setup.sh --check    # verify only, change nothing
#   tools/decomp/m2c/setup.sh --force    # recreate the venv, re-fetch the pin
#
# Environment overrides:
#   M2C_URL      clone URL (default: the pinned upstream repository)
#   GET_PIP_URL  get-pip.py URL (default: bootstrap.pypa.io)
#   PYTHON       interpreter used for the venv (default: python3)

set -euo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd -- "$SCRIPT_DIR/../../.." && pwd)

M2C_PIN=c632946b8cfbe8fce442b522dba92dfa72f1f317
M2C_URL=${M2C_URL:-https://github.com/matt-kempster/m2c}
M2C_DIR="$ROOT/work/tools/m2c"
VENV_DIR="$ROOT/work/tools/m2c-venv"
GET_PIP_URL=${GET_PIP_URL:-https://bootstrap.pypa.io/get-pip.py}
GET_PIP="$ROOT/work/tools/get-pip.py"
PYTHON=${PYTHON:-python3}

CHECK_ONLY=0
FORCE=0

msg()  { printf 'm2c-setup: %s\n' "$*"; }
warn() { printf 'm2c-setup: WARNING: %s\n' "$*" >&2; }
die()  { printf 'm2c-setup: ERROR: %s\n' "$*" >&2; exit 1; }

usage() {
    cat <<'EOF'
Usage: tools/decomp/m2c/setup.sh [--check] [--force]

  --check   verify the pinned checkout, venv, graphviz and m2c CLI; make no change
  --force   recreate the venv and re-checkout the pinned m2c commit
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

"$PYTHON" -c 'import sys; sys.exit(0 if sys.version_info >= (3, 8) else 1)' \
    || die "$PYTHON is too old; m2c needs Python >= 3.8"

command -v git >/dev/null 2>&1 || die "missing git (needed to clone the pinned m2c)"

# ---------------------------------------------------------------------------
# 1. Pinned m2c checkout (work/tools/m2c, git-ignored)
# ---------------------------------------------------------------------------

m2c_head() {
    git -C "$M2C_DIR" rev-parse HEAD 2>/dev/null || true
}

checkout_pin() {
    git -C "$M2C_DIR" fetch --quiet origin "$M2C_PIN" 2>/dev/null || \
        git -C "$M2C_DIR" fetch --quiet origin
    git -C "$M2C_DIR" checkout --quiet --detach "$M2C_PIN"
}

if [ -e "$M2C_DIR" ] && [ ! -d "$M2C_DIR/.git" ]; then
    if [ "$FORCE" = 1 ]; then
        rm -rf "$M2C_DIR"
    else
        die "$M2C_DIR exists but is not a git checkout; re-run with --force to replace it"
    fi
fi

if [ ! -d "$M2C_DIR/.git" ]; then
    if [ "$CHECK_ONLY" = 1 ]; then
        die "m2c is not set up at $M2C_DIR; run setup.sh once"
    fi
    msg "cloning $M2C_URL -> $M2C_DIR"
    mkdir -p "$(dirname "$M2C_DIR")"
    git clone --quiet "$M2C_URL" "$M2C_DIR"
    checkout_pin
fi

HEAD=$(m2c_head)
if [ "$HEAD" != "$M2C_PIN" ]; then
    if [ "$FORCE" = 1 ] && [ "$CHECK_ONLY" = 0 ]; then
        msg "checkout is ${HEAD:-unknown}, wanted $M2C_PIN; re-fetching"
        checkout_pin
        HEAD=$(m2c_head)
    fi
    if [ "$HEAD" != "$M2C_PIN" ]; then
        die "m2c is at ${HEAD:-<not a checkout>}, expected the pinned $M2C_PIN
    fix with: tools/decomp/m2c/setup.sh --force
    (never commit this checkout; m2c is GPL-3.0-only and work/ is ignored)"
    fi
fi
msg "m2c at $M2C_PIN"

# ---------------------------------------------------------------------------
# 2. Private venv with m2c (editable) + graphviz
# ---------------------------------------------------------------------------

venv_python() { printf '%s/bin/python' "$VENV_DIR"; }
venv_has_m2c() {
    [ -x "$VENV_DIR/bin/m2c" ] || return 1
    "$(venv_python)" -c 'import graphviz, m2c' >/dev/null 2>&1 || return 1
    "$VENV_DIR/bin/m2c" -h >/dev/null 2>&1
}

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
        die "venv at $VENV_DIR is missing or incomplete; run setup.sh once"
    fi
    rm -rf "$VENV_DIR"
    mkdir -p "$(dirname "$VENV_DIR")"

    if "$PYTHON" -m venv "$VENV_DIR" 2>"$ROOT/work/tools/m2c-venv.err"; then
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

    msg "installing the pinned m2c into $VENV_DIR (network or pip cache required)"
    "$(venv_python)" -m pip install --quiet --disable-pip-version-check --no-input \
        -e "$M2C_DIR" \
        || die "pip install -e $M2C_DIR failed; check network, pip cache or poetry-core availability"
}

if venv_has_m2c; then
    msg "venv ready at $VENV_DIR"
elif [ "$CHECK_ONLY" = 1 ]; then
    if [ ! -x "$(venv_python)" ]; then
        die "venv is missing at $VENV_DIR; run setup.sh once"
    fi
    die "venv at $VENV_DIR cannot import graphviz/m2c or run the m2c CLI; run setup.sh"
else
    bootstrap_venv
fi

venv_has_m2c || die "m2c/graphviz still not usable from $VENV_DIR"

# ---------------------------------------------------------------------------
# 3. Verify the pieces run.sh depends on
# ---------------------------------------------------------------------------

"$(venv_python)" - <<'PY' || die "graphviz import check failed"
import graphviz
print("m2c-setup: graphviz %s" % getattr(graphviz, "__version__", "?"))
PY

"$VENV_DIR/bin/m2c" -h >/dev/null 2>&1 || die "m2c CLI at $VENV_DIR/bin/m2c is broken"
msg "m2c CLI importable: $VENV_DIR/bin/m2c"

# ---------------------------------------------------------------------------
# 4. Done
# ---------------------------------------------------------------------------

msg "OK: pin=$M2C_PIN"
msg "OK: venv=$VENV_DIR"
msg "OK: next: tools/decomp/m2c/run.sh --self-check"
