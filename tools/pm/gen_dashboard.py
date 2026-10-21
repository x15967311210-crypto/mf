#!/usr/bin/env python3
"""Generate docs/dashboard.md from the four project sources of truth.

The dashboard is a deterministic, read-only summary of:

* ``jira.md``                    — the backlog (source of truth for tasks)
* ``docs/roadmap.md``            — phase gates
* ``docs/playtest.md``           — recorded human sign-offs
* ``docs/shiftability-audit.md`` — relocation counts and build SHAs

Every section links its source.  The output contains no timestamps, no
absolute paths, and no host-specific data, so it is stable across runs and
machines.  ``--check`` fails when the checked-in dashboard is stale.

Only the Python standard library is used.
"""

from __future__ import annotations

import argparse
import contextlib
import io
import os
import re
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_jira  # noqa: E402  (same directory, stdlib-only module)

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DEFAULT_OUT = os.path.join(ROOT, "docs", "dashboard.md")

GATE_RE = re.compile(r"^Gate \*\*(?P<id>[^*]+)\*\*:\s*(?P<text>.*)$")
OPEN_LITERALS_RE = re.compile(
    r"open ROM literals[^\n:]*:\s*\**(\d+)\**", re.IGNORECASE
)
HEX_RE = re.compile(r"\b[0-9a-fA-F]{7,40}\b")


def _read(path):
    with open(path, "r", encoding="utf-8") as handle:
        return handle.read()


def _one_line(text):
    return re.sub(r"\s+", " ", text).strip()


def _section_source(label, target):
    return "Source: [%s](%s)" % (label, target)


def render_backlog(result):
    entries = result["entries"]
    counts = result["counts"]
    doing = [entry for entry in entries if entry.state == "DOING"]
    todo = [entry for entry in entries if entry.state == "TODO"][:5]
    done = [entry for entry in entries if entry.state == "DONE"][-5:]

    lines = [
        "## Backlog",
        "",
        "_`jira.md` is the backlog source of truth._  "
        + _section_source("jira.md", "../jira.md"),
        "",
        "Counts: **%d TODO / %d DOING / %d DONE / %d PARK** (%d entries)."
        % (
            counts["TODO"],
            counts["DOING"],
            counts["DONE"],
            counts["PARK"],
            len(entries),
        ),
        "",
        "### In progress (DOING)",
        "",
    ]
    if doing:
        for entry in doing:
            lines.append(
                "- `%s` — %s" % ("/".join(entry.ids), _one_line(entry.title))
            )
    else:
        lines.append("_none_")

    lines.extend(["", "### Next TODO (first 5 in file order)", ""])
    if todo:
        for entry in todo:
            lines.append(
                "- `%s` — %s" % ("/".join(entry.ids), _one_line(entry.title))
            )
    else:
        lines.append("_none_")

    lines.extend(["", "### Most recent DONE (last 5 in file order)", ""])
    if done:
        for entry in done:
            lines.append(
                "- `%s` — %s" % ("/".join(entry.ids), _one_line(entry.title))
            )
            evidence = check_jira.entry_evidence(entry)
            if evidence:
                kind, value = evidence
                lines.append("  - evidence: %s `%s`" % (kind, value))
            else:
                lines.append("  - evidence: not found")
    else:
        lines.append("_none_")
    return lines


def parse_gates(text):
    lines = text.splitlines()
    gates = []
    for index, line in enumerate(lines):
        match = GATE_RE.match(line)
        if not match:
            continue
        body = match.group("text").strip()
        if index + 1 < len(lines):
            following = lines[index + 1].strip()
            structural = (
                not following
                or following.startswith(("#", "-", "*", "|", "```"))
                or GATE_RE.match(lines[index + 1])
            )
            if not structural and not body.endswith((".", "!", "?")):
                body = body + " " + following
        gates.append((match.group("id").strip(), _one_line(body)))
    return gates


def render_gates(text):
    lines = [
        "## Gates",
        "",
        _section_source("roadmap.md", "roadmap.md"),
        "",
    ]
    gates = parse_gates(text)
    if gates:
        for gate_id, body in gates:
            lines.append("- **%s** — %s" % (gate_id, body))
    else:
        lines.append("_not found_")
    return lines


def parse_playtest_rows(text):
    return [
        line.strip()
        for line in text.splitlines()
        if line.strip().startswith("| M")
    ]


def render_playtest(text):
    lines = [
        "## Playtest",
        "",
        _section_source("playtest.md", "playtest.md"),
        "",
    ]
    rows = parse_playtest_rows(text)
    if not rows:
        lines.append("_not found_")
        return lines
    lines.append("| Gate | Date | Build | Result |")
    lines.append("|---|---|---|---|")
    lines.extend(rows)
    return lines


def _sha_near(text, word, alternatives=()):
    """Return the first hex SHA following ``word`` on a SHA-labelled line."""
    for line in text.splitlines():
        lowered = line.lower()
        if "sha" not in lowered and "hash" not in lowered:
            continue
        for needle in (word,) + tuple(alternatives):
            index = lowered.find(needle)
            if index < 0:
                continue
            match = HEX_RE.search(line[index + len(needle) :])
            if match:
                return match.group(0)
    return None


def parse_relocation(text):
    open_match = OPEN_LITERALS_RE.search(text)
    open_literals = open_match.group(1) if open_match else None
    return {
        "open_literals": open_literals,
        "baseline": _sha_near(text, "baseline", ("normal",)),
        "shifted": _sha_near(text, "shifted"),
        "reordered": _sha_near(text, "reordered"),
    }


def render_relocation(text):
    values = parse_relocation(text)
    if values["open_literals"] is None:
        open_literal_line = "- Open ROM literals: not found"
    else:
        open_literal_line = "- Open ROM literals: **%s**" % values["open_literals"]
    lines = [
        "## Relocation",
        "",
        _section_source("shiftability-audit.md", "shiftability-audit.md"),
        "",
        open_literal_line,
    ]
    for label, key in (
        ("Baseline SHA", "baseline"),
        ("Shifted SHA", "shifted"),
        ("Reordered SHA", "reordered"),
    ):
        value = values[key]
        lines.append("- %s: %s" % (label, "`%s`" % value if value else "not found"))
    return lines


def generate_text(root):
    """Render the dashboard for a repository root, without writing anything."""
    jira = check_jira.analyze(_read(os.path.join(root, "jira.md")))
    roadmap = _read(os.path.join(root, "docs", "roadmap.md"))
    playtest = _read(os.path.join(root, "docs", "playtest.md"))
    audit = _read(os.path.join(root, "docs", "shiftability-audit.md"))

    lines = [
        "# Project dashboard",
        "",
        "Generated by tools/pm/gen_dashboard.py from roadmap/playtest/jira/audit; do not hand-edit.",
        "",
        "Sources: [backlog](../jira.md) · [roadmap](roadmap.md) · "
        "[playtest](playtest.md) · [shiftability audit](shiftability-audit.md)",
        "",
    ]
    lines.extend(render_backlog(jira))
    lines.append("")
    lines.extend(render_gates(roadmap))
    lines.append("")
    lines.extend(render_playtest(playtest))
    lines.append("")
    lines.extend(render_relocation(audit))
    lines.append("")
    return "\n".join(lines)


def _display(path, root=ROOT):
    try:
        relative = os.path.relpath(path, root)
    except ValueError:  # different drive on Windows
        relative = os.path.basename(path)
    if relative.startswith(".."):
        return os.path.basename(path)
    return relative


def write_dashboard(root, out):
    text = generate_text(root)
    parent = os.path.dirname(out)
    if parent:
        os.makedirs(parent, exist_ok=True)
    with open(out, "w", encoding="utf-8", newline="\n") as handle:
        handle.write(text)
    print("dashboard: wrote %s" % _display(out, root))
    return 0


def check_dashboard(root, out):
    text = generate_text(root)
    label = _display(out, root)
    try:
        current = _read(out)
    except FileNotFoundError:
        print("dashboard-check: FAIL (%s is missing; run make dashboard)" % label)
        return 1
    if current != text:
        print("dashboard-check: FAIL (%s is stale; run make dashboard)" % label)
        return 1
    print("dashboard-check: OK (%s is current)" % label)
    return 0


# --------------------------------------------------------------------------
# Self-check: synthetic fixtures for every parser plus determinism.
# --------------------------------------------------------------------------


JIRA_FIXTURE = """# backlog

- [TODO] T-01 (tools) — first open item
- [TODO] T-02 (tools) — second open item
- [TODO] T-03 (tools) — third open item
- [TODO] T-04 (tools) — fourth open item
- [TODO] T-05 (tools) — fifth open item
- [TODO] T-06 (tools) — sixth open item, must not appear
- [DOING @dev9] T-07 (tools) — in progress item
  - working on `tools/pm/gen_dashboard.py`
- [DONE] T-08 (tools) — older done
  - commit `deadbeef`
- [DONE] T-09 (tools) — newer done
  - landed `tests/pm/dashboard_test.py`
- [PARK] T-10 (emulator) — waiting on a human
  - blocked on the playtest
"""

ROADMAP_FIXTURE = """# Roadmap

Gate **A1**: a gate whose sentence
continues on the next line.

Gate **A2**: a complete one-line gate.
"""

PLAYTEST_FIXTURE = """# Playtest

## Recorded sign-offs

| Gate | Date | Build | Result |
|---|---|---|---|
| M0 | 2026-01-01 | baseline `deadbeef...` | **PASS** |
| M1 | 2026-02-02 | shifted `feedface...` | pending |
"""

AUDIT_FIXTURE = """# Shiftability audit

- open ROM literals (both kinds): **7**
- baseline SHA: `deadbeef...`
- shifted SHA: `feedface...`
- reordered SHA: `cafebabe...`
"""


def _fixture(root, name, text):
    path = os.path.join(root, name)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as handle:
        handle.write(text)
    return path


def _check_quiet(root, out):
    with contextlib.redirect_stdout(io.StringIO()):
        return check_dashboard(root, out)


def self_check():
    checks = []

    def expect(name, condition):
        checks.append((name, bool(condition)))

    with tempfile.TemporaryDirectory(prefix="gen-dashboard-") as tmp:
        root = os.path.join(tmp, "repo")
        _fixture(root, "jira.md", JIRA_FIXTURE)
        _fixture(root, "docs/roadmap.md", ROADMAP_FIXTURE)
        _fixture(root, "docs/playtest.md", PLAYTEST_FIXTURE)
        _fixture(root, "docs/shiftability-audit.md", AUDIT_FIXTURE)

        text = generate_text(root)

        # Backlog: counts, DOING, first-five truncation, last-five DONE.
        expect(
            "backlog counts",
            "**6 TODO / 1 DOING / 2 DONE / 1 PARK**" in text,
        )
        expect("doing entry", "`T-07` — in progress item" in text)
        expect("TODO truncation", "T-06" not in text)
        expect("DONE list", "`T-08` — older done" in text and "`T-09` — newer done" in text)
        expect("DONE commit evidence", "evidence: commit `deadbeef`" in text)
        expect("DONE path evidence", "evidence: path `tests/pm/dashboard_test.py`" in text)
        expect("source-of-truth note", "backlog source of truth" in text)

        # Gates: continuation line joined, one-line gate untouched.
        expect(
            "gate continuation",
            "**A1** — a gate whose sentence continues on the next line." in text,
        )
        expect("gate one-line", "**A2** — a complete one-line gate." in text)

        # Playtest table rows.
        expect("playtest rows", "| M0 | 2026-01-01 |" in text and "| M1 | 2026-02-02 |" in text)

        # Relocation values.
        expect("open literals", "Open ROM literals: **7**" in text)
        expect("baseline sha", "Baseline SHA: `deadbeef`" in text)
        expect("shifted sha", "Shifted SHA: `feedface`" in text)
        expect("reordered sha", "Reordered SHA: `cafebabe`" in text)

        # Missing values degrade to "not found" instead of crashing.
        _fixture(root, "docs/shiftability-audit.md", "# Shiftability audit\n")
        missing = generate_text(root)
        expect("missing open literals", "Open ROM literals: not found" in missing)
        expect("missing baseline", "Baseline SHA: not found" in missing)
        _fixture(root, "docs/shiftability-audit.md", AUDIT_FIXTURE)

        # Determinism: same inputs, byte-identical output.
        expect("deterministic output", generate_text(root) == text)

        # --write then --check is green; a manual edit makes --check fail.
        out = os.path.join(root, "docs", "dashboard.md")
        with contextlib.redirect_stdout(io.StringIO()):
            write_dashboard(root, out)
        expect("check after write", _check_quiet(root, out) == 0)
        expect("written text matches", _read(out) == text)
        with open(out, "a", encoding="utf-8") as handle:
            handle.write("\nstale\n")
        expect("check detects stale", _check_quiet(root, out) == 1)

    failed = [name for name, ok in checks if not ok]
    if failed:
        print("gen-dashboard self-check: FAIL (%s)" % ", ".join(failed))
        return 1
    print("gen-dashboard self-check: PASS (%d checks)" % len(checks))
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description="Generate docs/dashboard.md.")
    parser.add_argument("--root", default=ROOT, help=argparse.SUPPRESS)
    parser.add_argument("--out", default=DEFAULT_OUT)
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--write", action="store_true", help="write the dashboard")
    group.add_argument("--check", action="store_true", help="fail if it is stale")
    group.add_argument("--self-check", action="store_true", help="run synthetic fixtures")
    args = parser.parse_args(argv)

    if args.self_check:
        return self_check()
    if args.write:
        return write_dashboard(args.root, args.out)
    if args.check:
        return check_dashboard(args.root, args.out)
    sys.stdout.write(generate_text(args.root))
    return 0


if __name__ == "__main__":
    sys.exit(main())
