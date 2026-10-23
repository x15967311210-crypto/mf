#!/usr/bin/env bash
# End-to-end objdiff pilot for SramWrite_MostRecentSaveFile (TECH-008).
#
# Builds the two objects objdiff needs and prints the match report:
#
#   target.o  assembled from the split disassembly
#             asm/disasm_0x0807e678_0807eea4_08080068.s
#   base.o    the C candidate, compiled with the project's pinned agbcc
#             (cpp -nostdinc -Iinclude -DREGION_US -> agbcc -O1 -> arm-none-eabi-as)
#
# The candidate is work/decompme/SramWrite_MostRecentSaveFile.seed.c by default;
# pass --from-c FILE to diff an arbitrary scratch file instead.  Nothing under
# src/ is read or written.
#
# Usage:
#   tools/decomp/objdiff/pilot_sram_recent.sh
#   tools/decomp/objdiff/pilot_sram_recent.sh --from-c /tmp/cand.c --json
#   tools/decomp/objdiff/pilot_sram_recent.sh --compare-text
#
# The script exits like tools/decomp/objdiff/diff.sh: 0 = objdiff scored 100 %,
# 1 = the candidate differs (the expected pilot result, ~90.71 %), 2 = a tool,
# input or setup error.  objdiff's score is a fuzzy instruction/argument match;
# --compare-text adds the authoritative byte comparison (it needs the same two
# objects, and it compares relocatable code, so cross-references show as raw
# bytes).
#
# Prerequisites: tools/decomp/objdiff/setup.sh (pinned objdiff-cli), the
# project agbcc in tools/agbcc, cpp, and arm-none-eabi-as.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"

SPLIT="asm/disasm_0x0807e678_0807eea4_08080068.s"
SYMBOL="SramWrite_MostRecentSaveFile"
DEFAULT_SEED="work/decompme/SramWrite_MostRecentSaveFile.seed.c"
DEFAULT_OUT="work/tools/objdiff/pilot"

diag() {
    printf 'objdiff pilot: %s\n' "$*" >&2
}

die() {
    printf 'objdiff pilot: %s\n' "$*" >&2
    exit 2
}

usage() {
    sed -n '2,30p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

# Same discovery order as diff.sh and compare_text.py: PATH first, then the
# project's per-user binutils install (non-interactive shells rarely have it in
# PATH).
find_as() {
    if command -v arm-none-eabi-as >/dev/null 2>&1; then
        command -v arm-none-eabi-as
    elif [ -x "$HOME/.local/bin/arm-none-eabi-as" ]; then
        printf '%s\n' "$HOME/.local/bin/arm-none-eabi-as"
    else
        return 1
    fi
}

FROM_C=""
OUT="$DEFAULT_OUT"
JSON=0
COMPARE_TEXT=0

while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help) usage; exit 0 ;;
        --from-c) [ $# -ge 2 ] || die "--from-c needs a path"; FROM_C="$2"; shift 2 ;;
        --out) [ $# -ge 2 ] || die "--out needs a directory"; OUT="$2"; shift 2 ;;
        --json) JSON=1; shift ;;
        --compare-text) COMPARE_TEXT=1; shift ;;
        *) die "unknown argument '$1' (try --help)" ;;
    esac
done

CANDIDATE="${FROM_C:-$DEFAULT_SEED}"
[ -f "$CANDIDATE" ] || die "candidate C not found: $CANDIDATE"
[ -f "$ROOT/$SPLIT" ] || die "split disassembly not found: $SPLIT (run from a worktree with the asm/ split)"

AS="$(find_as)" || die "arm-none-eabi-as not found (PATH or ~/.local/bin)"
CPP="${CPP:-cpp}"
command -v "$CPP" >/dev/null 2>&1 || die "$CPP not found (set CPP=...)"
AGBCC="$ROOT/tools/agbcc/bin/agbcc"
[ -x "$AGBCC" ] || die "agbcc not found at tools/agbcc (run: make setup-agbcc)"

case "$OUT" in
    /*) OUT_ABS="$OUT" ;;
    *) OUT_ABS="$ROOT/$OUT" ;;
esac

printf 'objdiff pilot: %s\n' "$SYMBOL"
printf '  target  %s\n' "$SPLIT"
printf '  base    %s\n' "$CANDIDATE"
printf '  objects %s\n' "$OUT_ABS"

mkdir -p "$OUT_ABS"
TARGET_OBJ="$OUT_ABS/target.o"
BASE_OBJ="$OUT_ABS/base.o"
BASE_I="$OUT_ABS/base.i"
BASE_S="$OUT_ABS/base.s"

# --- target: assemble the split disassembly ---------------------------------
# One .s file holds several functions; objdiff filters by symbol name, so the
# whole object is fine as the target.
( cd "$ROOT" && "$AS" -mcpu=arm7tdmi -I. "$SPLIT" -o "$TARGET_OBJ" ) \
    || die "assembling $SPLIT failed"

# --- base: cpp -> agbcc -> .s -> .o --------------------------------------
# agbcc emits `.section .text` with no trailing alignment; the project's own
# rule appends `.align 2, 0` so the function body lands at an even offset and
# objdiff does not see phantom 2-byte shifts.
( cd "$ROOT" && "$CPP" -nostdinc -Iinclude -DREGION_US "$CANDIDATE" >"$BASE_I" ) \
    || die "preprocessing $CANDIDATE failed"
( cd "$ROOT" && "$AGBCC" -O1 -mthumb-interwork -fhex-asm -o "$BASE_S" "$BASE_I" ) \
    || die "agbcc failed for $CANDIDATE"
printf '\t.align 2, 0\n' >>"$BASE_S"
"$AS" -mcpu=arm7tdmi -I. "$BASE_S" -o "$BASE_OBJ" \
    || die "assembling $BASE_S failed"

# --- report -----------------------------------------------------------------
set +e
diff_args=(--target "$TARGET_OBJ" --base "$BASE_OBJ" --symbol "$SYMBOL")
if [ "$JSON" = 1 ]; then
    diff_args+=(--json)
fi
"$HERE/diff.sh" "${diff_args[@]}"
rc=$?
set -e

if [ "$COMPARE_TEXT" = 1 ]; then
    printf '\n--- byte comparison (tools/decomp/compare_text.py) ---\n'
    set +e
    python3 "$ROOT/tools/decomp/compare_text.py" \
        --baseline "$BASE_OBJ" --candidate "$TARGET_OBJ" --symbol "$SYMBOL"
    ct_rc=$?
    set -e
    printf 'compare_text exit %d (0 = byte-identical, 1 = differs)\n' "$ct_rc"
fi

exit "$rc"
