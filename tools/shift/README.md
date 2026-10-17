# Shift tooling

Goal: make ROM code/data relocatable while keeping the header, entry point,
EWRAM, IWRAM and MMIO fixed (D-002).  These tools find and classify the hardcoded
addresses that break when the link moves.

## Commands

```sh
make -f Makefile.shift audit
make -f Makefile.shift check-relocs
make -f Makefile.shift check-relocs-strict   # later gate; fails while refs are open
make -f Makefile.shift shift-build
```

Or run the scripts directly:

```sh
python3 tools/shift/map_symbols.py --map mf_us.map --out work/shift/symbols.json
python3 tools/shift/audit_asm.py --map mf_us.map --out work/shift/abs_refs.json
python3 tools/shift/audit_blobs.py --map mf_us.map --out work/shift/blob_scan.json
python3 tools/shift/rewrite_refs.py --out work/shift/rewrite_suggestions.md
python3 tools/shift/report.py --out docs/shiftability-audit.md
```

`audit_blobs.py` reads extracted bytes from `data/` by default.  In a worktree
without extracted data (for example a fresh `git worktree`), the audit reports
`missing: 47` and exits 0; pass
`--data-root /home/x1596/proj/mf/data` to classify the blobs.

## Current baseline counts

- 662 ROM literals in `.4byte`/`.word`; 697 `ldr =0x08...` reference comments.
- 388 unique ROM values.
- Literal targets: 580 in `.rodata`, 82 in `.data`.
- 47 extracted blobs: 7 confirmed pointer tables, 3 possible (embedded
  pointers in struct/audio data), 37 data.  The SHIFT-002 density rule is kept
  as `baseline_classification`; see `docs/blob-classification.md` for the
  per-blob evidence and the 11/7 baseline reconciliation.

The six remaining assembly blobs are the bulk:

| File | ROM refs |
|---|---:|
| `asm/disasm_0x0808F5C4.s` | 649 |
| `asm/disasm_0x0809deb4.s` | 238 |
| `asm/disasm_0x0807e678.s` | 193 |
| `asm/disasm_0x08079afc.s` | 156 |
| `asm/disasm_0x080765f8.s` | 86 |
| `asm/disasm_0x08056140.s` | 30 |

Converting those functions to C removes most of them; the audit exists to catch
the leftovers and to prove the result with the shift test.

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
block.  It is expected to build today; the dynamic behavior test will fail until
SHIFT-005/006 rewrite the pointers.  That failing run is the refactor's
acceptance target.
