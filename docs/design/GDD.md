# Metroid Fusion hack — GDD (draft 1)

Status: **direction signed off; slice details in review**.
Owned by the `game-designer` agent. The human has selected:

- Core experience: **exploration and atmosphere**
- First milestone: **15–30 minute vertical slice**
- Structure: **a new area / new sector**
- Ability design: **add one new ability**
- Concept: **Sector Null — The Silent Deck**
- Slice ending: **a teaching mini-boss**
- Pulse economy: **cooldown, no ammo/energy cost**
- Story tone: **mystery / archaeology**

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
- **Stillness is survival.**  Standing still breaks a sound lock; the pulse is
  loud and can attract what is listening.
- **Reuse to ship.**  Vanilla tilesets/music and one enemy AI variant until the
  pipeline is proven.

## 3. Core loop

Enter a dark room → listen → pulse to reveal a route/object (and risk being
heard) → freeze to break a sound lock → avoid or distract the inhabitant →
recover the next piece of the deck → escape or descend.

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

- **Input:** engine team to choose after auditing vanilla bindings; candidates
  are `R + A`, `Select`, or a charged-beam alternate.  Must not collide with
  missile/diagonal aim bindings.
- **Effect:** expanding ring; reveals hidden tiles/objects in radius; brief stun
  or distraction on sound-sensitive enemies; triggers resonance switches.
- **Noise:** the pulse is loud.  Using it near a listener pulls attention; this
  is the risk side of the reveal/stillness loop.
- **Cost:** cooldown only, no ammo/energy cost (signed off).
- **HUD:** minimal icon in the slice; full pause/status integration later.
- **Save/event:** one ability bit and one event flag; save version plan required.

## 6.1 Mini-boss: The Cantor

A blind, sound-hunting X adaptation that anchors the slice's climax.  It should
teach the pulse and the stillness loop, not test execution for five minutes.
Signed off: three phases, pulse-revealed organs, stand-still sound-lock break.

- **Arena:** Choir Nest, mostly dark; three resonance organs/crystals are
  invisible until pulsed.
- **Phase 1 — Listening:** the Cantor patrols; pulse reveals the organs; its
  sonar scream charges toward the player's last known position.  Standing still
  breaks the lock; moving while it listens invites a charge.
- **Phase 2 — Chorus:** it destroys one light/speaker and spawns a decoy echo;
  the player must pulse to find the real body and hit the exposed organ.
- **Phase 3 — Core:** all organs destroyed; the core opens for missiles/charge
  beam; one last scream, then the exit unlocks.
- **Reward:** data core + event flag; no new permanent upgrade in the slice.
- **Reuse:** start from an existing multi-part boss AI, reskin one enemy; the
  exact vanilla base is an engine-team decision.

## 7. Story and event graph

Mystery/archaeology, delivered through discoverable logs and environmental
fragments, not a long cutscene.

- The deck was built to study sound as a containment signal for the X.
- The researchers tried to "teach" the X a human choir; the Cantor is the
  result.  The final log reveals the deck was sealed from the inside.
- The slice ends with a data core and a locked door to the rest of the sector.
- Text budget: 3–4 short log entries; one optional hidden message; no Adam
  conversation in the slice.

## 8. Art, audio and reuse budget

- Tilesets: Sector 6 dark/lab tiles, recolored; no new tileset in the slice.
- Music: one ambient track, reused or a short original loop.
- Enemies: one Echo Hunter variant using an existing AI.
- Budget targets: TBD after a content spike.

Room-by-room layout: `level-layout.md`.

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

Layout is signed off in `level-layout.md`.  Remaining design questions:

1. Does the Cantor attack set in `boss-cantor.md` feel right (charge, sweep,
   decoy, core shockwave)?
2. Should the optional secret be a **missile tank** (power) or a **lore log**
   (atmosphere), or one of each?
3. Music direction: low ambient drone, or a sparse melodic motif?
4. Should the final data core be a **story beat** or just a completion flag?
