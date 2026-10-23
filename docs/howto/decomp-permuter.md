# How to run decomp-permuter on one function

`decomp-permuter` is a search tool: given a C function and the **target
assembly** for it, it perturbs the C (variable reuse, statement order, expression
shape, casts, loop form, ...) and keeps whatever compiles to a lower diff score.
It is a *hint generator* for a human porting a function, not a decompiler and not
a gate.

This repository ships three wrappers:

| Script | Purpose |
|---|---|
| `tools/decomp/permuter/setup.sh` | one-time bootstrap: pinned clone, private venv with `toml`, toolchain check |
| `tools/decomp/permuter/run.sh` | build the permuter input dir for one function and run a bounded search |
| `tools/decomp/permuter/import_sram_recent.sh` | the TECH-007 worked example (`SramWrite_MostRecentSaveFile`) |

Nothing here runs in CI. `make permute` is a convenience alias, deliberately
outside `audit`/`smoke`/`test`.

## 1. Prerequisites

- **decomp-permuter pin**: `8556c81d80d1c1af98a858c8f4dc951357f29139`
  (`simonlindholm/decomp-permuter`, MIT). The clone lives in
  `work/tools/decomp-permuter`, which is git-ignored; **never commit it** and
  never copy its source into the tree.
- **Python >= 3.8** plus a venv at `work/tools/permuter-venv` with `toml`.
  The venv is private to `work/`; do not install into the system interpreter.
- **`git`**, **`cpp`** (host `gcc`), **`timeout`** (coreutils), and `curl` or
  `wget` for the first network-enabled setup.
- **ARM binutils**: `arm-none-eabi-as`, `arm-none-eabi-objdump`,
  `arm-none-eabi-nm` (plus `objcopy` for the import script). On this box they
  live in `$HOME/.local/bin`; the scripts add that directory to `PATH`
  themselves, but your shell will want the same line as in
  `docs/howto/c-port-scratch.md`:
  ```sh
  export PATH="$HOME/.local/bin:$PATH"
  ```
- **agbcc**, already built: `tools/agbcc/bin/agbcc`. If it is missing run
  `make setup-agbcc` (or `tools/setup_agbcc.sh`).

The first `setup.sh` run needs network access (clone, `pip install toml`, and
possibly `get-pip.py`). After that, `run.sh` is fully offline.

### venv bootstrap without `python3-venv`

On minimal Debian/Ubuntu images `python3 -m venv` creates the environment but
cannot install `pip` (`ensurepip` is missing). `setup.sh` detects that, falls
back to `--without-pip`, downloads `get-pip.py` from
<https://bootstrap.pypa.io/get-pip.py> into `work/tools/get-pip.py`, bootstraps
`pip` into the venv, and only then installs `toml`. The equivalent manual
sequence, if you ever need to redo it by hand:

```sh
python3 -m venv --without-pip work/tools/permuter-venv
curl -fsSL https://bootstrap.pypa.io/get-pip.py -o work/tools/get-pip.py
work/tools/permuter-venv/bin/python work/tools/get-pip.py
work/tools/permuter-venv/bin/python -m pip install toml
```

## 2. Setup

```sh
tools/decomp/permuter/setup.sh --check   # verify pin, venv, toml, toolchain
tools/decomp/permuter/setup.sh           # bootstrap what is missing
tools/decomp/permuter/setup.sh --force   # recreate the venv / re-fetch the pin
```

`--check` changes nothing and is the right command to run after a rebase or on
a new machine. It prints `OK: pin=...`, `OK: venv=...` on success.

## 3. Self-check

```sh
tools/decomp/permuter/run.sh --self-check
```

This builds a two-instruction fixture (`adds r0, r0, r1; bx lr`) through the
**exact** candidate pipeline the search uses and byte-compares the disassembly
of the result with the fixture target. It proves `cpp -> agbcc -> as ->
objdump` works without starting a search, and takes under a second. Run it
after touching `run.sh` or switching machines.

## 4. Run the pilot

`import_sram_recent.sh` reproduces the TECH-007 pilot end to end:

```sh
# base score only (fast, no search)
tools/decomp/permuter/import_sram_recent.sh --debug

# bounded search; the timeout is a hard wall-clock bound
tools/decomp/permuter/import_sram_recent.sh --timeout 900 --jobs 20
```

It extracts the function body (and its literal pool) from
`asm/disasm_0x0807e678_0807eea4_08080068.s`, symbolicates the
`0x03000B8D` literal to `gMostRecentSaveFile`, assembles the target `.o`, and
hands the hand-tightened seed in `tools/decomp/permuter/seeds/` to `run.sh`.
When `mf_us.gba` is present it also checks the extraction against the baseline:
the raw body is assembled separately (`*.target.raw.o`) and every byte must
match the ROM except the 4-byte words that still carry relocations
(`unk_dd4`, `sUnk_582280`). A corrupted ROM copy makes the script fail rather
than score against the wrong target. Everything it writes stays under `work/`:

| Path | Contents |
|---|---|
| `work/decompme/SramWrite_MostRecentSaveFile.target.s` / `.o` | standalone target (symbolicated) |
| `work/decompme/SramWrite_MostRecentSaveFile.target.raw.s` / `.o` | raw extraction, used for the ROM byte check |
| `work/decompme/SramWrite_MostRecentSaveFile.seed435.c` | seed copy |
| `work/decompme/pilot*.log` | console transcript, when you redirect stdout there |
| `work/permuter/SramWrite_MostRecentSaveFile/` | input dir, `base.c`, `compile.sh`, `settings.toml`, `permuter.log`, `output-*/` candidates |

`run.sh` tees the search to `work/permuter/<name>/permuter.log` and reports the
lowest `score.txt` found under `output-*/`. A timeout exits `124` internally and
is reported as "bounded search stopped", not as a failure.

### Using another function

```sh
tools/decomp/permuter/run.sh \
  --seed work/myseed/Foo.c \
  --target work/mytarget/Foo.o \
  --name Foo \
  --timeout 900
```

Swap-in checklist:

1. **Seed**: exactly one function, named `Foo`, that already compiles and is
   *semantically correct*; the permuter only changes codegen shape. Preprocess
   it like the ROM does (`globals.h` + the real headers); `run.sh` runs
   `cpp -P -nostdinc -Iinclude -DREGION_US` for you, so `#include "globals.h"`
   is the right entry point.
2. **Target**: cut the function from the split `.s` **including its literal
   pool** (up to the next `thumb_func_start`), or use an existing `.o` that
   defines the same symbol. `run.sh` accepts `.s` or `.o` and verifies the
   symbol exists with `arm-none-eabi-nm`.
3. **Relocations**: any absolute address in the literal pool must be
   symbolic. A raw `0x03000B8D` forces the candidate to emit a plain constant
   and inflates the score (the pilot reads 475 instead of the true 435);
   `import_sram_recent.sh` shows how to symbolicate one word.
4. **Flags**: `run.sh` hardcodes the ROM build recipe
   (`agbcc -O1 -mthumb-interwork -fhex-asm`, `.align 2, 0`, `as -mcpu=arm7tdmi`).
   If a function only matches at `-O2` (see `src/sram/sram_world_read.s`) this
   adapter cannot help; that is a documented limitation, not a bug.
5. `--name` must be a C identifier and must match the target symbol.

### Inspecting a candidate

The search writes `output-<score>-<n>/` directories, each with `score.txt`,
`diff.txt` and `source.c`. Those sources are **preprocessed** (headers inlined,
`#define`s expanded), so diff them against the input dir's `base.c`, never
against the hand-written seed:

```sh
diff -u work/permuter/SramWrite_MostRecentSaveFile/base.c \
        work/permuter/SramWrite_MostRecentSaveFile/output-<score>-1/source.c
```

Expect formatting noise and scorer artifacts: a duplicated store, an inserted
`if (1) { }`, or a shared temporary. Some of those are harmless at runtime
(the best candidate writes `*(u16*)(header + 2) = 0;` twice, which is legal
and saves a register) but none of them should be copied into `src/` verbatim. Read
the C shape the candidate implies and apply it to the real seed by hand.

## 5. Reading the score

The score is the sum of penalties from decomp-permuter's diff of the two
`objdump` outputs (`ins`/`reg` weights from the upstream
`default_weights.toml`):

- **`score = 0`** — the candidate compiles to the same instruction/register
  stream as the target. Still verify bytes (section 6); the scorer normalizes
  registers and ignores some non-code differences.
- **`base score = N`** — the seed's distance. `--debug` prints the penalty list
  (which instructions/registers differ), which is the actual work order: fix
  the top penalty by hand, re-run, repeat. A search that only shaves tens of
  points rarely closes; the interesting signal is a jump to single digits.
- Scores are **not comparable across functions**; they are only a local
  gradient.

The pilot's reference numbers: base **435**, decomposed by `--debug` as
7 register differences (35), 2 insertions (200) and 2 deletions (200):

```
Register Differences:          7  (5)
Insertions:                    2  (100)
Deletions:                     2  (100)
```

All of it is agbcc register allocation around the `u16` checksum loop and the
trailing `0xFFFF - checksum` write (the seed keeps a `u16* ptr` local, so agbcc
materializes an extra `movs r1, #0` / `adds r0, r1, #0` pair). The search can
shave that shape but cannot re-derive the exact original C, so a non-zero
residual is a normal outcome. Results vary a little with the seed and the
search's random state.

### Measured pilot (2026-10-23, US baseline)

| Run | Wall clock | Best score |
|---|---:|---:|
| seed (`--debug`) | — | 435 |
| bounded search, 20 jobs | 900 s | **200** |
| bounded search, 20 jobs | 120 s | 205 |
| bounded search, 20 jobs | 60 s | 230 |

No run produced a `score = 0` candidate, so nothing was proposed for `src/`.
The best candidate keeps the same structure and only rewrites the zero/`0xFFFF`
stores and the checksum loop's register assignment; the residual is agbcc's
loop register allocation, which the search cannot express differently without
inventing code. The best source is preserved at
`work/decompme/SramWrite_MostRecentSaveFile.best200.c` (preprocessed — diff it
against the input dir's `base.c`).

Pilot caveat: the 900 s run must not overlap a ROM build. When it does, most of
the wall clock goes to CPU starvation (2.1k iterations in 900 s vs 447k alone),
and the best score is correspondingly worse (230).

## 6. Limitations

- **Search is regalloc/codegen-only.** It reorders and rewrites existing C; it
  cannot invent a missing branch, a different type, or a different loop bound.
  A wrong seed stays wrong; the score may even drop.
- **Not a gate.** A score-0 candidate is evidence, not acceptance. The gates
  are `tools/decomp/compare_text.py` on a scratch ELF and the whole-ROM SHA
  `ca33f4348c2c05dd330d37b97e2c5a69531dfe87`. `make permute`/`run.sh` never
  run in CI.
- **`thumb_func_start` has no `.size`.** Split-asm symbols report size 0, so
  the function extent must be cut by hand. Include the literal pool, and stop
  at the next `thumb_func_start`. `import_sram_recent.sh` asserts the exact
  `0x8c` byte length; `compare_text.py` falls back to `next-global` when `nm`
  reports zero.
- **One function at a time.** The input dir contains a single function; the
  `base.c` is preprocessed, so `#define`s are already expanded (edit the seed,
  not `base.c`, and re-run).
- **Needs a correct, compiling seed.** If the seed does not compile the search
  produces nothing useful.
- **Verify through a scratch build.** Copy the candidate into a throwaway tree
  (`docs/howto/c-port-scratch.md`), build, then:
  ```sh
  python3 tools/decomp/compare_text.py \
      --baseline mf_us.elf --candidate /tmp/mf-cport/mf_us.elf \
      --symbol <Function> --disasm
  ```
  Exit `0` means identical bytes for that symbol. Never copy a permuter
  candidate straight into `src/`.

## 7. Attribution and licensing

decomp-permuter is MIT-licensed, © 2019 Simon Lindholm and contributors; the
license text is in `work/tools/decomp-permuter/LICENSE` after setup. This
repository does **not** vendor it: `setup.sh` clones the pinned commit into the
ignored `work/` tree, so no third-party source, binaries, or ROM-derived data
are committed. If you redistribute a candidate, attribute the tool and keep its
MIT notice with any copy of its source you pass on.
