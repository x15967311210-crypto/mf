#!/usr/bin/env python3
"""Rewrite a linker script to reference a private object directory.

The baseline linker script names input objects by their tree-relative paths
(e.g. ``src/room.o``).  GNU ld loads every object explicitly named in the
script, so the HACK=1 build needs the same script with those paths prefixed by
``work/hack/obj/``.  This keeps the baseline object tree out of the hack link
without changing the normal/shifted/reordered link scripts.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

OBJECT_RE = re.compile(r"(?<![A-Za-z0-9_./-])((?:src|asm|sound)/[^\s;()]+\.o)")


def rewrite(text: str, obj_dir: str) -> str:
    prefix = obj_dir.rstrip("/") + "/"
    out = []
    for line in text.splitlines(keepends=True):
        if "work/" not in line:
            line = OBJECT_RE.sub(lambda m: prefix + m.group(1), line)
        out.append(line)
    return "".join(out)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("script", type=Path)
    ap.add_argument("--obj-dir", default="work/hack/obj")
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    original = args.script.read_text()
    updated = rewrite(original, args.obj_dir)
    if args.check:
        if original != updated:
            print(f"PREFIX-LINKER: FAIL {args.script} is not prefixed")
            return 1
        print(f"PREFIX-LINKER: PASS {args.script}")
        return 0
    if original != updated:
        args.script.write_text(updated)
        print(f"PREFIX-LINKER: wrote {args.script}")
    else:
        print(f"PREFIX-LINKER: unchanged {args.script}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
