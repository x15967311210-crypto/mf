# mf-hack — open backlog

Metroid Fusion: shiftable C engine + new hack.

House rules: `AGENTS.md`.  Roadmap and gates: `docs/roadmap.md`.  Settled
decisions: `docs/decisions.md`.  Relocation report: `docs/shiftability-audit.md`.

State: `TODO` assignable · `DOING @dev` claimed · `PARK` waiting on the human.
Line format: `- [STATE] ID (source, …) — title  [deps: …]  @dev`.

Sources: `baseline` (measured in this tree), `REA` (Ghidra/REA evidence),
`emulator` (behavior run), `playtest`, `GDD`.

---

## Phase S0 — behavior harness

- [DONE @mgr] SHIFT-001 (baseline) — mGBA/libmgba harness + vanilla boot smoke
  - static ROM smoke + headless mGBA harness; vanilla 600-frame boot **PASS**
    (`frame_counter=578`, `sub_mode=0x0001`)
- [TODO] SHIFT-001a (baseline) — add title/new-game/pause/save scenarios  [deps: SHIFT-001]
- [TODO] SHIFT-001b (emulator) — room-sweep scenario and telemetry mailbox  [deps: SHIFT-001]

## Phase S1 — relocation audit

- [DONE @mgr] SHIFT-002 (baseline) — asm/C/blob relocation audit scripts and report
  - `docs/shiftability-audit.md`: 1359 ROM refs, 662 literals, 388 unique,
    47 blobs classified (11 pointer tables, 7 possible, 29 data)
- [DONE @mgr] SHIFT-003 (baseline) — address → symbol mapping and whitelist
  - map + ELF local symbols merged; all 662 ROM literals now resolve to
    `symbol+offset`, `unknown=0`; rewrite proposals in
    `work/shift/rewrite_suggestions.md`
- [TODO] SHIFT-004 (REA) — classify blob pointer tables vs graphics/audio  [deps: SHIFT-002]

## Phase S2 — relocatable build

- [TODO] SHIFT-005 (baseline) — rewrite hardcoded refs in non-disasm asm  [deps: SHIFT-003]
- [TODO] SHIFT-006 (baseline) — convert blob pointer tables to relocatable C  [deps: SHIFT-004]
- [TODO] SHIFT-007 (baseline) — relocatable linker + `check_relocs` gate  [deps: SHIFT-003]
- [TODO] SHIFT-008 (emulator) — shift test: padding and section reorder  [deps: SHIFT-007, SHIFT-001]

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

- [TODO] HACK-001 (GDD) — vertical-slice GDD and room brief  [deps: SHIFT-011]
- [TODO] HACK-002 (GDD) — content ID registry and save-version plan  [deps: HACK-001]
- [TODO] HACK-003 (baseline) — content pipeline: Tiled/PNG → room data  [deps: SHIFT-008]
- [TODO] HACK-004 (emulator) — vertical slice: 3 rooms + 1 enemy + 1 event
- [TODO] HACK-005 (playtest) — first playable slice sign-off  [deps: HACK-004]

## Open questions

- HACK-001 needs the creative direction (theme, story, ability set).  Until it
  exists, the slice uses Test Area slots and placeholder text.
- Audio timing under the C engine is unverified; treat as a risk until a
  behavior scenario covers it.
