# Design decisions

Append-only.  A decision is changed by a new entry, not by editing history.
Every entry names the rule, the reason, and what it forbids.

---

## D-001 — Hard fork of the decomp baseline

**Decision.** The decomp at commit `fdf3e43` is frozen as the vanilla baseline.
There is no automatic upstream merge.  Future decompilation happens inside this
tree and is evaluated by the behavior suite.

**Reason.** The hack needs freedom to change engine layout.  Chasing upstream
matching would fight the shiftable refactor.

**Forbids.** Adding an `upstream` remote that silently changes `main`; rebasing
baseline tags.

---

## D-002 — Shiftable ROM, fixed RAM

**Decision.** ROM code and ROM data are relocatable.  The ROM header/entry
point, EWRAM, IWRAM, MMIO, palette, VRAM and OAM addresses stay fixed.

**Reason.** GBA RAM/MMIO addresses are small, numerous and hardcoded everywhere;
relocating them buys little.  ROM pointers are the actual blocker.

**Forbids.** New hardcoded ROM address literals.  New globals outside the
documented free EWRAM/IWRAM regions.

---

## D-003 — Behavior tests, not SHA1, gate the C engine

**Decision.** `make check` is a baseline-tag tool.  The shiftable engine and the
hack are gated by the behavior suite (`tests/emulator`) and the shift test.

**Reason.** Functional C will not be byte-identical, and the hack will
intentionally change behavior.  SHA1 would reject both.

**Forbids.** Using a SHA1 mismatch as a reason to reject a functional change.
Using a green SHA1 as evidence that a new feature works.

---

## D-004 — C-NONMATCH is normal

**Decision.** Decompiled C does not have to match the original instruction
stream.  It must be behaviorally verified.  `MATCHED` remains an optional
quality label.

**Reason.** Byte matching is the most expensive part of decompilation and buys
nothing for the hack once the engine is shiftable.

**Forbids.** Blocking a C conversion on codegen matching.

---

## D-005 — No copyrighted binaries in Git

**Decision.** ROMs, baseroms, extracted `data/` blobs, savestates, screenshots
containing original graphics, Ghidra projects/databases and REA evidence
bundles stay out of Git.

**Reason.** The repository distributes source and patches, not the game.

**Forbids.** `git add -f` on ignored artifacts.  Committing `work/`.

---

## D-006 — Emulator-only target, 32 MB ceiling

**Decision.** The hack targets emulators (mGBA/libmgba).  ROM may grow to
16/32 MB by linker padding.  Flashcart compatibility is not a requirement.

**Reason.** Removes flashcart/save-type constraints and unlocks free-space
planning.

**Forbids.** Assuming a flashcart save-type detection path in new code.

---

## D-007 — Hack starts after S3a, not after the full 396

**Decision.** S3a = shiftable build + behavior suite + the 106 hack-critical
functions in C (SRAM/Status 54, Pause 25, Navigation 27).  The vertical-slice
hack may start there.  S3b (remaining 290 functions) continues in parallel.

**Reason.** The cutscene/ending code is large but irrelevant to the first
playable slice; blocking on it delays the project without reducing risk.

**Forbids.** Declaring the C engine "complete" at S3a; cutscene work still has
to land before the full-C tag.

---

## D-008 — Source-of-truth content, generated binaries ignored

**Decision.** Rooms, graphics, text and music are authored in
`hack/content/` (YAML/Tiled/PNG/UTF-8).  `hack/gen/` is generated and ignored.
The build regenerates it from source and the baserom extractor.

**Reason.** Reviewable content, reproducible builds, no accidental binary
assets in history.

**Forbids.** Editing generated files as the primary change.

---

## D-009 — ID registry before content

**Decision.** Every new room, sprite, event, text block, music track and save
field gets an ID in `hack/include/hack/ids.h` and
`docs/content-tracker.md` before use.

**Reason.** ID collisions are silent corruption in this engine.

**Forbids.** Magic numbers in new content code.

---

## D-010 — Decomp status vocabulary

**Decision.** `ASM` → `C-REF` (readable, not linked) → `C-FUNC` (linked,
behavior-tested) → `VERIFIED` (covered by suite).  `MATCHED` is optional.

**Reason.** Makes progress measurable without pretending matching is the goal.

**Forbids.** Counting `C-REF` as integrated engine code.

---

## D-011 — Baseline extraction stays address-based

**Decision.** `tools/extractor.py` and `database.json` keep extracting from the
original ROM addresses.  Relocation happens in the link, not in the extractor.

**Reason.** The extractor is a stable oracle; rewriting it to chase layout would
add risk with no benefit.

**Forbids.** Changing `database.json` addresses to follow the current build.

---

## D-012 — Checkpoint-first parity iteration, full TAS only at the end

**Decision.** Do not run the 339,001-frame native/headless movie after every
BUG fix.  Start each iteration from the last confirmed PASS checkpoint state,
reproduce the first diff in a few seconds, fix it, and extend the run in
chunks from that checkpoint.  Run the full 339,001 tier only after the
incremental chunks pass the previous failure point without exposing a new
diff.

**Reason.** A full run is ~10-15 minutes; a checkpoint resume is seconds.  The
checkpoint states are exact mGBA `SAVESTATE_SAVEDATA` blobs, so the CPU,
memory and movie timeline are reproduced, not approximated.

**Forbids.** Treating a chunk PASS as a full-TAS PASS; running full after every
fix; using a state from a different core/ROM build without verifying a short
overlap (or recapturing the checkpoint).

**Requires.** Keep normal + shifted (+ reordered when relevant) states at the
last PASS node in `work/` (ignored), record their SHA256 and the ROM SHA1s in
the task evidence, and recapture them after a ROM-changing fix when the old
state no longer loads cleanly.

---

## D-013 — Hack content owns its tables, IDs, text and build overlay

**Decision.** Baseline `src/data` stays vanilla-owned.  New hack content lives
in `hack/content` (YAML/JSON/Tiled/text) and is generated into ignored
`hack/gen`.  `hack/include/hack/ids.h` and `docs/content-tracker.md` are
generated from `hack/content/ids.yaml`.  A `HACK=1` build links the generated
content overlay; normal, shifted and reordered baseline builds remain unchanged
and continue to serve parity gates.  Text uses `charmap.txt` plus the existing
`tools/preproc` C `INCTEXT` path.

**Reasons.** D-009 requires IDs before content, and editing baseline tables for
every room makes vanilla parity and content changes inseparable.  A separate
hack overlay lets M1/M2 content grow without rewriting `src/data` or silently
changing the parity ROMs.

**Implementation contract.**
- One narrow, reviewed hook selects hack-owned AREA_TEST_1 room/door/text
  tables when `HACK=1`; no other baseline table edits for content.
- Generated C tables are deterministic and ignored; only source YAML/JSON,
  `charmap.txt`, `hack/include/hack/ids.h` and the tracker are committed.
- The golden path must be one room + one dialogue + one enemy behavior driven
  from source, with a validator and a behavior scenario.
- No hand-written magic IDs; unknown text characters and dangling references
  fail the generator.

**Forbids.** Hand-editing `src/data` tables to add hack rooms, items, events or
text; committing generated `hack/gen`; using an ID without the registry;
guessing charmap codes.
