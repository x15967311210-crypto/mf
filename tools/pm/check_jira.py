#!/usr/bin/env python3
"""Validate the mf-hack backlog in jira.md.

The backlog is a hand-maintained Markdown file.  Each entry starts with a
bullet of the form

    - [STATE] ID (source, ...) -- title  [deps: ID, ID]  @dev

followed by indented continuation lines.  This checker is deliberately
conservative about prose: anything it cannot classify is left alone, while a
malformed entry, a duplicate ID, a dangling dependency or a DONE entry without
evidence is reported with a line number.

Rules
-----
1. STATE is one of TODO, DOING, DONE, PARK.
2. Combined IDs (``QA-002/QA-003``) are split, and every resulting ID must be
   unique in the file.
3. ``[deps: ...]`` must reference existing IDs and may not be self-referential.
4. A DONE entry's title or continuation lines must contain a commit hash
   (7-40 lowercase hex characters) or a repository path token (docs/...,
   tools/..., tests/..., src/..., hack/... and friends).
5. A DOING entry must carry an ``@dev`` marker (``@dev``, ``@dev17``, ...).
6. A PARK entry should say why in its block; a missing reason is a warning.

Only the Python standard library is used.  Output contains no timestamps and
no absolute paths.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
import tempfile

STATES = ("TODO", "DOING", "DONE", "PARK")

# - [DONE @qa] QA-029 (emulator) — title
ENTRY_RE = re.compile(
    r"^(?P<indent>\s*)-\s*\[(?P<state>[A-Za-z]+)(?P<markers>[^\]]*)\]\s+"
    r"(?P<ids>\S+)\s*(?:\((?P<source>[^)]*)\))?\s*—\s*(?P<title>.*)$"
)
HEADING_RE = re.compile(r"^#{1,6}\s")
HASH_RE = re.compile(r"\b[0-9a-f]{7,40}\b")
PATH_RE = re.compile(
    r"(?<![\w/])(?:docs|tools|tests|src|hack|asm|sound|include|mk|data|work)"
    r"/(?:[\w.\-]+/)*[\w.\-]+"
)
DEV_RE = re.compile(r"@dev\w*")
DEPS_RE = re.compile(r"\[deps:\s*([^\]]*)\]")
PAREN_REASON_RE = re.compile(r"\([^)]*(?:defer|pause|block|wait|hold|reason)[^)]*\)", re.I)


class Entry:
    """One parsed backlog entry and the lines that belong to it."""

    def __init__(self, line, state, markers, ids, source, title, body):
        self.line = line
        self.state = state
        self.markers = markers
        self.ids = ids
        self.source = source
        self.title = title
        self.body = body

    def block_text(self, include_header=True):
        parts = []
        if include_header:
            parts.append("- [%s] %s — %s" % (self.state, "/".join(self.ids), self.title))
        parts.extend(self.body)
        return "\n".join(parts)


def split_ids(token):
    """Split ``QA-002/QA-003`` into separate IDs, preserving order."""
    return [part.strip() for part in token.split("/") if part.strip()]


def parse_entries(text):
    """Parse the Markdown backlog into Entry objects, in file order."""
    lines = text.splitlines()
    header_indexes = [i for i, line in enumerate(lines) if ENTRY_RE.match(line)]
    entries = []
    for pos, start in enumerate(header_indexes):
        match = ENTRY_RE.match(lines[start])
        stop = header_indexes[pos + 1] if pos + 1 < len(header_indexes) else len(lines)
        # A heading or unindented prose after the entry ends the block even
        # when the next entry header is far away (the "Open questions" tail).
        end = stop
        for j in range(start + 1, stop):
            line = lines[j]
            if HEADING_RE.match(line):
                end = j
                break
            if line.strip() and not line[:1].isspace():
                end = j
                break
        entries.append(
            Entry(
                line=start + 1,
                state=match.group("state"),
                markers=match.group("markers").strip(),
                ids=split_ids(match.group("ids")),
                source=(match.group("source") or "").strip(),
                title=match.group("title").strip(),
                body=lines[start + 1 : end],
            )
        )
    return entries


def entry_evidence(entry):
    """Return ``(kind, value)`` for a DONE entry, or ``None``.

    The source annotation and state marker are not evidence: ``(tools/qa)``
    is a label, not a committed path.  The title and continuation lines are
    searched instead.
    """
    text = entry.title + "\n" + "\n".join(entry.body)
    match = HASH_RE.search(text)
    if match:
        return ("commit", match.group(0))
    match = PATH_RE.search(text)
    if match:
        return ("path", match.group(0))
    return None


def analyze(text):
    """Return the full check result for a backlog document."""
    entries = parse_entries(text)
    all_ids = {}
    errors = []
    warnings = []

    for entry in entries:
        for entry_id in entry.ids:
            all_ids.setdefault(entry_id, []).append(entry.line)

    for entry in entries:
        if entry.state not in STATES:
            errors.append(
                {
                    "line": entry.line,
                    "rule": "invalid-state",
                    "id": "/".join(entry.ids),
                    "message": "unknown state %r (expected one of %s)"
                    % (entry.state, ", ".join(STATES)),
                }
            )
        if not entry.ids:
            errors.append(
                {
                    "line": entry.line,
                    "rule": "missing-id",
                    "id": "",
                    "message": "entry has no ID",
                }
            )

    for entry_id, lines in all_ids.items():
        if len(lines) > 1:
            errors.append(
                {
                    "line": lines[0],
                    "rule": "duplicate-id",
                    "id": entry_id,
                    "lines": lines,
                    "message": "duplicate ID %s (lines %s)"
                    % (entry_id, ", ".join(str(line) for line in lines)),
                }
            )

    known_ids = set(all_ids)
    for entry in entries:
        deps_match = DEPS_RE.search(
            "- [%s] %s — %s" % (entry.state, "/".join(entry.ids), entry.title)
        )
        if not deps_match:
            continue
        deps = []
        for chunk in deps_match.group(1).split(","):
            deps.extend(split_ids(chunk))
        for dep in deps:
            if dep in entry.ids:
                errors.append(
                    {
                        "line": entry.line,
                        "rule": "self-dependency",
                        "id": "/".join(entry.ids),
                        "dep": dep,
                        "message": "%s depends on itself"
                        % "/".join(entry.ids),
                    }
                )
            elif dep not in known_ids:
                errors.append(
                    {
                        "line": entry.line,
                        "rule": "missing-dependency",
                        "id": "/".join(entry.ids),
                        "dep": dep,
                        "message": "%s depends on unknown ID %s"
                        % ("/".join(entry.ids), dep),
                    }
                )

    for entry in entries:
        label = "/".join(entry.ids)
        if entry.state == "DONE" and entry_evidence(entry) is None:
            errors.append(
                {
                    "line": entry.line,
                    "rule": "done-without-evidence",
                    "id": label,
                    "message": "DONE %s has no evidence (commit hash or path)" % label,
                }
            )
        if entry.state == "DOING" and not DEV_RE.search(
            entry.markers + " " + entry.block_text()
        ):
            errors.append(
                {
                    "line": entry.line,
                    "rule": "doing-without-dev",
                    "id": label,
                    "message": "DOING %s has no @dev marker" % label,
                }
            )
        if entry.state == "PARK":
            has_reason = any(line.strip() for line in entry.body)
            if not has_reason:
                has_reason = bool(PAREN_REASON_RE.search(entry.title))
            if not has_reason:
                warnings.append(
                    {
                        "line": entry.line,
                        "rule": "park-without-reason",
                        "id": label,
                        "message": "PARK %s has no reason in its block" % label,
                    }
                )

    errors.sort(key=lambda item: (item["line"], item["rule"], item.get("id", "")))
    warnings.sort(key=lambda item: (item["line"], item["rule"], item.get("id", "")))

    counts = {state: 0 for state in STATES}
    for entry in entries:
        if entry.state in counts:
            counts[entry.state] += 1

    return {
        "entries": entries,
        "counts": counts,
        "errors": errors,
        "warnings": warnings,
    }


def _json_result(result):
    entries = []
    for entry in result["entries"]:
        evidence = entry_evidence(entry) if entry.state == "DONE" else None
        entries.append(
            {
                "line": entry.line,
                "state": entry.state,
                "ids": entry.ids,
                "title": entry.title,
                "deps": _deps_for(entry),
                "evidence": (
                    {"kind": evidence[0], "value": evidence[1]} if evidence else None
                ),
            }
        )
    summary = {
        "entries": len(result["entries"]),
        "states": result["counts"],
        "errors": len(result["errors"]),
        "warnings": len(result["warnings"]),
    }
    return {
        "summary": summary,
        "errors": result["errors"],
        "warnings": result["warnings"],
        "entries": entries,
    }


def _deps_for(entry):
    match = DEPS_RE.search(
        "- [%s] %s — %s" % (entry.state, "/".join(entry.ids), entry.title)
    )
    if not match:
        return []
    deps = []
    for chunk in match.group(1).split(","):
        deps.extend(split_ids(chunk))
    return deps


def _summary_line(result):
    counts = result["counts"]
    return (
        "jira-check: %d entries, %d TODO/%d DOING/%d DONE/%d PARK"
        % (
            len(result["entries"]),
            counts["TODO"],
            counts["DOING"],
            counts["DONE"],
            counts["PARK"],
        )
    )


def report(result):
    lines = [_summary_line(result)]
    for error in result["errors"]:
        lines.append("ERROR line %d: %s" % (error["line"], error["message"]))
    for warning in result["warnings"]:
        lines.append("WARNING line %d: %s" % (warning["line"], warning["message"]))
    if result["errors"]:
        lines.append(
            "jira-check: %d error(s), %d warning(s)"
            % (len(result["errors"]), len(result["warnings"]))
        )
    else:
        lines.append("jira-check: OK (%d warning(s))" % len(result["warnings"]))
    return "\n".join(lines)


def check_file(path, as_json=False):
    with open(path, "r", encoding="utf-8") as handle:
        text = handle.read()
    result = analyze(text)
    if as_json:
        print(json.dumps(_json_result(result), indent=2, sort_keys=True))
    else:
        print(report(result))
    return 1 if result["errors"] else 0


# --------------------------------------------------------------------------
# Self-check: synthetic fixtures in a temporary directory.
# --------------------------------------------------------------------------


def _fixture(root, name, text):
    path = os.path.join(root, name)
    with open(path, "w", encoding="utf-8") as handle:
        handle.write(text)
    return path


def _rules(result):
    return {error["rule"] for error in result["errors"]}


def self_check():
    checks = []

    def expect(name, condition):
        checks.append((name, bool(condition)))

    with tempfile.TemporaryDirectory(prefix="jira-check-") as tmp:
        path = _fixture(
            tmp,
            "duplicate.md",
            "- [TODO] QA-001 (tools) — first\n"
            "- [DONE] QA-001 (tools) — second\n"
            "  - landed `deadbeef`\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        expect("duplicate ID", "duplicate-id" in _rules(result))

        path = _fixture(
            tmp,
            "combined.md",
            "- [DONE] QA-002/QA-003 (emulator) — combined\n"
            "  - landed `deadbeef`\n"
            "- [TODO] QA-003 (emulator) — collides\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        dup = [e for e in result["errors"] if e["rule"] == "duplicate-id"]
        expect("combined-ID collision", dup and dup[0]["lines"] == [1, 3])

        path = _fixture(
            tmp,
            "missing-dep.md",
            "- [TODO] QA-010 (tools) — needs work  [deps: QA-999]\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        expect("missing dependency", "missing-dependency" in _rules(result))

        path = _fixture(
            tmp,
            "self-dep.md",
            "- [TODO] QA-011 (tools) — loops  [deps: QA-011]\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        expect("self dependency", "self-dependency" in _rules(result))

        path = _fixture(
            tmp,
            "done-no-evidence.md",
            "- [DONE] QA-012 (tools) — prose only\n"
            "  - everything works and the suite is green\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        expect("DONE without evidence", "done-without-evidence" in _rules(result))

        path = _fixture(
            tmp,
            "doing-no-dev.md",
            "- [DOING] QA-013 (tools) — unclaimed\n"
            "  - in progress\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        expect("DOING without @dev", "doing-without-dev" in _rules(result))

        path = _fixture(
            tmp,
            "valid.md",
            "# backlog\n\n"
            "- [TODO] QA-020 (tools) — open item  [deps: QA-021]\n"
            "- [DOING @dev7] QA-021 (tools) — claimed\n"
            "  - working on `tools/pm/check_jira.py`\n"
            "- [DONE] QA-022 (tools) — landed\n"
            "  - commit `deadbeef` in `docs/roadmap.md`\n"
            "- [PARK] QA-023 (emulator) — waiting\n"
            "  - blocked on the human playtest\n",
        )
        with open(path, encoding="utf-8") as handle:
            result = analyze(handle.read())
        expect("valid file passes", not result["errors"])
        expect("valid file has no warnings", not result["warnings"])

    failed = [name for name, ok in checks if not ok]
    if failed:
        print("jira-check self-check: FAIL (%s)" % ", ".join(failed))
        return 1
    print("jira-check self-check: PASS (%d checks)" % len(checks))
    return 0


def main(argv=None):
    root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    parser = argparse.ArgumentParser(description="Validate the jira.md backlog.")
    parser.add_argument("--jira", default=os.path.join(root, "jira.md"))
    parser.add_argument("--json", action="store_true", help="machine-readable output")
    parser.add_argument("--check", action="store_true", help="validate (default)")
    parser.add_argument("--self-check", action="store_true", help="run synthetic fixtures")
    args = parser.parse_args(argv)

    if args.self_check:
        return self_check()
    if not os.path.isfile(args.jira):
        print("jira-check: ERROR: backlog not found: %s" % os.path.basename(args.jira))
        return 1
    return check_file(args.jira, as_json=args.json)


if __name__ == "__main__":
    sys.exit(main())
