# Data blob classification (SHIFT-004)

Status: **DONE** (tools-dev, branch `dev1`).  Inputs: `database.json`,
`work/shift/blob_scan.json`, `/home/x1596/proj/mf/mf_us.map`,
`/home/x1596/proj/mf/mf_us.elf`, and the extracted bytes under
`/home/x1596/proj/mf/data/`.

This report answers one question for SHIFT-006: **which of the 47 extracted
blobs are real pointer arrays that must become relocatable C, and which are
graphics/audio/data that must stay raw?**

The blob `addr` values in `database.json` are **ROM offsets**, not absolute
addresses (`Blob_a5224_a5258.bin` is at offset `0x000A5224`, i.e. absolute
`0x080A5224`).  Pointer values inside the blobs are absolute (`0x080A...`).
Keep that distinction when writing C.

Reproduce:

```sh
python3 tools/shift/audit_blobs.py --self-check
python3 tools/shift/audit_blobs.py \
    --data-root /home/x1596/proj/mf/data \
    --map /home/x1596/proj/mf/mf_us.map \
    --out work/shift/blob_scan.json
```

## Result

| Classification | Count | Meaning for SHIFT-006 |
|---|---:|---|
| `pointer_table` | 7 | Confirm and convert to relocatable C pointer arrays. |
| `possible` | 3 | Real pointers, but structured/mixed; manual model first. |
| `data` | 37 | Keep raw (`INCBIN`); do not convert in SHIFT-006. |

The SHIFT-002 heuristic reported 11 / 7 / 29.  That rule was
`hits >= 8 and density >= 15%`, which is too weak for 16-bit data: a pair of
adjacent palette, tilemap or sprite samples can form `0x08xxxxxx` or
`0x03xxxxxx` by accident.  The SHIFT-004 tool keeps that old result as
`baseline_classification` and adds structural tests (below).  The corrected
split is 7 / 3 / 37.  The 11 baseline "pointer tables" and 7 baseline
"possible" blobs are reconciled explicitly at the end of this report.

## Rule change in `tools/shift/audit_blobs.py`

The tool still counts every aligned 32-bit word whose value is in ROM, EWRAM
or IWRAM as pointer-like (`hits`), and still reports `density = hits / words`,
target sections and samples.  It now classifies with these metrics:

| Metric | Definition | Why it matters |
|---|---|---|
| `longest_run` | longest run of adjacent pointer words | A flat pointer table is a contiguous run. 16-bit false positives are isolated (runs 1-5). |
| `run_coverage` | fraction of hits in runs of length >= 8 | Rejects an isolated pointer every few words (audio/struct data). |
| `known_ratio` | fraction of hits resolving into a mapped section | Fake targets often land in unallocated ROM (`unknown`). |
| `stride`, `stride_coverage` | most common non-contiguous hit gap and fraction of hits on that stride | Finds 12-byte struct arrays with an embedded pointer. |
| `median_target_delta` | median gap between sorted unique targets | Evidence for "one tight target cluster" vs "addresses all over ROM". |

Rule (standard-library Python, no data files needed for `--self-check`):

```text
pointer_table
  hits >= 8
  and density >= 0.15
  and known_ratio >= 0.90
  and density >= 0.50
  and longest_run >= 8
  and run_coverage >= 0.50

possible
  hits >= 8
  and density >= 0.15
  and known_ratio >= 0.90
  and (longest_run >= 8 or (stride >= 2 and stride_coverage >= 0.50))

data
  everything else
```

`possible` is deliberately not called `pointer_table`: a mixed blob or a
struct array cannot be replaced by a flat C `u32[]` without losing its layout.
The JSON keeps the historical token `possible_pointer_table` so
`tools/shift/report.py` stays compatible; this report calls it `possible`.

## Confirmed pointer tables (7) — high confidence

These are fully contiguous pointer arrays.  Every candidate resolves into a
mapped section, and every blob is essentially 100% pointers.

| Blob | Bytes | Hits | Density | Max run | Target sections | Class | Evidence |
|---|---:|---:|---:|---:|---|---|---|
| `Blob_a5224_a5258.bin` | 52 | 13 | 1.000 | 13 | `.text` 13 | `pointer_table` | 13 consecutive Thumb callback pointers: 9× `Callback_Empty` plus DMA/VBlank/HBlank/VCount callbacks; sits immediately before `sSaveDataSramPointers`. |
| `Blob_79bec0_79c128.bin` | 616 | 154 | 1.000 | 154 | `.rodata` 140, `.data` 14 | `pointer_table` | 140 pointers into `sBlob_5657a8` (minimap palettes/tiles) plus 14 into `79ce10`; pause-screen map array. |
| `Blob_79c394_79c3c8.bin` | 52 | 13 | 1.000 | 13 | `.data` 7, `.rodata` 6 | `pointer_table` | 13-entry table: 6 pointers into intro tilemap blob `6094d0`, 7 into text-pointer blob `79ce10`. |
| `Blob_79c448_79c5a4.bin` | 348 | 87 | 1.000 | 87 | `.rodata` 87 | `pointer_table` | 87 ascending pointers indexing intro graphics: 37 into `64e470`, 44 into `6638a0`, 6 into `662cfc`. |
| `Blob_79c5c0_79cdd8.bin` | 2072 | 518 | 1.000 | 518 | `.rodata` 518 | `pointer_table` | 518 strictly ascending pointers into text blob `6b2fac`; 7 language groups of message-text pointers (`sMessageTextPointers`). |
| `Blob_79ce10_79e6a0.bin` | 6288 | 1572 | 1.000 | 1572 | `.rodata` 1572 | `pointer_table` | 1572 strictly ascending pointers into text blob `6b2fac`; monologue-text pointer table (`sMonologueTextPointers`). |
| `Blob_79e868_79eca0.bin` | 1080 | 270 | 1.000 | 270 | `.rodata` 249, `.data` 21 | `pointer_table` | 270 pointers: 249 into Sa-X close-up graphics `73421e` plus 21 self-references (shared ending pose/image frames). |

## Possible pointer tables (3) — medium confidence, manual review

These contain genuine pointers, but the blob is **not** a flat array.  A naive
`u32[]` conversion would produce the right values but the wrong structure, and
would likely be wrong about which word is the pointer in each record.

| Blob | Bytes | Hits | Density | Max run | Target sections | Class | Evidence |
|---|---:|---:|---:|---:|---|---|---|
| `Blob_74dc48_74e620.bin` | 2520 | 210 | 0.333 | 1 | `.rodata` 210 | `possible` | 12-byte structs `[flags, x/y, ptr]`; 210 genuine pointers at stride 3 into the credits blob `74a7d8` (0x0874Axxx). Needs a struct definition, not a pointer array. |
| `Blob_79c170_79c27c.bin` | 268 | 25 | 0.373 | 21 | `.rodata` 21, `.text` 3, `ewram` 1 | `possible` | Mixed: 3 Thumb code pointers at +0, glyph/coordinate bytes, then a 21-entry pointer run at +0xB8 into `582288`. Only the pointer regions are convertible. |
| `Blob_a5710_a8cdc.bin` | 13772 | 885 | 0.257 | 4 | `.rodata` 881, `ewram` 4 | `possible` | 12-byte sound entries `[0x3Cxx, ptr, 0x00FF00FF]`; 885 genuine pointers at stride 3 into `DirectSoundData_*`. Needs audio-aware relocation. |

**Manual review list: exactly these three blobs.**  They are the only ones
where real pointers are embedded in a larger record layout.  Everything else
is either a confirmed flat table or data.

SHIFT-006b1 update: `Blob_79c170_79c27c` is converted.  It is now the
268-byte struct `sBlob_79c170_79c27c` in `src/text.c` (3 Thumb code pointers,
counts/glyph/coordinate bytes, and 21 anchored text pointers); see
`tools/shift/README.md` for the field table and
`tools/shift/gen_blob_tables.py --check`.  `74dc48` and `a5710` remain
unconverted.

## Data blobs (37)

### Data with non-trivial pointer-like hits (8) — medium confidence

These were baseline candidates.  Inspection shows the hits are 16-bit
palette/tile/sprite pairs or graphics byte noise, not pointers.  They stay raw.

| Blob | Bytes | Hits | Density | Max run | Target sections | Class | Evidence |
|---|---:|---:|---:|---:|---|---|---|
| `Blob_2e5cae_2e6160.bin` | 1202 | 47 | 0.157 | 2 | `.rodata` 34, unmapped 13 | `data` | 16-bit sprite/animation data (`sprite_data.c`); 13/47 fake targets unmapped, longest run 2; the SHIFT-002 pointer-table false positive. |
| `Blob_4f7d80_4f8d30.bin` | 4016 | 21 | 0.021 | 5 | `.rodata` 21 | `data` | Tileset graphics (`tilesets_set4.c`); hits are the repeated 16-bit tile value `0x0840`; run of 5 at +0x284 but median target gap 627 B. |
| `Blob_5657a8_575a60.bin` | 66232 | 681 | 0.041 | 2 | `.rodata` 541, `iwram` 65, unmapped 47, `.text` 24, `ewram` 4 | `data` | Minimap palettes/tilemaps (`pause_screen_map_data.c`); 681/16.5k hits are BGR555 halfword pairs, longest run 2. |
| `Blob_5dfd6c_5e116c.bin` | 5120 | 40 | 0.031 | 1 | unmapped 28, `.rodata` 12 | `data` | Intro palette data; 28/40 hits land in unmapped ROM, longest run 1; classic BGR555 artifact. |
| `Blob_5f6990_60093c.bin` | 40876 | 219 | 0.021 | 2 | `.rodata` 115, unmapped 44, `iwram` 36, `.text` 22, `ewram` 2 | `data` | Intro graphics/palette data; 219 isolated hits (longest run 2), 20% unmapped. |
| `Blob_6094d0_60b148.bin` | 7288 | 153 | 0.084 | 1 | `.rodata` 145, `iwram` 7, `.text` 1 | `data` | Intro space tilemap (`new_file_intro_data.c`); tile pairs such as `0x03000002` and `0x0800A207` fake RAM/ROM pointers; longest run 1. |
| `Blob_6131c8_63a19c.bin` | 159700 | 1042 | 0.026 | 2 | `.rodata` 605, unmapped 216, `iwram` 137, `.text` 70, `ewram` 12, `.data` 1, `.bss` 1 | `data` | Cutscene background graphics; 1027 isolated hits, 21% unmapped, no run. |
| `Blob_64e470_662804.bin` | 82836 | 511 | 0.025 | 3 | `.rodata` 269, `iwram` 135, unmapped 62, `.text` 34, `ewram` 11 | `data` | Intro graphics indexed by table `79c448`; 511 isolated hits (longest run 3), 12% unmapped. |

### Clean data (29) — high confidence

No table structure; zero or only isolated hits.

| Blob | Bytes | Hits | Density | Max run | Target sections | Class | Evidence |
|---|---:|---:|---:|---:|---|---|---|
| `Blob_2e6382_2e6ba4.bin` | 2082 | 0 | 0.000 | 0 | — | `data` | Sprite target data (`target.c`); 86% zero words, no pointer-like words. |
| `Blob_39aa34_39f4b0.bin` | 19068 | 35 | 0.007 | 1 | `.rodata` 34, `ewram` 1 | `data` | Omega Metroid sprite data; 35 isolated hits in 19 KB (0.7%), no run. |
| `Blob_40a310_40afa8.bin` | 3224 | 0 | 0.000 | 0 | — | `data` | Common palette data (`common_pals.c`); no pointer-like words. |
| `Blob_458df0_4597c0.bin` | 2512 | 2 | 0.003 | 1 | `.rodata` 2 | `data` | Tileset_1 graphics; 2 isolated hits in 2.5 KB. |
| `Blob_462610_462be8.bin` | 1496 | 0 | 0.000 | 0 | — | `data` | Tileset_1 graphics; no pointer-like words. |
| `Blob_463414_4639ec.bin` | 1496 | 0 | 0.000 | 0 | — | `data` | Tileset_1 graphics; no pointer-like words. |
| `Blob_4f3f70_4f4d20.bin` | 3504 | 3 | 0.003 | 1 | `.rodata` 3 | `data` | Tileset_4 graphics; 3 isolated hits in 3.5 KB. |
| `Blob_4f4f74_4f5d24.bin` | 3504 | 3 | 0.003 | 1 | `.rodata` 3 | `data` | Tileset_4 graphics; 3 isolated hits in 3.5 KB. |
| `Blob_4f6d7c_4f7b2c.bin` | 3504 | 0 | 0.000 | 0 | — | `data` | Tileset_4 graphics; no pointer-like words. |
| `Blob_54d950_54e700.bin` | 3504 | 0 | 0.000 | 0 | — | `data` | Tileset_7 graphics; no pointer-like words. |
| `Blob_54e9a4_54f704.bin` | 3424 | 0 | 0.000 | 0 | — | `data` | Tileset_7 graphics; no pointer-like words. |
| `Blob_54f9a8_550708.bin` | 3424 | 0 | 0.000 | 0 | — | `data` | Tileset_7 graphics; no pointer-like words. |
| `Blob_5760e8_576168.bin` | 128 | 1 | 0.031 | 1 | `ewram` 1 | `data` | Event flag bytes (`event_data.c`); one isolated EWRAAM-looking word in 128 B. |
| `Blob_576217_576234.bin` | 29 | 0 | 0.000 | 0 | — | `data` | Pause-debug ID table (29 B); no pointer-like words. |
| `Blob_5766D4_581510.bin` | 44604 | 198 | 0.018 | 25 | unmapped 62, `.rodata` 53, `iwram` 45, `.text` 30, `ewram` 8 | `data` | Pause-debug event data; 198 scattered hits, 31% unmapped; the 25-word run at +0x551C is 16-bit pairs (`0x08010800`/`0x08010802`). |
| `Blob_58217b_58225c.bin` | 225 | 2 | 0.036 | 2 | `.text` 1, unmapped 1 | `data` | Pause-debug text/ID data; 2 isolated hits, one unmapped. |
| `Blob_582288_58b3cc.bin` | 37188 | 117 | 0.013 | 2 | `.rodata` 69, unmapped 34, `iwram` 9, `ewram` 3, `.text` 2 | `data` | ASCII save-menu strings (starts `SELECTSAVENUMBER...`); 117 isolated hits, 29% unmapped. |
| `Blob_598440_598818.bin` | 984 | 1 | 0.004 | 1 | `.text` 1 | `data` | Intro data; one isolated hit in 984 B. |
| `Blob_5f4e54_5f4ed4.bin` | 128 | 0 | 0.000 | 0 | — | `data` | Intro palette; 94% zero bytes, no table structure. |
| `Blob_605930_605d08.bin` | 984 | 0 | 0.000 | 0 | — | `data` | Title-screen background graphics; no pointer-like words. |
| `Blob_606a00_609020.bin` | 9760 | 41 | 0.017 | 2 | unmapped 21, `.rodata` 10, `iwram` 5, `.text` 4, `ewram` 1 | `data` | Title-screen space background graphics/palette; 41 isolated hits, 51% unmapped. |
| `Blob_6101b8_612e48.bin` | 11408 | 36 | 0.013 | 1 | `iwram` 15, unmapped 8, `.text` 6, `.rodata` 6, `ewram` 1 | `data` | Intro graphics/palette; 36 hits mostly IWRAM-form 16-bit pairs, no run. |
| `Blob_662cfc_663820.bin` | 2852 | 8 | 0.011 | 1 | `.rodata` 7, `.text` 1 | `data` | Intro palette; 8 isolated hits, median target gap 527 KB. |
| `Blob_6638a0_682fac.bin` | 128780 | 587 | 0.018 | 4 | `.rodata` 220, `iwram` 173, unmapped 117, `.text` 58, `ewram` 16, `rom` 3 | `data` | Intro graphics; 587 isolated hits (longest run 4), 20% unmapped. |
| `Blob_6b2fac_72eee0.bin` | 507700 | 710 | 0.006 | 3 | unmapped 618, `.rodata` 89, `.text` 3 | `data` | Text data (`text_data.c`, 507 KB); 87% of hits land in unmapped ROM because string bytes form fake addresses. |
| `Blob_73421e_7478a0.bin` | 79490 | 235 | 0.012 | 2 | unmapped 96, `iwram` 63, `.rodata` 39, `.text` 22, `ewram` 15 | `data` | Sa-X close-up graphics; 235 isolated hits, 41% unmapped. |
| `Blob_74a7d8_74b0b0.bin` | 2264 | 0 | 0.000 | 0 | — | `data` | Credits data; no pointer-like words. It is the target region of the `74dc48` struct pointers. |
| `Blob_74e650_74eb50.bin` | 1280 | 2 | 0.006 | 2 | unmapped 2 | `data` | Pre-results background graphics; 2 hits, both unmapped. |
| `Blob_79a19c_79a29c.bin` | 256 | 0 | 0.000 | 0 | — | `data` | Ending data; 256 bytes of `0xFF` padding, no pointer-like words. |

## Reconciliation with the SHIFT-002 candidate lists

### The 11 baseline `pointer_table` candidates

| Blob | SHIFT-002 | SHIFT-004 verdict | Why |
|---|---|---|---|
| `Blob_a5224_a5258.bin` | pointer_table | **pointer_table** | 13 contiguous Thumb callback pointers. |
| `Blob_79bec0_79c128.bin` | pointer_table | **pointer_table** | 154 contiguous pointers into `5657a8`/`79ce10`. |
| `Blob_79c394_79c3c8.bin` | pointer_table | **pointer_table** | 13 contiguous pointers into `6094d0`/`79ce10`. |
| `Blob_79c448_79c5a4.bin` | pointer_table | **pointer_table** | 87 contiguous pointers into `64e470`/`6638a0`/`662cfc`. |
| `Blob_79c5c0_79cdd8.bin` | pointer_table | **pointer_table** | 518 contiguous text pointers. |
| `Blob_79ce10_79e6a0.bin` | pointer_table | **pointer_table** | 1572 contiguous text pointers. |
| `Blob_79e868_79eca0.bin` | pointer_table | **pointer_table** | 270 contiguous ending-image pointers. |
| `Blob_74dc48_74e620.bin` | pointer_table | **possible** | 12-byte struct array, pointer at stride 3. |
| `Blob_79c170_79c27c.bin` | pointer_table | **possible** | Mixed code pointers + glyph data + 21-entry pointer run. |
| `Blob_a5710_a8cdc.bin` | pointer_table | **possible** | 12-byte sound entries with a pointer field. |
| `Blob_2e5cae_2e6160.bin` | pointer_table | **data** | 16-bit sprite data; 28% of fake targets unmapped. |

### The 7 baseline `possible` candidates

All seven are graphics/palette/tilemap data and are now `data`:

| Blob | SHIFT-004 verdict | Why it was a false positive |
|---|---|---|
| `Blob_4f7d80_4f8d30.bin` | **data** | Tileset graphics; repeated 16-bit tile value `0x0840`. |
| `Blob_5657a8_575a60.bin` | **data** | Minimap palettes/tilemaps; BGR555 halfword pairs. |
| `Blob_5dfd6c_5e116c.bin` | **data** | Intro palette; 70% of hits unmapped. |
| `Blob_5f6990_60093c.bin` | **data** | Intro graphics/palette; isolated hits only. |
| `Blob_6094d0_60b148.bin` | **data** | Intro tilemap; tile pairs fake RAM/ROM addresses. |
| `Blob_6131c8_63a19c.bin` | **data** | Cutscene graphics; isolated hits only. |
| `Blob_64e470_662804.bin` | **data** | Intro graphics; isolated hits only. |

**Uncertain cases:** only the three `possible` blobs above.  Their pointer
values are real (they resolve to mapped sections and repeat at a fixed stride
or in one run), but the record layout is not a flat array.  No other blob is
uncertain: the 37 `data` blobs have source context and structure that explain
every hit, and the 7 tables are byte-for-byte pointers.

## How to use this report

### Blobs that become C pointer arrays in SHIFT-006 (7)

`Blob_a5224_a5258`, `Blob_79bec0_79c128`, `Blob_79c394_79c3c8`,
`Blob_79c448_79c5a4`, `Blob_79c5c0_79cdd8`, `Blob_79ce10_79e6a0`,
`Blob_79e868_79eca0`.

Replace the `INCBIN_U8` declaration with a C array of the same byte size.  Emit
**symbol + offset** expressions, never new `0x08...` constants, because these
are exactly the values that `check_relocs --strict` must keep relocatable.
For example:

```c
static const u32 sBlob_79c448_79c5a4[87] = {
    (u32)sBlob_64e470_662804 + 0x000,
    (u32)sBlob_64e470_662804 + 0x738,
    /* ... */
};
```

For `Blob_a5224_a5258` the targets are Thumb functions; keep the low bit (`| 1`)
or use a correctly typed function-pointer array, and verify the call site.
The arrays are data (`const u32[]`), so they can live at the same ROM location
without resizing anything.

### Blobs that stay raw (37)

All 37 `data` blobs keep their `INCBIN_U8` declaration.  SHIFT-006 must **not**
convert them.  Their symbol names already provide the relocation anchor; any
code that references the blob should use the symbol, not a literal address.

The 8 medium-confidence `data` blobs (`2e5cae`, `4f7d80`, `5657a8`, `5dfd6c`,
`5f6990`, `6094d0`, `6131c8`, `64e470`) are the ones most likely to be
re-proposed by a naive density scan.  Point SHIFT-006 at this report before
converting them.

### Blobs that need a manual model first (3)

- `Blob_74dc48_74e620` — define the 12-byte struct (three words: flags,
  coordinates, pointer) and convert the pointer field of each entry.
- `Blob_a5710_a8cdc` — define the sound-entry struct (`[0x3Cxx, ptr,
  0x00FF00FF]`) or leave the audio blob raw and relocate its pointer fields
  with an audio-aware pass.
- `Blob_79c170_79c27c` — **converted by SHIFT-006b1**: the blob is the
  268-byte struct `sBlob_79c170_79c27c` in `src/text.c` (3 code pointers,
  glyph/coordinate data, 21-entry anchored pointer run).

### Next task: SHIFT-006

1. Convert the 7 confirmed tables to C arrays with `symbol + offset`
   expressions; keep byte size and linker placement unchanged.
2. Do **not** touch the 37 data blobs; they stay `INCBIN`.
3. Handle the 3 `possible` blobs manually (struct arrays / mixed regions).
   Until they are handled they are expected `check_relocs --strict` failures.
4. Re-run `audit_blobs.py`, then `make -f Makefile.shift audit`,
   `check_relocs --strict`, and the padded shift test.  The shift test should
   move from "fails because pointers are absolute" to "passes with the tables
   relocated".
5. Add a byte-size assertion for each converted array (compiled size must equal
   the original `bytes` column) so a struct change cannot silently resize a
   blob.
