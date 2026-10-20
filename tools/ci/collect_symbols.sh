#!/usr/bin/env bash
# Collect the text-only build-symbols artifact (BUILD-004).
#
# The protected CI job uploads this directory as an artifact; a future symbols
# branch can publish the same directory.  Nothing ROM-derived is copied: only
# the linker map and the text/JSON audit outputs.
#
# Usage:
#   bash tools/ci/collect_symbols.sh [--out DIR]
#   OUT_DIR=/path/to/out bash tools/ci/collect_symbols.sh
#   make collect-symbols
#
# Environment:
#   OUT_DIR        output directory (default: tools/ci/out/symbols)
#   MAP            linker map (default: <repo>/mf_us.map); required
#   SYMBOLS_JSON   default: <repo>/work/shift/symbols.json (optional)
#   ABS_REFS_JSON  default: <repo>/work/shift/abs_refs.json  (optional)
#
# Exits nonzero when mf_us.map is missing.  Never copies mf_us.gba, mf_us.elf,
# savestates or extracted data blobs.
set -euo pipefail

usage() {
    cat <<'EOF'
usage: bash tools/ci/collect_symbols.sh [--out DIR]

Collect mf_us.map plus work/shift/symbols.json and work/shift/abs_refs.json
(when present) into a text-only symbols artifact.  Also writes SHA256SUMS,
BUILD.txt and README.md.  Requires the normal build's mf_us.map; exits nonzero
when it is missing.

Environment: OUT_DIR (default tools/ci/out/symbols), MAP, SYMBOLS_JSON,
ABS_REFS_JSON.
EOF
}

HERE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd -- "$HERE/../.." && pwd)"
cd "$ROOT"

OUT_DIR="${OUT_DIR:-tools/ci/out/symbols}"

while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help)
            usage
            exit 0
            ;;
        --out)
            [ $# -ge 2 ] || { echo "error: --out needs a directory" >&2; exit 2; }
            OUT_DIR="$2"
            shift 2
            ;;
        --out=*)
            OUT_DIR="${1#--out=}"
            shift
            ;;
        *)
            usage >&2
            exit 2
            ;;
    esac
done

export PYTHONDONTWRITEBYTECODE=1
export LC_ALL=C

# Resolve optional relative paths against the repository root so the script is
# independent of the caller's working directory.
resolve() {
    case "$1" in
        /*) printf '%s\n' "$1" ;;
        *)  printf '%s/%s\n' "$ROOT" "$1" ;;
    esac
}

OUT_DIR="$(resolve "$OUT_DIR")"
MAP_PATH="$(resolve "${MAP:-mf_us.map}")"
SYMBOLS_PATH="$(resolve "${SYMBOLS_JSON:-work/shift/symbols.json}")"
ABS_REFS_PATH="$(resolve "${ABS_REFS_JSON:-work/shift/abs_refs.json}")"

if [ ! -f "$MAP_PATH" ]; then
    echo "error: linker map not found: $MAP_PATH" >&2
    echo "       run the normal ROM build first (the map is produced by make)." >&2
    exit 1
fi

mkdir -p "$OUT_DIR"

# Drop only the files this script owns, so a rerun cannot leave stale inputs.
rm -f "$OUT_DIR/mf_us.map" \
      "$OUT_DIR/symbols.json" \
      "$OUT_DIR/abs_refs.json" \
      "$OUT_DIR/SHA256SUMS" \
      "$OUT_DIR/BUILD.txt" \
      "$OUT_DIR/README.md"

cp "$MAP_PATH" "$OUT_DIR/mf_us.map"
files=(mf_us.map)

if [ -f "$SYMBOLS_PATH" ]; then
    cp "$SYMBOLS_PATH" "$OUT_DIR/symbols.json"
    files+=(symbols.json)
fi
if [ -f "$ABS_REFS_PATH" ]; then
    cp "$ABS_REFS_PATH" "$OUT_DIR/abs_refs.json"
    files+=(abs_refs.json)
fi

normal_sha="$(awk 'NR == 1 { print $1 }' "$ROOT/mf_us.sha1" 2>/dev/null || true)"
[ -n "$normal_sha" ] || normal_sha="unknown"
git_commit="$(git -C "$ROOT" rev-parse --verify HEAD 2>/dev/null || true)"
[ -n "$git_commit" ] || git_commit="unknown"
git_branch="$(git -C "$ROOT" rev-parse --abbrev-ref HEAD 2>/dev/null || true)"
[ -n "$git_branch" ] || git_branch="unknown"

cat > "$OUT_DIR/BUILD.txt" <<EOF
normal_sha1: $normal_sha
git_commit: $git_commit
git_branch: $git_branch
date_utc: $(date -u +%Y-%m-%dT%H:%M:%SZ)
collector: tools/ci/collect_symbols.sh
EOF

cat > "$OUT_DIR/README.md" <<'EOF'
# mf_us build symbols

Text-only artifact produced by `tools/ci/collect_symbols.sh`.

| File | Contents |
|---|---|
| `mf_us.map` | Linker map from the normal ROM build. |
| `symbols.json` | `tools/shift/map_symbols.py` output (when present). |
| `abs_refs.json` | `tools/shift/audit_asm.py` output (when present). |
| `BUILD.txt` | Normal ROM SHA1, git commit/branch and UTC date. |
| `SHA256SUMS` | SHA256 of every file in this directory except itself. |

These files describe ROM addresses but are generated text, not source. Do not
commit this directory, and never add `mf_us.gba`, `mf_us.elf`, savestates or
extracted data blobs here.
EOF

# Deterministic, sorted SHA256SUMS over the known text files.
python3 - "$OUT_DIR" "${files[@]}" BUILD.txt README.md > "$OUT_DIR/SHA256SUMS" <<'PY'
import hashlib
import pathlib
import sys

out = pathlib.Path(sys.argv[1])
for name in sorted(sys.argv[2:]):
    digest = hashlib.sha256((out / name).read_bytes()).hexdigest()
    print(f"{digest}  {name}")
PY

echo "SYMBOLS-ARTIFACT: $OUT_DIR"
for name in "${files[@]}" BUILD.txt README.md SHA256SUMS; do
    echo "  $name"
done
