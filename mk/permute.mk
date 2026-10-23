# mk/permute.mk — manual decomp-permuter entry point (TECH-007).
#
# decomp-permuter is a *hint generator* for one function at a time.  It is
# cloned under the git-ignored work/ tree and is never vendored, so this
# target is a developer convenience and is deliberately NOT part of `all`,
# `audit`, `smoke`, `test` or CI.  It changes no tracked file.
#
#   make permute                       # self-check + 900s bounded pilot
#   make permute PERMUTE_TIMEOUT=300
#   make permute PERMUTE_JOBS=8
#   make permute PERMUTE_ARGS=--debug  # base score only, no search
#
# The full workflow, score meaning and limitations are in
# docs/howto/decomp-permuter.md.

PERMUTE_TIMEOUT ?= 900
PERMUTE_JOBS ?=
PERMUTE_ARGS ?=

.PHONY: permute
permute:
	$(MSG) PERMUTE SramWrite_MostRecentSaveFile timeout=$(PERMUTE_TIMEOUT)s
	$Qtools/decomp/permuter/run.sh --self-check
	$Qtools/decomp/permuter/import_sram_recent.sh \
		--timeout $(PERMUTE_TIMEOUT) \
		$(if $(PERMUTE_JOBS),--jobs $(PERMUTE_JOBS)) $(PERMUTE_ARGS)

define PERMUTE_HELP
	@echo "  permute: bounded decomp-permuter pilot (manual; never a gate or CI target)"
endef
