# Vertical slice brief — First Echo (draft 1)

Status: **concept proposed; waiting on human sign-off**.
Owned by the `game-designer` agent.  Parent: `GDD.md` concept A.

## Fantasy

The player enters a silent, dark research deck, learns to read the room with a
sonar pulse, and escapes a creature that hunts by sound.

## Scope

- 5 rooms, prototyped in Test Area slots before a real new `AREA_*`.
- 1 new ability: **Resonance Pulse**.
- 1 enemy variant: **Echo Hunter** (reuses an existing AI, reacts to pulses).
- 1 mini-boss **or** chase **or** event-only reveal (human to choose).
- 1 optional secret and 1 save point.
- Placeholder text and one ambient track.

## Room flow

1. **Entry Ledge** — dark, no pulse; teach lighting/audio.
2. **Silent Atrium** — vertical room, Echo Hunter, hidden route revealed later.
3. **Resonance Chamber** — acquire the pulse; scripted reveal; opens the way.
4. **Hidden Conduit** — pulse path, optional shortcut back to the atrium.
5. **Choir Nest** — mini-boss/chase/event; pulse exposes the weak point; exit.

## Acceptance scenarios

- Boot → warp/enter → complete the slice → exit without crash or softlock.
- The pulse reveals the hidden route and the optional secret.
- The Echo Hunter reacts to the pulse as designed.
- Save → load preserves ability/event/room state.
- Vanilla rooms outside the slice behave unchanged (differential smoke).
- No new lag frames beyond the agreed budget; no OAM overflow.

## Technical prerequisites

- `SHIFT-008` shift test green (padded/reordered build boots).
- Test Area room slots and warp/telemetry scenario.
- Scripted pulse prototype before HUD/pause integration.
- Control binding checked against vanilla bindings.

## Cut lines

- Full pause/status icon can wait; a temporary HUD marker is enough for the
  slice.
- Mini-boss can become a chase if the boss AI budget is too high.
- New music can be replaced by a reused ambient track.
- New tileset can be replaced by recolored Sector 6/lab tiles.
