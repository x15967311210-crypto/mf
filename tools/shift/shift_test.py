#!/usr/bin/env python3
"""Build a deliberately shifted ROM and run the behavior smoke.

The current baseline is *not* shiftable yet: padding the link breaks the
hardcoded pointers found by `audit_asm.py`.  This tool exists so the refactor
has a concrete, repeatable failing test instead of a theoretical promise.

It backs up the normal mf_us.gba/elf/map, builds with a perturbed linker, copies
the result to work/shift/, and restores the baseline in a finally block.

Padding mode (default) inserts `. += --pad-bytes` after `intr_main` so code
moves.  `--reorder` swaps two existing `.rodata` input sections instead, so
data addresses move while code addresses stay fixed.

Statuses are explicit and never conflate a skip with a pass:

    SHIFT-BUILD: PASS|FAIL
    SHIFT-LAYOUT: PASS|FAIL     (AgbMain moved by at least --pad-bytes)
    SHIFT-STATIC: PASS|FAIL     (static ROM/header smoke on the shifted ROM)
    SHIFT-DYNAMIC: PASS|FAIL|SKIP (77 = no emulator/harness)

    SHIFT-REORDER-BUILD: PASS|FAIL
    SHIFT-REORDER-LAYOUT: PASS|FAIL  (AgbMain fixed, swapped data moved)
    SHIFT-REORDER-STATIC: PASS|FAIL
    SHIFT-REORDER-DYNAMIC: PASS|FAIL|SKIP (77 = no emulator/harness)

`--check-linker` audits `linker.ld` itself: only the hardware MEMORY origins
(header/entry at 0x08000000/0x080000C0, EWRAM/IWRAM/MMIO) may be fixed.
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / "work" / "shift"
BASELINE = WORK / "baseline"

# Fixed hardware contract (D-002): the ROM header/entry and RAM/MMIO origins.
EXPECTED_ORIGINS = {
    "ewram": 0x02000000,
    "iwram": 0x03000000,
    "rom": 0x08000000,
}
ORIGIN_RE = re.compile(
    r"\b(ewram|iwram|rom)\s*:\s*ORIGIN\s*=\s*(0x[0-9A-Fa-f]+)"
)
ROM_ADDR_RE = re.compile(r"\b0x(0[89][0-9A-Fa-f]{6})\b")
OBJECT_RE = re.compile(r"[\w./$@-]+\.o\b")
ROM_OUT_RE = re.compile(
    r"\brom\s*:\s*ALIGN\([^)]*\)\s*\{(?P<body>.*?)\}\s*>\s*rom\b",
    re.S,
)
INPUT_RE = re.compile(r"([^\s;{}]+\.o\([^)]*\))\s*;")
EXPECTED_ROM_INPUTS = [
    "asm/romheader.o(.text)",
    "asm/crt0.o(.text)",
    "asm/intr_main.o(.text)",
]

# Reorder pair: both are existing `.rodata` input sections with different
# sizes.  Swapping them moves data but leaves the `.text` output section (and
# therefore AgbMain) at its baseline address.
GENERIC_DATA_OBJECT = "src/data/generic_data.o"
AUDIO_OBJECT = "src/data/audio.o"
GENERIC_DATA_RODATA = f"{GENERIC_DATA_OBJECT}(.rodata);"
AUDIO_RODATA = f"{AUDIO_OBJECT}(.rodata);"
REORDER_PAIR = (GENERIC_DATA_RODATA, AUDIO_RODATA)
SYMBOL_LINE_RE = re.compile(r"^\s+0x([0-9a-fA-F]{8})\s+(\S+)\s*$")
OBJECT_SECTION_RE = re.compile(r"^\s+\S+\.o\(")


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


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return re.sub(r"//.*", "", text)


def check_linker(path: Path) -> list[str]:
    """Return every fixed ROM address or missing hardware origin in *path*."""
    errors: list[str] = []
    try:
        text = path.read_text()
    except OSError as exc:
        return [f"{path}: {exc}"]

    code = strip_comments(text)

    origins: dict[str, int] = {}
    for match in ORIGIN_RE.finditer(code):
        origins[match.group(1)] = int(match.group(2), 16)
    for name, expected in EXPECTED_ORIGINS.items():
        got = origins.get(name)
        if got != expected:
            errors.append(
                f"{path}: {name} ORIGIN is "
                f"{'missing' if got is None else f'0x{got:08X}'}, "
                f"expected 0x{expected:08X}"
            )

    # The MEMORY origin is the only legal fixed ROM address.  Remove it and
    # object filenames such as asm/disasm_0x0808F5C4.o, then anything left in
    # the 0x08/0x09 range is an absolute ROM address in the layout.
    without_origins = ORIGIN_RE.sub("", code)
    for line in without_origins.splitlines():
        cleaned = OBJECT_RE.sub("", line)
        for match in ROM_ADDR_RE.finditer(cleaned):
            errors.append(
                f"{path}: fixed ROM address 0x{match.group(1).upper()} "
                f"in {line.strip()!r}; use a symbol or a section-relative '.'"
            )

    rom_section = ROM_OUT_RE.search(code)
    if not rom_section:
        errors.append(f"{path}: no 'rom : ALIGN(...) {{ ... }} >rom' section")
    else:
        inputs = INPUT_RE.findall(rom_section.group("body"))
        if inputs[: len(EXPECTED_ROM_INPUTS)] != EXPECTED_ROM_INPUTS:
            errors.append(
                f"{path}: rom output section must start with "
                f"{', '.join(EXPECTED_ROM_INPUTS)}; got {inputs[:3]}"
            )
    return errors


def preprocess_linker() -> Path:
    """Run the same cpp pass the Makefile applies to linker.ld."""
    WORK.mkdir(parents=True, exist_ok=True)
    base = WORK / "linker.base.ld"
    cpp = shutil.which("cpp")
    if not cpp:
        raise RuntimeError("cpp not found")
    subprocess.run(
        [cpp, "-nostdinc", "-Iinclude", "linker.ld", "-o", str(base)],
        cwd=ROOT,
        check=True,
    )
    return base


def generate_padded_linker(pad: int) -> Path:
    text = preprocess_linker().read_text()
    marker = "asm/intr_main.o(.text);"
    if text.count(marker) != 1:
        raise RuntimeError(
            f"expected exactly one {marker!r} in linker.ld, "
            f"found {text.count(marker)}"
        )
    # `.` inside an output section is relative to the section start, so add a
    # delta rather than assigning an absolute 0x08... address.
    text = text.replace(marker, f"{marker}\n        . += 0x{pad:X};", 1)
    padded = WORK / "linker.pad.ld"
    padded.write_text(text)
    return padded


def generate_reordered_linker() -> Path:
    """Swap the two proven `.rodata` input sections in a preprocessed linker."""
    text = preprocess_linker().read_text()
    for marker in REORDER_PAIR:
        count = text.count(marker)
        if count != 1:
            raise RuntimeError(
                f"expected exactly one {marker!r} in linker.ld, found {count}; "
                "cannot reorder sections"
            )

    first, second = REORDER_PAIR
    placeholder = "@@SHIFT_REORDER_PLACEHOLDER@@"
    text = text.replace(first, placeholder, 1)
    text = text.replace(second, first, 1)
    text = text.replace(placeholder, second, 1)
    if text.index(second) > text.index(first):
        raise RuntimeError("rodata swap did not take effect")

    reordered = WORK / "linker.reorder.ld"
    reordered.write_text(text)
    return reordered


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
        elif path.exists():
            path.unlink()


def map_symbol_address(path: Path, symbol: str) -> int | None:
    """First absolute address of *symbol* in a GNU ld map, if present."""
    if not path.exists():
        return None
    pattern = re.compile(
        rf"^\s*0x([0-9a-fA-F]{{8}})\s+{re.escape(symbol)}\s*$"
    )
    for line in path.read_text(errors="replace").splitlines():
        match = pattern.match(line)
        if match:
            return int(match.group(1), 16)
    return None


def check_layout(pad: int) -> tuple[bool, str]:
    """Prove the padded link actually moved post-intr_main code."""
    baseline = map_symbol_address(BASELINE / "mf_us.map", "AgbMain")
    shifted = map_symbol_address(WORK / "mf_us_shift.map", "AgbMain")
    if baseline is None or shifted is None:
        return False, (
            "cannot compare AgbMain addresses "
            f"(baseline={baseline}, shifted={shifted}); run --build first"
        )
    delta = shifted - baseline
    if delta < pad:
        return False, (
            f"AgbMain moved 0x{delta:X} (0x{baseline:08X} -> "
            f"0x{shifted:08X}), expected at least 0x{pad:X}"
        )
    return True, (
        f"AgbMain 0x{baseline:08X} -> 0x{shifted:08X} (+0x{delta:X})"
    )


def map_section_symbols(path: Path, obj: str) -> list[tuple[str, int]]:
    """Symbols printed under `<obj>(.rodata)` in a GNU ld map."""
    if not path.exists():
        return []
    marker = f"{obj}(.rodata)"
    lines = path.read_text(errors="replace").splitlines()
    symbols: list[tuple[str, int]] = []
    for index, line in enumerate(lines):
        if line.strip() != marker:
            continue
        for following in lines[index + 1 :]:
            match = SYMBOL_LINE_RE.match(following)
            if match:
                symbols.append((match.group(2), int(match.group(1), 16)))
                continue
            if symbols or OBJECT_SECTION_RE.match(following):
                break
        break
    return symbols


def _moved_symbol(
    baseline: list[tuple[str, int]],
    reordered: list[tuple[str, int]],
) -> tuple[str, int, int, int] | None:
    """First common symbol in map order plus its address delta."""
    current = dict(reordered)
    for name, address in baseline:
        if name in current:
            return name, address, current[name], current[name] - address
    return None


def check_reorder_layout() -> tuple[bool, str]:
    """Prove a `.rodata` swap moves data but leaves code at its address."""
    baseline_map = BASELINE / "mf_us.map"
    reordered_map = WORK / "mf_us_reorder.map"
    baseline_agb = map_symbol_address(baseline_map, "AgbMain")
    reordered_agb = map_symbol_address(reordered_map, "AgbMain")
    if baseline_agb is None or reordered_agb is None:
        return False, (
            "cannot compare AgbMain addresses "
            f"(baseline={baseline_agb}, reordered={reordered_agb}); "
            "run --build first"
        )
    if baseline_agb != reordered_agb:
        return False, (
            f"AgbMain moved 0x{baseline_agb:08X} -> 0x{reordered_agb:08X}; "
            "a data-only reorder must not move code"
        )

    moves: list[tuple[str, str, int, int, int]] = []
    for obj in (GENERIC_DATA_OBJECT, AUDIO_OBJECT):
        moved = _moved_symbol(
            map_section_symbols(baseline_map, obj),
            map_section_symbols(reordered_map, obj),
        )
        if moved is None:
            return False, (
                f"no common .rodata symbol for {obj} in baseline/reordered "
                "maps; cannot prove data moved"
            )
        name, old, new, delta = moved
        if delta == 0:
            return False, (
                f"{name} ({obj}) did not move (0x{old:08X}); "
                "section swap had no effect"
            )
        moves.append((obj, name, old, new, delta))

    generic_delta = moves[0][4]
    audio_delta = moves[1][4]
    if generic_delta < 0 or audio_delta > 0:
        return False, (
            "swap direction is wrong: "
            f"{moves[0][1]} {generic_delta:+#x}, "
            f"{moves[1][1]} {audio_delta:+#x}"
        )

    parts = [f"AgbMain 0x{baseline_agb:08X} unchanged"]
    for obj, name, old, new, delta in moves:
        parts.append(
            f"{name} ({obj}) 0x{old:08X} -> 0x{new:08X} ({delta:+#x})"
        )
    return True, "; ".join(parts)


def build_shifted(
    linker: Path,
    label: str,
    artifact_stem: str,
    toolchain: str | None,
    jobs: int,
) -> int:
    """Link with *linker*, copy artifacts, and always restore the baseline."""
    prefix, bin_dir = toolchain_paths(toolchain)
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
            f"-j{jobs}",
            f"LD_SCRIPT={linker.relative_to(ROOT)}",
        ]
        print("build:", " ".join(cmd))
        proc = subprocess.run(
            cmd,
            cwd=ROOT,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            encoding="utf-8",
            errors="replace",
        )
        if proc.stdout:
            sys.stdout.write(proc.stdout)
            if not proc.stdout.endswith("\n"):
                print()
        if proc.returncode != 0:
            print(f"{label}: FAIL (make exit {proc.returncode})")
            return proc.returncode if proc.returncode > 0 else 1
        # A missing incbin input silently produces an incomplete ROM.  Never
        # let that count as a passing shift build, even if it still boots.
        if "Failed to open" in proc.stdout or "for reading" in proc.stdout:
            print(
                f"{label}: FAIL (missing incbin input; "
                "fix data/ and rebuild)"
            )
            return 1
        built = ROOT / "mf_us.gba"
        if not built.exists():
            print(f"{label}: FAIL (no mf_us.gba produced)")
            return 1
        artifact = WORK / f"{artifact_stem}.gba"
        shutil.copy2(built, artifact)
        shutil.copy2(ROOT / "mf_us.elf", WORK / f"{artifact_stem}.elf")
        shutil.copy2(ROOT / "mf_us.map", WORK / f"{artifact_stem}.map")
        print(f"artifact: {artifact}")
    finally:
        restore(files)
    return 0


def build(pad: int, toolchain: str | None, jobs: int) -> int:
    linker_errors = check_linker(ROOT / "linker.ld")
    if linker_errors:
        for error in linker_errors:
            print(f"FAIL: {error}")
        print("SHIFT-BUILD: FAIL (linker premise)")
        return 1

    try:
        padded = generate_padded_linker(pad)
    except (RuntimeError, OSError, subprocess.CalledProcessError) as exc:
        print(f"SHIFT-BUILD: FAIL ({exc})")
        return 1
    print(f"padded linker: {padded}")
    status = build_shifted(
        padded, "SHIFT-BUILD", "mf_us_shift", toolchain, jobs
    )
    if status != 0:
        return status

    ok, detail = check_layout(pad)
    if not ok:
        print(f"SHIFT-LAYOUT: FAIL ({detail})")
        return 1
    print(f"SHIFT-LAYOUT: PASS ({detail})")
    print("SHIFT-BUILD: PASS")
    return 0


def reorder_build(toolchain: str | None, jobs: int) -> int:
    linker_errors = check_linker(ROOT / "linker.ld")
    if linker_errors:
        for error in linker_errors:
            print(f"FAIL: {error}")
        print("SHIFT-REORDER-BUILD: FAIL (linker premise)")
        return 1

    try:
        reordered = generate_reordered_linker()
    except (RuntimeError, OSError, subprocess.CalledProcessError) as exc:
        print(f"SHIFT-REORDER-BUILD: FAIL ({exc})")
        return 1
    print(f"reordered linker: {reordered}")
    status = build_shifted(
        reordered, "SHIFT-REORDER-BUILD", "mf_us_reorder", toolchain, jobs
    )
    if status != 0:
        return status

    ok, detail = check_reorder_layout()
    if not ok:
        print(f"SHIFT-REORDER-LAYOUT: FAIL ({detail})")
        return 1
    print(f"SHIFT-REORDER-LAYOUT: PASS ({detail})")
    print("SHIFT-REORDER-BUILD: PASS")
    return 0


def run_behavior(
    artifact: Path, scenario: str, frames: int, label: str = "SHIFT"
) -> int:
    cmd = [
        sys.executable,
        "tests/emulator/run.py",
        "--rom",
        str(artifact),
        "--scenario",
        scenario,
        "--frames",
        str(frames),
    ]
    print("run:", " ".join(cmd))
    try:
        proc = subprocess.run(
            cmd,
            cwd=ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
    except OSError as exc:
        print(f"{label}-DYNAMIC: FAIL (cannot start runner: {exc})")
        return 1
    sys.stdout.write(proc.stdout)
    if proc.stdout and not proc.stdout.endswith("\n"):
        print()

    static_ok = "PASS: static ROM smoke" in proc.stdout
    dynamic_ok = f"PASS: {scenario}" in proc.stdout

    if proc.returncode == 77:
        # run.py only skips after static checks pass, but report both.
        print(f"{label}-STATIC: {'PASS' if static_ok else 'FAIL'}")
        print(
            f"{label}-DYNAMIC: SKIP (77) - no emulator/harness; "
            "this is not a pass"
        )
        return 77

    print(f"{label}-STATIC: {'PASS' if static_ok else 'FAIL'}")
    if proc.returncode != 0 or not dynamic_ok:
        print(
            f"{label}-DYNAMIC: FAIL (runner exit {proc.returncode}, "
            f"PASS marker {'present' if dynamic_ok else 'missing'})"
        )
        return 1
    print(f"{label}-DYNAMIC: PASS")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--build", action="store_true")
    ap.add_argument("--run", action="store_true")
    ap.add_argument(
        "--reorder",
        action="store_true",
        help="swap two .rodata input sections instead of padding .text",
    )
    ap.add_argument("--check-linker", action="store_true")
    ap.add_argument("--pad-bytes", default="0x1000")
    ap.add_argument("--frames", type=int, default=600)
    ap.add_argument("--scenario", default="boot_smoke")
    ap.add_argument("--toolchain", default=None)
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1)
    args = ap.parse_args()

    if args.check_linker:
        linker = ROOT / "linker.ld"
        errors = check_linker(linker)
        if errors:
            for error in errors:
                print(f"FAIL: {error}")
            return 1
        print(
            "PASS: linker.ld fixes only the hardware MEMORY origins "
            "(header/entry 0x08000000/0x080000C0; EWRAM/IWRAM/MMIO); "
            "no other absolute ROM address"
        )
        return 0

    if not args.build and not args.run:
        print("nothing to do: pass --build, --run, or --check-linker")
        return 2

    if args.reorder:
        artifact = WORK / "mf_us_reorder.gba"
        if args.build:
            status = reorder_build(args.toolchain, args.jobs)
            if status != 0:
                return status
        else:
            ok, detail = check_reorder_layout()
            print(
                f"SHIFT-REORDER-LAYOUT: "
                f"{'PASS' if ok else 'FAIL'} ({detail})"
            )
            if not ok:
                return 1

        if args.run:
            if not artifact.exists():
                print(f"FAIL: no artifact at {artifact}; run --build first")
                return 1
            return run_behavior(
                artifact,
                args.scenario,
                args.frames,
                label="SHIFT-REORDER",
            )
        return 0

    pad = int(args.pad_bytes, 0)
    artifact = WORK / "mf_us_shift.gba"

    if args.build:
        status = build(pad, args.toolchain, args.jobs)
        if status != 0:
            return status
    else:
        ok, detail = check_layout(pad)
        print(
            f"SHIFT-LAYOUT: {'PASS' if ok else 'FAIL'} ({detail})"
        )

    if args.run:
        if not artifact.exists():
            print(f"FAIL: no artifact at {artifact}; run --build first")
            return 1
        return run_behavior(artifact, args.scenario, args.frames)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
