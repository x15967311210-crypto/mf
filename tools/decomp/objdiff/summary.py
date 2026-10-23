#!/usr/bin/env python3
"""Summarise an ``objdiff-cli diff --format json`` document (TECH-008).

The one-shot JSON mode is the scriptable interface of objdiff, but the payload
is a single, very large line: ``{"left": {...}, "right": {...}}`` with every
symbol and every instruction.  This helper turns it into a short report:

* the per-symbol ``match_percent`` (objdiff's fuzzy instruction/argument score);
* target/base symbol sizes;
* one row per differing instruction, aligned exactly as objdiff aligned them.

``left`` is the ``-1`` target object and ``right`` is the ``-2`` base object, so
the report always prints target on the left and base on the right.

Exit status mirrors ``tools/decomp/compare_text.py``:

* ``0`` -- every compared function is at 100 %;
* ``1`` -- at least one function differs (or exists on only one side);
* ``2`` -- usage error, unreadable JSON or an unknown requested symbol.

The ``--self-check`` fixture is synthetic and needs neither objdiff nor ARM
tools, so it is safe to run in any worktree::

    python3 tools/decomp/objdiff/summary.py --self-check

This is a *diagnostic*: 100 % means objdiff found no operation/argument
difference, not that the bytes match.  ``compare_text.py`` and the whole-ROM
SHA remain the authoritative gates.
"""

from __future__ import annotations

import argparse
import json
import sys

EXIT_MATCH = 0
EXIT_DIFF = 1
EXIT_ERROR = 2

SCHEMA = "objdiff-summary/1"

# objdiff marks a paired row with one of these; anything else is printed
# verbatim so a future objdiff release still produces a useful report.
KIND_LABELS = {
    "DIFF_NONE": "same",
    "DIFF_REPLACE": "replace",
    "DIFF_DELETE": "delete",
    "DIFF_INSERT": "insert",
    "DIFF_ARG_MISMATCH": "arg",
    "DIFF_OP_MISMATCH": "op",
    "DIFF_TYPE_CHANGED": "type",
}


def _as_int(value):
    """objdiff serialises sizes and addresses as strings or ints."""
    if value is None:
        return None
    if isinstance(value, int):
        return value
    try:
        return int(str(value), 0)
    except ValueError:
        try:
            return int(str(value), 16)
        except ValueError:
            return None


def _fmt_size(value):
    size = _as_int(value)
    if size is None:
        return "?"
    return f"{size} B"


def _fmt_addr(value):
    address = _as_int(value)
    if address is None:
        return "      "
    return f"+0x{address:03x}"


def _functions(side):
    """Return the function-like symbols of one JSON side, in table order."""
    result = []
    for symbol in side.get("symbols", []):
        name = symbol.get("name", "")
        if not name or name.startswith(("[", "$", ".gcc")):
            continue
        if symbol.get("kind") == "SYMBOL_FUNCTION" or "instructions" in symbol:
            result.append(symbol)
    return result


def _match_percent(left, right):
    for symbol in (right, left):
        if symbol is not None:
            value = symbol.get("match_percent")
            if value is not None:
                return float(value)
    return None


def _differing_rows(left, right):
    """Pair the two instruction tables the way objdiff emitted them.

    One-shot JSON contains aligned rows: both sides carry ``diff_kind`` but a
    DIFF_INSERT/DIFF_DELETE row has an instruction on only one side.  The tables
    are normally the same length; tolerate a mismatch at the tail.
    """
    rows = []
    left_instructions = (left or {}).get("instructions", [])
    right_instructions = (right or {}).get("instructions", [])
    for index in range(max(len(left_instructions), len(right_instructions))):
        lrow = left_instructions[index] if index < len(left_instructions) else {}
        rrow = right_instructions[index] if index < len(right_instructions) else {}
        lins = lrow.get("instruction")
        rins = rrow.get("instruction")
        kind = lrow.get("diff_kind") or rrow.get("diff_kind") or "DIFF_NONE"
        if kind == "DIFF_NONE" and lins is None and rins is None:
            continue
        if kind == "DIFF_NONE" and (lins is None) == (rins is None):
            continue
        rows.append(
            {
                "kind": kind,
                "label": KIND_LABELS.get(kind, kind.lower().replace("diff_", "")),
                "left": lins,
                "right": rins,
                "left_address": _fmt_addr((lins or {}).get("address")),
                "right_address": _fmt_addr((rins or {}).get("address")),
                "left_text": (lins or {}).get("formatted", ""),
                "right_text": (rins or {}).get("formatted", ""),
            }
        )
    return rows


def summarise(document, symbol=None):
    """Return (exit_code, report_text)."""
    if not isinstance(document, dict) or "left" not in document or "right" not in document:
        return EXIT_ERROR, "objdiff summary: JSON has no left/right object tables\n"

    left_symbols = _functions(document["left"])
    right_symbols = _functions(document["right"])
    left_by_name = {s.get("name"): s for s in left_symbols}
    right_by_name = {s.get("name"): s for s in right_symbols}

    names = []
    if symbol:
        names = [symbol]
    else:
        for entry in left_symbols + right_symbols:
            name = entry.get("name")
            if name not in names:
                names.append(name)

    compared = 0
    differing = 0
    details = []
    for name in names:
        left = left_by_name.get(name)
        right = right_by_name.get(name)
        if left is None and right is None:
            continue
        compared += 1
        match = _match_percent(left, right)
        missing = left is None or right is None
        # objdiff annotates every symbol in the table but only scores the
        # selected one.  Do not print instruction rows for a function that is
        # absent from one side: they are all noise.
        rows = [] if missing else _differing_rows(left, right)
        differs = missing or match is None or match < 100.0 or bool(rows)
        if differs:
            differing += 1
        if not differs:
            continue

        source = left if left is not None else right
        address = source.get("address")
        lines = []
        head = f"  {name}"
        if match is None:
            head += "  match n/a"
        else:
            head += f"  match {match:.2f}%"
        head += f"  (target {_fmt_size((left or {}).get('size'))}, "
        head += f"base {_fmt_size((right or {}).get('size'))})"
        lines.append(head)
        if address is not None:
            lines.append(f"    address +0x{_as_int(address):03x}")
        if missing:
            existing = left if left is not None else right
            lines.append(
                "    missing from "
                + ("target" if left is None else "base")
                + f" ({len(existing.get('instructions', []))} instruction(s) on the other side)"
            )
            details.append("\n".join(lines))
            continue
        if rows:
            lines.append(f"    {len(rows)} differing instruction(s), target | base:")
            for row in rows:
                lines.append(
                    "      {la} {lt:<44} | {ra} {rt:<44} [{label}]".format(
                        la=row["left_address"],
                        lt=row["left_text"] or "(none)",
                        ra=row["right_address"],
                        rt=row["right_text"] or "(none)",
                        label=row["label"],
                    )
                )
        else:
            lines.append("    no instruction rows differ")
        details.append("\n".join(lines))

    lines = []
    lines.append(f"symbols: {compared} compared, {differing} differing")
    if differing:
        lines.extend(details)
    else:
        lines.append("all compared symbols match at 100% (objdiff fuzzy score)")
    return (EXIT_DIFF if differing else EXIT_MATCH), "\n".join(lines) + "\n"


def _fixture(match, left_rows, right_rows):
    """Build a one-symbol JSON document from explicit instruction rows."""
    def symbol(rows):
        return {
            "symbols": [
                {
                    "name": "fixture",
                    "kind": "SYMBOL_FUNCTION",
                    "size": "4",
                    "match_percent": match,
                    "instructions": rows,
                }
            ]
        }

    return {"left": symbol(left_rows), "right": symbol(right_rows)}


def _row(address, text, kind=None):
    row = {"instruction": {"address": str(address), "size": 2, "formatted": text}}
    if kind:
        row["diff_kind"] = kind
    return row


def self_check():
    checks = 0

    def check(condition, message):
        nonlocal checks
        checks += 1
        if not condition:
            raise AssertionError(message)

    same = _fixture(
        100.0,
        [_row(0, "mov r0, #1"), _row(2, "bx lr")],
        [_row(0, "mov r0, #1"), _row(2, "bx lr")],
    )
    code, report = summarise(same)
    check(code == EXIT_MATCH, "identical fixture must exit 0")
    check("100%" in report, "identical fixture must report 100%")
    check("differing" in report, "identical fixture must report the counts")

    different = _fixture(
        50.0,
        [_row(0, "mov r0, #1", "DIFF_ARG_MISMATCH"), _row(2, "bx lr")],
        [_row(0, "mov r0, #2", "DIFF_ARG_MISMATCH"), _row(2, "bx lr")],
    )
    code, report = summarise(different)
    check(code == EXIT_DIFF, "one-argument fixture must exit 1")
    check("50.00%" in report, "fixture match percent must be formatted")
    check("[arg]" in report, "DIFF_ARG_MISMATCH must be labelled arg")
    check("mov r0, #2" in report and "mov r0, #1" in report,
          "fixture rows must show both sides")

    inserted = _fixture(
        50.0,
        [{"diff_kind": "DIFF_INSERT"}, _row(2, "bx lr")],
        [_row(0, "mov r0, #3", "DIFF_INSERT"), _row(2, "bx lr")],
    )
    code, report = summarise(inserted)
    check(code == EXIT_DIFF, "insert fixture must exit 1")
    check("[insert]" in report, "DIFF_INSERT must be labelled insert")
    check("(none)" in report, "insert fixture must mark the missing side")

    missing = {"left": {"symbols": []}, "right": {"symbols": []}}
    code, report = summarise(missing)
    check(code == EXIT_MATCH, "empty fixture has no differences")

    code, report = summarise({"left": {}})
    check(code == EXIT_ERROR, "malformed JSON must exit 2")

    print(f"summary self-check: PASS ({checks} checks)")
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("json", nargs="?", help="path to objdiff JSON ('-' for stdin)")
    parser.add_argument("--target", default="target", help="target label (-1)")
    parser.add_argument("--base", default="base", help="base label (-2)")
    parser.add_argument("--symbol", help="require this symbol to be present")
    parser.add_argument("--self-check", action="store_true")
    args = parser.parse_args(argv)

    if args.self_check:
        return self_check()

    if not args.json:
        parser.error("a JSON path is required (or --self-check)")

    try:
        if args.json == "-":
            document = json.load(sys.stdin)
        else:
            with open(args.json, encoding="utf-8") as handle:
                document = json.load(handle)
    except (OSError, ValueError) as error:
        print(f"objdiff summary: cannot read JSON: {error}", file=sys.stderr)
        return EXIT_ERROR

    names = {s.get("name") for side in ("left", "right") for s in _functions(document.get(side, {}))}
    if args.symbol and args.symbol not in names:
        print(
            f"objdiff summary: symbol {args.symbol!r} is not present in the diff "
            "(check --symbol spelling; objdiff-cli dumps all symbols instead of "
            "failing for an unknown name)",
            file=sys.stderr,
        )
        return EXIT_ERROR

    print(f"target: {args.target}")
    print(f"base:   {args.base}")
    code, report = summarise(document, symbol=args.symbol)
    sys.stdout.write(report)
    return code


if __name__ == "__main__":
    sys.exit(main())
