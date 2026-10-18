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
QA-001/002/003/005/006, BUG-001/002/003/004/005/006 (harness, audit, symbol
map, blob classification, literal and C-literal rewrites, raw FrameData/Sa-X/
intro/popup descriptor/map-OAM relocation, padded and section-reordered boot,
Start/file-select gate, headless TAS input 4k/30k, screenshot/OAM parity,
578/600 and input/visual parity), PLAYTEST-000 (controlled map pass; full M0 reopened), and
HACK-001/001a/006 (GDD, layout, Cantor).  Details in `git log`.

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
  - `PLAYTEST-PASS` received 2026-10-18 for the fixed shifted candidate
    `work/playtest/m0f-2026-10-17/fixed/mf_us_m0f_shifted_fixed.gba`
    (`a822b2d8...`); normal/reordered original artifacts unchanged.
  - Retest evidence: `work/playtest/m0f-2026-10-17/fixed/RETEST.md` and
    `fixed/retest/`; common save restored to pristine `C34B0F60...`.
  - before/after/final `active_oam=22/29/51`; after/final screenshots
    byte-identical to normal (`97EFFB81...` / `1E6535B7...`).  This controlled
    map check remains valid.
  - **REOPENED 2026-10-18**: BizHawk baseline TAS file-select parity fails.
    normal/reordered frame 600 `s1=0002 s2=0001`; shifted `s1=0003 s2=0000`.
    The original movie sticks at `SAMUS DATA`; ±1-frame input offset reaches
    gameplay, so it is not a hard deadlock.  Same on unpatched shifted, so not
    a BUG-006 regression.  Evidence in
    `work/playtest/m0-2026-10-17/tas/bizhawk_m0f_20261018/`.
  - **REOPENED AGAIN 2026-10-18**: fresh manual shifted path fails Navigation
    Room/computer dialogue (slot2 corrupted, active_oam=96; normal 66); this
    path is not covered by the common-save controlled map PASS (BUG-009).
  - **BLOCKED AGAIN 2026-10-18**: candidate `0bddba78` hard-freezes on
    room-61 elevator state (BUG-010); M0 is not DONE.  QA-012 coverage is
    paused; M1 blockout stays parked.
- [DONE] QA-011 (emulator) — common file-select state parity (inconclusive)
  - mGBA f600 common state loads visually identically in normal/reordered/
    shifted (`1C00/7/3/0`, same framebuffer hash).
  - Execution-level replay is invalid: the state was captured mid-BIOS with
    saved code/IWRAM pointers.  Normal resumes; reordered and shifted freeze
    with PC in BIOS (`~0x38..0x68`, IRQ disabled).  Reordered is the control
    and fails too, so this cannot decide BUG-008.  mGBA 0.11 vs capture 0.10.5
    and the committed harness having no state option are contributing factors.
  - Do not use the mid-BIOS state or a per-build input offset as a gate.
- [DONE] QA-011a (emulator) — cold-boot file-select parity
  - rebuild normal/reordered/shifted in one tree with identical `data/Blob_*`
    inputs and record SHA1s; use the common SaveRAM and cold boot, not a
    cross-build BIOS state;
  - log `frame_counter disp main s1 s2` every frame around file-select
    (normal 600 vs shifted 600) and compare first divergence;
  - if shifted is exactly one frame ahead from the same boot/input, classify
    boot/frame alignment vs engine; do not close BUG-008 until this is proven.
- [DONE] QA-011b (emulator) — BizHawk file-select A trace
  - capture per-build BizHawk 2.3 states at 400/401 and CPU/PC trace around the
    A handler; record the BizHawk mGBA core version; compare with the clean
    mGBA 0.11 control.
  - decide whether the gate is BizHawk-specific or whether mGBA 0.11 is
    authoritative before changing source.
- [DONE] BUG-009 (playtest) — shifted Navigation Room computer-dialogue corruption
  - final shifted fixed `a822b2d8...` fresh manual path: slot1 Navigation Room
    frame 18171 `disp=5E00 main=1 s2=0100 active_oam=40` clean; slot2 computer
    dialogue frame 24263 `disp=5F00 main=3 s2=0100 active_oam=96` corrupted,
    still 96 after +180 frames. normal reference frame 26198 active_oam=66
    clean; controlled common-save final active_oam=51 clean.
  - not stale VRAM/state; fresh manual path.  This path is not covered by the
    common-save controlled map PASS.  Likely another unrelocated OAM/data table
    not covered by BUG-006's 501 pointers.
  - evidence: `work/playtest/m0f-2026-10-17/FRESH_DIALOG_FAIL.md`,
    `mgba-final/retest_fresh_dialog/`; slot2 screenshot SHA1
    `863862094074CB9930514F065A5B862EB05898CC`.
  - engine reproduction: slot2 OAM/shadow entries are structurally present and
    `gNextOamSlot=96` is the game's queued count; the **dialog text is correct**
    but the map legend/overlay tiles are wrong.  This is not the 501 OAM
    pointer table alone; likely a legend/BG tilemap descriptor table.
  - **node located from the savestate**: shifted slot2 is
    `gCurrentArea=0`, `gCurrentRoom=0x10` (16), `gCurrentNavigationRoom=1`,
    `main=3`, `s2=0x0100`, `eventCounter=3`.  This is the Navigation Room
    dialogue node; the dialogue image is not needed for identification.
  - matched normal state exists (`area=0 room=0x10 navroom=1 event=3
    main=3 s2=0x0100 active_oam=96`); dump diff: OAM only 7 animation bytes,
    PAL 40, IO 175, VRAM 2511 starting 0xC80A/0x153B8.  Evidence:
    `work/playtest/m0f-2026-10-17/matched_state/`.
  - **scroll lead disproved:** the desktop IO `0x4A46` scroll is stale state
    capture.  Loading the shifted slot2 state in mGBA 0.11 and running 180
    frames gives normal `gBackgroundPositions` (`0,0,0,0x100,0,0,0x1F0,0x1F0`)
    and normal-looking BG scroll registers, but the VRAM/PAL/OBJ differences
    persist (VRAM 2507 bytes, PAL 50, OAM 28).  The corruption is in the
    **BG tilemap/OBJ/graphics data**, not a scroll writer.
  - BGxCNT is identical (`1800/1B03/1A0A/DC49`).  Focus VRAM `0xC800` and OBJ
    blocks `0x14740/0x14B40/0x14F40/0x15340`; inspect
    `sNavigationConversationPopUpGraphics` / `NavigationConversationLoadPopUpGraphics`
    and the map/legend tilemap descriptor source for an unrelocated pointer.
  - next: prove the wrong graphics/tilemap table and fix; do not patch BG
    scroll or the 501 OAM pointers.
  - M0f is BLOCKED again; controlled map PASS is path-specific only.
  - graphics-source check: the minimap/pop-up LZ77 sources are byte-identical
    normal vs shifted at +0x1000; shifted loads a **different legend stream**
    into VRAM 0xC800 (L1–L4 panel) instead of normal's X-parasite portrait.
    Not a stale graphics pointer; likely pause/map-state descriptor selection
    (`StatusScreenDrawEverything` vs portrait path, `sDebugSectionInfo+...`,
    `sCharacterWidths+...`, `sExploredMinimapBitFlags+...`).
  - **likely root table**: `sNavigationConversationPopUpGraphics`
    (`src/data/menus/pause_debug.c`) has relocated `pGraphics` on the four
    records, but raw pointer-like words remain in the `preamble` and each
    record's `data` (0x0857BBC4/0x0857BBD0/0x0857BBF0, 0x08576804/...+0x44/
    +0x64/+0x84/+0xA4/+0xC4/+0xE4).  All are inside
    `sBlob_5766D4_prefix` and need `+0x1000` in the shifted build.  Fix all of
    them as `sBlob_5766D4_prefix + offset`, preserving the 0x14 preamble +
    4x0x18 record layout.
  - LANDED `b394ab3`: converted preamble/record data pointers to
    `sBlob_5766D4_prefix + offset`; layout remains 0x14 + 4*0x18; normal SHA1
    `ca33f434...` preserved.  Shifted table at 0x57CC50 has all pointers
    +0x1000; shifted artifact is `0bddba78...`.
  - automatic gates (4k/30k/screen/OAM/shift/boot/audit/strict/smoke) pass.
  - fresh paired Navigation Room/computer-dialogue retest is pending; new
    candidate at `work/playtest/m0f-2026-10-17/mgba-final-bug009/`.
  - if fresh room-16 UI matches normal, close BUG-009; otherwise continue the
    descriptor path.  Do not call M0 DONE yet.
  - **PASS**: fresh room-16 candidate `0bddba78...` from the 4FD087E9 SaveRAM,
    Nintendo Presents frame 139, `story_route_normal_from139.input`, ends
    frame 21649 `event=3 disp=5F00 main=3 s1=0 s2=0x100 active_oam=96`.
    End PNG/VRAM/PAL/OAM/IO all byte-identical to matched normal:
    `ED432C7A...` / `E25649D0...` / `1EA43B79...` / `B09CECD8...` /
    `449C2591...`.  Fresh path, not the saved slot2.
  - pop-up table fix `b394ab3` is the resolution; BUG-009 closed.
  - evidence: `work/playtest/m0f-2026-10-17/matched_state/bug009_fresh_0bddba78/`.
- [TODO] QA-014 (emulator) — valid elevator/pre-transition reproducer
  - capture states **before** the black screen with the same mGBA version/build
    and verify loader warnings/CPU mode; include a cold-boot route if needed.
  - matched normal/shifted/reordered states at the same transition; otherwise
    BUG-010 is not actionable.
- [DOING @dev1] BUG-010 (playtest) — shifted elevator hard freeze / black screen
  - candidate `0bddba78...` loading `elevator_01.ss0` frame 11274
    `event=4 area=0 room=61 main=4 s1=2 s2=0x100 disp=0x1500 active_oam=3`
    goes pure black, stops frame callbacks after ~60 frames; A/Start/Right/Up
    cannot recover.  Normal `elevator_02.ss0` same area/room/event/main but
    `disp=0x9700`, visible and advancing.
  - handoff: `work/playtest/m0f-2026-10-17/HANDOFF_ELEVATOR.md`;
    evidence `elevator_problem/`; normal_saves has pause/status/map/save/load/
    navigation/boss/game-over states.
  - M0f is blocked by this; QA-012 coverage matrix is paused.
  - **state is not a valid reproducer**: mGBA state v0x01000007, candidate
    romCrc; loader restores ARM state at `PC=0x0809680C` (inside padded
    `EndingBslCrashing`), Thumb bytes -> illegal opcode `21038968`; old
    `a822...` fails identically.  The `.ss0` was captured after the black
    screen / mid-transition, not at a stable pre-transition frame.  Normal
    reference is a different state version/size and route.
  - next: recapture a valid pre-transition state (or cold-boot route) in the
    same emulator/build; verify `mCoreLoadStateNamed` has no "different game"
    warning and CPU is at a game PC/Thumb state.  Only then classify source.
  - Do not call M0 PASS; no source patch from the invalid state.
- [PARK] BUG-008 (shift/engine) — BizHawk file-select/VBlank compatibility
  - Observed BizHawk-only: normal and reordered are identical for 701
    frames; first divergence at frame 401
    immediately after the single-frame A at 400. normal/reordered go
    `1C00 -> 1E00`; shifted stays `1C00 / 0007 / 0003 / 0000` through 700.
    No k=-10..+10 shift matches; same SaveRAM `7E6591CD...`, no per-build
    offset. Evidence:
    `work/playtest/m0f-2026-10-17/tas/coldboot_parity/`.
  - mGBA 0.11 control (same `common.SaveRAM`, BIOS, full baseline input)
    does **not** reproduce: normal and shifted normalized traces are identical;
    file-select A is at mGBA frame 824 and both transition `1C00 -> 1E00` at
    mGBA frame 837.  So the BizHawk 2.3 failure is currently
    emulator-core/timing-specific, not proven source; do not patch blindly.
  - BizHawk core identified: EmuHawk 2.3.0.1, mgba.dll SHA1
    `4109E16135B2F44A4E8EF046ACD99EAB8600AC4A` = mGBA 0.6.x branch (not
    0.10/0.11).  Per-build 400/401 states and logs are in
    `work/playtest/m0f-2026-10-17/tas/bizhawk_400_401/`.
  - state decoder result: BizState 1.03 -> mGBA 0.6.3 state v2; frames/ROM CRCs
    match, but normal and shifted snapshots are at **different CPU phases**.
    normal f400/f401 PC=0x1C/CPSR=0x92 (IRQ); shifted PC=0x60/0x24,
    CPSR=0x8000009B (SVC); masterCycles shifted +2 (`...88` vs `...8A`).
    Same displayed state, different saved execution point; these snapshots
    alone cannot prove a source branch.
  - state consistency check: the shifted f400 and f401 `.State` files contain
    the **same game state** (`gFrameCounter=84`, `gInput=0xF077`,
    `gChanged=0xFC03`); normal advances `gFrameCounter=99 -> 100` with
    `gInput=0 -> A`.  The BizHawk frame trailer (400/401) does not match the
    core game frame for the shifted states, so the 398-403 register trace is
    not at the A-handler decision.  This invalidates the state/trace
    comparison; no source conclusion.
  - live trace v2 confirms shifted `gFrameCounter=84` frozen from emu 398-403,
    `gInput=0xF077`, PC in BIOS context; normal advances 97..102 and receives A
    at 401.  This is a real BizHawk 2.3/mGBA 0.6 freeze, not a state-marking
    artifact.  mGBA 0.11 cold boot is clean.
  - BizHawk 2.3.2/mGBA 0.7.2 also fails with the same frozen game counter 84;
    mGBA 0.11 standalone passes.  The problem is in the BizHawk core path, not
    an old-0.6-only issue.
  - state IO at the trace point: normal IE=0x2401 (VBlank on), callback
    FileSelectVblank+1; shifted IE=0x2400 (VBlank cleared), callback
    0x0809C30A.  Shifted is at game frame 84, normal at 99, so this is not yet
    a same-phase comparison.
  - game84 comparison: normal `VBlankReq=0, callback 0x0809E9E1
    (FileSelectVblank+1)`; shifted `VBlankReq=1, callback 0x0809C30A`, then
    IE `0x2401 -> 0x2400` and SVC.  Frames 78-83 match, so the divergence is
    the game-frame-84 VBlank transition.  `0x0809C30A` is inside normal
    `CutsceneBslExplodingInit`, not a callback; the shifted FileSelectVblank
    literal itself is correct (`0x0809F9E1`).
  - next: BizHawk watchpoint on `gVBlankCallback` (0x030019C4) at game frame
    84 with writer PC/LR/stack, or live PC/LR trace at 84.  Do not patch from
    the state value alone.
  - NEW scope: mGBA 0.7.2 **standalone** with frame-synced baseline input does
    not reproduce through VB700 and sees **no `0x030019C4` write**; mGBA
    0.10.5/0.11 also pass.  BizHawk 2.3.0.1 and 2.3.2 both fail.  The
    source/data relocation conclusion is **not confirmed**; it is BizHawk-only
    VBlank/callback corruption with an unknown writer.
  - next: instrument BizHawk's MGBAHawk core with a `0x030019C4` write
    watchpoint, or use mGBA 0.11 standalone as the authoritative shiftability
    emulator and document BizHawk 2.3.x as a compatibility issue.  Do not
    patch source without the writer.
  - keep BUG-008 open; do not mask with input offset.

  - DECISION A (2026-10-18): mGBA 0.11 standalone is authoritative for M0;
    BizHawk 2.3.0.1/2.3.2 mGBA cores are a known compatibility issue.  BUG-008
    is parked (source relocation unconfirmed; writer unknown); no source patch.
  - M0f final mGBA handoff:
    `work/playtest/m0f-2026-10-17/mgba-final/` (shifted `a822b2d8...`,
    normal `ca33f434...`, reordered `af62233e...`, common save `C34B0F60...`).
    Final human `PLAYTEST-PASS` in mGBA 0.11 is still pending.
- [DONE] BUG-006 (playtest) — shifted fresh map objective UI missing
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
  - LANDED `462d803`: `tools/shift/gen_map_oam_blob.py` generates the blob
    as `u32[16558]`; 501 pointer words are same-object address expressions
    (target offset, not pointer-word offset), all other words verbatim.
  - normal SHA1 `ca33f4348c2c05dd330d37b97e2c5a69531dfe87`; shifted build
    SHA1 `a822b2d82a6501b7d6caa74211f3b7079c7be885`, exactly the validated
    temporary-patch artifact. 501/501 pointers are baseline+0x1000; 0 stale,
    0 outside, 16057 non-pointer words unchanged.
  - automatic gates: `shift-input`, `shift-input-30k`, `screen-diff`,
    `oam-diff` 6/6, `shift-check`, `shift-start`, audit, strict relocs and
    smoke all PASS.
  - controlled pair: fixed shifted SHA equals the patched artifact that
    produced active_oam 22/29/51 and after/final screenshots byte-identical
    to normal; fixed candidate at
    `work/playtest/m0f-2026-10-17/fixed/mf_us_m0f_shifted_fixed.gba`.
  - M0f still needs the human retest; M0 is not DONE and M1 does not start.
- [DONE] QA-010 (emulator) — full 259k local differential
  - normal/shifted/reordered all match at SCREEN/OAM 300/600/900/1059/4000/
    30000 and at `INPUT_FINAL` (`frame_counter=61634 disp=0x5F00 main=1 s1=2
    s2=256`).
  - QA-010a landed `0300d80`: modulo-65536 liveness delta; normal/shifted/
    reordered full 259k now exit 0 with identical checkpoints/final state.
    The full input stays local (`work/playtest`), not committed.
- [DONE] QA-010a (emulator) — long-input liveness and full differential
  - `0300d80` wrap-aware harness: full 259k normal/shifted/reordered exit 0,
    `INPUT_FINAL frame_counter=61634 disp=0x5F00 main=1 s1=2 s2=256`.
  - 4k/30k/screen/OAM gates pass after the change; full input remains local.
- [DONE] QA-013 (emulator) — event-progress telemetry and parity
  - `gEventCounter` (0x03000B87) is the saved u8 high-water event marker;
    `sEventLocationAndNavigationInfo`/`sPauseDebugEventNames` define the
    allowed event order and names.
  - add `EVENT frame=... counter=... area=... room=... nav=...` at input
    checkpoints and `EVENTCHG frame=... old=... new=...` on every event
    transition; compare normal/shifted/reordered event sequences, not only
    final state.
  - event counter is monotonic, not a per-event flag set; document that logs
    and independent flags cannot be inferred from it.
  - run 30k committed and full 259k local; add an `event-diff` target.
  - `EVENT`/`EVENTCHG` telemetry + `event-diff.py` + `event-diff` target
    landed `d9d3f96`; 30k gate passes (trivially 0 transitions).
  - full 259k baseline also has `gEventCounter=0` throughout: it is a movement/
    visual route, not a story-event route.  Need a story fixture that triggers
    the important events (e.g. matched normal recording ending at event=3).
  - story-route three-version pass: normal/shifted/reordered frame-139 states
    from SaveRAM `4FD0...` + same input all reach event=3 at relative 21511
    (`21649` absolute), `FINAL_EVENT counter=3 area=0 room=16 nav=1`.
    `FINAL_OAM count=96 hash=53ae6710c2f82951`, `FINAL_SCREEN
    5ab8765608532bbf`; PAL/VRAM/IO/EWRAM final dumps byte-identical.
    IWRAM differs only by code/ROM addresses (normalized diff still to file).
  - reordered frame-139 state supplied and works; final `--final`/dump-prefix
    harness support landed (`4c61351`).
  - remaining coverage gaps: pause/status, map/save/load, other Navigation
    dialogs/rooms, intro beyond start, ending and game over.  No M0 PASS yet.
  - next: extend the route/UI matrix for those paths; normalize IWRAM for the
    shift/reorder ROM pointers.
- [DONE] QA-013a (emulator) — story-route event parity fixture
  - capture/replay a normal route that sets the key story/event IDs, then run
    shifted from the same save/route and compare `EVENTCHG` sequences, not just
    final state.
  - harness `--state`/`--save` support landed.  Matching **4FD087E9...**
    normal/shifted frame-139 states from Nintendo Presents reproduce:
    `EVENTCHG 0->1->2->3` (relative 12610/16601/19039); event logs SHA1
    `643E1FC9...` identical; `EVENT-DIFF: PASS (checkpoints=74,
    transitions=3)`.
  - the earlier missing 2->3 was a SaveRAM/start-state mismatch, not event
    parity.  Story fixture files:
    `story_route/{normal,shifted}_start_4fd0_139.state` + from139 input.
  - baseline movement TAS still has event counter 0; do not use it for story
    coverage.
- [PARK] QA-012 (emulator) — M0 fresh-path room/dialog coverage matrix (paused: BUG-010)
  - run normal/shifted/reordered from matched saves/states through all rooms,
    Navigation Room dialogs, pause/map/status, save/load, intro/ending and
    game-over paths; compare OAM/PAL/VRAM/IO and normalized IWRAM/EWRAM.
  - any shifted-only difference becomes a BUG; M0 sign-off requires this
    matrix plus the fresh manual route, not only the controlled map.
  - depends on BUG-009; run after the current fix lands.  Do not close M0 on a
    single controlled path.
- [TODO] QA-004 (tools) — scanner for 2-byte/4-byte pointer-like data in raw
  blobs (the BUG-003/004/005/006/009 class); no raw pointer table may remain
  hidden behind a `data` classification.
- [TODO] QA-009 (emulator) — checkpoint memory parity (OAM/PAL/VRAM/IO exact;
  IWRAM/EWRAM normalized); feeds QA-012.
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

- [DONE] HACK-002 (GDD) — content ID registry and save-version plan
  - `docs/design/content-ids.md`: Pulse = appended event `0x6F`; event block
    `0x6E–0x77`, `EVENT_END=0x78`; Test Area 1 rooms 0–4/doors 0–9; save
    version unchanged; no `Equipment` bit or `SaveFile` resize.
  - blocking follow-up for HACK-004a2: broad `>= EVENT_ORBIT_CHANGE_IMPLEMENTED`
    checks disable the save/navigation/recharge pads after `0x6F`; fix before
    M1 sign-off.
- [DONE] HACK-003a (tools) — harden content pipeline before arbitrary rooms
  - `gDecompClipdataMap` is 1024 u16 (`0x800`), not 6144; reject rooms above
    1024 blocks or resize the decoder buffer
  - enforce spriteset-slot/`SPRITESET_IDX` encoding so `sprite_id` cannot be
    silently dropped; add regression cases
  - HACK-003 scaffold landed `dfe4b5a`: `content-check` PASS, synthetic
    fixture, `docs/content-pipeline.md`; bg3/palettes/composition/scripts are
    documented gaps
  - LANDED `9ad586e`: clipdata capped at 1024 blocks; table/direct sprite
    record encoding + decode round-trip; `content-check` PASS; docs updated.
  - HACK-004a2 may now start with Test Area 1 rooms; still document bg3,
    palettes, composition/scripts and secondary-sprite tables as pipeline gaps.
- [DONE] HACK-003 (baseline) — content pipeline: Tiled/PNG → room data
- [DONE] HACK-004a1 (content) — five-room blockout source assets
  - `1d3d03a`: synthetic tileset + 5 Tiled maps/manifests under
    `hack/content/tiled/`; 12 doors, 12 spawns, camera scrolls; all rooms
    ≤450 blocks; `check_blockout.py` and `content-check` PASS.
  - generated `hack/gen/rooms/` stays ignored; README has the HACK-004a2
    integration checklist. Door IDs 10/11 are a provisional post-boss return
    pair and need design sign-off before the 13-entry door table is committed.
- [PARK] HACK-004a2 (engine/content) — integrate 5 Test Area 1 rooms (paused: M0 file-select parity)
  - extend `sTest1RoomEntries` to 5 and `sTest1Doors` to 13; room/door data
    promotion needs an ADR because `src/data` is baseline-owned
  - resolve tileset 0, bg0/dark-room handling, spawn tables, entry warp
  - fix broad `>= EVENT_ORBIT_CHANGE_IMPLEMENTED` checks before M1

- [TODO] PLAYTEST-001 (human) — M1 blockout playtest  [deps: HACK-004a2]
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
- HACK-002 is decided in `docs/design/content-ids.md`; the save-pad broad-check
  fix remains a HACK-004a2 blocker.
- The 3 `possible` blobs need a data model before SHIFT-006 is complete.
