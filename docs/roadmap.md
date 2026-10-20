# Roadmap and gates

## North star

A shiftable C engine that behaves like Metroid Fusion, then a new hack built on
top of it.  "Shiftable" means code and ROM data can change size and order while
the game still boots and behaves correctly.

## Human playtest gates

The human playtests every major milestone before the next one starts.  See
`docs/playtest.md`.  The gates are **M0** shiftable boot, **M1** blockout,
**M2** pulse, **M3** Cantor, **M4** content-complete slice, **M5** release
candidate.  A gate only passes with human sign-off; blocking feedback becomes
`BUG-*` / `PLAYTEST-*` tasks.

## Phase S0 — behavior harness

Deliverables:

- libmgba headless runner (or mGBA Lua fallback), input replay, telemetry reads.
- Vanilla scenarios: boot/title, file select, new game, pause/status, save/load,
  navigation, room sweep, intro/ending, game over.
- Static ROM/header smoke that works without an emulator.

Gate **S0**: every core scenario is repeatable on the baserom and reports a
clear pass/fail.

## Phase S1 — relocation audit

Deliverables:

- `tools/shift/audit_asm.py`, `audit_blobs.py`, `map_symbols.py`.
- `docs/shiftability-audit.md` with counts: hardcoded ROM refs, blob pointer
  candidates, whitelist.
- `tools/shift/check_relocs.py` skeleton.

Gate **S1**: every ROM absolute reference is classified as code, data, RAM,
MMIO, header, or whitelisted; no "unknown" remains.

## Phase S2 — relocatable build

Deliverables:

- Hardcoded refs in non-disasm asm rewritten to symbols.
- Blob pointer tables converted to relocatable C/asm labels.
- Relocatable linker and `check_relocs` gate.
- `tools/shift/shift_test.py`: padding and section-reorder builds.

Gate **S2**: the padded/reordered build boots and passes the core behavior
scenarios.

## Phase S3a — hack-critical C

Deliverables:

- SRAM/Status 54 functions in C.
- Pause 25 + Navigation 27 functions in C.
- Hack-critical behavior suite.

Gate **S3a**: shiftable build + hack-critical C + scenarios green.  The hack
vertical slice may start.

## Phase S3b — full C engine

Deliverables:

- FileSelect/GameOver 53, Cutscene/Intro/Ending 217, Gunship 20 in C.
- Full behavior suite and shift test.

Gate **S3b**: 396/396 C-FUNC or VERIFIED, full suite green, `c-engine-complete`
tag.  This is the point where the engine is "fully C" in practice.

## Phase S4 — hack

Deliverables:

- GDD, ID registry, save version.
- Content pipeline: Tiled/PNG → room data, text, sprites.
- Vertical slice: 3 rooms + 1 enemy + 1 event, then full content.

Gate **S4**: playable slice sign-off, then content production.

## Current status

**M0 shiftable-boot gate: BLOCKED** — the headless 339001-frame gate now
passes normal to the ending (`1900 0009 0002 0100 109 0 63 0`) but fails
shifted at frame **114671** (BUG-016: raw `sBlob_6638a0_682fac` cutscene
table, OAM overflow/undefined exception) and reordered at frame **223045**
(BUG-011: room-14 branch).  BUG-013 native idle/focused checks pass on shifted
`012a2c95…` (merged `424fd7f`).  `PLAYTEST-000` human sign-off is still
pending.  BUG-010's elevator state is parked as an invalid post-entry capture;
QA-012 coverage is paused.  The post-link scan reports 74 latent pointer runs
(BUG-014); BUG-016 is the first confirmed hit, so that triage is now on the
critical path.  M1 blockout is paused; see `jira.md`.

Baseline evidence (2026-10-17):

- Vanilla static ROM smoke: **PASS** (SHA1 `ca33f434…`).
- Vanilla dynamic boot smoke: **PASS** — 600 frames, `frame_counter=578`,
  `sub_mode=0x0001`.
- SHIFT-005: **662/662** ROM literals rewritten to symbols; `make check` still
  matches SHA1; audit now reports **0 literals**, 697 `ldr` comments.
- SHIFT-006a/006b: all 10 pointer-like blobs converted to relocatable C;
  SHA1 preserved.
- SHIFT-005b/005c/006b4/006b5/006b6: 660 track headers, two `sound_code`
  pseudo-literals, and **1034 C ROM literals** rewritten to symbols.
- Static gates are green: `make check`, `audit`, `check-relocs-strict`,
  `smoke`.
- Shifted build (`. += 0x1000` after `intr_main`): static **PASS**, dynamic
  **FAIL** — `frame_counter=3`.  The remaining failure is a runtime/pointer
  issue documented in `docs/shift-test-diagnosis.md`; it is not an unclassified
  literal.
- Boot smoke now requires **450/600** frames, not just nonzero, so an early
  crash cannot pass.
