# Disable built-in rules
.SUFFIXES:

REGION ?= us
PAD_TO = 0x08800000

ifeq ($(REGION),us)
	TARGET = mf_us
	GAME_TITLE = METROID4USA
	GAME_CODE = AMTE
	CPPFLAGS += -DREGION_US
	ASFLAGS += --defsym REGION_US=1
endif

# ifeq ($(REGION),eu)
# 	TARGET = mf_eu
# 	GAME_TITLE = METROID4EUR
# 	GAME_CODE = AMTP
# 	CPPFLAGS += -DREGION_EU
# 	ASFLAGS += --defsym REGION_EU=1
# endif

# ifeq ($(REGION),eu_beta)
# 	TARGET = mf_eu_beta
# 	GAME_TITLE = METROIDAGBJ
# 	GAME_CODE = METJ
# 	CPPFLAGS += -DREGION_EU -DREGION_EU_BETA -DDEBUG
# 	ASFLAGS += --defsym REGION_EU=1 --defsym REGION_EU_BETA=1 --defsym DEBUG=1
# 	PAD_TO = 0x09000000
# endif

# ifeq ($(REGION),jp)
# 	TARGET = mf_jp
# 	GAME_TITLE = METROID4JPN
# 	GAME_CODE = AMTJ
# 	CPPFLAGS += -DREGION_JP
# 	ASFLAGS += --defsym REGION_JP=1
# endif

# ifeq ($(REGION),cn)
# 	TARGET = mf_cn
# 	GAME_TITLE = METFUSIONCHN
# 	GAME_CODE = AMTC
# 	CPPFLAGS += -DREGION_CN
#	ASFLAGS += --defsym REGION_CN=1
# endif

ifeq ($(DEBUG),1)
	CPPFLAGS += -DDEBUG
	ASFLAGS += --defsym DEBUG=1
	TARGET := $(TARGET)_debug
endif

# HACK-008c1 / D-013: optional hack content overlay.  `make hack-build`
# (mk/hack.mk) runs a sub-make with HACK=1; a plain `make` never sets it.  The
# flag reaches C (-DHACK) and assembly (--defsym HACK=1), and the overlay
# headers are the only extra include path.  The artifact and the object tree
# live under work/hack/, so a hack build can never overwrite mf_us.* or the
# baseline objects it was built from.
ifeq ($(HACK),1)
	CPPFLAGS += -DHACK -Ihack/include
	ASFLAGS += --defsym HACK=1
	ROM_STEM := work/hack/mf_us_hack
	OBJ_DIR ?= work/hack/obj
endif

# ROM_STEM is the artifact basename without .gba.  A command-line override
# (`make ... ROM_STEM=...`) always wins; baseline builds use $(TARGET).
ROM_STEM ?= $(TARGET)
BASEROM := $(ROM_STEM)_baserom.gba
TARGET := $(ROM_STEM).gba

# Default target
.PHONY: all
all: $(TARGET)

ELF = $(TARGET:.gba=.elf)
MAP = $(TARGET:.gba=.map)
SHA1FILE = $(TARGET:.gba=.sha1)
DUMPS = $(BASEROM:.gba=.dump) $(TARGET:.gba=.dump)
LD_SCRIPT = linker.ld.pp

# ROM header
MAKER_CODE = 01
GAME_REVISION = 00

# Binaries
CPP = cpp
# ARM binutils prefix.  An explicit TOOLCHAIN (command line or environment)
# always wins.  Otherwise prefer `arm-none-eabi-` from PATH, and when that does
# not resolve fall back to this project's per-user install in $(HOME)/.local/bin
# (non-interactive shells do not source ~/.bashrc or ~/.profile, so that
# directory is often missing from PATH).
ifeq ($(filter $(origin TOOLCHAIN),command line environment),)
  ifeq ($(shell command -v arm-none-eabi-as 2>/dev/null),)
    ifneq ($(wildcard $(HOME)/.local/bin/arm-none-eabi-as),)
      TOOLCHAIN := $(HOME)/.local/bin/arm-none-eabi-
    endif
  endif
endif
TOOLCHAIN ?= arm-none-eabi-
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump

CC = agbcc

DIFF = diff -u
HOSTCC = cc
HOST_CFLAGS = -std=gnu11 -O2 -ffunction-sections -fdata-sections -Iinclude \
	-Wno-implicit-function-declaration -Wno-pointer-to-int-cast
HOST_TEST_DIR = tests/host/bin
HOST_TEST_ROOM_BIN = $(HOST_TEST_DIR)/room_rle_test
HOST_TEST_SPRITE_BIN = $(HOST_TEST_DIR)/sprite_spawn_test
HOST_TEST_TIMER_BIN = $(HOST_TEST_DIR)/timer_test
HOST_TEST_FIXED_BIN = $(HOST_TEST_DIR)/fixed_point_test
MKDIR = mkdir -p
RM = rm -f
SHA1SUM = sha1sum
TAIL = tail

# Tools
include make_tools.mk
GBAFIX = $(TOOLS_DIR)/gbafix/gbafix
PYTHON = python3
EXTRACTOR = $(PYTHON) $(TOOLS_DIR)/extractor.py
PREPROC = $(TOOLS_DIR)/preproc/preproc

# Flags
ASFLAGS += -mcpu=arm7tdmi
CFLAGS = -Werror -O2 -mthumb-interwork -fhex-asm
CPPFLAGS += -nostdinc -Iinclude/
PREPROCFLAGS = charmap.txt

# Objects
CSRC = $(wildcard src/**.c) $(wildcard src/**/**.c) $(wildcard src/**/**/**.c) $(wildcard src/**/**/**/**.c)
.PRECIOUS: $(CSRC:.c=.s)
ASMSRC = $(CSRC:.c=.s) $(wildcard asm/*.s) $(wildcard sound/*.s) $(wildcard sound/**/*.s)
OBJ = $(ASMSRC:.s=.o) 

# HACK-008c1: OBJ_DIR redirects intermediates into a private tree (see
# mk/hack.mk).  It is empty for every baseline/shift/reorder target, so their
# object paths and link order are unchanged.  When set, the link order below
# still follows ASMSRC exactly.
OBJ_DIR ?=
ifneq ($(OBJ_DIR),)
	OBJ := $(addprefix $(OBJ_DIR)/,$(OBJ))
endif

# Detect if agbcc was installed into the project
ifneq (,$(wildcard tools/agbcc))
	AGBCC_BIN := tools/agbcc/bin/agbcc
	AGBCC_LIB := tools/agbcc/lib
	CC = $(AGBCC_BIN)
else
	# Dynamically find agbcc path and its lib folder
	AGBCC_BIN := $(shell which agbcc)
	AGBCC_DIR := $(dir $(AGBCC_BIN))/
	AGBCC_LIB := $(abspath $(AGBCC_DIR))
endif

LIBS := $(AGBCC_LIB)/libgcc.a $(AGBCC_LIB)/libc.a


# Enable verbose output
ifeq ($(V),1)
	Q =
	MSG = @:
else
	Q = @
	MSG = @echo " "
endif

# Rules that do not require scanning for dependencies
RULES_NO_SCAN += dump diff extract clean tidy host-test doctor doctor-source setup setup-agbcc
# Shift/audit/test targets are host/Python-only; they never need the generated
# tool binaries.  Targets that do (postlink-scan, shift-*) build them in their
# own recursive make invocation.
RULES_NO_SCAN += symbols audit-asm audit-blobs rewrite report audit \
	check-relocs check-relocs-strict check-linker smoke content-check \
	test test-input input-smoke emulator-harness shift-build shift-test \
	shift-check shift-reorder shift-start shift-input shift-input-30k \
	shift-screen screen-diff oam-diff event-diff shift-check-all \
	postlink-scan postlink-scan-strict shift-help \
	compare-text c-port-check permute \
	content-tables content-tables-check hack-build hack-sha1 hack-smoke \
	format format-check format-list

# Generate tools before building anything
SETUP_PREREQS ?= 1
# Disable generating tools for rules that do not build anything
ifneq (,$(MAKECMDGOALS))
  ifeq (,$(filter-out $(RULES_NO_SCAN),$(MAKECMDGOALS)))
    SETUP_PREREQS := 0
  endif
endif
.SHELLSTATUS ?= 0
ifeq ($(SETUP_PREREQS),1)
  $(foreach line, $(shell $(MAKE) -f make_tools.mk | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))
  ifneq ($(.SHELLSTATUS),0)
    $(error Errors occurred while building tools. See error messages above for more details)
  endif
endif

.PHONY: check
check: all
	$(MSG) SHA1SUM $(SHA1FILE)
	$Q$(SHA1SUM) -c $(SHA1FILE)

.PHONY: doctor
doctor:
	$Q$(PYTHON) tools/doctor.py

.PHONY: doctor-source
doctor-source:
	$Q$(PYTHON) tools/doctor.py --source-only

.PHONY: setup-agbcc
setup-agbcc:
	$Qsh tools/setup_agbcc.sh

.PHONY: setup
setup: setup-agbcc doctor

.PHONY: dump
dump: $(DUMPS)

.PHONY: diff
diff: $(DUMPS)
	$(MSG) DIFF $^
	$Q$(DIFF) $^

.PHONY: extract
extract:
	$(MSG) Extracting
	$Q$(EXTRACTOR) -r $(REGION)

.PHONY: clean
clean: clean-tools tidy

.PHONY: tidy
tidy:
	$(MSG) RM roms
# Delete every gba file that doesn't end with baserom
	$Qfind -type f -name "*.gba" -a ! -name "*baserom.gba" -delete
	$(MSG) RM elf
	$Q$(RM) *.elf
	$(MSG) RM map
	$Q$(RM) *.map

	$(MSG) RM \*.dump
	$Q$(RM) $(DUMPS)
	$(MSG) RM \*.o
	$Q$(RM) $(OBJ)
	$(MSG) RM data/*.s
	$(MSG) RM src/\*\*/\*.s
	$Q$(RM) $(CSRC:.c=.s)
	$(MSG) RM $(GBAFIX)
	$Q$(RM) $(GBAFIX)
ifeq ($(DATA),1)
	$(MSG) RM data/
	$Q$(RM) -r data
	$(MSG) RM sound/direct_sound_samples
	$Q$(RM) -r sound/direct_sound_samples
endif
	$(MSG) RM linker.ld.pp
	$Q$(RM) linker.ld.pp

.PHONY: host-test
host-test:
	$(MSG) HOSTCC $(HOST_TEST_ROOM_BIN)
	$Q$(MKDIR) $(HOST_TEST_DIR)
	$Q$(HOSTCC) $(HOST_CFLAGS) tests/host/room_rle_test.c src/room.c \
		-Wl,--gc-sections -o $(HOST_TEST_ROOM_BIN)
	$(MSG) HOSTCC $(HOST_TEST_SPRITE_BIN)
	$Q$(HOSTCC) $(HOST_CFLAGS) tests/host/sprite_spawn_test.c src/sprite.c \
		-Wl,--gc-sections -o $(HOST_TEST_SPRITE_BIN)
	$(MSG) HOSTCC $(HOST_TEST_TIMER_BIN)
	$Q$(HOSTCC) $(HOST_CFLAGS) tests/host/timer_test.c src/in_game_timer.c \
		-Wl,--gc-sections -o $(HOST_TEST_TIMER_BIN)
	$(MSG) HOSTCC $(HOST_TEST_FIXED_BIN)
	$Q$(HOSTCC) $(HOST_CFLAGS) tests/host/fixed_point_test.c src/fixed_point.c \
		-Wl,--gc-sections -o $(HOST_TEST_FIXED_BIN)
	$Q$(HOST_TEST_ROOM_BIN)
	$Q$(HOST_TEST_SPRITE_BIN)
	$Q$(HOST_TEST_TIMER_BIN)
	$Q$(HOST_TEST_FIXED_BIN)
	@echo 'host-test: all suites passed'

# Shift/audit/test surface (BUILD-002).  The targets live in mk/shift.mk and
# are exported from this single entry point: `make audit`, `make smoke`,
# `make shift-build`, ...  `make -f Makefile.shift <target>` remains as a thin
# compatibility wrapper.  Included before `help` so the help text can use
# $(SHIFT_HELP).
include mk/shift.mk

# HACK=1 overlay build (HACK-008c1 / D-013).  Contributes `hack-build`,
# `hack-sha1`, `hack-smoke` and $(HACK_HELP); it owns no `all`/`help` target.
include mk/hack.mk

# Project-management targets (PM-001): `jira-check`, `dashboard`,
# `dashboard-check`, `jira-check-self`.  Contributes $(PM_HELP) and owns no
# `all`/`help` target, matching mk/shift.mk and mk/hack.mk.
include mk/pm.mk

# Format contract (DOC-002): `format`, `format-check`, `format-list`.
# Contributes $(FORMAT_HELP); it owns no `all`/`help` target and never runs
# without being asked, so a normal build is unchanged.
include mk/format.mk

# Manual decomp-permuter pilot (TECH-007).  Contributes $(PERMUTE_HELP); it
# owns no `all`/`help` target and is never a gate.
include mk/permute.mk

.PHONY: help
help:
	@echo 'Targets:'
	@echo '  all: build the ROM'
	@echo '  check: checksum the ROM'
	@echo '  host-test: build and run host-side unit tests (no emulator/toolchain)'
	@echo '  doctor: check Python, host tools, ARM binutils, agbcc, and baserom'
	@echo '  doctor-source: check Python/host tools and tool self-checks (no baserom)'
	@echo '  setup-agbcc: build and install the pinned agbcc into tools/agbcc'
	@echo '  setup: setup-agbcc then doctor'
	@echo '  dump: dump the ROMs'
	@echo '  diff: compare the ROM with the original'
	@echo '  clean: remove the ROM and intermediate files'
	@echo '  	DATA=1: removes the data folder generated by the extractor'
	@echo '  help: show this message'
	@echo '  shift-help: show only the shift/audit/test targets'
	@echo ''
	@echo 'Shift/audit/test targets (always available; legacy: make -f Makefile.shift <target>):'
	$(SHIFT_HELP)
	@echo ''
	@echo 'Hack overlay build (D-013; HACK=1, artifacts under work/hack/):'
	$(HACK_HELP)
	@echo ''
	@echo 'Project management (jira.md is the backlog source of truth):'
	$(PM_HELP)
	@echo ''
	@echo 'Format contract (DOC-002; style in .clang-format and docs/style.md):'
	$(FORMAT_HELP)
	@echo ''
	@echo 'Manual decomp tooling (never part of a gate):'
	$(PERMUTE_HELP)
	@echo ''
	@echo 'Flags:'
	@echo '  V=1: enable verbose output'
	@echo '  REGION=<region>: selects the region of the ROM, possible values are "us", "eu", "jp", "cn", and "eu_beta"'
	@echo '  DEBUG=1: enables the debug code'
	@echo '  SHIFT=1: accepted for compatibility; the shift targets are always available'

$(TARGET): $(ELF)
	$(MSG) OBJCOPY $@
	$Q$(OBJCOPY) -O binary --gap-fill 0xff --pad-to $(PAD_TO) $< $@
	$(MSG) GBAFIX $@
	$Q$(GBAFIX) $@ -t$(GAME_TITLE) -c$(GAME_CODE) -m$(MAKER_CODE) -r$(GAME_REVISION)

$(ELF) $(MAP): $(OBJ) $(LD_SCRIPT)
	$(MSG) LD $@
	$Q$(LD) $(LDFLAGS) -n -T $(LD_SCRIPT) -Map=$(MAP) $(LIBS) -o $@

ifneq ($(HACK),1)
$(LD_SCRIPT): linker.ld
	$(MSG) CPP $@
	$Q$(CPP) $(CPPFLAGS) $< -o $@
endif

%.dump: %.gba
	$(MSG) OBJDUMP $@
	$Q$(OBJDUMP) -D -bbinary -marm7tdmi -Mforce-thumb  $< | $(TAIL) -n+3 >$@
#--stop-address 0x8c71c
%.o: %.s
	$(MSG) AS $@
	$Q$(AS) $(ASFLAGS) $< -o $@

# track_data.s includes every generated track header.  The generic rule only
# knows about track_data.s, so without these prerequisites a stale object can
# hide a relocation rewrite (and make the shift test lie).
sound/track_data.o: sound/track_data.s $(wildcard sound/tracks/*.s)

%.s: %.c
	$(MSG) CC $@
	$Q$(PREPROC) $< $(PREPROCFLAGS) | $(CPP) $(CPPFLAGS) | $(CC) -o $@ $(CFLAGS) && printf '\t.align 2, 0 @ dont insert nops\n' >> $@

src/dma.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm
src/dma.s: src/dma.c

src/sram/%.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm
src/sram/%.s: src/sram/%.c

# SramRead_WorldData matches the baseline only at -O2 (push {r4-r7,lr}, live
# r8 save pointer, single r7 offset).  Keep the rest of src/sram at -O1.
src/sram/sram_world_read.s: CFLAGS = -Werror -O2 -mthumb-interwork -fhex-asm
$(OBJ_DIR)/src/sram/sram_world_read.s: CFLAGS = -Werror -O2 -mthumb-interwork -fhex-asm

.PHONY: us
# us_debug eu eu_debug eu_beta jp jp_debug cn cn_debug

us:
	$(MAKE) REGION=us
# us_debug:
# 	$(MAKE) REGION=us DEBUG=1

# eu:
# 	$(MAKE) REGION=eu
# eu_debug:
# 	$(MAKE) REGION=eu DEBUG=1
# eu_beta:
# 	$(MAKE) REGION=eu_beta

# jp:
# 	$(MAKE) REGION=jp
# jp_debug:
# 	$(MAKE) REGION=jp DEBUG=1

# cn:
# 	$(MAKE) REGION=cn
# cn_debug:
# 	$(MAKE) REGION=cn DEBUG=1
