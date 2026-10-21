#!/usr/bin/env python3
"""Generate and validate the Sector Null content ID registry.

``hack/content/ids.yaml`` is the source of truth for D-009: every new room,
door, sprite/enemy, event, text block, music track and saved field has an ID
before use.  This tool validates that file and renders two committed artifacts:

    hack/include/hack/ids.h     C enums with CATEGORY_NAME constants
    docs/content-tracker.md     human-readable allocation tables

Usage::

    python3 tools/content/gen_ids.py --check
    python3 tools/content/gen_ids.py --write
    python3 tools/content/gen_ids.py --self-check

The generator is deterministic: no timestamps, no absolute paths and no ROM
addresses.  It is standard-library Python only; the YAML reader below is a
small subset parser for the registry schema (mappings, sequences, quoted
scalars, decimal/hex integers, booleans and ``[]``), not a general YAML parser.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_IDS = REPO_ROOT / "hack/content/ids.yaml"
DEFAULT_HEADER = REPO_ROOT / "hack/include/hack/ids.h"
DEFAULT_TRACKER = REPO_ROOT / "docs/content-tracker.md"

SCHEMA_VERSION = 1

# Canonical declaration order.  It is also the output order, so the generated
# header/tracker and the source YAML stay byte-stable.
CATEGORY_ORDER = (
    "rooms",
    "doors",
    "sprites",
    "events",
    "text",
    "music",
    "save_fields",
)

# Optional entry keys that reference another registry entry.
REF_KEYS = {
    "room": "rooms",
    "door": "doors",
    "event": "events",
    "text": "text",
    "sprite": "sprites",
}

STATUSES = ("active", "reserved", "vanilla", "deprecated")
SPRITE_KINDS = ("primary", "secondary")

CATEGORY_KEYS = {
    "name",
    "prefix",
    "min_id",
    "max_id",
    "radix",
    "note",
    "reserved_note",
    "reserved",
    "entries",
}
ENTRY_KEYS = {
    "name",
    "id",
    "note",
    "status",
    "owner",
    "area",
    "kind",
    "link",
} | set(REF_KEYS)
RESERVED_KEYS = {"start", "end", "note"}

NAME_RE = re.compile(r"^[a-z][a-z0-9_]*$")
PREFIX_RE = re.compile(r"^[A-Z][A-Z0-9_]*$")
AREA_RE = re.compile(r"^AREA_[A-Z0-9_]+$")
INT_RE = re.compile(r"^-?(?:0[xX][0-9A-Fa-f]+|[0-9]+)$")


class ContentIdError(Exception):
    """A registry validation, generation or self-check failure."""


# ---------------------------------------------------------------------------
# Minimal deterministic YAML reader
# ---------------------------------------------------------------------------


@dataclass
class _Line:
    number: int
    indent: int
    text: str


def _strip_comment(raw: str) -> str:
    in_single = False
    in_double = False
    escaped = False
    for index, char in enumerate(raw):
        if escaped:
            escaped = False
            continue
        if char == "\\" and in_double:
            escaped = True
            continue
        if char == "'" and not in_double:
            in_single = not in_single
            continue
        if char == '"' and not in_single:
            in_double = not in_double
            continue
        if char == "#" and not in_single and not in_double:
            if index == 0 or raw[index - 1].isspace():
                return raw[:index]
    return raw


def _split_key(text: str) -> tuple[str, str] | None:
    in_single = False
    in_double = False
    escaped = False
    for index, char in enumerate(text):
        if escaped:
            escaped = False
            continue
        if char == "\\" and in_double:
            escaped = True
            continue
        if char == "'" and not in_double:
            in_single = not in_single
            continue
        if char == '"' and not in_single:
            in_double = not in_double
            continue
        if char == ":" and not in_single and not in_double:
            if index + 1 == len(text) or text[index + 1].isspace():
                return text[:index].strip(), text[index + 1 :].strip()
    return None


def _parse_scalar(text: str, line: _Line) -> Any:
    if text == "[]":
        return []
    if text == "{}":
        return {}
    if text.startswith('"'):
        try:
            return json.loads(text)
        except json.JSONDecodeError as exc:
            raise ContentIdError(f"{line.number}: invalid double-quoted string: {exc}") from exc
    if text.startswith("'"):
        if len(text) < 2 or not text.endswith("'"):
            raise ContentIdError(f"{line.number}: unterminated single-quoted string")
        return text[1:-1].replace("''", "'")
    if text in ("true", "false"):
        return text == "true"
    if text in ("null", "~"):
        return None
    if INT_RE.match(text):
        if text.lower().startswith("0x") or text.lower().startswith("-0x"):
            return int(text, 16)
        return int(text, 10)
    if text.startswith("[") or text.startswith("{") or text.startswith("|"):
        raise ContentIdError(f"{line.number}: unsupported YAML construct {text!r}")
    return text


class _YamlReader:
    def __init__(self, text: str) -> None:
        self.lines: list[_Line] = []
        for number, raw in enumerate(text.splitlines(), 1):
            if "\t" in raw:
                raise ContentIdError(f"{number}: tabs are not allowed for indentation")
            stripped = _strip_comment(raw).rstrip()
            if not stripped.strip():
                continue
            indent = len(stripped) - len(stripped.lstrip(" "))
            self.lines.append(_Line(number, indent, stripped.strip()))
        self.pos = 0

    def peek(self) -> _Line | None:
        if self.pos >= len(self.lines):
            return None
        return self.lines[self.pos]

    def parse(self) -> Any:
        if not self.lines:
            raise ContentIdError("empty YAML document")
        if self.lines[0].indent != 0:
            raise ContentIdError(f"{self.lines[0].number}: top-level content must not be indented")
        value = self._parse_block(0)
        if self.pos != len(self.lines):
            line = self.lines[self.pos]
            raise ContentIdError(f"{line.number}: unexpected content {line.text!r}")
        return value

    def _parse_block(self, indent: int) -> Any:
        line = self.peek()
        if line is None:
            raise ContentIdError("unexpected end of YAML document")
        if line.indent != indent:
            raise ContentIdError(
                f"{line.number}: expected indent {indent}, found {line.indent}"
            )
        if line.text.startswith("- "):
            return self._parse_sequence(indent)
        return self._parse_mapping(indent)

    def _parse_mapping(self, indent: int, initial: dict[str, Any] | None = None) -> dict[str, Any]:
        result: dict[str, Any] = dict(initial or {})
        while True:
            line = self.peek()
            if line is None or line.indent < indent:
                return result
            if line.indent > indent:
                raise ContentIdError(f"{line.number}: unexpected indentation")
            if line.text.startswith("- "):
                return result
            split = _split_key(line.text)
            if split is None:
                raise ContentIdError(f"{line.number}: expected 'key: value', found {line.text!r}")
            key, rest = split
            if not key:
                raise ContentIdError(f"{line.number}: empty key")
            if key in result:
                raise ContentIdError(f"{line.number}: duplicate key {key!r}")
            self.pos += 1
            if rest:
                value = _parse_scalar(rest, line)
            else:
                nxt = self.peek()
                if nxt is not None and nxt.indent > indent:
                    value = self._parse_block(nxt.indent)
                else:
                    value = None
            result[key] = value

    def _parse_sequence(self, indent: int) -> list[Any]:
        result: list[Any] = []
        while True:
            line = self.peek()
            if line is None or line.indent < indent:
                return result
            if line.indent > indent:
                raise ContentIdError(f"{line.number}: unexpected indentation")
            if not line.text.startswith("- "):
                return result
            content = line.text[2:].strip()
            self.pos += 1
            if not content:
                nxt = self.peek()
                if nxt is None or nxt.indent <= indent:
                    result.append(None)
                else:
                    result.append(self._parse_block(nxt.indent))
                continue

            split = _split_key(content)
            if split is None:
                result.append(_parse_scalar(content, line))
                continue

            # Sequence item that starts a mapping: "- name: value", with the
            # remaining keys indented two spaces past the dash.
            key, rest = split
            item: dict[str, Any] = {}
            item_indent = indent + 2
            if rest:
                item[key] = _parse_scalar(rest, line)
            else:
                nxt = self.peek()
                if nxt is not None and nxt.indent > item_indent:
                    item[key] = self._parse_block(nxt.indent)
                else:
                    item[key] = None
            nxt = self.peek()
            if nxt is not None and nxt.indent > indent:
                if nxt.indent != item_indent:
                    raise ContentIdError(
                        f"{nxt.number}: expected indent {item_indent} for mapping item, "
                        f"found {nxt.indent}"
                    )
                item = self._parse_mapping(item_indent, initial=item)
            result.append(item)


def parse_yaml(text: str) -> Any:
    return _YamlReader(text).parse()


# ---------------------------------------------------------------------------
# Registry model and validation
# ---------------------------------------------------------------------------


@dataclass
class ReservedRange:
    start: int
    end: int
    note: str

    @property
    def label(self) -> str:
        return f"0x{self.start:X}..0x{self.end:X}"


@dataclass
class Entry:
    category: str
    name: str
    id: int
    note: str
    status: str
    owner: str | None
    fields: dict[str, Any] = field(default_factory=dict)

    @property
    def constant(self) -> str:
        prefix = self.fields["_prefix"]
        return f"{prefix}_{self.name.upper()}"


@dataclass
class Category:
    name: str
    prefix: str
    min_id: int
    max_id: int
    radix: str
    note: str
    reserved_note: str
    entries: list[Entry]
    reserved: list[ReservedRange]


@dataclass
class Registry:
    schema_version: int
    areas: list[str]
    categories: list[Category]

    @property
    def entry_count(self) -> int:
        return sum(len(category.entries) for category in self.categories)

    def category(self, name: str) -> Category:
        for category in self.categories:
            if category.name == name:
                return category
        raise KeyError(name)


def _ctx(*parts: Any) -> str:
    return ".".join(str(part) for part in parts)


def _check_mapping(value: Any, allowed: set[str], required: set[str], ctx: str) -> dict[str, Any]:
    if not isinstance(value, dict):
        raise ContentIdError(f"{ctx}: expected a mapping")
    unknown = sorted(set(value) - allowed)
    if unknown:
        raise ContentIdError(f"{ctx}: unknown key(s): {', '.join(unknown)}")
    missing = sorted(required - set(value))
    if missing:
        raise ContentIdError(f"{ctx}: missing key(s): {', '.join(missing)}")
    return value


def _get_int(value: Any, ctx: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int):
        raise ContentIdError(f"{ctx}: expected an integer, found {value!r}")
    return value


def _get_str(value: Any, ctx: str, *, required: bool = True) -> str:
    if value is None:
        if required:
            raise ContentIdError(f"{ctx}: expected a non-empty string")
        return ""
    if not isinstance(value, str) or not value.strip():
        raise ContentIdError(f"{ctx}: expected a non-empty string")
    return value.strip()


def _check_canonical_order(entries: list[Entry], ctx: str) -> None:
    expected = sorted(entries, key=lambda entry: (entry.id, entry.name))
    for actual, wanted in zip(entries, expected):
        if actual is not wanted:
            raise ContentIdError(
                f"{ctx}: entries must be sorted by (id, name); "
                f"expected {wanted.name!r} before {actual.name!r}"
            )


def validate_registry(document: Any) -> Registry:
    document = _check_mapping(
        document,
        {"schema_version", "areas", "categories"},
        {"schema_version", "areas", "categories"},
        "document",
    )

    schema_version = _get_int(document["schema_version"], "schema_version")
    if schema_version != SCHEMA_VERSION:
        raise ContentIdError(
            f"schema_version: expected {SCHEMA_VERSION}, found {schema_version}"
        )

    areas_raw = document["areas"]
    if not isinstance(areas_raw, list) or not areas_raw:
        raise ContentIdError("areas: expected a non-empty sequence")
    areas: list[str] = []
    for index, raw in enumerate(areas_raw):
        area = _get_str(raw, _ctx("areas", index))
        if not AREA_RE.match(area):
            raise ContentIdError(f"{_ctx('areas', index)}: invalid area name {area!r}")
        if area in areas:
            raise ContentIdError(f"{_ctx('areas', index)}: duplicate area {area!r}")
        areas.append(area)

    categories_raw = document["categories"]
    if not isinstance(categories_raw, list) or not categories_raw:
        raise ContentIdError("categories: expected a non-empty sequence")

    categories: list[Category] = []
    seen_categories: set[str] = set()
    for index, raw in enumerate(categories_raw):
        ctx = _ctx("categories", index)
        raw = _check_mapping(
            raw,
            CATEGORY_KEYS,
            {"name", "prefix", "min_id", "max_id", "radix", "entries"},
            ctx,
        )
        name = _get_str(raw["name"], f"{ctx}.name")
        if name not in CATEGORY_ORDER:
            raise ContentIdError(
                f"{ctx}.name: unknown category {name!r}; expected one of "
                + ", ".join(CATEGORY_ORDER)
            )
        if name in seen_categories:
            raise ContentIdError(f"{ctx}.name: duplicate category {name!r}")
        seen_categories.add(name)

        prefix = _get_str(raw["prefix"], f"{ctx}.prefix")
        if not PREFIX_RE.match(prefix):
            raise ContentIdError(f"{ctx}.prefix: invalid C prefix {prefix!r}")

        min_id = _get_int(raw["min_id"], f"{ctx}.min_id")
        max_id = _get_int(raw["max_id"], f"{ctx}.max_id")
        if not (0 <= min_id <= max_id <= 0xFFFF):
            raise ContentIdError(
                f"{ctx}: id range must satisfy 0 <= min_id <= max_id <= 0xFFFF"
            )

        radix = _get_str(raw["radix"], f"{ctx}.radix")
        if radix not in ("decimal", "hex"):
            raise ContentIdError(f"{ctx}.radix: expected 'decimal' or 'hex'")
        note = _get_str(raw.get("note"), f"{ctx}.note", required=False)
        reserved_note = _get_str(
            raw.get("reserved_note"), f"{ctx}.reserved_note", required=False
        )

        entries_raw = raw["entries"]
        if not isinstance(entries_raw, list):
            raise ContentIdError(f"{ctx}.entries: expected a sequence")

        entries: list[Entry] = []
        seen_names: set[str] = set()
        seen_ids: dict[int, str] = {}
        for entry_index, entry_raw in enumerate(entries_raw):
            entry_ctx = _ctx(ctx, "entries", entry_index)
            entry_raw = _check_mapping(
                entry_raw,
                ENTRY_KEYS,
                {"name", "id", "note"},
                entry_ctx,
            )
            entry_name = _get_str(entry_raw["name"], f"{entry_ctx}.name")
            if not NAME_RE.match(entry_name):
                raise ContentIdError(
                    f"{entry_ctx}.name: expected lowercase snake_case, found {entry_name!r}"
                )
            if entry_name == "reserved":
                raise ContentIdError(
                    f"{entry_ctx}.name: 'reserved' is the generated placeholder suffix"
                )
            if entry_name in seen_names:
                raise ContentIdError(
                    f"{entry_ctx}.name: duplicate entry name {entry_name!r}"
                )
            seen_names.add(entry_name)

            entry_id = _get_int(entry_raw["id"], f"{entry_ctx}.id")
            if not (min_id <= entry_id <= max_id):
                raise ContentIdError(
                    f"{entry_ctx}.id: {entry_id} is outside [{min_id}, {max_id}]"
                )
            if entry_id in seen_ids:
                raise ContentIdError(
                    f"{entry_ctx}.id: duplicate id {entry_id} "
                    f"(also used by {seen_ids[entry_id]!r})"
                )
            seen_ids[entry_id] = entry_name

            entry_note = _get_str(entry_raw["note"], f"{entry_ctx}.note")
            status = _get_str(
                entry_raw.get("status", "active"), f"{entry_ctx}.status"
            )
            if status not in STATUSES:
                raise ContentIdError(
                    f"{entry_ctx}.status: expected one of {', '.join(STATUSES)}"
                )
            owner = _get_str(
                entry_raw.get("owner"), f"{entry_ctx}.owner", required=False
            )

            fields: dict[str, Any] = {"_prefix": prefix}
            if "area" in entry_raw:
                area = _get_str(entry_raw["area"], f"{entry_ctx}.area")
                if area not in areas:
                    raise ContentIdError(
                        f"{entry_ctx}.area: unknown area {area!r}; add it to areas first"
                    )
                fields["area"] = area
            if "area" in entry_raw:
                if name not in ("rooms", "text"):
                    raise ContentIdError(
                        f"{entry_ctx}.area: only room and text entries may "
                        "declare an area"
                    )
            elif name == "rooms":
                raise ContentIdError(f"{entry_ctx}: room entries require 'area'")

            if "kind" in entry_raw:
                kind = _get_str(entry_raw["kind"], f"{entry_ctx}.kind")
                if name != "sprites":
                    raise ContentIdError(
                        f"{entry_ctx}.kind: only sprite entries may declare a kind"
                    )
                if kind not in SPRITE_KINDS:
                    raise ContentIdError(
                        f"{entry_ctx}.kind: expected one of {', '.join(SPRITE_KINDS)}"
                    )
                fields["kind"] = kind
            elif name == "sprites":
                raise ContentIdError(f"{entry_ctx}: sprite entries require 'kind'")

            if "link" in entry_raw:
                if name != "doors":
                    raise ContentIdError(
                        f"{entry_ctx}.link: only door entries may declare a link"
                    )
                fields["link"] = _get_str(entry_raw["link"], f"{entry_ctx}.link")
            elif name == "doors":
                raise ContentIdError(f"{entry_ctx}: door entries require 'link'")

            for key in REF_KEYS:
                if key in entry_raw:
                    fields[key] = _get_str(entry_raw[key], f"{entry_ctx}.{key}")

            entries.append(
                Entry(
                    category=name,
                    name=entry_name,
                    id=entry_id,
                    note=entry_note,
                    status=status,
                    owner=owner or None,
                    fields=fields,
                )
            )

        reserved_raw = raw.get("reserved", [])
        if not isinstance(reserved_raw, list):
            raise ContentIdError(f"{ctx}.reserved: expected a sequence")
        reserved: list[ReservedRange] = []
        for range_index, range_raw in enumerate(reserved_raw):
            range_ctx = _ctx(ctx, "reserved", range_index)
            range_raw = _check_mapping(
                range_raw, RESERVED_KEYS, {"start", "end", "note"}, range_ctx
            )
            start = _get_int(range_raw["start"], f"{range_ctx}.start")
            end = _get_int(range_raw["end"], f"{range_ctx}.end")
            if not (min_id <= start <= end <= max_id):
                raise ContentIdError(
                    f"{range_ctx}: range must satisfy min_id <= start <= end <= max_id"
                )
            reserved.append(
                ReservedRange(
                    start=start,
                    end=end,
                    note=_get_str(range_raw["note"], f"{range_ctx}.note"),
                )
            )

        if reserved != sorted(reserved, key=lambda item: (item.start, item.end)):
            raise ContentIdError(f"{ctx}.reserved: ranges must be sorted by start")
        for previous, current in zip(reserved, reserved[1:]):
            if current.start <= previous.end:
                raise ContentIdError(
                    f"{ctx}.reserved: ranges {previous.label} and {current.label} overlap"
                )

        for entry in entries:
            for reserved_range in reserved:
                if reserved_range.start <= entry.id <= reserved_range.end:
                    raise ContentIdError(
                        f"{ctx}: entry {entry.name!r} id {entry.id} falls inside "
                        f"reserved range {reserved_range.label}"
                    )

        if not entries and not reserved_note:
            raise ContentIdError(
                f"{ctx}: category has no entries; declare reserved_note with the "
                "reason no ID is safe to allocate"
            )

        _check_canonical_order(entries, ctx)
        categories.append(
            Category(
                name=name,
                prefix=prefix,
                min_id=min_id,
                max_id=max_id,
                radix=radix,
                note=note,
                reserved_note=reserved_note,
                entries=entries,
                reserved=reserved,
            )
        )

    present = [category.name for category in categories]
    missing = [name for name in CATEGORY_ORDER if name not in present]
    if missing:
        raise ContentIdError(f"categories: missing required category {missing[0]!r}")
    if present != list(CATEGORY_ORDER):
        raise ContentIdError(
            "categories: expected canonical order " + ", ".join(CATEGORY_ORDER)
        )

    prefixes = [category.prefix for category in categories]
    if len(set(prefixes)) != len(prefixes):
        raise ContentIdError("categories: prefix values must be unique")

    registry = Registry(
        schema_version=schema_version,
        areas=areas,
        categories=categories,
    )

    constants: dict[str, str] = {}
    names: dict[str, set[str]] = {category.name: set() for category in categories}
    for category in categories:
        for entry in category.entries:
            if entry.constant in constants:
                raise ContentIdError(
                    f"{category.name}.{entry.name}: C constant {entry.constant} "
                    f"collides with {constants[entry.constant]}"
                )
            constants[entry.constant] = f"{category.name}.{entry.name}"
            names[category.name].add(entry.name)

    for category in categories:
        for entry in category.entries:
            for key, target_category in REF_KEYS.items():
                if key not in entry.fields:
                    continue
                target = entry.fields[key]
                if target not in names[target_category]:
                    raise ContentIdError(
                        f"{category.name}.{entry.name}.{key}: unknown "
                        f"{target_category} entry {target!r}"
                    )
            if category.name == "doors":
                link = entry.fields["link"]
                if link == entry.name:
                    raise ContentIdError(
                        f"doors.{entry.name}.link: door must not link to itself"
                    )
                if link not in names["doors"]:
                    raise ContentIdError(
                        f"doors.{entry.name}.link: unknown door {link!r}"
                    )
                target = next(
                    other for other in category.entries if other.name == link
                )
                if target.fields["link"] != entry.name:
                    raise ContentIdError(
                        f"doors.{entry.name}.link: {link!r} does not link back"
                    )

    return registry


def load_registry(path: Path) -> Registry:
    if not path.is_file():
        raise ContentIdError(f"{_display_path(path)}: missing source file")
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise ContentIdError(f"{_display_path(path)}: {exc}") from exc
    try:
        document = parse_yaml(text)
    except ContentIdError as exc:
        raise ContentIdError(f"{_display_path(path)}: {exc}") from exc
    return validate_registry(document)


# ---------------------------------------------------------------------------
# Rendering
# ---------------------------------------------------------------------------


def _format_id(value: int, radix: str) -> str:
    if radix == "hex":
        return f"0x{value:X}"
    return str(value)


def _c_comment(text: str) -> str:
    text = " ".join(text.split())
    return text.replace("/*", "/ *").replace("*/", "* /")


def _md_cell(text: str) -> str:
    return " ".join(text.split()).replace("|", "\\|")


def _camel(prefix: str) -> str:
    return "".join(part.capitalize() for part in prefix.split("_"))


def _entry_comment(entry: Entry) -> str:
    parts: list[str] = []
    fields = entry.fields
    if "area" in fields:
        parts.append(fields["area"])
    if "kind" in fields:
        parts.append(fields["kind"])
    if "room" in fields:
        parts.append(f"room {fields['room']}")
    if entry.owner:
        parts.append(entry.owner)
    parts.append(entry.status)
    parts.append(entry.note)
    return _c_comment("; ".join(parts))


def _owner_area(entry: Entry) -> str:
    parts: list[str] = []
    if entry.owner:
        parts.append(f"`{entry.owner}`")
    fields = entry.fields
    if "area" in fields:
        parts.append(f"`{fields['area']}`")
    if "kind" in fields:
        parts.append(fields["kind"])
    if "room" in fields:
        parts.append(f"room `{fields['room']}`")
    return " / ".join(parts) if parts else "—"


def render_header(registry: Registry) -> str:
    lines = [
        "/*",
        " * Generated by tools/content/gen_ids.py --write.  Do not hand-edit.",
        " * Source: hack/content/ids.yaml (schema_version "
        + str(registry.schema_version)
        + ").",
        " *",
        " * Each category is a separate engine namespace.  Use these constants",
        " * instead of numeric IDs in content code (D-009).",
        " */",
        "#ifndef HACK_IDS_H",
        "#define HACK_IDS_H",
        "",
        f"#define HACK_IDS_SCHEMA_VERSION {registry.schema_version}",
        "",
    ]

    for category in registry.categories:
        type_name = f"Hack{_camel(category.prefix)}Id"
        title = category.name.replace("_", " ")
        if category.entries:
            lines.append(f"/* {title}: {_c_comment(category.note)} */")
            lines.append(f"typedef enum {type_name} {{")
            for entry in category.entries:
                value = _format_id(entry.id, category.radix)
                lines.append(
                    f"    {entry.constant} = {value}, /* {_entry_comment(entry)} */"
                )
            lines.append(f"}} {type_name};")
        else:
            lines.append(
                f"/* {title}: no IDs assigned in schema {registry.schema_version}. */"
            )
            lines.append(f"/* Reserved: {_c_comment(category.reserved_note)} */")
            lines.append(f"typedef enum {type_name} {{")
            lines.append(
                f"    {category.prefix}_RESERVED = -1, "
                "/* placeholder only; not a valid content ID */"
            )
            lines.append(f"}} {type_name};")
        if category.reserved:
            for reserved in category.reserved:
                lines.append(
                    f"/* {title} reserved {reserved.label}: {_c_comment(reserved.note)} */"
                )
        lines.append("")

    lines.append("#endif /* HACK_IDS_H */")
    return "\n".join(lines) + "\n"


def render_tracker(registry: Registry) -> str:
    counts = ", ".join(
        f"{category.name.replace('_', ' ')} {len(category.entries)}"
        for category in registry.categories
    )
    lines = [
        "<!-- Generated by tools/content/gen_ids.py --write. Do not hand-edit. -->",
        "# Content ID tracker",
        "",
        f"Schema version: **{registry.schema_version}**.  "
        "Source: `hack/content/ids.yaml`.",
        "",
        "Generated files: `hack/include/hack/ids.h` (C constants) and this "
        "tracker.  Edit the YAML and run `--write`; never hand-edit either "
        "generated file.",
        "",
        f"Allocated IDs: **{registry.entry_count}** ({counts}).",
        "",
    ]

    for category in registry.categories:
        title = category.name.replace("_", " ").title()
        lines.append(f"## {title}")
        lines.append("")
        if category.note:
            lines.append(_md_cell(category.note))
            lines.append("")

        if category.entries:
            lines.append("| Constant | ID | Owner / Area | Status | Notes |")
            lines.append("| --- | --- | --- | --- | --- |")
            for entry in category.entries:
                lines.append(
                    f"| `{entry.constant}` | `{_format_id(entry.id, category.radix)}` "
                    f"| {_owner_area(entry)} | {entry.status} | "
                    f"{_md_cell(entry.note)} |"
                )
        else:
            lines.append(
                f"No IDs assigned in schema {registry.schema_version}.  "
                f"Reserved: {_md_cell(category.reserved_note)}"
            )
        lines.append("")

        if category.reserved:
            lines.append("Reserved ranges:")
            lines.append("")
            lines.append("| Range | Notes |")
            lines.append("| --- | --- |")
            for reserved in category.reserved:
                lines.append(
                    f"| `{_format_id(reserved.start, category.radix)}`.."
                    f"`{_format_id(reserved.end, category.radix)}` | "
                    f"{_md_cell(reserved.note)} |"
                )
            lines.append("")

    return "\n".join(lines).rstrip() + "\n"


# ---------------------------------------------------------------------------
# Write / check
# ---------------------------------------------------------------------------


def _display_path(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _write_bytes(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)


def write_outputs(registry: Registry, header: Path, tracker: Path) -> None:
    _write_bytes(header, render_header(registry).encode("utf-8"))
    _write_bytes(tracker, render_tracker(registry).encode("utf-8"))


def verify_outputs(registry: Registry, header: Path, tracker: Path) -> list[str]:
    problems: list[str] = []
    expected = (
        (header, render_header(registry)),
        (tracker, render_tracker(registry)),
    )
    for path, text in expected:
        display = _display_path(path)
        if not path.is_file():
            problems.append(f"{display}: missing (run --write)")
            continue
        try:
            actual = path.read_bytes()
        except OSError as exc:
            problems.append(f"{display}: {exc}")
            continue
        if actual != text.encode("utf-8"):
            problems.append(f"{display}: stale (run --write)")
    return problems


def run_check(ids_path: Path, header: Path, tracker: Path) -> Registry:
    registry = load_registry(ids_path)
    problems = verify_outputs(registry, header, tracker)
    if problems:
        raise ContentIdError("\n".join(problems))
    return registry


def run_write(ids_path: Path, header: Path, tracker: Path) -> Registry:
    registry = load_registry(ids_path)
    write_outputs(registry, header, tracker)
    return registry


# ---------------------------------------------------------------------------
# Self-check
# ---------------------------------------------------------------------------


FIXTURE_YAML = """\
schema_version: 1

areas:
  - AREA_TEST_1

categories:
  - name: rooms
    prefix: ROOM
    min_id: 0
    max_id: 255
    radix: decimal
    note: "fixture rooms"
    entries:
      - name: test_room
        id: 0
        area: AREA_TEST_1
        owner: FIXTURE
        status: active
        note: "fixture room"

  - name: doors
    prefix: DOOR
    min_id: 0
    max_id: 255
    radix: decimal
    note: "fixture doors"
    entries:
      - name: test_door_a
        id: 0
        room: test_room
        link: test_door_b
        owner: FIXTURE
        status: active
        note: "fixture door a"
      - name: test_door_b
        id: 1
        room: test_room
        link: test_door_a
        owner: FIXTURE
        status: active
        note: "fixture door b"

  - name: sprites
    prefix: SPRITE
    min_id: 0
    max_id: 255
    radix: hex
    note: "fixture sprites"
    entries:
      - name: test_sprite
        id: 0x10
        kind: primary
        owner: FIXTURE
        status: active
        note: "fixture sprite"

  - name: events
    prefix: EVENT
    min_id: 0
    max_id: 255
    radix: hex
    note: "fixture events"
    reserved:
      - start: 0x20
        end: 0x2F
        note: "fixture reserved block"
    entries:
      - name: test_event
        id: 0x10
        room: test_room
        sprite: test_sprite
        text: test_text
        owner: FIXTURE
        status: active
        note: "fixture event"

  - name: text
    prefix: TEXT
    min_id: 0
    max_id: 65535
    radix: hex
    note: "fixture text"
    entries:
      - name: test_text
        id: 0x100
        event: test_event
        door: test_door_a
        owner: FIXTURE
        status: active
        note: "fixture text"

  - name: music
    prefix: MUSIC
    min_id: 0
    max_id: 255
    radix: hex
    note: "fixture music"
    reserved_note: "fixture music IDs are reserved"
    entries: []

  - name: save_fields
    prefix: SAVE_FIELD
    min_id: 0
    max_id: 4607
    radix: hex
    note: "fixture save fields"
    reserved_note: "fixture save-field IDs are reserved"
    entries: []
"""


def _replace_once(text: str, old: str, new: str) -> str:
    count = text.count(old)
    if count != 1:
        raise ContentIdError(
            f"self-check fixture mutation expected one match, found {count}"
        )
    return text.replace(old, new)


def _expect_error(
    name: str,
    yaml_text: str,
    needle: str,
    root: Path,
) -> None:
    path = root / f"{name}.yaml"
    path.write_text(yaml_text, encoding="utf-8")
    try:
        load_registry(path)
    except ContentIdError as exc:
        message = str(exc)
        if needle not in message:
            raise ContentIdError(
                f"self-check {name!r}: expected error containing {needle!r}, "
                f"got {message!r}"
            ) from exc
        return
    raise ContentIdError(f"self-check {name!r}: expected a validation error")


def _self_check() -> int:
    cases = 0
    with tempfile.TemporaryDirectory(prefix="gen_ids_selfcheck_") as temp_dir:
        root = Path(temp_dir)
        source = root / "ids.yaml"
        header = root / "ids.h"
        tracker = root / "tracker.md"
        source.write_text(FIXTURE_YAML, encoding="utf-8")

        registry = load_registry(source)
        if registry.entry_count != 6:
            raise ContentIdError(
                f"self-check known-good: expected 6 entries, found {registry.entry_count}"
            )
        cases += 1

        first_header = render_header(registry)
        first_tracker = render_tracker(registry)
        second = load_registry(source)
        if first_header != render_header(second) or first_tracker != render_tracker(second):
            raise ContentIdError("self-check determinism: renders differ between runs")
        cases += 1

        write_outputs(registry, header, tracker)
        if verify_outputs(registry, header, tracker):
            raise ContentIdError("self-check known-good: generated files are not current")
        cases += 1

        first_bytes = (header.read_bytes(), tracker.read_bytes())
        write_outputs(registry, header, tracker)
        if (header.read_bytes(), tracker.read_bytes()) != first_bytes:
            raise ContentIdError("self-check determinism: --write is not byte-stable")
        cases += 1

        # Stale output must be rejected, and --write must repair it.
        header.write_bytes(header.read_bytes() + b"\n")
        problems = verify_outputs(registry, header, tracker)
        if not any("stale" in problem for problem in problems):
            raise ContentIdError(
                f"self-check stale-output: expected a stale error, got {problems!r}"
            )
        write_outputs(registry, header, tracker)
        if verify_outputs(registry, header, tracker):
            raise ContentIdError("self-check stale-output: --write did not repair output")
        cases += 1

        mutations = [
            (
                "duplicate-id",
                _replace_once(
                    FIXTURE_YAML,
                    "      - name: test_door_b\n        id: 1\n",
                    "      - name: test_door_b\n        id: 0\n",
                ),
                "duplicate id 0",
            ),
            (
                "out-of-range",
                _replace_once(
                    FIXTURE_YAML,
                    "        id: 0\n        area: AREA_TEST_1\n",
                    "        id: 256\n        area: AREA_TEST_1\n",
                ),
                "outside [0, 255]",
            ),
            (
                "unknown-category",
                _replace_once(FIXTURE_YAML, "  - name: music\n", "  - name: tracks\n"),
                "unknown category 'tracks'",
            ),
            (
                "duplicate-name",
                _replace_once(
                    FIXTURE_YAML,
                    "      - name: test_door_b\n",
                    "      - name: test_door_a\n",
                ),
                "duplicate entry name 'test_door_a'",
            ),
            (
                "bad-reciprocal-link",
                _replace_once(
                    FIXTURE_YAML,
                    "        link: test_door_a\n",
                    "        link: test_door_b\n",
                ),
                "does not link back",
            ),
            (
                "unknown-room-ref",
                _replace_once(
                    FIXTURE_YAML,
                    "        room: test_room\n        link: test_door_b\n",
                    "        room: missing_room\n        link: test_door_b\n",
                ),
                "unknown rooms entry 'missing_room'",
            ),
            (
                "entry-in-reserved-range",
                _replace_once(
                    FIXTURE_YAML,
                    "        id: 0x10\n        room: test_room\n        sprite: test_sprite\n",
                    "        id: 0x20\n        room: test_room\n        sprite: test_sprite\n",
                ),
                "falls inside reserved range 0x20..0x2F",
            ),
            (
                "overlapping-reserved-ranges",
                _replace_once(
                    FIXTURE_YAML,
                    '        note: "fixture reserved block"\n',
                    '        note: "fixture reserved block"\n'
                    "      - start: 0x28\n"
                    "        end: 0x3F\n"
                    '        note: "fixture overlapping block"\n',
                ),
                "overlap",
            ),
            (
                "empty-category-without-reserved-note",
                _replace_once(
                    FIXTURE_YAML,
                    '    reserved_note: "fixture music IDs are reserved"\n',
                    "",
                ),
                "declare reserved_note",
            ),
            (
                "unsorted-entries",
                _replace_once(
                    FIXTURE_YAML,
                    "      - name: test_door_a\n        id: 0\n",
                    "      - name: test_door_a\n        id: 5\n",
                ),
                "sorted by (id, name)",
            ),
            (
                "invalid-status",
                _replace_once(
                    FIXTURE_YAML,
                    '        status: active\n        note: "fixture room"\n',
                    '        status: maybe\n        note: "fixture room"\n',
                ),
                "status: expected one of",
            ),
            (
                "unknown-entry-key",
                _replace_once(
                    FIXTURE_YAML,
                    '        note: "fixture room"\n',
                    '        foo: bar\n        note: "fixture room"\n',
                ),
                "unknown key(s): foo",
            ),
            (
                "bad-schema-version",
                _replace_once(FIXTURE_YAML, "schema_version: 1\n", "schema_version: 2\n"),
                "schema_version: expected 1",
            ),
        ]

        for name, mutated, needle in mutations:
            _expect_error(name, mutated, needle, root)
            cases += 1

    print(f"gen_ids self-check: PASS ({cases} cases)")
    return 0


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Generate and validate the Sector Null content ID registry."
    )
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument(
        "--check",
        action="store_true",
        help="validate ids.yaml and fail if generated files are stale",
    )
    group.add_argument(
        "--write",
        action="store_true",
        help="regenerate ids.h and docs/content-tracker.md from ids.yaml",
    )
    group.add_argument(
        "--self-check",
        action="store_true",
        help="run the built-in known-good and invalid-input checks",
    )
    parser.add_argument(
        "--ids",
        type=Path,
        default=DEFAULT_IDS,
        help=f"registry source (default: {_display_path(DEFAULT_IDS)})",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER,
        help=f"generated C header (default: {_display_path(DEFAULT_HEADER)})",
    )
    parser.add_argument(
        "--tracker",
        type=Path,
        default=DEFAULT_TRACKER,
        help=f"generated Markdown tracker (default: {_display_path(DEFAULT_TRACKER)})",
    )
    args = parser.parse_args(argv)

    try:
        if args.self_check:
            return _self_check()
        if args.write:
            registry = run_write(args.ids, args.header, args.tracker)
            print(
                f"gen_ids: wrote {_display_path(args.header)} and "
                f"{_display_path(args.tracker)} "
                f"({registry.entry_count} IDs, {len(registry.categories)} categories)"
            )
            return 0

        registry = run_check(args.ids, args.header, args.tracker)
        print(
            f"gen_ids: PASS ({registry.entry_count} IDs, "
            f"{len(registry.categories)} categories; generated files current)"
        )
        return 0
    except ContentIdError as exc:
        print(f"gen_ids: FAIL: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
