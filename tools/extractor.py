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
    """
    blob_path = Path(DATA_PATH, "Blob_73421e_7478a0.bin")
    if not blob_path.exists():
        return
    split_blob(
        blob_path, 0xC5C2, 0x138 + 0x130 + 0x2C0,
        Path(DATA_PATH, "Blob_73421e_prefix.bin"),
        Path(DATA_PATH, "Blob_73421e_after.bin"),
    )
    # The prefix contains two raw FrameData pFrame words at 0xC5A2 and
    # 0xC5B2.  Split them out so the C representation can relocate the
    # pointers; the surrounding bytes stay byte-identical.
    prefix = blob_path.read_bytes()[:0xC5C2]
    Path(DATA_PATH, "Blob_73421e_prefix_before.bin").write_bytes(prefix[:0xC5A2])
    Path(DATA_PATH, "Blob_73421e_prefix_between.bin").write_bytes(prefix[0xC5A6:0xC5B2])
    Path(DATA_PATH, "Blob_73421e_prefix_after.bin").write_bytes(prefix[0xC5B6:0xC5C2])


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


def split_navigation_pop_up_graphics_blob() -> None:
    """Carve the navigation pop-up graphics descriptor table out of its blob.

    `Blob_5766D4_581510.bin` contains a 0x14-byte preamble followed by four
    0x18-byte graphics descriptors at offset 0x557C.  Their pGraphics words are
    raw ROM addresses, so the table must be rebuilt as C data to let the linker
    relocate them.  Split the blob into the bytes before the table and the
    bytes after it so the surrounding graphics/palette data stays
    byte-identical; the table itself is skipped (0x557C + 0x74 + 0x584C =
    0xAE3C).
    """
    blob_path = Path(DATA_PATH, "Blob_5766D4_581510.bin")
    if not blob_path.exists():
        return
    split_blob(
        blob_path, 0x557C, 0x14 + 4 * 0x18,
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
    parser.add_argument("-q", "--quiet", action="store_true", help="Suppress output")
    parser.add_argument("--sort", action="store_true",
        help="Sort database entries by address")
    
    args = parser.parse_args()
    args.debug = False # TODO: Remove this line
    if not args.region and not args.debug:
        args.region = "us"

    if args.blob:
        total_blob_size()
    elif args.sort:
        sort_by_address(args.debug, args.quiet)
    else:
        extract_data(args.region, args.debug, args.quiet)
