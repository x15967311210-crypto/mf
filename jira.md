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

Last landed: SHIFT-001/002/003/004/005/005b/005c/006a/006b1/006b2/006b3/006b4/006b5/006b6/006c/007/008,
QA-001/002/003/005/006, BUG-001/002/003/004/005 (harness, audit, symbol map,
blob classification, literal and C-literal rewrites, raw FrameData/Sa-X/intro/
popup descriptor relocation, padded and section-reordered boot, Start/file-
select gate, headless TAS input 4k/30k, screenshot parity, 578/600 and
input/visual parity) and HACK-001/001a/006
(GDD, layout, Cantor).  Details in `git log`.

---

## Phase S0 — behavior harness

- [TODO] SHIFT-001a (baseline) — add title/new-game/pause/save scenarios
- [TODO] SHIFT-001b (emulator) — room-sweep scenario and telemetry mailbox
- [DONE] QA-002/QA-003 (emulator) — headless TAS input replay + shifted gate
  - committed 4k fixture + `INPUT_CHECK` assertions; `make test` runs it
  - `shift-input` runs the same 4k input against the shifted build; PASS
  - full 259k input stays manual/BizHawk; manual playtest remains extra
- [TODO] QA-004 (tools) — scanner for 2-byte-aligned embedded
  `FrameData`/pointer tables; prototype found the BUG-003/004 tables but the
  tool/report is not committed yet

## Phase S2 — relocatable build

- [BLOCKED @human] PLAYTEST-000 (human) — M0 shiftable-boot playtest
  - M0f fresh shifted map at frame 7806: tile garbage fixed, but objective
    dialog box body/legend/bottom UI missing (BUG-006)
  - M0 is not DONE and M1 does not start until human sign-off
- [DOING @dev1] BUG-006 (playtest) — shifted fresh map objective UI missing
  - fresh state `m0f_fresh_map_7806.state` (PNG savestate), frame 7806,
    `disp=5F00 main=3 s1=0 s2=0`
  - normal screenshot shows top `L SLEEP`/`MAIN DECK`/`STATUS R`, right
    `L1-L4 LOCK`, bottom `OBJECTIVE`; shifted fresh has the map tiles/icons
    but those UI overlays are missing
  - text renders; dialog box body, legend and bottom UI are missing; old M0e
    slot screenshots are stale VRAM and not evidence
  - compare OAM/BG/OBJ/palette and map UI writers; TAS map frame 1059 is a
    clean reference for the plain map, not the objective text
- [TODO] QA-007 (emulator) — later map/dialog/Enter regression checkpoint
  - shifted black-screen reproduction can be automated from
    `m0e_shifted_slot3.ss3` + held Start; map/dialog visual comparison needs a
    normal same-page state or a deterministic normal route
  - BUG-005 fixed; slot3 local state check passes
- [DONE] QA-006 (emulator) — 30k input fixture + `shift-input-30k` gate
  - normal/reordered/shifted 30k PASS after BUG-004
- [DONE] QA-005 (emulator) — screenshot-parity gate
  - `screen-diff` passes after BUG-003; normal/shifted/reordered match at
    600/900
- [TODO] QA-004 (tools) — scanner for 2-byte-aligned embedded
  `FrameData`/pointer tables; prototype found the BUG-003/004/005 tables but
  the tool/report is not committed yet

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
