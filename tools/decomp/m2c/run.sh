#!/usr/bin/env bash
# run.sh -- extract ONE function from the split disassembly and decompile it
# with the pinned m2c (TECH-009).
#
# Pipeline:
#   asm/disasm_*.s --extract.py--> standalone .s (literals symbolicated)
#                  --m2c -t gba --no-cache [--context ...]--> C
#
# Nothing here is a build gate and nothing here is committed: the extracted asm
# and the decompiled C land in work/decompme/, which is git-ignored.  m2c itself
# is GPL-3.0-only and lives in work/tools/m2c -- never vendor it.
#
# The output is a *draft* for a human.  It is not expected to compile and it is
# not expected to match the ROM byte for byte; see docs/howto/m2c.md for the
# known output-quality limitations.
#
# Usage:
#   tools/decomp/m2c/run.sh --asm ASM --function NAME [options]
#
# Options:
#   --asm FILE        split disassembly .s file (required)
#   --function NAME   function symbol to extract (required)
#   --context FILE    C context file; preprocessed here with cpp -nostdinc
#   --symbols FILE    LITERAL NAME mapping file (repeatable)
#   --symbol SPEC     extra LITERAL=NAME rewrite (repeatable)
#   --target TRIPLE   m2c target, platform is enough (default: gba)
#   --gotos-only      pass --gotos-only to m2c (no structured control flow)
#   --valid-syntax    pass --valid-syntax to m2c (M2C_* macros, always parses)
#   --out FILE        where to write the C (default: work/decompme/NAME.m2c.c)
#   --extracted FILE  where to write the standalone asm
#                     (default: work/decompme/NAME.s)
#   --self-check      verify extract.py + m2c end to end on a fixture, then exit
#   -h, --help

set -euo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd -- "$SCRIPT_DIR/../../.." && pwd)

M2C_DIR="$ROOT/work/tools/m2c"
M2C_BIN="$ROOT/work/tools/m2c-venv/bin/m2c"
PYTHON=${PYTHON:-python3}
OUT_DIR="$ROOT/work/decompme"
EXTRACT="$SCRIPT_DIR/extract.py"

ASM=""
FUNCTION=""
CONTEXT=""
TARGET="gba"
OUT=""
EXTRACTED=""
GOTOS_ONLY=0
VALID_SYNTAX=0
SELF_CHECK=0
SYMBOL_FILES=()
SYMBOL_SPECS=()

msg()  { printf 'm2c-run: %s\n' "$*"; }
die()  { printf 'm2c-run: ERROR: %s\n' "$*" >&2; exit 1; }
usage() {
    cat <<'EOF'
Usage: tools/decomp/m2c/run.sh --asm ASM --function NAME [options]

Extracts one function from the split disassembly and decompiles it with the
pinned m2c.  Writes only under work/decompme/.  See docs/howto/m2c.md.

Options:
  --asm FILE        split disassembly .s file (required)
  --function NAME   function symbol to extract (required)
  --context FILE    C context file (preprocessed with cpp -nostdinc -Iinclude)
  --symbols FILE    LITERAL NAME mapping file (repeatable)
  --symbol SPEC     extra LITERAL=NAME rewrite (repeatable)
  --target TRIPLE   m2c target (default: gba)
  --gotos-only      emit gotos instead of structured control flow
  --valid-syntax    emit M2C_* macros so the output always parses
  --out FILE        C output path (default: work/decompme/NAME.m2c.c)
  --extracted FILE  standalone asm path (default: work/decompme/NAME.s)
  --self-check      run the fixture self-check and exit
  -h, --help
EOF
}

need_value() {
    [ $# -ge 2 ] && [ -n "$2" ] || die "option $1 needs a value"
}

while [ $# -gt 0 ]; do
    case "$1" in
        --asm)        need_value "$@"; ASM=$2; shift 2 ;;
        --function)   need_value "$@"; FUNCTION=$2; shift 2 ;;
        --context)    need_value "$@"; CONTEXT=$2; shift 2 ;;
        --symbols)    need_value "$@"; SYMBOL_FILES+=("$2"); shift 2 ;;
        --symbol)     need_value "$@"; SYMBOL_SPECS+=("$2"); shift 2 ;;
        --target)     need_value "$@"; TARGET=$2; shift 2 ;;
        --out)        need_value "$@"; OUT=$2; shift 2 ;;
        --extracted)  need_value "$@"; EXTRACTED=$2; shift 2 ;;
        --gotos-only) GOTOS_ONLY=1; shift ;;
        --valid-syntax) VALID_SYNTAX=1; shift ;;
        --self-check) SELF_CHECK=1; shift ;;
        -h|--help)    usage; exit 0 ;;
        *) usage >&2; die "unknown argument: $1" ;;
    esac
done

require_m2c() {
    [ -x "$M2C_BIN" ] || die "m2c is not installed at $M2C_BIN
    run: tools/decomp/m2c/setup.sh"
}

extract_one() {
    local asm=$1 fn=$2 out=$3
    local args=(--asm "$asm" --function "$fn" --out "$out" --json)
    local f
    for f in "${SYMBOL_FILES[@]}"; do args+=(--symbols "$f"); done
    local s
    for s in "${SYMBOL_SPECS[@]}"; do args+=(--symbol "$s"); done
    "$PYTHON" "$EXTRACT" "${args[@]}" || die "extraction failed for $fn"
    [ -s "$out" ] || die "extraction wrote nothing to $out"
}

# ---------------------------------------------------------------------------
# --self-check: extract.py's fixture checks plus one real m2c run
# ---------------------------------------------------------------------------

if [ "$SELF_CHECK" = 1 ]; then
    "$PYTHON" "$EXTRACT" --self-check || die "extract.py self-check failed"
    require_m2c
    command -v cpp >/dev/null 2>&1 || die "missing cpp (host gcc), needed for --context"

    tmp="$ROOT/work/tmp/m2c-self-check"
    rm -rf "$tmp"
    mkdir -p "$tmp"
    fixture="$SCRIPT_DIR/fixtures/mini.s"
    [ -f "$fixture" ] || die "missing fixture $fixture"

    # 1. extraction through the same helper run.sh uses for real functions.
    SYMBOL_FILES=(); SYMBOL_SPECS=("0x03001234=gMiniFlag")
    extract_one "$fixture" "Mini_Add" "$tmp/Mini_Add.s" >/dev/null
    grep -q '[[:space:]]\.4byte gMiniFlag$' "$tmp/Mini_Add.s" \
        || die "self-check: literal pool was not symbolicated"
    grep -q '^Mini_Add: @ 0x08000000$' "$tmp/Mini_Add.s" \
        || die "self-check: function label missing from the extraction"
    grep -q '^[[:space:]]\.thumb$' "$tmp/Mini_Add.s" \
        || die "self-check: thumb directive missing from the extraction"
    grep -q '0x03001234' "$tmp/Mini_Add.s" \
        && die "self-check: raw literal still present after symbolication"

    # 2. real decompile, twice, to prove the CLI works and the output is stable.
    "$M2C_BIN" -t "$TARGET" --no-cache -f Mini_Add "$tmp/Mini_Add.s" >"$tmp/1.c" 2>"$tmp/1.err" \
        || { cat "$tmp/1.err" >&2; die "self-check: m2c failed on the fixture"; }
    "$M2C_BIN" -t "$TARGET" --no-cache -f Mini_Add "$tmp/Mini_Add.s" >"$tmp/2.c" 2>/dev/null
    grep -q 'Mini_Add' "$tmp/1.c" || die "self-check: m2c output does not mention Mini_Add"
    cmp -s "$tmp/1.c" "$tmp/2.c" || die "self-check: m2c output is not deterministic"

    msg "OK: self-check (extract + m2c $TARGET, fixture $(basename "$fixture"))"
    exit 0
fi

[ -n "$ASM" ] || die "--asm is required (or use --self-check)"
[ -n "$FUNCTION" ] || die "--function is required (or use --self-check)"
[ -f "$ASM" ] || die "asm file not found: $ASM"
[ -f "$EXTRACT" ] || die "missing $EXTRACT"
require_m2c

OUT=${OUT:-$OUT_DIR/$FUNCTION.m2c.c}
EXTRACTED=${EXTRACTED:-$OUT_DIR/$FUNCTION.s}
case "$OUT" in
    -) : ;;
    *) mkdir -p "$(dirname -- "$OUT")" ;;
esac
mkdir -p "$(dirname -- "$EXTRACTED")"

extract_one "$ASM" "$FUNCTION" "$EXTRACTED"
msg "extracted $FUNCTION -> ${EXTRACTED#"$ROOT"/}"

m2c_args=(-t "$TARGET" --no-cache)
if [ -n "$CONTEXT" ]; then
    [ -f "$CONTEXT" ] || die "context file not found: $CONTEXT"
    command -v cpp >/dev/null 2>&1 || die "missing cpp (host gcc), needed for --context"
    stem=$(basename -- "$CONTEXT")
    stem=${stem%.c}
    ctx_pp="$OUT_DIR/$stem.ctx.c"
    mkdir -p "$(dirname -- "$ctx_pp")"
    # m2c requires an already-preprocessed context file.
    cpp -nostdinc -I"$ROOT/include" "$CONTEXT" -o "$ctx_pp" \
        || die "cpp failed on context $CONTEXT"
    m2c_args+=(--context "$ctx_pp")
    msg "context $CONTEXT -> ${ctx_pp#"$ROOT"/}"
fi
[ "$GOTOS_ONLY" = 1 ] && m2c_args+=(--gotos-only)
[ "$VALID_SYNTAX" = 1 ] && m2c_args+=(--valid-syntax)
m2c_args+=(-f "$FUNCTION" "$EXTRACTED")

msg "m2c $TARGET ${m2c_args[*]}"
if [ "$OUT" = "-" ]; then
    "$M2C_BIN" "${m2c_args[@]}"
else
    "$M2C_BIN" "${m2c_args[@]}" >"$OUT" || die "m2c failed; nothing written to $OUT"
    msg "wrote ${OUT#"$ROOT"/} ($(wc -l <"$OUT") lines)"
    msg "artifacts are git-ignored (work/); this is a draft, not a gate"
fi
