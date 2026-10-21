# mk/hack.mk — HACK=1 overlay build (HACK-008c1 / D-013).
#
# The hack build is the same engine and baseline data as `all`, compiled with
# -DHACK (C) and --defsym HACK=1 (assembly).  The only baseline hook is a
# narrow `#ifdef HACK` selection in src/room.c, which includes
# hack/include/hack/content_tables.h.  For HACK-008c1 that header falls back to
# the baseline AREA_TEST_1 room/door tables, so the overlay is empty; HACK-008c2
# replaces the fallback with generated tables from the ignored hack/gen/ tree
# without touching this build boundary.
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
HACK_ROOM ?= entry_ledge
HACK_ROOM_DIR ?= hack/gen/rooms/$(HACK_ROOM)
HACK_TABLES ?= hack/gen/content_tables.h

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

# The one baseline hook includes the generated table header; make must rebuild
# it when content-tables regenerates that header.
$(OBJ_DIR)/src/room.o: $(HACK_TABLES)

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

.PHONY: content-tables content-tables-check hack-build hack-sha1 hack-smoke

# HACK-008c2: the only generated-content step.  The room converter output and
# the C header are both under ignored hack/gen/.
content-tables:
	@mkdir -p hack/gen/rooms
	$(PYTHON) tools/content/tiled_to_room.py \
		--map hack/content/tiled/$(HACK_ROOM).tmj \
		--manifest hack/content/tiled/$(HACK_ROOM).room.json \
		--out $(HACK_ROOM_DIR) --force
	$(PYTHON) tools/content/gen_content_tables.py \
		--room-dir $(HACK_ROOM_DIR) --out $(HACK_TABLES) --write

content-tables-check:
	$(PYTHON) tools/content/gen_content_tables.py \
		--room-dir $(HACK_ROOM_DIR) --out $(HACK_TABLES) --check

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

define HACK_HELP
	@echo "  content-tables      generate hack/gen/rooms/entry_ledge + content_tables.h"
	@echo "  content-tables-check verify the generated one-room table is fresh"
	@echo "  hack-build          build the HACK=1 overlay ROM into work/hack/ (D-013)"
	@echo "  hack-sha1           hack-build, then write work/hack/mf_us_hack.sha1"
	@echo "  hack-smoke          hack-build + static smoke + boot smoke (77 if no harness)"
	@echo "Variables: HACK_WORK, HACK_STEM, HACK_ROM, HACK_OBJ_DIR, HACK_LD_SCRIPT, HACK_FRAMES, HACK_SCENARIO"
endef
