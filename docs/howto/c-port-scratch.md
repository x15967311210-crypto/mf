# How to port one function on a scratch branch (C-port loop)

This is the repeatable loop from TECH-003a: take one still-assembly function,
write a C candidate in a **throwaway copy** of the tree, build it, and compare
its code bytes with the baseline ELF before the port is proposed for the real
tree. It does not change the decompilation policy: the shiftable engine does
not require byte-matching, but a **baseline C port** must keep the normal ROM
SHA `ca33f4348c2c05dd330d37b97e2c5a69531dfe87`.

Tooling in this repository is deliberately dependency-light. `objdiff` and
`decomp-permuter` are **not installed here**; the default path is
`arm-none-eabi-objdump` plus `tools/decomp/compare_text.py`. Do not clone
third-party tool trees into this repository.

## 0. Pick a function

Start with the TECH-002a priority list
(`docs/architecture/disasm-split-plan.md`, "C-ification priority"):

| Rank | Function | Scratch `.s` file | Why |
|---:|---|---|---|
| 7 | `Sram_WriteFileInfo` (`0x080808B4`) | `asm/disasm_0x0807e678_0807eea4.s` | no calls, 84 lines — best first port |
| 1 | `Sram_CheckLoadSaveFile` (`0x08080664`) | same file | small, blocks QA-027/QA-030 |
| 2 | `SramRead_WorldData` (`0x0807FF7C`) | same file | world/room restore |
| 4 | `Sram_InitSaveFile` (`0x080803E4`) | same file | new-game defaults |

Read the function in the split `.s`, then map the fields it touches onto
`include/structs/save_file.h` and the existing headers. `struct SaveFile` is
still a stub; do not invent fields in the main tree — that is a separate decomp
task.

Check the baseline symbol and its current extent:

```sh
export PATH="$HOME/.local/bin:$PATH"   # ARM binutils live here on this box
arm-none-eabi-nm -S -P --defined-only mf_us.elf | grep -E 'Sram_(WriteFileInfo|CheckLoadSaveFile)'
arm-none-eabi-objdump -d --no-show-raw-insn \
  --start-address=0x080808B4 --stop-address=0x08080950 mf_us.elf
```

The assembler split files use `thumb_func_start`, which does **not** emit
`.size`, so `nm` reports a zero size for these symbols.
`compare_text.py` then infers the extent from the next global text symbol in
the same section (the next `thumb_func_start`, which includes the function's
literal pool) and labels the size source `next-global`. Pass `--size 0x...` if
you want a narrower range.

## 1. Make a scratch tree

Never experiment in the working tree. Use `/tmp` or the ignored `work/`
directory; neither is ever committed.

```sh
# Snapshot the current tip, including generated data and the pinned agbcc,
# but without git history or the old work/ scratch.
rsync -a --exclude '.git' --exclude 'work/' ./ /tmp/mf-cport/

# Keep the clean baseline ELF for comparisons (already built from this tip).
BASELINE_ELF="$PWD/mf_us.elf"
```

A `git worktree add` is also possible, but a fresh worktree has no `data/`,
`sound/direct_sound_samples/` or `tools/agbcc/` (all ignored); copying those
in is more work than the snapshot above.

## 2. Write the candidate C function

Inside `/tmp/mf-cport` only:

1. Add the C implementation, e.g. `src/sram_candidates.c`, using the existing
   headers and `#include "global.h"` conventions. Keep one function per
   experiment so the comparison is unambiguous.
2. Remove the original function body from the scratch copy of the split
   `.s`: from its `thumb_func_start <name>` line through the last literal-pool
   word, leaving the rest of the file untouched. The symbol must be defined
   exactly once.
3. Add the candidate object to the scratch `linker.ld` at the position where
   the removed asm function lived. The linker lists every object explicitly,
   so an unreferenced C object is otherwise not linked:

   ```
   src/sram_candidates.o(.text);
   ```

   This keeps the layout around the function stable; it does not have to be
   perfect for the comparison (symbols are looked up by name) but it makes the
   eventual SHA result easier to reason about.

Build the scratch tree:

```sh
cd /tmp/mf-cport
make -j"$(nproc)"
```

The candidate ELF is `/tmp/mf-cport/mf_us.elf`.

## 3. Compare the function

From the clean tree (or any tree with the tool):

```sh
python3 tools/decomp/compare_text.py \
  --baseline "$BASELINE_ELF" \
  --candidate /tmp/mf-cport/mf_us.elf \
  --symbol Sram_WriteFileInfo \
  --disasm
```

Exit status is the contract:

| Exit | Meaning |
|---:|---|
| `0` | same address/size lookup succeeded and every compared byte is identical |
| `1` | bytes differ, or the symbol sizes differ |
| `2` | usage error, missing tool, unreadable ELF, unknown symbol |

The report always names the symbol, both sizes (with the size source), the
first differing byte offset, and the number of differing bytes. `--disasm` adds
a normalized `objdump` diff: instruction addresses and encoding columns are
removed, and absolute branch/literal targets are resolved to `Symbol+0xoff`
using `nm`.

Use `--json` for a machine-readable report and `--pretty` for indented JSON.
`--baseline-symbol`/`--candidate-symbol` compare two differently named symbols
(useful for a renamed helper); `--size`/`--candidate-size` override the extent.

If the sizes differ, the tool runs the comparison over the longer range and
counts missing bytes as differences, so a truncated C function is never a
silent pass.

The tool's own checks run without any candidate build:

```sh
python3 tools/decomp/compare_text.py --self-check
```

It assembles a two-function fixture ELF with `arm-none-eabi-as`/`ld` in a
temporary directory and asserts identical → 0, modified → 1 with the expected
first byte, truncated → 1 with a size mismatch, and that the normalized
disassembly diff is empty only for identical code.

## 4. Acceptance rule

For a **baseline C port**, all four must hold before the port is proposed:

1. `compare_text.py` exits `0` for the symbol (byte-identical, including its
   literal pool).
2. `make` in the scratch tree produces SHA1
   `ca33f4348c2c05dd330d37b97e2c5a69531dfe87` (`make check`, or
   `sha1sum -c mf_us.sha1`).
3. The behavior suite is green:
   `make -f Makefile.shift test` (a missing emulator is `SKIP (77)` and is not
   a pass) plus `make -f Makefile.shift audit` and `smoke`.
4. `tools/shift/check_relocs.py` stays clean if the port introduces data or
   tables.

If the bytes differ, the port is not accepted yet, even if the shiftable
engine would tolerate non-matching C. The baseline SHA gate is the stricter
contract. Use `--disasm` to see whether the difference is a register choice, a
branch width, or a literal-pool ordering; that is the point where a
register/scheduling permutation loop (decomp-permuter) would normally help, but
it is not installed here, so iterate by hand and re-run the comparison.

A port that only needs to be *shiftable* (not part of the vanilla baseline) may
be accepted with a behavior scenario and a green `shift-check`, but it must not
be described as a baseline `MATCHED`/`C-FUNC` port until the SHA gate passes.

## 5. Worked dry-run (using the current baseline ELF)

All commands below use the baseline `mf_us.elf` as both sides; no candidate
build is needed. This is exactly the PASS/FAIL signal the loop uses.

Identical symbol — PASS (`exit 0`):

```console
$ python3 tools/decomp/compare_text.py \
    --baseline work/decomp/mf_us.elf --candidate work/decomp/mf_us.elf \
    --symbol RoomLoad --disasm
compare_text: RoomLoad
  baseline   work/decomp/mf_us.elf  RoomLoad @ 0x080645c4  size 0x124 (292) [nm]
  candidate  work/decomp/mf_us.elf  RoomLoad @ 0x080645c4  size 0x124 (292) [nm]
  status     PASS - 292 bytes identical
  disassembly diff (normalized):
    (no differences)
$ echo $?
0
```

A renamed/modified target — FAIL (`exit 1`). Comparing `RoomLoad` with another
symbol shows the size and byte reporting; a scratch copy with one byte flipped
inside `RoomLoad` shows the offset report and the disassembly diff:

```console
$ python3 tools/decomp/compare_text.py \
    --baseline work/decomp/mf_us.elf --candidate work/decomp/mf_us.elf \
    --baseline-symbol RoomLoad --candidate-symbol InGameHandler
compare_text: RoomLoad
  baseline   work/decomp/mf_us.elf  RoomLoad @ 0x080645c4  size 0x124 (292) [nm]
  candidate  work/decomp/mf_us.elf  InGameHandler @ 0x0800dd24  size 0x234 (564) [nm]
  size       MISMATCH - baseline 0x124 (292), candidate 0x234 (564)
  status     FAIL - first difference at +0x0 (baseline 0x00 vs candidate 0x10)
             545 of 564 compared bytes differ
$ echo $?
1
```

```console
$ cp work/decomp/mf_us.elf work/decomp/mf_us_roomload_patched.elf
$ python3 - <<'PY'
from pathlib import Path
p = Path("work/decomp/mf_us_roomload_patched.elf")
with p.open("r+b") as f:
    off = 0x94 + (0x080645C4 - 0x08000000) + 0x10   # rom section file offset + +0x10
    f.seek(off); b = f.read(1)[0]
    f.seek(off); f.write(bytes([b ^ 0x01]))
PY
$ python3 tools/decomp/compare_text.py \
    --baseline work/decomp/mf_us.elf \
    --candidate work/decomp/mf_us_roomload_patched.elf --symbol RoomLoad --disasm
compare_text: RoomLoad
  baseline   work/decomp/mf_us.elf  RoomLoad @ 0x080645c4  size 0x124 (292) [nm]
  candidate  work/decomp/mf_us_roomload_patched.elf  RoomLoad @ 0x080645c4  size 0x124 (292) [nm]
  status     FAIL - first difference at +0x10 (baseline 0x89 vs candidate 0x88)
             1 of 292 compared bytes differ
  disassembly diff (normalized):
    --- baseline:RoomLoad
    +++ candidate:RoomLoad
    @@ -3,5 +3,5 @@
     bl RoomReset
     bl RoomLoadEntry
    -bl RoomLoadTileset
    +bl RoomLoad+0x122
     bl RoomLoadScrollsAndEventBasedEffects
     bl RoomLoadBackgrounds
$ echo $?
1
```

`work/` is ignored, so this patched ELF is scratch-only and must never be
committed.

## 6. Cleanup

- Delete `/tmp/mf-cport` when the experiment ends; nothing under `/tmp` is
  tracked.
- Delete `work/decomp/` scratch ELFs when they are no longer useful.
- Commit only the real port (C source, removed asm, `linker.ld` line) with an
  explicit pathspec. Never commit scratch ELFs, ROMs, dumps, or tool trees.

## Tool limitations

- `compare_text.py` is a flat byte comparison of the symbol range. It does not
  relocate operands the way `objdiff` does; if the candidate build moves data,
  literal-pool words can differ even when the instruction sequence is the same.
  The normalized `--disasm` diff is the fallback for reading those differences.
- For asm symbols without `.size`, the inferred extent runs to the next global
  text symbol (the next `thumb_func_start`) and therefore **includes the
  literal pool** and alignment padding. Use `--size`/`--candidate-size` for a
  tighter range.
- `objdiff` and `decomp-permuter` are not installed in this environment. The
  objdump path documented above is the supported default; do not add those
  trees to the repository.
