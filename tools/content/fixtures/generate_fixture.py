#!/usr/bin/env python3
"""Generate the synthetic content-pipeline tileset fixture.

The image is 64x32 pixels: an 8x2 grid of 16x16 tiles, indexed, four colours,
and deliberately without timestamps or ancillary metadata.  It is synthetic
geometry only; no game art is encoded.

Usage::

    python3 tools/content/fixtures/generate_fixture.py --check
    python3 tools/content/fixtures/generate_fixture.py --write
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import pngio


WIDTH = 64
HEIGHT = 32
TILE = 16

PALETTE = (
    (0, 0, 0),        # 0: transparent
    (64, 180, 220),   # 1: cool panel
    (235, 140, 60),   # 2: warning lamp
    (230, 230, 230),  # 3: highlight
)
TRANSPARENCY = (0,)


def tile_pixels(index: int) -> list[list[int]]:
    result = [[0 for _ in range(TILE)] for _ in range(TILE)]
    for y in range(TILE):
        for x in range(TILE):
            if index == 0:
                value = 0
            elif index == 1:
                value = 2 if x in (0, TILE - 1) or y in (0, TILE - 1) else 1
            elif index == 2:
                value = 2 if ((x // 4) + (y // 4)) % 2 else 3
            elif index == 3:
                value = 1 if (x + y) % 8 < 4 else 0
            elif index == 4:
                value = 1 if x < TILE // 2 and y < TILE // 2 else (
                    2 if x >= TILE // 2 and y < TILE // 2 else (
                        3 if x < TILE // 2 else 0
                    )
                )
            elif index == 5:
                near_edge = x in (0, TILE - 1) or y in (0, TILE - 1)
                in_centre = 5 <= x <= 10 and 5 <= y <= 10
                value = 3 if near_edge else (2 if in_centre else 1)
            elif index == 6:
                value = 2 if (x // 2) % 2 else 3
            else:
                value = 1 if 6 <= x <= 9 and 6 <= y <= 9 else 0
            result[y][x] = value
    return result


def build_pixels() -> list[list[int]]:
    columns = WIDTH // TILE
    rows = HEIGHT // TILE
    pixels = [[0 for _ in range(WIDTH)] for _ in range(HEIGHT)]
    for tile_index in range(columns * rows):
        tile = tile_pixels(tile_index)
        tile_x = (tile_index % columns) * TILE
        tile_y = (tile_index // columns) * TILE
        for y in range(TILE):
            for x in range(TILE):
                pixels[tile_y + y][tile_x + x] = tile[y][x]
    return pixels


def expected_bytes() -> bytes:
    # Encode in memory through a temporary path-like object: pngio writes to
    # a Path, so render into a scratch file under the system temp directory.
    import tempfile

    with tempfile.TemporaryDirectory(prefix="mf-fixture-png-") as tmp:
        path = Path(tmp) / "fixture_tileset.png"
        pngio.write_indexed_png(
            path,
            WIDTH,
            HEIGHT,
            PALETTE,
            build_pixels(),
            transparency=TRANSPARENCY,
        )
        return path.read_bytes()


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--check", action="store_true", help="verify the checked-in fixture")
    group.add_argument("--write", action="store_true", help="regenerate the fixture")
    args = parser.parse_args(argv)

    target = Path(__file__).resolve().parent / "fixture_tileset.png"
    payload = expected_bytes()

    if args.write:
        target.write_bytes(payload)
        print(f"wrote {target} ({len(payload)} bytes)")
        return 0

    if not target.exists():
        print(f"FIXTURE: FAIL: missing {target}", file=sys.stderr)
        return 1
    actual = target.read_bytes()
    if actual != payload:
        print(
            "FIXTURE: FAIL: fixture_tileset.png is stale; "
            "run generate_fixture.py --write",
            file=sys.stderr,
        )
        return 1
    digest = hashlib.sha256(actual).hexdigest()
    print(f"FIXTURE: PASS: fixture_tileset.png {len(actual)} bytes sha256={digest}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
