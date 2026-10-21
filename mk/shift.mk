# Shiftability and behavior harness targets (BUILD-002).
#
# This fragment is included by the top-level Makefile, so all of these targets
# are available from the single build entry point:
#   make audit
#   make smoke
#   make shift-check TOOLCHAIN=/path/to/arm-none-eabi-
#   make -f Makefile.shift audit      # legacy wrapper, still supported
#
# It is self-contained: every default below uses `?=`, so the main Makefile's
# PYTHON/MAP/ROM/TOOLCHAIN/CC definitions always win.  It defines no `all`,
# `help` or `host-test` target; those belong to the main Makefile, and the
# shift help lines are contributed through $(SHIFT_HELP).
#
# Toolchain: put arm-none-eabi-* on PATH, or set TOOLCHAIN to an absolute
# prefix, e.g.:
#   make shift-check TOOLCHAIN=/path/to/arm-none-eabi-
#
# Blob evidence: `audit-blobs` reads extracted bytes from DATA_ROOT.  A fresh
# `git worktree` has no `data/` directory, so pass the main tree's path when
# running the strict gate there:
#   make check-relocs-strict DATA_ROOT=/path/to/data
#
# Exit status: report targets (`audit`, `check-relocs`) do not fail on open
# refs or raw blobs, but they do fail when their evidence inputs (map, ledger)
# are missing.  `check-relocs-strict` and `shift-check` exit nonzero on
# failure.  A shift test skipped because no emulator is installed reports
# `SKIP (77)` and never `PASS`; GNU make itself reports any failed recipe as
# exit 2, but the 77 is preserved in the message and by
# tools/shift/shift_test.py.

PYTHON ?= python3
MAP ?= mf_us.map
ROM ?= mf_us.gba
BASEROM ?= mf_us_baserom.gba
SCENARIO ?= boot_smoke
FRAMES ?= 600
START_FRAMES ?= 1200
INPUT ?= tests/emulator/inputs/baseline_first4000.input
INPUT_FRAMES ?=
INPUT_EXPECT ?= tests/emulator/inputs/baseline_first4000.expected
INPUT_30K ?= tests/emulator/inputs/baseline_first30000.input
INPUT_30K_EXPECT ?= tests/emulator/inputs/baseline_first30000.expected
INPUT_30K_FRAMES ?= 30000
OAM_CHECKPOINTS ?= 300 600 900 1059 4000 30000
PAD_BYTES ?= 0x1000
DATA_ROOT ?= data
DATABASE ?= database.json
TOOLCHAIN ?=

# BUILD-003: text-only manifest of the ignored extracted-data trees.  The
# bytes stay out of Git; the manifest describes them for caches and CI.
DATA_MANIFEST ?= tools/data-manifest.json
DATA_MANIFEST_ROOTS = --root data --extra sound/direct_sound_samples

SHIFT_WORK ?= work/shift
SYMBOLS ?= $(SHIFT_WORK)/symbols.json
ABS_REFS ?= $(SHIFT_WORK)/abs_refs.json
BLOB_SCAN ?= $(SHIFT_WORK)/blob_scan.json
REWRITE_REPORT ?= $(SHIFT_WORK)/rewrite_suggestions.md
POSTLINK_ELF ?= $(SHIFT_WORK)/mf_us_postlink.elf
POSTLINK_MAP ?= $(SHIFT_WORK)/mf_us_postlink.map
POSTLINK_JSON ?= $(SHIFT_WORK)/postlink_scan.json
POSTLINK_WHITELIST ?=
POSTLINK_SCAN = $(PYTHON) tools/shift/postlink_pointer_scan.py \
	--elf $(POSTLINK_ELF) --map $(POSTLINK_MAP) \
	$(if $(POSTLINK_WHITELIST),--whitelist $(POSTLINK_WHITELIST)) \
	--json-out $(POSTLINK_JSON)
# Relink only into work/: the normal mf_us.elf/mf_us.gba and the ROM SHA are
# never touched.  --emit-relocs records the words that are already pointers.
POSTLINK_RELINK = $(MAKE) -f Makefile ELF=$(POSTLINK_ELF) \
	MAP=$(POSTLINK_MAP) LDFLAGS=--emit-relocs $(POSTLINK_ELF)

# `all`, `help` and `host-test` stay owned by the main Makefile: defining them
# here would override the ROM build / host suites with a second recipe.
.PHONY: symbols audit-asm audit-blobs rewrite report audit \
        check-relocs check-relocs-strict check-linker smoke test test-input \
        input-smoke emulator-harness shift-build shift-test shift-check \
        shift-reorder shift-start shift-input shift-input-30k shift-screen \
        screen-diff oam-diff event-diff shift-check-all content-check \
        data-manifest data-verify data-cache-key \
        postlink-scan postlink-scan-strict shift-help \
        public-gate protected-gate collect-symbols

symbols:
	$(PYTHON) tools/shift/map_symbols.py --map $(MAP) --out $(SYMBOLS)

audit-asm:
	$(PYTHON) tools/shift/audit_asm.py --map $(MAP) --out $(ABS_REFS)

audit-blobs:
	$(PYTHON) tools/shift/audit_blobs.py --database $(DATABASE) \
		--data-root $(DATA_ROOT) --map $(MAP) --out $(BLOB_SCAN)

rewrite: audit-asm
	$(PYTHON) tools/shift/rewrite_refs.py --refs $(ABS_REFS) \
		--out $(REWRITE_REPORT)

report: symbols audit-asm audit-blobs
	$(PYTHON) tools/shift/report.py --refs $(ABS_REFS) \
		--blobs $(BLOB_SCAN) --symbols $(SYMBOLS) \
		--out docs/shiftability-audit.md

audit: symbols audit-asm audit-blobs rewrite report check-relocs

# Post-link scan: find raw ROM pointer words that survived a partial
# conversion.  The ELF is relinked into work/ with --emit-relocs so the normal
# mf_us.gba/mf_us.elf and the ROM SHA stay untouched.  Report mode exits 0;
# the strict target exits 1 on any structured run that is not whitelisted.
# Not part of check-relocs-strict/shift-check yet: the current tree has latent
# findings that need triage.
postlink-scan:
	@mkdir -p $(SHIFT_WORK)
	$(POSTLINK_RELINK)
	$(POSTLINK_SCAN) --report

postlink-scan-strict:
	@mkdir -p $(SHIFT_WORK)
	$(POSTLINK_RELINK)
	$(POSTLINK_SCAN) --strict

# Informational: regenerate the evidence and report what would fail the gate.
check-relocs: audit-asm audit-blobs
	$(PYTHON) tools/shift/check_relocs.py \
		--refs $(ABS_REFS) --blob-scan $(BLOB_SCAN)

# Gate: literals, C ROM refs, and pointer-like data blobs still included raw.
check-relocs-strict: audit-asm audit-blobs
	$(PYTHON) tools/shift/check_relocs.py --self-check
	$(PYTHON) tools/shift/check_relocs.py \
		--refs $(ABS_REFS) --blob-scan $(BLOB_SCAN) --strict

# Gate premise: the linker fixes only the header/entry and RAM/MMIO ranges.
check-linker:
	$(PYTHON) tools/shift/shift_test.py --check-linker

smoke:
	$(PYTHON) tests/emulator/run.py --static --rom $(ROM)

# HACK-003/HACK-008a: deterministic Tiled/PNG room pipeline and the D-009
# content ID registry.  This is emulator-free and ROM-free; it is not part of
# the S2 relocation gate.
content-check:
	$(PYTHON) tools/content/fixtures/generate_fixture.py --check
	$(PYTHON) tools/content/tiled_to_room.py --self-check
	$(PYTHON) tools/content/gen_ids.py --self-check
	$(PYTHON) tools/content/gen_ids.py --check
	$(PYTHON) tools/content/text_roundtrip.py --self-check
	$(PYTHON) tools/content/gen_content_tables.py --self-check

# BUILD-003: extracted-data manifest.  data/ and sound/direct_sound_samples/
# are generated by tools/extractor.py and ignored by Git; these targets record
# and verify their relative paths, sizes and SHA256 without committing bytes.
# They are deliberately not prerequisites of all/check.
data-manifest:
	$(PYTHON) tools/data_manifest.py --write $(DATA_MANIFEST_ROOTS) \
		--manifest $(DATA_MANIFEST)

data-verify:
	$(PYTHON) tools/data_manifest.py --verify $(DATA_MANIFEST_ROOTS) \
		--manifest $(DATA_MANIFEST)

data-cache-key:
	$(PYTHON) tools/data_manifest.py --cache-key --manifest $(DATA_MANIFEST)

# BUILD-004: CI layers.  `public-gate` is ROM-free; `protected-gate` needs the
# private baserom/toolchain/BIOS/movie; `collect-symbols` packages the existing
# map plus work/shift/*.json into a text-only artifact.
public-gate:
	bash tools/ci/public_gate.sh

protected-gate:
	bash tools/ci/protected_gate.sh

collect-symbols:
	bash tools/ci/collect_symbols.sh

# Fast host-compiler unit tests for pure engine code.  No emulator, baserom,
# data/ directory, or ARM toolchain required.  The target itself lives in the
# main Makefile (`make host-test`); the legacy wrapper forwards to it.

emulator-harness:
	MGBA_SRC=$(MGBA_SRC) MGBA_BUILD=$(MGBA_BUILD) \
		tests/emulator/build_harness.sh tests/emulator/bin/mgba-harness

# Boot smoke plus the committed 4k input replay.  A missing harness makes the
# input leg exit 77; propagate that skip instead of reporting a pass.
test:
	@status=0; \
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario $(SCENARIO) --frames $(FRAMES); \
	first=$$?; \
	if [ $$first -ne 0 ]; then status=$$first; fi; \
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario input \
		--input "$(INPUT)" $(if $(INPUT_EXPECT),--expect "$(INPUT_EXPECT)") \
		$(if $(INPUT_FRAMES),--frames $(INPUT_FRAMES)); \
	second=$$?; \
	if [ $$second -eq 77 ]; then \
		if [ $$status -eq 0 ]; then status=77; fi; \
	elif [ $$second -ne 0 ]; then status=$$second; fi; \
	exit $$status

# QA-002: automatic replay of the committed 4k fixture on the normal ROM with
# the normal-fixture checkpoint assertion.  This is not a BizHawk parity test.
test-input:
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario input \
		--input "$(INPUT)" $(if $(INPUT_EXPECT),--expect "$(INPUT_EXPECT)") \
		$(if $(INPUT_FRAMES),--frames $(INPUT_FRAMES))

# Explicit replay of any `frame keys` file, without the normal fixture's
# checkpoint assertion.  INPUT defaults to the committed 4k fixture:
#   make input-smoke INPUT=/path/to/full.input INPUT_FRAMES=4000
input-smoke:
	@if [ -z "$(INPUT)" ]; then \
		echo "usage: make input-smoke INPUT=path/to/file.input [INPUT_FRAMES=N]"; \
		echo "       (legacy: make -f Makefile.shift input-smoke ...)"; \
		exit 2; \
	fi
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario input \
		--input "$(INPUT)" $(if $(INPUT_FRAMES),--frames $(INPUT_FRAMES))

shift-build:
	$(PYTHON) tools/shift/shift_test.py --build --pad-bytes $(PAD_BYTES) \
		--toolchain "$(TOOLCHAIN)"

shift-test:
	$(PYTHON) tools/shift/shift_test.py --build --run \
		--pad-bytes $(PAD_BYTES) --frames $(FRAMES) \
		--toolchain "$(TOOLCHAIN)"

# Full shift gate: static audit + smoke + link check + shifted build/behavior.
# A missing emulator is a SKIP (77), never a PASS.
shift-check: audit smoke check-linker
	@$(PYTHON) tools/shift/shift_test.py --build --run \
		--pad-bytes $(PAD_BYTES) --frames $(FRAMES) \
		--toolchain "$(TOOLCHAIN)"; \
	status=$$?; \
	if [ $$status -eq 0 ]; then \
		echo "SHIFT-CHECK: PASS"; \
	elif [ $$status -eq 77 ]; then \
		echo "SHIFT-CHECK: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "              this is not a pass"; \
	else \
		echo "SHIFT-CHECK: FAIL ($$status)"; \
	fi; \
	exit $$status

# QA-001: the boot smoke never presses Start, so it cannot see BUG-001 (the
# shifted build blanks the screen after the title).  Build the padded ROM with
# the existing shift_test path and press Start.  Deliberately separate from
# shift-check until BUG-001 lands and this gate is green.
shift-start:
	@$(PYTHON) tools/shift/shift_test.py --build --run \
		--pad-bytes $(PAD_BYTES) --scenario start --frames $(START_FRAMES) \
		--toolchain "$(TOOLCHAIN)"; \
	status=$$?; \
	if [ $$status -eq 0 ]; then \
		echo "SHIFT-START: PASS"; \
	elif [ $$status -eq 77 ]; then \
		echo "SHIFT-START: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "              this is not a pass"; \
	else \
		echo "SHIFT-START: FAIL ($$status)"; \
	fi; \
	exit $$status

# QA-003: the shifted build must survive the same committed 4k TAS replay as
# the normal build.  Build through the existing shift_test.py path, then run
# the input scenario on the shifted artifact with the normal-fixture checkpoint
# assertion.  A shifted-only intro stall (BUG-002: counter=792) fails here.
shift-input:
	@$(PYTHON) tools/shift/shift_test.py --build --pad-bytes $(PAD_BYTES) \
		--toolchain "$(TOOLCHAIN)"; \
	build=$$?; \
	if [ $$build -ne 0 ]; then \
		echo "SHIFT-INPUT: FAIL ($$build) - shifted build did not complete"; \
		exit $$build; \
	fi; \
	$(PYTHON) tests/emulator/run.py --rom $(SHIFT_WORK)/mf_us_shift.gba \
		--scenario input --input "$(INPUT)" \
		$(if $(INPUT_EXPECT),--expect "$(INPUT_EXPECT)") \
		--frames 4000; \
	status=$$?; \
	if [ $$status -eq 0 ]; then \
		echo "SHIFT-INPUT: PASS"; \
	elif [ $$status -eq 77 ]; then \
		echo "SHIFT-INPUT: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "              this is not a pass"; \
	else \
		echo "SHIFT-INPUT: FAIL ($$status)"; \
	fi; \
	exit $$status

# QA-006: 30k input parity gate.  The 4k fixture is already green, so run the
# normal and padded-shift builds through the committed 30k prefix and compare
# the frame-30000 checkpoint plus the final state.  BUG-004 currently diverges
# only after the 4k prefix, so the shifted leg is expected to report a
# mismatch here.  A missing harness is SKIP (77), never a pass.
shift-input-30k:
	@mkdir -p $(SHIFT_WORK); \
	normal_log=$(SHIFT_WORK)/input30k_normal.log; \
	shift_log=$(SHIFT_WORK)/input30k_shift.log; \
	get_field() { \
		echo "$$1" | tr ' ' '\n' | grep "^$$2=" | head -1 | cut -d= -f2; \
	}; \
	echo "input-30k: normal replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario input \
		--input "$(INPUT_30K)" --expect "$(INPUT_30K_EXPECT)" \
		--frames $(INPUT_30K_FRAMES) > $$normal_log 2>&1; \
	normal=$$?; \
	cat $$normal_log; \
	if [ $$normal -eq 77 ]; then \
		echo "SHIFT-INPUT-30K: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "                   this is not a pass"; \
		exit 77; \
	fi; \
	if [ $$normal -ne 0 ]; then \
		echo "SHIFT-INPUT-30K: FAIL ($$normal) - normal 30k replay did not pass"; \
		exit $$normal; \
	fi; \
	echo "input-30k: padded shifted build"; \
	$(PYTHON) tools/shift/shift_test.py --build --pad-bytes $(PAD_BYTES) \
		--toolchain "$(TOOLCHAIN)" > $(SHIFT_WORK)/input30k_build.log 2>&1; \
	build=$$?; \
	cat $(SHIFT_WORK)/input30k_build.log; \
	if [ $$build -ne 0 ]; then \
		echo "SHIFT-INPUT-30K: FAIL ($$build) - shifted build did not complete"; \
		exit $$build; \
	fi; \
	echo "input-30k: shifted replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(SHIFT_WORK)/mf_us_shift.gba \
		--scenario input --input "$(INPUT_30K)" \
		--frames $(INPUT_30K_FRAMES) > $$shift_log 2>&1; \
	shifted=$$?; \
	cat $$shift_log; \
	if [ $$shifted -eq 77 ]; then \
		echo "SHIFT-INPUT-30K: FAIL - harness disappeared after the normal replay"; \
		exit 1; \
	fi; \
	normal_final=$$(grep '^INPUT_FINAL ' $$normal_log | tail -1); \
	shift_final=$$(grep '^INPUT_FINAL ' $$shift_log | tail -1); \
	normal_ckpt=$$(grep '^INPUT frame=$(INPUT_30K_FRAMES) ' $$normal_log | tail -1); \
	shift_ckpt=$$(grep '^INPUT frame=$(INPUT_30K_FRAMES) ' $$shift_log | tail -1); \
	if [ -z "$$normal_final" ] || [ -z "$$shift_final" ]; then \
		echo "SHIFT-INPUT-30K: FAIL - missing INPUT_FINAL state"; \
		exit 1; \
	fi; \
	if [ -z "$$normal_ckpt" ] || [ -z "$$shift_ckpt" ]; then \
		echo "SHIFT-INPUT-30K: FAIL - missing INPUT checkpoint at frame $(INPUT_30K_FRAMES)"; \
		exit 1; \
	fi; \
	nfc=$$(get_field "$$normal_final" frame_counter); \
	sfc=$$(get_field "$$shift_final" frame_counter); \
	ndisp=$$(get_field "$$normal_final" disp); \
	sdisp=$$(get_field "$$shift_final" disp); \
	nmain=$$(get_field "$$normal_final" main); \
	smain=$$(get_field "$$shift_final" main); \
	ns1=$$(get_field "$$normal_final" s1); \
	ss1=$$(get_field "$$shift_final" s1); \
	ns2=$$(get_field "$$normal_final" s2); \
	ss2=$$(get_field "$$shift_final" s2); \
	ncd=$$(get_field "$$normal_ckpt" disp); \
	scd=$$(get_field "$$shift_ckpt" disp); \
	ncm=$$(get_field "$$normal_ckpt" main); \
	scm=$$(get_field "$$shift_ckpt" main); \
	ncs1=$$(get_field "$$normal_ckpt" s1); \
	scs1=$$(get_field "$$shift_ckpt" s1); \
	ncs2=$$(get_field "$$normal_ckpt" s2); \
	scs2=$$(get_field "$$shift_ckpt" s2); \
	echo "SHIFT-INPUT-30K normal  frame_counter=$$nfc disp=$$ndisp main=$$nmain s1=$$ns1 s2=$$ns2"; \
	echo "SHIFT-INPUT-30K shifted frame_counter=$$sfc disp=$$sdisp main=$$smain s1=$$ss1 s2=$$ss2"; \
	if [ "$$nfc" != "$$sfc" ] || [ "$$ndisp" != "$$sdisp" ] || \
	   [ "$$nmain" != "$$smain" ] || [ "$$ns1" != "$$ss1" ] || \
	   [ "$$ns2" != "$$ss2" ]; then \
		echo "SHIFT-INPUT-30K: FAIL - normal/shifted final state diverged at $(INPUT_30K_FRAMES) frames (BUG-004)"; \
		exit 1; \
	fi; \
	if [ "$$ncd" != "$$scd" ] || [ "$$ncm" != "$$scm" ] || \
	   [ "$$ncs1" != "$$scs1" ] || [ "$$ncs2" != "$$scs2" ]; then \
		echo "SHIFT-INPUT-30K: FAIL - normal/shifted checkpoint state diverged at frame $(INPUT_30K_FRAMES) (BUG-004)"; \
		exit 1; \
	fi; \
	if [ $$shifted -ne 0 ]; then \
		echo "SHIFT-INPUT-30K: FAIL ($$shifted) - shifted replay did not pass"; \
		exit $$shifted; \
	fi; \
	echo "SHIFT-INPUT-30K: PASS - normal and shifted state match at $(INPUT_30K_FRAMES) frames"

# QA-013: compare the saved gEventCounter high-water sequence and its
# area/room/nav context at the committed 30k checkpoints/transitions.
event-diff: shift-input-30k
	$(PYTHON) tests/emulator/event_diff.py --self-check
	$(PYTHON) tests/emulator/event_diff.py \
		$(SHIFT_WORK)/input30k_normal.log $(SHIFT_WORK)/input30k_shift.log

# QA-008: OAM parity telemetry.  Replay the committed 30k fixture on the normal
# and padded-shift builds, then compare the harness's OAM checkpoint lines:
# `count` is gNextOamSlot and `hash` is FNV-1a over all 128 hardware OAM
# entries.  A count/hash mismatch at a shared checkpoint fails this target.
# The line also carries a gOamData shadow-buffer hash; it is reported as
# telemetry and does not decide pass/fail.  A missing harness is SKIP (77),
# never a pass.  Savestate-based map/objective-page comparisons stay local-only
# (see tests/emulator/README.md); no .state file is part of this gate.
oam-diff:
	@mkdir -p $(SHIFT_WORK); \
	normal_log=$(SHIFT_WORK)/oam30k_normal.log; \
	shift_log=$(SHIFT_WORK)/oam30k_shift.log; \
	$(PYTHON) tests/emulator/oam_diff.py --self-check; \
	selfcheck=$$?; \
	if [ $$selfcheck -ne 0 ]; then \
		echo "OAM-DIFF: FAIL ($$selfcheck) - oam_diff self-check failed"; \
		exit $$selfcheck; \
	fi; \
	echo "oam-diff: normal 30k replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario input \
		--input "$(INPUT_30K)" --expect "$(INPUT_30K_EXPECT)" \
		--frames $(INPUT_30K_FRAMES) > $$normal_log 2>&1; \
	normal=$$?; \
	cat $$normal_log; \
	if [ $$normal -eq 77 ]; then \
		echo "OAM-DIFF: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "               this is not a pass"; \
		exit 77; \
	fi; \
	if [ $$normal -ne 0 ]; then \
		echo "OAM-DIFF: FAIL ($$normal) - normal 30k replay did not pass"; \
		exit $$normal; \
	fi; \
	echo "oam-diff: padded shifted build"; \
	$(PYTHON) tools/shift/shift_test.py --build --pad-bytes $(PAD_BYTES) \
		--toolchain "$(TOOLCHAIN)" > $(SHIFT_WORK)/oam30k_build.log 2>&1; \
	build=$$?; \
	cat $(SHIFT_WORK)/oam30k_build.log; \
	if [ $$build -ne 0 ]; then \
		echo "OAM-DIFF: FAIL ($$build) - shifted build did not complete"; \
		exit $$build; \
	fi; \
	echo "oam-diff: shifted 30k replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(SHIFT_WORK)/mf_us_shift.gba \
		--scenario input --input "$(INPUT_30K)" \
		--frames $(INPUT_30K_FRAMES) > $$shift_log 2>&1; \
	shifted=$$?; \
	cat $$shift_log; \
	if [ $$shifted -eq 77 ]; then \
		echo "OAM-DIFF: FAIL - harness disappeared after the normal replay"; \
		exit 1; \
	fi; \
	if [ $$shifted -ne 0 ]; then \
		echo "OAM-DIFF: FAIL ($$shifted) - shifted replay did not pass"; \
		exit $$shifted; \
	fi; \
	$(PYTHON) tests/emulator/oam_diff.py --normal $$normal_log \
		--shifted $$shift_log --checkpoints "$(OAM_CHECKPOINTS)"; \
	status=$$?; \
	if [ $$status -ne 0 ]; then \
		echo "OAM-DIFF: FAIL ($$status) - OAM checkpoint comparison failed"; \
	fi; \
	exit $$status

# QA-005: screenshot parity at the input checkpoints.  Run the committed 4k
# replay with --screen on the normal, padded-shift and data-reorder builds.
# The gate compares the framebuffer hashes at frames 600 and 900; the shifted
# build is expected to diverge there while BUG-003 is open.  State checkpoints
# stay in test/shift-input; this target fails only on a screen mismatch or a
# missing checkpoint.  A missing harness is SKIP (77), never a pass.
shift-screen:
	@mkdir -p $(SHIFT_WORK); \
	normal_log=$(SHIFT_WORK)/screen_normal.log; \
	shift_log=$(SHIFT_WORK)/screen_shift.log; \
	reorder_log=$(SHIFT_WORK)/screen_reorder.log; \
	echo "screen: normal 4k replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(ROM) --scenario input \
		--input "$(INPUT)" --frames 4000 --screen > $$normal_log 2>&1; \
	normal=$$?; \
	cat $$normal_log; \
	if [ $$normal -eq 77 ]; then \
		echo "SCREEN-DIFF: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "               this is not a pass"; \
		exit 77; \
	fi; \
	if [ $$normal -ne 0 ]; then \
		echo "SCREEN-DIFF: FAIL ($$normal) - normal --screen replay did not pass"; \
		exit $$normal; \
	fi; \
	echo "screen: padded shifted build"; \
	$(PYTHON) tools/shift/shift_test.py --build --pad-bytes $(PAD_BYTES) \
		--toolchain "$(TOOLCHAIN)" > $(SHIFT_WORK)/screen_shift_build.log 2>&1; \
	build=$$?; \
	cat $(SHIFT_WORK)/screen_shift_build.log; \
	if [ $$build -ne 0 ]; then \
		echo "SCREEN-DIFF: FAIL ($$build) - shifted build did not complete"; \
		exit $$build; \
	fi; \
	echo "screen: shifted 4k replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(SHIFT_WORK)/mf_us_shift.gba \
		--scenario input --input "$(INPUT)" --frames 4000 --screen \
		> $$shift_log 2>&1; \
	shifted=$$?; \
	cat $$shift_log; \
	if [ $$shifted -eq 77 ]; then \
		echo "SCREEN-DIFF: FAIL - harness disappeared after the normal replay"; \
		exit 1; \
	fi; \
	echo "screen: reordered build"; \
	$(PYTHON) tools/shift/shift_test.py --reorder --build \
		--pad-bytes $(PAD_BYTES) --toolchain "$(TOOLCHAIN)" \
		> $(SHIFT_WORK)/screen_reorder_build.log 2>&1; \
	reorder_build=$$?; \
	cat $(SHIFT_WORK)/screen_reorder_build.log; \
	if [ $$reorder_build -ne 0 ]; then \
		echo "SCREEN-DIFF: FAIL ($$reorder_build) - reordered build did not complete"; \
		exit $$reorder_build; \
	fi; \
	echo "screen: reordered 4k replay"; \
	$(PYTHON) tests/emulator/run.py --rom $(SHIFT_WORK)/mf_us_reorder.gba \
		--scenario input --input "$(INPUT)" --frames 4000 --screen \
		> $$reorder_log 2>&1; \
	reordered=$$?; \
	cat $$reorder_log; \
	hash_at() { \
		grep -oE "SCREEN frame=$$2 hash=[0-9a-f]+" "$$1" | tail -1 | sed 's/.*hash=//'; \
	}; \
	n600=$$(hash_at $$normal_log 600); n900=$$(hash_at $$normal_log 900); \
	s600=$$(hash_at $$shift_log 600); s900=$$(hash_at $$shift_log 900); \
	r600=$$(hash_at $$reorder_log 600); r900=$$(hash_at $$reorder_log 900); \
	echo "SCREEN-DIFF normal 600=$$n600 900=$$n900"; \
	echo "SCREEN-DIFF shifted 600=$$s600 900=$$s900"; \
	echo "SCREEN-DIFF reordered 600=$$r600 900=$$r900"; \
	if [ -z "$$n600" ] || [ -z "$$n900" ] || [ -z "$$s600" ] || [ -z "$$s900" ]; then \
		echo "SCREEN-DIFF: FAIL - missing SCREEN checkpoint (600/900)"; \
		exit 1; \
	fi; \
	if [ "$$s600" != "$$n600" ] || [ "$$s900" != "$$n900" ]; then \
		echo "SCREEN-DIFF: FAIL - normal and shifted framebuffer hashes differ"; \
		exit 1; \
	fi; \
	if [ $$shifted -ne 0 ]; then \
		echo "SCREEN-DIFF: FAIL ($$shifted) - shifted replay did not pass"; \
		exit $$shifted; \
	fi; \
	if [ -z "$$r600" ] || [ -z "$$r900" ]; then \
		echo "SCREEN-DIFF: FAIL - reordered replay has no 600/900 SCREEN checkpoint"; \
		exit 1; \
	fi; \
	if [ "$$r600" != "$$n600" ] || [ "$$r900" != "$$n900" ]; then \
		echo "SCREEN-DIFF: FAIL - normal and reordered framebuffer hashes differ"; \
		exit 1; \
	fi; \
	if [ $$reordered -ne 0 ]; then \
		echo "SCREEN-DIFF: FAIL ($$reordered) - reordered replay did not pass"; \
		exit $$reordered; \
	fi; \
	echo "SCREEN-DIFF: PASS - normal, shifted and reordered match at 600/900"

# Alias used by the QA-005 charter; it is exactly the shift-screen gate.
screen-diff: shift-screen

# Data-only reorder: swap two .rodata inputs.  Code (AgbMain) must not move,
# the swapped data symbols must, and the boot smoke must still pass.
shift-reorder: audit smoke check-linker
	@$(PYTHON) tools/shift/shift_test.py --reorder --build --run \
		--frames $(FRAMES) --toolchain "$(TOOLCHAIN)"; \
	status=$$?; \
	if [ $$status -eq 0 ]; then \
		echo "SHIFT-REORDER: PASS"; \
	elif [ $$status -eq 77 ]; then \
		echo "SHIFT-REORDER: SKIP (77) - no emulator/harness; dynamic behavior did not run"; \
		echo "                  this is not a pass"; \
	else \
		echo "SHIFT-REORDER: FAIL ($$status)"; \
	fi; \
	exit $$status

# Both halves of the S2 shift gate.  `shift-check` keeps its padding-only
# meaning; this convenience target runs padding first, then section reorder.
shift-check-all: shift-check shift-reorder

# Help text is written once: the main Makefile expands $(SHIFT_HELP) inside
# `make help`, and `make shift-help` prints the same block on its own.  `help`
# itself stays owned by the main Makefile (no duplicate recipe here).
define SHIFT_HELP
	@echo "  audit               regenerate symbols, relocation audit, blobs, report"
	@echo "  check-relocs        report remaining hardcoded ROM refs and raw blobs"
	@echo "  check-relocs-strict fail on literals, C ROM refs, or raw pointer-like blobs"
	@echo "  check-linker        verify linker.ld has no fixed ROM addresses"
	@echo "  postlink-scan       report raw pointer runs in --emit-relocs data sections"
	@echo "  postlink-scan-strict fail on any unwhitelisted structured pointer run"
	@echo "  smoke               static ROM/header smoke"
	@echo "  content-check       content pipeline + D-009 ID registry check (no ROM)"
	@echo "  data-manifest       write tools/data-manifest.json from extracted data"
	@echo "  data-verify         fail if extracted data is missing, extra, or changed"
	@echo "  data-cache-key      print baserom+manifest cache key (one line)"
	@echo "  public-gate         ROM-free public CI gate (no baserom/toolchain)"
	@echo "  protected-gate      private-runner CI gate (baserom/toolchain/BIOS/movie)"
	@echo "  collect-symbols     package mf_us.map + work/shift/*.json as an artifact"
	@echo "  host-test           host-compiler unit tests for pure engine code"
	@echo "  emulator-harness    build tests/emulator/bin/mgba-harness (MGBA_SRC/MGBA_BUILD)"
	@echo "  test                static + headless boot smoke + 4k input replay (exit 77 if no harness)"
	@echo "  test-input          normal-ROM 4k input replay + checkpoint assertion"
	@echo "  input-smoke         replay a frame/keys file (INPUT=..., INPUT_FRAMES=N)"
	@echo "  shift-build         build with a padded linker layout"
	@echo "  shift-test          padded build + behavior scenario"
	@echo "  shift-check         audit + smoke + link check + shift-test (padding)"
	@echo "  shift-start         padded build + Start/file-select scenario (QA-001)"
	@echo "  shift-input         padded build + 4k input replay + checkpoint assertion (QA-003)"
	@echo "  shift-input-30k     normal/shifted 30k input parity + checkpoint assertion (QA-006)"
	@echo "  shift-screen        normal/shifted/reordered 4k framebuffer parity at 600/900 (QA-005)"
	@echo "  screen-diff         alias for shift-screen"
	@echo "  oam-diff            normal/shifted 30k OAM count/hash parity at 300..30000 (QA-008)"
	@echo "  event-diff          normal/shifted 30k event-counter/context parity (QA-013)"
	@echo "  shift-reorder       audit + smoke + link check + .rodata reorder test"
	@echo "  shift-check-all     shift-check then shift-reorder"
	@echo "Variables: MAP, ROM, DATA_ROOT, DATA_MANIFEST, TOOLCHAIN, FRAMES, START_FRAMES, INPUT, INPUT_FRAMES, INPUT_EXPECT, INPUT_30K, INPUT_30K_EXPECT, INPUT_30K_FRAMES, OAM_CHECKPOINTS, PAD_BYTES, SHIFT_WORK, POSTLINK_ELF, POSTLINK_MAP, POSTLINK_JSON, POSTLINK_WHITELIST"
	@echo "CI variables: OUT_DIR (collect-symbols), HEADLESS, HEADLESS_TIER, HEADLESS_SHIFT_BUILD, HEADLESS_BIOS, HEADLESS_MOVIE, JOBS, SYMBOLS"
endef

.PHONY: shift-help
shift-help:
	@echo "Shift/audit/test targets (also via: make -f Makefile.shift <target>):"
	$(SHIFT_HELP)
	@echo ""
