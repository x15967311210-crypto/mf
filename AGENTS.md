# mf-hack — agent house rules

Metroid Fusion decompilation turned into a shiftable C engine and a new hack.
This file is the contract for every agent and human working in the tree.

## Current phase

**Shiftability gates are green (2026-10-22).**  Normal `ca33f434…`, padded
`5888a563…` (`SHIFT-DYNAMIC` PASS) and section-reordered `9dac0a4b…`
(`SHIFT-REORDER-DYNAMIC` PASS) all build and pass static + dynamic smoke.  Next:
hack-critical C (S3a) and the upstream intro sync; M1 rendering/playtest remains
paused by the human.

## Team

This is a multi-agent project. The **manager** is a primary agent that owns
`jira.md` and dispatches subagents; it does not write feature code. Available
project agents live in `.opencode/agents/`: `manager`, `game-designer`,
`engine-dev`, `tools-dev`, `content-dev`, `qa`.

- The manager dispatches ONE background subagent per task, with a self-contained
  charter and a worktree/branch (`../mf-devN` / `devN`).
- Devs work only in their worktree, commit by explicit pathspec, never push.
- The manager gates a dev branch with `make -f Makefile.shift audit/smoke/test`
  and `check_relocs.py`, then merges `--ff-only`.
- The game designer discusses gameplay with the human, writes
  `docs/design/GDD.md` and `docs/design/vertical-slice.md`, and does not write
  code or edit `jira.md`.
- QA files `BUG-*` / `QA-*` tasks; it does not implement features.

The built-in `general` subagent cannot launch more subagents, so orchestration
must happen in a primary session (the `manager` agent or the human's session).

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

- **Human playtest gates are hard gates.**  At M0–M5 in `docs/playtest.md`, the
  manager hands the human a local build and waits for sign-off.  No milestone is
  DONE, no dependent task starts, and no gate is removed until the human has
  played it.  Blocking feedback becomes `BUG-*` / `PLAYTEST-*` tasks.
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
