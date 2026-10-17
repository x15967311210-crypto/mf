"""Minimal deterministic PNG reader/writer for the room content pipeline.

This module intentionally supports only what the pipeline needs:

* non-interlaced images,
* bit depth 8,
* colour types 0 (grey), 2 (RGB), 3 (indexed), 4 (grey+alpha), 6 (RGBA).

It is standard-library only.  No image library is allowed to leak host colour
management or metadata into generated content, so writing an image produces a
fixed chunk set with no timestamps: ``IHDR``, optional ``PLTE``/``tRNS``,
``IDAT`` and ``IEND``.

The reader is used by ``tiled_to_room.py`` to validate tileset dimensions and
the per-8x8-tile colour budget.  It is *not* a general PNG decoder.
"""

from __future__ import annotations

import struct
import zlib
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Sequence


PNG_SIGNATURE = b"\x89PNG\r\n\x1a\n"

COLOR_TYPE_CHANNELS = {
    0: 1,  # grey
    2: 3,  # RGB
    3: 1,  # palette index
    4: 2,  # grey + alpha
    6: 4,  # RGBA
}

COLOR_TYPE_NAMES = {
    0: "grey",
    2: "rgb",
    3: "indexed",
    4: "grey+alpha",
    6: "rgba",
}


class PngError(ValueError):
    """Raised when a PNG cannot be read by the strict fixture reader."""


@dataclass(frozen=True)
class PngImage:
    path: str
    width: int
    height: int
    bit_depth: int
    color_type: int
    palette: tuple[tuple[int, int, int], ...]
    transparency: tuple[int, ...]
    pixels: tuple[tuple[object, ...], ...]

    @property
    def color_type_name(self) -> str:
        return COLOR_TYPE_NAMES.get(self.color_type, f"type-{self.color_type}")


def _read_chunks(data: bytes) -> Iterable[tuple[bytes, bytes]]:
    if not data.startswith(PNG_SIGNATURE):
        raise PngError("not a PNG file (bad signature)")

    pos = len(PNG_SIGNATURE)
    while pos < len(data):
        if pos + 8 > len(data):
            raise PngError("truncated PNG chunk header")
        length = struct.unpack_from(">I", data, pos)[0]
        chunk_type = data[pos + 4:pos + 8]
        start = pos + 8
        end = start + length
        crc_end = end + 4
        if crc_end > len(data):
            raise PngError(f"truncated PNG chunk {chunk_type!r}")
        payload = data[start:end]
        expected_crc = struct.unpack_from(">I", data, end)[0]
        actual_crc = zlib.crc32(chunk_type + payload) & 0xFFFFFFFF
        if expected_crc != actual_crc:
            raise PngError(f"bad CRC in PNG chunk {chunk_type.decode('ascii', 'replace')}")
        yield chunk_type, payload
        pos = crc_end
        if chunk_type == b"IEND":
            break

    if pos != len(data):
        raise PngError("trailing bytes after PNG IEND")


def _paeth(a: int, b: int, c: int) -> int:
    p = a + b - c
    pa = abs(p - a)
    pb = abs(p - b)
    pc = abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    if pb <= pc:
        return b
    return c


def _unfilter(
    raw: bytes, width: int, height: int, channels: int
) -> list[bytearray]:
    stride = width * channels
    expected = height * (stride + 1)
    if len(raw) != expected:
        raise PngError(
            f"decompressed PNG has {len(raw)} bytes, expected {expected} "
            f"for {width}x{height} with {channels} channel(s)"
        )

    rows: list[bytearray] = []
    previous = bytearray(stride)
    pos = 0
    for _ in range(height):
        filter_type = raw[pos]
        pos += 1
        row = bytearray(raw[pos:pos + stride])
        pos += stride

        if filter_type == 0:
            pass
        elif filter_type == 1:  # Sub
            for i in range(stride):
                left = row[i - channels] if i >= channels else 0
                row[i] = (row[i] + left) & 0xFF
        elif filter_type == 2:  # Up
            for i in range(stride):
                row[i] = (row[i] + previous[i]) & 0xFF
        elif filter_type == 3:  # Average
            for i in range(stride):
                left = row[i - channels] if i >= channels else 0
                row[i] = (row[i] + ((left + previous[i]) >> 1)) & 0xFF
        elif filter_type == 4:  # Paeth
            for i in range(stride):
                left = row[i - channels] if i >= channels else 0
                upper_left = previous[i - channels] if i >= channels else 0
                row[i] = (row[i] + _paeth(left, previous[i], upper_left)) & 0xFF
        else:
            raise PngError(f"unsupported PNG scanline filter type {filter_type}")

        rows.append(row)
        previous = row

    return rows


def read_png(path: str | Path) -> PngImage:
    """Read a non-interlaced, 8-bit PNG.

    ``pixels`` is a tuple of rows.  Indexed images contain palette indices;
    grey images contain one channel; RGB/RGBA contain tuples.  Keeping the
    original channel shape lets the caller decide how to count colours.
    """

    path = Path(path)
    try:
        data = path.read_bytes()
    except OSError as exc:
        raise PngError(f"cannot read PNG {path}: {exc}") from exc

    ihdr = None
    palette: list[tuple[int, int, int]] = []
    transparency: tuple[int, ...] = ()
    idat = bytearray()

    for chunk_type, payload in _read_chunks(data):
        if chunk_type == b"IHDR":
            if ihdr is not None:
                raise PngError("duplicate IHDR chunk")
            if len(payload) != 13:
                raise PngError("bad IHDR length")
            ihdr = struct.unpack(">IIBBBBB", payload)
        elif chunk_type == b"PLTE":
            if len(payload) % 3 != 0 or not payload:
                raise PngError("bad PLTE length")
            palette = [
                (payload[i], payload[i + 1], payload[i + 2])
                for i in range(0, len(payload), 3)
            ]
        elif chunk_type == b"tRNS":
            transparency = tuple(payload)
        elif chunk_type == b"IDAT":
            idat.extend(payload)
        elif chunk_type == b"IEND":
            pass
        elif chunk_type in (b"IHDR", b"PLTE", b"tRNS", b"IDAT"):
            raise PngError(f"duplicate PNG chunk {chunk_type!r}")
        # Ancillary chunks (gAMA, pHYs, tEXt, ...) are ignored on read.

    if ihdr is None:
        raise PngError("missing IHDR chunk")
    if not idat:
        raise PngError("missing IDAT chunk")

    width, height, bit_depth, color_type, compression, filter_method, interlace = ihdr
    if width <= 0 or height <= 0:
        raise PngError(f"invalid PNG dimensions {width}x{height}")
    if bit_depth != 8:
        raise PngError(
            f"unsupported PNG bit depth {bit_depth}; the content pipeline "
            "requires 8-bit images"
        )
    if color_type not in COLOR_TYPE_CHANNELS:
        raise PngError(f"unsupported PNG colour type {color_type}")
    if compression != 0 or filter_method != 0:
        raise PngError("unsupported PNG compression/filter method")
    if interlace != 0:
        raise PngError("interlaced PNGs are not supported")

    if color_type == 3:
        if not palette:
            raise PngError("indexed PNG is missing its PLTE chunk")
        if len(palette) > 256:
            raise PngError("indexed PNG palette has more than 256 entries")
    elif palette:
        raise PngError("non-indexed PNG must not contain a PLTE chunk")

    channels = COLOR_TYPE_CHANNELS[color_type]
    try:
        raw = zlib.decompress(bytes(idat))
    except zlib.error as exc:
        raise PngError(f"bad PNG IDAT compression: {exc}") from exc
    rows = _unfilter(raw, width, height, channels)

    pixels: list[tuple[object, ...]] = []
    for row in rows:
        if color_type == 3:
            pixels.append(tuple(row))
        elif color_type in (0, 4):
            step = channels
            pixels.append(tuple(row[i] for i in range(0, len(row), step))
                          if channels == 1
                          else tuple((row[i], row[i + 1])
                                     for i in range(0, len(row), 2)))
        elif color_type == 2:
            pixels.append(tuple(
                (row[i], row[i + 1], row[i + 2])
                for i in range(0, len(row), 3)
            ))
        else:  # RGBA
            pixels.append(tuple(
                (row[i], row[i + 1], row[i + 2], row[i + 3])
                for i in range(0, len(row), 4)
            ))

    return PngImage(
        path=path.name,
        width=width,
        height=height,
        bit_depth=bit_depth,
        color_type=color_type,
        palette=tuple(palette),
        transparency=transparency,
        pixels=tuple(pixels),
    )


def _chunk(chunk_type: bytes, payload: bytes) -> bytes:
    crc = zlib.crc32(chunk_type + payload) & 0xFFFFFFFF
    return struct.pack(">I", len(payload)) + chunk_type + payload + struct.pack(">I", crc)


def write_indexed_png(
    path: str | Path,
    width: int,
    height: int,
    palette: Sequence[tuple[int, int, int]],
    pixels: Sequence[Sequence[int]],
    transparency: Sequence[int] | None = None,
) -> bytes:
    """Write a deterministic, 8-bit indexed PNG and return its bytes.

    Only ``IHDR``, ``PLTE``, optional ``tRNS``, ``IDAT`` and ``IEND`` are
    emitted.  There is no timestamp or text metadata.
    """

    if width <= 0 or height <= 0:
        raise PngError("PNG dimensions must be positive")
    if not 1 <= len(palette) <= 256:
        raise PngError("palette must have between 1 and 256 entries")
    if len(pixels) != height or any(len(row) != width for row in pixels):
        raise PngError("pixel rows do not match the requested dimensions")

    flat = bytes(index for row in pixels for index in row)
    if any(index >= len(palette) for index in flat):
        raise PngError("pixel index is outside the palette")

    raw = bytearray()
    for row in pixels:
        raw.append(0)  # filter: None
        raw.extend(row)

    payload = bytearray(PNG_SIGNATURE)
    payload += _chunk(
        b"IHDR",
        struct.pack(">IIBBBBB", width, height, 8, 3, 0, 0, 0),
    )
    payload += _chunk(b"PLTE", bytes(channel for rgb in palette for channel in rgb))
    if transparency is not None:
        if len(transparency) > len(palette):
            raise PngError("tRNS has more entries than the palette")
        payload += _chunk(b"tRNS", bytes(transparency))
    payload += _chunk(b"IDAT", zlib.compress(bytes(raw), 9))
    payload += _chunk(b"IEND", b"")

    path = Path(path)
    path.write_bytes(payload)
    return bytes(payload)


def validate_tileset_image(
    image: PngImage,
    *,
    tile_width: int,
    tile_height: int,
    block_width: int,
    block_height: int,
    colors_per_tile: int,
    transparent_index: int | None,
) -> tuple[int, int]:
    """Validate tileset dimensions and the 4bpp colour budget.

    Returns ``(tile_count, block_count)``.  A block is a ``block_width`` x
    ``block_height`` chunk of the image (16x16 for the GBA engine), while a
    tile is the PNG/Tiled grid cell (normally 8x8 or 16x16).  Each 8x8 GBA
    tile may use at most ``colors_per_tile`` colours.
    """

    if tile_width <= 0 or tile_height <= 0:
        raise PngError("tile dimensions must be positive")
    if block_width <= 0 or block_height <= 0:
        raise PngError("block dimensions must be positive")
    if block_width % 8 != 0 or block_height % 8 != 0:
        raise PngError("block dimensions must be multiples of 8")
    if tile_width % 8 != 0 or tile_height % 8 != 0:
        raise PngError("tile dimensions must be multiples of 8")
    if colors_per_tile < 1 or colors_per_tile > 16:
        raise PngError("colors_per_tile must be in 1..16 (GBA 4bpp)")

    if image.width % tile_width != 0 or image.height % tile_height != 0:
        raise PngError(
            f"tileset image {image.width}x{image.height} is not a multiple "
            f"of the {tile_width}x{tile_height} tile grid"
        )
    if image.width % block_width != 0 or image.height % block_height != 0:
        raise PngError(
            f"tileset image {image.width}x{image.height} is not a multiple "
            f"of the {block_width}x{block_height} block grid"
        )

    if transparent_index is not None:
        if image.color_type == 3:
            if not 0 <= transparent_index < len(image.palette):
                raise PngError(
                    f"transparent_index {transparent_index} is outside the "
                    f"{len(image.palette)}-entry palette"
                )
        elif not 0 <= transparent_index <= 255:
            raise PngError("transparent_index must be in 0..255")

    tile_count = (image.width // tile_width) * (image.height // tile_height)
    block_count = (image.width // block_width) * (image.height // block_height)
    if tile_count == 0 or block_count == 0:
        raise PngError("tileset image contains no tiles")

    def colour_key(pixel: object) -> object:
        if image.color_type == 3:
            return pixel
        if image.color_type == 0:
            return ("grey", pixel)
        if image.color_type == 2:
            return pixel
        if image.color_type == 4:
            grey, alpha = pixel  # type: ignore[misc]
            return None if alpha == 0 else ("grey", grey)
        red, green, blue, alpha = pixel  # type: ignore[misc]
        return None if alpha == 0 else (red, green, blue)

    for y0 in range(0, image.height, 8):
        for x0 in range(0, image.width, 8):
            colours = set()
            for y in range(y0, min(y0 + 8, image.height)):
                row = image.pixels[y]
                for x in range(x0, min(x0 + 8, image.width)):
                    key = colour_key(row[x])
                    if key is not None:
                        colours.add(key)
            if len(colours) > colors_per_tile:
                raise PngError(
                    f"tileset tile at pixel ({x0},{y0}) uses {len(colours)} "
                    f"colours, budget is {colors_per_tile} (4bpp)"
                )

    return tile_count, block_count
