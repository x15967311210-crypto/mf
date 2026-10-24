# mf-hack — open backlog

Metroid Fusion: shiftable C engine + new hack.

House rules: `AGENTS.md`. Roadmap/gates: `docs/roadmap.md`. Decisions:
`docs/decisions.md`. Playtest protocol: `docs/playtest.md`.

State: `TODO` assignable · `DOING @devN` claimed · `PARK` waiting on the human.
DONE entries are removed from this board; `git log` is the history. Keep entries
short: one line plus only the context a fresh dev needs.

Last updated: 2026-10-23.

## Engine and decompilation

- [TODO] TECH-005 (tools/decomp) — decomp.me preset 250 corpus
  - 561/600 scratches are perfect (score 0 = 100%). Fetch read-only into
    `work/decompme/`, map names to `thumb_func_start` symbols, port with
    `compare_text`, credit the author. Never commit scratch source.
- [TODO] SHIFT-009 (REA) — SRAM/Status 54 functions → C
  - `SramRead_WorldData` / `SramWrite_WorldData` done. `Sram_InitSaveFile`
    candidate is blocked on `gEquipment`/door register shape and the
    `0x4C/0x4D` fold; `yEnd`/`yExit` are confirmed (struct offsets 5/8).
    Use the m2c draft next. `SramWrite_MostRecentSaveFile` is parked.
- [DOING @dev84] SHIFT-010 (REA) — Pause 25 + Navigation 27 functions → C
  - Twenty-four pause/input/status functions are done; next `GetMinimapData`
    (decomp.me `jPgTL`, 0x08077084). Continue from
    `work/decompme/perfect.tsv`.
- [TODO] SHIFT-011 (emulator) — hack-critical behavior suite  [deps: SHIFT-009, SHIFT-010]
- [TODO] SHIFT-012 (REA) — FileSelect/GameOver 53 functions → C  [deps: SHIFT-011]
- [TODO] SHIFT-013 (REA) — Intro/Ending/Cutscene 217 functions → C  [deps: SHIFT-011]
- [TODO] SHIFT-014 (REA) — Gunship 20 functions → C  [deps: SHIFT-011]
- [TODO] SHIFT-015 (emulator) — full C engine behavior suite + shift test  [deps: SHIFT-012, SHIFT-013, SHIFT-014]

## Shift and relocation

- [TODO] BUG-014 (shift/engine) — post-link scan: raw pointer runs remain
  - `postlink-scan` is committed; triage remaining structured runs as real
    unrelocated tables vs reviewed whitelist. Do not auto-whitelist and do not
    wire strict into the main gate until the list is zero/justified.
- [TODO] QA-004 (tools) — scanner for pointer-like data in raw blobs
  - find 2/4-byte aligned embedded `FrameData`/pointer tables; no raw pointer
    table may hide behind a `data` classification.
- [TODO] QA-028 (tools/qa) — settle window restarts on every new byte pair
  - replace “no new pair” with a duration/state-field criterion; do not weaken
    OAM/PAL/VRAM durable checks.

## Harness and parity

- [TODO] SHIFT-001a (baseline) — title/new-game/pause/save scenarios
- [TODO] SHIFT-001b (emulator) — room-sweep scenario and telemetry mailbox
- [TODO] QA-009 (emulator) — checkpoint memory parity
  - exact OAM/PAL/VRAM/IO; normalized IWRAM/EWRAM 32-bit ROM pointers.
- [TODO] QA-007 (emulator) — later map/dialog/Enter regression checkpoint
  - shifted black-screen route + normal same-page state; BUG-005 fixed.

## M1 and hack content

- [PARK] PLAYTEST-001 (human) — M1 blockout; M1 is **FAIL/paused**
  - artifact `work/playtest/M1-2026-10-21b/`; 2026-10-21b feedback:
    BUG-024 player sprite invisible, BUG-025 wrong tile colours, BUG-026
    HUD/minimap textures. Rendering paused by the human; do not start
    HACK-004b/M2 until M1 passes.
- [TODO] BUG-024 (engine) — player sprite invisible in the M1 rooms
- [TODO] BUG-025 (content) — room tile colours wrong in the M1 rooms
- [TODO] BUG-026 (engine/content) — HUD/minimap textures wrong
- [TODO] HACK-004a2b (engine/content/qa) — events, pads and transition scenario
  - add `AREA_TEST_1` event block 0x6E..0x77 and fix broad pad checks; keep
    normal/shifted/reordered SHAs unchanged; add the cross-room save/load
    scenario. M2-enabling, not an M1 blocker.
- [TODO] QA-030 (qa/tools) — automated hack save/load on the Entry Ledge pad
  - needs a valid SaveRAM or TAS save sequence; QA-027 host coverage is done.
    Assert `area=7 room=0`, saved `gEventCounter`, banner/enemy/spriteset
    after load.
- [TODO] HACK-004b (engine/content) — Resonance Pulse prototype  [deps: PLAYTEST-001]
- [TODO] PLAYTEST-002 (human) — M2 pulse playtest  [deps: HACK-004b]
- [TODO] HACK-004c (engine/content) — The Cantor prototype  [deps: PLAYTEST-002]
- [TODO] PLAYTEST-003 (human) — M3 Cantor playtest  [deps: HACK-004c]
- [TODO] HACK-004d (content) — content-complete slice  [deps: PLAYTEST-003]
- [TODO] PLAYTEST-004 (human) — M4 content-complete slice playtest  [deps: HACK-004d]
- [TODO] HACK-004e (content/qa) — polish and release candidate  [deps: PLAYTEST-004]
- [TODO] PLAYTEST-005 (human) — M5 release-candidate playtest  [deps: HACK-004e]
- [TODO] HACK-007 (design/qa) — one-page playtest scripts and feedback rubric per gate

## Parked / blocked

- [PARK] TECH-003f (decomp) — `SramWrite_MostRecentSaveFile` kept asm
  - C port stopped at a 17-byte diff; permuter 900 s best **200**, no `score 0`
    (best source: `work/decompme/SramWrite_MostRecentSaveFile.best200.c`).
    Function remains asm, SHA/gates clean; revisit with m2c or a new
    epilogue/checksum shape.
- [PARK] QA-014 (emulator) — valid elevator/pre-entry reproducer
  - existing states are post-entry; capture matched normal/shifted/reordered
    pre-entry states before BUG-010 is actionable.
- [PARK] BUG-010 (playtest) — shifted elevator hard freeze / black screen
  - blocked on QA-014; do not call M0 PASS from the unmatched states.
- [PARK] QA-012 (emulator) — M0 room/dialog coverage matrix
  - paused behind BUG-010; required for M0 sign-off.

## Milestone gates

- S0 harness / S1 audit / S2 relocatable build: **green**. Normal
  `ca33f434…`, padded `5888a563…` (`SHIFT-DYNAMIC`), reordered
  `9dac0a4b…` (`SHIFT-REORDER-DYNAMIC`).
- S3a hack-critical C: in progress (SHIFT-009/010).
- S3b full C engine: not started.
- M0 human PASS recorded; **M1 FAIL/paused**; M2–M5 blocked on M1.

## Open questions

- Audio timing under the C engine is unverified; risk until a behavior scenario
  covers it.
- Remaining `possible` blobs still lack a data model; not blocking shiftability.
- HACK-002 content IDs/save version are settled in `docs/design/content-ids.md`;
  the broad save-pad check stays in HACK-004a2b.
