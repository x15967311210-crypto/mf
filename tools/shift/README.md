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

## Current baseline counts

- 662 ROM literals in `.4byte`/`.word`; 697 `ldr =0x08...` reference comments.
- 388 unique ROM values.
- Literal targets: 580 in `.rodata`, 82 in `.data`.
- 47 extracted blobs: 11 pointer-table candidates, 7 possible, 29 data
  (graphics/audio false-positive candidates are kept in the report).

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
- A blob is a pointer-table candidate when at least 15% of its aligned words
  land in a ROM/RAM address range and at least four distinct targets appear.
  Graphics/audio can pass that test by accident; review the samples.

## Shift test

`shift_test.py --build` moves the normal `mf_us.gba/.elf/.map` into
`work/shift/baseline/`, builds with `. += 0x1000` after `intr_main`, copies the
result to `work/shift/mf_us_shift.gba`, and restores the baseline in a `finally`
block.  It is expected to build today; the dynamic behavior test will fail until
SHIFT-005/006 rewrite the pointers.  That failing run is the refactor's
acceptance target.
