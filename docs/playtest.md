# Human playtest protocol

The human is the creative director and the final playtest gate.  **Every major
milestone stops for a human playtest before the next milestone starts.**

This is a hard gate, not a status update.  The manager must not mark a
milestone done, remove its task, or start dependent work until the human has
played the build and signed off (or filed blocking feedback).

## Cadence

| Gate | Build | What the human tests | Not yet in scope |
|---|---|---|---|
| **M0** | Shiftable engine boots | Boot/title, vanilla smoke, save/load | new content |
| **M1** | First Echo blockout | 5-room flow, doors, camera, dark-room readability, save pad | pulse, boss, final art |
| **M2** | Pulse prototype | pulse reveal, cooldown, noise/attention, stealth timing | boss, full HUD |
| **M3** | Cantor prototype | three phases, organ reveal, stillness, death/restart | polish, final audio |
| **M4** | Content-complete slice | full 15–30 min run, logs, secret, data core, save | balance polish |
| **M5** | Release candidate | final balance, performance, save compatibility | release packaging |

M0/M1 are allowed to be ugly.  The question is whether the **feel and flow**
work, not whether the art is final.

## Handoff

The manager produces:

```text
work/playtest/<gate>-<date>/
├─ mf_us_<gate>.gba        # never committed; local only
├─ README.md               # what to test, controls, known issues
└─ feedback.md             # filled by the human
```

Every handoff includes:

- exact build command and commit SHA;
- warp/cheat instructions to reach the slice (debug menu or test scenario);
- expected duration;
- known issues and explicitly out-of-scope items;
- a one-page script: "do this, then this, then this".

No ROM, savestate, screenshot with original graphics, or extracted asset is
committed or shared outside the local machine.

## Playtest script shape

1. Boot and reach the slice in under 2 minutes.
2. Traverse the 5 rooms without using debug tools.
3. Trigger the main mechanic and the optional secret.
4. Fight the Cantor (when present).
5. Save, quit, reload, confirm state.
6. Try to break it: leave the route, backtrack, die intentionally, pause.

## Feedback template

The human fills `feedback.md`:

```md
## Gate: M2
Build: <sha>
Duration: <minutes>

### Feel (1–5)
- Movement:
- Pulse:
- Stealth:
- Atmosphere:

### Clarity
- Did you know where to go?
- Did the pulse read clearly?
- Did the Cantor telegraph its attacks?

### Bugs / softlocks
- ...

### Keep / change
- Keep:
- Change:
- Cut:
```

The manager turns every blocking item into a `BUG-*` or `PLAYTEST-*` task and
does not advance the gate until the human signs off.

## Gate status vocabulary

- `PLAYTEST-REQUESTED` — build handed over, waiting for the human.
- `PLAYTEST-FEEDBACK` — human played; issues filed.
- `PLAYTEST-PASS` — human signs off; next milestone may start.
- `PLAYTEST-FAIL` — blocking issues; fix and re-hand.

## Recorded sign-offs

| Gate | Date | Build | Result |
|---|---|---|---|
| M0 | 2026-10-18 | fixed shifted `a822b2d8...` | decision A: mGBA 0.11 authoritative; controlled map pass, but fresh Navigation Room/computer dialogue reopened M0 (BUG-009); BizHawk 2.3.x issue parked as BUG-008 |
