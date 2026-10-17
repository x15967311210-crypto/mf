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
  - normal same-page state is now available:
    `m0f_normal_map_26198.state` + shifted `m0f_fresh_map_7806.state`
  - OAM diff: normal has 66 populated OAM entries (gNextOamSlot=66); shifted
    has all 66 slots `00FF00FF` and gNextOamSlot=0, while BG map/text and
    `main=3/s2=0` match -> missing UI is the OAM layer, not VRAM/palette
  - state diff: normal 66 OAM entries / gNextOamSlot=66; shifted all
    `00FF00FF` / 0; pause substate and active type bytes are present in both,
    so the OAM build/update is not running or is cleared before capture
  - automation: QA-008 adds OAM count/hash checkpoints + `oam-diff`;
    savestate-based objective-page comparison stays local-only
  - before/after state pairs now available:
    normal before 4433 main=1 OAM=30 -> after 4824 main=3 OAM=27
    shifted before 5266 main=1 OAM=26 -> after 5625 main=3 OAM=0
  - before OAM is healthy; only the map-open transition fails (44 slots differ
    in normal after). Normal after has MenuOam entries 33–36; shifted misses
    them, entry 18 oamId 0x1B vs 0x1A, and shifted after leaves one stray
    gOamData slot (`gNextOamSlot=1`)
  - the raw `0x08576150/51/58` comments are already `sSecurityUnlockEvents`
    symbol literals; not the cause
  - shifted after leaves gNextOamSlot=1 and only one gOamData slot; normal
    has 46 queued/27 active and MenuOam 33–36. The pause type/state and the
    `sSecurityUnlockEvents+0x88/0x89/0x90` bytes are correct, so focus on the
    `PauseScreenSetupOam`/`MapScreenDrawSpecialOam` branch and OAM id 0x1A/0x1B
    at entry 18
  - before→open trace: setup writes MenuOam 33–36 correctly in both
    (normal `pc=08078308`, shifted `pc=08079308`); but `PauseScreenProcessOam`
    emits ~45 OAM entries/frame normal vs **1/frame shifted**, leaving
    gNextOamSlot=1. ProcessOam runs every frame in both; the shifted MenuOam
    entries/types at process time are effectively empty after one entry.
  - MenuOam dump after the same replay: normal and shifted have the **same 17
    active type indices** (3,4,5,13,16,17,18,26–29,31–36) and entries 33–36 are
    present in both; only entry 18 differs by one animation frame (0x1A vs
    0x1B). No writer clears 33–36 after setup.
  - At the first map-open frame (normal 4454 / shifted 5287), MenuOam types
    are already identical, incl. 33–36; but shifted is missing the **type-0
    map entries** 9,20,21,22,30,37,38,39 (normal has 7,8,9,20,21,22,30,37–39;
    shifted only 7,8), and the `+4` word of 33–36 is 1 normal / 0 shifted.
  - `gNextOamSlot` at that frame: normal **48**, shifted **1**; ProcessOam then
    emits one entry/frame in shifted. Save data, minimap data, equipment,
    securityHatchLevel and current area are identical between the pair, so this
    is not exploration/save progress.
  - CONTROLLED PAIR (same `mf_us_m0f_normal.sav`, same input): before frame
    1399 both `main=1 active_oam=22`; after frame 1499 normal `main=3
    active_oam=29`, shifted 0; final 1699 normal 51, shifted 0. Normal shows
    the top status bar, L1–L4, OBJECTIVE and dialog body; shifted misses them.
  - Unpatched shifted controlled states are in
    `work/playtest/m0f-2026-10-17/scripts/unpatched_shifted/` (state SHA1s:
    before `53df72ca...`, after `11acde4d...`, final `feb75dc4...`); common
    save `C34B0F60...`; input A@1410/Start@1470/A@1530. Patched shifted
    after/final are `controlled_a_m0g_shifted_patched_*` (29/51).
  - ROOT CAUSE: `sBlob_5657a8_575a60` is a raw `INCBIN`, moved +0x1000, but
    its **501 frame-record OAM-data pointers** were not relocated. Example:
    type 71 shifted outer ptr is `0x08569A3C`, frame first word is
    `0x08567920` (normal) but must be `0x08568920`. Patching all 501 pointers
    +0x1000 yields byte-identical normal/shifted after+final screenshots and
    restores `active_oam=29/51`.
  - The outer table `sBlob_79bec0_79c128` is correctly relocated; this is only
    the frame-record data inside the raw blob.
  - Formal fix: model the 501 frame-record pointer words as a generated,
    relocatable C table/symbol expressions (or equivalent generated frame
    table); keep the normal/reordered builds unchanged. Secondary cleanup:
    direct `sBlob_79bec0_79c128` reference in `asm/disasm_0x080765f8.s`.
  - next: implement the source relocation, verify the controlled pair, then
    rebuild M0f shifted artifact for human retest; do not mark BUG-006 DONE
    until the controlled pair matches byte-for-byte.
- [DONE] QA-008 (emulator) — OAM parity telemetry at checkpoints
  - `oam-diff` PASS 6/6 at 300/600/900/1059/4000/30000, including the plain
    map frame 1059; the earlier 30k mismatch was a worktree data-artifact issue,
    not BUG-007
  - savestate-based objective-page comparison stays local-only
- [TODO] QA-009 (emulator) — checkpoint memory parity (OAM/PAL/VRAM/IO exact;
  IWRAM/EWRAM normalized)
  - exact: OAM/PAL/VRAM-BG/VRAM-OBJ/IO registers
  - normalized: IWRAM/EWRAM 32-bit ROM pointers (+0x1000), excluding the
    known IWRAM code-copy tail; state-based local diff for manual pages
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
