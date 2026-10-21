# Sector Null — content IDs and save version

Status: **decided** (HACK-002).  This document is the source of truth for the
IDs and save-state decisions used by HACK-003/HACK-004a.

Scope: the five-room M1 blockout and the later vertical slice.  This is not a
new save format and not a new area.

## Corrected baseline numbers

The earlier working notes in this task had two wrong numbers.  Use these:

```text
EVENT_END (current)     0x6E
EVENT_ESCAPED_ON_SHIP   0x6D
save slots              0x200 + 0x1200*n, n = 0..5
last save byte          0x6E00
unused gap              0x6E00..0x6FFF (512 bytes)
```

The gap is **not** per save slot and is not used for per-file flags in this
plan.

## 1. Resonance Pulse

Resonance Pulse is represented by a **new event**, not by a new ability mask
bit:

```c
EVENT_RESONANCE_PULSE_ACQUIRED = 0x6F
```

Pulse availability is:

```c
gEventCounter >= EVENT_RESONANCE_PULSE_ACQUIRED
```

Why:

- `SMF` bits 0–7, `BF` bits 0–4 and `MBF` bits 0–5 are all assigned
  (`include/constants/samus.h`); there is no free equipment bit.
- `struct Equipment` is saved byte-for-byte at save `+0xB4`; adding a field
  would change the record layout and is not needed.
- `gEventCounter` is already a saved `u8` at slot `+0x21`; an old save has a
  value at or below `0x6D`, so the pulse check is false and old saves load.
- The pulse must not be added to `sObtainItemEvents`/`sAbilityRamValues`
  (`src/event.c`).  Those tables are tied to the vanilla ability-count and
  message/audio paths; the pulse is a story/ability event with its own check.

Trade-off: `gEventCounter` is a **monotonic high-water mark**, not a flag set.
It cannot represent independent “log 1/2/3 read” states.  Logs therefore stay
re-readable; per-log persistence is a future save-byte task (see non-goals).

## 2. Event block

Reserve a contiguous block after the vanilla enum:

```text
0x6E  EVENT_SLICE_NULL_STARTED
0x6F  EVENT_RESONANCE_PULSE_ACQUIRED
0x70  EVENT_LOG_DECK_07_SEALED        (reserved; not set by the slice)
0x71  EVENT_LOG_CHOIR_EXPERIMENT      (reserved; not set by the slice)
0x72  EVENT_LOG_CANTOR_ORIGIN         (reserved; not set by the slice)
0x73  EVENT_LOG_DIRECTOR_FINAL        (reserved; not set by the slice)
0x74  EVENT_ECHO_HUNTER_INTRO_SEEN    (optional)
0x75  EVENT_CANTOR_ENGAGED
0x76  EVENT_CANTOR_DEFEATED
0x77  EVENT_DATA_CORE_RECOVERED       (slice complete)
```

After the block:

```c
EVENT_END = 0x78
```

Implementation work for HACK-003/HACK-004a:

- Extend the enum in `include/constants/event.h` and `EVENT_END`.
- Add entries to `sEventLocationAndNavigationInfo` (`src/data/event_data.c`) and
  `sPauseDebugEventNames` (`src/menus/pause_debug.c`).
- Keep the IDs contiguous; `EventCheckRoomHasEventTrigger` walks
  `gEventCounter + 1`, and the tables are sized by `EVENT_END`.
- The optional missile tank needs **no event**: use
  `gCollectedTanks[AREA_TEST_1]` and `gEquipment.maxMissiles`.
- Cantor restart needs **no extra ID**: `EVENT_CANTOR_ENGAGED` set and
  `EVENT_CANTOR_DEFEATED` clear means “respawn at the arena entrance”.
- Logs are re-readable and do not set their reserved events in the first slice.

### Blocking event-counter interaction

Several vanilla checks use broad thresholds around
`EVENT_ORBIT_CHANGE_IMPLEMENTED` (0x67), including:

- `src/event_checks.c`: `EventCheckWith_SaveDisabled`,
  `EventCheckWith_NavigationDisabled`, `EventCheckWith_RechargeDisabled`,
  `EventCheckAfter_OrbitChange`
- `src/room_effect.c` (operations-room effect)
- `src/room.c` (BG3 direction)
- `src/color_fading.c` (escape-failed cutscene)

Consequences once the pulse sets `gEventCounter` to `0x6F`:

- the Entry Ledge **save pad stops working** because `save_pad.c` calls
  `EventCheckWith_SaveDisabled`;
- navigation and recharge pads follow the same broad check;
- BG3 scroll direction can flip.

This is a design constraint, not an ID change.  HACK-004a must do one of:

1. add an explicit “Sector Null slice” exception to the broad checks, or
2. make those checks compare against the exact vanilla event range instead of
   `>= 0x67`.

The slice's “save → load preserves pulse state” acceptance scenario cannot
pass until this is fixed.  Track it as a HACK-004a blocker; do not work around
it by lowering the pulse event.

## 3. Rooms and doors

Use **`AREA_TEST_1` (area index 7)** only.  Do not use `AREA_TEST_2/3` until the
`MAX_AMOUNT_OF_AREAS`/designated-initializer audit is complete.

Rooms:

```text
room 0  Entry Ledge
room 1  Silent Atrium
room 2  Resonance Chamber
room 3  Hidden Conduit
room 4  Choir Nest
```

`sTest1RoomEntries` currently has four entries (plus its terminator) and
`sTest1Doors` has twelve entries.  HACK-003 must extend the room table to five
active rooms, keep the door array shape/terminator, and document the change as
an ADR because `src/data` is baseline-owned.

Door indices (implemented in the generated HACK overlay):

```text
0/1   Entry Ledge <-> Silent Atrium
2/3   Silent Atrium <-> Resonance Chamber
4/5   Resonance Chamber <-> Hidden Conduit
6/7   Hidden Conduit <-> Choir Nest
8/9   Hidden Conduit <-> Silent Atrium (optional shortcut)
10/11 Choir Nest <-> Entry Ledge (post-boss return)
```

`HACK-004a2a` emits all 12 records with reciprocal `dstDoor` values and a
`DOOR_TYPE_NONE` terminator; the baseline `sTest1Doors[0]` self-loop is not
used by the overlay. Door transitions and hatch/lock behaviour still need the
dedicated scenario in `HACK-004a2b`.

## 4. Save version

Decision: **do not bump the save version and do not resize `SaveFile`**.

- Header string remains `MetroidAGB-EUVerE004`; `SRAM_V112` is an SDK string,
  not the save version.
- `SaveFile` remains `u8 todo[0x1200]`.
- New state rides in the existing `gEventCounter` at slot `+0x21`;
  `struct Equipment` stays untouched at `+0xB4`.
- The save checksum span (`0x900` bytes from the slot start) covers `+0x21`
  and `+0xB4`, so the vanilla save code recomputes it normally.
- Vanilla saves load in the hack (their counter is at or below `0x6D`).
- Hack saves with events `>= 0x6E` are not promised to work in vanilla; this is
  an explicit unsupported cross-load, not a crash path.
- The `0x6E00..0x6FFF` gap is not used for per-file state in this plan.

## 5. ID allocation table

| Type | ID/range | Owner | Collision status | Consumer |
|---|---|---|---|---|
| ability/pulse | event `0x6F` | HACK-004a/b | reserved, new | pulse check/HUD |
| slice start | event `0x6E` | HACK-004a | reserved, new | room/event script |
| logs 1–4 | events `0x70–0x73` | HACK-004d | reserved, not set in M1 | log UI (re-readable) |
| Echo Hunter intro | event `0x74` | HACK-004b | reserved, optional | enemy intro trigger |
| Cantor engaged/defeated | events `0x75/0x76` | HACK-004c | reserved, new | boss state/restart |
| data core/slice complete | event `0x77` | HACK-004d | reserved, new | story/exit gate |
| rooms 0–4 | `AREA_TEST_1` room IDs | HACK-003 | Test 1 extension | room loader |
| doors 0–9 | `sTest1Doors` indices | HACK-003/004a | provisional; table audit required | transitions |
| missile tank | `gCollectedTanks[AREA_TEST_1]` | HACK-004d | vanilla field | item collection |

## Non-goals

- No new ability mask bit or `Equipment` field.
- No `SaveFile` resize or save-header/version bump.
- No new `AREA_*`; use Test Area 1.
- No per-log persistent flags in M1; logs are re-readable.
- No second save slot or minimap-area promotion.
- No use of Test Area 2/3 until the `MAX_AMOUNT_OF_AREAS` audit is complete.

## Follow-ups

HACK-003 / pipeline:

- extend `sTest1RoomEntries` to five rooms under an ADR;
- implement the room/door tables and the synthetic fixture round-trip;
- finalize door indices 0–9 after the `sTest1Doors[0]` audit.

HACK-004a / blockout:

- fix the `>= EVENT_ORBIT_CHANGE_IMPLEMENTED` broad checks so the save pad and
  navigation/recharge pads still work after `0x6F`;
- add the event-table entries for `0x6E–0x77`;
- wire save/load and the entry warp.

HACK-004d / content-complete:

- keep logs re-readable; if per-log persistence is required, design a saved
  bitfield outside the `gEventCounter` high-water path;
- set the data-core/slice-complete event and test the exit.
