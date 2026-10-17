# mf-hack — open backlog

Metroid Fusion: shiftable C engine + new hack.

House rules: `AGENTS.md`.  Roadmap and gates: `docs/roadmap.md`.  Settled
decisions: `docs/decisions.md`.  Relocation report: `docs/shiftability-audit.md`.
Blob classification: `docs/blob-classification.md`.  Playtest protocol:
`docs/playtest.md`.

State: `TODO` assignable · `DOING @dev` claimed · `PARK` waiting on the human.
Line format: `- [STATE] ID (source, …) — title  [deps: …]  @dev`.

Sources: `baseline` (measured in this tree), `REA` (Ghidra/REA evidence),
`emulator` (behavior run), `playtest`, `GDD`.

Last landed: SHIFT-001/002/003/004/005/005b/005c/006a/006b1/006b2/006b3/006b4/006b5/006b6/006c/007/008
(harness, audit, symbol map, blob classification, literal/pseudo-literal and
1034 C-literal rewrites, all pointer-like blobs, raw FrameData relocation,
padded and section-reordered boot 578/600, strict gate) and HACK-001/001a/006
(GDD, layout, Cantor).  Details in `git log`.

---

## Phase S0 — behavior harness

- [TODO] SHIFT-001a (baseline) — add title/new-game/pause/save scenarios
- [TODO] SHIFT-001b (emulator) — room-sweep scenario and telemetry mailbox

## Phase S2 — relocatable build

- [PARK @human] PLAYTEST-000 (human) — M0 shiftable-boot playtest
  - handoff: `work/playtest/m0-2026-10-17/`
  - normal passes; **shifted black-screens after Start**; reordered passes
  - blocked on BUG-001; M0 is not DONE and M1 does not start
- [DOING @dev1] BUG-001 (playtest) — shifted M0 build black screen after
  pressing Start; reproduced at frame 778 with the supplied savestates
  - shifted `gNonGameplayRam` OAM entries are already garbage at frame 778;
    `gNextOamSlot` reaches 0x17B without a logged CPU store, then
    `FileSelectDrawOam` overwrites `gVBlankCallback` at `0x030019C4`
  - root cause likely a DMA/block copy or another raw table in the
    file-select path; trace first corrupt write and fix
- [DOING @dev2] QA-001 (emulator) — add a Start/file-select scenario to the
  headless harness and a `shift-start` gate; current boot smoke does not press
  Start and falsely passed BUG-001

## Phase S3a — hack-critical C (106 functions)

- [TODO] SHIFT-009 (REA) — SRAM/Status 54 functions → C  [deps: SHIFT-008]
- [TODO] SHIFT-010 (REA) — Pause 25 + Navigation 27 functions → C  [deps: SHIFT-008]
- [TODO] SHIFT-011 (emulator) — hack-critical behavior suite  [deps: SHIFT-009, SHIFT-010]

## Phase S3b — full C engine

- [TODO] SHIFT-012 (REA) — FileSelect/GameOver 53 functions → C  [deps: SHIFT-011]
- [TODO] SHIFT-013 (REA) — Intro/Ending/Cutscene 217 functions → C  [deps: SHIFT-011]
- [TODO] SHIFT-014 (REA) — Gunship 20 functions → C  [deps: SHIFT-011]
- [TODO] SHIFT-015 (emulator) — full C engine behavior suite + shift test  [deps: SHIFT-012, SHIFT-013, SHIFT-014]

## Phase S4 — hack

- [TODO] HACK-002 (GDD) — content ID registry and save-version plan
- [TODO] HACK-003 (baseline) — content pipeline: Tiled/PNG → room data  [deps: SHIFT-008]
- [TODO] HACK-004a (content) — blockout: 5 rooms, doors, camera, save pad  [deps: HACK-003]
- [TODO] PLAYTEST-001 (human) — M1 blockout playtest  [deps: HACK-004a]
- [TODO] HACK-004b (engine/content) — Resonance Pulse prototype  [deps: PLAYTEST-001]
- [TODO] PLAYTEST-002 (human) — M2 pulse playtest  [deps: HACK-004b]
- [TODO] HACK-004c (engine/content) — The Cantor prototype  [deps: PLAYTEST-002]
- [TODO] PLAYTEST-003 (human) — M3 Cantor playtest  [deps: HACK-004c]
- [TODO] HACK-004d (content) — content-complete slice: logs, secret, data core  [deps: PLAYTEST-003]
- [TODO] PLAYTEST-004 (human) — M4 content-complete slice playtest  [deps: HACK-004d]
- [TODO] HACK-004e (content/qa) — polish and release candidate  [deps: PLAYTEST-004]
- [TODO] PLAYTEST-005 (human) — M5 release-candidate playtest  [deps: HACK-004e]
- [TODO] HACK-007 (design/qa) — one-page playtest scripts and feedback rubric per gate

## Open questions

- Audio timing under the C engine is unverified; treat as a risk until a
  behavior scenario covers it.
- HACK-002 must decide the new ability bit and save version before content uses
  them.
- The 3 `possible` blobs need a data model before SHIFT-006 is complete.
