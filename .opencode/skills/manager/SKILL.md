---
name: mf-hack Manager
description: Run the mf-hack multi-agent loop: read jira.md, dispatch engine/tools/content/QA/design subagents, gate builds, merge fast-forwards, keep the roadmap true.
---

# mf-hack manager loop

Use this when acting as the manager for the Metroid Fusion shiftable-engine
hack. You do not write feature code; you plan, assign, verify and keep
`jira.md` true.

## Inputs

- `AGENTS.md` — house rules, change classes, no-binary rule.
- `docs/roadmap.md` — phases and gates.
- `docs/decisions.md` — settled ADRs.
- `jira.md` — task board. Line format:
  `- [TODO] ID (source) — title  [deps: ...]  @dev`.

## One tick

1. **Sense:** `git status`, `git log --oneline -10`, read `jira.md`.
2. **Reconcile:** dead owner → `TODO`; clear stale `[deps:]`.
3. **Claim:** flip one task to `[DOING @devN]`, commit `jira.md` by pathspec.
4. **Dispatch:** launch ONE background subagent per task. Use the
   `engine-dev`, `tools-dev`, `content-dev`, `qa` or `game-designer` agent.
   The manager must be the primary session; the built-in `general` subagent
   cannot launch more subagents.
5. **Charter:** include worktree/branch, the full task line, acceptance
   commands, commit rules (explicit pathspec, no push), and scope. OpenCode
   creates dev worktrees under
   `~/.local/share/opencode/worktree/<session>/devN`; `../mf-devN` is only
   shorthand. Tell it to report `(branch, base SHA, commit SHA, results)` and
   stay available.
6. **Gate:** on report, run on the dev branch:
   - `make -f Makefile.shift audit`
   - `make -f Makefile.shift smoke`
   - `make -f Makefile.shift test` (exit 77 = no emulator, not a pass)
   - `python3 tools/shift/check_relocs.py --refs work/shift/abs_refs.json`
   - `make -f Makefile.shift shift-test` once SHIFT-005/006 claim shiftability.
7. **Land:** `git merge --ff-only devN`; never plain merge, never resolve
   conflicts. On refusal, bounce with the new tip SHA.
8. **Board:** remove landed tasks, clear deps, commit board by pathspec.
9. **Reap:** after the merge is on `hack` and the worktree has no uncommitted
   work, `git worktree remove <path>` (remove the ignored `data`/`sound`
   symlinks first if that is the only refusal), `git branch -d devN`,
   `git worktree prune`. Never reap the active dev; keep a dirty/parked
   worktree only for a real WIP and record why.
10. **Loop.** Keep ≤3 devs live. QA and designer can run alongside.

## Human playtest gates

M0–M5 are hard human gates (`docs/playtest.md`).  At each gate, build
`work/playtest/<gate>-<date>/`, write the one-page test script, hand it to the
human, and stop.  Do not mark the milestone done or start dependent tasks until
`PLAYTEST-PASS`.  Blocking feedback becomes `BUG-*` / `PLAYTEST-*`.

## Rules

- Pushed/green means the gate commands ran unpiped and the counts are reported.
- A SHA1 mismatch is expected on the C engine; do not use `make check` as the
  hack gate (D-003).
- Golden/expected-output changes need evidence in the commit message; reject
  pass-hacks.
- Never commit ROMs, baseroms, extracted blobs, savestates, screenshots with
  original graphics, or Ghidra/REA databases.
- The manager may write `jira.md`, `docs/**` and test fixtures, not engine,
  tools or hack content.
