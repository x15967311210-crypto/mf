# Metroid Fusion hack — GDD (draft 1)

Status: **direction chosen; concept not signed off**.
Owned by the `game-designer` agent. The human has selected:

- Core experience: **exploration and atmosphere**
- First milestone: **15–30 minute vertical slice**
- Structure: **a new area / new sector**
- Ability design: **add one new ability**

## 1. High concept

A silent, derelict research deck where sound is the only reliable map.  Samus
recovers a resonance tool, reveals paths that were never meant to be found, and
learns why the deck was sealed.

## 2. Pillars

- **Silence is information.**  Darkness, muffled audio, and visible sound waves
  replace a conventional map.
- **Reveal, don't unlock.**  The new ability changes how the player reads a
  room, not just which door opens.
- **Dread with a small footprint.**  A compact deck, a few rooms, one creature
  that hunts by sound.
- **Reuse to ship.**  Vanilla tilesets/music and one enemy AI variant until the
  pipeline is proven.

## 3. Core loop

Enter a dark room → listen/scan → reveal a hidden route or object → avoid or
distract the sound-sensitive inhabitant → recover the next piece of the deck →
escape or descend.

## 4. Concept candidates

### A. Sector Null — The Silent Deck (recommended)

- A sealed acoustic-research deck attached to the BSL station.
- New ability: **Resonance Pulse** — a sonar ring that reveals hidden passages,
  highlights interactables, distracts/stuns sound-sensitive enemies, and
  triggers resonance locks.
- Atmosphere: darkness, fog, flickering emergency lights, distant metallic
  echoes; the pulse is the main light source.
- Reuse: Sector 6 dark tileset + lab tiles, recolored; one ambient track.
- Slice: 5 rooms (entry, dark atrium, resonance chamber, hidden conduit, nest).

### B. Sector Bloom — The Overgrown Conduit

- Bioluminescent overgrowth in a flooded research wing.
- New ability: **Spore Sense** — reveals organic paths and pacifies/attracts
  creatures.
- Strong atmosphere, but needs more original art and organic tileset work.

### C. Sector Forge — The Abandoned Foundry

- Industrial deck with heat, steam and broken machinery.
- New ability: **Magnetic Anchor** — traversal and machinery manipulation.
- More mechanical/traversal, less atmospheric; larger engine risk because it
  changes movement.

**Recommendation:** A.  It matches exploration/atmosphere, keeps the new ability
observational rather than movement-heavy, and can be built with heavy asset reuse.

## 5. Recommended vertical slice

Working title: **Sector Null — First Echo**

1. **Entry Ledge** — dark docking ledge; no pulse yet; teach lighting and sound.
2. **Silent Atrium** — vertical dark room; one Echo Hunter; a hidden route is
   visible only after the pulse.
3. **Resonance Chamber** — acquire the Resonance Pulse; scripted reveal; first
   use opens the way forward and exposes an optional lore cache.
4. **Hidden Conduit** — pulse-based path; one sound-sensitive enemy; optional
   shortcut back to the atrium.
5. **Choir Nest** — mini-boss or chase; pulse exposes the weak point; exit.

The slice should be playable in 15–30 minutes, with one optional secret and one
save point.  It can be prototyped in Test Area slots before it becomes a real
new `AREA_*`.

## 6. Ability: Resonance Pulse

- **Input:** TBD.  Candidates: `R + A`, `Select`, or a charged-beam alternate.
  Must not collide with missile/diagonal aim bindings.
- **Effect:** expanding ring; reveals hidden tiles/objects in radius; brief stun
  or distraction on sound-sensitive enemies; triggers resonance switches.
- **Cost:** cooldown first; ammo/energy cost only if the slice needs a resource
  loop.
- **HUD:** minimal icon in the slice; full pause/status integration later.
- **Save/event:** one ability bit and one event flag; save version plan required.

## 7. Story and event graph

Minimal, environmental.  The deck was sealed after an acoustic experiment
failed; the "choir" is an X adaptation.  The slice ends with a data core and a
locked door to the rest of the sector.  No long cutscenes in the slice.

## 8. Art, audio and reuse budget

- Tilesets: Sector 6 dark/lab tiles, recolored; no new tileset in the slice.
- Music: one ambient track, reused or a short original loop.
- Enemies: one Echo Hunter variant using an existing AI.
- Budget targets: TBD after a content spike.

## 9. Technical notes and risks

- A real new sector needs `AREA_END`, room/door/scroll/event arrays, minimap and
  connections expanded.  The slice should use Test Area slots first; promote to
  a new area only after the behavior suite is green.
- A new ability touches input, HUD, pickup, save, events and room data.  The
  slice should prototype it as a scripted tool before full pause/status work.
- Darkness/fog effects already exist, but audio timing under the C engine is
  unverified; add a behavior scenario.
- Controls must be checked against the vanilla bindings before implementation.

## 10. Open questions for the human

1. Does **Sector Null / Resonance Pulse** fit the atmosphere you want?
2. Should the slice end with a **mini-boss**, a **chase**, or an **event-only**
   reveal?
3. Do you want the pulse to be **free with cooldown** or **cost energy/ammo**?
4. Any preference for the control binding, or should the designer/engine team
   choose after checking vanilla bindings?
