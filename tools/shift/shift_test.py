#!/usr/bin/env python3
"""Build a deliberately shifted ROM and run the behavior smoke.

The current baseline is *not* shiftable yet: padding the link will break the
hardcoded pointers found by `audit_asm.py`.  This tool exists so the refactor
has a concrete, repeatable failing test instead of a theoretical promise.

It backs up the normal mf_us.gba/elf/map, builds with a padded linker, copies
the result to work/shift/, and restores the baseline in a finally block.
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / "work" / "shift"
BASELINE = WORK / "baseline"


def toolchain_paths(arg: str | None) -> tuple[str | None, str | None]:
    if not arg:
        return None, None
    p = Path(arg)
    if p.is_dir():
        prefix = str(p / "arm-none-eabi-")
        return prefix, str(p)
    if p.name.endswith("-"):
        return str(p), str(p.parent)
    return str(p) + "-", str(p.parent)


def generate_padded_linker(pad: int) -> Path:
    WORK.mkdir(parents=True, exist_ok=True)
    base = WORK / "linker.base.ld"
    cpp = shutil.which("cpp")
    if not cpp:
        raise SystemExit("cpp not found")
    subprocess.run(
        [cpp, "-nostdinc", "-Iinclude", "linker.ld", "-o", str(base)],
        cwd=ROOT,
        check=True,
    )
    text = base.read_text()
    marker = "asm/intr_main.o(.text);"
    if marker not in text:
        raise SystemExit(f"marker {marker!r} not found in linker.ld")
    # `.` inside an output section is relative to the section start, so add a
    # delta rather than assigning an absolute 0x08... address.
    text = text.replace(marker, f"{marker}\n        . += 0x{pad:X};", 1)
    padded = WORK / "linker.pad.ld"
    padded.write_text(text)
    return padded


def backup(paths: list[Path]) -> None:
    BASELINE.mkdir(parents=True, exist_ok=True)
    for path in paths:
        if path.exists():
            saved = BASELINE / path.name
            if saved.exists():
                saved.unlink()
            shutil.move(str(path), str(saved))


def restore(paths: list[Path]) -> None:
    for path in paths:
        saved = BASELINE / path.name
        if saved.exists():
            shutil.copy2(saved, path)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--build", action="store_true")
    ap.add_argument("--run", action="store_true")
    ap.add_argument("--pad-bytes", default="0x1000")
    ap.add_argument("--toolchain", default=None)
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1)
    args = ap.parse_args()

    if not args.build and not args.run:
        print("nothing to do: pass --build and/or --run")
        return 2

    artifact = WORK / "mf_us_shift.gba"
    if args.build:
        padded = generate_padded_linker(int(args.pad_bytes, 16))
        print(f"padded linker: {padded}")
        prefix, bin_dir = toolchain_paths(args.toolchain)
        env = os.environ.copy()
        if bin_dir:
            env["PATH"] = bin_dir + os.pathsep + env.get("PATH", "")
        if prefix:
            env["TOOLCHAIN"] = prefix
        files = [ROOT / "mf_us.gba", ROOT / "mf_us.elf", ROOT / "mf_us.map"]
        backup(files)
        try:
            cmd = [
                "make",
                f"-j{args.jobs}",
                f"LD_SCRIPT={padded.relative_to(ROOT)}",
            ]
            print("build:", " ".join(cmd))
            proc = subprocess.run(cmd, cwd=ROOT, env=env)
            if proc.returncode != 0:
                print("FAIL: shifted build failed")
                return proc.returncode
            built = ROOT / "mf_us.gba"
            if not built.exists():
                print("FAIL: shifted build produced no mf_us.gba")
                return 1
            shutil.copy2(built, artifact)
            shutil.copy2(ROOT / "mf_us.elf", WORK / "mf_us_shift.elf")
            shutil.copy2(ROOT / "mf_us.map", WORK / "mf_us_shift.map")
            print(f"artifact: {artifact}")
        finally:
            restore(files)

    if args.run:
        if not artifact.exists():
            print(f"FAIL: no artifact at {artifact}; run --build first")
            return 1
        cmd = [
            sys.executable,
            "tests/emulator/run.py",
            "--rom",
            str(artifact),
            "--scenario",
            "boot_smoke",
        ]
        print("run:", " ".join(cmd))
        return subprocess.call(cmd, cwd=ROOT)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
