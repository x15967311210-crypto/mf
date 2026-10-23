# mk/m2c.mk — manual m2c decompiler entry point (TECH-009).
#
# m2c is a *draft generator* for one function at a time: it turns split
# disassembly into readable, non-matching C.  It is cloned under the git-ignored
# work/ tree and is never vendored, so this target is a developer convenience
# and is deliberately NOT part of `all`, `audit`, `smoke`, `test` or CI.  It
# changes no tracked file.
#
#   make m2c                           # setup --check, self-check, one-shot pilot
#   tools/decomp/m2c/run.sh --asm ... --function ...   # a real function
#
# Unlike `make permute` this target runs no search: one extraction plus one
# decompile, then it exits.  The full workflow, options and output-quality
# limitations are in docs/howto/m2c.md.

.PHONY: m2c
m2c:
	$(MSG) M2C SramWrite_MostRecentSaveFile one-shot pilot
	$Qtools/decomp/m2c/setup.sh --check
	$Qtools/decomp/m2c/run.sh --self-check
	$Qtools/decomp/m2c/run.sh \
		--asm asm/disasm_0x0807e678_0807eea4_08080068.s \
		--function SramWrite_MostRecentSaveFile \
		--context tools/decomp/m2c/context/sram_write_recent.c \
		--symbols tools/decomp/m2c/symbols/sram.syms \
		--out work/decompme/SramWrite_MostRecentSaveFile.m2c.c

define M2C_HELP
	@echo "  m2c: optional m2c decompiler pilot (manual; never a gate or CI target)"
endef
