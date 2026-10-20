#!/usr/bin/env python3
"""Environment doctor for the mf-hack tree.

Checks the reproducibility prerequisites without building a ROM:

* Python >= 3.8;
* host commands git, make, cc (or gcc) and python3;
* ARM binutils ``as``, ``ld`` and ``objcopy`` resolved through ``TOOLCHAIN``;
* the pinned agbcc install in ``tools/agbcc`` (binary, libs and commit stamp);
* the baserom SHA1 against ``tools/baserom.sha1``.

``--source-only`` stops after the host/tool checks and runs the repository's
``--self-check`` suites, so public CI can use it without a baserom, agbcc or
an ARM toolchain.  No data/ extraction and no ROM build is attempted.

Examples::

    python3 tools/doctor.py
    python3 tools/doctor.py --source-only
    python3 tools/doctor.py --self-check
    TOOLCHAIN=$HOME/.local/bin/arm-none-eabi- python3 tools/doctor.py
    python3 tools/doctor.py --json-out work/doctor.json
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional, Sequence

MIN_PYTHON = (3, 8)
BASEROM_NAME = "mf_us_baserom.gba"
ARM_TOOLS = ("as", "ld", "objcopy")
SELF_CHECKS = (
    "tools/shift/audit_asm.py",
    "tools/shift/audit_blobs.py",
    "tools/shift/postlink_pointer_scan.py",
    "tools/content/tiled_to_room.py",
)
SELF_CHECK_TIMEOUT = 180

PASS = "PASS"
FAIL = "FAIL"
SKIP = "SKIP"


@dataclass
class Check:
    name: str
    status: str
    detail: str
    hints: List[str] = field(default_factory=list)

    def as_dict(self) -> dict:
        data = {"name": self.name, "status": self.status, "detail": self.detail}
        if self.hints:
            data["hints"] = list(self.hints)
        return data


def read_pin(path: Path) -> str:
    text = path.read_text(encoding="utf-8").strip()
    # Accept both a bare hash and sha1sum's "<hash>  <file>" form.
    token = text.split()[0] if text else ""
    return token.lower()


def is_hex_sha1(value: str) -> bool:
    if len(value) != 40:
        return False
    return all(c in "0123456789abcdef" for c in value)


def sha1_file(path: Path) -> str:
    digest = hashlib.sha1()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def toolchain_prefix() -> tuple[str, str]:
    """Return (prefix, source) for the configured TOOLCHAIN.

    Unset means the project default ``arm-none-eabi-``; an empty value means
    bare tool names (fully PATH-driven); a directory appends
    ``arm-none-eabi-``; anything else is used verbatim as a prefix.
    """
    raw = os.environ.get("TOOLCHAIN")
    if raw is None:
        return "arm-none-eabi-", "default"
    if raw == "":
        return "", "empty"
    if os.path.isdir(raw):
        return os.path.join(raw, "arm-none-eabi-"), "directory"
    return raw, "prefix"


def resolve_tool(prefix: str, tool: str) -> Optional[str]:
    name = prefix + tool
    if os.sep in name or (os.altsep and os.altsep in name):
        candidate = Path(name)
        if candidate.is_file() and os.access(candidate, os.X_OK):
            return str(candidate)
        return None
    return shutil.which(name)


def check_python() -> Check:
    version = platform.python_version()
    if sys.version_info >= MIN_PYTHON:
        return Check("python", PASS, f"{version} (>= 3.8)")
    return Check(
        "python",
        FAIL,
        f"{version} is too old (need >= 3.8)",
        ["install Python 3.8 or newer"],
    )


def check_host_command(label: str, names: Sequence[str]) -> Check:
    for name in names:
        path = shutil.which(name)
        if path:
            extra = ""
            if name != names[0]:
                extra = f" (accepted as {label})"
            return Check(f"host command {label}", PASS, f"{name} -> {path}{extra}")
    wanted = " or ".join(names)
    return Check(
        f"host command {label}",
        FAIL,
        f"none of {wanted} found on PATH",
        [f"install {wanted}"],
    )


def check_arm_binutils() -> Check:
    prefix, source = toolchain_prefix()
    resolved = {tool: resolve_tool(prefix, tool) for tool in ARM_TOOLS}
    missing = [tool for tool, path in resolved.items() if path is None]

    if not missing:
        detail = "prefix {!r}: {}".format(
            prefix, ", ".join(f"{tool}={resolved[tool]}" for tool in ARM_TOOLS)
        )
        return Check("ARM binutils (as, ld, objcopy)", PASS, detail)

    hint = "export TOOLCHAIN=$HOME/.local/bin/arm-none-eabi-"
    if source == "default":
        # Convenience for this project's per-user binutils install.  The note
        # matters: make itself still uses the default prefix unless exported.
        fallback = os.path.join(os.path.expanduser("~"), ".local", "bin", "arm-none-eabi-")
        fallback_resolved = {tool: resolve_tool(fallback, tool) for tool in ARM_TOOLS}
        if all(fallback_resolved.values()):
            detail = "found under {}: {}; export the hint so make uses it".format(
                os.path.dirname(fallback),
                ", ".join(f"{tool}={fallback_resolved[tool]}" for tool in ARM_TOOLS),
            )
            return Check(
                "ARM binutils (as, ld, objcopy)",
                PASS,
                detail,
                [hint],
            )

    return Check(
        "ARM binutils (as, ld, objcopy)",
        FAIL,
        f"missing: {', '.join(missing)} (TOOLCHAIN={prefix!r})",
        [hint, "or install binutils-arm-none-eabi"],
    )


def check_agbcc_binaries(root: Path) -> Check:
    install = root / "tools" / "agbcc"
    wanted = [
        install / "bin" / "agbcc",
        install / "lib" / "libgcc.a",
        install / "lib" / "libc.a",
    ]
    missing = [str(path.relative_to(root)) for path in wanted if not path.is_file()]
    if not missing:
        return Check(
            "agbcc binaries",
            PASS,
            "tools/agbcc/bin/agbcc, lib/libgcc.a, lib/libc.a",
        )
    return Check(
        "agbcc binaries",
        FAIL,
        "missing: " + ", ".join(missing),
        ["run make setup-agbcc"],
    )


def check_agbcc_pin(root: Path) -> Check:
    pin_path = root / "tools" / "agbcc-version"
    stamp_path = root / "tools" / "agbcc" / ".agbcc-commit"

    if not pin_path.is_file():
        return Check(
            "agbcc pin",
            FAIL,
            "missing tools/agbcc-version",
            ["restore tools/agbcc-version from Git"],
        )
    try:
        expected = read_pin(pin_path)
    except OSError as exc:
        return Check("agbcc pin", FAIL, f"cannot read tools/agbcc-version: {exc}")
    if not is_hex_sha1(expected):
        return Check(
            "agbcc pin",
            FAIL,
            "tools/agbcc-version is not a 40-character hex commit",
        )
    if not stamp_path.is_file():
        return Check(
            "agbcc pin",
            FAIL,
            "missing tools/agbcc/.agbcc-commit (no accepted stamp)",
            ["run make setup-agbcc"],
        )
    try:
        found = read_pin(stamp_path)
    except OSError as exc:
        return Check("agbcc pin", FAIL, f"cannot read stamp: {exc}")
    if found != expected:
        return Check(
            "agbcc pin",
            FAIL,
            f"stamp {found or '<empty>'} != pinned {expected}",
            ["run make setup-agbcc"],
        )
    return Check("agbcc pin", PASS, expected)


def check_baserom(root: Path) -> Check:
    pin_path = root / "tools" / "baserom.sha1"
    rom_path = root / BASEROM_NAME

    if not pin_path.is_file():
        return Check(
            "baserom SHA1",
            FAIL,
            "missing tools/baserom.sha1",
            ["restore tools/baserom.sha1 from Git"],
        )
    try:
        expected = read_pin(pin_path)
    except OSError as exc:
        return Check("baserom SHA1", FAIL, f"cannot read tools/baserom.sha1: {exc}")
    if not is_hex_sha1(expected):
        return Check(
            "baserom SHA1",
            FAIL,
            "tools/baserom.sha1 is not a 40-character hex SHA1",
        )
    if not rom_path.is_file():
        return Check(
            "baserom SHA1",
            FAIL,
            f"missing {BASEROM_NAME}",
            [
                f"place the US baserom at {BASEROM_NAME} (SHA1 {expected})",
                "this file is copyrighted and is never committed",
            ],
        )
    try:
        found = sha1_file(rom_path)
    except OSError as exc:
        return Check("baserom SHA1", FAIL, f"cannot read {BASEROM_NAME}: {exc}")
    if found != expected:
        return Check(
            "baserom SHA1",
            FAIL,
            f"{BASEROM_NAME} is {found}, expected {expected}",
            ["use the clean US baserom listed in tools/baserom.sha1"],
        )
    return Check("baserom SHA1", PASS, f"{BASEROM_NAME} {found}")


def run_self_check(root: Path, relative: str) -> Check:
    script = root / relative
    name = f"self-check: {relative}"
    if not script.is_file():
        return Check(name, FAIL, "script missing")
    command = [sys.executable, str(script), "--self-check"]
    try:
        proc = subprocess.run(
            command,
            cwd=str(root),
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="replace",
            timeout=SELF_CHECK_TIMEOUT,
        )
    except subprocess.TimeoutExpired:
        return Check(name, FAIL, f"timed out after {SELF_CHECK_TIMEOUT}s")
    except OSError as exc:
        return Check(name, FAIL, f"could not run: {exc}")

    output = proc.stdout or ""
    lines = [line.strip() for line in output.splitlines() if line.strip()]
    summary = lines[-1] if lines else ""
    if proc.returncode == 0:
        return Check(name, PASS, summary or "exit 0")

    tail = "\n".join(lines[-8:]) if lines else "no output"
    return Check(name, FAIL, f"exit {proc.returncode}\n{tail}")


def print_check(check: Check) -> None:
    print(f"[{check.status}] {check.name}: {check.detail}")
    for hint in check.hints:
        print(f"       hint: {hint}")


def run_doctor_self_check() -> int:
    """Synthetic checks for the doctor's parsing and comparison helpers."""
    results: List[tuple[str, bool, str]] = []

    def record(name: str, passed: bool, detail: str = "") -> None:
        results.append((name, passed, detail))

    pin = "da598c1d918402c42c0c0d7128ba14567f3175e9"
    other = "0" * 40
    abc_sha1 = "a9993e364706816aba3e25717850c26c9cd0d89d"

    with tempfile.TemporaryDirectory(prefix="mf-doctor-selfcheck-") as tmp:
        root = Path(tmp)
        tools_dir = root / "tools"
        tools_dir.mkdir()

        pin_file = tools_dir / "agbcc-version"
        pin_file.write_text(pin.upper() + "  agbcc\n", encoding="utf-8")
        record("read_pin lowercases and takes the first token", read_pin(pin_file) == pin)

        record("is_hex_sha1 accepts 40 lowercase hex", is_hex_sha1(pin))
        record("is_hex_sha1 rejects short input", not is_hex_sha1(pin[:-1]))
        record("is_hex_sha1 rejects uppercase", not is_hex_sha1(pin.upper()))
        record("is_hex_sha1 rejects non-hex", not is_hex_sha1("g" + pin[1:]))

        abc_file = root / "abc.bin"
        abc_file.write_bytes(b"abc")
        record("sha1_file matches the known SHA1 of b'abc'", sha1_file(abc_file) == abc_sha1)

        # Baserom + pin: matching file passes, mismatched pin fails.
        rom_path = root / BASEROM_NAME
        rom_path.write_bytes(b"abc")
        baserom_pin = tools_dir / "baserom.sha1"
        baserom_pin.write_text(abc_sha1 + "\n", encoding="utf-8")
        record("check_baserom accepts the matching hash", check_baserom(root).status == PASS)
        baserom_pin.write_text(pin + "\n", encoding="utf-8")
        record("check_baserom rejects the wrong hash", check_baserom(root).status == FAIL)

        # agbcc binaries and stamp.
        install = tools_dir / "agbcc"
        (install / "bin").mkdir(parents=True)
        (install / "lib").mkdir()
        for relative in ("bin/agbcc", "lib/libgcc.a", "lib/libc.a"):
            (install / relative).write_bytes(b"x")
        record("check_agbcc_binaries accepts a complete install", check_agbcc_binaries(root).status == PASS)
        (install / "lib" / "libc.a").unlink()
        record("check_agbcc_binaries rejects a missing lib", check_agbcc_binaries(root).status == FAIL)
        (install / "lib" / "libc.a").write_bytes(b"x")

        pin_file.write_text(pin + "\n", encoding="utf-8")
        record("check_agbcc_pin rejects a missing stamp", check_agbcc_pin(root).status == FAIL)
        (install / ".agbcc-commit").write_text(pin.upper() + "\n", encoding="utf-8")
        record("check_agbcc_pin accepts a case-insensitive stamp", check_agbcc_pin(root).status == PASS)
        (install / ".agbcc-commit").write_text(other + "\n", encoding="utf-8")
        record("check_agbcc_pin rejects a stale stamp", check_agbcc_pin(root).status == FAIL)

        # TOOLCHAIN parsing: unset, empty, directory and prefix.
        saved = os.environ.pop("TOOLCHAIN", None)
        try:
            record("toolchain default is arm-none-eabi-", toolchain_prefix()[0] == "arm-none-eabi-")
            os.environ["TOOLCHAIN"] = ""
            record("empty TOOLCHAIN uses bare PATH names", toolchain_prefix() == ("", "empty"))
            os.environ["TOOLCHAIN"] = tmp
            record(
                "directory TOOLCHAIN appends the target prefix",
                toolchain_prefix()[0] == os.path.join(tmp, "arm-none-eabi-"),
            )
            os.environ["TOOLCHAIN"] = "/opt/arm/bin/arm-none-eabi-"
            record(
                "prefix TOOLCHAIN is used verbatim",
                toolchain_prefix() == ("/opt/arm/bin/arm-none-eabi-", "prefix"),
            )
        finally:
            if saved is None:
                os.environ.pop("TOOLCHAIN", None)
            else:
                os.environ["TOOLCHAIN"] = saved

    failed = 0
    for name, passed, detail in results:
        status = PASS if passed else FAIL
        suffix = f": {detail}" if detail else ""
        print(f"[{status}] self-check: {name}{suffix}")
        if not passed:
            failed += 1
    total = len(results)
    print(f"DOCTOR-SELF-CHECK: {PASS if failed == 0 else FAIL} ({total - failed}/{total} passed)")
    return 0 if failed == 0 else 1


def parse_args(argv: Sequence[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Check the local build prerequisites (Python, host tools, ARM "
            "binutils, pinned agbcc, baserom SHA1)."
        ),
        epilog=(
            "Use --source-only in public CI: it runs the host checks and the "
            "tool self-checks, but skips ARM binutils, agbcc and the baserom."
        ),
    )
    parser.add_argument(
        "--source-only",
        action="store_true",
        help="skip ARM binutils, agbcc and baserom; run tool self-checks",
    )
    parser.add_argument(
        "--self-check",
        action="store_true",
        help="run synthetic checks of doctor's helper logic and exit",
    )
    parser.add_argument(
        "--json-out",
        metavar="PATH",
        help="also write a machine-readable JSON report to PATH",
    )
    return parser.parse_args(argv)


def main(argv: Optional[Sequence[str]] = None) -> int:
    args = parse_args(sys.argv[1:] if argv is None else argv)
    if args.self_check:
        return run_doctor_self_check()
    root = Path(__file__).resolve().parent.parent
    mode = "source-only" if args.source_only else "full"

    print(f"DOCTOR: {mode} check in {root}")
    checks: List[Check] = []

    checks.append(check_python())
    checks.append(check_host_command("git", ("git",)))
    checks.append(check_host_command("make", ("make",)))
    checks.append(check_host_command("cc", ("cc", "gcc")))
    checks.append(check_host_command("python3", ("python3",)))

    if args.source_only:
        checks.append(
            Check("ARM binutils (as, ld, objcopy)", SKIP, "--source-only")
        )
        checks.append(Check("agbcc binaries", SKIP, "--source-only"))
        checks.append(Check("agbcc pin", SKIP, "--source-only"))
        checks.append(Check("baserom SHA1", SKIP, "--source-only"))
        for relative in SELF_CHECKS:
            checks.append(run_self_check(root, relative))
    else:
        checks.append(check_arm_binutils())
        checks.append(check_agbcc_binaries(root))
        checks.append(check_agbcc_pin(root))
        checks.append(check_baserom(root))

    for check in checks:
        print_check(check)

    failed = [check for check in checks if check.status == FAIL]
    result = FAIL if failed else PASS

    if args.json_out:
        report = {
            "mode": mode,
            "root": str(root),
            "python": platform.python_version(),
            "checks": [check.as_dict() for check in checks],
            "result": result,
        }
        out = Path(args.json_out)
        try:
            if out.parent and not out.parent.exists():
                out.parent.mkdir(parents=True, exist_ok=True)
            out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        except OSError as exc:
            print(f"[FAIL] json report: cannot write {out}: {exc}")
            result = FAIL

    print(f"DOCTOR: {result}")
    return 0 if result == PASS else 1


if __name__ == "__main__":
    sys.exit(main())
