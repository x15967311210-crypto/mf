#!/usr/bin/env bash
# import_sram_recent.sh -- TECH-007 concrete pilot for SramWrite_MostRecentSaveFile.
#
# Reproduces the bounded permuter pilot from a clean tree:
#
#   1. extracts the function body and its literal pool (0x08080068, 0x8C bytes)
#      from asm/disasm_0x0807e678_0807eea4_08080068.s into a standalone .s;
#   2. assembles the raw body and compares it with the baseline ROM when
#      mf_us.gba is present (relocated words excluded);
#   3. symbolicates the literal pool (0x03000B8D -> gMostRecentSaveFile) so the
#      target object carries relocations, exactly like the compiled candidate;
#   4. assembles the target object with arm-none-eabi-as;
#   5. copies the hand-tightened 435-score seed and calls run.sh.
#
# Everything is written under work/ (git-ignored); nothing is committed.  A
# score-0 candidate is left in the permuter output directory for an engine-dev
# to verify through a scratch build -- this script never touches src/.
#
# Usage:
#   tools/decomp/permuter/import_sram_recent.sh            # bounded search
#   tools/decomp/permuter/import_sram_recent.sh --debug    # base score only
#   tools/decomp/permuter/import_sram_recent.sh --timeout 900 --jobs 8
#
# Extra arguments are passed through to run.sh.

set -euo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd -- "$SCRIPT_DIR/../../.." && pwd)

FUNC=SramWrite_MostRecentSaveFile
FUNC_ADDR=0x08080068
FUNC_SIZE=0x8C
LAST_LITERAL=_080800F0
ASM_FILE="$ROOT/asm/disasm_0x0807e678_0807eea4_08080068.s"
BASELINE_ROM=${BASELINE_ROM:-$ROOT/mf_us.gba}
OUT_DIR="$ROOT/work/decompme"
TARGET_S="$OUT_DIR/$FUNC.target.s"
TARGET_O="$OUT_DIR/$FUNC.target.o"
TARGET_RAW_S="$OUT_DIR/$FUNC.target.raw.s"
TARGET_RAW_O="$OUT_DIR/$FUNC.target.raw.o"
SEED_SRC="$SCRIPT_DIR/seeds/$FUNC.c"
SEED_COPY="$OUT_DIR/$FUNC.seed435.c"

msg()  { printf 'import-sram: %s\n' "$*"; }
die()  { printf 'import-sram: ERROR: %s\n' "$*" >&2; exit 1; }

if [ "${1:-}" = "-h" ] || [ "${1:-}" = "--help" ]; then
    sed -n '2,30p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
    exit 0
fi

if [ -d "$HOME/.local/bin" ] && ! command -v arm-none-eabi-as >/dev/null 2>&1; then
    PATH="$HOME/.local/bin:$PATH"
    export PATH
fi
command -v arm-none-eabi-as >/dev/null 2>&1 || die "missing arm-none-eabi-as"
command -v arm-none-eabi-objcopy >/dev/null 2>&1 || die "missing arm-none-eabi-objcopy"

[ -f "$ASM_FILE" ] || die "missing split assembly: $ASM_FILE"
[ -f "$SEED_SRC" ] || die "missing seed: $SEED_SRC"
mkdir -p "$OUT_DIR"

# ---------------------------------------------------------------------------
# 1. Extract the function and its literal pool (through the next
#    thumb_func_start, which is the next function in the split file).
# ---------------------------------------------------------------------------

msg "extracting $FUNC from ${ASM_FILE#$ROOT/}"
BODY=$(mktemp "${TMPDIR:-/tmp}/sram-body.XXXXXX")
ROM_BYTES=""
OBJ_BYTES=""
cleanup() {
    rm -f "$BODY"
    [ -n "$ROM_BYTES" ] && rm -f "$ROM_BYTES"
    [ -n "$OBJ_BYTES" ] && rm -f "$OBJ_BYTES"
}
trap cleanup EXIT

awk -v f="$FUNC" '
    $0 ~ "^[[:space:]]*thumb_func_start[[:space:]]+" f "[[:space:]]*$" { on = 1 }
    on && /^[[:space:]]*thumb_func_start/ && $0 !~ f { exit }
    on { print }
' "$ASM_FILE" >"$BODY"
# Drop the blank separator lines before the next function.
while [ -s "$BODY" ] && [ -z "$(tail -1 "$BODY")" ]; do
    sed -i '$d' "$BODY"
done

[ -s "$BODY" ] || die "could not find thumb_func_start $FUNC in $ASM_FILE"
grep -q "SramWrite_MostRecentSaveFile: @ 0x08080068" "$BODY" \
    || die "unexpected start address (wanted $FUNC_ADDR)"
grep -q "^_080800F0: .4byte" "$BODY" \
    || die "literal pool does not end at $LAST_LITERAL (wanted size $FUNC_SIZE)"
tail -1 "$BODY" | grep -q "^$LAST_LITERAL:" \
    || die "trailing data after $LAST_LITERAL; refusing to guess the function extent"

# Write a standalone .s around the extracted body (the split file's macros and
# the unified syntax are the only context it needs).
write_target_s() {
    {
        printf '    .include "asm/macros.inc"\n\n'
        printf '    .syntax unified\n\n'
        cat "$1"
        printf '\n'
    } >"$2"
}

write_target_s "$BODY" "$TARGET_RAW_S"

# ---------------------------------------------------------------------------
# 2. Assemble the raw target and check it against the baseline ROM
#
# The ROM check must use the *raw* body: the shipped target keeps unresolved
# relocations (the `bl unk_dd4` and the symbolic literal), so its .text holds
# placeholders and cannot be byte-compared with the ROM.
# ---------------------------------------------------------------------------

msg "assembling raw target -> ${TARGET_RAW_O#$ROOT/}"
arm-none-eabi-as -mcpu=arm7tdmi -I"$ROOT" "$TARGET_RAW_S" -o "$TARGET_RAW_O"

text_size=$(arm-none-eabi-objdump -h "$TARGET_RAW_O" | awk '$2 == ".text" { print $3 }')
[ "$text_size" = "0000008c" ] \
    || die "target .text is 0x$text_size bytes, expected 0x8c"

if [ -f "$BASELINE_ROM" ]; then
    ROM_BYTES=$(mktemp "${TMPDIR:-/tmp}/sram-rom.XXXXXX")
    OBJ_BYTES=$(mktemp "${TMPDIR:-/tmp}/sram-obj.XXXXXX")
    # 0x08080068 - 0x08000000 = 0x80068
    dd if="$BASELINE_ROM" of="$ROM_BYTES" bs=1 skip=$((FUNC_ADDR - 0x08000000)) \
        count=$((FUNC_SIZE)) status=none
    arm-none-eabi-objcopy -O binary --only-section=.text "$TARGET_RAW_O" "$OBJ_BYTES"

    # The raw body still calls/loads two external symbols (unk_dd4,
    # sUnk_582280), so those 4-byte words carry relocations and hold
    # placeholders instead of the final ROM values.  Every byte outside a
    # relocation must match the baseline.
    relocs=$(arm-none-eabi-objdump -r "$TARGET_RAW_O" \
        | awk '$2 ~ /^R_ARM_/ { print $1 }')
    [ -n "$relocs" ] || die "raw target has no relocation records; extraction is broken"

    bad=0
    while read -r pos _; do
        [ -n "$pos" ] || continue
        off=$((pos - 1))
        covered=0
        for r in $relocs; do
            roff=$((16#$r))
            if [ "$off" -ge "$roff" ] && [ "$off" -lt $((roff + 4)) ]; then
                covered=1
                break
            fi
        done
        if [ "$covered" -eq 0 ]; then
            bad=1
            printf 'import-sram: byte 0x%x differs outside a relocation\n' "$off" >&2
        fi
    done <<< "$(cmp -l "$ROM_BYTES" "$OBJ_BYTES" || true)"
    [ "$bad" -eq 0 ] \
        || die "extracted target object differs from $BASELINE_ROM at $FUNC_ADDR"
    msg "raw target matches the baseline ROM at $FUNC_ADDR (relocated words excluded)"
else
    msg "baseline ROM not present; skipping the byte check"
fi

# 0x03000B8D is gMostRecentSaveFile in the US baseline.  A symbolic relocation
# is what the compiled candidate produces, and it keeps the target object
# reusable after a ROM shift.
sed -i -E 's/^(_080800EC: \.4byte )0x03000B8D$/\1gMostRecentSaveFile/' "$BODY"

write_target_s "$BODY" "$TARGET_S"

msg "assembling symbolic target -> ${TARGET_O#$ROOT/}"
arm-none-eabi-as -mcpu=arm7tdmi -I"$ROOT" "$TARGET_S" -o "$TARGET_O"

text_size=$(arm-none-eabi-objdump -h "$TARGET_O" | awk '$2 == ".text" { print $3 }')
[ "$text_size" = "0000008c" ] \
    || die "symbolic target .text is 0x$text_size bytes, expected 0x8c"

arm-none-eabi-objdump -r "$TARGET_O" | grep -q 'R_ARM_ABS32[[:space:]]*gMostRecentSaveFile' \
    || die "target .o has no R_ARM_ABS32 relocation for gMostRecentSaveFile"


# ---------------------------------------------------------------------------
# 3. Copy the 435-score seed and run the bounded search
# ---------------------------------------------------------------------------

cp "$SEED_SRC" "$SEED_COPY"
msg "seed -> ${SEED_COPY#$ROOT/}"

"$SCRIPT_DIR/run.sh" \
    --seed "$SEED_COPY" \
    --target "$TARGET_O" \
    --name "$FUNC" \
    "$@"
