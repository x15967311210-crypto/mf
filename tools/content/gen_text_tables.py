#!/usr/bin/env python3
"""Generate the HACK=1 per-area message-banner text tables.

``hack/content/text/messages.json`` is the source of truth for hack-owned
message-banner text.  It maps an allocated ``TEXT_*`` registry ID to one
``INCTEXT`` block in a content source file and to the in-area ``message_id``
that the message-banner sprite passes to ``TextDrawMessageBanner``.

This tool validates that mapping and emits ``hack/gen/text_tables.h``:

* one ``static const u16 HackText<Id>[]`` per message, holding the exact words
  that ``tools/preproc`` produces from the committed ``INCTEXT`` literal;
* ``HACK_<AREA>_TEXT_COUNT`` (22: the banner clamps message ids at 21);
* one ``static const u16* const HackArea<Area>Text[22]`` per area with
  designated initialisers, so unused slots stay ``NULL``.

``src/text.c`` includes the tracked shim ``hack/include/hack/text_tables.h``
(and therefore this ignored generated header) only under ``#ifdef HACK``.  It
uses the table only when ``gCurrentArea`` matches and the slot is non-NULL;
otherwise the original vanilla ``sMessageTextPointers`` index math runs
unchanged.  ``TextDisplayMessage`` (event/ability messages) is not touched.

The generator never invents a charmap encoder: source words come from
``tools/content/text_roundtrip.py``, which runs the real ``tools/preproc`` and
decodes the result back through ``charmap.txt``.  Registry IDs come from
``tools/content/gen_ids.py``, the same parser that generates
``hack/include/hack/ids.h``.

Usage::

    python3 tools/content/gen_text_tables.py --write
    python3 tools/content/gen_text_tables.py --check
    python3 tools/content/gen_text_tables.py --self-check

Standard-library Python only, deterministic, no timestamps, no absolute paths
and no ROM addresses.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Callable, Sequence

TOOLS_DIR = Path(__file__).resolve().parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

import gen_ids  # noqa: E402  (same directory, shared registry parser)
import text_roundtrip  # noqa: E402  (same directory, shared preproc path)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_MESSAGES = REPO_ROOT / "hack/content/text/messages.json"
DEFAULT_TEXT_DIR = REPO_ROOT / "hack/content/text"
DEFAULT_IDS = REPO_ROOT / "hack/content/ids.yaml"
DEFAULT_AREA_HEADER = REPO_ROOT / "include/constants/connection.h"
DEFAULT_PREPROC = text_roundtrip.DEFAULT_PREPROC
DEFAULT_CHARMAP = text_roundtrip.DEFAULT_CHARMAP
DEFAULT_OUT = "hack/gen/text_tables.h"

SCHEMA = "mf-hack.text-messages/v1"
# TextDrawMessageBanner clamps messageId to 21, so the table has 22 slots.
MESSAGE_BANNER_MAX_ID = 21
MESSAGE_BANNER_TEXT_COUNT = MESSAGE_BANNER_MAX_ID + 1

TEXT_ID_RE = re.compile(r"^TEXT_[A-Z0-9_]+$")
AREA_RE = re.compile(r"^AREA_[A-Z0-9_]+$")
SOURCE_RE = re.compile(r"^[A-Za-z0-9_.-]+(?:/[A-Za-z0-9_.-]+)*$")
AREA_ENUM_RE = re.compile(r"enum\s+Area\s*\{(?P<body>.*?)\};", re.S)
AREA_NAME_RE = re.compile(r"\bAREA_[A-Z0-9_]+\b")

MAPPING_KEYS = {"schema", "areas"}
AREA_KEYS = {"area", "messages"}
MESSAGE_KEYS = {"text_id", "message_id", "source", "literal"}


class TextTableError(Exception):
    """A messages.json, registry, source, preproc or generated-file failure."""


# ---------------------------------------------------------------------------
# Strict input loading
# ---------------------------------------------------------------------------


def display_path(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _reject_duplicate_keys(pairs: list[tuple[str, Any]]) -> dict[str, Any]:
    result: dict[str, Any] = {}
    for key, value in pairs:
        if key in result:
            raise TextTableError(f"duplicate JSON key {key!r}")
        result[key] = value
    return result


def load_json(path: Path, label: str) -> Any:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise TextTableError(f"{display_path(path)}: {exc}") from exc
    try:
        return json.loads(text, object_pairs_hook=_reject_duplicate_keys)
    except json.JSONDecodeError as exc:
        raise TextTableError(f"{label}: invalid JSON: {exc}") from exc


def require_mapping(
    value: Any, allowed: set[str], required: set[str], ctx: str
) -> dict[str, Any]:
    if not isinstance(value, dict):
        raise TextTableError(f"{ctx}: expected an object")
    unknown = sorted(set(value) - allowed)
    if unknown:
        raise TextTableError(f"{ctx}: unknown key(s): {', '.join(unknown)}")
    missing = sorted(required - set(value))
    if missing:
        raise TextTableError(f"{ctx}: missing key(s): {', '.join(missing)}")
    return value


def require_int(value: Any, ctx: str, minimum: int, maximum: int) -> int:
    if isinstance(value, bool) or not isinstance(value, int):
        raise TextTableError(f"{ctx}: expected an integer, found {value!r}")
    if not minimum <= value <= maximum:
        raise TextTableError(f"{ctx}: {value} is outside {minimum}..{maximum}")
    return value


def require_str(value: Any, ctx: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise TextTableError(f"{ctx}: expected a non-empty string")
    return value.strip()


@dataclass
class Message:
    text_id: str
    message_id: int
    source: str
    literal: int
    words: tuple[int, ...] = ()


@dataclass
class AreaTable:
    name: str
    messages: list[Message]


def load_messages(path: Path) -> list[AreaTable]:
    document = require_mapping(
        load_json(path, "messages.json"), MAPPING_KEYS, MAPPING_KEYS, "messages"
    )
    schema = require_str(document["schema"], "schema")
    if schema != SCHEMA:
        raise TextTableError(f"schema: expected {SCHEMA!r}, found {schema!r}")

    raw_areas = document["areas"]
    if not isinstance(raw_areas, list) or not raw_areas:
        raise TextTableError("areas: expected a non-empty list")

    areas: list[AreaTable] = []
    seen_areas: set[str] = set()
    seen_text_ids: dict[str, str] = {}
    seen_symbols: dict[str, str] = {}
    for area_index, raw_area in enumerate(raw_areas):
        ctx = f"areas.{area_index}"
        raw_area = require_mapping(raw_area, AREA_KEYS, AREA_KEYS, ctx)
        area_name = require_str(raw_area["area"], f"{ctx}.area")
        if not AREA_RE.match(area_name):
            raise TextTableError(f"{ctx}.area: invalid area name {area_name!r}")
        if area_name in seen_areas:
            raise TextTableError(f"{ctx}.area: duplicate area {area_name!r}")
        seen_areas.add(area_name)

        raw_messages = raw_area["messages"]
        if not isinstance(raw_messages, list) or not raw_messages:
            raise TextTableError(f"{ctx}.messages: expected a non-empty list")

        messages: list[Message] = []
        seen_message_ids: dict[int, str] = {}
        for message_index, raw_message in enumerate(raw_messages):
            message_ctx = f"{ctx}.messages.{message_index}"
            raw_message = require_mapping(
                raw_message, MESSAGE_KEYS, MESSAGE_KEYS, message_ctx
            )
            text_id = require_str(raw_message["text_id"], f"{message_ctx}.text_id")
            if not TEXT_ID_RE.match(text_id):
                raise TextTableError(
                    f"{message_ctx}.text_id: invalid TEXT_* constant {text_id!r}"
                )
            if text_id in seen_text_ids:
                raise TextTableError(
                    f"{message_ctx}.text_id: duplicate text id {text_id!r} "
                    f"(also used by {seen_text_ids[text_id]})"
                )
            seen_text_ids[text_id] = message_ctx

            symbol = text_symbol(text_id)
            if symbol in seen_symbols:
                raise TextTableError(
                    f"{message_ctx}.text_id: C symbol {symbol} collides with "
                    f"{seen_symbols[symbol]}"
                )
            seen_symbols[symbol] = message_ctx

            message_id = require_int(
                raw_message["message_id"],
                f"{message_ctx}.message_id",
                0,
                MESSAGE_BANNER_MAX_ID,
            )
            if message_id in seen_message_ids:
                raise TextTableError(
                    f"{message_ctx}.message_id: duplicate message_id {message_id} "
                    f"in {area_name} (also used by {seen_message_ids[message_id]})"
                )
            seen_message_ids[message_id] = message_ctx

            source = require_str(raw_message["source"], f"{message_ctx}.source")
            if (
                source.startswith("/")
                or "\\" in source
                or not SOURCE_RE.match(source)
                or any(part in ("", ".", "..") for part in source.split("/"))
            ):
                raise TextTableError(
                    f"{message_ctx}.source: {source!r} must be a relative path "
                    "inside the text content directory"
                )

            literal = require_int(
                raw_message["literal"],
                f"{message_ctx}.literal",
                0,
                0x7FFFFFFF,
            )
            messages.append(Message(text_id, message_id, source, literal))

        messages.sort(key=lambda message: (message.message_id, message.text_id))
        areas.append(AreaTable(area_name, messages))

    areas.sort(key=lambda area: area.name)
    return areas


def load_area_names(path: Path) -> set[str]:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise TextTableError(f"{display_path(path)}: {exc}") from exc
    match = AREA_ENUM_RE.search(text)
    if match is None:
        raise TextTableError(
            f"{display_path(path)}: cannot find the Area enum declaration"
        )
    names = set(AREA_NAME_RE.findall(match.group("body")))
    if not names:
        raise TextTableError(f"{display_path(path)}: Area enum declares no AREA_*")
    return names


def text_ids(ids_path: Path) -> dict[str, gen_ids.Entry]:
    try:
        registry = gen_ids.load_registry(ids_path)
        category = registry.category("text")
    except gen_ids.ContentIdError as exc:
        raise TextTableError(f"{display_path(ids_path)}: {exc}") from exc
    except KeyError as exc:
        raise TextTableError(f"{display_path(ids_path)}: no text category") from exc
    return {entry.constant: entry for entry in category.entries}


def resolve_source(text_dir: Path, source: str, ctx: str) -> Path:
    root = text_dir.resolve()
    path = (root / source).resolve()
    try:
        path.relative_to(root)
    except ValueError:
        raise TextTableError(
            f"{ctx}: source {source!r} escapes {display_path(text_dir)}"
        ) from None
    if not path.is_file():
        raise TextTableError(
            f"{ctx}: missing source {display_path(path)}"
        )
    return path


# ---------------------------------------------------------------------------
# C names
# ---------------------------------------------------------------------------


def _camel(parts: Sequence[str]) -> str:
    return "".join(part.capitalize() for part in parts)


def text_symbol(value: str) -> str:
    return "HackText" + _camel(value[len("TEXT_") :].split("_"))


def area_symbol(value: str) -> str:
    return "HackArea" + _camel(value[len("AREA_") :].split("_")) + "Text"


def area_count_macro(value: str) -> str:
    return f"HACK_{value}_TEXT_COUNT"


# ---------------------------------------------------------------------------
# Build
# ---------------------------------------------------------------------------


def build_tables(
    messages_path: Path,
    text_dir: Path,
    ids_path: Path,
    area_header: Path,
    preproc_path: Path,
    charmap_path: Path,
) -> list[AreaTable]:
    areas = load_messages(messages_path)
    known_areas = load_area_names(area_header)
    registry = text_ids(ids_path)

    for area in areas:
        if area.name not in known_areas:
            raise TextTableError(
                f"areas: unknown area {area.name!r}; not declared in "
                f"{display_path(area_header)}"
            )
        for message in area.messages:
            if message.text_id not in registry:
                raise TextTableError(
                    f"{message.text_id}: is not in the text registry "
                    f"({display_path(ids_path)})"
                )
            entry = registry[message.text_id]
            if "area" in entry.fields and entry.fields["area"] != area.name:
                raise TextTableError(
                    f"{message.text_id}: registry area {entry.fields['area']} "
                    f"does not match messages.json area {area.name}"
                )

    try:
        preproc = text_roundtrip.ensure_preproc(preproc_path)
        charmap = text_roundtrip.load_charmap(charmap_path)
    except text_roundtrip.RoundtripError as exc:
        raise TextTableError(str(exc)) from exc

    cache: dict[Path, list[list[int]]] = {}
    for area in areas:
        for message in area.messages:
            ctx = f"{area.name} {message.text_id}"
            path = resolve_source(text_dir, message.source, ctx)
            if path not in cache:
                try:
                    results = text_roundtrip.check_file(
                        path, preproc, charmap_path, charmap
                    )
                except text_roundtrip.RoundtripError as exc:
                    raise TextTableError(f"{ctx}: {exc}") from exc
                cache[path] = [list(result["words"]) for result in results]
            blocks = cache[path]
            if message.literal >= len(blocks):
                raise TextTableError(
                    f"{ctx}: literal {message.literal} is out of range; "
                    f"{display_path(path)} has {len(blocks)} INCTEXT block(s)"
                )
            message.words = tuple(blocks[message.literal])
    return areas


def render_header(areas: Sequence[AreaTable]) -> str:
    lines = [
        "/*",
        " * Generated by tools/content/gen_text_tables.py --write.  Do not hand-edit.",
        f" * Source: hack/content/text/messages.json (schema {SCHEMA}).",
        " *",
        " * One u16 text block per TEXT_* ID plus a per-area message-id pointer",
        " * list.  The message-banner sprite passes its roomSlot (the spawn record",
        " * index, see SpriteInitPrimary) as the message id, so each list is",
        " * indexed by message_id 0..21.",
        " */",
        "#ifndef HACK_GEN_TEXT_TABLES_H",
        "#define HACK_GEN_TEXT_TABLES_H",
        "",
        '#include "types.h"',
        "",
    ]

    for area in areas:
        for message in area.messages:
            lines.append(
                f"/* {message.text_id}: {area.name} message_id "
                f"{message.message_id}, {message.source} literal "
                f"{message.literal}. */"
            )
            lines.append(f"static const u16 {text_symbol(message.text_id)}[] = {{")
            words = list(message.words)
            for start in range(0, len(words), 8):
                chunk = " ".join(
                    f"0x{word:04X}," for word in words[start : start + 8]
                )
                lines.append(f"    {chunk}")
            lines.append("};")
            lines.append("")

    for area in areas:
        count = area_count_macro(area.name)
        lines.append(f"#define {count} {MESSAGE_BANNER_TEXT_COUNT}")
        lines.append(
            f"static const u16* const {area_symbol(area.name)}[{count}] = {{"
        )
        for message in area.messages:
            lines.append(
                f"    [{message.message_id}] = {text_symbol(message.text_id)},"
            )
        lines.append("};")
        lines.append("")

    lines.append("#endif /* HACK_GEN_TEXT_TABLES_H */")
    return "\n".join(lines) + "\n"


def build_header(
    messages_path: Path = DEFAULT_MESSAGES,
    text_dir: Path = DEFAULT_TEXT_DIR,
    ids_path: Path = DEFAULT_IDS,
    area_header: Path = DEFAULT_AREA_HEADER,
    preproc_path: Path = DEFAULT_PREPROC,
    charmap_path: Path = DEFAULT_CHARMAP,
) -> str:
    return render_header(
        build_tables(
            messages_path,
            text_dir,
            ids_path,
            area_header,
            preproc_path,
            charmap_path,
        )
    )


# ---------------------------------------------------------------------------
# Write/check
# ---------------------------------------------------------------------------


def write_header(path: Path, content: str) -> bool:
    try:
        if path.exists() and path.read_text(encoding="utf-8") == content:
            return False
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8")
    except OSError as exc:
        raise TextTableError(f"cannot write {display_path(path)}: {exc}") from exc
    return True


def check_header(path: Path, content: str) -> None:
    if not path.is_file():
        raise TextTableError(
            f"{display_path(path)} is missing; run "
            "`make content-tables` (or `make hack-build`)"
        )
    try:
        actual = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise TextTableError(f"cannot read {display_path(path)}: {exc}") from exc
    if actual != content:
        raise TextTableError(
            f"{display_path(path)} is stale; run `make content-tables`"
        )


# ---------------------------------------------------------------------------
# Self-check
# ---------------------------------------------------------------------------


FIXTURE_IDS = """\
schema_version: 1

areas:
  - AREA_TEST_1

categories:
  - name: rooms
    prefix: ROOM
    min_id: 0
    max_id: 255
    radix: decimal
    reserved_note: "fixture rooms are reserved"
    entries: []
  - name: doors
    prefix: DOOR
    min_id: 0
    max_id: 255
    radix: decimal
    reserved_note: "fixture doors are reserved"
    entries: []
  - name: sprites
    prefix: SPRITE
    min_id: 0
    max_id: 255
    radix: hex
    reserved_note: "fixture sprites are reserved"
    entries: []
  - name: events
    prefix: EVENT
    min_id: 0
    max_id: 255
    radix: hex
    reserved_note: "fixture events are reserved"
    entries: []
  - name: text
    prefix: TEXT
    min_id: 0
    max_id: 65535
    radix: hex
    note: "fixture text"
    entries:
      - name: entry_ledge_signal
        id: 0x0000
        area: AREA_TEST_1
        owner: FIXTURE
        status: active
        note: "fixture first message"
      - name: second_signal
        id: 0x0001
        area: AREA_TEST_1
        owner: FIXTURE
        status: active
        note: "fixture second message"
  - name: music
    prefix: MUSIC
    min_id: 0
    max_id: 255
    radix: hex
    reserved_note: "fixture music is reserved"
    entries: []
  - name: save_fields
    prefix: SAVE_FIELD
    min_id: 0
    max_id: 4607
    radix: hex
    reserved_note: "fixture save fields are reserved"
    entries: []
"""

FIXTURE_TEXT = """\
/* fixture text source */
#include "constants/text.h"

static const u16 sFirst[] = INCTEXT("HELLO");
static const u16 sSecond[] = INCTEXT("WORLD{NEW_LINE}AGAIN");
"""


def _fixture_messages() -> dict[str, Any]:
    return {
        "schema": SCHEMA,
        "areas": [
            {
                "area": "AREA_TEST_1",
                "messages": [
                    {
                        "text_id": "TEXT_ENTRY_LEDGE_SIGNAL",
                        "message_id": 5,
                        "source": "fixture_text.c",
                        "literal": 0,
                    },
                    {
                        "text_id": "TEXT_SECOND_SIGNAL",
                        "message_id": 12,
                        "source": "fixture_text.c",
                        "literal": 1,
                    },
                ],
            }
        ],
    }


def _write_json(path: Path, value: Any) -> None:
    path.write_text(
        json.dumps(value, sort_keys=True, indent=2) + "\n", encoding="utf-8"
    )


def _expect_error(callback: Callable[[], Any], needle: str) -> None:
    try:
        callback()
    except TextTableError as exc:
        if needle not in str(exc):
            raise TextTableError(
                f"self-check: expected error containing {needle!r}, got {exc}"
            ) from exc
        return
    raise TextTableError(f"self-check: expected an error containing {needle!r}")


def self_check() -> None:
    import tempfile

    with tempfile.TemporaryDirectory(prefix="mf-text-tables-") as temp:
        root = Path(temp)
        text_dir = root / "text"
        text_dir.mkdir()
        (text_dir / "fixture_text.c").write_text(FIXTURE_TEXT, encoding="utf-8")
        ids_path = root / "ids.yaml"
        ids_path.write_text(FIXTURE_IDS, encoding="utf-8")
        messages_path = root / "messages.json"
        _write_json(messages_path, _fixture_messages())
        out = root / "text_tables.h"

        def build() -> str:
            return build_header(
                messages_path=messages_path,
                text_dir=text_dir,
                ids_path=ids_path,
            )

        # Deterministic known-good output.
        first = build()
        second = build()
        if first != second:
            raise TextTableError("self-check: generation is not deterministic")
        for needle in (
            "static const u16 HackTextEntryLedgeSignal[] = {",
            "static const u16 HackTextSecondSignal[] = {",
            "#define HACK_AREA_TEST_1_TEXT_COUNT 22",
            "static const u16* const HackAreaTest1Text[HACK_AREA_TEST_1_TEXT_COUNT] = {",
            "[5] = HackTextEntryLedgeSignal,",
            "[12] = HackTextSecondSignal,",
            "0xFF00,",
        ):
            if needle not in first:
                raise TextTableError(
                    f"self-check: generated header lacks {needle!r}"
                )
        if str(root) in first:
            raise TextTableError("self-check: generated header contains a temp path")
        if re.search(r"0x08[0-9A-Fa-f]{6}", first):
            raise TextTableError("self-check: generated header contains a ROM address")

        # write/check/byte-stability.
        if not write_header(out, first):
            raise TextTableError("self-check: --write did not write a missing header")
        check_header(out, first)
        if write_header(out, first):
            raise TextTableError("self-check: --write rewrote an identical header")
        if out.read_text(encoding="utf-8") != first:
            raise TextTableError("self-check: written header does not match build")

        # Stale and missing headers must fail.
        out.write_text(first + "\n", encoding="utf-8")
        _expect_error(lambda: check_header(out, first), "stale")
        write_header(out, first)
        out.unlink()
        _expect_error(lambda: check_header(out, first), "missing")
        write_header(out, first)

        # Negative messages.json cases.  Each mutation writes the source file
        # and rebuilds from scratch.
        def negative(mutate: Callable[[dict[str, Any]], None], needle: str) -> None:
            document = _fixture_messages()
            mutate(document)
            _write_json(messages_path, document)
            _expect_error(build, needle)

        def first_message(document: dict[str, Any]) -> dict[str, Any]:
            return document["areas"][0]["messages"][0]

        negative(
            lambda document: first_message(document).update(
                {"text_id": "TEXT_MISSING"}
            ),
            "is not in the text registry",
        )
        negative(
            lambda document: document["areas"][0]["messages"][1].update(
                {"message_id": 5}
            ),
            "duplicate message_id 5",
        )
        negative(
            lambda document: first_message(document).update({"message_id": 22}),
            "outside 0..21",
        )
        negative(
            lambda document: first_message(document).update(
                {"source": "missing.c"}
            ),
            "missing source",
        )
        negative(
            lambda document: first_message(document).update({"literal": 9}),
            "literal 9 is out of range",
        )
        negative(
            lambda document: first_message(document).update(
                {"source": "../fixture_text.c"}
            ),
            "must be a relative path",
        )
        negative(
            lambda document: document["areas"][0].update(
                {"area": "AREA_TEST_9"}
            ),
            "unknown area",
        )
        negative(
            lambda document: document["areas"][0]["messages"][1].update(
                {"text_id": "TEXT_ENTRY_LEDGE_SIGNAL"}
            ),
            "duplicate text id",
        )
        negative(
            lambda document: document.update({"schema": "mf-hack.text/v0"}),
            "schema: expected",
        )
        negative(
            lambda document: document["areas"][0]["messages"][0].update(
                {"extra": 1}
            ),
            "unknown key(s): extra",
        )

    print("TEXT-TABLES: PASS (self-check)")


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Generate the HACK=1 per-area message-banner text table "
            "(hack/gen/text_tables.h)."
        )
    )
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--write", action="store_true", help="write the header")
    mode.add_argument("--check", action="store_true", help="fail if it is stale")
    mode.add_argument("--self-check", action="store_true", help="run the tool suite")
    parser.add_argument(
        "--messages",
        type=Path,
        default=DEFAULT_MESSAGES,
        help=f"message mapping (default: {display_path(DEFAULT_MESSAGES)})",
    )
    parser.add_argument(
        "--text-dir",
        type=Path,
        default=DEFAULT_TEXT_DIR,
        help=f"root for message sources (default: {display_path(DEFAULT_TEXT_DIR)})",
    )
    parser.add_argument(
        "--ids",
        type=Path,
        default=DEFAULT_IDS,
        help=f"ID registry source (default: {display_path(DEFAULT_IDS)})",
    )
    parser.add_argument(
        "--area-header",
        type=Path,
        default=DEFAULT_AREA_HEADER,
        help=f"Area enum header (default: {display_path(DEFAULT_AREA_HEADER)})",
    )
    parser.add_argument(
        "--preproc",
        type=Path,
        default=DEFAULT_PREPROC,
        help=f"preproc binary (default: {display_path(DEFAULT_PREPROC)})",
    )
    parser.add_argument(
        "--charmap",
        type=Path,
        default=DEFAULT_CHARMAP,
        help=f"charmap (default: {display_path(DEFAULT_CHARMAP)})",
    )
    parser.add_argument(
        "--out",
        default=DEFAULT_OUT,
        help=f"generated header path (default: {DEFAULT_OUT})",
    )
    args = parser.parse_args(argv)

    try:
        if args.self_check:
            self_check()
            return 0

        content = build_header(
            messages_path=args.messages,
            text_dir=args.text_dir,
            ids_path=args.ids,
            area_header=args.area_header,
            preproc_path=args.preproc,
            charmap_path=args.charmap,
        )
        out = Path(args.out)
        if args.write:
            changed = write_header(out, content)
            state = "wrote" if changed else "unchanged"
            print(f"TEXT-TABLES: {state} {display_path(out)}")
            print("TEXT-TABLES: PASS")
        else:
            check_header(out, content)
            print(f"TEXT-TABLES: PASS ({display_path(out)} is fresh)")
        return 0
    except TextTableError as exc:
        print(f"TEXT-TABLES: FAIL: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
