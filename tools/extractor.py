import argparse
from io import BufferedReader
import json
from pathlib import Path


DATA_PATH = "data"
DATABASE_PATH = "database.json"
DATABASE_DEBUG_PATH = "database_debug.json"
REGIONS = ["us"]


def extract_data(region: str, debug: bool, quiet: bool = False) -> None:
    if debug:
        region = "eu_beta"
    rom: BufferedReader = open(f"mf_{region}_baserom.gba", "rb")
    db_path = DATABASE_DEBUG_PATH if debug else DATABASE_PATH
    with open(db_path, "r") as f:
        db = json.load(f)

    for entry in db:
        path: str = entry["path"]
        if not quiet:
            print(f"Extracting {path}")

        # Create directories if they don't exist
        root_dir = entry.get("dir", DATA_PATH)
        path_obj = Path(root_dir, path)
        path_obj.parent.mkdir(parents=True, exist_ok=True)

        addr = entry["addr"].get(region)
        if addr is not None:
            count = entry["count"]
            if isinstance(count, dict):
                count = count[region]
            size: int = int(count, 16) * entry["size"]
            rom.seek(int(addr, 16))
            with open(path_obj, "wb") as f:
                f.write(rom.read(size))

    rom.close()
    split_intro_blob()
    split_sa_x_close_up_blob()
    split_new_file_intro_frame_data_blob()
    split_new_file_intro_data_pointer_tables()
    split_new_file_intro_gfx_pointer_tables()
    split_navigation_pop_up_graphics_blob()


def split_blob(path: Path, table_offset: int, table_size: int,
               before_path: Path, after_path: Path) -> None:
    blob = path.read_bytes()
    table_end = table_offset + table_size
    if len(blob) < table_end:
        raise ValueError(
            f"{path} is {len(blob)} bytes, too small for a table at "
            f"0x{table_offset:x} (size 0x{table_size:x})")
    before_path.write_bytes(blob[:table_offset])
    after_path.write_bytes(blob[table_end:])


def split_intro_blob() -> None:
    """Carve the raw FrameData table out of the intro tilemap blob.

    `Blob_6094d0_60b148.bin` contains a 9-entry `struct FrameData` table at
    offset 0x1738.  Its pFrame pointers are raw ROM addresses, so the table
    must be rebuilt as C data to let the linker relocate it.  Split the blob
    into the bytes before and after the table so the surrounding tilemap data
    stays byte-identical; the table itself is skipped.
    """
    blob_path = Path(DATA_PATH, "Blob_6094d0_60b148.bin")
    if not blob_path.exists():
        return
    split_blob(
        blob_path, 0x1738, 0x48,
        Path(DATA_PATH, "Blob_6094d0_before.bin"),
        Path(DATA_PATH, "Blob_6094d0_after.bin"),
    )


# Raw pointer words inside the Sa-X close-up prefix.  Every word is a ROM
# address into the prefix itself, so keeping it in a raw blob would leave an
# absolute pointer that breaks as soon as the prefix moves (BUG-008 and the
# elevator callback corruption in BUG-012).
SA_X_CLOSE_UP_PREFIX_SIZE = 0xC5C2
SA_X_CLOSE_UP_PREFIX_POINTERS = (
    0x8056, 0x805E, 0x8066, 0x806E, 0x807E, 0x8086, 0x808E, 0x8096,
    0x809E, 0x80A6, 0x80AE, 0x80B6,
    0xC4DA, 0xC4EA, 0xC4FA, 0xC50A, 0xC51A, 0xC52A, 0xC532, 0xC542,
    0xC54A, 0xC55A, 0xC562, 0xC572, 0xC57A, 0xC58A, 0xC592,
    0xC5A2, 0xC5B2,
)


def split_sa_x_close_up_blob() -> None:
    """Carve the three raw FrameData tables out of the Sa-X close-up blob.

    `Blob_73421e_7478a0.bin` contains a 39-entry file-select `struct
    FrameData` table at offset 0xC5C2, a 38-entry animation `struct
    FrameData` table at offset 0xC6FA, and an 88-entry `struct FrameData`
    table at offset 0xC82A.  Their pFrame pointers are raw ROM addresses, so
    all three tables must be rebuilt as C data to let the linker relocate
    them.  Split the blob into the bytes before the first table and after the
    last table so the surrounding data stays byte-identical; the tables
    themselves are skipped.

    The prefix before the first table also embeds pointer tables whose words
    point inside the prefix.  Split every one of those pointers out so the C
    representation can relocate the words; the segments between them stay
    byte-identical.  The complete prefix is still written for audit evidence.
    """
    blob_path = Path(DATA_PATH, "Blob_73421e_7478a0.bin")
    if not blob_path.exists():
        return
    split_blob(
        blob_path, 0xC5C2, 0x138 + 0x130 + 0x2C0,
        Path(DATA_PATH, "Blob_73421e_prefix.bin"),
        Path(DATA_PATH, "Blob_73421e_after.bin"),
    )
    prefix = blob_path.read_bytes()[:SA_X_CLOSE_UP_PREFIX_SIZE]
    if len(prefix) != SA_X_CLOSE_UP_PREFIX_SIZE:
        raise ValueError(
            f"{blob_path} is too small for the 0x{SA_X_CLOSE_UP_PREFIX_SIZE:X}"
            "-byte Sa-X close-up prefix")
    start = 0
    for pointer in SA_X_CLOSE_UP_PREFIX_POINTERS:
        if pointer < start or pointer + 4 > len(prefix):
            raise ValueError(
                f"invalid Sa-X close-up prefix pointer offset 0x{pointer:X}")
        Path(DATA_PATH, f"Blob_73421e_prefix_seg_{start:04X}.bin").write_bytes(
            prefix[start:pointer])
        start = pointer + 4
    Path(DATA_PATH, f"Blob_73421e_prefix_seg_{start:04X}.bin").write_bytes(
        prefix[start:])


def split_new_file_intro_frame_data_blob() -> None:
    """Carve the two raw FrameData tables out of the intro blob.

    `Blob_5f6990_60093c.bin` contains a 26-entry landing `struct FrameData`
    table at offset 0x79E0 and a 70-entry ship-landing `struct FrameData`
    table at 0x8B48.  Their pFrame pointers are raw ROM addresses, so both
    tables must be rebuilt as C data to let the linker relocate them.  Split
    the blob into the prefix, the bytes between the tables, and the tail; the
    two tables themselves are skipped.  The spans keep the blob's original
    size and ordering inside the linked object.
    """
    blob_path = Path(DATA_PATH, "Blob_5f6990_60093c.bin")
    if not blob_path.exists():
        return
    blob = blob_path.read_bytes()
    if len(blob) != 0x9FAC:
        raise ValueError(
            f"{blob_path} is {len(blob)} bytes, expected 0x9FAC")
    spans = (
        (0x0000, 0x79E0, "Blob_5f6990_prefix.bin"),
        (0x7AB0, 0x8B48, "Blob_5f6990_middle.bin"),
        (0x8D78, 0x9FAC, "Blob_5f6990_after.bin"),
    )
    for start, end, name in spans:
        Path(DATA_PATH, name).write_bytes(blob[start:end])


# `Blob_6638a0_682fac.bin` also embeds a 52-record cutscene `struct FrameData`
# table at +0x159E0 (normal ROM 0x08679280..0x08679420).  The cutscene entries
# set their pOam to +0x159E0, +0x15A30, +0x15B00 or +0x15B10 and then walk the
# records by frame index, so every pFrame word must relocate with the blob
# (BUG-016: the shifted ROM read the stale normal targets and the OAM loop
# overflowed into gNonGameplayRam).
INTRO_DATA_BLOB_ADDR = 0x086638A0
INTRO_DATA_BLOB_SIZE = 0x1F70C
INTRO_DATA_STRUCT_PATH = Path("src/data/new_file_intro_data.c")
INTRO_CUTSCENE_TABLE_OFFSET = 0x159E0
INTRO_CUTSCENE_TABLE_COUNT = 52
INTRO_CUTSCENE_TABLE_END = (
    INTRO_CUTSCENE_TABLE_OFFSET + INTRO_CUTSCENE_TABLE_COUNT * 8)


def new_file_intro_cutscene_records(blob: bytes) -> list:
    """Return (offset, target blob offset or None, timer) for the table.

    A zero pFrame is a `FRAME_DATA_TERMINATOR` and stays a NULL initializer.
    Every other pFrame must point inside this blob, and the record's upper
    three metadata bytes must be zero so a C `struct FrameData` initializer
    reproduces them exactly.
    """
    if len(blob) != INTRO_DATA_BLOB_SIZE:
        raise ValueError(
            f"intro data blob is {len(blob)} bytes, "
            f"expected 0x{INTRO_DATA_BLOB_SIZE:X}")
    records = []
    for offset in range(
            INTRO_CUTSCENE_TABLE_OFFSET, INTRO_CUTSCENE_TABLE_END, 8):
        word = int.from_bytes(blob[offset:offset + 4], "little")
        rest = int.from_bytes(blob[offset + 4:offset + 8], "little")
        if rest > 0xFF:
            raise ValueError(
                f"intro cutscene record at +0x{offset:04X} has nonzero "
                f"padding 0x{rest:08X}")
        if word == 0:
            if rest != 0:
                raise ValueError(
                    f"intro cutscene terminator at +0x{offset:04X} has "
                    f"timer 0x{rest:02X}")
            records.append((offset, None, 0))
            continue
        if not (INTRO_DATA_BLOB_ADDR
                <= word < INTRO_DATA_BLOB_ADDR + INTRO_DATA_BLOB_SIZE):
            raise ValueError(
                f"intro cutscene pFrame at +0x{offset:04X} is 0x{word:08X}, "
                f"outside 0x{INTRO_DATA_BLOB_ADDR:08X}.."
                f"0x{INTRO_DATA_BLOB_ADDR + INTRO_DATA_BLOB_SIZE:08X}")
        records.append((offset, word - INTRO_DATA_BLOB_ADDR, rest))
    return records


def emit_new_file_intro_cutscene_table(blob: bytes) -> str:
    """Emit the C initializer entry for the cutscene FrameData table.

    `src/data/new_file_intro_data.c` embeds this exact text so the extractor
    and the committed table cannot drift apart.
    """
    records = new_file_intro_cutscene_records(blob)
    lines = ["    .cutsceneFrameData = {"]
    for offset, target, timer in records:
        if target is None:
            lines.append(
                f"        FRAME_DATA_TERMINATOR, /* +0x{offset:04X} */")
        else:
            lines.append(
                f"        {{ .pFrame = (const u16*)((const u8*)"
                f"&sBlob_6638a0_682fac + 0x{target:04X}), "
                f".timer = 0x{timer:02X} }}, /* +0x{offset:04X} */")
    lines.append("    },")
    return "\n".join(lines)


def check_new_file_intro_cutscene_table(blob: bytes) -> None:
    """Fail extraction if the committed C table does not match this blob."""
    if not INTRO_DATA_STRUCT_PATH.exists():
        return
    expected = emit_new_file_intro_cutscene_table(blob)
    if expected not in INTRO_DATA_STRUCT_PATH.read_text():
        raise ValueError(
            f"{INTRO_DATA_STRUCT_PATH} does not match the generated "
            "cutscene FrameData table; regenerate it with "
            "`python3 tools/extractor.py --emit-intro-cutscene-table`")


def split_new_file_intro_data_pointer_tables() -> None:
    """Split the raw FrameData pointer tables out of the intro data blob.

    `Blob_6638a0_682fac.bin` has a 0x50-byte region at 0x5BC containing two
    FrameData tables used by the monologue cutscenes.  Their pFrame words are
    raw ROM addresses; split the surrounding bytes into segments so the C
    representation can relocate the eight pointers.  The table bytes must stay
    at their original offsets because the cutscene code references the tables
    by absolute address.

    The 52-record cutscene table at 0x159E0 is also rebuilt in C (BUG-016), so
    the blob is split before it and resumed after it; the table bytes stay at
    their original offsets and the two surrounding segments keep the blob
    byte-identical.
    """
    blob_path = Path(DATA_PATH, "Blob_6638a0_682fac.bin")
    if not blob_path.exists():
        return
    blob = blob_path.read_bytes()
    if len(blob) != INTRO_DATA_BLOB_SIZE:
        raise ValueError(
            f"{blob_path} is {len(blob)} bytes, expected 0x1F70C")
    spans = (
        (0x0000, 0x0530, "Blob_6638a0_before0.bin"),
        (0x0534, 0x0538, "Blob_6638a0_gap_0530.bin"),
        (0x053C, 0x0540, "Blob_6638a0_gap_0538.bin"),
        (0x0544, 0x0548, "Blob_6638a0_gap_0540.bin"),
        (0x054C, 0x0550, "Blob_6638a0_gap_0548.bin"),
        (0x0550, 0x0558, "Blob_6638a0_term_0550.bin"),
        (0x055C, 0x0560, "Blob_6638a0_gap_0558.bin"),
        (0x0560, 0x0568, "Blob_6638a0_term_0560.bin"),
        (0x0568, 0x05BC, "Blob_6638a0_before2.bin"),
        (0x05C0, 0x05C4, "Blob_6638a0_gap_05C0.bin"),
        (0x05C8, 0x05CC, "Blob_6638a0_gap_05C8.bin"),
        (0x05CC, 0x05D4, "Blob_6638a0_term_05CC.bin"),
        (0x05D8, 0x05DC, "Blob_6638a0_gap_05D8.bin"),
        (0x05E0, 0x05E4, "Blob_6638a0_gap_05E0.bin"),
        (0x05E8, 0x05EC, "Blob_6638a0_gap_05E8.bin"),
        (0x05F0, 0x05F4, "Blob_6638a0_gap_05F0.bin"),
        (0x05F8, 0x05FC, "Blob_6638a0_gap_05F8.bin"),
        (0x0600, 0x0604, "Blob_6638a0_gap_0600.bin"),
        (0x0604, 0x060C, "Blob_6638a0_term_0604.bin"),
        (0x060C, INTRO_CUTSCENE_TABLE_OFFSET,
         "Blob_6638a0_seg_060C_159E0.bin"),
        (INTRO_CUTSCENE_TABLE_END, INTRO_DATA_BLOB_SIZE,
         "Blob_6638a0_seg_15B80_1F70C.bin"),
    )
    for start, end, name in spans:
        Path(DATA_PATH, name).write_bytes(blob[start:end])
    check_new_file_intro_cutscene_table(blob)


# `Blob_64e470_662804.bin` is the normal-ROM image of the intro graphics blob.
# Its SpecialCutscene `struct FrameData` array starts at +0xD6C8 and holds 229
# 8-byte records: a pFrame word followed by four metadata bytes.  Every nonzero
# pFrame word is a normal-layout ROM address into this same blob.
INTRO_GFX_BLOB_ADDR = 0x0864E470
INTRO_GFX_BLOB_SIZE = 0x14394
INTRO_GFX_FRAME_DATA_OFFSET = 0x0D6C8
INTRO_GFX_FRAME_DATA_COUNT = 229
INTRO_GFX_FRAME_DATA_POINTER_COUNT = 219
INTRO_GFX_STRUCT_PATH = Path("src/data/new_file_intro_data.c")


def new_file_intro_gfx_pointers(blob: bytes) -> list:
    """Return the (field offset, target blob offset) of every nonzero pFrame.

    Zero pFrame records are terminators, not pointers; they must stay inside
    the surrounding byte segments so the linked blob keeps its exact layout.
    """
    if len(blob) != INTRO_GFX_BLOB_SIZE:
        raise ValueError(
            f"intro graphics blob is {len(blob)} bytes, "
            f"expected 0x{INTRO_GFX_BLOB_SIZE:X}")
    pointers = []
    for i in range(INTRO_GFX_FRAME_DATA_COUNT):
        offset = INTRO_GFX_FRAME_DATA_OFFSET + i * 8
        word = int.from_bytes(blob[offset:offset + 4], "little")
        if word == 0:
            continue
        if not (INTRO_GFX_BLOB_ADDR
                <= word < INTRO_GFX_BLOB_ADDR + INTRO_GFX_BLOB_SIZE):
            raise ValueError(
                f"intro pFrame at +0x{offset:04X} is 0x{word:08X}, outside "
                f"0x{INTRO_GFX_BLOB_ADDR:08X}.."
                f"0x{INTRO_GFX_BLOB_ADDR + INTRO_GFX_BLOB_SIZE:08X}")
        pointers.append((offset, word - INTRO_GFX_BLOB_ADDR))
    if len(pointers) != INTRO_GFX_FRAME_DATA_POINTER_COUNT:
        raise ValueError(
            f"intro graphics blob has {len(pointers)} nonzero pFrame words, "
            f"expected {INTRO_GFX_FRAME_DATA_POINTER_COUNT}")
    return pointers


def new_file_intro_gfx_fields(blob: bytes) -> list:
    """Return the blob layout as interleaved ('seg'|'ptr', start, end) fields.

    A 'seg' field copies bytes verbatim; a 'ptr' field is a relocatable
    `const u16 *` whose end is the target blob offset.  Splitting only at
    pointer fields keeps zero terminator records inside their segment.
    """
    fields = []
    prev = 0
    for offset, target in new_file_intro_gfx_pointers(blob):
        if offset < prev:
            raise ValueError(f"overlapping intro pFrame offset 0x{offset:04X}")
        if offset > prev:
            fields.append(("seg", prev, offset))
        fields.append(("ptr", offset, target))
        prev = offset + 4
    if prev < len(blob):
        fields.append(("seg", prev, len(blob)))
    total = sum(
        end - start if kind == "seg" else 4
        for kind, start, end in fields)
    if total != len(blob):
        raise ValueError("intro graphics blob layout does not sum to its size")
    return fields


def emit_new_file_intro_gfx_struct(blob: bytes) -> str:
    """Emit the C struct/initializer matching the extractor's segment files.

    `src/data/new_file_intro_data.c` embeds this exact text so the pointer
    field list and the generated `data/Blob_64e470_seg_*.bin` files cannot
    drift apart.
    """
    fields = new_file_intro_gfx_fields(blob)
    lines = ["struct NewFileIntroGfxBlob {"]
    for kind, start, end in fields:
        if kind == "seg":
            lines.append(
                f"    u8 seg_{start:04X}_{end:04X}[0x{end - start:X}];")
        else:
            lines.append(
                f"    const u16 *p{start:04X}; "
                f"/* +0x{start:04X} -> +0x{end:04X} */")
    lines.append("} __attribute__((packed));")
    lines.append("")
    lines.append(
        "static const struct NewFileIntroGfxBlob sBlob_64e470_662804 = {")
    for kind, start, end in fields:
        if kind == "seg":
            name = f"seg_{start:04X}_{end:04X}"
            lines.append(
                f'    .{name} = INCBIN_U8("data/Blob_64e470_{name}.bin"),')
        else:
            lines.append(
                f"    .p{start:04X} = "
                f"(const u16*)((const u8*)&sBlob_64e470_662804 + 0x{end:04X}),")
    lines.append("};")
    return "\n".join(lines) + "\n"


def check_new_file_intro_gfx_struct(blob: bytes) -> None:
    """Fail extraction if the committed C struct does not match this blob."""
    if not INTRO_GFX_STRUCT_PATH.exists():
        return
    expected = emit_new_file_intro_gfx_struct(blob)
    if expected not in INTRO_GFX_STRUCT_PATH.read_text():
        raise ValueError(
            f"{INTRO_GFX_STRUCT_PATH} does not match the generated "
            "NewFileIntroGfxBlob; regenerate it with "
            "`python3 tools/extractor.py --emit-intro-gfx-struct`")


def split_new_file_intro_gfx_pointer_tables() -> None:
    """Split the raw pFrame pointer table out of the intro graphics blob.

    `Blob_64e470_662804.bin` contains one 229-record SpecialCutscene
    `struct FrameData` array at +0xD6C8.  Its 219 nonzero pFrame words are
    normal-layout ROM addresses, so they must become relocatable C pointers;
    the 10 zero terminators and all metadata bytes stay in the segment files.
    Split only at the nonzero pFrame offsets so the linked blob keeps its
    original 0x14394-byte layout.
    """
    blob_path = Path(DATA_PATH, "Blob_64e470_662804.bin")
    if not blob_path.exists():
        return
    blob = blob_path.read_bytes()
    for kind, start, end in new_file_intro_gfx_fields(blob):
        if kind != "seg":
            continue
        Path(
            DATA_PATH,
            f"Blob_64e470_seg_{start:04X}_{end:04X}.bin").write_bytes(
                blob[start:end])
    check_new_file_intro_gfx_struct(blob)


def split_navigation_pop_up_graphics_blob() -> None:
    """Carve the navigation pop-up graphics descriptor table out of its blob.

    `Blob_5766D4_581510.bin` contains a 0x14-byte preamble followed by four
    0x18-byte graphics descriptors at offset 0x557C.  Their pGraphics words are
    raw ROM addresses, so the table must be rebuilt as C data to let the linker
    relocate them.  The descriptor consumer also indexes id 4, whose pGraphics
    word lives at table + 0x74 (one word past the four records; BUG-017), so
    that word is part of the rebuilt table too.  Split the blob into the bytes
    before the table and the bytes after it so the surrounding
    graphics/palette data stays byte-identical; the table itself is skipped
    (0x557C + 0x78 + 0x5848 = 0xAE3C).
    """
    blob_path = Path(DATA_PATH, "Blob_5766D4_581510.bin")
    if not blob_path.exists():
        return
    split_blob(
        blob_path, 0x557C, 0x14 + 4 * 0x18 + 4,
        Path(DATA_PATH, "Blob_5766D4_prefix.bin"),
        Path(DATA_PATH, "Blob_5766D4_after.bin"),
    )


def sort_by_address(debug: bool, quiet: bool = False) -> None:
    db_path = DATABASE_DEBUG_PATH if debug else DATABASE_PATH
    with open(db_path, "r") as f:
        db = json.load(f)

    # Sort by first region
    region = REGIONS[0]
    entries = [e for e in db if region in e["addr"]]
    entries.sort(key=lambda e: int(e["addr"][region], 16))
    remaining = [e for e in db if region not in e["addr"]]

    # Sort remaining regions
    for region in REGIONS[1:]:
        next_remaining = []
        for entry in remaining:
            addr = entry["addr"].get(region)
            if addr is not None:
                # Find index to insert entry
                addr = int(addr, 16)
                idx = len(entries)
                for i, cmp_entry in enumerate(entries):
                    cmp_addr = cmp_entry["addr"].get(region)
                    if cmp_addr is not None and addr < int(cmp_addr, 16):
                        idx = i
                        break
                entries.insert(idx, entry)
            else:
                next_remaining.append(entry)
        remaining = next_remaining

    if len(remaining) > 0:
        raise ValueError(f"{len(remaining)} entries were not sorted")
    
    # Write sorted entries
    with open(db_path, "w") as f:
        json.dump(entries, f, indent=2)
    if not quiet:
        print(f"Sorted entries in {db_path} by address")


def total_blob_size() -> None:
    total_size = 0x6f9d24
    with open(DATABASE_PATH, "r") as f:
        db = json.load(f)
    blob_size = 0
    for entry in db:
        path: str = entry["path"]
        if not path.startswith("Blob"):
            continue
        count: int = entry["count"]
        size: int = int(count, 16) * entry["size"]
        blob_size += size
    assert blob_size <= total_size
    non_blob = total_size - blob_size
    fraction = f"0x{non_blob:x}/0x{total_size:x}"
    percent = f"{non_blob / total_size:.2%}"
    print(f"{fraction} bytes of data not in blobs ({percent}, 0x{blob_size:x} left)")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    # TODO: Add "eu", "jp", "cn", "eu_beta"
    group.add_argument("-r", "--region", type=str, choices=["us"],
        default="us", help="The region of the rom to extract from")
    # TODO: Support debug
    # group.add_argument("-d", "--debug", action="store_true",
    #     help="Extract debug data from the EU beta rom")
    group.add_argument("-b", "--blob", action="store_true", help="Compute total blob size")
    group.add_argument("--emit-intro-gfx-struct", action="store_true",
        help="Print the NewFileIntroGfxBlob C definition generated from the "
             "extracted intro graphics blob")
    group.add_argument("--emit-intro-cutscene-table", action="store_true",
        help="Print the cutscene FrameData initializer generated from the "
             "extracted new-file intro data blob")
    parser.add_argument("-q", "--quiet", action="store_true", help="Suppress output")
    parser.add_argument("--sort", action="store_true",
        help="Sort database entries by address")
    
    args = parser.parse_args()
    args.debug = False # TODO: Remove this line
    if not args.region and not args.debug:
        args.region = "us"

    if args.blob:
        total_blob_size()
    elif args.emit_intro_gfx_struct:
        blob_path = Path(DATA_PATH, "Blob_64e470_662804.bin")
        if not blob_path.exists():
            parser.error(f"{blob_path} does not exist; run the extractor first")
        print(emit_new_file_intro_gfx_struct(blob_path.read_bytes()), end="")
    elif args.emit_intro_cutscene_table:
        blob_path = Path(DATA_PATH, "Blob_6638a0_682fac.bin")
        if not blob_path.exists():
            parser.error(f"{blob_path} does not exist; run the extractor first")
        print(
            emit_new_file_intro_cutscene_table(blob_path.read_bytes()),
            end="")
    elif args.sort:
        sort_by_address(args.debug, args.quiet)
    else:
        extract_data(args.region, args.debug, args.quiet)
