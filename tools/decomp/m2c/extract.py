#!/usr/bin/env python3
"""Extract one function from a GNU-as split disassembly file.

The split asm in ``asm/`` is assembled as part of a larger file: a function is
introduced by a ``thumb_func_start NAME`` / ``arm_func_start NAME`` macro and
has no ``.size`` directive, so there is no machine-readable end marker.  The
function body ends where the next function starts (the next
``*_func_start``, or a column-0 ``Name: @ 0x...`` label).

This tool turns that slice into a standalone, assemblable-and-decompilable
``.s`` file:

* ``thumb_func_start NAME`` becomes ``.global NAME`` (the label line that
  follows is kept, including its ``@ 0x...`` comment);
* the file gets ``.syntax unified`` / ``.text`` / ``.thumb`` (or ``.arm``);
* optional ``--symbol LITERAL=NAME`` rewrites literal-pool entries, so absolute
  addresses in the disassembly become names the m2c context can type
  (``.4byte 0x0203F000`` -> ``.4byte gSramRecentSave``).  Only the operand of a
  ``.word``/``.4byte`` data directive is rewritten; instructions are untouched.

The output is deterministic for a given input/mapping and is meant to be fed to
``m2c.py``.  Nothing here is a decompilation gate.

Usage:
    extract.py --asm FILE --function NAME [--out FILE]
               [--mode thumb|arm] [--symbols FILE] [--symbol SPEC ...] [--json]
    extract.py --self-check

``--self-check`` runs the boundary and literal-rewrite assertions against
``fixtures/mini.s`` and changes no file.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

FUNC_START_RE = re.compile(r"^\s*(thumb_func_start|arm_func_start)\s+([A-Za-z_.$][\w.$]*)\s*$")
# A function label sits at column 0 in this tree: `SramWrite_X: @ 0x08080068`.
TOP_LABEL_RE = re.compile(r"^([A-Za-z_.$][\w.$]*):\s*(@.*)?$")
LOCAL_LABEL_RE = re.compile(r"^\s*([A-Za-z_.$][\w.$]*):")
DATA_DIRECTIVE_RE = re.compile(r"^(\s*[A-Za-z_.$][\w.$]*:\s*\.(?:4byte|word)\s+)(\S+)(.*)$")


class ExtractError(Exception):
    pass


def load_symbols(paths, specs):
    """Return {literal_text: symbol_name} from files and SPEC arguments.

    A symbols file has one ``LITERAL NAME`` pair per line; ``#`` starts a
    comment.  SPEC is ``LITERAL=NAME``.  Later entries win.
    """
    mapping = {}
    for path in paths:
        with open(path, encoding="utf-8") as fh:
            for lineno, line in enumerate(fh, 1):
                line = line.split("#", 1)[0].strip()
                if not line:
                    continue
                parts = line.split()
                if len(parts) != 2:
                    raise ExtractError(f"{path}:{lineno}: expected `LITERAL NAME`, got: {line}")
                mapping[parts[0]] = parts[1]
    for spec in specs:
        if "=" not in spec:
            raise ExtractError(f"--symbol expects LITERAL=NAME, got: {spec}")
        literal, name = spec.split("=", 1)
        literal, name = literal.strip(), name.strip()
        if not literal or not name:
            raise ExtractError(f"--symbol expects LITERAL=NAME, got: {spec}")
        mapping[literal] = name
    return mapping


def find_function(lines, name):
    """Locate the body of `name`; return (start, end_exclusive, mode).

    `start` is the index of the ``*_func_start`` line when present, otherwise of
    the column-0 label.  `end_exclusive` points at the next function marker.
    """
    start = None
    mode = None
    for i, line in enumerate(lines):
        m = FUNC_START_RE.match(line)
        if m:
            if m.group(2) == name:
                start, mode = i, "arm" if m.group(1) == "arm_func_start" else "thumb"
                break
            continue
        # Fallback for split files that use a plain label (no macro).
        m = TOP_LABEL_RE.match(line)
        if m and m.group(1) == name and m.group(2):
            start, mode = i, "thumb"
            break
    if start is None:
        raise ExtractError(
            f"function {name!r} not found: expected `thumb_func_start {name}`, "
            f"`arm_func_start {name}`, or a column-0 `{name}: @ 0x...` label"
        )

    end = len(lines)
    for j in range(start + 1, len(lines)):
        line = lines[j]
        m = FUNC_START_RE.match(line)
        if m:
            end = j
            break
        m = TOP_LABEL_RE.match(line)
        if m and m.group(2):
            if m.group(1) == name:
                # The label that belongs to the function we are extracting.
                continue
            # Column-0 label annotated with a hex address == next function.
            end = j
            break
    if end <= start + 1:
        raise ExtractError(f"function {name!r} at line {start + 1} has no body")
    return start, end, mode


def build(lines, start, end, name, mode, symbols):
    """Render the standalone assembly text for lines[start:end]."""
    first = lines[start]
    body = [f"\t.global {name}"]
    if not FUNC_START_RE.match(first):
        body.append(first.rstrip("\n"))

    for line in lines[start + 1:end]:
        m = DATA_DIRECTIVE_RE.match(line)
        if m:
            prefix, operand, rest = m.groups()
            if operand in symbols:
                line = f"{prefix}{symbols[operand]}{rest}"
        body.append(line.rstrip("\n"))

    header = [
        f"@ Extracted by tools/decomp/m2c/extract.py from the split disassembly.",
        f"@ function: {name}",
        "\t.syntax unified",
        "\t.text",
        "\t.arm" if mode == "arm" else "\t.thumb",
        "",
    ]
    return "\n".join(header + body).rstrip("\n") + "\n"


def self_check():
    """Exercise boundaries, mode detection and literal rewrite on the fixture.

    Prints one ``OK`` line on success and raises ExtractError otherwise.  No
    files are written.
    """
    here = Path(__file__).resolve().parent
    fixture = here / "fixtures" / "mini.s"
    checks = 0

    def expect(cond, what):
        nonlocal checks
        if not cond:
            raise ExtractError(f"self-check failed: {what}")
        checks += 1

    if not fixture.is_file():
        raise ExtractError(f"self-check failed: missing fixture {fixture}")
    lines = fixture.read_text(encoding="utf-8").splitlines(keepends=True)

    # Thumb function: body starts at the macro, ends before the next function.
    start, end, mode = find_function(lines, "Mini_Add")
    expect(mode == "thumb", "Mini_Add is detected as thumb")
    expect("thumb_func_start Mini_Add" in lines[start], "Mini_Add starts at its macro")
    body = "".join(lines[start:end])
    expect("Mini_Next" not in body, "Mini_Add body stops before Mini_Next")
    expect("_08000008" in body, "Mini_Add keeps its own literal pool")
    text = build(lines, start, end, "Mini_Add", mode, {"0x03001234": "gMiniFlag"})
    expect(".thumb" in text, "thumb header emitted")
    expect(".global Mini_Add" in text, "global emitted")
    expect("Mini_Add: @ 0x08000000" in text, "address comment on the label is kept")
    expect(".4byte gMiniFlag" in text, "literal pool operand rewritten")
    expect("0x03001234" not in text, "raw literal is gone")
    expect("adds r0, r0, r1" in text, "instructions are untouched")
    expect("\t.syntax unified" in text, "syntax directive emitted")

    # A second function must not inherit the first one's pool.
    start2, end2, mode2 = find_function(lines, "Mini_Next")
    expect(mode2 == "thumb", "Mini_Next is detected as thumb")
    text2 = build(lines, start2, end2, "Mini_Next", mode2, {})
    expect("_08000014: .4byte 0x0000FFFF" in text2, "Mini_Next keeps its own pool")
    expect("Mini_Add" not in text2, "Mini_Next body stops before Mini_Arm")
    expect("gMiniFlag" not in text2, "mapping does not leak between functions")

    # ARM detection.
    start3, end3, mode3 = find_function(lines, "Mini_Arm")
    expect(mode3 == "arm", "Mini_Arm is detected as arm")
    expect("\t.arm" in build(lines, start3, end3, "Mini_Arm", mode3, {}),
           "arm header emitted")

    # Errors must be ExtractError, not a traceback.
    try:
        find_function(lines, "NoSuchFunction")
    except ExtractError:
        checks += 1
    else:
        raise ExtractError("self-check failed: missing function did not raise")

    # Symbol plumbing.
    expect(load_symbols([], ["0x0203F000=gSramMostRecent"])
           == {"0x0203F000": "gSramMostRecent"}, "--symbol LITERAL=NAME parsed")
    try:
        load_symbols([], ["0x0203F000"])
    except ExtractError:
        checks += 1
    else:
        raise ExtractError("self-check failed: bad --symbol did not raise")
    expect(load_symbols([], ["0x1=gA", "0x1=gB"]) == {"0x1": "gB"},
           "later --symbol wins")

    print(f"OK: extract self-check ({checks} checks, {fixture.name})")


def main(argv=None):
    ap = argparse.ArgumentParser(add_help=True)
    ap.add_argument("--asm", help="split disassembly .s file")
    ap.add_argument("--function", help="function symbol to extract")
    ap.add_argument("--out", help="write the standalone .s here (default: stdout)")
    ap.add_argument("--mode", choices=("thumb", "arm"), help="instruction set override")
    ap.add_argument("--symbols", action="append", default=[], metavar="FILE",
                    help="LITERAL NAME mapping file (repeatable)")
    ap.add_argument("--symbol", action="append", default=[], metavar="LITERAL=NAME",
                    help="single literal-pool rewrite (repeatable)")
    ap.add_argument("--json", action="store_true", help="print an extraction summary")
    ap.add_argument("--self-check", action="store_true",
                    help="run the fixture self-check and exit")
    args = ap.parse_args(argv)

    if args.self_check:
        try:
            self_check()
        except ExtractError as exc:
            print(f"m2c-extract: ERROR: {exc}", file=sys.stderr)
            return 1
        return 0

    if not args.asm or not args.function:
        print("m2c-extract: ERROR: --asm and --function are required "
              "(or use --self-check)", file=sys.stderr)
        return 2

    try:
        with open(args.asm, encoding="utf-8") as fh:
            lines = fh.readlines()
        start, end, detected = find_function(lines, args.function)
        mode = args.mode or detected
        symbols = load_symbols(args.symbols, args.symbol)
        text = build(lines, start, end, args.function, mode, symbols)
    except ExtractError as exc:
        print(f"m2c-extract: ERROR: {exc}", file=sys.stderr)
        return 2
    except OSError as exc:
        print(f"m2c-extract: ERROR: {exc}", file=sys.stderr)
        return 2

    if args.out:
        with open(args.out, "w", encoding="utf-8") as fh:
            fh.write(text)
    else:
        sys.stdout.write(text)

    if args.json:
        summary = {
            "function": args.function,
            "asm": args.asm,
            "line_start": start + 1,
            "line_end": end,
            "mode": mode,
            "symbols": len(symbols),
            "bytes": len(text.encode("utf-8")),
        }
        print(json.dumps(summary, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
