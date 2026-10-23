# How to use objdiff-cli (fuzzy instruction diff)

`objdiff` is a third-party instruction diff for Game Boy Advance decompilation.
It pairs the instructions of a **target** object (the split disassembly) with a
**base** object (our C candidate) and reports a fuzzy match percentage plus one
row per differing instruction. This document covers the thin adapter in
`tools/decomp/objdiff/`, the pinned binary, the object recipes used by this
repository, and the pilot result that the adapter is calibrated against.

`objdiff` is a *diagnostic*. It answers "what does my C compile to, and how far
is it from the original instruction stream?" It is **not** an acceptance gate.
Byte acceptance stays with `tools/decomp/compare_text.py` and the whole-ROM
SHA1 (`ca33f4348c2c05dd330d37b97e2c5a69531dfe87`).

## 1. Pinned tool

| Field | Value |
|---|---|
| Upstream | [`encounter/objdiff`](https://github.com/encounter/objdiff) |
| Version | `v3.8.3` (release 2026-10-19) |
| Linux x86_64 asset | `objdiff-cli-linux-x86_64` |
| SHA-256 | `e823ae932a56c68dcd86b68d12f2268c953e0c027402162c8a6dfa6a00d65008` |
| Linux aarch64 asset | `objdiff-cli-linux-aarch64` |
| SHA-256 | `0e630457e2f33a43da3723e195ecd0b39b683a6a83122955fdc68c5b17183cbc` |
| Install path | `work/tools/objdiff/objdiff-cli` (ignored) |
| License | Apache-2.0 |

Only those two Linux assets are pinned. Any other OS/arch fails loudly; there is
no fallback to an unpinned version. The binary and its source are **never**
committed — `work/` is git-ignored.

```sh
tools/decomp/objdiff/setup.sh           # download if missing or wrong version
tools/decomp/objdiff/setup.sh --check   # verify only, never downloads
tools/decomp/objdiff/setup.sh --force   # re-download the pinned asset
```

`--check` is the cheap gate for scripts and CI-like runs:

```console
$ tools/decomp/objdiff/setup.sh --check
objdiff-cli 3.8.3 OK (/path/to/work/tools/objdiff/objdiff-cli)
$ echo $?
0
```

Exit status is `0` verified, `1` missing/wrong version, `2` setup or network
error. `setup.sh` verifies both `objdiff-cli --version` (must be exactly
`objdiff-cli 3.8.3`) and the SHA-256 of the downloaded asset, so a proxy that
serves a captive-portal page fails instead of installing garbage. It needs
`curl` or `wget` plus `sha256sum`/`shasum`; a missing network is an error, not a
silent skip.

## 2. `diff.sh` — one function, one report

```sh
tools/decomp/objdiff/diff.sh --target target.o --base base.o \
    [--symbol NAME] [--json]
```

It invokes the pinned CLI exactly as

```sh
work/tools/objdiff/objdiff-cli diff -1 target.o -2 base.o -o - --format json [NAME]
```

and pipes the one-shot JSON through `tools/decomp/objdiff/summary.py`. `left`
is always the `-1` **target** (original disassembly), `right` is always the
`-2` **base** (C candidate). `--json` appends the raw, single-line JSON payload
after the human report (useful when filing an issue or writing a fixture).

| Exit | Meaning |
|---:|---|
| `0` | every compared function scored 100 % (objdiff fuzzy score) |
| `1` | at least one function differs, or exists on only one side |
| `2` | usage error, missing/wrong `objdiff-cli`, unreadable object, bad JSON, or `--symbol` not present |

`--self-check` assembles a two-instruction synthetic object pair with
`arm-none-eabi-as`, runs an identical pair (expects exit 0 / "100 %") and an
argument-mismatch pair (expects exit 1 / an `[arg]` row), and prints
`diff.sh self-check: PASS`. It needs neither a baserom, a seed nor agbcc, so it
is safe to run in any worktree:

```sh
tools/decomp/objdiff/diff.sh --self-check
python3 tools/decomp/objdiff/summary.py --self-check   # 12/12 JSON checks
```

`diff.sh` finds `arm-none-eabi-as` on `PATH`, then at `~/.local/bin` — the same
order as `compare_text.py`.

## 3. Building the two objects

objdiff only reads ELF objects, so both sides must be compiled/assembled first.
Do this in the ignored `work/` tree (or `/tmp`); nothing here belongs in Git.

### Target: the split disassembly

Each split `.s` file contains several functions; objdiff filters by symbol name,
so the whole object is a valid target.

```sh
arm-none-eabi-as -mcpu=arm7tdmi -I. \
    asm/disasm_0x0807e678_0807eea4_08080068.s \
    -o work/tools/objdiff/pilot/target.o
```

`-I.` matters: the split files use `.include` for shared macros/constants.

### Base: the C candidate through the project toolchain

The exact recipe used by this repository (and by `pilot_sram_recent.sh`) is
`cpp → agbcc → text `.s` → arm-none-eabi-as`, mirroring the `Makefile` rules:

```sh
# 1. Preprocess with the project headers only.
cpp -nostdinc -Iinclude -DREGION_US candidate.c > base.i

# 2. Compile with the pinned agbcc (tools/agbcc; run `make setup-agbcc` once).
tools/agbcc/bin/agbcc -O1 -mthumb-interwork -fhex-asm -o base.s base.i

# 3. agbcc ends `.text` without trailing alignment; add the project's rule so
#    the function body lands at an even offset and objdiff does not see a
#    phantom 2-byte shift.
printf '\t.align 2, 0\n' >> base.s

# 4. Assemble the same way as the target.
arm-none-eabi-as -mcpu=arm7tdmi -I. base.s -o base.o
```

`-O1` is the project baseline. `-fhex-asm` makes agbcc emit hexadecimal
immediates, which keeps the textual form stable for diffs. `-DREGION_US` selects
the US layout used by `mf_us`. If you compare code that includes headers
outside `include/`, add the matching `-I` to `cpp` (keep `-nostdinc`, or host
glibc headers will leak in).

Prefer keeping candidates in `work/decompme/` or a scratch tree so no `src/`
file changes just to run a diff.

## 4. `pilot_sram_recent.sh` — end-to-end worked example

The pilot builds both objects for `SramWrite_MostRecentSaveFile` and prints the
report. It is the calibration fixture for the adapter:

```sh
make setup-agbcc                       # once, if tools/agbcc is missing
tools/decomp/objdiff/pilot_sram_recent.sh
tools/decomp/objdiff/pilot_sram_recent.sh --compare-text
tools/decomp/objdiff/pilot_sram_recent.sh --from-c /tmp/cand.c --json
tools/decomp/objdiff/pilot_sram_recent.sh --out work/tools/objdiff/my-run
```

- default candidate: `work/decompme/SramWrite_MostRecentSaveFile.seed.c`
  (ignored scratch; never a `src/` file);
- `--from-c FILE` diffs any candidate without editing `src/`;
- `--compare-text` runs `tools/decomp/compare_text.py` on the same pair;
- `--json` forwards the raw JSON from `diff.sh`;
- `--out DIR` changes the object directory (default
  `work/tools/objdiff/pilot`).

Exit status is inherited from `diff.sh`: `0` = 100 %, `1` = differs (the
expected pilot result), `2` = tool/input/setup error. `--compare-text` does not
change the exit status; its own code is printed as `compare_text exit N`.

### Expected pilot output (pinned tools, 2026-10-23)

```console
$ tools/decomp/objdiff/pilot_sram_recent.sh --compare-text
objdiff pilot: SramWrite_MostRecentSaveFile
  target  asm/disasm_0x0807e678_0807eea4_08080068.s
  base    work/decompme/SramWrite_MostRecentSaveFile.seed.c
  objects <root>/work/tools/objdiff/pilot
objdiff-cli 3.8.3
target: <root>/work/tools/objdiff/pilot/target.o
base:   <root>/work/tools/objdiff/pilot/base.o
symbols: 1 compared, 1 differing
  SramWrite_MostRecentSaveFile  match 90.71%  (target 138 B, base 136 B)
    15 differing instruction(s), target | base:
             push {r4, r5, lr}                            |        push {r4, r5, r6, lr}                        [replace]
      +0x002 ldr r5, [pc, #0x78] (->0x7c)                 | +0x002 ldr r5, [pc, #0x74] (->0x78)                 [arg]
             (none)                                       | +0x008 ldr r6, [pc, #0x70] (->0x7c)                 [insert]
      +0x014 ldr r0, [pc, #0x68] (->0x80)                 |        (none)                                       [delete]
      ...
      +0x04e ldrh r2, [r3, #0x0]                          | +0x04e ldrh r1, [r3, #0x0]                          [arg]
      +0x050 add r0, r2                                   | +0x050 add r0, r1                                   [arg]
      +0x06a ldr r2, [pc, #0x14] (->0x80)                 |        (none)                                       [delete]
      +0x06c mov r0, r2                                   |        (none)                                       [delete]
      +0x06e sub r0, r1                                   | +0x06a sub r0, r6, r1                               [replace]
      +0x076 pop {r4, r5}                                 | +0x072 pop {r4, r5, r6}                             [replace]
      +0x084 .word 0x3000b8d                              | +0x080 .word gMostRecentSaveFile                    [arg]
      +0x088 .hword sUnk_582280+0x8                       | +0x084 .word sUnk_582280+0x8                        [op]

--- byte comparison (tools/decomp/compare_text.py) ---
compare_text: SramWrite_MostRecentSaveFile
  baseline   .../base.o    SramWrite_MostRecentSaveFile @ 0x00000000  size 0x88 (136) [nm]
  candidate  .../target.o  SramWrite_MostRecentSaveFile @ 0x00000000  size 0x8c (140) [next-global]
  size       MISMATCH - baseline 0x88 (136), candidate 0x8c (140)
  status     FAIL - first difference at +0x0 (baseline 0x70 vs candidate 0x30)
             52 of 140 compared bytes differ
compare_text exit 1 (0 = byte-identical, 1 = differs)
```

(`...` abbreviates the low-order rows and absolute paths; the real report prints
all 15 rows. `pilot` exits `1`.)

What the pilot demonstrates:

- **90.71 % is not byte equality.** The candidate is close but still differs in
  15 instructions: the prologue saves `r6`, the checksum byte is read into
  `r2` instead of `r1`, the epilogue is `ldr r2; mov r0, r2; sub` instead of
  `sub r0, r6, r1`, and several literal-pool references/word kinds differ.
- **`compare_text.py` says FAIL on the same pair**: 52 of 140 bytes differ and
  the extents disagree (`0x88` vs `0x8c`), so 90.71 % must never be reported as
  a match.
- The 4-byte size difference is partly an extent artefact: the base object has
  an `nm` size (`0x88`) while the target object has no `.size` for this symbol,
  so `compare_text` falls back to `next-global` (`0x8c`, including the literal
  pool and padding).

`pilot_sram_recent.sh` reads the split `.s` from `asm/` but writes only to
`work/`. It never edits `src/`, `asm/`, `include/` or `linker.ld`.

## 5. Reading the one-shot JSON

`--format json` emits a single line:

```json
{
  "left":  {"sections": [...], "symbols": [...]},
  "right": {"sections": [...], "symbols": [...]}
}
```

- Top level: `left` = target (`-1`), `right` = base (`-2`).
- Each side has `sections` and `symbols`. Section entries carry `name`, `kind`
  (`SECTION_CODE`, `SECTION_DATA`, `SECTION_BSS`), `size` and `match_percent`.
- Symbol entries carry `name`, `size` (string, may be absent), `flags`
  (`global`, `local`, `hidden`, `size_inferred`, …), `kind`
  (`SYMBOL_FUNCTION`, `SYMBOL_SECTION`, or absent), `target_symbol` (index into
  the target symbol table when paired), `match_percent`, and `instructions`.
- `match_percent` is present only on the **scored** symbol. Other paired symbols
  in the table are annotation; do not average or quote their absence as 0 %.
- Instruction rows are aligned between the two sides and look like:

  ```json
  {"diff_kind": "DIFF_REPLACE",
   "instruction": {"size": 2, "formatted": "push {r4, r5, lr}", "parts": [...]}}
  ```

  `diff_kind` is omitted (or `DIFF_NONE`) for matching rows. The kinds are
  `DIFF_REPLACE`, `DIFF_INSERT`, `DIFF_DELETE`, `DIFF_ARG_MISMATCH`,
  `DIFF_OP_MISMATCH` and `DIFF_TYPE_CHANGED`; `summary.py` labels them
  `replace`, `insert`, `delete`, `arg`, `op`, `type`. `parts` exposes mnemonics
  and opaque arguments for tooling, but the adapter only prints `formatted` and
  `size`.

In the pilot, the target has 66 instruction rows (functions plus their literal
pools) and the scored symbol carries `match_percent: 90.707695`.

### What "90.71 %" means

objdiff's score is a fuzzy operation/argument match over the aligned
instruction stream (its own diff algorithm). It rewards matching mnemonics and
operands, tolerates insertions/deletions, and **ignores byte encoding
differences and relocation values**. It is useful for ranking how close two
compilations are and for spotting a register or scheduling mistake. It is not a
byte comparison:

- a 100 % score means "no operation/argument row differs", not "same bytes"
  (encodings, literal values, relocation addends and padding can still differ);
- a 90.71 % score says "most rows match", and 15 rows still differ;
- byte equality is decided only by `compare_text.py` (per symbol) and the ROM
  SHA (whole image).

## 6. Symbols without `.size`, and unknown symbols

Split files use `thumb_func_start`, which emits `.thumb_func` but **no
`.size`. `nm` therefore reports size 0 for those functions. objdiff infers the
extent instead: the symbol runs to the end of its section, so the reported size
**includes the literal pool and trailing alignment**. The `flags.size_inferred`
bit in the JSON says so. This is why the pilot target is 138 B while the C
object's `nm` size is 136 B.

Practical consequences:

- expect a small size delta between target and base even when the code is right;
- literal-pool words appear as instruction rows (`.word`, `.hword`) and can
  produce `[arg]`/`[op]` rows after the last real instruction;
- `compare_text.py` handles this with `--size`/`--candidate-size` when a
  tighter range is needed;
- an unknown `--symbol` does **not** fail in `objdiff-cli`: it exits 0 and dumps
  the whole symbol table. Always let `summary.py` validate it — it exits `2`
  with "symbol ... is not present in the diff". `diff.sh` does this for you, so
  a typo is an error, not a silent 100 %.

## 7. Limitations and rules

- **Never a gate.** `make -f Makefile.shift audit`, `smoke`, `test`,
  `compare_text.py` and the whole-ROM SHA remain the acceptance criteria.
  Nothing in the build calls objdiff.
- `compare_text.py` acts on **relocatable objects** too, so cross-references
  show as raw bytes/relocations there; objdiff is the better tool for reading
  instruction-level differences before a full link.
- objdiff does not evaluate semantics. A 100 % function can still be wrong in C
  (undefined behaviour, wrong types) and a 90 % function can already be
  behaviorally correct. The behavior suite is what decides correctness.
- `work/` (including `work/tools/objdiff/` and `work/decompme/`) is ignored.
  Never commit the binary, objects, JSON dumps, seeds or ROMs. Commit only
  scripts/docs with an explicit pathspec.
- The adapter is a thin wrapper: `setup.sh`, `diff.sh`, `summary.py`,
  `pilot_sram_recent.sh`. There is no vendored objdiff source and no
  `make objdiff` target; call the scripts directly.
- Version drift is a bug: `diff.sh` refuses anything that does not report
  `objdiff-cli 3.8.3`.

## 8. Attribution

`objdiff` is developed by the [encounter/objdiff](https://github.com/encounter/objdiff)
project and is licensed under the **Apache License, Version 2.0**. This
repository does not redistribute the binary or its source: `setup.sh`
downloads the pinned release asset into the ignored `work/tools/objdiff/` and
verifies its SHA-256. Copyright remains with the upstream contributors.

See also `docs/howto/c-port-scratch.md` for the full port loop
(`compare_text.py`, scratch tree, baseline SHA) that this diagnostic plugs into.
