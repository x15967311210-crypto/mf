# mk/hack.mk — HACK=1 overlay build (HACK-008c1 / D-013).
#
# The hack build is the same engine and baseline data as `all`, compiled with
# -DHACK (C) and --defsym HACK=1 (assembly).  The baseline hooks are the narrow
# `#ifdef HACK` selections in src/room.c, src/scroll.c, src/sprite.c and
# src/text.c: the hack-owned room/door, scroll, spriteset and message-banner
# tables all live in ignored hack/gen/ headers behind tracked shims.  For
# HACK-008c1 those headers fall back to the baseline AREA_TEST_1 tables, so the
# overlay is empty; HACK-008c2/HACK-008d replace them with generated tables
# without touching this build boundary.  HACK-004a2a converts and links all
# five authored Test Area 1 rooms plus the 12 reciprocal doors; see HACK_ROOMS
# and HACK_ACTIVE_DOORS below.
#
# Isolation rules:
#   * the artifact, ELF, map, sha1 and preprocessed linker script live in
#     work/hack/, so mf_us.gba/.elf/.map are never replaced;
#   * HACK=1 implies OBJ_DIR=work/hack/obj, so the HACK objects never overwrite
#     the baseline objects a later `make` would relink;
#   * the static pattern rules below bind each prefixed object to exactly one
#     source rule, so a stale in-tree .s can never be assembled into the hack
#     ROM.
#
# Targets:
#   make hack-build   -> work/hack/mf_us_hack.gba (+ .elf/.map)
#   make hack-sha1    -> hack-build, then write work/hack/mf_us_hack.sha1
#   make hack-smoke   -> hack-build + static smoke + boot_smoke scenario
#
# This file is self-contained: every default uses `?=`, so command-line and
# main-Makefile definitions win.  Like mk/shift.mk it defines no `all`,
# `help` or `host-test` target.

PYTHON ?= python3
SHA1SUM ?= sha1sum

HACK_WORK ?= work/hack
HACK_STEM ?= $(HACK_WORK)/mf_us_hack
HACK_ROM ?= $(HACK_STEM).gba
HACK_SHA1FILE ?= $(HACK_STEM).sha1
HACK_OBJ_DIR ?= $(HACK_WORK)/obj
HACK_LD_SCRIPT ?= $(HACK_WORK)/linker.ld.pp
HACK_FRAMES ?= 600
HACK_SCENARIO ?= boot_smoke
# HACK-008d4a: first file-load input fixture that reaches in-game, plus the
# expected hack entry area/room (AREA_TEST_1 = 7, Entry Ledge room 0).
#
# HACK-004a2a: the full 30k fixture reaches Entry Ledge's door 0 at ~frame
# 29657 and legitimately ends in another Test Area 1 room, so the door-chaining
# tail must not decide this entry-warp gate.  `hack-room-check` therefore
# replays a deterministic prefix (frames 0..29500, verified room 0) generated
# from the committed fixture into work/emulator/ (ignored).
HACK_ROOM_FIXTURE ?= tests/emulator/inputs/baseline_first30000.input
HACK_ROOM_FRAME ?= 29500
HACK_ROOM_PREFIX ?= work/emulator/hack_room_prefix_$(HACK_ROOM_FRAME).input
HACK_ROOM_INPUT ?= $(HACK_ROOM_PREFIX)
HACK_ROOM_EVENT ?= area=7 room=0
HACK_ROOM_TIMEOUT ?= 600
# HACK-004a2a: the default content-tables/hack-build path converts and links all
# five authored Test Area 1 rooms (manifest indices 0..4).  HACK_ROOM and
# HACK_ROOM_DIR remain the single-room selection for debugging; override
# HACK_ROOMS (and set HACK_ACTIVE_DOORS=0 if the subset has no destinations).
HACK_ROOMS ?= entry_ledge silent_atrium resonance_chamber hidden_conduit choir_nest
HACK_ROOMS_DIR ?= hack/gen/rooms
HACK_ROOM ?= $(firstword $(HACK_ROOMS))
HACK_ROOM_DIR ?= $(HACK_ROOMS_DIR)/$(HACK_ROOM)
HACK_ROOM_DIRS ?= $(addprefix $(HACK_ROOMS_DIR)/,$(HACK_ROOMS))
# HACK-004a2a: the 12 authored doors are reciprocal pairs
# (0/1, 2/3, 4/5, 6/7, 8/9, 10/11).  Set to 0 for a subset that has no
# destination records (the one-room debugging table then keeps DOOR_TYPE_NONE).
HACK_ACTIVE_DOORS ?= 1
HACK_DOOR_FLAGS ?= $(if $(filter 0,$(HACK_ACTIVE_DOORS)),,--active-doors)
HACK_TABLES ?= hack/gen/content_tables.h
# HACK-008d1: the generator writes this scroll-only sibling beside HACK_TABLES.
HACK_SCROLL_TABLES ?= $(patsubst %content_tables.h,%scroll_tables.h,$(HACK_TABLES))
# HACK-008d2: per-area message-banner text table from hack/content/text.
HACK_TEXT_TABLES ?= hack/gen/text_tables.h
# HACK-008d3: per-room (spriteId, gfxSlot) spriteset tables, beside HACK_TABLES.
HACK_SPRITE_TABLES ?= $(patsubst %content_tables.h,%sprite_tables.h,$(HACK_TABLES))

# Objects for the private tree.  The split mirrors ASMSRC: C sources are
# preprocessed/compiled there, while checked-in .s files are assembled from
# their real path.  The link order is the main Makefile's OBJ order.
ifneq ($(OBJ_DIR),)
HACK_GEN_S := $(addprefix $(OBJ_DIR)/,$(CSRC:.c=.s))
HACK_DIRECT_S := $(filter-out $(CSRC:.c=.s),$(ASMSRC))
HACK_C_OBJ := $(addprefix $(OBJ_DIR)/,$(CSRC:.c=.o))
HACK_DIRECT_OBJ := $(addprefix $(OBJ_DIR)/,$(HACK_DIRECT_S:.s=.o))

$(HACK_GEN_S): $(OBJ_DIR)/%.s: %.c
	$(MSG) CC $@
	@mkdir -p $(dir $@)
	$Q$(PREPROC) $< $(PREPROCFLAGS) | $(CPP) $(CPPFLAGS) | $(CC) -o $@ $(CFLAGS) && printf '\t.align 2, 0 @ dont insert nops\n' >> $@

$(HACK_C_OBJ): $(OBJ_DIR)/%.o: $(OBJ_DIR)/%.s
	$(MSG) AS $@
	@mkdir -p $(dir $@)
	$Q$(AS) $(ASFLAGS) $< -o $@

$(HACK_DIRECT_OBJ): $(OBJ_DIR)/%.o: %.s
	$(MSG) AS $@
	@mkdir -p $(dir $@)
	$Q$(AS) $(ASFLAGS) $< -o $@

# The two baseline hooks include generated headers; make must rebuild each
# object when content-tables regenerates its header.
$(OBJ_DIR)/src/room.s: $(HACK_TABLES)
$(OBJ_DIR)/src/room.o: $(OBJ_DIR)/src/room.s $(HACK_TABLES)
$(OBJ_DIR)/src/scroll.s: $(HACK_SCROLL_TABLES)
$(OBJ_DIR)/src/scroll.o: $(OBJ_DIR)/src/scroll.s $(HACK_SCROLL_TABLES)
$(OBJ_DIR)/src/text.s: $(HACK_TEXT_TABLES)
$(OBJ_DIR)/src/text.o: $(OBJ_DIR)/src/text.s $(HACK_TEXT_TABLES)
$(OBJ_DIR)/src/sprite.s: $(HACK_SPRITE_TABLES)
$(OBJ_DIR)/src/sprite.o: $(OBJ_DIR)/src/sprite.s $(HACK_SPRITE_TABLES)

# Same per-file optimisation overrides as the baseline build (Makefile).
$(OBJ_DIR)/src/dma.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm
$(OBJ_DIR)/src/sram/%.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm

# sound/track_data.s includes every generated track header.
$(OBJ_DIR)/sound/track_data.o: $(wildcard sound/tracks/*.s)
endif

# HACK linker script: the same layout as linker.ld, but every source object is
# under the private $(HACK_OBJ_DIR) tree.  GNU ld loads objects named in the
# script, so this is what keeps baseline src/*.o out of the hack link.
$(HACK_LD_SCRIPT): linker.ld tools/shift/prefix_linker_objects.py
	@mkdir -p $(HACK_WORK)
	$(CPP) $(CPPFLAGS) $< -o $@
	$(PYTHON) tools/shift/prefix_linker_objects.py $@ --obj-dir $(HACK_OBJ_DIR)

.PHONY: content-tables content-tables-check hack-build hack-sha1 hack-smoke hack-room-check hack-liveness-check

# HACK-008c2/HACK-008d1/HACK-008d2/HACK-004a2a: the only generated-content
# step.  The room converter output and all C headers are under ignored
# hack/gen/.  Every room in HACK_ROOMS converts into its own directory first;
# gen_content_tables.py then emits one room-indexed table set for all of them.
content-tables:
	@mkdir -p $(HACK_ROOMS_DIR)
	@set -e; for room in $(HACK_ROOMS); do \
		echo "  CONVERT $$room"; \
		$(PYTHON) tools/content/tiled_to_room.py \
			--map hack/content/tiled/$$room.tmj \
			--manifest hack/content/tiled/$$room.room.json \
			--out $(HACK_ROOMS_DIR)/$$room --force; \
	done
	$(PYTHON) tools/content/gen_content_tables.py \
		$(foreach room,$(HACK_ROOMS),--room-dir $(HACK_ROOMS_DIR)/$(room)) \
		$(HACK_DOOR_FLAGS) --out $(HACK_TABLES) --write
	$(PYTHON) tools/content/gen_text_tables.py \
		--out $(HACK_TEXT_TABLES) --write
# gen_content_tables.py writes content_tables.h, scroll_tables.h and
# sprite_tables.h together; HACK_SPRITE_TABLES must match that sibling path.

# --check verifies $(HACK_TABLES), its scroll and sprite siblings, and the
# HACK-008d2 text table for the same HACK_ROOMS table set.
content-tables-check:
	$(PYTHON) tools/content/gen_content_tables.py \
		$(foreach room,$(HACK_ROOMS),--room-dir $(HACK_ROOMS_DIR)/$(room)) \
		$(HACK_DOOR_FLAGS) --out $(HACK_TABLES) --check
	$(PYTHON) tools/content/gen_text_tables.py \
		--out $(HACK_TEXT_TABLES) --check

hack-build: content-tables
	@mkdir -p $(HACK_WORK)
	$(MAKE) -f Makefile HACK=1 \
		ROM_STEM=$(HACK_STEM) OBJ_DIR=$(HACK_OBJ_DIR) \
		LD_SCRIPT=$(HACK_LD_SCRIPT)
	@test -f $(HACK_ROM) || { echo "HACK-BUILD: FAIL (no $(HACK_ROM))"; exit 1; }
	@echo "HACK-BUILD: PASS ($(HACK_ROM))"

hack-sha1: hack-build
	$(SHA1SUM) $(HACK_ROM) | tee $(HACK_SHA1FILE)

hack-smoke: hack-build
	$(PYTHON) tests/emulator/run.py --static --rom $(HACK_ROM)
	$(PYTHON) tests/emulator/run.py --rom $(HACK_ROM) \
		--scenario $(HACK_SCENARIO) --frames $(HACK_FRAMES)

# HACK-008d4a/HACK-004a2a: replay the deterministic 29500-frame prefix and
# require the hack ROM to end in Entry Ledge (AREA_TEST_1 room 0), still
# in-game, with a live frame counter (77 if the headless harness is
# unavailable).  The prefix keeps the comment lines and every frame
# `<= HACK_ROOM_FRAME`; the 30k fixture is its prerequisite.
$(HACK_ROOM_PREFIX): $(HACK_ROOM_FIXTURE)
	@mkdir -p $(dir $@)
	awk '/^#/ || ($$1+0)<= $(HACK_ROOM_FRAME)' $< > $@

hack-room-check: hack-build $(HACK_ROOM_INPUT)
	$(PYTHON) tests/emulator/run.py --rom $(HACK_ROM) \
		--input $(HACK_ROOM_INPUT) --expect-event "$(HACK_ROOM_EVENT)" \
		--timeout $(HACK_ROOM_TIMEOUT)

# HACK-008d4b: replay the verified 28450-frame prefix, dump IWRAM and assert the
# generated 7-entry spriteset plus the four live Entry Ledge spawns.  77 if the
# headless harness is unavailable.
hack-liveness-check: hack-build
	$(PYTHON) tests/emulator/hack_room_check.py --rom $(HACK_ROM) --elf $(HACK_STEM).elf

define HACK_HELP
	@echo "  content-tables      convert HACK_ROOMS + generate hack/gen/{content,scroll,sprite,text}_tables.h"
	@echo "  content-tables-check verify the five-room generated headers and text table are fresh"
	@echo "  hack-build          build the HACK=1 overlay ROM into work/hack/ (D-013)"
	@echo "  hack-sha1           hack-build, then write work/hack/mf_us_hack.sha1"
	@echo "  hack-smoke          hack-build + static smoke + boot smoke (77 if no harness)"
	@echo "  hack-room-check     hack-build + 29500-frame prefix replay; require Entry Ledge area=7 room=0 in-game (77 if no harness)"
	@echo "  hack-liveness-check hack-build + 28450-frame replay; assert IWRAM spriteset table and 4 live spawns (77 if no harness)"
	@echo "Variables: HACK_WORK, HACK_STEM, HACK_ROM, HACK_OBJ_DIR, HACK_LD_SCRIPT, HACK_FRAMES, HACK_SCENARIO,"
	@echo "           HACK_ROOM_FIXTURE, HACK_ROOM_FRAME, HACK_ROOM_PREFIX,"
	@echo "           HACK_ROOM_INPUT, HACK_ROOM_EVENT, HACK_ROOM_TIMEOUT, HACK_ROOMS, HACK_ROOMS_DIR,"
	@echo "           HACK_ROOM, HACK_ROOM_DIR, HACK_ACTIVE_DOORS"
endef
