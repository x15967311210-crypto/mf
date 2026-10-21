# C style and format contract

Status: **contract added (DOC-002); the tree is not mass-reformatted yet.**

`.clang-format` in the repository root is the machine-readable contract, and
`mk/format.mk` (included from `Makefile`) exposes it as `make format`,
`make format-check` and `make format-list`. This page explains the rules, what
the targets cover, and how the style is adopted without a giant diff.

## The rules

| Rule | Setting |
|---|---|
| Indent | 4 spaces, no tabs, 4-column continuation (`UseTab: Never`, `IndentWidth: 4`) |
| Braces | Allman: the opening brace of a function, struct, enum, `if`/`else`, loop or `switch` body is on its own line (`BreakBeforeBraces: Allman`) |
| Single-statement bodies | no braces added, and no single-line short functions/blocks/ifs (`AllowShort*: Never/None`) |
| Pointers | `const u8* p`, never `const u8 *p` (`PointerAlignment: Left`, `DerivePointerAlignment: false`) |
| Case labels | indented one level inside the `switch` body (`IndentCaseLabels: false`) |
| Line length | 120 columns (`ColumnLimit: 120`) |
| Wrapped calls | continuation indent, no alignment to `(` (`AlignAfterOpenBracket: DontAlign`) |
| Operators | binary/ternary operators stay at the end of the line |
| Casts / parens | `(u8*)p`, `if (x)`, `f(x)` |
| Includes | not sorted, blocks preserved (`SortIncludes: false`, `IncludeBlocks: Preserve`) |
| Comments | not reflowed (`ReflowComments: false`) |

Match the surrounding file when a file already disagrees with a rule: the goal
is that new code is consistent and reviewable, not that the whole tree looks
identical.

## What the targets cover

| Target | What it does |
|---|---|
| `make format` | `clang-format -i` over the file list below |
| `make format-check` | `clang-format --dry-run --Werror` over the same list |
| `make format-list` | prints the exact list, one path per line |

The list is `src/**/*.c`, `include/**/*.h` and `hack/**/*.c|h`.

Never formatted, by design:

- `hack/gen/**` — generated content tables (`content_tables.h`,
  `scroll_tables.h`, `sprite_tables.h`, `text_tables.h`, `tileset_tables.h`);
- everything under `work/`, and any `.s`/`.inc` assembly or extracted `data/`;
- data tables and headers produced by the extractor or the content pipeline.

Overridable variables: `CLANG_FORMAT` (default `clang-format`), `FORMAT_STYLE`
(default `--style=file`), `FORMAT_PATHS` (default `src include hack`),
`FORMAT_EXCLUDE` (default `hack/gen`) and `FORMAT_FILES` (an explicit list wins
over the `find`).

## How to run

```sh
make format-list                 # what would be touched
make format                      # rewrite those files in place
make format-check                # report only; nonzero if a file differs
make format-check CLANG_FORMAT=clang-format-18
```

`--dry-run --Werror` needs **clang-format >= 10**. When the binary is missing,
`format-check` prints `FORMAT-CHECK: SKIP (77) - ... not found; this is not a
pass` and exits 0, so the docs/CI path never reports a false pass. `make
format` fails instead: silently doing nothing on an explicit rewrite request is
worse than a clear error.

`make format-check` is not part of `make all`, `make check`, `make audit` or
`make smoke` yet; adding it to a gate is a separate decision once the existing
files are clean.

## Adoption

- **No mass reformat.** Existing files are not reformatted until a dedicated
  task does it in one isolated commit, so blame and the baseline SHA history
  stay readable.
- `format-check` is therefore **expected to fail** on the current tree. Do not
  make it green by reformatting unrelated code, and do not silence it by
  narrowing `FORMAT_PATHS`.
- New files must be clang-format clean when they land. When you substantially
  edit an existing file, run `clang-format -i` on that file only and keep the
  reformat in the same commit as the change (or in its own commit if the file
  is large).
- Generated and vendored code is out of scope: see the exclusion list above.
- If you must deviate from `.clang-format`, change the contract in this task's
  files (`.clang-format` plus this page) rather than reformatting around it.
