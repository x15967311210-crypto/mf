# The Cantor — mini-boss spec (draft 1)

Status: **signed off for implementation**.
Owned by `game-designer`.  Parent: `GDD.md`, `level-layout.md`.

Locked: four attacks (charge, sonar sweep, echo decoy, core shockwave), three
organs + core, 1×2 arena, low ambient drone, data core = story beat + flag.

## Fantasy

A blind X adaptation that hears the player before it sees them.  The fight is a
conversation between the pulse (reveal) and stillness (hide), ending with a
short execution window.

## Arena

- **1×2 screens**, dark; three resonance organs: left wall, right wall, ceiling.
- Two light/speaker fixtures; one is destroyed in phase 2.
- Arena doors lock on entry; death restarts at the arena entrance with the
  pre-boss state.
- No pits or instant-death hazards in the slice.

## Organ / core model

- **Resonance organs** are invisible until pulsed.  Each organ has a small
  health pool (placeholder: 6 missile-equivalent hits).
- Destroying all three exposes the **core** for phase 3.
- The core has a larger pool (placeholder: 30 missile-equivalent hits) and is
  only vulnerable after the last organ dies.
- Pulse has a cooldown; it is loud and can pull the Cantor's attention.

## Phase 1 — Listening

**Intent:** teach pulse → organ and stillness → break lock.

- The Cantor circles the dark arena, emitting a low pulse.
- If the player moves or fires while it is listening, it locks the last known
  position and **charges** after a short screech telegraph.
- **Standing still** (velocity zero, no attack input) breaks the lock; the
  Cantor overshoots or loses interest.
- After a charge into a wall, it is briefly stunned and one organ is exposed
  even without a pulse.
- Player job: pulse to find an organ, stand still to break the lock, shoot the
  organ during the recovery window.

## Phase 2 — Chorus

**Intent:** combine pulse with a decoy.

- At 2 organs destroyed, the Cantor destroys one light/speaker and spawns an
  **echo decoy**: a false body/organ that pulses like the real one.
- The real body has a slightly different echo timbre; the pulse reveals which
  is real (visual: real organ has a core pulse; decoy dissolves).
- New attack: a wide **sonar sweep** that forces the player to crouch/still
  behind cover rather than simply stand in the open.
- Player job: pulse, identify the real organ, avoid the sweep, destroy it.

## Phase 3 — Core

**Intent:** a short, readable execution phase.

- All organs dead; the core opens; the Cantor becomes aggressive.
- Attacks: radial **core shockwave** (jump/dodge), a short charge, and a
  scream that shakes the camera.
- Player job: missiles/charge beam on the core, dodge the shockwave, finish.
- On death: data core event, exit unlock, final log.

## Events and IDs (placeholders)

- `EVENT_CANTOR_STARTED`
- `EVENT_CANTOR_PHASE2`
- `EVENT_CANTOR_DEFEATED`
- `EVENT_DATA_CORE_RECOVERED`
- Sprite IDs: Cantor body, 3 organs, decoy; exact IDs assigned by content dev.

## Audio / visual

- Low ambient drone; sonar ring; sharp screech telegraph; wall-impact shake.
- Organ reveal: bright pulse ring and a short high tone.
- Decoy: same silhouette, wrong echo color/timbre.
- Death: core collapse, lights flicker, silence for one beat before the exit.

## Technical notes

- Reuse an existing multi-part boss AI; do not build a new boss framework.
- Stand-still detection: player velocity zero and no attack input for N frames.
- Pulse noise: a flag the boss AI reads; pulse near the boss raises attention.
- Darkness: reuse the dark-room background property; ensure organs are visible
  only through the pulse, not by palette accident.
- Budget: 1 boss sprite + 3 organs + 1 decoy within OAM/spriteset limits;
  content dev confirms slots.

## Acceptance scenarios

1. Enter arena → doors lock → phase 1 starts.
2. Pulse reveals at least one organ; standing still breaks a charge lock.
3. Destroying two organs triggers phase 2 and the decoy.
4. Pulse distinguishes the real organ; destroying the third opens the core.
5. Core dies → event set → exit unlocks → final log.
6. Player death → restart at arena entrance with pre-boss state; no softlock.
7. No OAM overflow, no new lag frames beyond the agreed budget.

## Sign-off

- Attack set: **charge, sonar sweep, echo decoy, core shockwave**.
- Optional secret: **missile tank + lore log**.
- Music: **low ambient drone**; Boss variation uses the same palette.
- Final data core: **story beat + completion flag**.

Any new boss idea goes to `docs/design/backlog.md`; this file is frozen for the
first slice.
