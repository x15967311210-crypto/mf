# How to run m2c on one function

`m2c` (Machine Code to C) is a *decompiler*: it takes the assembly of a single
function and prints C that **describes** what the machine code does. That C is a
reading aid for a human porting the function — it is not the original source, it
does not necessarily compile, and it never matches the ROM. The tool is used
here as a draft generator, alongside the permuter
(`docs/howto/decomp-permuter.md`), which goes the other way: it searches for C
that *does* compile to the target bytes.

This repository ships three wrappers plus fixtures:

| Path | Purpose |
|---|---|
| `tools/decomp/m2c/setup.sh` | one-time bootstrap: pinned clone, private venv, `graphviz`/CLI check |
| `tools/decomp/m2c/run.sh` | extract one function from split asm and decompile it |
| `tools/decomp/m2c/extract.py` | standalone extractor: cut one function and symbolicate its literal pool |
| `tools/decomp/m2c/context/sram_write_recent.c` | the pilot's C context (types, globals, callee) |
| `tools/decomp/m2c/symbols/sram.syms` | the pilot's literal-pool rewrites |
| `tools/decomp/m2c/fixtures/mini.s` | synthetic split-disasm fixture for both self-checks |

Nothing here runs in CI. `make m2c` is a convenience alias, deliberately outside
`all`/`audit`/`smoke`/`test`. The wrappers change no tracked file: the extracted
asm and the C output both land under the git-ignored `work/` tree.

## 1. Prerequisites

- **m2c pin**: `c632946b8cfbe8fce442b522dba92dfa72f1f317`
  (`matt-kempster/m2c`, 2026-10-22, "Don't crash decompiling functions declared
  as data"). The clone lives in `work/tools/m2c`, which is git-ignored.
  **Never commit it** and never copy its source into the tree: m2c is
  **GPL-3.0-only**, this repository is not, and vendoring it would relicense the
  whole tree. See section 10.
- **Python >= 3.8** plus a private venv at `work/tools/m2c-venv`. The only
  runtime dependency is `graphviz ~= 0.20.1`; do not install into the system
  interpreter.
- **`git`** (clone/fetch of the pin) and **`cpp`** from the host `gcc`
  (`--context` files are preprocessed here, because m2c requires an
  already-preprocessed context).
- **`curl` or `wget`** for the first network-enabled setup, if `pip` has to be
  bootstrapped.
- **Network** for the first `setup.sh` (clone, `pip install -e .`). After that,
  `run.sh` is fully offline.

No ARM toolchain is needed: unlike the permuter, m2c only reads an `.s` file, it
never assembles or compiles anything.

### venv bootstrap without `python3-venv`

On minimal Debian/Ubuntu images `python3 -m venv` creates the environment but
cannot install `pip` (`ensurepip` is missing). `setup.sh` detects that, falls
back to `--without-pip`, downloads `get-pip.py` from
<https://bootstrap.pypa.io/get-pip.py> into `work/tools/get-pip.py`, bootstraps
`pip` into the venv, and only then installs the pinned m2c. The equivalent
manual sequence, if you ever need to redo it by hand:

```sh
python3 -m venv --without-pip work/tools/m2c-venv
curl -fsSL https://bootstrap.pypa.io/get-pip.py -o work/tools/get-pip.py
work/tools/m2c-venv/bin/python work/tools/get-pip.py
work/tools/m2c-venv/bin/python -m pip install -e work/tools/m2c
```

## 2. Setup

```sh
tools/decomp/m2c/setup.sh --check   # verify pin, venv, graphviz, m2c CLI
tools/decomp/m2c/setup.sh           # bootstrap what is missing
tools/decomp/m2c/setup.sh --force   # recreate the venv / re-checkout the pin
```

`--check` changes nothing and is the right command after a rebase or on a new
machine. It prints `OK: pin=...` and `OK: venv=...` on success, and fails loudly
if the checkout is at the wrong commit (never silently reuse a drifted clone).

## 3. Self-check

```sh
tools/decomp/m2c/extract.py --self-check   # extractor only, 21 assertions
tools/decomp/m2c/run.sh --self-check       # extractor + one real m2c run
```

`extract.py --self-check` runs the boundary, thumb/arm and literal-rewrite
assertions against `fixtures/mini.s` (21 checks, no files written).
`run.sh --self-check` then extracts that fixture through the *same* code path
used for real functions, asserts that the literal was symbolicated and the
`thumb_func_start` macro became a plain `@ 0x...` label, decompiles it twice
with `m2c -t gba --no-cache`, and requires the two outputs to be byte-identical
(the adapter must be deterministic). It takes under a second and needs no
network. Run it after touching `run.sh`, `extract.py` or switching machines.

## 4. Extraction

Split disassembly in `asm/` has no `.size` directive: a function is introduced
by a `thumb_func_start NAME` / `arm_func_start NAME` macro and ends where the
next function starts. `extract.py` turns that slice into a standalone file:

- `thumb_func_start NAME` becomes `.global NAME`; the label line (with its
  `@ 0x...` comment) is kept and the right `.arm`/`.thumb` directive is emitted
  together with `.syntax unified` / `.text`;
- the function body runs to the next `*_func_start` or the next column-0
  `Name: @ 0x...` label, so its **literal pool is included** (m2c needs the
  `ldr` targets);
- `--symbol`/`--symbols` rewrites literal-pool data directives only:
  `.4byte 0x0203F000` → `.4byte gSramMostRecent`. Instruction operands and the
  `@ =0x...` comments are left alone; the raw address would otherwise become a
  constant m2c cannot type.

The mapping-file format (`symbols/sram.syms`) is one `LITERAL NAME` pair per
line, `#` starts a comment. `LITERAL` must match the `.4byte`/`.word` operand
exactly as written in the split disassembly, including an offset expression such
as `sUnk_582280+0x8`. Later mappings win, so a command-line `--symbol` overrides
a file entry.

```sh
tools/decomp/m2c/extract.py \
    --asm asm/disasm_0x0807e678_0807eea4_08080068.s \
    --function SramWrite_MostRecentSaveFile \
    --symbols tools/decomp/m2c/symbols/sram.syms \
    --out work/decompme/SramWrite_MostRecentSaveFile.s --json
```

The `--json` summary (function, line range, mode, symbol count) is what
`run.sh` prints when it extracts. The extractor is deliberately dumb: it does
not follow branch targets, decode data blobs, or guess symbols. If a function is
split across files or its pool holds addresses you have not named, fix the input
by hand.

## 5. Context files

m2c infers types from the code; a **context** file teaches it names. The pilot's
`context/sram_write_recent.c` declares:

- the `struct SramSave` layout (field offsets read off the store instructions),
  so m2c prints `gSramMostRecent.counter` instead of `*(u8*)(r5 + 1)`;
- the globals behind the rewritten literals (`gSramMostRecent`,
  `gMostRecentSaveFile`, `sBlob_582288`);
- the one callee this function calls, so it is not printed with an unknown
  signature;
- `s64`/`u64`, because m2c emits 64-bit casts for widening arithmetic and
  `include/types.h` stops at 32 bits.

Keep a context file small and function-local. It is **not** a project-wide
header: pulling in the whole game would make m2c's parse slow and its guesses
worse, and a full context is a separate task. `run.sh` preprocesses the file
with `cpp -nostdinc -I include` and writes the result to
`work/decompme/<name>.ctx.c`; m2c requires that preprocessed form, so never
point `--context` at a file with `#include`s.

## 6. Decompile one function

```sh
tools/decomp/m2c/run.sh \
    --asm asm/disasm_0x0807e678_0807eea4_08080068.s \
    --function SramWrite_MostRecentSaveFile \
    --context tools/decomp/m2c/context/sram_write_recent.c \
    --symbols tools/decomp/m2c/symbols/sram.syms \
    --out work/decompme/SramWrite_MostRecentSaveFile.m2c.c
```

| Option | Meaning |
|---|---|
| `--asm FILE` | split disassembly file to read (required) |
| `--function NAME` | symbol to extract (required) |
| `--context FILE` | C context, preprocessed here with `cpp -nostdinc -Iinclude` |
| `--symbols FILE` | literal mapping file (repeatable) |
| `--symbol LITERAL=NAME` | one extra rewrite (repeatable) |
| `--target TRIPLE` | m2c target (default `gba`) |
| `--gotos-only` | keep gotos instead of structured control flow |
| `--valid-syntax` | emit `M2C_*` macros so the output always parses |
| `--out FILE` | C output (default `work/decompme/NAME.m2c.c`; `-` is stdout) |
| `--extracted FILE` | standalone asm path (default `work/decompme/NAME.s`) |
| `--self-check` | run the fixture checks and exit |

`--target gba` is m2c's ARM little-endian platform with the GCC dialect and C
language, which is the closest match to agbcc/ARMv4T. It is still a *generic*
ARM model: agbcc's register allocation and its stack-slot reuse are not
modelled, which is exactly where the output gets ugly (section 8).

## 7. The `make m2c` pilot

```sh
make m2c
```

runs `setup.sh --check`, `run.sh --self-check`, then the one pilot command from
section 6 and exits. There is no search and no timeout: extraction plus one m2c
run took **~1.6 s** on the reference box, and the output is 37 lines. The target
is listed in `make help` under "Manual decomp tooling" and is in
`RULES_NO_SCAN`, so it never triggers the tool bootstrap.

Everything it writes stays under `work/decompme/`:

| Path | Contents |
|---|---|
| `work/decompme/SramWrite_MostRecentSaveFile.s` | extracted, symbolicated asm (0x8c = 140 bytes, code + literal pool) |
| `work/decompme/sram_write_recent.ctx.c` | preprocessed context handed to m2c |
| `work/decompme/SramWrite_MostRecentSaveFile.m2c.c` | the decompiled draft |

`make m2c` is idempotent: it overwrites those three files and nothing else. It
never touches `src/`, `asm/`, the ROM or the object tree, so it cannot change a
build artifact.

## 8. Reading the pilot output

The draft gets a lot right for free: the save-buffer pointer is named
(`gSramMostRecent`), so the magic byte, the incrementing counter, the zeroed
checksum pair and the file index are printed as struct field assignments; the
first `0xF`-iteration copy loop comes out as a real `do { } while` loop over
`u8*` pointers; the trailing call to `unk_dd4` is recognised as a call. That is
useful as a skeleton for a hand-written C port.

The weakness is the **second checksum loop**, which m2c cannot type. Its output
collapses the halfword walk into pointer arithmetic on a struct pointer:

```c
    var_r4_2 = 7;
    do {
        temp_r3 = &var_r3->checksum + 2;
        var_r1_2 = (u16) ((u16) ((u16) (var_r1_2 + var_r3->unk0) + var_r3->checksum)
                    + var_r3->checksumComplement) + temp_r3->unk2;
        var_r3 = (struct SramSave *) (temp_r3 + 2 + 2);
        var_r4_2 -= 1;
    } while (var_r4_2 >= 0);
```

Three things are wrong there, and they are all m2c heuristics, not wrapper bugs:

- the struct-relative `->unk0` / `->checksum` / `->checksumComplement` /
  `->unk2` reads are four independent fields of one `SramSave`, while the target
  walks a flat `u16` stream (the context's field layout made m2c prefer the
  struct interpretation);
- `&var_r3->checksum + 2` and `(temp_r3 + 2 + 2)` are byte/word arithmetic
  mixed through a typed pointer, which silently changes the stride;
- the loop variable is a pointer, not an index, so `var_r4_2`'s bound and the
  state update no longer read like the assembly.

Read the draft for *structure* (what is stored where, which loop runs how many
times, what is called), then write the C by hand against the disassembly, and
verify with `compare_text.py` (see `docs/howto/c-port-scratch.md`). Do not paste
m2c output into `src/`: it has no types for the locals (`s32 var_r4`,
`u8 *var_r1`), no `#include`s, and as printed it does not compile.

### Tuning the draft

- **Name more addresses** in the symbols file; an unnamed literal becomes a raw
  constant and every access to it is printed as arithmetic.
- **Type the data** in the context: a `u16 *` global plus a typed array usually
  reads better than a struct whose fields happen to line up. If a struct view
  produces field soup like the loop above, try the flat pointer type instead.
- **`--gotos-only`** produces an uglier but more literally faithful draft when
  m2c's control-flow structuring invents loops or early returns.
- **`--valid-syntax`** wraps unknown constructs in `M2C_*` macros so the output
  parses under a C compiler; useful for diffing two drafts, not for porting.
- Output is not formatted with the repo style and locals are generated names
  (`var_rN`); `make format` never sees it because it lives in `work/`.

## 9. Limitations

- **Draft only.** m2c is not a matching decompiler and there is no score to
  optimise. A clean-looking draft can still be wrong; only a byte comparison
  against `mf_us.elf` (`tools/decomp/compare_text.py`) proves a port.
- **One function at a time, cut by hand.** The extractor stops at the next
  function label; jump tables, shared tails, `.incbin` data and functions split
  across disassembly files need manual input.
- **Generic ARM model.** agbcc-specific codegen (stack-slot reuse, `-O1` vs
  `-O2` differences, register allocation around halfword loops) is not modelled;
  the checksum loop above is the visible symptom.
- **Context quality is the ceiling.** Wrong struct layout or a missing global
  produces confidently wrong C. Keep the context minimal and checked against the
  instruction offsets.
- **No 64-bit types in the project headers.** Any context must supply
  `s64`/`u64` itself (the pilot does).
- **Not a gate, ever.** `make m2c` is not in `all`, `audit`, `smoke`, `test` or
  CI, and must not be added to them: it needs network on the first run and a
  third-party GPL checkout. The gates remain the whole-ROM SHA
  `ca33f4348c2c05dd330d37b97e2c5a69531dfe87` (plus the padded/reordered shift
  builds) and the per-function `compare_text.py` check.
- **Nothing to review in Git.** The wrappers, context, symbols and fixture are
  tracked; the clone, venv, extracted asm and C drafts are not. A reviewer only
  sees the recipe, never a ROM-derived blob.

## 10. Attribution and licensing

m2c is **GPL-3.0-only**, © Matt Kempster, Simon Lindholm, Zach Banks and
contributors: <https://github.com/matt-kempster/m2c>. The license text is at
`work/tools/m2c/LICENSE` after setup.

This repository does **not** vendor m2c: `setup.sh` clones the pinned commit
into the git-ignored `work/` tree and `pip install -e`s that checkout into a
private venv. No third-party source, binary, wheel or ROM-derived data is
committed, so the repository's own license is unaffected and the GPL obligations
attach only to copies of m2c itself. If you redistribute a copy of the tool (or
a modified checkout), you must do so under GPL-3.0-only and keep its notices
intact. The C drafts m2c prints are output of the tool, not a derived work of
m2c; treat them as ROM-derived analysis and keep them out of Git.
