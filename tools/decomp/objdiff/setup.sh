#!/usr/bin/env bash
# Install the pinned objdiff-cli release (TECH-008).
#
# objdiff is a third-party Rust binary; neither its source nor the binary is
# committed.  The download goes to the ignored work/tools/objdiff/ directory.
# Pin: encounter/objdiff v3.8.3 (2026-10-19), Linux release assets only.
#
# Usage:
#   tools/decomp/objdiff/setup.sh            # download if missing/wrong
#   tools/decomp/objdiff/setup.sh --force    # re-download the pinned asset
#   tools/decomp/objdiff/setup.sh --check    # verify only, never download
#
# Exit status: 0 installed/verified, 1 verification failed, 2 setup error.
# A missing network, curl/wget/sha256sum or unsupported OS/arch fails loudly;
# there is no silent fallback to an unpinned version.
set -euo pipefail

OBJDIFF_VERSION="3.8.3"
OBJDIFF_RELEASE_DATE="2026-10-19"
OBJDIFF_REPO="encounter/objdiff"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
DEST_DIR="$ROOT/work/tools/objdiff"
DEST="$DEST_DIR/objdiff-cli"

usage() {
    sed -n '2,18p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

die() {
    printf 'objdiff setup: %s\n' "$*" >&2
    exit 2
}

case "${1:-}" in
    -h|--help) usage; exit 0 ;;
    --check) MODE=check ;;
    --force) MODE=force ;;
    "") MODE=install ;;
    *) die "unknown argument '$1' (try --help)" ;;
esac

# --- pinned asset table -----------------------------------------------------
case "$(uname -s):$(uname -m)" in
    Linux:x86_64|Linux:amd64)
        ASSET="objdiff-cli-linux-x86_64"
        SHA256="e823ae932a56c68dcd86b68d12f2268c953e0c027402162c8a6dfa6a00d65008"
        ;;
    Linux:aarch64|Linux:arm64)
        ASSET="objdiff-cli-linux-aarch64"
        SHA256="0e630457e2f33a43da3723e195ecd0b39b683a6a83122955fdc68c5b17183cbc"
        ;;
    *)
        die "no pinned objdiff-cli asset for $(uname -s) $(uname -m); pin one in tools/decomp/objdiff/setup.sh (upstream releases: https://github.com/$OBJDIFF_REPO/releases/tag/v$OBJDIFF_VERSION)"
        ;;
esac

URL="https://github.com/$OBJDIFF_REPO/releases/download/v$OBJDIFF_VERSION/$ASSET"

sha256_of() {
    if command -v sha256sum >/dev/null 2>&1; then
        sha256sum "$1" | cut -d' ' -f1
    elif command -v shasum >/dev/null 2>&1; then
        shasum -a 256 "$1" | cut -d' ' -f1
    else
        die "sha256sum/shasum is required to verify the downloaded binary"
    fi
}

installed_version() {
    [ -x "$DEST" ] || return 1
    "$DEST" --version 2>/dev/null | head -n 1
}

version_ok() {
    [ "$(installed_version || true)" = "objdiff-cli $OBJDIFF_VERSION" ]
}

if [ "$MODE" = check ]; then
    if version_ok; then
        printf 'objdiff-cli %s OK (%s)\n' "$OBJDIFF_VERSION" "$DEST"
        exit 0
    fi
    printf 'objdiff-cli %s NOT installed or wrong version at %s\n' \
        "$OBJDIFF_VERSION" "$DEST" >&2
    printf 'run: %s\n' "tools/decomp/objdiff/setup.sh" >&2
    exit 1
fi

if [ "$MODE" = install ] && version_ok; then
    printf 'objdiff-cli %s already installed (%s)\n' "$OBJDIFF_VERSION" "$DEST"
    exit 0
fi

if ! command -v curl >/dev/null 2>&1 && ! command -v wget >/dev/null 2>&1; then
    die "curl or wget is required to download $URL"
fi

mkdir -p "$DEST_DIR"
TMP="$(mktemp "$DEST_DIR/.objdiff-cli.XXXXXX")"
trap 'rm -f "$TMP"' EXIT

printf 'objdiff setup: downloading %s v%s (%s)\n' "$OBJDIFF_REPO" "$OBJDIFF_VERSION" "$ASSET"
if command -v curl >/dev/null 2>&1; then
    curl --fail --silent --show-error --location --retry 2 --connect-timeout 20 \
        --output "$TMP" "$URL" \
        || die "download failed: $URL (network/proxy unavailable?)"
else
    wget --quiet --output-document="$TMP" "$URL" \
        || die "download failed: $URL (network/proxy unavailable?)"
fi

ACTUAL="$(sha256_of "$TMP")"
if [ "$ACTUAL" != "$SHA256" ]; then
    die "SHA-256 mismatch for $ASSET: expected $SHA256, got $ACTUAL"
fi

chmod +x "$TMP"
mv "$TMP" "$DEST"
trap - EXIT

if ! version_ok; then
    die "downloaded binary did not report 'objdiff-cli $OBJDIFF_VERSION'"
fi

printf 'objdiff-cli %s installed (%s, release %s, sha256 %s)\n' \
    "$OBJDIFF_VERSION" "$DEST" "$OBJDIFF_RELEASE_DATE" "$SHA256"
