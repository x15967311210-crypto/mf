# Shift-test diagnosis (SHIFT-006c)

Status: **open — shifted boot still fails at `frame_counter=3`**.
Every static/relocation gate is green; the remaining failure is dynamic.

## Green gates

- `make check` after a full clean build: SHA1 `ca33f4348c2c05dd330d37b97e2c5a69531dfe87`
- `make -f Makefile.shift audit`: 0 open literals, 0 C ROM refs, 0 unknown
- `make -f Makefile.shift check-relocs-strict`: PASS
- `make -f Makefile.shift smoke`: PASS
- 1034 C ROM literals were rewritten to symbols (314 function / 720 data);
  816 in `src/data/sprite_pointers.c`. The rewrite is address-equivalent.

## Failure

```
SHIFT-BUILD: PASS
SHIFT-LAYOUT: PASS (AgbMain 0x08000230 -> 0x08001230, +0x1000)
SHIFT-STATIC: PASS
SHIFT-DYNAMIC: FAIL (frame_counter=3 < 450)
```

The shifted ROM stops advancing the main frame counter at 3. It is not a
straight-line crash: the CPU keeps executing ROM/IWRAM code, but the game state
does not advance.

## Evidence from mGBA tracing (local `/tmp` harnesses, not committed)

1. **PC trace.** Normalizing shifted PCs by `-0x1000`, baseline and shifted
   agree through frame 23. At frame 24:
   - baseline: stays in BIOS (`pc=0x1C4`), waiting;
   - shifted: returns to `CutsceneElevatorMonologueSetupOam` (`0x08099F1C`,
     baseline `0x08098F1C`) and then to `CutsceneProcessElevatorScrolling`.
2. **SWI trace.** Baseline calls `SWI 2` (Halt) from `InitTrack+0x86` at frame
   24; shifted does not take that path. Baseline then does `SWI 31`/`SWI 2`
   and reaches `SpecialCutsceneDrawAllOam`; shifted enters the cutscene setup
   without the `InitTrack` halt path.
3. **OAM corruption.** `gNonGameplayRam` OAM entry at `0x030017E4`:
   - baseline frame 24: `[+0x1C] = 0x0860AC18` (valid ROM pointer);
   - shifted frame 24: `[+0x1C] = 0x0860BC18` (correct +0x1000);
   - shifted frame 25: the cutscene setup writes bytes/halfwords to
     `0x03001800` (`0x0A`, `0x10A0`, `0x4463`, ...), overwriting the pointer.
4. **Bad reads.** `0x08099DEE` reads `0x10A00CCA`; `0x08098DBC` reads
   `0xF7F67D5E`. These are symptoms of the corrupted OAM state, not necessarily
   the first cause.

## Ruled out

- Interrupt table `sBlob_a5224_a5258`: every pointer is correctly +0x1000 in
  the padded ROM.
- Track headers: 660 headers now point at the relocated sound blob.
- `sound_code.s` bare pseudo-literals: fixed.
- C literals: 1034 rewritten; SHA1 preserved.
- Raw pointer-like blobs: 10/10 converted; 37 remain raw by design.
- Linker fixed ROM addresses: only the hardware header/entry and RAM/MMIO.

## Hypotheses to investigate next

1. **InitTrack/audio path divergence.** Why does shifted skip the `SWI 2`
   halt path at `InitTrack+0x86`? Compare `InitTrack` inputs/state at frame 24
   (track pointer, voice table, channel flags) between baseline and shifted.
2. **Runtime-generated pointer table.** A table built at runtime from a raw
   data blob or an asm table may still contain a stale/incorrect pointer. Watch
   the first write to `gNonGameplayRam+0x1C` and the source of the value.
3. **Data vs code relocation split.** Build a data-only reorder (swap two
   `.rodata` objects, no padding) and a code-only perturbation to identify
   which side still has an absolute reference.
4. **Interrupt/BIOS timing.** The shifted path returns from BIOS earlier than
   baseline. Check `gVBlankRequestFlag`, `REG_IE`/`REG_IF`, and the
   `InterruptCode` callback table at the frame-24 boundary.
5. **Shift-test method.** If data-only reorder passes but padding fails, the
   remaining issue is code-address-specific (function pointer/code copy), not
   data relocatability.

## Do not

- Do not weaken the 450/600 liveness gate.
- Do not claim shiftability or start M0 until `SHIFT-CHECK: PASS`.
- Do not commit the local trace harnesses or `work/` artifacts.

## Update — frame-25 OAM overflow (local mGBA hooks)

The first corrupt state is a **cutscene/intro OAM overflow**, not the illegal
opcode itself:

- At frame 25 the shifted build runs `CutsceneElevatorMonologueInit` (PC
  `0x0809A766`, baseline `0x08099766`) and writes **`gNextOamSlot = 0x96`**
  (150) from the byte at source pointer `0x0860A22E` (baseline path uses
  `0x086098B0` and writes 1..8).
- `gNextOamSlot` is at IWRAM `0x030011EE`; the normal `SpecialCutsceneDrawOam`
  path increments it 1..8 then resets it. A value of 150 makes the OAM writes
  run past the 20-entry array and overwrite `gVBlankCallback` at
  `0x030019C4` (`gHBlankCallback` becomes `0x5B454D34`, ASCII `M4EU`).
- `CallbackCallVblank` then `bl`-indirects through the corrupted
  `gVBlankCallback`, lands mid-instruction in ARM state, and the main loop
  stops (`frame_counter=3`).
- `gCurrentCutscene`, `gMainGameMode`, `gSubGameMode1/2`, `gCurrentDemo`,
  `gDemoPlaying`, `gEventCounter` are identical between baseline and shifted at
  frames 23–25, so the divergence is inside the OAM/pointer setup, not the
  mode state.
- The source pointer `0x0860A22E` is a valid shifted address inside
  `sBlob_6094d0_60b148`; it is not a stale unshifted pointer. The code is
  selecting the **wrong data entry** (or interpreting a tilemap/graphics byte
  as an OAM count).
- `0x100` padding is a false pass: it corrupts state but happens to let the
  frame counter advance; `gCurrentArea` becomes 39.

Next focus: find where the OAM data pointer (`r10` in the setup loop) and
`gNextOamSlot` count are selected. Compare the baseline and shifted register
values at the instruction that loads the pointer from the OAM table. Check for
an index/length derived from a ROM address or a raw table entry that was not
converted. The illegal opcode and `gVBlankCallback` corruption are downstream.

## Update — after the FrameData carve (frame 86)

`SHIFT-006c2` carved the 9-entry table out of `sBlob_6094d0_60b148`; SHA1
stayed `ca33f434…`.  The shifted build now advances to **frame 86** instead of
3, so the carve was correct but not sufficient.

New first corruption: at frame 107, `CutsceneElevatorMonologueInit`
(`PC 0x08099E3E`) again writes through `gVBlankCallback`:

```
WRITE16 frame=107 pc=08099E3E lr=08099D75 addr=030019C4 value=000041D2
  r9=030016A0 r10=0860AA36 r12=030019C4 nextslot=0
```

- `r9` is `gNonGameplayRam + 0x21C` (`0x030016A0`), `r12` is
  `gVBlankCallback` (`0x030019C4`). The code is copying tilemap/frame words
  from `0x0860AA36` into a `gNonGameplayRam` buffer and writes one word past
  the buffer end.
- `0x0860AA36` is inside the carved `sBlob_6094d0_before`; it is a valid,
  correctly shifted source. The destination/buffer extent is the problem, not
  a stale source pointer.
- Earlier, the shifted build reaches intro code around frame 18 (setting
  `gVBlankCallback` to `0x0809A941` / `0x0809A8F5`); the baseline does not set
  those callbacks until frame 24. This suggests the shifted init path runs
  intro/cutscene code **before** the main loop has completed its Halt/timing
  setup, then overflows a `gNonGameplayRam` buffer.
- The missing `SWI 2` / `InitTrack` Halt is still a candidate for the initial
  timing divergence; fixing individual overflows is whack-a-mole unless that
  path is understood.

Next focus: trace `InitTrack` and the first callback setup at frames 18–24 in
both builds, and compare the call stack/state that makes the shifted build
enter intro code early. Then decide whether the correct fix is the init/Halt
path or another raw table.
