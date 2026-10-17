# mf-hack — agent house rules

Metroid Fusion decompilation turned into a shiftable C engine and a new hack.
This file is the contract for every agent and human working in the tree.

## Current phase

**SHIFT-001 / SHIFT-002 / SHIFT-003** — behavior harness, relocation audit,
symbol mapping.  Do not start content production or a full C conversion before
the shiftability gates in `docs/roadmap.md` are green.

## The one rule that prevents lost work

Commit only with an explicit pathspec:

```sh
git commit tools/shift/audit_asm.py docs/shiftability-audit.md -m "dev1: DONE SHIFT-002 — asm relocation audit"
```

Never use `git add -A`, `git add .`, or `git commit -a`.  Never push from a dev
worktree.  The manager merges with `git merge --ff-only devN`; a refusal means
the tip moved, so the dev rebases and re-runs the gate.

## Change classes

| Class | Allowed paths | Acceptance |
|---|---|---|
| Decomp | `src/`, `include/`, `asm/` | C compiles; behavior suite green |
| Shift | `tools/shift/`, `linker*`, `asm/` relocs | `check_relocs` + shift test green |
| Hack | `hack/` | feature scenario + no regression |
| Content | `hack/content/`, `hack/gen/` (generated ignored) | content validator + room scenario |
| Docs | `docs/`, `*.md` | links/commands valid |

`src/`, `include/`, `asm/`, `data/`, `sound/`, `linker.ld` are baseline-owned.
Only decomp/shift work may touch them, and only when the behavior suite stays
green.

## Address and layout rules

- ROM header and entry point stay fixed at `0x08000000` / `0x080000c0`.
- EWRAM, IWRAM and MMIO addresses stay fixed.  New globals go into the free
  EWRAM/IWRAM areas listed in `docs/shiftability-audit.md`.
- ROM code and ROM data must be relocatable.  Any new hardcoded ROM address is
  a bug; `tools/shift/check_relocs.py` is the gate.
- New code and data live in `hack/` until promoted by an ADR.
- Never resize an existing data blob in place during the baseline phase; add
  new data at the end and redirect pointers.

## Testing

- `make -f Makefile.shift smoke` — static ROM/header checks, always available.
- `make -f Makefile.shift test` — emulator scenarios; skipped with exit 77 if
  no emulator is installed.
- `make -f Makefile.shift audit` — relocation and blob audit.
- A feature is not done until its scenario exists and passes.
- `make check` (SHA1) is a **baseline-tag** tool only.  Do not use it to gate
  the shiftable engine; use the behavior suite instead.

## No copyrighted binaries in Git

Never commit ROMs, baseroms, extracted `data/` blobs, savestates, emulator
screenshots containing original graphics, Ghidra projects/databases, or REA
evidence bundles.  `work/` is ignored.  Release artifacts are BPS patches,
not ROMs.

## Definition of done

1. The change is scoped to the class table above.
2. `check_relocs` passes (shift work) or the feature scenario passes (hack work).
3. The behavior suite has no regression in the touched systems.
4. `docs/` and `jira.md` are updated when a gate, ID, or status moves.
5. Commit is local, pathspec-only, one concern per commit.

## Decomp status vocabulary

`ASM` → `C-REF` (readable C, not linked) → `C-FUNC` (linked, behavior-tested)
→ `VERIFIED` (covered by the behavior suite).  `MATCHED` is optional and never
a gate for the C engine.
