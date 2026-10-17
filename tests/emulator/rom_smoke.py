#!/usr/bin/env python3
"""Static GBA ROM/header smoke test.

This runs without an emulator and catches the common broken-build cases:
wrong pad size, broken entry branch, missing header checksum, missing title.
It does not execute the game; that is the dynamic scenario's job.
"""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path

ROM_START = 0x08000000
VALID_SIZES = {4 * 1024 * 1024, 8 * 1024 * 1024, 16 * 1024 * 1024, 32 * 1024 * 1024}


def header_checksum(rom: bytes) -> int:
    return (-(0x19 + sum(rom[0xA0:0xBD]))) & 0xFF


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rom", default="mf_us.gba")
    ap.add_argument("--expect-sha1", default=None)
    args = ap.parse_args()

    path = Path(args.rom)
    if not path.exists():
        print(f"FAIL: missing ROM {path}")
        return 1

    data = path.read_bytes()
    errors: list[str] = []
    warnings: list[str] = []

    if len(data) not in VALID_SIZES:
        errors.append(f"size {len(data)} is not 4/8/16/32 MiB")
    if len(data) < 0xC0:
        errors.append("file is smaller than the GBA header")
        print("FAIL: " + "; ".join(errors))
        return 1

    entry = int.from_bytes(data[0x00:0x04], "little")
    if (entry & 0x0F000000) != 0x0A000000:
        errors.append(f"entry 0x{entry:08X} is not an ARM branch")
    else:
        imm = entry & 0x00FFFFFF
        if imm & 0x00800000:
            imm -= 0x01000000
        target = ROM_START + 8 + (imm << 2)
        if not (ROM_START <= target < ROM_START + len(data)):
            errors.append(f"entry target 0x{target:08X} is outside the ROM")
        elif target != ROM_START + 0xC0:
            warnings.append(f"entry target is 0x{target:08X}, not 0x080000C0")

    logo = data[0x04:0xA0]
    if not any(logo):
        errors.append("Nintendo logo area is empty")
    if data[0xB2] != 0x96:
        errors.append(f"fixed byte 0xB2 is 0x{data[0xB2]:02X}, expected 0x96")

    title = data[0xA0:0xAC].rstrip(b"\x00")
    code = data[0xAC:0xB0].rstrip(b"\x00")
    if not title:
        warnings.append("empty title")
    if not code:
        warnings.append("empty game code")

    expected = header_checksum(data)
    if data[0xBD] != expected:
        errors.append(
            f"header checksum 0x{data[0xBD]:02X}, expected 0x{expected:02X}"
        )

    sha1 = hashlib.sha1(data).hexdigest()
    if args.expect_sha1 and sha1.lower() != args.expect_sha1.lower():
        errors.append(f"SHA1 {sha1} != {args.expect_sha1}")

    print(
        f"ROM {path}: {len(data)} bytes, title={title.decode('ascii', 'replace')!r}, "
        f"code={code.decode('ascii', 'replace')!r}, sha1={sha1}"
    )
    for warning in warnings:
        print(f"WARN: {warning}")
    for error in errors:
        print(f"FAIL: {error}")
    if errors:
        return 1
    print("PASS: static ROM smoke")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
