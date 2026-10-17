# Sector Null — First Echo: room layout (draft 1)

Status: **layout signed off**.
Owned by `game-designer`.  Parent: `GDD.md`, `vertical-slice.md`.

Signed off: Atrium is the vertical set-piece; the Conduit shortcut is two-way;
one save pad at Entry Ledge; the Cantor arena is 1×2 screens.

Dimensions are in **screens** (about 15×10 blocks each), not exact block numbers.
The content team converts them to room width/height and clipdata.

## Flow

```
Entry Ledge
   → Silent Atrium (vertical)
        → Resonance Chamber (pulse pickup)
             → Hidden Conduit (optional shortcut back to Atrium)
                  → Choir Nest (The Cantor)
```

The slice is a loop, not a corridor: the Hidden Conduit opens a shortcut back to
the Atrium, so the player can return for the optional secret before the boss.

## Rooms

### 1. Entry Ledge — 1×1 screen

- Dark landing ledge; broken lights; one save pad.
- No pulse yet; teach movement, light, and the sound of the deck.
- Exit right to the Atrium.
- One short log: "Deck 07 sealed by order of the research director."

### 2. Silent Atrium — 1×3 screens (vertical)

- Tall dark atrium with a collapsed central platform.
- One **Echo Hunter** patrols the lower half; it reacts to pulse noise.
- Hidden upper route is invisible until pulsed; it leads to an optional log and
  a missile tank.
- Exit top-right to the Resonance Chamber; the lower route is a dead end with
  atmosphere.
- Stealth teaching: stand still behind cover to break the Hunter's sound lock.

### 3. Resonance Chamber — 2×1 screens

- Intact lab room, one working light, resonance equipment.
- **Resonance Pulse pickup** on a pedestal; scripted first pulse reveals the
  sealed door and a short log.
- Exit right to the Hidden Conduit; a one-way drop returns to the Atrium.
- This is the slice's midpoint; the player can backtrack for the Atrium secret.

### 4. Hidden Conduit — 3×1 screens

- Maintenance shaft; mostly invisible platforms revealed by pulses.
- One Echo Hunter nests in the middle; pulse can distract it.
- Two-way shortcut door back to the Atrium, so the player can return for the
  optional secret before the boss.
- Exit right to the Choir Nest.
- One hidden log behind a pulse-only wall.

### 5. Choir Nest — 1×2 screens

- Boss arena; three resonance organs on walls/ceiling, invisible until pulsed.
- **The Cantor** enters after the player steps in; arena doors lock.
- Phase 1: listening/charge; stand still to break the lock.
- Phase 2: one light/speaker destroyed, decoy echo; pulse finds the real body.
- Phase 3: core exposed; missiles/charge beam finish it.
- On defeat: data core event, exit door unlocks, one final log.

## Encounters and pacing

| Beat | Room | Purpose |
|---|---|---|
| Teach light/sound | Entry | no combat |
| Teach stealth | Atrium | one Echo Hunter |
| Teach pulse | Resonance Chamber | pickup + scripted reveal |
| Combine pulse + stealth | Conduit | hidden path + Hunter |
| Test both | Choir Nest | The Cantor |

Target time: 15–20 minutes first play, 8–12 minutes on replay.

## Optional secret

- Atrium upper alcove: pulse-only platform, one missile tank, one log.
- Conduit hidden wall: one log that hints at the Cantor's origin.
- Missing either secret must not block the exit.

## Events and save

- `EVENT_PULSE_ACQUIRED` — set on pickup; enables pulse and HUD marker.
- `EVENT_CANTOR_DEFEATED` — set on boss death; unlocks exit and final log.
- `EVENT_DATA_CORE_RECOVERED` — set on interaction; slice completion marker.
- One save pad in Entry Ledge; no second save room.  Boss death restarts at the
  Choir Nest entrance with the pre-boss state.
- New ability bit: one unused/added bit; save-version plan required.

## Resolved layout questions

- Vertical set-piece: **Silent Atrium**.
- Conduit shortcut: **two-way**, supports the optional secret.
- Save points: **one** at Entry Ledge; boss death restarts at the arena entrance.
- Cantor arena: **1×2 screens**.
