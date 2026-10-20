#!/usr/bin/env bash
# Public CI gate (BUILD-004).
#
# This gate runs on a clean checkout with no baserom, no extracted data/, no
# agbcc, no ARM toolchain, and no mf_us.gba/mf_us.elf/mf_us.map.  It therefore
# only exercises host/Python checks, the host unit tests and the tool
# self-checks.  It never touches the network and needs no secrets.
#
# Usage:
#   bash tools/ci/public_gate.sh
#   make public-gate
#
# On success it prints exactly `PUBLIC-CI: PASS`.
set -euo pipefail

usage() {
    cat <<'EOF'
usage: bash tools/ci/public_gate.sh

Run the ROM-free public CI gate.  Requires only bash, GNU make, a host C
compiler and Python 3; no baserom, agbcc, ARM binutils or extracted data.
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

# Keep the checkout clean and make repeated runs byte-stable.
export PYTHONDONTWRITEBYTECODE=1
export LC_ALL=C

on_exit() {
    status=$?
    if [ "$status" -ne 0 ]; then
        echo "PUBLIC-CI: FAIL (status $status)" >&2
    fi
}
trap on_exit EXIT

step() {
    printf '\n==> %s\n' "$*"
    "$@"
}

echo "PUBLIC-CI: ROM-free gate in $ROOT"

step make doctor-source
step make host-test
step make content-check
step python3 tools/doctor.py --self-check
step python3 tools/data_manifest.py --self-check
step python3 tools/shift/check_relocs.py --self-check
step python3 tools/shift/audit_asm.py --self-check
step python3 tools/shift/audit_blobs.py --self-check
step python3 tools/shift/postlink_pointer_scan.py --self-check

echo
echo "PUBLIC-CI: PASS"
