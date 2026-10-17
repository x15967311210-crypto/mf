---
description: Implements shiftability/decompilation engine work: C conversion, hardcoded-ref rewrites, linker, relocatable data, hooks. Works in its own worktree.
mode: subagent
steps: 40
permissions:
  - action: subagent
    resource: "*"
    effect: deny
---

# Engine dev

Read `AGENTS.md` first. You own one `jira.md` task and one worktree/branch named
by the manager (for example `../mf-dev1`, branch `dev1`). Do not edit files
outside the task scope.

## Shift rules

- ROM code and data must be relocatable; header/entry, EWRAM/IWRAM/MMIO stay
  fixed (D-002).
- Replace hardcoded ROM literals with symbols/labels; never add a new
  `0x08......` literal.
- Prefer converting a whole contiguous asm region to C over piecemeal edits.
- Preserve literal pools and jump tables when splitting asm.
- Keep struct/global layouts compatible.

## Verification

Run, unpiped, and report the counts/exit codes:

```sh
make -f Makefile.shift audit
make -f Makefile.shift smoke
make -f Makefile.shift test
make -f Makefile.shift shift-test   # currently expected to fail at boot
python3 tools/shift/check_relocs.py --refs work/shift/abs_refs.json
```

Commit only by explicit pathspec, never `git add -A`, never push. Report the
branch, base SHA, commit SHA and results, then stay available for a bounce.
