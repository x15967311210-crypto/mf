# mk/hack.mk — HACK=1 overlay build (HACK-008c1 / D-013).
#
# The hack build is the same engine and baseline data as `all`, compiled with
# -DHACK (C) and --defsym HACK=1 (assembly).  The baseline hooks are three narrow
# `#ifdef HACK` selections: src/room.c includes
# hack/include/hack/content_tables.h (room/door/spriteset tables), src/scroll.c
# includes hack/include/hack/scroll_tables.h (scroll blocks) and src/text.c
# includes hack/include/hack/text_tables.h (message-banner text).  For
# HACK-008c1 those headers fall back to the baseline AREA_TEST_1 tables, so the
# overlay is empty; HACK-008c2/HACK-008d1 replace them with generated tables
# from the ignored hack/gen/ tree without touching this build boundary.
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
HACK_ROOM_INPUT ?= tests/emulator/inputs/baseline_first30000.input
HACK_ROOM_EVENT ?= area=7 room=0
HACK_ROOM_TIMEOUT ?= 600
HACK_ROOM ?= entry_ledge
HACK_ROOM_DIR ?= hack/gen/rooms/$(HACK_ROOM)
HACK_TABLES ?= hack/gen/content_tables.h
# HACK-008d1: the generator writes this scroll-only sibling beside HACK_TABLES.
HACK_SCROLL_TABLES ?= $(patsubst %content_tables.h,%scroll_tables.h,$(HACK_TABLES))
# HACK-008d2: per-area message-banner text table from hack/content/text.
HACK_TEXT_TABLES ?= hack/gen/text_tables.h

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

.PHONY: content-tables content-tables-check hack-build hack-sha1 hack-smoke hack-room-check

# HACK-008c2/HACK-008d1/HACK-008d2: the only generated-content step.  The room
# converter output and all C headers are under ignored hack/gen/.
content-tables:
	@mkdir -p hack/gen/rooms
	$(PYTHON) tools/content/tiled_to_room.py \
		--map hack/content/tiled/$(HACK_ROOM).tmj \
		--manifest hack/content/tiled/$(HACK_ROOM).room.json \
		--out $(HACK_ROOM_DIR) --force
	$(PYTHON) tools/content/gen_content_tables.py \
		--room-dir $(HACK_ROOM_DIR) --out $(HACK_TABLES) --write
	$(PYTHON) tools/content/gen_text_tables.py \
		--out $(HACK_TEXT_TABLES) --write

# --check verifies $(HACK_TABLES), the sibling scroll header derived from it and
# the HACK-008d2 text table.
content-tables-check:
	$(PYTHON) tools/content/gen_content_tables.py \
		--room-dir $(HACK_ROOM_DIR) --out $(HACK_TABLES) --check
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

# HACK-008d4a: replay the first 30k baseline frames and require the hack ROM to
# end in Entry Ledge (AREA_TEST_1 room 0), still in-game, with a live frame
# counter (77 if the headless harness is unavailable).
hack-room-check: hack-build
	$(PYTHON) tests/emulator/run.py --rom $(HACK_ROM) \
		--input $(HACK_ROOM_INPUT) --expect-event "$(HACK_ROOM_EVENT)" \
		--timeout $(HACK_ROOM_TIMEOUT)

define HACK_HELP
	@echo "  content-tables      generate hack/gen/rooms/entry_ledge + content_tables.h + scroll_tables.h + text_tables.h"
	@echo "  content-tables-check verify the generated one-room headers and text table are fresh"
	@echo "  hack-build          build the HACK=1 overlay ROM into work/hack/ (D-013)"
	@echo "  hack-sha1           hack-build, then write work/hack/mf_us_hack.sha1"
	@echo "  hack-smoke          hack-build + static smoke + boot smoke (77 if no harness)"
	@echo "  hack-room-check     hack-build + 30k input replay; require Entry Ledge area=7 room=0 in-game (77 if no harness)"
	@echo "Variables: HACK_WORK, HACK_STEM, HACK_ROM, HACK_OBJ_DIR, HACK_LD_SCRIPT, HACK_FRAMES, HACK_SCENARIO,"
	@echo "           HACK_ROOM_INPUT, HACK_ROOM_EVENT, HACK_ROOM_TIMEOUT"
endef
