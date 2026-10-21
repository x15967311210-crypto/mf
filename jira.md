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

Last landed: SHIFT-001/002/003/004/005/005b/005c/006a/006b1/006b2/006b3/006b4/006b5/006b6/006b7/006c/007/008,
QA-001/002/003/005/006, BUG-001/002/003/004/005/006 (harness, audit, symbol
map, blob classification, literal and C-literal rewrites, raw FrameData/Sa-X/
intro/popup descriptor/map-OAM relocation, padded and section-reordered boot,
Start/file-select gate, headless TAS input 4k/30k, screenshot/OAM parity,
578/600 and input/visual parity), PLAYTEST-000 (controlled map pass; full M0 reopened), and
HACK-001/001a/006 (GDD, layout, Cantor), HACK-008a/008b/008c1/008c2/008d1/008d2/008d3/008d4a/008d4b
(ID/text/overlay/generated Entry Ledge room, scroll, message and sprite tables + entry warp and liveness gate), QA-020 (native normal/shifted/
reordered full TAS and Any%), and PLAYTEST-000 (M0 human PASS).  Details in
`git log`.

---

## Phase S0 — behavior harness

- [TODO] SHIFT-001a (baseline) — add title/new-game/pause/save scenarios
- [TODO] SHIFT-001b (emulator) — room-sweep scenario and telemetry mailbox
- [DONE] QA-002/QA-003 (emulator) — headless TAS input replay + shifted gate
  - committed 4k fixture + `INPUT_CHECK` assertions; `make test` runs it
  - `shift-input` runs the same 4k input against the shifted build; PASS
  - full 259k input stays manual/BizHawk; manual playtest remains extra
  - landed `c4312f0` + `75d94bc`; fixtures
    `tests/emulator/inputs/baseline_first4000.input` / `.expected`
- [TODO] QA-004 (tools) — scanner for 2-byte/4-byte pointer-like data in raw
  blobs (the BUG-003/004/005/006/009 class)
  - find 2-byte-aligned embedded `FrameData`/pointer tables; prototype found
    the BUG-003/004 tables but the tool/report is not committed yet
  - no raw pointer table may remain hidden behind a `data` classification
- [DONE] QA-024 (tools) — host-side RoomRleDecompress unit-test harness
  - `tests/host/test.h`, `tests/host/room_rle_test.c`, `make host-test`
    (also `make -f Makefile.shift host-test`); 33/33 checks in ~1s, no
    emulator, baserom, data/ or ARM toolchain.
  - links the real `RoomRleDecompress` from `src/room.c` using host cc,
    `-ffunction-sections -fdata-sections -Wl,--gc-sections`; no algorithm
    duplication, synthetic vectors only.
  - coverage: type 0 size codes, type 1/type>1 headers, 8/16-bit literal
    and run modes, two-pass interleaving.
  - normal SHA stays `ca33f434...`; landed `904831c`.
- [DONE] QA-025 (tools) — host harness: sprite spawn pure logic
  - `tests/host/sprite_spawn_test.c`; 148/148 checks, linked against the real
    `src/sprite.c` with host cc + `--gc-sections`; only fixture globals
    (`gSpriteData`, spriteset id/gfx arrays) are defined by the test.
  - covers `SpriteSpawnPrimary`, `SpriteSpawnSecondary` and
    `SpriteInitPrimary`: exact fields, `statusToAdd`, hidden `0x80`,
    spriteset index `>0x10`, first-free/full-table, no clobber.
  - engine note: `SpriteSpawnPrimary` stores explicit id/gfx verbatim and does
    **no** spriteset lookup; the `0x80`/`>0x10` rules live in
    `SpriteInitPrimary`, so both are tested.
  - `make host-test` now runs both suites: `33/33` + `148/148`, ~1.4s;
    normal SHA stays `ca33f434...`; landed `ba737b4`.
- [DONE] QA-026 (tools) — host harness: timer state machine + fixed-point
  - `tests/host/timer_test.c` (47/47) and `tests/host/fixed_point_test.c`
    (27/27), linked against the real `src/in_game_timer.c` and
    `src/fixed_point.c` with host cc + `--gc-sections`; test-only globals.
  - `make host-test` now runs four suites: 33 + 148 + 47 + 27 = 255 checks,
    ~1.5s; normal SHA stays `ca33f434...`; landed `15170df`.
  - engine note: `InGameTimerUpdate` adds an extra frame in the hour-rollover
    path, so `00:59:59:63 -> 01:00:00:01`, not `01:00:00:00`.  The test
    locks the current behavior; review before changing it (normal ROM is the
    baseline).  The 99-hour cap clamps to `99:59:59:59` and sets the flag.
- [TODO] QA-027 (tools) — host harness: save validation/checksum
  - `Sram_CheckLoadSaveFile` / `Sram_ChecLoadSaveFileWithBlank` are still in
    `asm/disasm_0x0807e678.s`; `SramCheckInternal` is static and
    GBA-register bound.  This needs a C decomp/pure helper first, without
    changing normal ROM behavior; then add `tests/host/save_test.c`.
  - do not duplicate the algorithm in the test; synthetic buffers only.
  - keep host tests as a fast pre-gate; native/behavior suite remains the
    authority.
- [TODO] QA-028 (tools/qa) — settle window restarts on every new byte pair
  - during room transitions the two cores are continuously one frame apart in
    copy phase, so `--settle N` never closes and a run that matches all
    durable state fields can still report `PARITY: FAIL` (223045 EWRAM,
    23100-frame run at 223100 with VRAM `0x4B0B`).
  - use a duration/state-field criterion (e.g. compare disp/main/event/room
    or require the same byte pair to persist) instead of only "no new pair".
  - do not weaken OAM/PAL/VRAM durable checks.
- [DONE @qa] QA-029 (emulator) — BUG-020 cutscene callback/state trace at 332884
  - normal: `disp=1800`, `nextOam=0`, LR BIOS; shifted: `disp=4000`,
    `nextOam=20`, executing `SpecialCutsceneDrawOam` at 332884.
  - `gOamData` ends at `0x030011E8`, exactly where shifted IWRAM corrupts at
    332885; this is an OAM draw overflow after the cutscene reset was missed.
  - trace who should reset `gNextOamSlot` / clear the VBlank cutscene callback
    at the ending transition; compare `gCurrentCutscene=0x80`,
    `gSubGameMode1/2`, `gMainGameMode`, callback pointers and the
    `CutsceneElevatorMonologue` entry/exit.  Do not chase data pointers.
  - **result**: VBlank callback at 332883 is `unk_99940` in both;
    at 332884 normal switches to `EndingBslCrashingVblank`
    (`0x08095C55`), shifted stays `unk_99940` (shifted `0x0809A941`).
    `gNextOamSlot` is 6 in both at 332883; at 332884 normal 0, shifted 20.
    Normal therefore completes `EndingHandler`/`EndingBslCrashingInit` and
    resets OAM, while shifted starts `SpecialCutsceneDrawAllOam` from slot
    20 and overflows `gOamData` at 0x11E8.
  - **timing conclusion (2026-10-20)**: at 332883 both states are still
    identical (`frame16=65409`, `gNextOamSlot=6`, audio channels identical).
    At 332884 normal completes the ending init/draw and reaches
    `EndingBslCrashingVblank` with `gNextOamSlot=0`; shifted is still inside
    `SpecialCutsceneDrawAllOam`/`DrawOam` with `gNextOamSlot=20`.  The OAM
    frame data at the active slot pointers is byte-identical normal/+0x1000,
    so this is **not a data relocation**.  At 332885 shifted `frame16` is
    still 65409 while normal is 65410: the shifted main-loop iteration
    overruns the video frame at the ending transition.
  - **cycle/VCOUNT trace (2026-10-20)**: mGBA watch trace from the 332883
    states (frame 332884):
    - normal: cycles `36845..267239`, VCOUNT `189..148`, 5645 stores;
      `EndingBslCrashingInit+0x14A` 1024 stores; ends with callback switched
      and `gNextOamSlot=0`.
    - shifted: cycles `36845..280888`, VCOUNT `189..159`, 4680 stores;
      `+0x82` 128 stores, then `SpecialCutsceneDrawOam`; no init completion;
      frame is **+13,649 cycles** and still active.
    - next frame starts at cycle 281065 normal vs 314526 shifted (+33,461).
    - normal init runs the `+0x82` palette fill (0x05000000..0x050001FC,
      128 stores, cycles 250338..251104), then draw, then the `+0x14A`
      VRAM fill (0x0600D000..0x0600DFFC, 1024 stores, cycles
      264168..267239).  Shifted runs the same palette fill, then gets stuck
      in `SpecialCutsceneDrawOam` and **never reaches +0x14A**.
    - shifted OAM writes 462 vs normal 403 in that frame; first OAM values
      differ (normal 0 vs shifted 15), and shifted's only `gNextOamSlot` write
      is 20; it overflows before `DrawAll` resets.
  - **slot/gNonGameplayRam watch trace**: the setup writes to the 20
    `SpecialCutsceneOam` slots are identical normal/shifted modulo the
    `+0x1c/+0x20` pointer relocations; no setup data difference.
    At 332884 end, slots 16/17/18 differ only in
    `animationDurationCounter` (`+0x12`): normal `1/1/1`, shifted `1/0/0`
    (plus the expected `+0x1c/+0x20` `+0x1000`).
  - normal writes `+0x12` for slots 16/17/18 at cycles
    `256029/258555/261089`; shifted writes only slot 16 at `260241`, then the
    frame ends inside `SpecialCutsceneDrawOam` before slots 17/18.
  - **actual data root found (2026-10-20)**: the pOam table at
    `0x08636050` (slot 16) is inside `sBlob_6131c8_63a19c`.  Its nested
    `FrameData.pFrame` words are still normal addresses in shifted
    (`0x08635A5A` ...), should be `+0x1000`; `SpecialCutsceneDrawOam` follows
    the raw pFrame to normal-layout data, reads different OAM bytes, and
    loops/overruns.  The pOam pointer itself is correctly `+0x1000`; the
    earlier slot `+0x12`/cycle differences are downstream of this.
  - fix: add `sBlob_6131c8_63a19c` to the sparse-pointer generator with
    **inside-blob-only** relocation (leave non-pointer outside words
    literal), preserving normal SHA; then test 332880 -> 339001.  This is the
    same class as BUG-019, not a timing-only bug.
  - this is a timing/control-flow overrun, not a data relocation.  The
    shifted init does not execute the same `+0x14A` store loop as normal;
    inspect `EndingBslCrashingInit` +0x82/+0x14A branch/IRQ interaction, or
    add a shift-only OAM-slot guard.  Do not add a normal-ROM-only patch
    without a baseline decision and do not chase another blob pointer.
  - landed `919c8cb` (trace); follow-up `3a0e6cd` relocated the inside-blob
    pFrame words in `sBlob_6131c8_63a19c` (BUG-020) per the root cause above.
- [DONE] BUILD-001 (tools) — reproducible toolchain checks
  - `tools/doctor.py` (full / `--source-only` / `--self-check`),
    `tools/setup_agbcc.sh`, `tools/agbcc-version` pinned at
    `da598c1d918402c42c0c0d7128ba14567f3175e9`, `tools/baserom.sha1`
    `ca33f434...`.
  - `make doctor` checks Python/host commands/ARM binutils (TOOLCHAIN
    semantics)/pinned agbcc/baserom; `make doctor-source` is baserom- and
    agbcc-free for public CI; `make setup` installs the pin.
  - normal SHA stays `ca33f434...`; landed `6069348`.
- [DONE] BUILD-002 (tools) — single build entry point
  - `mk/shift.mk` now holds the shift/audit/test targets; the top-level
    `Makefile` includes it.  `Makefile.shift` is a 44-line compatibility
    wrapper that forwards goals/vars to `make -f Makefile` and keeps the old
    default (`audit`), not a ROM build.
  - every target is available as `make <target>`; legacy
    `make -f Makefile.shift <target>` still works.  No duplicate
    `all`/`help`/`host-test`; `make help` lists both.
  - acceptance: doctor-source, host-test, audit, smoke, wrapper
    audit/smoke/check-relocs-strict, shift-build, `make -j20 check` all pass;
    normal SHA `ca33f434...`; landed `0e8b738`.
- [DONE] BUILD-003 (tools) — data tree manifest + cache verifier
  - `tools/data_manifest.py` + committed `tools/data-manifest.json`
    (3735 files, 6,947,008 bytes, schema 1, relative POSIX paths).
  - `make data-manifest`, `make data-verify` (fails on missing/extra/size/
    SHA256), `make data-cache-key`
    (`<baserom-sha1>-<manifest-sha256>`).
  - self-check 14/14; clean extractor output verifies; normal SHA
    `ca33f434...`; landed `0f2bce1`.
  - do not commit `data/`, `sound/direct_sound_samples/` or baserom.
- [DONE] BUILD-004 (ci/tools) — public/protected CI layers + symbols
  - public: `tools/ci/public_gate.sh` + `.github/workflows/public.yml`
    (ubuntu-latest, no baserom/agbcc/toolchain); runs doctor-source,
    host-test, content-check and all Python self-checks.  `PUBLIC-CI: PASS`.
  - protected: `tools/ci/protected_gate.sh` runs doctor, `data-verify`,
    `make check`, strict relocs, host tests, postlink report and optionally
    `tools/headless/ci_gate.sh`; `tools/ci/collect_symbols.sh` emits a
    text-only artifact (`mf_us.map`, `symbols.json`, `abs_refs.json`,
    `SHA256SUMS`, `BUILD.txt`).  `make public-gate`, `make protected-gate`,
    `make collect-symbols`; docs in `tools/ci/README.md`.
  - `data-verify` uses the BUILD-003 manifest/cache key; no silent
    regeneration.  `headless.yml` remains the human-owned self-hosted job and
    was not modified.
  - normal SHA `ca33f434...`; landed `4eaa1d6`.
  - **2026-10-20 push status**: fork `x15967311210-crypto/mf` `hack` is at
    `b068c53`; `public-gate` run 39413631873 **success** (12s, PUBLIC-CI
    PASS).  `headless-parity` run 39413631823 is **queued**: no self-hosted
    linux/x64 runner picked it up.  The local `headless.yml`/`tools/headless`
    changes are still uncommitted, so the remote run uses the committed
    `94c78c9` version, not `HEADLESS_SHIFT_FRAMES=339001`.
- [DONE] BUILD-005 (ci) — protected runner online and validated
  - runner `mf-wsl-01` is online (`self-hosted,linux,x64`); repository
    variables set: `MF_BASEROM`, `HEADLESS_BIOS`, `HEADLESS_MOVIE`,
    `MF_TOOLCHAIN=/home/x1596/.local/bin`, `HEADLESS_SHIFT_FRAMES=339001`.
  - workflow fixed to check ARM `as/ld/objcopy` (not `arm-none-eabi-gcc`),
    install pinned agbcc via `make setup-agbcc`, verify `data/` via
    `make data-verify`, and invoke `build06.sh` with bash; commits
    `2b4f465` / `c864a45`.
  - validation: `public-gate` success 13s; `headless-parity` push (early 30k)
    success 4m17s; `workflow_dispatch` full 339001 normal golden PASS and
    shifted first diff **114671** (BUG-016), as expected.  The gate is red
    until BUG-016 is fixed; that is correct, not a CI setup failure.
  - `gh` in this checkout defaults to upstream `metroidret/mf`; use
    `-R x15967311210-crypto/mf` or `gh repo set-default` for fork runs.
  - `tests/emulator/harness.c` remains uncommitted and was not touched.
- [DONE] BUILD-006 (tools) — headless checkpoint state save/load/resume
  - runner flags `--state-in`, `--diff-state-in`, `--state-out`,
    `--diff-state-out`, `--start-frame`; real mGBA `SAVESTATE_SAVEDATA` via
    `BizStartGetState`/`BizFinishGetState`/`BizPutState`; commit `097dbf1`.
  - 0..115000 diff PASS in 208.5 s with A/B states saved; resume at 115000
    reproduces BUG-017 frame 117234 in **3.85 s** (56x).  Single-core resume
    matches an uninterrupted run byte-for-byte in all dumped regions.
  - states + evidence: `work/playtest/m0f-2026-10-17/tas/bug017_117234/`
    (`states/n_115000.state`, `states/s_115000.state`,
    `BUG017_RESULT.md`, `diff_117234/`).  Shifted state is tied to
    `e5d202c8...`; recapture after ROM-changing fixes if needed.
  - policy D-012: checkpoint-first iteration, full 339001 only after the
    incremental chunks pass the previous failure point.
- [DONE] BUILD-007 (tools) — settle-aware headless diff
  - `--settle N` in `mf_bizhawk_linux --diff`; `tools/headless/ci_gate.sh`
    defaults `HEADLESS_SETTLE=8`; README documents the window-end caveat.
  - control 200k->223046 still fails at 223045; settle 8 ignores the transient
    and reports the durable diff at 226117 (OAM 0x30, normal room 40 /
    shifted room 24).  Commit `d57e081`; normal SHA `ca33f434...`.
- [DONE] BUILD-008 (tools) — make auto-detects the ARM binutils path
  - non-interactive shells do not source `.bashrc`/`.profile`, so make now
    falls back to `$(HOME)/.local/bin/arm-none-eabi-` when `TOOLCHAIN` was not
    explicitly set and `arm-none-eabi-as` is not on PATH; explicit overrides
    still win.  Commit `fe1f221`.
  - verified `env -u TOOLCHAIN PATH=/usr/bin:/bin make -j20 check` ->
    `mf_us.gba: OK`, `ca33f434...`; `make doctor` and the
    `Makefile.shift` wrapper PASS on the same clean PATH.

## Phase S2 — relocatable build

- [DONE] SHIFT-008 (tools) — section-reorder shift test
  - padding boot was already green (`SHIFT-CHECK: PASS`, 578/600); this entry
    added the section-reorder build and made both a repeatable gate.
  - landed `a1178d5`: `Makefile.shift` targets + `tools/shift/shift_test.py`
    (reorder layout build and boot check).
  - the entry was dropped in a later backlog sweep, which left the SHIFT-009 /
    SHIFT-010 dependencies dangling; the deps are real work, not placeholders.
- [DONE] PLAYTEST-000 (human) — M0 shiftable-boot playtest
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
    room-61 elevator state (BUG-010); M0 was not done.  QA-012 coverage was
    paused.
  - **PLAYTEST-PASS 2026-10-21**: human native QA-020 full 339001 PASS for
    normal, shifted and reordered; native Any% TAS also PASS at 259176 for
    all three.  Candidates: normal `ca33f434...`, shifted `5888a563...`,
    reordered `9dac0a4b...`.  Final state `DISPCNT=1900 main=9 s1=2 s2=0100
    event=109 area=0 room=63`; shifted callback `08098325` is the expected
    `+0x1000`.  Evidence:
    `work/playtest/m0f-2026-10-17/tas/qa020_latest/` and `anypct_latest/`
    (`QA020_LATEST_RESULT.md`, `ANY_PCT_LATEST_RESULT.md`).  M0 is DONE.
- [DONE] QA-011 (emulator) — common file-select state parity (inconclusive)
  - mGBA f600 common state loads visually identically in normal/reordered/
    shifted (`1C00/7/3/0`, same framebuffer hash).
  - Execution-level replay is invalid: the state was captured mid-BIOS with
    saved code/IWRAM pointers.  Normal resumes; reordered and shifted freeze
    with PC in BIOS (`~0x38..0x68`, IRQ disabled).  Reordered is the control
    and fails too, so this cannot decide BUG-008.  mGBA 0.11 vs capture 0.10.5
    and the committed harness having no state option are contributing factors.
  - Do not use the mid-BIOS state or a per-build input offset as a gate.
  - landed `2c47fe9`; state-container analysis in
    `docs/shift-test-diagnosis.md` ("BUG-008 state-container finding").
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
  - landed `d160eaf` + `9ef2e57`; core matrix and scope in
    `docs/shift-test-diagnosis.md` ("BUG-008 emulator-core scope") and the
    M0 row in `docs/playtest.md`.
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
- [PARK] QA-014 (emulator) — valid elevator/pre-entry reproducer (deferred)
  - `pre-transition.ss0` is CPU-valid but the t0 image already shows the moving
    elevator/platform; it is post-entry and not matched to normal/reordered.
  - capture true pre-entry states in all three builds from the same SaveRAM,
    input and frame, before the platform starts; verify loader warnings/CPU
    mode; only then is BUG-010 actionable.
- [DONE] QA-017 (emulator) — pre-failure IRQ state/watchpoint
  - capture normal/shifted/reordered state at frame 384/385 (before
    `gVBlankCallback` corruption) from the native TAS, same BIOS/state.
  - use mGBA 0.6.3/0.7.2 (BizHawk BIOS) or an instrumented core to watch writes
    to `0x030019C4`/`gNonGameplayRam+0x540`; report writer PC/LR/value.
  - states/BIOS now available in `tas/bizhawk_bug008_watch/`:
    `state_{normal,shifted,reordered}_{384,385}.State`, BIOS
    `300C20DF...`.  BizHawk Lua cannot capture the writer; use mGBA
    0.6.3/0.7.2 or an instrumented core from the 384 state.
  - observed: shifted 384 callback `0x0809F9E1`, 385 `0x0809C30A`;
    normal/reordered remain `0x0809E9E1`.  Wrong write is between 384-385.
  - state loader reproduces all six states; shifted 385 also has
    `gHBlankCallback=0x88045C4F` clobbered.  Two adjacent callback words are
    overwritten -> multi-word overflow/copy, not a single setter; candidate
    `gNonGameplayRam` end at 0x030019C4 plus oversized DMA/copy.  Writer still
    not captured because the current libmgba lacks a usable store hook.
  - QA-017a: build mGBA 0.7.2 with GBAStore8/16/32 + DMA range logging,
    run shifted_384 one frame, normal/reordered controls; log writer PC/LR/SP.
  - QA-017a partial: states/BIOS validated; state trailer frame is one behind
    the core counter.  One-frame probes with 0/Right/Down/R did not reproduce;
    the write needs the real input rows 385 Right, 386 Up, 387 A and 4–8 frames.
    The existing libmgba has no store hook; patch `src/gba/memory.c`
    (`GBAStore8/16/32/Multiple`) and `src/gba/dma.c`, log
    `0x030019C0..0x030019CC`, run shifted/normal/reordered controls.  No writer
    captured yet.
  - QA-017b: finish instrumented build and input-correct run; do not source-patch
    until the writer is identified.
  - QA-017b partial: instrumented mGBA 0.7.2 built; from shifted_384 with
    Right/Up/A rows the callback stayed `0x0809F9E1` for 7 frames and no watched
    write fired (mGBA then segfaulted); normal/reordered controls stayed clean.
    Vanilla mGBA 0.7.2 does **not** reproduce the 384→385 corruption.
  - **writer captured in the native MGBAHawk hook**: frame 385 writes
    `0x030019C4` (low half `0xC70A`, then `0xC3`, then `0xC30A`) with
    PC `080A2380`, LR `080A2227`, SP `03007DFC`, CPSR `0000003F`; final
    callback becomes `0809C30A`.  This is inside the shifted
    `FileSelectDrawOam` OAM loop (`0x080A2248`); the destination pointer
    (`r7`/`r3`) overruns the 1024-byte `gOamData` buffer into
    `gVBlankCallback` at `0x030019C4`.  Inspect `gNextOamSlot`/MenuOam frame
    data/count and the `FileSelectDrawOam` destination calculation.
  - mGBA standalone did not reproduce; VBA-Next/native MGBAHawk does.  The
    source fix target is the OAM loop/count/pointer, not the callback setter.
  - checked `FileSelectSetUpAreaNameOam` table at normal 0x0879E944 /
    shifted 0x0879F944: code literal and all six language/case entries are
    correctly +0x1000.  So the simple "raw area-name table" hypothesis is not
    enough; inspect the actual MenuOam entry `pAnim`/count at 384/385 and the
    `FileSelectDrawOam` loop (`gNextOamSlot + sb`), plus other file-select
    frame-data pointers.  Engine dev2 hit its step limit; BUG-008 still DOING.
  - further check: area-name entries 19-21 at 384 carry valid shifted pAnim
    targets; their pFrame targets/counts are identical normal/shifted
    (1/26/6).  The simple pointer-table hypothesis is false.  Need the actual
    `r5/r7/r3/r9/sl`/`gNextOamSlot` at the writer store to see which entry/index
    makes `r7` reach 0x030019C4; add register logging to the MGBAHawk hook.
  - QA-017c: extend the native hook with r5/r7/r3/r9/sl/sb/gNextOamSlot at the
    watched store (and pAnim writes); capture the exact entry and count.
  - full writer registers: `r5=030016E8` (entry21), `r7=030019C6`,
    `r3=030019C0`, `r9=sb=0x160`, `sl=0x1F28`, `nextOamSlot=0x1B`;
    index 0x160+0x1B=0x17B -> destination 0x030019C0.  Entry21 `p5_14`
    (`pAnim`) is `0x08740024`, pFrame `0x0873FC12`, count `0x1F28`; at state
    384 entry21 pAnim was the valid `0x087417E0`, so pAnim is changed/stale
    before DrawOam.  Likely missing `+0x1000` in the pAnim/frame table or an
    earlier write; need writer for entry21 `pAnim` (`0x030016FC`) in the 384→385
    window.
  - QA-017d: hook writes to `0x030016FC`/MenuOam entry pAnim and report
    PC/LR/value; then fix the table.
  - corrected pAnim-target check: shifted `0x087417C0` **does** contain the
    normal prefix bytes (`caf37308...`), so pAnim/setup is correct.  But the
    first word is the **pFrame pointer `0x0873F3CA`**, which was not relocated
    inside raw `sBlob_73421e_prefix`; shifted should be `0x087403CA`.  At the
    old address the frame count is garbage (`sl=0x1F28`), causing the OAM loop
    to overrun into pAnim/callback.  This is a **prefix/blob pointer relocation
    bug**, not OAM-slot code or the pAnim table.
  - fix direction: model the pointer words inside
    `sBlob_73421e_prefix` (at least the record at prefix+0xC5A2, plus other
    frame records) as relocatable expressions while preserving the 2-byte
    aligned prefix layout and normal SHA1.  Then re-check pFrame/count.
  - next: capture the writer in BizHawk's VBA-Next/MGBAHawk path (the core that
    reproduces); mGBA standalone is not sufficient.  Do not source-patch until
    a reproducing core reports PC/LR/SP/value.
  - observed: shifted 384 callback `0x0809F9E1`, 385 `0x0809C30A`;
    normal/reordered remain `0x0809E9E1`.  Wrong write is between 384-385.
  - **FIX LANDED `1d5e422`**: `sBlob_73421e_prefix` is now a packed C
    struct with relocatable `pFileSelectFrame0`/`pFileSelectFrame1` fields at
    prefix+0xC5A2/0xC5B2; `tools/extractor.py` emits the matching split blobs.
    Normal SHA1 stays `ca33f434...`; shifted is `812d0090...`.
  - shifted prefix+0xC5A2 now holds `0x087403CA` (was `0x0873F3CA`); the
    pFrame target starts with count `6`, so the `sl=0x1F28` OAM-loop overrun
    can no longer reach `gVBlankCallback`.
  - automatic gates on the integration tree: audit, smoke, test, strict
    relocs, shift/start/input 4k/30k, screen/OAM diff, reorder all PASS.
  - **native 384/385 PASS**: candidate `812d0090...`, native BizHawk 2.3.2,
    mGBA core, normalized SaveRAM, 100% TAS: frames 384/385/386 callback
    `0809F9E1`, IE `2401`, PC `1C`, CPSR `92`; frame 401 `DISPCNT=1E00`.
    No Undefined transition.  BUG-008 is closed.
  - the full run still fails later at frame 22923; that is **BUG-012**, not a
    file-select regression.
- [DONE] QA-018 (emulator) — native TAS parity after BUG-008
  - run native Windows BizHawk 2.3.2, mGBA core, BIOS `300C20DF...`, normalized
    SaveRAM `FB611BD6...`, 100% TAS movie; no converted `.bk2` input and no
    per-build offsets.
  - builds in `work/playtest/m0f-2026-10-17/mgba-final-bug008/`: normal
    `ca33f434...`, shifted `812d0090...`, reordered `af62233e...`.
  - expected: frames 384/385 callback `0809F9E1`, no write to `030019C4`, no
    Undefined at 386, frame 401 `DISPCNT=1E00`, final 339001 normal/shifted
    `1900 0009 0002 0100 109 0 63 0`.
  - reordered still needs the separate BUG-011 room 23/14 check; do not gate it
    on BUG-008.
  - only after this passes can M0f/PLAYTEST-000 advance.
  - **result: PARTIAL**.  File-select 384/385/386/401 PASS, but shifted
    diverges at native TAS frame **22923**: callback `080967E0` (normal
    `0809A2C9`), `CPSR=40000092` vs `92`; frame 22924 IE lost / PC leaves IRQ,
    22925 Undefined, 22952 still black while normal `DISPCNT=9700`.
    full final checkpoint not reached.  Evidence:
    `tas/bug008_candidate_fine/BUG008_CANDIDATE_FINE.md` and logs.
  - parity remains FAIL because of BUG-012, not BUG-008.
- [DONE @windows] QA-020 (emulator) — full native TAS parity after BUG-013
  - current candidate `012a2c95089485ebd37d19e86717b666ccc00e09` (merged
    `424fd7f`), BIOS `300C20DF...`, normalized SaveRAM `FB611BD6...`,
    same 100% TAS.
  - **headless full gate 2026-10-20** (`tools/headless/ci_gate.sh`,
    movie-native mGBA 0.6, 339001 frames, `HEADLESS_SHIFT_FRAMES=339001`):
    normal golden **PASS**, ending `1900 0009 0002 0100 109 0 63 0`.
    shifted first diff **114671**: OAM offset 0, a=`80` b=`02`; state
    `1600 0004 0002 0100 43 0 20 0`; normal PC `1C`/CPSR `92`, shifted
    PC `60`/CPSR `8000009B` (undefined/exception).  reordered first diff
    **223045**: EWRAM `0x32290`, a=`41` b=`72`, room 14/event 81 — BUG-011.
    The strict CI gate is therefore red for shifted and reordered.
  - evidence: `tools/headless/out/full/` (ignored):
    `normal_339001_*`, `diff_shift/shift_{a,b}_114671_*`,
    `diff_reorder/reorder_{a,b}_223045_*`; timings normal 302.6s,
    shift diff 208.7s, reorder diff 422.0s.
  - **after BUG-016 fix `1f01180`**: shifted 115000 PASS; full 339001 first
    diff moved to **117234** (BUG-017, EWRAM `0x02000000` zero-fill).
    Re-run full after BUG-017; reordered remains at 223045 (BUG-011).
  - **2026-10-20/21 headless full PASS**: with BUG-020 fixed, shifted
    `5888a563...` completes the full 339001-frame diff:
    `PARITY: PASS (339001 frames)` in 646.7 s, final state
    `main=9 sub1=2 frame16=5979` in both, and the 0/115k/200k/300k chunk
    ladder also passes.
  - **2026-10-21 reordered full PASS**: current reorder build
    `9dac0a4bcd6257d443a0c1a41b36f54000d1e2c3` (latest fixes, reorder
    layout PASS) completes normal vs reordered 0 -> 339001:
    `PARITY: PASS (339001 frames)` in 647.4 s; final state
    `main=9 sub1=2 frame16=5979` both.  BUG-011's old reordered 223045
    failure is gone.
  - This is the headless half of QA-020 for normal/shifted/reordered.
  - **native Windows 2026-10-21 PASS**: normal, shifted and reordered all
    reach 339001 with final `DISPCNT=1900 main=9 s1=2 s2=0100 event=109
    area=0 room=63`; shifted callback `08098325` (`+0x1000`).  Key
    checkpoints 384/385/386, 401, 22923/22924/22925 and 22952 PASS; no
    `LONG_BLACK`, all rc=0.  Any% TAS also PASS at 259176 for all three.
    Native core `4109E16135B2F44A4E8EF046ACD99EAB8600AC4A`; no EmuHawk
    left running.  Evidence: `tas/qa020_latest/`, `tas/anypct_latest/` and
    `mgba-final-latest/`.
  - **D-012 checkpoint ladder (2026-10-20)**: 115000 -> 150000 PASS;
    150000 -> 200000 PASS after BUG-018; 200000 -> 223040 PASS; 223040
    audio/channel state differs and the room-14 transition phase shifts at
    223048, leading to the room 23/14 branch at 223227.  Full 339001 not
    run.
  - **partial run on `2447dfb7...`**: 384/385/386 callback `0809F9E1`,
    401 `DISPCNT=1E00`, 22922/22923/22924/22925 `0809B2C9`, 22952
    `DISPCNT=9700`, 30000 state fields normal/shifted match.  This confirms
    BUG-012's 22923 fix in the full movie.
  - after 30000 the shifted display went black and the run was stopped before
    the next checkpoint; **no first-black frame or 30000 state was saved**.
    That partial run predates the BUG-013 merge, so it must be repeated on
    `012a2c95` before treating the black as a current regression.
  - require 22923 callbacks `0809A2C9`/`0809B2C9`, both `CPSR=92`; no Undefined
    at 22924/22925; 22952 `DISPCNT=9700`; final 339001
    `1900 0009 0002 0100 109 0 63 0`; file-select 385/401 still PASS.
  - **local converted-input triage (not a gate)**: replaying
    `reseren-100.input` on `012a2c95` reaches 339001 with no persistent black.
    The only black frames after 30000 are 1-3 frame fades at
    55146, 55921-55923, 89885, 90392-90394, 125731, 126163-126165, etc.;
    normal shows the same black frames at the same positions with callback
    normal `080768A5` / shifted `080778A5` (the usual `+0x1000` shift).  Local
    final state is still gameplay (`DISPCNT=5F00` at 339000), so this does
    **not** prove TAS parity; it only suggests the native stop was a normal
    fade, not a persistent shifted black screen.
  - next run: do not stop on a single black frame; require a continuous
    black run (e.g. >60 frames) or compare normal at the same frame, and save
    a state at 30000 plus the last healthy/first-long-black frames.
  - evidence: `tas/bug012c_full/` (`BUG012C_PARTIAL.md`, logs, states).
  - reordered still needs BUG-011 room 23/14; do not gate it on BUG-012.
- [DONE] QA-022 (emulator) — BUG-013b native verification
  - candidate `012a2c95089485ebd37d19e86717b666ccc00e09`; native BizHawk 2.3.2,
    BIOS `300C20DF...`, normalized SaveRAM `FB611BD6...`.
  - **PASS**: 2331 state -> 5000 clean (`callback=08094901`, `IE=2401`);
    idle 2238/2331/2332/2333/2400/5000 clean; 2238/2332 pOam counts sane
    (1..11, no 25100/61443/1008); focused 384/385/386/401 PASS;
    22923/22924/22925 `0809B2C9`/`CPSR=92`; 22952 `DISPCNT=9700`.
  - 2238/2239 screenshots are 242 bytes, but normal is also 242 at those
    frames; baseline transition, not a regression.
  - evidence: `tas/bug013b_state/`, `tas/bug013b_idle/`,
    `tas/bug013b_focus/`, `tas/bug013b_probe/`;
    `tas/bug013b_state/BUG013B_NATIVE_RESULT.md`.
  - no full 339001 TAS; that is QA-020.
  - pre-fix capture notes retained below for history.
  - candidate `c4b62c65378602b03f7144913fbf9d45140720fd`; state
    `tas/bug013_crash/shifted_2331.State`; no movie; same BIOS/SaveRAM.
  - run `work/playtest/m0f-2026-10-17/tools/bizhawk/bug013_2332_probe.lua`
    and return the 20-entry pOam/frame/pFrame/count table at 2331/2332/2333;
    identify the active table with count >20 and its pOam address.
  - save states 2332/2333 and screenshots; report the first pOam/count that
    pushes `gNextOamSlot` past 19; do not patch source.
  - **pre-fix capture done locally** (mGBA 0.7.2 core, same native state; the
    BizHawk `.State` is a zip whose `Core.bin` has a 4-byte BizHawk prefix):
    frame 2331 active slots 0..10 have pOam `0865CB38..0865D230`; the huge
    counts (`66`, `70`, `25100`, `61443`, `1008`) are not animation counts but
    **unrelocated pFrame pointers**.  The whole FrameData array is blob
    offsets `0x0D6C8..0x0DDE8` = 229 8-byte records: 31 were fixed by
    `da248e3`, 10 are zero, and **188 are still raw** (including slot 0
    frame 15 and every table from `0865CE00` onward).
  - a throwaway ROM patch adding `+0x1000` to exactly those 188 words made
    idle frames 2332..2351 healthy (`callback=08094901`, no IE loss, no
    invalid jump) and field-identical to normal.  This headless result was
    later confirmed by the native BUG-013b run above.
  - **post-fix candidate staged**: `mgba-final-bug013b/` shifted
    `012a2c95089485ebd37d19e86717b666ccc00e09` (source build from dev4
    `424fd7f`, originally `32d3513`), state `shifted_2331.State`.  Local
    mGBA 0.7.2 replay is clean through 120 frames; `BUG013B_RESULT.md` has
    the native checklist.
- [DONE] QA-019 (emulator) — capture 22923 gVBlankCallback writer
  - use the native MGBAHawk/BizHawk 2.3.2 path that reproduced BUG-008; watch
    `0x030019C4` and `0x030019C0..0x030019CC` over frames 22920-22930, same
    BIOS/SaveRAM/movie and candidate `812d0090...`.
  - save a state at 22922 (before the write) and log writer PC/LR/SP/value;
    compare normal and shifted.  Do not use a converted headless input.
  - if the write is an OAM/copy overflow, identify source table and hand it to
    BUG-012; do not patch IWRAM or the callback setter.
  - **closed by state inspection, not a write hook**: loading the native 22922
    state showed `R10=0xF164`, `R6=08664460`; the pOam table at
    `0x08663DD0` was the source.  Fixed by `df60f8f`.
- [DONE] QA-021 (emulator) — idle 2238 writer capture
  - native MGBAHawk store hook on `0x030019C4`, no movie/no input, state
    `shifted_2200`: writer `PC=08099F28`, `LR=08099D75`, value `0000C1A2`,
    `r3=030019C0`, `sl=0865A2E4`, `nextOamSlot=0x47`.
  - filed as BUG-013; callback setter/IRQ not patched.
  - landed `19193f1` (capture + BUG-013 record); follow-up fix `da248e3`
    (`src/data/new_file_intro_data.c`, `tools/extractor.py`).
- [DONE] QA-015 (emulator/tools) — native BizHawk TAS parity
  - native 100% TAS, normalized SaveRAM `FB611BD6...`: `PARITY: FAIL`.
  - shifted first behavior divergence frame 401 (`DISPCNT 1E00` vs `1C00`),
    state divergence at 600, then frozen through 339001 (known BUG-008
    file-select/BizHawk path).
  - reordered is identical through frame 223200; at 223300 `room=23` normal
    vs `room=14` reordered; final state differs.  Coarse trace only; refine
    223201-223300.
  - normal reaches the ending state at 339001.  Event counter is not QA-013a
    story evidence.
  - landed `9f4b502`; result section in `docs/shift-test-diagnosis.md`
    ("QA-015 native TAS parity result").
- [DONE] QA-016 (emulator) — refine reordered TAS room branch
  - run native BizHawk single-frame/checkpoint trace 223201-223300 for normal
    and reordered; capture first differing frame, PC/LR/SP, room/transition,
    OAM/VRAM/IO and the last matching state.
  - feed BUG-011; do not patch source until the exact branch/table is proven.
  - next: run native normal/reordered fine trace 223201-223300 with PC/LR/SP
    and first-diff dumps; the 100-frame coarse interval is not enough for a
    source patch.
  - landed `b1b85c6`; fine trace in `docs/shift-test-diagnosis.md`
    ("BUG-011 fine trace"), feeding BUG-011's `tas/bizhawk_fine/` evidence.

- [DONE @dev17] BUG-011 (shift/reorder) — room-14 branch at TAS frame ~223045
  - native 100% TAS normal vs reordered: identical through 223200; at 223300
    normal `room=23`, reordered `room=14`; final state differs.
  - exact fine trace: loaded state at 223200 already differs in OAM/VRAM/IO
    (PAL same); first field divergence 223214 (normal s1=3, reordered s1=2);
    first room divergence 223227 (normal room=23, reordered room=14).
    At 223227 normal `disp=1800 s1=0 room=23`, reordered `disp=5F00 s1=2
    room=14`; PC both 0x1C, LR `0x1238` vs `0x1B8`, CPSR `0x20000092` vs
    `0x00000092`.  Saved per-frame dumps/states are in `tas/bizhawk_fine/`.
  - engine investigation: 223200 input/save/route match; OAM/VRAM dump
    difference is not trustworthy (dump inside onframeend); first trustworthy
    field diff is 223214 `s1`.  All word-aligned pointers into the reordered
    `.rodata` range appear relocated (43 word diffs); the divergence is in the
    BIOS IRQ/return path (`LR 0x1238` normal vs `0x01B8` reordered).  BIOS
    checksum in the states differs; verify same BIOS before source chase.
  - leading candidate: copied IRQ/callback table in IWRAM (`sBlob_a5224_a5258`
    at 0x080A5224, moved by reorder) or a raw literal in intr/audio code.
  - **headless full gate 2026-10-20**: first diff **frame 223045**, EWRAM
    offset `0x32290`, a=`41` b=`72`; state `disp=1800 main=1 s1=0 s2=0100
    event=81 area=4 room=14`; LR normal `0x11E0` vs reordered `0x1248`,
    CPSR normal `0x60000092` vs reordered `0x20000092`.  This is earlier than
    the native 223227 checkpoint but the same room-14 branch; use it as the
    deterministic repro for the fix.
  - evidence: `tools/headless/out/full/diff_reorder/reorder_{a,b}_223045_*`.
  - the EWRAM `0x32290` diff lands in `gDecompBg3Map` (0x02032000..0x02035D20)
    in both maps; first inspect the room-14 BG3 decompression/copy path.
  - **headless shifted also hits it after BUG-018** (`6f71b687`): 200000 ->
    223045 first diff EWRAM `0x32290` a=`41` b=`72`, same state
    `1800 0001 0000 0100 81 4 14 0` (main 1, s1 0, s2 0100, event 0x81,
    area 4, room 0x14); normal LR `0x11E0`, shifted LR `0x1258`, CPSR
    `60000092` both.  This is shared, not reorder-only.
  - evidence: `work/playtest/m0f-2026-10-17/tas/bug011_223045/`
    (`BUG011_RESULT.md`, `diff_200k/`, 200k/223045 states).
  - **223045 is a transient gate artifact**: LZ77 source/output are identical
    (`sSector4_Bg3_1`, shifted +0x1000); normal is still mid-copy at the frame
    boundary, shifted has finished.  From the 223045 states, EWRAM
    `gDecompBg3Map+0x290` converges by 223047 (both `0x72`); 223045..223060
    has no persistent EWRAM diff (diffs at 223046/47/48, 0 at 223049-52,
    transient at 223053/54, etc.).  Do not treat this as a source bug.
  - **caller/phase trace (2026-10-20)**: the real start is **223048/223049**,
    not 223214.  At 223048 normal `gSamusData.x=928`, shifted `x=916`
    (shifted has already applied one frame of movement); at 223049 normal
    `s1=0`, shifted `s1=1`; at 223100 shifted frame counters are +1
    (`gFrameCounter8Bit 0x88 vs 0x87`, `gFrameCounter16Bit +1`,
    `gColorFading.unk_3 0x21 vs 0x20`).  The shifted core runs **one extra
    game-loop iteration** when `SUB_GAME_MODE_LOADING_ROOM` /
    `ColorFadingReveal` completes.
  - that one-frame phase offset flips Samus at 223205 (normal pose 14
    grounded/vy 0, shifted pose 16 airborne), so only normal reaches door 79
    (`gLastDoorUsed=78` vs shifted 32) and room 23/14 at 223227.
  - the earlier `sBlob_a5224_a5258` IRQ/callback hypothesis is **ruled out**:
    the table is already relocatable (`src/data/generic_data.c:331`),
    `sUnk_a5278` is a u16 delay table, and the LR/CPSR difference is an IRQ
    sampling artifact (both cores print the same PC/LR/SP/CPSR at the durable
    frame).
  - **223040 checkpoint PASS** (23040 frames, 53.9 s); 223040 -> 223080
    resumes in ~0.04 s.  States in
    `work/playtest/m0f-2026-10-17/tas/checkpoints/{n,s}_223040.state`.
  - **first differing write**: `gSubGameMode1++` at `InGameHandler+0xAE`
    lands at 223049 shifted vs 223050 normal (same value).  The frame counter
    advances once per video frame in `AgbMain+0x1A`; the gap inside the single
    `InGameHandler` case 0 call is **8 video frames shifted vs 9 normal**
    (counter 0x25 -> 0x26).  `ColorFadingReveal`/`ColorFadingProcess` are
    already byte-identical at 223041; the one-frame cost is inside
    `InitAndLoadGenerics()` case 0 (`src/in_game.c:396`), prime suspects the
    VCOUNT busy-waits at `src/in_game.c:445-451` / `:455`.
  - no raw pointer, wrong door bound, IRQ or callback corruption was found.
    The LR/CPSR signature is a sampling artifact.
  - **VCOUNT trace / audio bisect (2026-10-20)**: the three VCOUNT waits in
    `InitAndLoadGenerics` are identical and exit in the same VCOUNT window.
    `gMusicInfo` non-pointer fields and channel envelope states are identical
    at 115000/150000/200000; they first differ by 223040 (channels in
    different envelope phases, `currentSoundChannel` 5 vs 3).  `UpdateMusic`
    processes ~half the channels/cycles in shifted in that frame, so the game
    loop reaches the next iteration one video frame earlier.
  - all track/vars/voice pointers checked so far relocate +0x1000; postlink
    has no sound/audio structured runs.  This looks like an audio/music phase
    or timing difference, not a raw pointer.
  - **audio bisection (A) completed**: channels are identical through
    **222333**; first divergence is **222334 channel 0**.  Track 60's current
    pattern bytes at `pRawData` (08268F2A / shifted 08269F2A) are identical,
    and `pRawData` is correctly `+0x1000`; the channel's sample/voice
    selection differs (`pSample1` normal `080CA0BC` vs shifted `080A6560`).
    No raw pointer was found in the track/voice tables; the suspected
    `sBlob_a5710` word at +0x62C is Envelope data, not pSample.
  - **FIXED 2026-10-20 (A continued)**: the suspected `sBlob_a5710` word is a
    real pointer after all, just at record **131 +8**, not +0x62C.  Record 131
    is a layered 0x40 voice: `unk_481c` reads +8 as a byte index-table pointer.
    The generated C had copied the bytes `20 8C 0A 08` as `struct Envelope`,
    so shifted kept `0x080A8C20` instead of `0x080A9C20`; the note at 222334
    then picked record 129 (normal) vs 126 (shifted).
  - fix: `tools/shift/gen_blob_tables.py` models the +8 field as
    `const u32*`, emits `&sBlob_a5710_a8cdc.records[1132]` for the intra-blob
    target, and relocates it.  Normal SHA stays `ca33f434...`.
  - verified with fresh shifted states: 200000 -> 222340 PASS, 222340 ->
    223300 PASS, 223300 -> 260000 PASS, 260000 -> 300000 PASS (settle 8).
    The 223048 one-frame phase and room 23/14 branch are gone.  The BUG-011
    audio-only shifted SHA was `934d0cf0...`.
  - 223040/223100 checkpoint states remain in
    `work/playtest/m0f-2026-10-17/tas/checkpoints/`; new states are under
    `audio_fix_diff/`, `audio_fix_diff2/` and `audio_fix_ladder/`.
  - fast repro from checkpoint 200000 takes ~50 s; do not rerun full.
- [DONE] BUG-012 (shift/engine) — shifted elevator callback/IRQ divergence at native TAS 22923
  - candidate `812d0090...` (BUG-008 fix) passes file-select, then native TAS
    first CPU/IRQ divergence at **22923**:
    normal callback `0809A2C9` (`CutsceneElevatorMonologueVblank`), shifted
    `080967E0`; normal `CPSR=00000092`, shifted `40000092`; both `PC=1C`,
    `IE=2401`, `DISPCNT=1500`.
  - 22924 shifted `IE=2400`, PC `0809680C`; 22925 Undefined
    (`CPSR=8000009B`), PC `00000068`; normal recovers at 22952 with
    `DISPCNT=9700`, shifted stays `1500`.
  - `080967E0` is an **even address inside shifted
    `EndingProcessLeavingSmallShip` (`080967CC` + 0x14)**, not a valid Thumb
    VBlank callback.  This is a callback/data corruption, not a legitimate
    callback setter; same class as BUG-008 but a different write.
  - prime suspect: the remaining raw pointer words inside
    `sBlob_73421e_prefix` (`0x8056..0x80B6`, `0xC4DA..0xC592`) that were
    identified as residual risk when BUG-008 was fixed.  The `0x8056` group
    is referenced by the new-file/cutscene frame tables; the `0xC4DA` group is
    a second embedded FrameData region.
  - next: convert those 27 pointer words to relocatable expressions, preserve
    normal SHA/layout, then re-run static/OAM/input gates; native EmuHawk
    retest is required before closing.  If the writer is not in this prefix,
    capture the write to `030019C4` at 22923 with the native MGBAHawk hook.
  - do not patch the `CallbackSetVBlank` setter, IRQ vectors, or IWRAM tables
    from the symptom alone.
  - **FIX LANDED `2650880`**: all 29 pointer words in the prefix
    (0x8056..0x80B6, 0xC4DA..0xC592, 0xC5A2, 0xC5B2) are relocatable packed
    struct fields; `tools/extractor.py` emits 30 byte-identical segments.
    Normal SHA1 `ca33f434...`; shifted `25f92d3be6822655c26ad17fdbc90ad8bea8e35d`.
  - static checks: all 29 words normal+0x1000 in shifted; 50,510 non-pointer
    bytes identical; file-select pFrame `087403CA` count 6.
  - automatic gates PASS: audit, smoke, test, strict relocs, shift/start/input
    4k/30k, screen/OAM diff, shift-reorder.
  - **native 22923 retest FAILED on `25f92d3b`**: callback still `080967E0`,
    LR `0809DFA6`, then IE loss/Undefined.  The prefix sweep was a valid
    relocation fix but not the 22923 root.
  - **actual root found**: shifted `0809DFA6` is inside
    `CutsceneMnologueDrawOam`; it reads a FrameData table at normal
    `0x08663E5C` / `0x08663E74` inside `sBlob_6638a0_682fac`.  Those pFrame
    words were still raw normal addresses.  In shifted the table at
    `0x08664E5C` pointed at old `0x08663E08`, whose count is `0x7810`, not the
    correct `0x0002`; the OAM loop overran into `gVBlankCallback`.
  - **FIX LANDED `162ad9a`**: all eight pFrame words in those two tables are
    relocatable fields; the surrounding 128,780-byte blob is preserved.
    Normal SHA1 `ca33f434...`; shifted
    `a69334ee1c367fada1aa388b8a889e14bb6cb0aa`.  Static: all eight words
    normal+0x1000; correct target count 2 vs stale target `0x7810`.
  - automatic gates PASS (audit/smoke/test/strict relocs, shift/start/input
    4k/30k, screen/OAM diff, shift-reorder).
  - **native 22923 retest FAILED on `a69334ee`**: callback still wrong
    (`0809A823`), then NewFileIntroVblank/IE loss/Undefined.  The two simple
    FrameData tables were not the only raw pointers.
  - **actual pOam table found by loading the native 22922 state**: shifted
    `R6=08664460`, `R5=030016B0`, `R10/sl=0xF164`.  The pOam table at
    `0x08663DD0` still had raw pFrame words.  Its first word points at old
    `0x08663AE0`, whose count is `0xF164`; the correct shifted target
    `0x08664AE0` has count `0x38`.  The loop therefore still overflowed into
    `gVBlankCallback`.
  - **FIX LANDED `df60f8f`**: the five pFrame words at
    `0x08663DD0/DD8/DE0/DE8/DF8` are now relocatable; the surrounding blob is
    byte-identical.  Normal SHA1 `ca33f434...`; shifted
    `2447dfb772077ce3d627e7a279e4cc1536d996b6`.
  - **native state check PASSED**: loading the existing
    `tas/bug012b_focus/shifted_22922.State` into the new ROM gives
    22923/22924/22925 `callback=0809B2C9`, `LR=000001B8`, `CPSR=92`, `PC=1C`;
    no IE loss and no Undefined.
  - automatic gates PASS (audit/smoke/test/strict relocs, shift/start/input
    4k/30k, screen/OAM diff, shift-reorder).
  - **native focused PASS on `c4b62c65`**: 22923/22924/22925 callback
    `0809B2C9`, LR `000001B8`, CPSR `00000092`; 22952 `DISPCNT=9700`;
    file-select 384/385/386/401 still PASS.
  - full 100% TAS remains QA-020; M0f stays BLOCKED until it reaches 339001.
- [DONE] BUG-013 (shift/engine) — idle/no-movie shifted black at frame 2238
  - independent of BUG-008/385 and BUG-012/22923.  Native BizHawk 2.3.2,
    no movie/no input, same BIOS/SaveRAM: normal/reordered OK; shifted first
    diverges at 2238:
    normal `DISPCNT=1300 callback=08093901`; shifted `DISPCNT=1B00
    callback=0809C1A2`; 2239 shifted IE=2400 and enters the exception path.
  - native MGBAHawk writer: final write to `0x030019C4` at PC `08099F28`,
    LR `08099D75`, value `0000C1A2`; `r3=030019C0`, `r9=030016E8`,
    `sl=0865A2E4`, `sb=030016E8`, `nextOamSlot=0x47`.  Another OAM-loop
    overflow into the VBlank callback.
  - source pointer `sl=0865A2E4` is in `sBlob_64e470_662804`; the shifted
    source target is zero-filled while the normal source at `0x0865A2E4` is
    populated.  Prime suspect: a raw source/base pointer for that intro frame
    table, not the BUG-012 tables.
  - evidence: `tas/idle_black_fine/` (`shifted_2200_bug013.txt`,
    `shifted_2238_store.log`, `BUG013_WRITER.md`); hook `mgba_store.log`.
  - deeper trace: the writer is `SpecialCutsceneDrawOam`; `pOam` is
    `entry+0x1C`; the animation frame record at `pOam+3*8` gives
    `pFrame=0865A2E2` (normal).  `0865A2E2` is inside
    `sBlob_64e470_662804` at +0xBE72; normal data there is populated, shifted
    data at the unrelocated target is zero.  The count halfword is 0x40 (64),
    and the 22nd 0x24-byte OAM entry starts at 0x030019B8, whose `pOam` field
    at +0xC is exactly `0x030019C4`; this explains the callback overwrite.
  - the raw value `0865A2E2` is **not** a 4-byte literal in normal/shifted
    ROM, so the fix is a base+offset pointer/table, not a simple literal.
    Likely source is the `sBlob_64e470` base/record table; decode the
    `shifted_2200`/`normal_2200` state or the writer `pOam` to locate the
    record.
  - **pOam write trace (MGBAHawk hook)**: slot 2's pOam at `0x03001704` is
    correctly written `0865CD48` (normal `0865BD48` +0x1000), but the active
    writer source is still `0865A2E2`, which corresponds to a different table
    at `0865A2CA`; that pOam value is not found as a 4-byte literal and is not
    the slot-2 CPU store.  The all-pOam trace also saw `0x030016F8` (entry+0x10)
    and `0x03001704` (entry+0x1C); neither holds `0865A2CA` before the
    overflow.  The OAM all-write trace walks `0865A216..0865A2D8`, so the
    active source is definitely the `A2CA` table, but its owner is still
    unidentified (likely computed/base+offset or DMA-selected, not a direct
    slot pOam store).
  - pOam field logging at `entry+0x10/0x14/0x18/0x1C` found no CPU store of
    `0865A2CA`; the value is not in the slot pOam fields before the overflow.
    DMA logging showed the `SpecialCutsceneOam` copy uses stack source
    `0x03007DEC` to `gNonGameplayRam`; stack writes do not contain `0865A2CA`
    either.  It is not a direct slot field or stack store; it is a computed
    base+offset or caller-selected table.
  - DMA transfer trace: at 2238 the `SpecialCutsceneOam` copy is
    `source=03007DF4 -> dest=030016F8/.../03001704` (DMA3, pc 0809447A).
    No DMA writes the stack source `03007D00..03007E00` and no CPU store of
    `0865A2CA` is present.  The active `A2CA` table is therefore not a direct
    pOam field/DMA source; it is selected/computed one level earlier.
  - attempted function-entry store hooks at `SpecialCutsceneDrawOam`
    (`08099DA0`/`08098DA0` + PC+2) did not fire in the current hook, so a
    normal store hook is not sufficient for the call-entry trace.
  - next: use an execution/PC hook (`on_bus_exec` or mGBA debugger) at
    `SpecialCutsceneDrawAllOam`/`DrawOam` to capture the pOam argument and
    caller; then relocate the selected table/pointer.
    Preserve normal SHA1 and all gates.  Do not patch the callback setter, IRQ
    vector, or IWRAM.
  - **M0f is blocked by this idle regression** even if the 22923 state check
    passes.
  - **FIX LANDED `da248e3`**: 31 raw pFrame words in the three pOam tables
    `0865CB38..0865CB90`, `0865CD00..0865CD38`, `0865CD48..0865CDA0` are now
    relocatable fields in `sBlob_64e470_662804`; `tools/extractor.py` emits
    32 byte-identical segments.  Normal SHA1 `ca33f434...`; shifted
    `c4b62c65378602b03f7144913fbf9d45140720fd`.
  - native idle PASS: 2239 `pOam=0865CD48 -> 0865ABA4 count=7`; 2299/2300
    `DISPCNT=1300 callback=08094901`; 2300 screenshot 14274 bytes (old black
    242 bytes).  Focused 384/385/386/401 and 22923/22924/22925 all PASS.
  - automatic gates PASS (audit/smoke/test/strict relocs, shift/start/input
    4k/30k, screen/OAM diff, shift-reorder).
  - **candidate c4b62 idle 2300-2331 healthy, but frame 2332 still crashes**:
    callback becomes `0809C021`, 2333 IE lost / PC `0000002C` / CPSR
    `FFFFFFFF8000009B`; invalid jump target `69626082`.
  - `030014E0 = gOamData + 0x6F8` = OAM slot 223; the 8-byte OAM entry wrote
    into `gNonGameplayRam+0x5C` and corrupted the `CutsceneProcessOam` function
    pointer.  This is another pOam/count overflow, later than 2238.
  - **QA-022 (Windows BizHawk)** assigned: load
    `tas/bug013_crash/shifted_2331.State` with candidate `c4b62c65`, run
    `bug013_2332_probe.lua`, return all 20 pOam/frame/pFrame/count rows for
    frames 2331-2333 and the active pOam table with count >20.
  - **ROOT CAUSE 2332 (local state replay, 2026-10-19)**: the pOam targets are
    correct (`+0x1000`), but their **pFrame words are still raw**.  The
    SpecialCutscene FrameData array spans blob offsets `0x0D6C8..0x0DDE8`
    (`sBlob_64e470_662804`, 229 records).  `da248e3` converted only the first
    12 records for three bases (31 unique words); it missed the rest of the
    same array.  At 2331, slot 4 points at `0865BB2E` (normal) instead of
    `0865CB2E`; shifted ROM at `0865BB2E` holds unrelated graphics, so the
    count halfword reads `66` instead of `1`; slots 6/7/9/10 read
    `25100/61443/1008/61443`.  Drawing those slots pushes `gNextOamSlot` to
    223 and overwrites `gNextOamSlot`/`CutsceneProcessOam` at
    `gNonGameplayRam+0x5C`.
  - fix scope: convert **all 188 remaining raw pFrame words** in
    `0x0D6C8..0x0DDE8` (not just the 3 x 12 windows) into relocatable
    `sBlob_64e470_662804 + offset` fields; keep the 10 zero records and all
    bytes byte-identical.  Normal SHA1 must stay `ca33f434...`.
  - pre-fix proof: a throwaway ROM patch adding `+0x1000` to those 188 words
    is healthy from 2331 through 2351 and matches normal's DISPCNT/callback
    (`08094901` is normal `08093901 + 0x1000`).
  - **FIX COMMITTED on `dev4` `424fd7f`** (rebased onto `b8fe9c2`; original
    `32d3513`): all 219 nonzero pFrame words in `0x0D6C8..0x0DDE8` are
    relocatable fields; extractor now generates the full 229-record layout and
    self-checks the C struct.  Normal SHA1 `ca33f434...`; shifted
    `012a2c95089485ebd37d19e86717b666ccc00e09`.
  - dev4 gates: audit/smoke/check-relocs-strict/shift-build PASS;
    normal `make check` PASS; `test`/`shift-start`/`shift-input`/
    `shift-reorder` dynamic stages SKIP (77, no harness in worktree).
  - candidate staged in `mgba-final-bug013b/` with the 2331 state and
    `BUG013B_RESULT.md`.
  - **native BUG-013b PASS 2026-10-19** (QA-022): 2331 state -> 5000 clean;
    idle 2238/2331/2332/2333/2400/5000 clean; pOam counts 1..11; focused
    384/385/386/401 and 22923/22924/22925/22952 PASS.  Merged fast-forward
    as `424fd7f`.
  - integrated `hack` rebuild: normal `ca33f434...`, shifted `012a2c95...`;
    post-link scan reports 74 runs but **no** `sBlob_64e470` run.
  - full 100% TAS is QA-020, now unblocked; M0f still waits on QA-020 and
    `PLAYTEST-000`.
- [DONE] BUG-019 (shift/engine) — Omega Metroid FrameData pFrame pointers
  - at TAS 331860 (room 63, PLAYING) normal OAM had 41 slots, shifted 12;
    `gNextOamSlot` and the Omega sprites diverged while game state matched.
  - root: `sBlob_39aa34_39f4b0` is a 19 KB extracted tail that embeds **34
    FrameData.pFrame pointers**.  `gSpriteData.pOam` was relocated, but each
    frame table's `pFrame` still pointed at normal addresses; shifted read
    shifted bytes through a normal pointer.
  - fix `tools/shift/gen_blob_tables.py`: sparse pointer blob mode keeps the
    bytes flat but emits the 34 intra-blob pointers as
    `(const u8*)sBlob...+offset`; normal SHA stays `ca33f434...`.
  - shifted SHA is now `d30310a634e83626e830cc0f481d9d8fece79488`; parity
    300000 -> 332883 PASS.  `gen_blob_tables --check`, `make smoke` and
    `make audit` pass; post-link runs drop 60 -> 56.
- [DONE] BUG-020 (shift/engine) — late-game VRAM/OAM at TAS 332884
  - after BUG-019, first diff is frame 332884 `VRAM 0xD000` a=`00` b=`8A`,
    then OAM slot 0 (`3C` vs `02`) and `gNextOamSlot` (`0` vs `16`).
  - the first non-pointer IWRAM divergence is also 332884: normal starts the
    ending/cutscene and sets `gNonGameplayRam+0x1484 = 0x0863A19C`
    (`sCutsceneTextNone`); shifted leaves it 0 and has `gChangedInput
    0x00140000`.  By 332885 shifted IWRAM from 0x11E8 onward is garbage
    (`0x08E81DBD`, `0x00004EB9`, ...); at 339001 normal is `sub1=2` (playing)
    while shifted is still `sub1=1` (transition) — a softlock.
  - **history trace (2026-10-20)**: at 332884 normal is idle in BIOS
    (`LR=0x1B8`, `disp=1800`, `nextOam=0`); shifted is inside
    `SpecialCutsceneDrawOam` (`LR=0x0809A008`, `disp=4000`, `nextOam=20`).
    Normal's `gNextOamSlot=0`; shifted starts drawing from slot 20.
  - `gOamData` is `0x03000DE8`, size `0x400`; its end is exactly `0x030011E8`,
    the first corrupted shifted IWRAM byte.  So the 332885 corruption is an
    OAM draw overflow, not a direct bad store to game state.
  - the `NewFileIntroLandingOnBsl` / `+0x1484` hypothesis is **wrong**:
    `gNonGameplayRam+0` is `INTRO_DATA.pText`; both states at 332884 have
    `gSubGameMode1=1` and `gCurrentCutscene=0x80`, so the direct
    `NewFileIntroLandingOnBsl` case-11 caller is not the path.  The pText/stage
    change is a downstream cutscene-state symptom.
  - the `sBlob_6131c8` table pointer itself is relocated, but its **nested
    pFrame words** are not (final root below); this is why the earlier
    table-pointer check looked clean.
  - next: trace the 332884 cutscene/ending transition that should reset
    `gNextOamSlot` (normal) but does not in shifted; inspect
    `gCurrentCutscene=0x80`, the VBlank/cutscene callback, and the
    `CutsceneElevatorMonologue` entry/exit.  This is a state/callback trace,
    not another data relocation.
  - history CSVs and states: `tas/checkpoints/bug020_hist/` (332884..332887)
    and `bug020_probe/` (332884).  `clean_332500/` is valid final-ROM 332500;
    old `oam_probe/s_332500` is contaminated by the pre-Omega-fix ROM.
  - **FIXED 2026-10-20**: `sBlob_6131c8_63a19c` is a 159700-byte cutscene
    blob whose nested `FrameData.pFrame` words were still normal addresses.
    Added `sparse_inside_only` to `gen_blob_tables.py`; 506 inside-blob
    pointer words now relocate, 382 outside text/graphics literals stay
    literal.  Normal SHA stays `ca33f434...`; shifted is
    `5888a563129ae391c0abb0f202748fd7fd883e93`.
    332880 -> 339001 `PARITY: PASS (6121 frames)`; final
    `gSubGameMode1=2` both.  `check-relocs-strict` passes (the reviewed
    generated block is data-whitelisted); post-link runs drop **56 -> 5**.
    Full 0 -> 339001 also passes 339001 frames (646.7 s), final
    `main=9 sub1=2 frame16=5979` both; all chunk ladders
    0-115k-200k-300k-332880-339001 PASS.
- [DONE] BUG-021 (content/tools) — hack rooms generated a garbage tileset
  - playtest 2026-10-21 (M1 artifact `098414b9…`): every Test Area 1 room was
    visually corrupted; HUD/minimap unreadable
  - root cause: the generated rooms used `.tileset = 0` with synthetic RLE
    block IDs that do not match tileset 0's tiles, and the pipeline had no
    tileset gfx/palette conversion
  - fix: `tools/content/gen_tileset.py` converts `blockout_tileset.png` to
    4bpp LZ77 gfx + RGB555 palette + 16-block tilemap; `RoomLoadTileset`
    selects `HackTest1TilesetEntry` for `AREA_TEST_1` under HACK.  The authored
    palette lives in `pPalette` row 2 (global PALRAM row 4) and the tilemap uses
    palette bank 4, because rows 1..3 are cleared by the first-load HUD/fade
    path; rows 4..15 survive
  - `build_rooms.py` maps roles to PNG block indices 0..15 (EMPTY 0 … MIST 15);
    rooms use the vanilla `sBg3_TestRoom` backdrop with `bg3_scrolling = 1`
  - verified: 28450 `_pal.bin` BG row 4 has the authored RGB555 values; the
    screenshot shows coherent room tiles, clean HUD/minimap and the correct
    banner text; `hack-room-check` + `hack-liveness-check` PASS
  - landed `32538da` (+ generator `5d7df83`); normal `ca33f434…`, shifted
    `5888a563…`, reordered `9dac0a4b…` unchanged; `content-check`,
    `Makefile.shift test`, `audit`, `check_relocs` PASS
  - remaining polish (not blocking): blockout art is placeholder; a custom
    tileset palette is tied to bank 4 by the fade path
- [DONE] BUG-022 (engine) — banner showed vanilla debug text
  - playtest 2026-10-21: the Entry Ledge banner displayed
    "Enemy location abnormal. Check message frame position."
  - root cause: the banner is a static spawn at record index 2;
    `MessageBannerInit` set `gCurrentSprite.roomSlot = UCHAR_MAX` when the
    sprite was not onscreen at init, so `TextDrawMessageBanner` received 255,
    clamped to 21, added 21 and drew vanilla English text index 42 —
    `sMessageTextPointers[2][42]` decodes to exactly that string
  - fix (`src/sprites_AI/message_banner.c`, HACK-only): for
    `gCurrentArea == AREA_TEST_1` keep the authored `roomSlot`; every other
    area keeps the baseline `UCHAR_MAX` overwrite token-for-token
  - evidence: instrumented EWRAM dump decoded to
    `ENTRY LEDGE{NEW_LINE}THE SIGNAL IS WEAK`, `pText = 0x0879C1D0`
    (`HackTextEntryLedgeSignal`, not `sMessageTextPointers`), `messageId = 2`;
    clean-ROM liveness reports `SPRITE[2] ... roomSlot=0x02`; the other three
    spawns unchanged; `hack-room-check` PASS
  - landed `8e05fbf`; normal `ca33f434…`, shifted `5888a563…`, reordered
    `9dac0a4b…` unchanged; `Makefile.shift test`, `audit`, `check_relocs` PASS
  - instrumentation was removed before commit (`src/text.c` clean)
- [DONE] BUG-023 (engine) — BG palette rows 1..3 black: not an engine bug
  - investigation (28450 prefix, `_pal.bin`): BG rows 1..3 are zero using
    tileset 0, but rows 4..15 are populated — this matches the Test Area
    tileset's actual palette layout, not a corrupted copy.  Vanilla Main Deck
    at the same frame has rows 0..4 because it uses a different tileset
  - the fade guard (`COLOR_FADING_NONE` for the first-load warp) removed the
    black fill but did not change the rows; the uniform screen then came from
    disabling display/fade state that the first load also relies on.  Reverted
  - conclusion: no engine writer to fix; the palette copy works (rows 0..5 are
    populated at the end of `RoomLoadTileset`), but the later HUD/fade path
    clears rows 1..3 while rows 4..15 survive.  The custom tileset therefore
    uses `pPalette` row 2 (global row 4) and tilemap bank 4 (BUG-021), which
    renders correctly
  - evidence: palette dumps, `_pal.bin` row 4 after the fix, and
    `work/emulator/bug021_truth_blocks.png`
- [TODO] BUG-024 (engine) — player sprite invisible in the M1 rooms
  - M1b screenshot evidence: the HUD/minimap draw, the room renders, but Samus
    is not visible anywhere in Entry Ledge
  - deferred with the M1 rendering pause; start after the documentation phase
    or when the human reopens M1
  - check sprite gfx slots vs the room spriteset, Samus palette/OBJ rows, and
    whether the custom tileset/backdrop path overwrote Samus' VRAM/palette
- [TODO] BUG-025 (content) — room tile colours wrong in the M1 rooms
  - M1b screenshot evidence: some blockout tiles use the wrong colours (the
    generated tileset palette is bank 4; row/bank edge cases remain)
  - deferred with the M1 rendering pause
- [TODO] BUG-026 (engine/content) — HUD/minimap textures wrong
  - M1b screenshot evidence: HUD and minimap tiles are garbled/incorrect while
    the banner and room tiles draw
  - deferred with the M1 rendering pause; likely VRAM/palette overlap from the
    room tileset/backdrop path
- [DONE] DOC-001 (docs) — rewrite README for the shiftable engine
  - removed the stale "not shiftable" warning; reframed the repo as the
    decomp baseline + shiftable engine + `HACK=1` Sector Null overlay, with
    quick start, gate inventory, docs map, M0 pass/M1 blocked status, regions
    and attribution
  - landed `6b856e3`; `README.md`
- [DONE] DOC-002 (tools/docs) — format contract
  - `.clang-format` (4 spaces, Allman, pointer-left, 120 cols), `mk/format.mk`
    with `format`/`format-check`/`format-list`, `docs/style.md`; no mass
    reformat; missing clang-format skips with a clear non-pass message
  - landed `6b856e3`; `make help` and `make format-check` verified
- [DONE] DOC-003 (docs) — engine architecture overview
  - `docs/architecture/overview.md`: boot/main loop/VBlank, file load and the
    HACK warp, room load pipeline, RLE/tilemap/clipdata, sprite/OAM, text,
    audio, SRAM, D-013 overlay hooks, gates and decomp gaps
  - landed `700b407`; based on dev39's verified symbol map (frame counters are
    main-loop counters, `SaveFile` is still a stub)
- [DONE] DOC-004 (docs) — how-to: add a room/door
  - `docs/howto/add-a-room.md`: IDs -> Tiled/manifest -> converter -> generated
    tables -> `HACK_ROOMS`/doors -> validation/pitfalls
  - landed `c035f9b`
- [DONE] DOC-005 (docs) — how-to: add dialogue/text
  - `docs/howto/add-dialogue.md`: INCTEXT/charmap, messages.json, TEXT IDs,
    spawn-index message id, BUG-022 roomSlot pitfall, validation
  - landed `c035f9b`
- [DONE] DOC-006 (docs) — how-to: add an enemy behaviour
  - `docs/howto/add-enemy.md`: PSPRITE_END constraint, proxy pattern, spriteset
    slot vs roomSlot, hack/*.c is not compiled, custom-AI options
  - landed `c035f9b`
- [DONE] TECH-001 (tools) — symbolise hardcoded ROM literals
  - `tools/shift/label_comments.py`: resolves ROM addresses via
    `map_symbols.py` and appends ` (Symbol+0xOFF)` to comments only;
    `--check/--write/--json/--limit/--scope`, `--self-check` 21/21
  - all **699** in-scope comments (697 asm + 2 C) labelled in two batches,
    0 unknown/ambiguous; code prefixes unchanged, normal `ca33f434…` stays,
    smoke/audit/check_relocs PASS
  - landed `6def7b9` + `b870374`; remaining `ldr` count in the audit is
    reference-only, not unresolved relocations
- [DONE] TECH-002a (decomp) — giant disasm split plan
  - `docs/architecture/disasm-split-plan.md`: inventory of the six files
    (52,883 lines), validated byte-identical cut points for
    `disasm_0x0808F5C4.s` (4 parts at `IntroSamusInShipProcess`,
    `EndingHandler`, `CutsceneHandler`) and the other five, exact `linker.ld`
    insertion order, C-ification top-10 and a safe-execution checklist
  - landed `ae0499b`; `ld -r` of the proposed parts is byte-identical
  - note: room load/backgrounds/clipdata/scroll/text are already C; the
    remaining hack-relevant asm is the SRAM/status/pause/navigation set
- [TODO] TECH-003 (tools/decomp) — objdiff + decomp-permuter scratch workflow
  - document/provide a scratch loop for C-ification: build a candidate C
    function in `work/` or `/tmp`, compare it with the baseline object using
    objdiff (or `arm-none-eabi-objdump`), and optionally run decomp-permuter
    for register/scheduling variants
  - the shiftable engine does not require byte-matching, but objdiff catches
    behavior-relevant codegen differences before a C port is accepted; never
    commit scratch output or third-party tool trees
  - start with the SRAM functions in the TECH-002a priority list
- [DONE] TECH-002b (decomp) — first disasm split
  - `asm/disasm_0x0808F5C4.s` split into `_090d60` / `_09223c` / `_094e84` /
    `_09994c` at the validated function boundaries; `linker.ld` lists the four
    objects in ascending address order; `.text` sizes match the plan exactly
    (0x14DC/0x2C48/0x4AC8/0x4228; total 0xCE14)
  - normal `ca33f434…`, shifted `5888a563…`, reordered `9dac0a4b…` unchanged;
    `audit`, `smoke`, `test` (boot + 4k input), `shift-test`, `shift-reorder`,
    `check_relocs` PASS; concatenating the parts reproduces the old file
    byte-for-byte (minus headers)
  - landed `2bac36c` (+ refreshed `docs/shiftability-audit.md` `64f2f3f`)
- [DONE] TECH-002c (decomp) — split SRAM/status and file-select asm
  - `disasm_0x0807e678.s` -> `_0807e678` (StatusScreenHandler, 0x82C) /
    `_0807eea4` (Sram_ReadAll, 0x1B4C) / `_080809f0` (EraseSramMenuHandler,
    0x77C); sum 0x2AF4
  - `disasm_0x0809deb4.s` -> `_0809deb4` (GameOverHandler, 0x6E4) /
    `_0809e598` (FileSelectHandler, 0x2E38) / `_080a13d0` (SetLanguage,
    0x8B4); sum 0x3DD0
  - normal `ca33f434…`, shifted `5888a563…`, reordered `9dac0a4b…` unchanged;
    audit/smoke/test (boot + 4k input), `shift-test`, `shift-reorder`,
    `check_relocs` PASS; bodies concatenate byte-identically minus headers
  - landed `acf2301` + `4b92bc9` (+ refreshed audit table)
- [TODO] TECH-002d (decomp) — split the remaining disasm files
  - `disasm_0x08079afc.s` (2 parts, cut at 3857), `disasm_0x080765f8.s`
    (2 parts, cut at 1227), `disasm_0x08056140.s` (2 parts, candidate)
  - same rule: function boundary, 3-line header, ascending `linker.ld` order,
    `ca33f434…` unchanged or revert
- [TODO] BUG-014 (shift/engine) — post-link scan: raw pointer runs remain
  - new gate `tools/shift/postlink_pointer_scan.py` (landed `ebf1f9c`):
    relinks with `--emit-relocs`, scans non-executable ROM data, ignores
    relocated words, and fails only on structured pointer runs
    (stride 0x4/0x8/0xC/0x18/0x24 with unique/known/alignment filters).
  - targets: `make -f Makefile.shift postlink-scan` (report) and
    `postlink-scan-strict` (exit 1).  Not wired into `check-relocs-strict`
    until triage; normal SHA stays `ca33f434...`.
  - self-check 4/4; known-bad old ELF reported 90 runs including the BUG-013
    `sBlob_64e470_662804` run `0x0865BB98..0x0865BCF0` (44 words).
    After merging the BUG-013 fix, the integrated tree reports **74 runs** and
    **no `sBlob_64e470` run**; normal `ca33f434...`, shifted `012a2c95...`.
  - after BUG-020, only **5** structured runs remain; the
    `sBlob_6131c8_63a19c` group is gone.  Remaining groups include
    `sBlob_6638a0_682fac`, `sBlob_582288_58b3cc`, `sBlob_5766D4_prefix`
    and `DirectSoundData_080BE5B8`.  `sBlob_39aa34_39f4b0` (BUG-019) and
    `sBlob_6131c8_63a19c` (BUG-020) are fixed.
  - **concrete hit fixed by BUG-016 `1f01180`**: the
    `sBlob_6638a0_682fac` run `0x086792E0..0x086793A0` is gone; postlink is
    now 67 runs.  The next full-TAS failure (BUG-017 at 117234) is **not**
    from the remaining `sBlob_6638a0_682fac+0x1D0xx` run; it is an EWRAM
    zero-fill.  `sBlob_6131c8_63a19c` remains the next-largest risk.
  - next: triage each group as either a real unrelocated FrameData/pointer
    table (convert) or a reviewed false positive (whitelist with evidence).
    Do not auto-whitelist; do not wire strict into the main gate until the
    list is zero or explicitly justified.
  - this is a shiftability P0 but does not block the BUG-013 native gate.
- [DONE] BUG-015 (emulator) — full TAS shifted black after frame 30000
  - partial native run on shifted `2447dfb7...` (pre-BUG-013 merge) passed
    file-select, 22922-22952 and 30000 (normal/shifted fields match), then
    shifted went black after 30000; the run was stopped before the next
    checkpoint, so there is no first-black frame or 30000 state.
  - **closed as early-stop/fade**: local converted-input replay and the
    headless 339001 gate show these black frames are 1-3 frame fades and
    normal is black at the same frames.  The real first shifted divergence is
    **BUG-016 at 114671**, not a persistent black after 30000.
  - evidence: `tas/bug012c_full/`, `tools/headless/out/full/`.
- [DONE] BUG-016 (shift/engine) — full TAS shifted divergence at 114671
  - headless movie-native mGBA 0.6, current `012a2c95...`, 339001 frames:
    first diff **114671**, OAM offset 0, a=`80` b=`02`; state
    `1600 0004 0002 0100 43 0 20 0` (disp 1600, main 4, s1 2, s2 0100,
    event 43, area 0, room 20).
  - normal PC `1C`, LR `1B8`, SP `03007FA0`, CPSR `92`;
    shifted PC `60`, LR `2000009B`, SP `03007FE8`, CPSR `8000009B`
    (undefined/exception path).
  - pre-crash dumps at 114650/114660/114665/114669/114670: at 114670 normal
    cutscene entries i=0..2 are active with pOam
    `086793B0`/`08679280`/`086793A0` and pFrame counts 19/4/6; shifted had
    garbage pOam and `gNextOamSlot` wrapped.
  - root cause: the 52-record `struct FrameData` table at
    `sBlob_6638a0_682fac+0x159E0` (normal `0x08679280..0x08679420`, 8-byte
    records: pFrame + timer + 3 pad) had raw normal pFrame words.  41 pointers
    / 11 terminators are now relocatable C; extractor splits at
    `0x159E0`/`0x15B80` and self-checks the table.
  - **FIX LANDED `1f01180`**: normal SHA `ca33f434...`, shifted
    `e5d202c84f5a638678cc474dddf96b30552249bf`; strict/host/doctor PASS;
    postlink 74 -> 67 and the `0x086792E0..0x086793A0` run is gone.
  - headless **115000 PASS**; full 339001 now first-diffs at **117234**
    (BUG-017), so BUG-016 is closed.
- [DONE] BUG-017 (shift/engine) — full TAS shifted EWRAM zero-fill at 117234
  - headless 339001 on shifted `e5d202c8...`: first diff **117234**, EWRAM
    offset `0x0`, a=`FF` b=`00`; state `0000 0003 0000 0100 47 6 2 9`
    (main 3, s1 0, s2 0100, event 47, area 6, room 2).
  - normal PC `1C`/LR `0x11DC`/CPSR `60000092`; shifted PC `1C`/LR `0x11D0`/
    CPSR `60000092`.  OAM/PAL/VRAM agree; the shifted 4 KiB window at EWRAM
    `0x02000000` is zero where normal holds data.
  - likely an intro/cutscene `LZ77UncompWram` destination/length or a different
    source pointer: call sites `EndingMonologueInit 0x08095E24`,
    `CutsceneElevatorMonologueInit 0x08099C38`,
    `CutsceneInternalMonologueInit 0x0809A3AC`,
    `CutsceneFederationMonologueInit 0x0809A6CC`; the
    `sIntroTilemap_662804` literal (`0x08662804` -> shifted `0x08663804`) is
    already relocated, so inspect the destination/length words.
  - not the remaining `sBlob_6638a0_682fac+0x1D0xx` run; do not whitelist.
  - next: reproduce with headless 117k, compare EWRAM source writes, find the
    writer/length, convert the stale constant, then extend from the 115000
    checkpoint and only run full 339001 after the chunks are clean.
  - fast repro: `work/playtest/m0f-2026-10-17/tas/bug017_117234/`
    `BUG017_RESULT.md`; states n/s_115000; 3.85 s resume to 117234.
  - **caller trace (2026-10-20)**: SWI 0x12 at frame 117234 has
    caller LR `0x0807BCF1` (`NavigationConversationLoadPopUpGraphics+0x59`)
    in both builds; `r0=0x08577024`, `r1=0x02000000` in both; `r2` relocates
    correctly (`0x0857BC64` -> `0x0857CC64`).  The caller and all earlier 36
    LZ77 calls are fine; only this call's `r0` is stale.
  - exact field: the consumer reads `pGraphics` at
    `table + 0x14 + id*0x18`.  For `id=4` that is `table+0x74`, which is
    **outside** the C `records[4]` table and is the first word of the opaque
    `sBlob_5766D4_after` blob: normal `0x08577024` (= `prefix+0x950`),
    shifted still `0x08577024` instead of `0x08578024`.
  - LZ77 evidence: normal at `0x08577024` has header `0x00200010` (type 0x10,
    size `0x2000`); shifted at the stale address has `0x01200000`
    (type 0x00, size `0x12000`), so it decompresses garbage.  The correctly
    relocated `0x08578024` is byte-identical to normal.
  - fix scope: model the id-4 pGraphics at table `+0x74` as a relocatable
    `const u8 *` = `sBlob_5766D4_prefix + 0x950`; start the opaque
    `sBlob_5766D4_after` at `+0x78` (4 bytes later) and update
    `tools/extractor.py` to skip the pointer.  No asm change, no LZ77 data
    change.
  - **FIX LANDED `e35a785`**: id-4 pGraphics now relocatable; normal SHA
    `ca33f434...`, shifted `26f1f4223d06844851999d5a3417cb38653b6961`;
    gates PASS; postlink 67 (unchanged).  Checkpoint 115000 -> 130000 PASS
    (29.7 s); 339001 not run, per D-012.
- [DONE] BUG-018 (shift/engine) — shifted OAM overflow at frame 168582
  - chunk ladder on `26f1f422...`: 115000 -> 150000 PASS; 150000 -> 168582
    first diff.
  - first diff frame 168582, OAM offset 0 a=`08` b=`02`; state
    `1500 0004 0002 0100 63 0 76 0` (main 4, s1 2, s2 0100, event 0x63,
    area 0, room 0x76).
  - normal PC `1C`/LR `1B8`/CPSR `92`; shifted PC `2C`/LR `0001301C`/
    CPSR `4000009B` (exception path).
  - `CutsceneElevatorMonologueSetupOam` writes all four pOam pointers
    correctly (+0x1000): `08663E5C`, `0866AA30`, `0866AA30`, `0866AA58`.
  - the pOam tables' **nested frame-entry pointers** are stale:
    `0866A764`, `0866A8A4`, `0866A9E4` should be `+0x1000`
    (`0866B764`/`0866B8A4`/`0866B9E4`).  Shifted reads count
    `0x3300`/`0xAA70` instead of normal `0x35`/`0x0C`, so
    `CutsceneMnologueDrawOam` overruns gOamData and clobbers
    gNextOamSlot/neighbouring state.
  - source: `src/data/new_file_intro_data.c` (`sBlob_6638a0_682fac`
    region between `sIntroPal_663820` and `sCharactersGfx`) plus
    `tools/extractor.py`; model the nested frame-entry pointer tables as
    relocatable C (`sIntroPal_663820 + offset`), preserving every non-pointer
    byte.  Do not patch callback/IRQ or whitelist.
  - evidence: `work/playtest/m0f-2026-10-17/tas/bug018_168582/`
    (`repro.log`, states, `diff_168582/`, `pre168581/`); scratch watch
    `/tmp/opencode/bug018_watch/`.
  - **FIX LANDED `80d04d1`**: all monologue/BSL nested FrameData tables in
    `sBlob_6638a0_682fac` are relocatable C (`+0x7190`, `+0x71B8`, `+0xE12C`,
    `+0xE154`, `+0x1D4B4`); normal `ca33f434...`, shifted
    `6f71b687530a4a123aba615cc6542a0ba500ee9d`; postlink 67 -> 60.
  - checkpoint 150000 -> 200000 PASS (50k, no diff at 168582); 200000 ->
    250000 stops at 223045 = BUG-011 (shared room-14/gDecompBg3Map).
- [PARK] BUG-010 (playtest) — shifted elevator hard freeze / black screen (deferred)
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
  - second state `pre-transition.ss0` (SHA1 `A69878...`) is CPU-valid
    (`pc=0x1C4`, CPSR `0x2000001F`, frame 10452) but its t0 screenshot already
    shows the elevator moving; it is post-entry, not a pre-entry matched state.
    Shifted stops after t60; normal `elevator_01.ss0` continues to t600, but
    the normal/reordered states are a different phase/route/SaveRAM.
  - next: capture true **pre-entry** matched states in normal/shifted/reordered
    from the same SaveRAM, input and frame (before stepping onto the platform);
    use the same mGBA version and verify loader has no "different game" warning.
    Only then can BUG-010 be classified as source.
  - Do not call M0 PASS; no source patch from this unmatched phase.
- [DONE] BUG-008 (shift/engine) — shifted IRQ/file-select undefined path
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
  - native 100% TAS (BizHawk 2.3.2) confirms the same first divergence at
    frame 401; shifted never reaches the TAS ending/elevator.  VBA-Next gives
    the same PC/GPR/IRQ trace and 400/401 dumps as mGBA, so this is **not
    mGBA-core-only**.
  - core matrix: BizHawk 2.3/2.3.1 ship mGBA 0.6 (fork updated 2018-09-10);
    BizHawk 2.3.2 ships mGBA 0.7.2.  The actual reproducer is the
    **MGBAHawk/mGBA path** (native `mgba.dll`); the later VBA-Next control did
    **not** reproduce the callback corruption.  Do not call this a universal
    core bug.
  - first IRQ anomaly at frame 385: shifted `LR=0x080A2334`, `SPSR=0x3F`
    (normal `LR=0x1B8`, `SPSR=0x1F`); frame 386 shifted enters Undefined mode
    (`CPSR=0x4000009B`) and clears IE bit0; normal stays in IRQ.  IRQ vector
    `0x03000BE8`, IF/IME equal.  Evidence:
    `work/playtest/m0f-2026-10-17/tas/bizhawk_bug008/BUG008_TRACE.md`.
  - investigate the shifted IRQ entry/return and file-select callback/IE
    write; do not patch until the wrong LR/SPSR source is proven.
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
    dialogs/rooms, intro beyond start, ending and game over.  BizHawk native
    parity Lua is available and is authoritative for normal TAS/ending visual
    reference; the 100% TAS is normal-only and cannot be replayed directly on
    shifted/reordered.  Headless TAS conversion remains invalid for parity.
    No M0 PASS yet.
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
  - landed `2b4a0a0` + `4c61351`; pass write-up in
    `docs/shift-test-diagnosis.md` ("QA-013a pass") and harness support in
    `tests/emulator/harness.c` / `tests/emulator/README.md`.
- [PARK] QA-012 (emulator) — M0 fresh-path room/dialog coverage matrix (paused: BUG-010)
  - run normal/shifted/reordered from matched saves/states through all rooms,
    Navigation Room dialogs, pause/map/status, save/load, intro/ending and
    game-over paths; compare OAM/PAL/VRAM/IO and normalized IWRAM/EWRAM.
  - any shifted-only difference becomes a BUG; M0 sign-off requires this
    matrix plus the fresh manual route, not only the controlled map.
  - depends on BUG-009; run after the current fix lands.  Do not close M0 on a
    single controlled path.
- [TODO] QA-009 (emulator) — checkpoint memory parity (OAM/PAL/VRAM/IO exact;
  IWRAM/EWRAM normalized)
  - exact: OAM/PAL/VRAM-BG/VRAM-OBJ/IO registers
  - normalized: IWRAM/EWRAM 32-bit ROM pointers (+0x1000), excluding the
    known IWRAM code-copy tail; state-based local diff for manual pages
  - feeds QA-012: the room/dialog coverage matrix reuses this checkpoint diff
    (OAM/PAL/VRAM/IO exact, IWRAM/EWRAM normalized)
- [DONE] QA-008 (emulator) — OAM parity telemetry at checkpoints
  - `oam-diff` PASS 6/6 at 300/600/900/1059/4000/30000, including the plain
    map frame 1059; the earlier 30k mismatch was a worktree data-artifact issue,
    not BUG-007
  - savestate-based objective-page comparison stays local-only
  - landed `e1793f5`; gate in `tests/emulator/oam_diff.py` and
    `tests/emulator/harness.c`.
- [TODO] QA-007 (emulator) — later map/dialog/Enter regression checkpoint
  - shifted black-screen reproduction can be automated from
    `m0e_shifted_slot3.ss3` + held Start; map/dialog visual comparison needs a
    normal same-page state or a deterministic normal route
  - BUG-005 fixed; slot3 local state check passes
- [DONE] QA-006 (emulator) — 30k input fixture + `shift-input-30k` gate
  - normal/reordered/shifted 30k PASS after BUG-004
  - landed `f466f7d`; fixture `tests/emulator/inputs/baseline_first30000.input`
    plus `.expected`.
- [DONE] QA-005 (emulator) — screenshot-parity gate
  - `screen-diff` passes after BUG-003; normal/shifted/reordered match at
    600/900
  - landed `d2485e7`; `screen-diff` gate in `tests/emulator/harness.c` and
    `Makefile.shift`.

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
  - landed `dfe4b5a`: `tools/content/tiled_to_room.py`, `tools/content/pngio.py`,
    synthetic fixture under `tools/content/fixtures/`, and
    `docs/content-pipeline.md`; `content-check` PASS.
- [DONE] HACK-004a1 (content) — five-room blockout source assets
  - `1d3d03a`: synthetic tileset + 5 Tiled maps/manifests under
    `hack/content/tiled/`; 12 doors, 12 spawns, camera scrolls; all rooms
    ≤450 blocks; `check_blockout.py` and `content-check` PASS.
  - generated `hack/gen/rooms/` stays ignored; README has the HACK-004a2
    integration checklist. Door IDs 10/11 are a provisional post-boss return
    pair and need design sign-off before the 13-entry door table is committed.
- [DONE] HACK-004a2a (content/tools) — generate all 5 Test Area 1 rooms
  - `HACK_ROOMS` converts `entry_ledge`, `silent_atrium`,
    `resonance_chamber`, `hidden_conduit`, `choir_nest` (15x10, 15x30, 30x10,
    45x10, 15x20) and `gen_content_tables.py` emits one room-indexed
    `content_tables.h`/`scroll_tables.h`/`sprite_tables.h` for rooms 0..4;
    per-room gfx slots stay independent
  - all 12 authored doors are active with reciprocal `dstDoor` pairs
    (0/1, 2/3, 4/5, 6/7, 8/9, 10/11); the generated `HackTest1Doors` is
    `0x9C` bytes = 12 records x 12-byte agbcc stride + terminator (the
    9-byte `doors.bin` is the file format only)
  - `hack-room-check` replays a deterministic **29500-frame prefix** (generated
    from the 30k fixture into `work/emulator/`): the full 30k replay now
    legitimately walks through door 0 at ~frame 29657, so door chaining is
    left to 004a2b; the entry warp still asserts `area=7 room=0`
  - landed `698a66a`; `content-tables-check`, `content-check`, `hack-build`,
    `hack-smoke`, `hack-room-check` (`FINAL_EVENT ... area=7 room=0`,
    `main=1`), `hack-liveness-check` (7-entry spriteset + 4 live spawns) PASS;
    normal `ca33f434…`, shifted `5888a563…`, reordered `9dac0a4b…` unchanged;
    `Makefile.shift test`, `audit`, `check_relocs` PASS
  - still missing (004a2b): event block 0x6E..0x77, broad
    `>= EVENT_ORBIT_CHANGE_IMPLEMENTED` checks, dedicated door-transition /
    save-load scenario, custom Echo Hunter AI
- [TODO] HACK-004a2b (engine/content/qa) — events, pads and transition scenario
  - M2-enabling work; M1 is already handed off and does not depend on it
  - add the authored `AREA_TEST_1` event block (0x6E..0x77) and fix the broad
    `>= EVENT_ORBIT_CHANGE_IMPLEMENTED` checks before the pulse (save/
    navigation/recharge pads); decide the ADR path for any baseline table
    growth so normal/shifted/reordered SHAs stay unchanged
  - transition entry positions and a dedicated cross-room door/save-load
    scenario for the five rooms
- [DONE] ADR-013 (design/manager) — hack-owned content tables and generated IDs
  - decide the narrow engine hook/link boundary that moves rooms, doors,
    tilesets, scrolls, text, events and save IDs that hacks mutate out of
    baseline-owned `src/data` into `hack/content` + generated `hack/gen`
  - D-009 requires `hack/include/hack/ids.h` and `docs/content-tracker.md`;
    no new magic numbers may enter before the ADR lands
  - landed as **D-013**: baseline `src/data` stays vanilla; `HACK=1` links a
    generated hack overlay; IDs/text/tables source in `hack/content`, generated
    into ignored `hack/gen`; one narrow AREA_TEST_1 hook only
- [DONE] HACK-008a (tools) — YAML ID registry -> ids.h/tracker
  - source `hack/content/ids.yaml`; deterministic generator
    `tools/content/gen_ids.py --check/--write`
  - emit `hack/include/hack/ids.h` and `docs/content-tracker.md`; validate
    uniqueness, reserved ranges, room/door/text/event/save references
  - add to `make content-check`; no engine/source data changes
  - landed `8be4573`: 28 IDs / 7 categories; generator + generated
    `hack/include/hack/ids.h`, `docs/content-tracker.md`; `content-check`
    PASS.  `SPRITE_ECHO_HUNTER=0xCF` is reserved for HACK-008d and requires
    extending `PSPRITE_END`/primary tables before use; text/music/save fields
    remain deliberately unallocated (typed reserved placeholders).
- [DONE] HACK-008b (tools) — charmap text pipeline + roundtrip
  - fill `charmap.txt` with the real MF character map; use the existing
    `tools/preproc` charmap support instead of a parallel encoder
  - compile one dialogue block to bytes and decode it back in a host test;
    add a content validator and docs
  - landed `cbc2a70`: real `charmap.txt` for proven letters/space/controls,
    `tools/content/text_roundtrip.py` via C `INCTEXT`, golden-path text
    example, `content-check` round-trip; `make content-check` PASS.
    Digits/punctuation remain deliberately unproven; text IDs stay
    unallocated until HACK-008d.
- [DONE] HACK-008c1 (engine/tools) — HACK=1 build overlay scaffold
  - add a separate hack build target/artifact that defines `HACK=1` and links
    a narrow AREA_TEST_1 selection hook; empty overlay falls back to baseline
    so normal/shifted/reordered SHAs stay unchanged
  - no generated tables yet; prove the build/boot and no-baseline-edit contract
  - landed `93a7d4f`: `mk/hack.mk` + `make hack-build`/`hack-smoke`, private
    `work/hack/obj`, `HACK=1` C/asm defines, and one `#ifdef HACK` hook in
    `src/room.c` selecting `hack/include/hack/content_tables.h`.
  - empty overlay is byte-identical to baseline: normal/hack SHA
    `ca33f434...`; hack `boot_smoke` PASS; `content-check` PASS.
- [DONE] HACK-008c2 (tools/content) — generated Entry Ledge room/door/spriteset table
  - `tools/content/gen_content_tables.py` reads the Tiled converter output and
    emits `hack/gen/content_tables.h`: one `RoomEntryRom`, RLE bg1/bg2/clip,
    default spriteset records, a safe empty bg3, and a `DOOR_TYPE_NONE`
    terminator; deterministic `--write/--check/--self-check`
  - `make content-tables` / `content-tables-check`; generated output remains
    ignored under `hack/gen`; no hand edits to `src/data`
  - HACK linker uses the same `linker.ld` rewritten by
    `tools/shift/prefix_linker_objects.py` to load only `work/hack/obj`
    objects; `src/room.o(.rodata)` carries the generated table and
    `hack-build` rebuilds `room.s` when the generated header changes
  - landed `4129ed1` + `cd29b7a`; normal/shifted/reordered SHAs unchanged
    (`ca33f434...` / `5888a563...` / `9dac0a4b...`), hack SHA
    `621ddc6e...`, `hack-smoke` PASS, `test` PASS, `content-check` PASS
  - scope note: this task generated room/door/spriteset data only.  Hack-owned
    scrolls, text, events and music remain for HACK-008d; the two authored
    Entry Ledge doors stay suppressed until their destinations exist.
- [DONE] HACK-008d1 (tools/engine) — hack-owned scroll table for AREA_TEST_1
  - `tools/content/gen_content_tables.py` now emits `scroll_tables.h` beside
    `content_tables.h`: one `SCROLL_DATA_SIZE(n)` block per room, byte-exact
    with `scrolls.bin`, the `0xFF` terminator, `HackTest1ScrollPointers` and
    `HACK_AREA_TEST_1_SCROLLS`; `--self-check` covers bad count/length/field/
    room-id plus stale/missing headers
  - scrolls are split from the room/door header so `src/room.c` and
    `src/scroll.c` each define the generated objects exactly once; a single
    shared header emitted every blob twice (now proven gone by `nm`: one
    `HackTest1Room0Scrolls` at `0x0879b978`, `sAreaScrollPointers[7]` =
    `0x0879b9d4` = the single list, ROM bytes = `scrolls.bin`)
  - one new `#ifdef HACK` hook in `src/scroll.c` selects the generated list;
    tracked shim `hack/include/hack/scroll_tables.h`; `mk/hack.mk` rebuilds
    `scroll.s` when the header changes
  - landed `5251917`; gates: `content-tables-check`, `content-check`,
    `hack-build`, `hack-smoke` (static + 600-frame boot) PASS; normal
    `ca33f434…`, shifted `5888a563…`, reordered `9dac0a4b…` unchanged; `make
    -f Makefile.shift test` (boot + 4k input), `audit`, `check_relocs` PASS
  - still missing: no active doors/entry warp, so `ScrollLoad()` with this
    table is linked but not yet exercised in a room-load scenario
- [DONE] HACK-008d2 (tools/engine) — text ID space and hack-owned message table
  - `TEXT_*` IDs are global (`ids.yaml`: first `TEXT_ENTRY_LEDGE_SIGNAL = 0x0`,
    area-scoped; `gen_ids.py` now accepts `area` on text entries); the engine
    lookup is per area and per `message_id`, which is the banner spawn's
    `roomSlot` (spawn record index from `SpriteInitPrimary`, not the spriteset
    slot); `TextDrawMessageBanner` clamps it at 21 and adds 21 for vanilla
  - `hack/content/text/messages.json` (`mf-hack.text-messages/v1`) maps
    `(area, message_id, text_id)` to a committed INCTEXT source + literal;
    Entry Ledge's new `signal_banner` spawn (Tiled object 102, spriteset slot
    5) is record 2, so the mapping is `message_id: 2`
  - `tools/content/gen_text_tables.py` reuses `text_roundtrip.py`
    (`tools/preproc`, no second encoder) and emits `hack/gen/text_tables.h`
    with one `u16` block per TEXT id, `HACK_<AREA>_TEXT_COUNT 22` and a
    `[message_id]` pointer list; tracked shim
    `hack/include/hack/text_tables.h`; strict schema/registry/range/source
    validation plus self-check negatives
  - one narrow `#ifdef HACK` hook in `src/text.c` uses the hack slot only when
    `gCurrentArea == AREA_TEST_1` and the entry is non-NULL; otherwise the
    vanilla `sMessageTextPointers` path is unchanged
  - landed `a148b76`; gates: `content-check`, `content-tables-check`,
    `hack-build`, `hack-smoke` (static + 600-frame boot) PASS; normal
    `ca33f434…`, shifted `5888a563…`, reordered `9dac0a4b…` unchanged;
    `make -f Makefile.shift test` (boot + 4k input), `audit`, `check_relocs`
    PASS; linked `HackTextEntryLedgeSignal` (`0x0879b9a8`) ROM bytes equal the
    preproc words
  - display in game is still unproven: no entry warp yet, so the banner is
    never drawn (HACK-008d4)
  - out of scope: entry warp, enemy, doors, save/load
- [DONE] HACK-008d3 (engine/content) — hack spriteset selection + Echo Hunter
  - **fixed a latent 008c2 bug**: the generated room entry's
    `defaultSpriteset = 255` fell back to the empty `sSpritesetPointers[129]`,
    so every spawn slot resolved through `gSpritesetSpriteIds[] = 0x10`
    (`PSPRITE_UNUSED_16`); the save pad, data pad and message banner had been
    spawning as placeholders and the d2 text could never draw
  - `gen_content_tables.py` now emits `hack/gen/sprite_tables.h` with the
    manifest `(spriteId, gfxSlot)` pairs + `0x00` terminator and a room-indexed
    pointer list; tracked shim `hack/include/hack/sprite_tables.h`;
    `SpriteLoadSpriteset` selects it for `AREA_TEST_1` with a non-HACK macro
    expansion that keeps the baseline tokens identical
  - `SPRITE_ECHO_HUNTER = 0xCF` is resolved by `tiled_to_room.py` from
    `hack/include/hack/ids.h` (plus a `parse_c_enum` brace fix for
    `typedef enum`); Entry Ledge has spriteset slot 6 and spawn record 3
  - runtime proxy: the table/spawn data keep 0xCF, but `SpriteInitPrimary`
    stores `PSPRITE_HORNOAD` and the spriteset/gfx/pal loads proxy 0xCF, so no
    baseline `PSPRITE_END`-sized array is indexed out of bounds; the enemy runs
    Hornoad data as a golden-path clone (custom AI/art is HACK-004b)
  - evidence: IWRAM dump shows `gSpritesetSpriteIds = 1F 1E 12 41 62 21 CF`,
    gfx slots 0..6, and live sprites `ids=1F,1E,21,12` with status
    `0003/0003/0013/8003` (save pad, data pad, message banner, Echo Hunter)
  - landed `1f73189`; gates: `content-tables-check`, `content-check`,
    `hack-build`, `hack-smoke`, `hack-room-check` (`FINAL_EVENT ... area=7
    room=0`, `main=1`, `frame_counter=29861`) PASS; normal `ca33f434…`,
    shifted `5888a563…`, reordered `9dac0a4b…` unchanged; `Makefile.shift
    test`, `audit`, `check_relocs` PASS
  - next: 008d4b (doors, save/load, golden-path doc); the banner now spawns,
    so its text display is the first thing to assert there
- [DONE] HACK-008d4a (engine/qa) — hack entry warp + room-load check
  - ordering changed by the manager: without an entry warp neither the d2 text
    nor the d3 enemy can be behaviour-tested, so the warp landed first
  - `src/in_game.c` `InitAndLoadGenerics()`, one `#ifdef HACK` block before
    `RoomLoad()`: sets `gCurrentArea = AREA_TEST_1`, `gLastDoorUsed = 0` and a
    Samus spawn at block (11,8)
  - **condition is `gUnk_3000be3 == 0`, not `gIsLoadingFile`**: AGBCC/asm
    evidence shows `gIsLoadingFile` is 0 on the New Game/empty-slot path and
    `SramRead_WorldData` clears it before the C room-load path, so it never
    fires there.  `gUnk_3000be3` is cleared by `Sram_CheckLoadSaveFile`, stays
    0 until the first room load and is set at the end of the same function, so
    door transitions keep the baseline destination
  - `tests/emulator/run.py --expect-event` (new, optional) passes `--final`,
    parses `FINAL_EVENT`, requires `area=7 room=0`, `main=1` and a live frame
    counter; `make hack-room-check` replays the committed 30k input with the
    existing harness binary (no `harness.c` rebuild needed)
  - landed `d6deecb`; `hack-room-check` PASS with
    `FINAL_EVENT frame=30000 counter=0 area=7 room=0 nav=0` and
    `INPUT_FINAL ... main=1 ... frame_counter=29862`; `hack-smoke`,
    `content-check`, baseline `ca33f434…`, shifted `5888a563…`, reordered
    `9dac0a4b…`, `make -f Makefile.shift test`, `audit`, `check_relocs` PASS
  - limits: HACK-only first-load warp; no door reciprocity, no save/load
    persistence, no route back into Entry Ledge, and the banner/enemy are now
    reachable but not yet exercised by a scenario
- [DONE] HACK-008d4b (qa/content) — liveness gate + golden-path doc
  - door decision: kept the **isolated one-room path** (doors stay suppressed;
    the entry warp is the only entrance).  Reciprocal records and the
    12-entry `sTest1Doors` shape belong to HACK-004a2
  - `tests/emulator/hack_room_check.py` + `make hack-liveness-check`: replays
    the verified input prefix 28450 (`frames=28451 frame_counter=28312`,
    IWRAM sha256 `e5347570…81a2`), resolves IWRAM symbols via `nm` (D-002
    fallback), and asserts the 7-entry spriteset
    `1F 1E 12 41 62 21 CF` / gfx slots `0..6` plus the four live spawns
    `1F/0003/0`, `1E/0003/1`, `21/0013/255`, `12/8003/3`
    (`SpriteData` stride 0x38; banner roomSlot is `UCHAR_MAX`)
  - negative paths verified: wrong table, wrong live entry and missing harness
    fail/skip with non-zero status; committed assertions were not weakened
  - `docs/golden-path.md`: build/run, entry warp, controls, what to see
    (room, pads, banner text, Echo Hunter clone), all check commands, known
    limits and the manual save/reset/continue step
  - landed `82364cf`; `hack-liveness-check`, `hack-room-check`, `hack-smoke`,
    `content-check`, normal `ca33f434…`, shifted `5888a563…`, reordered
    `9dac0a4b…`, `Makefile.shift test`, `audit`, `check_relocs` all PASS
  - automated save/load remains QA-030 (needs a valid SaveRAM fixture);
    HACK-008d is otherwise complete
- [TODO] QA-030 (qa/tools) — automated hack save/load on the Entry Ledge pad
  - needs a valid SaveRAM (checksum) or a TAS save sequence; depends on QA-027
    for `Sram_CheckLoadSaveFile` coverage
  - load the save in the hack build, assert `area=7 room=0`, the saved
    `gEventCounter` and that the banner/enemy/spriteset still load

- [PARK] PLAYTEST-001 (human) — M1 blockout playtest re-handed off 2026-10-21b
  - current artifact: `work/playtest/M1-2026-10-21b/mf_us_M1b.gba` (commit
    `7b65927`, SHA1 `d6dac5dbe4852d52ef02c03a40e7efe13c21d739`), README +
    feedback template in the same directory; the first artifact
    (`work/playtest/M1-2026-10-21/`) is superseded
  - scope per `docs/playtest.md`: 5-room flow, doors, camera, readability, save
    pad; pulse/boss/logs/art are explicitly out of scope
  - **PLAYTEST-FAIL 2026-10-21**: 花屏（tileset/背景错误，HUD/小地图不可读）
    and the banner shows a vanilla debug string; evidence filed as BUG-021 and
    BUG-022.  M1 is not signed off; do not start HACK-004b
  - **re-handed off 2026-10-21b**: `work/playtest/M1-2026-10-21b/mf_us_M1b.gba`
    (commit `7b65927`, SHA1 `d6dac5dbe4852d52ef02c03a40e7efe13c21d739`);
    BUG-021 and BUG-022 are fixed, the screen dump shows the generated blockout
    tileset, clean HUD/minimap and the authored banner text
  - **PLAYTEST-FAIL 2026-10-21b** (second attempt): 1) Samus/player sprite is
    invisible; 2) several room tile colours are wrong; 3) HUD/minimap textures
    are wrong.  Filed as BUG-024/025/026
  - **paused at the human's request**: rendering is not worth another
    round-trip now; the focus moves to engine comprehension and onboarding
    docs.  M1 stays failed/blocked; `HACK-004b` and M2 do not start
  - HACK-004a2b (event block + broad pad checks + dedicated transition/save
    scenario) stays queued for the M2 cycle; it does not block M1
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
