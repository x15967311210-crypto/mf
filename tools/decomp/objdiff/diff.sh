#!/usr/bin/env bash
# One-shot objdiff diagnostic for a single function (TECH-008).
#
#   tools/decomp/objdiff/diff.sh --target target.o --base base.o \
#       [--symbol NAME] [--json]
#
# Calls the pinned CLI as:
#   objdiff-cli diff -1 <target> -2 <base> -o - --format json [<symbol>]
#
# then prints a short report (match %, differing functions/instructions) from
# tools/decomp/objdiff/summary.py.  --json appends the raw one-shot JSON.
#
# This is a *diagnostic*, not a gate: a 100 % objdiff score is a fuzzy
# instruction/argument match, not a byte-exact match.  Byte acceptance stays
# with tools/decomp/compare_text.py and the whole-ROM SHA.
#
# Exit status:
#   0  every compared function is at 100 % (objdiff score)
#   1  a function differs, or exists on only one side
#   2  usage error, missing objdiff install, unreadable object, or bad JSON
#
# Use --self-check (after setup.sh) to exercise the whole pipeline on a
# two-instruction synthetic object pair; it needs no seed, agbcc or ROM.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
OBJDIFF="$ROOT/work/tools/objdiff/objdiff-cli"
SUMMARY="$HERE/summary.py"
PYTHON="${PYTHON:-python3}"

die() {
    printf 'objdiff diff: %s\n' "$*" >&2
    exit 2
}

TMP_FILES=()
cleanup() {
    if [ "${#TMP_FILES[@]}" -gt 0 ]; then
        rm -rf "${TMP_FILES[@]}"
    fi
}
trap cleanup EXIT

usage() {
    sed -n '2,25p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

find_as() {
    if command -v arm-none-eabi-as >/dev/null 2>&1; then
        command -v arm-none-eabi-as
    elif [ -x "$HOME/.local/bin/arm-none-eabi-as" ]; then
        printf '%s\n' "$HOME/.local/bin/arm-none-eabi-as"
    else
        return 1
    fi
}

require_objdiff() {
    [ -x "$OBJDIFF" ] || die "objdiff-cli not installed; run tools/decomp/objdiff/setup.sh"
    local version
    version="$("$OBJDIFF" --version 2>/dev/null | head -n 1 || true)"
    [ "$version" = "objdiff-cli 3.8.3" ] \
        || die "unexpected objdiff-cli version '$version' (expected 3.8.3; re-run setup.sh)"
}

# run_diff <target> <base> <symbol-or-empty> <raw-json-0|1>
run_diff() {
    local target="$1" base="$2" symbol="$3" raw="$4"
    local json_file err_file rc=0 version
    json_file="$(mktemp)"
    err_file="$(mktemp)"
    TMP_FILES+=("$json_file" "$err_file")

    local args=(diff -1 "$target" -2 "$base" -o - --format json)
    if [ -n "$symbol" ]; then
        args+=("$symbol")
    fi

    if ! "$OBJDIFF" "${args[@]}" >"$json_file" 2>"$err_file"; then
        cat "$err_file" >&2
        die "objdiff-cli failed for target '$target' / base '$base'"
    fi
    if [ ! -s "$json_file" ]; then
        cat "$err_file" >&2
        die "objdiff-cli produced no JSON"
    fi

    version="$("$OBJDIFF" --version | head -n 1 | awk '{print $2}')"
    printf 'objdiff-cli %s\n' "$version"
    local summary_args=(--target "$target" --base "$base")
    if [ -n "$symbol" ]; then
        summary_args+=(--symbol "$symbol")
    fi
    set +e
    "$PYTHON" "$SUMMARY" "${summary_args[@]}" "$json_file"
    rc=$?
    set -e

    if [ "$raw" = 1 ]; then
        printf '\n--- raw objdiff JSON ---\n'
        cat "$json_file"
        printf '\n'
    fi

    return "$rc"
}

self_check() {
    require_objdiff
    "$PYTHON" "$SUMMARY" --self-check || die "summary.py self-check failed"

    local as
    as="$(find_as)" || die "arm-none-eabi-as not found (needed for --self-check)"

    local tmp
    tmp="$(mktemp -d)"
    TMP_FILES+=("$tmp")

    cat >"$tmp/same.s" <<'EOF'
    .syntax unified
    .text
    .thumb
    .global fixture
    .type fixture, %function
fixture:
    movs r0, #1
    bx lr
    .size fixture, .-fixture
EOF
    cat >"$tmp/other.s" <<'EOF'
    .syntax unified
    .text
    .thumb
    .global fixture
    .type fixture, %function
fixture:
    movs r0, #2
    bx lr
    .size fixture, .-fixture
EOF

    "$as" -mcpu=arm7tdmi "$tmp/same.s" -o "$tmp/same.o" || die "fixture assembly failed"
    "$as" -mcpu=arm7tdmi "$tmp/other.s" -o "$tmp/other.o" || die "fixture assembly failed"

    local output rc=0
    output="$(run_diff "$tmp/same.o" "$tmp/same.o" fixture 0)" || rc=$?
    [ "$rc" -eq 0 ] || die "self-check: identical objects reported a difference (exit $rc)"
    case "$output" in
        *"all compared symbols match at 100%"*) : ;;
        *) printf '%s\n' "$output" >&2; die "self-check: identical objects did not report 100%" ;;
    esac

    rc=0
    output="$(run_diff "$tmp/other.o" "$tmp/same.o" fixture 0)" || rc=$?
    [ "$rc" -eq 1 ] || die "self-check: differing objects must exit 1 (got $rc)"
    case "$output" in
        *"[arg]"*) : ;;
        *) printf '%s\n' "$output" >&2; die "self-check: arg difference not reported" ;;
    esac

    printf 'diff.sh self-check: PASS\n'
}

TARGET=""
BASE=""
SYMBOL=""
RAW=0

while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help) usage; exit 0 ;;
        --self-check) self_check; exit 0 ;;
        --target) [ $# -ge 2 ] || die "--target needs a path"; TARGET="$2"; shift 2 ;;
        --base) [ $# -ge 2 ] || die "--base needs a path"; BASE="$2"; shift 2 ;;
        --symbol) [ $# -ge 2 ] || die "--symbol needs a name"; SYMBOL="$2"; shift 2 ;;
        --json) RAW=1; shift ;;
        *) die "unknown argument '$1' (try --help)" ;;
    esac
done

[ -n "$TARGET" ] || die "--target is required"
[ -n "$BASE" ] || die "--base is required"
[ -f "$TARGET" ] || die "target object not found: $TARGET"
[ -f "$BASE" ] || die "base object not found: $BASE"
require_objdiff

run_diff "$TARGET" "$BASE" "$SYMBOL" "$RAW"
