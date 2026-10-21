# mk/format.mk — C format contract (DOC-002).
#
# The style itself is `.clang-format` in the repository root and is described
# in docs/style.md.  This fragment only provides the entry points:
#
#   make format        clang-format -i over the tracked C/header sources
#   make format-check  clang-format --dry-run --Werror over the same list
#   make format-list   print the exact file list, one path per line
#
# Scope is C sources and headers only: src/**/*.c, include/**/*.h and
# hack/**/*.c|h.  Generated content under hack/gen/ is excluded, and no
# assembly, data, generated header or file under work/ is ever formatted.
#
# The tree is deliberately NOT mass-reformatted yet (DOC-002): `make
# format-check` may fail on existing files until a dedicated reformat task
# lands.  Do not "fix" the gate by reformatting unrelated code; see
# docs/style.md.
#
# A missing clang-format is reported as SKIP (77), never as a pass.
# `clang-format --dry-run --Werror` needs clang-format >= 10.
#
# The fragment is self-contained (every default uses `?=`) and defines no
# `all` or `help` target; its help lines are contributed through
# $(FORMAT_HELP), like mk/shift.mk, mk/hack.mk and mk/pm.mk.

CLANG_FORMAT ?= clang-format
FORMAT_STYLE ?= --style=file
FORMAT_PATHS ?= src include hack
FORMAT_EXCLUDE ?= hack/gen

# Recursive (`=`) on purpose: the find only runs when a format target expands
# it, so bootstrapping every other target pays nothing.  An explicit
# FORMAT_FILES=... on the command line always wins.
FORMAT_FILES ?= $(shell find $(FORMAT_PATHS) -type f \( -name '*.c' -o -name '*.h' \) \
	! -path '$(FORMAT_EXCLUDE)/*' 2>/dev/null | LC_ALL=C sort)

.PHONY: format format-check format-list

format:
	@files="$(FORMAT_FILES)"; set -- $$files; \
	if [ $$# -eq 0 ]; then \
		echo "FORMAT: FAIL - no C/header sources matched ($(FORMAT_PATHS))"; \
		exit 1; \
	fi; \
	if ! command -v "$(CLANG_FORMAT)" >/dev/null 2>&1; then \
		echo "FORMAT: FAIL - $(CLANG_FORMAT) not found; nothing was rewritten"; \
		echo "              install clang-format (>= 10) or set CLANG_FORMAT=<path>; see docs/style.md"; \
		exit 1; \
	fi; \
	echo "FORMAT: rewriting $$# files with $(CLANG_FORMAT) $(FORMAT_STYLE)"; \
	$(CLANG_FORMAT) $(FORMAT_STYLE) -i $$files

format-check:
	@files="$(FORMAT_FILES)"; set -- $$files; \
	if ! command -v "$(CLANG_FORMAT)" >/dev/null 2>&1; then \
		echo "FORMAT-CHECK: SKIP (77) - $(CLANG_FORMAT) not found; this is not a pass"; \
		echo "              install clang-format (>= 10) or set CLANG_FORMAT=<path>; see docs/style.md"; \
		exit 0; \
	fi; \
	if [ $$# -eq 0 ]; then \
		echo "FORMAT-CHECK: FAIL - no C/header sources matched ($(FORMAT_PATHS))"; \
		exit 1; \
	fi; \
	$(CLANG_FORMAT) --dry-run --Werror $(FORMAT_STYLE) $$files; \
	status=$$?; \
	if [ $$status -eq 0 ]; then \
		echo "FORMAT-CHECK: PASS ($$# files)"; \
	else \
		echo "FORMAT-CHECK: FAIL ($$status) - existing style differs from .clang-format"; \
		echo "               fix the files you touch, do not mass-reformat (docs/style.md)"; \
	fi; \
	exit $$status

format-list:
	@files="$(FORMAT_FILES)"; set -- $$files; \
	if [ $$# -eq 0 ]; then \
		echo "FORMAT-LIST: FAIL - no C/header sources matched ($(FORMAT_PATHS))"; \
		exit 1; \
	fi; \
	printf '%s\n' $$files

define FORMAT_HELP
	@echo "  format              clang-format -i over src/**/*.c, include/**/*.h, hack/**/*.c|h"
	@echo "  format-check        clang-format --dry-run --Werror on the same list (SKIP 77 if missing)"
	@echo "  format-list         print the files the format targets cover"
	@echo "Variables: CLANG_FORMAT, FORMAT_STYLE, FORMAT_PATHS, FORMAT_EXCLUDE, FORMAT_FILES"
endef
