# Project-management targets (PM-001).
#
# These targets read the Markdown sources of truth and never touch ROM inputs:
#   make jira-check       validate jira.md (states, IDs, deps, DONE evidence)
#   make dashboard        regenerate docs/dashboard.md
#   make dashboard-check  fail if docs/dashboard.md is stale
#   make jira-check-self  run both tools' synthetic self-checks
#
# The fragment is self-contained: every default uses `?=`, so the main
# Makefile's PYTHON definition wins.  It defines no `all` or `help` target;
# its help lines are contributed through $(PM_HELP), like mk/shift.mk and
# mk/hack.mk.

PYTHON ?= python3

JIRA_FILE ?= jira.md
PM_DASHBOARD ?= docs/dashboard.md

.PHONY: jira-check dashboard dashboard-check jira-check-self

jira-check:
	$(PYTHON) tools/pm/check_jira.py --jira $(JIRA_FILE)

dashboard:
	$(PYTHON) tools/pm/gen_dashboard.py --write --out $(PM_DASHBOARD)

dashboard-check:
	$(PYTHON) tools/pm/gen_dashboard.py --check --out $(PM_DASHBOARD)

jira-check-self:
	$(PYTHON) tools/pm/check_jira.py --self-check
	$(PYTHON) tools/pm/gen_dashboard.py --self-check

define PM_HELP
	@echo "  jira-check          validate jira.md (states, IDs, deps, DONE evidence, DOING owner)"
	@echo "  dashboard           regenerate docs/dashboard.md from jira/roadmap/playtest/audit"
	@echo "  dashboard-check     fail if docs/dashboard.md is stale (run make dashboard)"
	@echo "  jira-check-self     self-check the jira/dashboard tools on synthetic fixtures"
	@echo "Variables: JIRA_FILE, PM_DASHBOARD"
endef
