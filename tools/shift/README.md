# Shift tooling

Goal: make ROM code/data relocatable while keeping the header, entry point,
EWRAM, IWRAM and MMIO fixed (D-002).  These tools find and classify the hardcoded
addresses that break when the link moves.

## Commands

```sh
make -f Makefile.shift audit
make -f Makefile.shift check-relocs
make -f Makefile.shift check-relocs-strict   # gate: no open literals / C ROM refs
make -f Makefile.shift shift-build
```

Or run the scripts directly:

```sh
python3 tools/shift/map_symbols.py --map mf_us.map --out work/shift/symbols.json
python3 tools/shift/audit_asm.py --map mf_us.map --out work/shift/abs_refs.json
python3 tools/shift/audit_blobs.py --map mf_us.map --out work/shift/blob_scan.json
python3 tools/shift/rewrite_refs.py --out work/shift/rewrite_suggestions.md
python3 tools/shift/apply_refs.py --dry-run
python3 tools/shift/apply_refs.py --check
python3 tools/shift/report.py --out docs/shiftability-audit.md
```

`apply_refs.py` rewrites the operand of each `.4byte`/`.word` ROM literal in
`abs_refs.json` to a symbol expression (`symbol` or `symbol+0xNN`).  It refuses
to touch a line whose label, directive, or value no longer matches the ledger,
and `--check` fails while any literal is still numeric.  Static (`STB_LOCAL`)
data symbols in C objects are not link-visible across objects, so those targets
use an equivalent global anchor in the same output section (for example the
literal `0x0839EC68` inside `sBlob_39aa34_39f4b0` becomes
`sOmegaMetroidPartOam_LeftLeg_Swiping+0x4264`); `--elf` points at the baseline
ELF used for that lookup.  The rewrite is address-equivalent: the SHA1 of the
rebuilt ROM must not change.

`audit_blobs.py` reads extracted bytes from `data/` by default.  In a worktree
without extracted data (for example a fresh `git worktree`), the audit reports
`missing: 47` and exits 0; pass
`--data-root /home/x1596/proj/mf/data` to classify the blobs.

## Current baseline counts

- SHIFT-005 rewrote all 662 ROM literals in `.4byte`/`.word` to symbol
  expressions (0 remain); 697 `ldr =0x08...` reference comments remain.
- 388 unique ROM values.
- Rewritten targets: 580 in `.rodata`, 82 in `.data`.
- 47 extracted blobs: 7 confirmed pointer tables, 3 possible (embedded
  pointers in struct/audio data), 37 data.  The SHIFT-002 density rule is kept
  as `baseline_classification`; see `docs/blob-classification.md` for the
  per-blob evidence and the 11/7 baseline reconciliation.

After SHIFT-005, the six remaining assembly blobs still contain only `ldr`
reference comments, not data literals:

| File | `ldr` refs |
|---|---:|
| `asm/disasm_0x0808F5C4.s` | 335 |
| `asm/disasm_0x0809deb4.s` | 119 |
| `asm/disasm_0x0807e678.s` | 102 |
| `asm/disasm_0x08079afc.s` | 79 |
| `asm/disasm_0x080765f8.s` | 43 |
| `asm/disasm_0x08056140.s` | 15 |

SHIFT-006a converted the seven confirmed blob pointer tables to relocatable C
arrays.  SHIFT-006b1 converted the first `possible` blob, `79c170`, to a
relocatable mixed struct.  The padded build still fails early at boot because
`74dc48` and `a5710` (and other unconverted absolute pointer data) remain raw;
the shift test is the proof target.

## Pointer tables (SHIFT-006a)

`gen_blob_tables.py` reads each extracted blob, resolves every aligned 32-bit
word to a `symbol+offset` expression (using a same-section global anchor for
`STB_LOCAL` targets, exactly like `apply_refs.py`), and renders an equivalent
`u32[]` initialiser plus a compile-time byte-size check.  `Blob_a5224_a5258`
keeps the ELF-verified Thumb bit on its callback pointers.

```sh
python3 tools/shift/gen_blob_tables.py --check   # fail if a generated block is stale
python3 tools/shift/gen_blob_tables.py --write   # regenerate after reviewing the diff
```

Converted tables: `sBlob_a5224_a5258`, `sBlob_79bec0_79c128`,
`sBlob_79c394_79c3c8`, `sBlob_79c448_79c5a4`, `sBlob_79c5c0_79cdd8`,
`sBlob_79ce10_79e6a0`, `sBlob_79e868_79eca0`.  The generated blocks live
between `BEGIN GENERATED` / `END GENERATED` markers in
`src/data/generic_data.c`, `src/menus/pause_screen_map.c`, and
`src/new_file_intro.c`; do not hand-edit them.

## Mixed blobs (SHIFT-006b)

`gen_blob_tables.py` also models mixed blobs as one C struct when pointers are
embedded in a record layout.  `Blob_79c170_79c27c` is emitted as
`sBlob_79c170_79c27c` in `src/text.c`:

| Offset | Field | Handling |
|---|---|---|
| `+0x000` | `u32 code[3]` | Thumb function symbols; the ELF `STT_FUNC` values already carry bit 0. |
| `+0x00C` | `u8 counts[4]` | Raw bytes. |
| `+0x010` | `u8 glyphs[36]` | Raw bytes. |
| `+0x034` | `u8 offsetsX[108]` | Raw bytes (36 three-byte tuples). |
| `+0x0A0` | `u8 offsetsNegX[24]` | Raw bytes (8 three-byte tuples). |
| `+0x0B8` | `u32 text[21]` | Pointers into `sBlob_582288_58b3cc`, anchored at global `sUnk_582280`. |

The positional struct initialiser is 268 bytes with no padding; the generated
block ends with a compile-time `sizeof` check.  `74dc48` and `a5710` remain
raw until their SHIFT-006b models land, and the 37 `data` blobs stay `INCBIN`.

## Classification rules

- ROM: `0x08000000`–`0x0A000000`; must become a symbol/label or be whitelisted.
- EWRAM/IWRAM/MMIO/palette/VRAM/OAM: fixed by D-002; not rewritten.
- `.4byte`/`.word` records are the actual data word; `ldr` comments are references
  to that word.  A rewrite fixes the `.4byte` line, not the `ldr` comment.
- A blob is pointer-like when an aligned word lands in a ROM/RAM address range.
  Density alone is not enough: 16-bit palettes, tilemaps and sprite data can
  form `0x08xxxxxx`/`0x03xxxxxx` values from two adjacent samples.
- SHIFT-004 rule (`audit_blobs.py`): a **pointer table** needs at least 8 hits,
  15% density, 90% of targets in mapped sections, 50% of words being pointers,
  a run of 8 adjacent pointers, and 50% of hits inside such runs.  A blob that
  passes the density/target tests but is mixed (a pointer run inside other
  data, or pointers on a regular struct stride) is **possible** and needs
  manual review.  Everything else is **data**.
- The old SHIFT-002 density rule is still emitted as
  `baseline_classification` for before/after comparison.
- Current result: 7 pointer tables, 3 possible, 37 data.  Per-blob evidence:
  `docs/blob-classification.md`.

## Shift test

`shift_test.py --build` moves the normal `mf_us.gba/.elf/.map` into
`work/shift/baseline/`, builds with `. += 0x1000` after `intr_main`, copies the
result to `work/shift/mf_us_shift.gba`, and restores the baseline in a `finally`
block.  It builds today; the dynamic behavior test still fails at boot until
SHIFT-006 converts the raw blob pointer tables.  That failing run is the
refactor's acceptance target.
