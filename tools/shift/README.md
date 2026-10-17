# Shift tooling

Goal: make ROM code/data relocatable while keeping the header, entry point,
EWRAM, IWRAM and MMIO fixed (D-002).  These tools find and classify the hardcoded
addresses that break when the link moves.

## Commands

```sh
make -f Makefile.shift audit
make -f Makefile.shift check-relocs          # report: literals, C refs, blob status
make -f Makefile.shift check-relocs-strict   # gate: fails on any of the above
make -f Makefile.shift check-linker          # gate premise: linker has no fixed ROM addr
make -f Makefile.shift shift-build
make -f Makefile.shift shift-test            # padded build + dynamic behavior
make -f Makefile.shift shift-check           # audit + smoke + link check + shift-test
```

`audit` and `check-relocs` are **report mode**: open literals, C ROM refs, and
raw blobs are printed but do not fail the command.  A missing build map or
ledger still fails, because there is nothing to report.  The gates are
`check-relocs-strict` and `shift-check`; they exit nonzero on any finding.  A
shift test skipped for lack of an emulator prints `SKIP (77)` and is never
reported as a pass (GNU make itself reports a failed recipe as exit 2, but the
77 is visible in the message and in `shift_test.py`'s exit status).

`audit-blobs` needs extracted bytes.  In a fresh `git worktree` there is no
`data/`, so point `DATA_ROOT` at the main tree before running the strict gate:

```sh
make -f Makefile.shift check-relocs-strict DATA_ROOT=/path/to/mf/data
```

The toolchain is discovered on `PATH`, or set `TOOLCHAIN` to an absolute
prefix (`/path/to/arm-none-eabi-`) for `shift-build`/`shift-test`/`shift-check`.

Or run the scripts directly:

```sh
python3 tools/shift/map_symbols.py --map mf_us.map --out work/shift/symbols.json
python3 tools/shift/audit_asm.py --self-check
python3 tools/shift/audit_asm.py --map mf_us.map --out work/shift/abs_refs.json
python3 tools/shift/audit_blobs.py --map mf_us.map --out work/shift/blob_scan.json
python3 tools/shift/rewrite_refs.py --out work/shift/rewrite_suggestions.md
python3 tools/shift/apply_refs.py --dry-run
python3 tools/shift/apply_refs.py --check
python3 tools/shift/report.py --out docs/shiftability-audit.md
```

`audit_asm.py` accepts `.4byte`/`.word` operands with 1–8 hex digits.  The
audio track headers write a 7-digit address such as `0x80a5710`; the audit
zero-pads it to the canonical `0x080A5710` in the ledger's `value` field while
keeping the original source line in `text`.  `--self-check` exercises that
parsing without needing a map: 8-, 7-, 6- and 1-digit operands, canonical
zero-padding, non-ROM constants, and symbol/`symbol+offset` operands (which are
not references and must not be flagged).

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
`missing: 47` and exits 0; pass `--data-root /path/to/mf/data` (or set
`DATA_ROOT`) to classify the blobs.

## Strict relocation gate

`check_relocs.py --strict` fails on **all** of these:

1. an `open` or `unknown` ROM record in `abs_refs.json`;
2. a hardcoded `0x08xxxxxx` literal in `src/`, `include/`, or `hack/` C;
3. a `pointer_table` or `possible_pointer_table` blob that is still included
   raw, i.e. still named by an `INCBIN` macro in C;
4. an unreadable blob scan, or a scan with `missing` blobs: the gate fails
   closed instead of passing without evidence.

The raw/ converted distinction is what lets the gate finish: `audit_blobs.py`
classifies the **extracted bytes**, and those bytes never change when a blob is
converted.  `check_relocs.py` therefore checks whether the blob filename is
still used by `INCBIN`.  All ten pointer-like blobs (seven SHIFT-006a tables plus
the three SHIFT-006b models) are generated C now, so strict mode reports zero
raw blobs; it still fails on the 660 open track-header literals until
SHIFT-006b4 rewrites them.

Report mode prints the same list but exits 0.  Current output before
SHIFT-006b4:

```text
blob scan: 47 blobs, 10 pointer-like (10 converted, 0 still raw)
    converted          Blob_a5224_a5258.bin
    converted          Blob_a5710_a8cdc.bin
    ...
check_relocs: 1357 ROM refs in ledger
  open literals: 660
  unknown:       0
  ldr comments:  697 (reference-only)
REPORT: 1 issue(s) would fail --strict:
  - 660 open ROM literal(s) remain
```

`check_relocs.py --self-check` exercises the INCBIN parser and the
converted/raw grouping without touching the tree; `check-relocs-strict` runs it
before the gate.

## Linker layout audit

`linker.ld` checked (SHIFT-007): the only fixed ROM address is the `rom` MEMORY
origin (`0x08000000`), which is the hardware contract, not a layout choice.  The
header/entry ordering (`asm/romheader.o(.text)`, `asm/crt0.o(.text)`,
`asm/intr_main.o(.text)`) keeps `0x08000000`/`0x080000C0` fixed through section
order, and every other ROM placement is section-relative (`ALIGN`, sequential
input sections, `>rom`).  The `. = 0x...` assignments are all inside `ewram` and
`iwram`, where fixed addresses are required by D-002.  Names such as
`asm/disasm_0x0808F5C4.o` are object filenames, not addresses.

`make -f Makefile.shift check-linker` (or
`python3 tools/shift/shift_test.py --check-linker`) enforces this: it checks the
three MEMORY origins, rejects any remaining `0x08xxxxxx` literal outside object
filenames, and verifies the first three ROM inputs.  `shift_test.py --build`
runs the same audit before linking.

## Current baseline counts

- SHIFT-005 rewrote all 662 eight-digit ROM literals in `.4byte`/`.word` to
  symbol expressions (0 remain in `asm/`); 697 `ldr =0x08...` reference
  comments remain.
- SHIFT-005b found the 660 seven-digit track-header literals in
  `sound/tracks/*.s` (`.word 0x80a....`); all 660 resolve to
  `sBlob_a5710_a8cdc+offset` in `.rodata`, and 0 are unknown.  They stay
  `open` until SHIFT-006b4 rewrites them.
- Ledger totals after SHIFT-005b: 5513 assembly references, 1357 ROM refs
  (660 literals + 697 `ldr` comments), 425 unique ROM values.
- SHIFT-005 rewrite targets: 580 in `.rodata`, 82 in `.data`.
- 47 extracted blobs: 7 confirmed pointer tables, 3 possible (embedded
  pointers in struct/audio data), 37 data.  The SHIFT-002 density rule is kept
  as `baseline_classification`; see `docs/blob-classification.md` for the
  per-blob evidence and the 11/7 baseline reconciliation.
- SHIFT-006a converted the 7 pointer tables to C arrays; SHIFT-006b1/2/3
  converted `79c170`, `74dc48` and `a5710`.  The strict gate reports all ten
  pointer-like blobs as `converted`, but fails on the 660 open track-header
  literals until SHIFT-006b4 lands.

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
arrays.  SHIFT-006b1/2/3 converted the three `possible` blobs (`79c170`,
`74dc48`, `a5710`) to relocatable structs.  The padded build and static checks
pass, but the boot smoke still stops at `frame_counter=3`, below the 450-frame
floor; the shift test remains the proof target.  SHIFT-005b made the 660
numeric `.word` track-header pointers into `a5710` visible to the audit: every
one is an `open` literal resolving to `sBlob_a5710_a8cdc+offset` in `.rodata`.
They are the last absolute-reference surface for the shift test; SHIFT-006b4
rewrites them to symbol expressions.

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
block ends with a compile-time `sizeof` check.

`Blob_a5710_a8cdc` is a 1135-record array plus a 152-byte raw tail, emitted as
one `const` struct in `src/data/audio.c`:

| Offset | Field | Handling |
|---|---|---|
| `+0x000` | `records[1135]` of 12 bytes | `instrumentType`, `pitch`, `unk_2`, `unk_3`, `const u32* pSample`, `struct Envelope`. |
| record `+0x004` | `pSample` | `symbol+offset` for the 880 ROM-valued records (856 `DirectSoundData_*`, 13 `sArray_a548a+0xD6`, 11 self references anchored to `sMusicCommandFunctionPointers`); `(const u32*)0xN` for the 255 small immediates. |
| `+0x3534` | `u8 tail[152]` | Raw bytes. |

The record count is confirmed by the 660 track headers that point into the
blob at 12-byte boundaries and by the largest absolute `VOICE` index (1134).
Compile-time checks cover record 12, records 13620, tail 152 and total 13772
bytes.  The 37 `data` blobs stay `INCBIN`.

## Classification rules

- ROM: `0x08000000`–`0x0A000000`; must become a symbol/label or be whitelisted.
- EWRAM/IWRAM/MMIO/palette/VRAM/OAM: fixed by D-002; not rewritten.
- `.4byte`/`.word` records are the actual data word; `ldr` comments are references
  to that word.  A rewrite fixes the `.4byte` line, not the `ldr` comment.
- Literal operands accept 1–8 hex digits and are zero-padded to eight in the
  ledger (`0x80a5710` -> `0x080A5710`); `text` keeps the original source.
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
block.  It verifies the link actually moved: `AgbMain` must end up at least
`--pad-bytes` above its baseline address (`SHIFT-LAYOUT`), so a no-op padded
link cannot pass silently.

Status lines are explicit and are never inferred from a zero exit alone:

| Status | Meaning |
|---|---|
| `SHIFT-BUILD: PASS/FAIL` | padded link and artifact copy |
| `SHIFT-LAYOUT: PASS/FAIL` | `AgbMain` moved by the requested pad |
| `SHIFT-STATIC: PASS/FAIL` | static ROM/header smoke on the shifted ROM |
| `SHIFT-DYNAMIC: PASS/FAIL` | emulator boot smoke reached 75% of frames |
| `SHIFT-DYNAMIC: SKIP (77)` | no emulator/harness; **not** a pass |

A dynamic run must return 0 **and** contain both the static and dynamic `PASS:`
markers; a crash, timeout, missing marker, or a 75% frame-counter shortfall is a
failure.  The current tree builds and statically passes but dynamically fails at
boot (`frame_counter=3`, below the 450/600 floor) because the two remaining
SHIFT-006b blobs (`74dc48`, `a5710`) are still raw.  That failing run is the
refactor's acceptance target.
