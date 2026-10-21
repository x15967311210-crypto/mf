# Giant disasm split plan (TECH-002)

Status: **plan only**. No `asm/` file has been moved yet. The cut points below
were validated by assembling the proposed parts and `ld -r`-ing them back
together; the result was byte-identical to the original `.text` in every tested
case. The residual risk is the explicit `linker.ld` edit, which must keep the
objects in ascending address order.

## Why split at all

The six remaining `asm/disasm_*.s` files hold 52,883 lines / ~1.0 MB and are
the main obstacle to reading and C-ifying the engine. Every function in them is
self-contained by inspection: across all six files there are **0 cross-function
local-label references**, **0 fallthrough candidates** (each function ends in
`bx lr`, `pop {…pc}` or `b`), and all function boundaries are adjacent (no
inter-function padding). Each function's literal pool lies inside its own line
range, so a function boundary is a safe object cut.

## Inventory

| File | Lines | Bytes | `.text` size | Base | Funcs | ROM refs | Subsystem |
|---|---:|---:|---:|---|---:|---:|---|
| `asm/disasm_0x0808F5C4.s` | 25,948 | 499,776 | 0xCE14 | 0x08090D60 | 217 | 335 | NewFileIntro / Intro / Ending / DiedOnSr388 / SpecialCutscene / Cutscene |
| `asm/disasm_0x0809deb4.s` | 7,882 | 149,189 | 0x3DD0 | 0x0809DEB4 | 53 | 119 | GameOver / FileSelect / SetLanguage / EndingImage |
| `asm/disasm_0x08079afc.s` | 7,082 | 131,887 | 0x3850 | 0x08079AFC | 27 | 79 | NavigationConversation / PauseScreenText / EasySleepText |
| `asm/disasm_0x0807e678.s` | 5,336 | 104,266 | 0x2AF4 | 0x0807E678 | 54 | 102 | StatusScreen / SRAM / EraseSramMenu |
| `asm/disasm_0x080765f8.s` | 5,266 | 99,958 | 0x2B20 | 0x080765F8 | 25 | 43 | PauseScreen / MapScreen / EasySleepMenu |
| `asm/disasm_0x08056140.s` | 1,369 | 25,725 | 0xAE4 | 0x08056140 | 20 | 15 | GunshipEnd |

`ROM refs` are the labelled `ldr` comments (TECH-001), not unresolved
relocations; `check_relocs` is already clean.

## First target: `disasm_0x0808F5C4.s` (335 refs, 217 functions)

Proposed cuts are at function starts, in address order:

| Part | Lines | Labels | First function | `.text` | Funcs |
|---|---|---:|---|---:|---:|
| `disasm_0x0808F5C4_090d60.s` | 1–2661 | 1–20 | `IntroSamusInShipProcess` (0x0809223C) | 0x14DC | 20 |
| `disasm_0x0808F5C4_09223c.s` | 2662–8147 | 21–58 | `EndingHandler` (0x08094E84) | 0x2C48 | 38 |
| `disasm_0x0808F5C4_094e84.s` | 8148–17514 | 59–130 | `CutsceneHandler` (0x0809994C) | 0x4AC8 | 72 |
| `disasm_0x0808F5C4_09994c.s` | 17515–25948 | 131–217 | `CutsceneElevatorMonologue` … end | 0x4228 | 87 |

- The last part ends at 0x0809DB74; the next object in `linker.ld` is
  `src/sa_x_close_up.o` at 0x0809DB74 (size 0x340).
- Every part must start with `.include "asm/macros.inc"`, a blank line and
  `.syntax unified`; otherwise the assembler reports `Macro already defined`.
- `ld -r` of the four parts produced 52,756 bytes, `cmp`-identical to the
  original `.text`.

### Linker edit

`linker.ld` currently has one line per object, e.g. line 499:

```
asm/disasm_0x0808F5C4.o(.text);
```

Replace it with the four parts in ascending address order:

```
asm/disasm_0x0808F5C4_090d60.o(.text);
asm/disasm_0x0808F5C4_09223c.o(.text);
asm/disasm_0x0808F5C4_094e84.o(.text);
asm/disasm_0x0808F5C4_09994c.o(.text);
```

Object names are auto-discovered (`Makefile` uses `$(wildcard asm/*.s)`), and
`tools/shift/shift_test.py` strips object filenames before its address check,
so the split names do not disturb the shifted/reordered gates.
`tools/shift/prefix_linker_objects.py` regex-matches `asm/…\.o`, so the HACK
linker script follows automatically.

## Other files (validated cut lines)

| File | Cuts at line | Parts | Result |
|---|---|---|---|
| `disasm_0x0807e678.s` | 5 / 1068 / 4409 | 3 | byte-identical |
| `disasm_0x0809deb4.s` | 5 / 879 / 6759 | 3 | byte-identical |
| `disasm_0x08079afc.s` | 5 / 3857 | 2 | byte-identical |
| `disasm_0x080765f8.s` | 5 / 1227 | 2 | byte-identical |
| `disasm_0x08056140.s` | 5 | 2 | candidate, smaller file; verify before moving |

The same `.include`/`.syntax` header rule and the same linker insertion rule
(ascending address order, one line replaced by N lines) apply.

## C-ification priority (hack-relevant, still in asm)

The room load, backgrounds, clipdata, scroll and message-banner paths are
already C (`src/room.c`, `src/clipdata.c`, `src/scroll.c`, `src/text.c`). The
remaining hack-relevant asm to prioritise:

| Rank | Function | Location | Size / notes |
|---:|---|---|---|
| 1 | `Sram_CheckLoadSaveFile` | `asm/disasm_0x0807e678.s:3967` 0x08080664 | 97 lines, 21 locals; calls `SramLoad_CurrentSave` + `Sram_InitSaveFile`; blocks QA-027/QA-030 |
| 2 | `SramRead_WorldData` | `:3132` 0x0807FF7C | 115 lines; world/room/state restore |
| 3 | `SramWrite_WorldData` | `:3025` 0x0807FEA4 | 107 lines; save write path |
| 4 | `Sram_InitSaveFile` | `:3701` 0x080803E4 | 139 lines; new-game defaults |
| 5 | `Sram_QuickSave` | `:1700` 0x0807F3AC | save-pad path |
| 6 | `SramRead_FromEwram` / `Sram_ReadAll` | `:1069` 0x0807EEA4 | slot/backup read |
| 7 | `Sram_WriteFileInfo` | `:4243` 0x080808B4 | 84 lines, no calls; file metadata |
| 8 | `GetMinimapData` | `asm/disasm_0x080765f8.s:1228` 0x08077084 | 26 lines; calls `CallLZ77UncompVram` |
| 9 | `ProcessPauseScreenText` | `asm/disasm_0x08079afc.s:3858` 0x0807B8D4 | 148 lines; text/pause |
| 10 | `NavigationConversationProcessText` | `asm/disasm_0x08079afc.s:6` 0x08079AFC | 800 lines, 99 locals, 1 jump table; hardest |

`Sram_*` first: it unlocks QA-027 (save validation) and QA-030 (automated
save/load) and is small enough to port incrementally with the existing host
harness.

## How to execute one split safely

1. Split the `.s` at the chosen function boundary; add the three-line header to
   every part.
2. Replace the single `linker.ld` object line with the N parts in ascending
   address order.
3. `make -j`; require `mf_us.gba` SHA `ca33f4348c2c05dd330d37b97e2c5a69531dfe87`.
4. `make -f Makefile.shift audit`, `smoke`, `test`; `check_relocs.py` clean.
5. `git diff` must only move lines between files plus the `linker.ld` list;
   no instruction or data byte changes.
6. If the SHA changes, revert the split — the linker order/layout was not
   reproduced; do not "fix" it by editing code.

## Risks

- `linker.ld` names every object explicitly; order is layout. A split is only
  acceptable if the re-link is byte-identical.
- Shared literal pools or alignment padding across a proposed cut would break
  identity; the validated cuts avoid both, but re-check with `ld -r` before
  committing each file.
- `asm/macros.inc` must be included exactly once per assembled file.
- `work/shift/abs_refs.json` is ignored and must be regenerated by
  `make -f Makefile.shift audit` before a direct `check_relocs --refs` run.
