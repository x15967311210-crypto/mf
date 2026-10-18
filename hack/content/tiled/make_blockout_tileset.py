#!/usr/bin/env python3
"""Generate the synthetic Sector Null blockout tileset.

The image is a 64x64 indexed PNG: a 4x4 grid of 16x16 tiles.  Every pixel is
flat geometry drawn from a 16-colour palette; no game art, ROM data, scanned
material or third-party asset is encoded.  Palette index 0 is transparent.

Usage::

    python3 hack/content/tiled/make_blockout_tileset.py --check
    python3 hack/content/tiled/make_blockout_tileset.py --write
"""

from __future__ import annotations

import argparse
import hashlib
import sys
import tempfile
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(REPO_ROOT / "tools" / "content"))

import pngio  # noqa: E402


TILE = 16
COLUMNS = 4
ROWS = 4
WIDTH = TILE * COLUMNS
HEIGHT = TILE * ROWS
TARGET = Path(__file__).resolve().with_name("blockout_tileset.png")

PALETTE = (
    (0, 0, 0),        # 0  transparent / void
    (8, 12, 16),      # 1  near-black shadow
    (22, 30, 38),     # 2  dark slate
    (44, 56, 66),     # 3  slate
    (70, 86, 96),     # 4  panel
    (36, 88, 92),     # 5  dim teal
    (52, 148, 144),   # 6  teal
    (116, 232, 220),  # 7  signal cyan
    (202, 142, 58),   # 8  amber
    (118, 78, 36),    # 9  dim amber
    (226, 238, 236),  # 10 bright highlight
    (78, 30, 38),     # 11 dark red
    (178, 62, 68),    # 12 red
    (66, 78, 46),     # 13 olive
    (76, 58, 104),    # 14 violet
    (146, 158, 166),  # 15 pale grey
)

TRANSPARENCY = (0,)


def tile_pixels(index: int) -> list[list[int]]:
    """Return one 16x16 tile as palette indices."""

    out = [[0 for _ in range(TILE)] for _ in range(TILE)]

    for y in range(TILE):
        for x in range(TILE):
            value = 0
            if index == 0:  # empty / transparent
                value = 0
            elif index == 1:  # solid wall
                if x == 0 or y == 0:
                    value = 3
                elif x == TILE - 1 or y == TILE - 1:
                    value = 1
                else:
                    value = 2
            elif index == 2:  # floor surface
                if y < 3:
                    value = 7
                elif y == TILE - 1:
                    value = 1
                elif x % 8 == 0:
                    value = 2
                else:
                    value = 3
            elif index == 3:  # platform / ledge
                if y < 3:
                    value = 7
                elif x == 0 or x == TILE - 1 or y > 13:
                    value = 2
                else:
                    value = 4
            elif index == 4:  # dark panel
                if x % 8 == 0 or y % 8 == 0:
                    value = 2
                elif (x + y) % 16 == 0:
                    value = 3
                else:
                    value = 1
            elif index == 5:  # working light
                if 5 <= y <= 10:
                    value = 10 if 7 <= y <= 8 else 7
                elif x % 5 == 0:
                    value = 6
                else:
                    value = 2
            elif index == 6:  # door frame
                if x == 0 or y == 0 or x == TILE - 1 or y == TILE - 1:
                    value = 2
                elif x in (3, 12):
                    value = 9
                elif 7 <= y <= 8:
                    value = 6
                elif x in (7, 8):
                    value = 8
                else:
                    value = 5
            elif index == 7:  # console / terminal
                if 3 <= x <= 12 and 3 <= y <= 9:
                    value = 6
                elif 4 <= x <= 11 and 4 <= y <= 5:
                    value = 7
                elif x in (4, 11) and y in (11, 13):
                    value = 8
                else:
                    value = 2
            elif index == 8:  # pipe run
                if 5 <= y <= 10:
                    value = 5 if 6 <= y <= 7 else 4
                elif x % 8 < 2 and 4 <= y <= 11:
                    value = 3
                else:
                    value = 1
            elif index == 9:  # hazard stripe
                value = 8 if ((x + y) // 4) % 2 == 0 else 1
                if x == 0 or y == 0 or x == TILE - 1 or y == TILE - 1:
                    value = 2
            elif index == 10:  # pulse-only geometry
                edge = x < 2 or x > 13 or y < 2 or y > 13
                value = 6 if edge and (x % 4 == 0 or y % 4 == 0) else 0
                if 6 <= x <= 9 and 6 <= y <= 9:
                    value = 7
                elif x == 8 or y == 8:
                    value = 6
            elif index == 11:  # grate
                value = 4 if x % 4 == 0 or y % 4 == 0 else 1
                if x in (2, 6, 10, 14) and y in (2, 6, 10, 14):
                    value = 0
            elif index == 12:  # cable
                curve = abs((y - 8) - int(4 * ((x % 16) - 8) / 8))
                value = 6 if curve <= 1 else 0
                if curve == 2:
                    value = 4
            elif index == 13:  # rubble
                if y > 10:
                    if x < 5 and y > 12:
                        value = 3
                    elif 5 <= x < 10 and y > 10:
                        value = 4
                    elif x >= 10 and y > 12:
                        value = 2
                    else:
                        value = 0
            elif index == 14:  # route marker
                if (5 <= x <= 10 and 7 <= y <= 8) or (
                    7 <= x <= 8 and 5 <= y <= 10
                ):
                    value = 14
                if x in (7, 8) and y in (7, 8):
                    value = 7
            elif index == 15:  # mist wisp
                if 3 <= y <= 6 and x % 8 < 4:
                    value = 2
                elif 10 <= y <= 13 and x % 8 >= 4:
                    value = 2
                elif (x + y) % 11 == 0:
                    value = 1
            else:  # pragma: no cover - generator invariant
                raise AssertionError(f"unexpected tile index {index}")

            out[y][x] = value

    return out


def build_pixels() -> list[list[int]]:
    pixels = [[0 for _ in range(WIDTH)] for _ in range(HEIGHT)]
    for tile_index in range(COLUMNS * ROWS):
        tile = tile_pixels(tile_index)
        tile_x = (tile_index % COLUMNS) * TILE
        tile_y = (tile_index // COLUMNS) * TILE
        for y in range(TILE):
            for x in range(TILE):
                pixels[tile_y + y][tile_x + x] = tile[y][x]
    return pixels


def expected_bytes() -> bytes:
    with tempfile.TemporaryDirectory(prefix="mf-blockout-png-") as tmp:
        path = Path(tmp) / "blockout_tileset.png"
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
    group.add_argument("--check", action="store_true", help="verify the checked-in PNG")
    group.add_argument("--write", action="store_true", help="regenerate the PNG")
    args = parser.parse_args(argv)

    payload = expected_bytes()

    if args.write:
        TARGET.write_bytes(payload)
        print(f"wrote {TARGET} ({len(payload)} bytes)")
        return 0

    if not TARGET.exists():
        print(f"TILESET: FAIL: missing {TARGET}", file=sys.stderr)
        return 1
    actual = TARGET.read_bytes()
    if actual != payload:
        print(
            "TILESET: FAIL: blockout_tileset.png is stale; "
            "run make_blockout_tileset.py --write",
            file=sys.stderr,
        )
        return 1
    digest = hashlib.sha256(actual).hexdigest()
    print(
        f"TILESET: PASS: blockout_tileset.png {WIDTH}x{HEIGHT} "
        f"{len(actual)} bytes sha256={digest}"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
