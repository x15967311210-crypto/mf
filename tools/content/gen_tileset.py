#!/usr/bin/env python3
"""Generate the hack blockout tileset tables from the authored PNG.

``hack/content/tiled/blockout_tileset.png`` is a 64x64 indexed PNG with a
16-colour palette: a 4x4 grid of 16x16 blocks, palette index 0 transparent.
``hack/content/tiled/make_blockout_tileset.py`` is its authoring tool.  This
generator turns that image into ``hack/gen/tileset_tables.h``:

* ``HackTest1TilesetGfx`` -- the 16 blocks packed as 4bpp 8x8 tiles in the
  order ``RoomSetInitialTilemap`` writes them (TL, TR, BL, BR), 2048 bytes,
  inside a literal-only LZ77 stream (header ``0x10`` plus a 24-bit size);
* ``HackTest1TilesetPal`` -- 14 rows of 16 colours.  ``RoomLoadTileset``
  DMA-copies the table to global PALRAM row 2, so the authored palette lives
  in row 2 and lands in global row 4, which survives the engine's fade
  clears.  The tilemap therefore selects palette bank 4;
* ``HackTest1TilesetBgGfx`` -- a zero-size LZ77 stream (bytes ``10 00 00 00``);
* ``HackTest1TilesetTilemap`` -- header ``0x0002`` plus 16 blocks x 4 u16
  entries ``0x4000 | (0xC0 + block*4 + quadrant)``;
* ``HackTest1TilesetEntry`` -- the ``struct TilesetEntry`` referencing them.

Like the rest of the content pipeline, the tool is standard-library Python
only, deterministic and free of timestamps, absolute paths and ROM content.

Usage::

    python3 tools/content/gen_tileset.py --write
    python3 tools/content/gen_tileset.py --check
    python3 tools/content/gen_tileset.py --self-check
"""

from __future__ import annotations

import argparse
import re
import sys
import tempfile
from pathlib import Path
from typing import Callable, Sequence

# The PNG reader is a sibling module; importing it must not depend on the
# current working directory.
_CONTENT_DIR = str(Path(__file__).resolve().parent)
if _CONTENT_DIR not in sys.path:
    sys.path.insert(0, _CONTENT_DIR)

import pngio  # noqa: E402


REPO_ROOT = Path(__file__).resolve().parents[2]
SOURCE_PNG = REPO_ROOT / "hack/content/tiled/blockout_tileset.png"
DEFAULT_OUT = REPO_ROOT / "hack/gen/tileset_tables.h"
SOURCE_LABEL = "hack/content/tiled/blockout_tileset.png"

IMAGE_SIZE = 64
BLOCK_COLUMNS = 4
BLOCK_ROWS = 4
BLOCK_COUNT = BLOCK_COLUMNS * BLOCK_ROWS
BLOCK_SIZE = 16
TILE_SIZE = 8
TILES_PER_BLOCK = 4
TILE_BYTES = 32
GFX_BYTES = BLOCK_COUNT * TILES_PER_BLOCK * TILE_BYTES  # 2048

LZ77_LITERAL_HEADER = 0x10
LZ77_LITERAL_GROUP = 8
LZ77_EMPTY_STREAM = b"\x10\x00\x00\x00"
# Header (4 bytes) plus one flag byte per literal group.
GFX_STREAM_BYTES = 4 + (GFX_BYTES // LZ77_LITERAL_GROUP) * (
    LZ77_LITERAL_GROUP + 1
)
if GFX_STREAM_BYTES % 4:
    raise AssertionError("the literal LZ77 stream must be a whole u32 array")
GFX_STREAM_WORDS = GFX_STREAM_BYTES // 4  # 577

PALETTE_SIZE = 16
PALETTE_ROW_SIZE = 16
PALETTE_ROWS = 14
PALETTE_ENTRIES = PALETTE_ROW_SIZE * PALETTE_ROWS  # 224
PALETTE_ROW = 2
PALETTE_BANK = 4

TILEMAP_HEADER = 0x0002
TILE_BASE = 0xC0
TILEMAP_ENTRIES = 1 + BLOCK_COUNT * TILES_PER_BLOCK  # 65

HEADER_GUARD = "HACK_GEN_TILESET_TABLES_H"
GFX_NAME = "HackTest1TilesetGfx"
PAL_NAME = "HackTest1TilesetPal"
BG_NAME = "HackTest1TilesetBgGfx"
TILEMAP_NAME = "HackTest1TilesetTilemap"
ENTRY_NAME = "HackTest1TilesetEntry"

GFX_WORDS_PER_LINE = 4
PAL_WORDS_PER_LINE = 8
TILEMAP_WORDS_PER_LINE = 8


class TilesetError(Exception):
    """A user-facing tileset validation error."""


def display_path(path: Path) -> str:
    """Return a repo-relative path; never leak an absolute path into output."""

    try:
        return path.resolve().relative_to(REPO_ROOT).as_posix()
    except (OSError, ValueError):
        return path.name


# ---------------------------------------------------------------------------
# Image validation and packing


def load_image(path: Path) -> pngio.PngImage:
    try:
        image = pngio.read_png(path)
    except pngio.PngError as exc:
        raise TilesetError(f"cannot read {display_path(path)}: {exc}") from exc
    validate_image(image, label=display_path(path))
    return image


def validate_image(image: pngio.PngImage, *, label: str | None = None) -> None:
    """Validate the blockout tileset's shape, palette and 4bpp indices."""

    label = label or image.path
    if image.color_type != 3:
        raise TilesetError(
            f"{label}: expected an indexed PNG (colour type 3), got "
            f"{image.color_type_name}"
        )
    if (image.width, image.height) != (IMAGE_SIZE, IMAGE_SIZE):
        raise TilesetError(
            f"{label}: expected a {IMAGE_SIZE}x{IMAGE_SIZE} image, got "
            f"{image.width}x{image.height}"
        )
    if len(image.palette) != PALETTE_SIZE:
        raise TilesetError(
            f"{label}: expected a {PALETTE_SIZE}-entry palette, got "
            f"{len(image.palette)} entries"
        )
    # tRNS lists one alpha byte per palette index; index 0 must be transparent.
    if image.transparency and image.transparency[0] != 0:
        raise TilesetError(f"{label}: palette index 0 must be transparent")

    for y, row in enumerate(image.pixels):
        for x, value in enumerate(row):
            if not isinstance(value, int) or not 0 <= value < PALETTE_SIZE:
                raise TilesetError(
                    f"{label}: palette index {value!r} at ({x},{y}) is outside "
                    f"0..{PALETTE_SIZE - 1}; 4bpp tiles have 16 colours"
                )


def pack_tiles(image: pngio.PngImage) -> bytes:
    """Pack the image's 16 blocks into 2048 bytes of 4bpp tile data.

    Block order is the PNG's row-major order.  Within a block the quadrants are
    written TL, TR, BL, BR -- the order ``RoomSetInitialTilemap`` fills
    ``dst[0], dst[1], dst[32], dst[33]``.  Each 8x8 tile is 32 bytes, two
    pixels per byte, low nibble left.
    """

    out = bytearray()
    for block in range(BLOCK_COUNT):
        block_x = (block % BLOCK_COLUMNS) * BLOCK_SIZE
        block_y = (block // BLOCK_COLUMNS) * BLOCK_SIZE
        for quadrant_y in (0, TILE_SIZE):
            for quadrant_x in (0, TILE_SIZE):
                for y in range(TILE_SIZE):
                    row = image.pixels[block_y + quadrant_y + y]
                    base = block_x + quadrant_x
                    for x in range(0, TILE_SIZE, 2):
                        low = row[base + x] & 0x0F
                        high = row[base + x + 1] & 0x0F
                        out.append(low | (high << 4))
    if len(out) != GFX_BYTES:
        raise TilesetError(
            f"internal error: packed {len(out)} gfx bytes, expected {GFX_BYTES}"
        )
    return bytes(out)


def lz77_literal_stream(data: bytes) -> bytes:
    """Wrap ``data`` in a literal-only GBA LZ77 stream.

    Header ``0x10`` marks an uncompressed block; the next three bytes are the
    little-endian uncompressed size.  Each group is one zero flag byte followed
    by eight literal bytes.
    """

    if not 0 <= len(data) <= 0xFFFFFF:
        raise TilesetError(
            f"LZ77: {len(data)} bytes do not fit the 24-bit size field"
        )
    out = bytearray([LZ77_LITERAL_HEADER])
    out += len(data).to_bytes(3, "little")
    for offset in range(0, len(data), LZ77_LITERAL_GROUP):
        out.append(0x00)
        out += data[offset : offset + LZ77_LITERAL_GROUP]
    return bytes(out)


def decode_lz77_literal(stream: bytes) -> bytes:
    """Minimal literal-only LZ77 decoder used by the self-check.

    Rejects compressed back-references and any trailing bytes, so it verifies
    that the emitted stream is exactly a header plus literal groups.
    """

    if len(stream) < 4:
        raise TilesetError("LZ77: truncated stream header")
    if stream[0] != LZ77_LITERAL_HEADER:
        raise TilesetError(
            f"LZ77: expected literal header 0x{LZ77_LITERAL_HEADER:02X}, got "
            f"0x{stream[0]:02X}"
        )
    size = int.from_bytes(stream[1:4], "little")
    out = bytearray()
    pos = 4
    while len(out) < size:
        if pos >= len(stream):
            raise TilesetError("LZ77: truncated flag byte")
        flags = stream[pos]
        pos += 1
        for bit in range(7, -1, -1):
            if len(out) >= size:
                break
            if flags & (1 << bit):
                raise TilesetError(
                    "LZ77: compressed back-reference in a literal-only stream"
                )
            if pos >= len(stream):
                raise TilesetError("LZ77: truncated literal byte")
            out.append(stream[pos])
            pos += 1
    if pos != len(stream):
        raise TilesetError(f"LZ77: {len(stream) - pos} trailing byte(s)")
    return bytes(out)


def palette_words(image: pngio.PngImage) -> list[int]:
    """Build the 14x16 u16 palette with the authored colours in row 2."""

    words = [0] * PALETTE_ENTRIES
    base = PALETTE_ROW * PALETTE_ROW_SIZE
    for index, (red, green, blue) in enumerate(image.palette):
        if index == 0:
            # Index 0 is transparent; force it to RGB555 black regardless of
            # the colour the PNG tools left in the palette entry.
            words[base] = 0
            continue
        words[base + index] = (
            (red >> 3) | ((green >> 3) << 5) | ((blue >> 3) << 10)
        ) & 0x7FFF
    return words


def tilemap_words() -> list[int]:
    """Build the u16 tilemap: header plus one entry per block quadrant."""

    words = [TILEMAP_HEADER]
    for block in range(BLOCK_COUNT):
        for quadrant in range(TILES_PER_BLOCK):
            tile = TILE_BASE + block * TILES_PER_BLOCK + quadrant
            if tile > 0x3FF:
                raise TilesetError(
                    f"tile index 0x{tile:X} does not fit the 10-bit tile field"
                )
            words.append((PALETTE_BANK << 12) | tile)
    if len(words) != TILEMAP_ENTRIES:
        raise TilesetError(
            f"internal error: tilemap has {len(words)} entries, expected "
            f"{TILEMAP_ENTRIES}"
        )
    return words


# ---------------------------------------------------------------------------
# Header rendering


def _bytes_to_u32_words(data: bytes) -> list[int]:
    if len(data) % 4:
        raise TilesetError(
            f"internal error: {len(data)} bytes are not a whole number of u32"
        )
    return [int.from_bytes(data[i : i + 4], "little") for i in range(0, len(data), 4)]


def _emit_hex_array(
    lines: list[str],
    ctype: str,
    name: str,
    values: Sequence[int],
    digits: int,
    per_line: int,
) -> None:
    lines.append(f"static const {ctype} {name}[{len(values)}] = {{")
    for offset in range(0, len(values), per_line):
        chunk = values[offset : offset + per_line]
        body = ", ".join(f"0x{value:0{digits}X}" for value in chunk)
        lines.append(f"    {body},")
    lines.append("};")
    lines.append("")


def render_header(image: pngio.PngImage) -> str:
    """Render the complete generated header for one validated image."""

    gfx = lz77_literal_stream(pack_tiles(image))
    gfx_words = _bytes_to_u32_words(gfx)
    pal_words = palette_words(image)
    tilemap = tilemap_words()

    lines: list[str] = []
    lines.append("/*")
    lines.append(" * hack/gen/tileset_tables.h -- generated blockout tileset tables.")
    lines.append(" *")
    lines.append(" * Generated by tools/content/gen_tileset.py; do not edit.")
    lines.append(" *")
    lines.append(f" * Source: {SOURCE_LABEL}")
    lines.append(
        f" *   {IMAGE_SIZE}x{IMAGE_SIZE} indexed PNG, {BLOCK_COLUMNS}x"
        f"{BLOCK_ROWS} blocks of {BLOCK_SIZE}x{BLOCK_SIZE}, "
        f"{PALETTE_SIZE} colours, index 0 transparent."
    )
    lines.append(
        f" *   Gfx: {len(gfx_words)} u32 words = {len(gfx)} bytes holding "
        f"{GFX_BYTES} uncompressed bytes"
    )
    lines.append(
        " *   (literal-only LZ77: header 0x10, 24-bit size, 0x00 flag + "
        "8 literals)."
    )
    lines.append(
        f" *   Palette row {PALETTE_ROW} holds the authored colours; "
        "RoomLoadTileset copies it"
    )
    lines.append(
        f" *   to global PALRAM row {PALETTE_ROW + 2}, so the tilemap uses "
        f"palette bank {PALETTE_BANK}."
    )
    lines.append(
        f" *   Tilemap: header 0x{TILEMAP_HEADER:04X}, then "
        f"{BLOCK_COUNT} blocks x {TILES_PER_BLOCK} entries, TL/TR/BL/BR."
    )
    lines.append(" */")
    lines.append(f"#ifndef {HEADER_GUARD}")
    lines.append(f"#define {HEADER_GUARD}")
    lines.append("")
    lines.append('#include "types.h"')
    lines.append('#include "structs/room.h"')
    lines.append("")

    lines.append(
        f"/* Blockout tile graphics, {GFX_BYTES} bytes packed as 4bpp 8x8 "
        "tiles. */"
    )
    _emit_hex_array(
        lines, "u32", GFX_NAME, gfx_words, 8, GFX_WORDS_PER_LINE
    )
    lines.append(
        f"/* {PALETTE_ROWS} palette rows of {PALETTE_ROW_SIZE} RGB555 colours; "
        f"row {PALETTE_ROW} is the authored tileset palette. */"
    )
    _emit_hex_array(
        lines, "u16", PAL_NAME, pal_words, 4, PAL_WORDS_PER_LINE
    )
    lines.append(
        "/* Zero-size LZ77 stream (bytes 10 00 00 00): no BG0 background "
        "graphics. */"
    )
    _emit_hex_array(
        lines, "u32", BG_NAME, _bytes_to_u32_words(LZ77_EMPTY_STREAM), 8, 1
    )
    lines.append(
        f"/* Tilemap header 0x{TILEMAP_HEADER:04X} + {BLOCK_COUNT} blocks; "
        f"palette bank {PALETTE_BANK}, tile base 0x{TILE_BASE:02X}. */"
    )
    _emit_hex_array(
        lines, "u16", TILEMAP_NAME, tilemap, 4, TILEMAP_WORDS_PER_LINE
    )

    lines.append(f"static const struct TilesetEntry {ENTRY_NAME} = {{")
    lines.append(f"    .pTileGraphics = {GFX_NAME},")
    lines.append(f"    .pPalette = {PAL_NAME},")
    lines.append(f"    .pBackgroundGraphics = {BG_NAME},")
    lines.append(f"    .pTilemap = (const u8*){TILEMAP_NAME},")
    lines.append("    .animatedTileset = 0,")
    lines.append("    .animatedPalette = 0,")
    lines.append("};")
    lines.append("")
    lines.append(f"#endif /* {HEADER_GUARD} */")

    return "\n".join(lines) + "\n"


def build_header(png_path: Path | None = None) -> str:
    return render_header(load_image(png_path or SOURCE_PNG))


# ---------------------------------------------------------------------------
# Write / check


def write_header(path: Path, content: str) -> bool:
    """Write the header; return True when the file changed."""

    payload = content.encode("utf-8")
    try:
        if path.exists() and path.read_bytes() == payload:
            return False
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(payload)
    except OSError as exc:
        raise TilesetError(f"cannot write {display_path(path)}: {exc}") from exc
    return True


def check_header(path: Path, content: str) -> None:
    """Fail when the generated header is missing or stale."""

    if not path.exists():
        raise TilesetError(
            f"{display_path(path)} is missing; run "
            "tools/content/gen_tileset.py --write"
        )
    try:
        actual = path.read_bytes()
    except OSError as exc:
        raise TilesetError(f"cannot read {display_path(path)}: {exc}") from exc
    if actual != content.encode("utf-8"):
        raise TilesetError(
            f"{display_path(path)} is stale; run "
            "tools/content/gen_tileset.py --write"
        )


# ---------------------------------------------------------------------------
# Self-check


_ARRAY_RE = re.compile(
    r"static const (u16|u32) (\w+)\[(\d+)\] = \{\n(.*?)\n\};", re.DOTALL
)
_WORD_RE = re.compile(r"0x([0-9A-F]{4,8})")


def _parse_arrays(header: str) -> dict[str, list[int]]:
    arrays: dict[str, list[int]] = {}
    for match in _ARRAY_RE.finditer(header):
        ctype, name, count, body = match.groups()
        values = [int(word, 16) for word in _WORD_RE.findall(body)]
        if len(values) != int(count):
            raise TilesetError(
                f"self-check: {name} declares {count} entries but lists "
                f"{len(values)}"
            )
        if ctype == "u16" and any(value > 0xFFFF for value in values):
            raise TilesetError(f"self-check: {name} has a value above u16")
        if ctype == "u32" and any(value > 0xFFFFFFFF for value in values):
            raise TilesetError(f"self-check: {name} has a value above u32")
        if name in arrays:
            raise TilesetError(f"self-check: duplicate array {name}")
        arrays[name] = values
    return arrays


def _words_to_bytes(words: Sequence[int]) -> bytes:
    return b"".join(value.to_bytes(4, "little") for value in words)


def _expect_error(call: Callable[[], object], needle: str) -> None:
    try:
        call()
    except TilesetError as exc:
        if needle not in str(exc):
            raise TilesetError(
                f"self-check: expected an error containing {needle!r}, got "
                f"{exc}"
            ) from None
        return
    raise TilesetError(f"self-check: expected an error containing {needle!r}")


def self_check() -> None:
    """Verify the generator without a ROM, an emulator or a build."""

    image = load_image(SOURCE_PNG)

    # Determinism: two independent renders must be byte-identical.
    first = render_header(image)
    second = render_header(load_image(SOURCE_PNG))
    if first != second:
        raise TilesetError("self-check: rendering is not deterministic")
    if str(REPO_ROOT) in first or str(SOURCE_PNG) in first:
        raise TilesetError("self-check: generated header leaks an absolute path")

    arrays = _parse_arrays(first)
    for name in (GFX_NAME, PAL_NAME, BG_NAME, TILEMAP_NAME):
        if name not in arrays:
            raise TilesetError(f"self-check: generated header lacks {name}")

    # Gfx: literal-only LZ77, exactly 2048 uncompressed bytes, matching the PNG.
    gfx_stream = _words_to_bytes(arrays[GFX_NAME])
    if len(arrays[GFX_NAME]) != GFX_STREAM_WORDS:
        raise TilesetError(
            f"self-check: gfx array has {len(arrays[GFX_NAME])} u32 words, "
            f"expected {GFX_STREAM_WORDS}"
        )
    if gfx_stream[:4] != b"\x10\x00\x08\x00":
        raise TilesetError(
            "self-check: gfx stream header is "
            f"{gfx_stream[:4].hex(' ')}, expected 10 00 08 00"
        )
    decoded = decode_lz77_literal(gfx_stream)
    if len(decoded) != GFX_BYTES:
        raise TilesetError(
            f"self-check: gfx decodes to {len(decoded)} bytes, expected "
            f"{GFX_BYTES}"
        )
    expected_gfx = pack_tiles(image)
    if decoded != expected_gfx:
        raise TilesetError(
            "self-check: decoded gfx does not match the packed PNG tiles"
        )

    # Palette: 14 rows of 16, authored colours only in row 2.
    pal_words = arrays[PAL_NAME]
    if len(pal_words) != PALETTE_ENTRIES:
        raise TilesetError(
            f"self-check: palette has {len(pal_words)} entries, expected "
            f"{PALETTE_ENTRIES}"
        )
    base = PALETTE_ROW * PALETTE_ROW_SIZE
    if pal_words[base] != 0:
        raise TilesetError("self-check: palette row 2 index 0 is not forced to 0")
    if not any(pal_words[base + 1 : base + PALETTE_ROW_SIZE]):
        raise TilesetError("self-check: palette row 2 is all zero")
    for row in range(PALETTE_ROWS):
        if row == PALETTE_ROW:
            continue
        start = row * PALETTE_ROW_SIZE
        if any(pal_words[start : start + PALETTE_ROW_SIZE]):
            raise TilesetError(
                f"self-check: palette row {row} is not zero; only row "
                f"{PALETTE_ROW} may hold the tileset"
            )
    expected_pal = palette_words(image)
    if pal_words != expected_pal:
        raise TilesetError(
            "self-check: palette does not match the PNG palette converted "
            "to RGB555"
        )

    # Background graphics: the four-byte zero-size LZ77 stream.
    bg_words = arrays[BG_NAME]
    if len(bg_words) != 1 or _words_to_bytes(bg_words) != LZ77_EMPTY_STREAM:
        raise TilesetError(
            "self-check: background graphics are not the 10 00 00 00 stream"
        )

    # Tilemap: header, bank 4, base 0xC0, 16 blocks x 4 entries in TL/TR/BL/BR.
    tilemap = arrays[TILEMAP_NAME]
    if len(tilemap) != TILEMAP_ENTRIES:
        raise TilesetError(
            f"self-check: tilemap has {len(tilemap)} entries, expected "
            f"{TILEMAP_ENTRIES}"
        )
    if tilemap[0] != TILEMAP_HEADER:
        raise TilesetError(
            f"self-check: tilemap header is 0x{tilemap[0]:04X}, expected "
            f"0x{TILEMAP_HEADER:04X}"
        )
    for block in range(BLOCK_COUNT):
        for quadrant in range(TILES_PER_BLOCK):
            word = tilemap[1 + block * TILES_PER_BLOCK + quadrant]
            expected = (PALETTE_BANK << 12) | (
                TILE_BASE + block * TILES_PER_BLOCK + quadrant
            )
            if word != expected:
                raise TilesetError(
                    f"self-check: tilemap block {block} quadrant {quadrant} "
                    f"is 0x{word:04X}, expected 0x{expected:04X}"
                )
            if ((word >> 12) & 0xF) != PALETTE_BANK:
                raise TilesetError(
                    f"self-check: tilemap block {block} does not select "
                    f"palette bank {PALETTE_BANK}"
                )
            if (word & 0x3FF) < TILE_BASE:
                raise TilesetError(
                    f"self-check: tilemap block {block} is below tile base "
                    f"0x{TILE_BASE:02X}"
                )

    # The entry must reference every generated array.
    entry = re.search(
        r"static const struct TilesetEntry "
        + ENTRY_NAME
        + r" = \{(.*?)\n\};",
        first,
        re.DOTALL,
    )
    if entry is None:
        raise TilesetError(f"self-check: generated header lacks {ENTRY_NAME}")
    entry_body = entry.group(1)
    for needle in (
        f".pTileGraphics = {GFX_NAME},",
        f".pPalette = {PAL_NAME},",
        f".pBackgroundGraphics = {BG_NAME},",
        f".pTilemap = (const u8*){TILEMAP_NAME},",
        ".animatedTileset = 0,",
        ".animatedPalette = 0,",
    ):
        if needle not in entry_body:
            raise TilesetError(
                f"self-check: {ENTRY_NAME} lacks {needle!r}"
            )

    with tempfile.TemporaryDirectory(prefix="mf-gen-tileset-") as tmp:
        tmp_dir = Path(tmp)

        # Missing and stale headers must fail --check.
        missing = tmp_dir / "tileset_tables.h"
        _expect_error(lambda: check_header(missing, first), "missing")
        write_header(missing, first)
        check_header(missing, first)
        missing.write_bytes(first.encode("utf-8") + b"\n")
        _expect_error(lambda: check_header(missing, first), "stale")

        # Wrong image dimensions are rejected.
        small = tmp_dir / "small.png"
        pngio.write_indexed_png(
            small,
            32,
            32,
            [(0, 0, 0)] * PALETTE_SIZE,
            [[0] * 32 for _ in range(32)],
            transparency=(0,),
        )
        _expect_error(lambda: build_header(small), f"{IMAGE_SIZE}x{IMAGE_SIZE}")

        # A palette index above 15 is rejected (4bpp tiles have 16 colours).
        bad_pixels = tuple(
            tuple(16 if (x == 0 and y == 0) else 0 for x in range(IMAGE_SIZE))
            for y in range(IMAGE_SIZE)
        )
        bad_image = pngio.PngImage(
            path="bad.png",
            width=IMAGE_SIZE,
            height=IMAGE_SIZE,
            bit_depth=8,
            color_type=3,
            palette=tuple((0, 0, 0) for _ in range(PALETTE_SIZE)),
            transparency=(0,),
            pixels=bad_pixels,
        )
        _expect_error(lambda: validate_image(bad_image), "palette index 16")


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Generate hack/gen/tileset_tables.h from the authored blockout "
            "tileset PNG."
        )
    )
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--write", action="store_true", help="write the header")
    mode.add_argument("--check", action="store_true", help="fail if it is stale")
    mode.add_argument("--self-check", action="store_true", help="run the tool suite")
    parser.add_argument(
        "--out",
        type=Path,
        default=DEFAULT_OUT,
        help=f"generated header path (default: {display_path(DEFAULT_OUT)})",
    )
    args = parser.parse_args(argv)

    try:
        if args.self_check:
            self_check()
            print(
                f"TILESET: PASS: self-check ({GFX_BYTES} gfx bytes in "
                f"{GFX_STREAM_WORDS} u32 words, {PALETTE_ENTRIES} palette "
                f"u16, {TILEMAP_ENTRIES} tilemap u16)"
            )
            return 0

        content = build_header()
        out = Path(args.out)
        if args.write:
            changed = write_header(out, content)
            print(f"TILESET: {'wrote' if changed else 'unchanged'} {display_path(out)}")
            print("TILESET: PASS")
        else:
            check_header(out, content)
            print(f"TILESET: PASS ({display_path(out)} is fresh)")
        return 0
    except TilesetError as exc:
        print(f"TILESET: FAIL: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
