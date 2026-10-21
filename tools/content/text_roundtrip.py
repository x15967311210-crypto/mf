#!/usr/bin/env python3
"""HACK-008b: charmap text round-trip through tools/preproc's C INCTEXT path.

The pipeline under test is the real one used by the ROM build:

    tools/preproc/preproc file.c charmap.txt

preproc rewrites each ``INCTEXT("...")`` into a u16 initializer such as
``{ 0x00C1, 0x00C2, CHAR_TERMINATOR }``.  This tool runs that binary on a
temporary C file, parses the emitted words and decodes them back through the
same charmap.  It never invents a second encoder and it needs no ROM or
emulator.

Exit status: 0 on success, 1 on a round-trip/self-check failure, 2 on usage.
"""

from __future__ import annotations

import argparse
import json
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Sequence, Tuple

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_CHARMAP = ROOT / "charmap.txt"
DEFAULT_PREPROC = ROOT / "tools/preproc/preproc"
GOLDEN_PATH = ROOT / "hack/content/text/golden_path.c"

CHAR_TERMINATOR = 0xFF00
CHAR_WIDTH_MASK = 0x8000
CHAR_INDENT_MASK = 0x8300

# Control words emitted by the engine and recognised by the decoder.  preproc
# only prints CHAR_TERMINATOR symbolically; the rest are plain words today.
SYMBOL_WORDS = {
    "CHAR_TERMINATOR": CHAR_TERMINATOR,
    "CHAR_NEW_LINE": 0xFE00,
    "CHAR_NEW_PAGE": 0xFD00,
    "CHAR_NEXT_PAGE_ARROW": 0xFC00,
}
CONTROL_TOKENS = {
    0xFE00: "{NEW_LINE}",
    0xFD00: "{NEW_PAGE}",
    0xFC00: "{NEXT_PAGE_ARROW}",
}

INITIALIZER_RE = re.compile(r"=\s*\{(?P<body>[^{}]*)\}\s*;", re.S)
INCTEXT_RE = re.compile(
    r'INCTEXT\s*\((?P<args>(?:\s*"(?:\\.|[^"\\])*")+\s*)\)', re.S
)
WORD_RE = re.compile(r"0x[0-9A-Fa-f]{4}")
MAP_LINE_RE = re.compile(
    r"^(?:'(?P<char>(?:\\.|[^'])+)'|(?P<name>[A-Za-z_][A-Za-z0-9_]*))"
    r"\s*=\s*(?P<seq>[0-9A-Fa-f]{2}(?:\s+[0-9A-Fa-f]{2})*)\s*$"
)
BRACKET_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)(?:\((\d+)\))?$")


class RoundtripError(Exception):
    """A deterministic pipeline, charmap, parse or decode failure."""


@dataclass(frozen=True)
class Charmap:
    chars: Dict[int, int]  # Unicode code point -> engine word
    constants: Dict[str, int]  # charmap constant -> engine word
    by_word: Dict[int, str]  # engine word -> source character


def _strip_comment(line: str) -> str:
    """Drop an ``@`` comment, but not inside a charmap character literal."""
    out: List[str] = []
    in_quote = False
    escaped = False
    for ch in line:
        if in_quote:
            out.append(ch)
            if escaped:
                escaped = False
            elif ch == "\\":
                escaped = True
            elif ch == "'":
                in_quote = False
        else:
            if ch == "@":
                break
            out.append(ch)
            if ch == "'":
                in_quote = True
    return "".join(out)


def _unescape_char(text: str) -> str:
    if text == "\\'":
        return "'"
    if text == "\\\\":
        return "\\"
    if text.startswith("\\"):
        raise RoundtripError("unsupported charmap character escape %r" % text)
    if len(text) != 1:
        raise RoundtripError("charmap character literal must be one character")
    return text


def load_charmap(path: Path) -> Charmap:
    """Parse charmap.txt using the same byte-sequence rules as preproc.

    preproc turns a two-byte sequence ``HH LL`` into the word ``HH<<8 | LL``.
    A one-byte sequence is a high-byte-only word, which is why the character
    rows in charmap.txt use ``00 C1`` for 'A'.
    """
    chars: Dict[int, int] = {}
    constants: Dict[str, int] = {}
    by_word: Dict[int, str] = {}

    try:
        lines = path.read_text(encoding="utf-8").splitlines()
    except OSError as exc:
        raise RoundtripError("cannot read charmap %s: %s" % (path, exc))

    for lineno, raw in enumerate(lines, 1):
        line = _strip_comment(raw).strip()
        if not line:
            continue
        match = MAP_LINE_RE.match(line)
        if not match:
            raise RoundtripError(
                "%s:%d: malformed charmap line: %r" % (path, lineno, raw)
            )
        sequence = [int(pair, 16) for pair in match.group("seq").split()]
        if len(sequence) > 2:
            raise RoundtripError(
                "%s:%d: only one- and two-byte mappings are supported"
                % (path, lineno)
            )
        word = sequence[0] << 8
        if len(sequence) == 2:
            word |= sequence[1]

        if match.group("char") is not None:
            ch = _unescape_char(match.group("char"))
            code = ord(ch)
            if code in chars:
                raise RoundtripError(
                    "%s:%d: redefining char %r" % (path, lineno, ch)
                )
            if word in by_word:
                raise RoundtripError(
                    "%s:%d: word 0x%04X is already mapped to %r"
                    % (path, lineno, word, by_word[word])
                )
            chars[code] = word
            by_word[word] = ch
        else:
            name = match.group("name")
            if name in constants:
                raise RoundtripError(
                    "%s:%d: redefining constant %s" % (path, lineno, name)
                )
            constants[name] = word

    if not chars:
        raise RoundtripError("%s: no character mappings" % path)
    for required in ("NEW_LINE", "TERMINATOR", "WIDTH", "INDENT"):
        if required not in constants:
            raise RoundtripError(
                "%s: missing required constant %s" % (path, required)
            )
    return Charmap(chars=chars, constants=constants, by_word=by_word)


def ensure_preproc(path: Path) -> Path:
    """Return an executable preproc, building tools/preproc when absent."""
    if path.is_file() and path.stat().st_mode & 0o111:
        return path
    make = shutil.which("make")
    if make is None:
        raise RoundtripError(
            "%s is missing and make is not available; build tools/preproc first"
            % path
        )
    proc = subprocess.run(
        [make, "-C", str(path.parent)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if proc.returncode != 0 or not path.is_file():
        detail = (proc.stderr or proc.stdout).strip()
        raise RoundtripError(
            "failed to build %s (make exit %d)%s"
            % (path, proc.returncode, ": " + detail if detail else "")
        )
    return path


def run_preproc_file(
    source: Path, preproc: Path, charmap: Path
) -> str:
    proc = subprocess.run(
        [str(preproc), str(source), str(charmap)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if proc.returncode != 0:
        detail = (proc.stderr or proc.stdout).strip()
        raise RoundtripError(
            "preproc failed for %s (exit %d): %s"
            % (source.name, proc.returncode, detail)
        )
    return proc.stdout


def extract_initializers(output: str) -> List[List[int]]:
    bodies = [m.group("body") for m in INITIALIZER_RE.finditer(output)]
    if not bodies:
        raise RoundtripError("preproc output has no u16 initializer")
    return [parse_words(body) for body in bodies]


def parse_words(body: str) -> List[int]:
    """Parse the inside of ``{ 0x00C1, ..., CHAR_TERMINATOR }``."""
    text = body.strip()
    if not text:
        raise RoundtripError("empty initializer")
    words: List[int] = []
    for raw in text.split(","):
        token = raw.strip()
        if not token:
            raise RoundtripError("empty word in initializer (stray comma)")
        if WORD_RE.fullmatch(token):
            words.append(int(token, 16))
        elif token in SYMBOL_WORDS:
            words.append(SYMBOL_WORDS[token])
        else:
            raise RoundtripError("malformed output token %r" % token)
    return words


def decode_words(words: Sequence[int], charmap: Charmap) -> List[str]:
    """Decode engine words back to source tokens using the same charmap."""
    if not words:
        raise RoundtripError("text has no words")
    if words[-1] != CHAR_TERMINATOR:
        raise RoundtripError("text is missing trailing CHAR_TERMINATOR")
    if CHAR_TERMINATOR in words[:-1]:
        raise RoundtripError("CHAR_TERMINATOR appears before the end of text")

    tokens: List[str] = []
    for word in words[:-1]:
        if word in CONTROL_TOKENS:
            tokens.append(CONTROL_TOKENS[word])
        elif (word & 0xFF00) == CHAR_WIDTH_MASK:
            tokens.append("{WIDTH(%d)}" % (word & 0xFF))
        elif (word & 0xFF00) == CHAR_INDENT_MASK:
            tokens.append("{INDENT(%d)}" % (word & 0xFF))
        elif word in charmap.by_word:
            tokens.append(charmap.by_word[word])
        else:
            raise RoundtripError("unknown text word 0x%04X" % word)
    return tokens


def literal_to_content(literal: str) -> str:
    """Concatenate one or more adjacent C string literals into raw content."""
    pos = 0
    out: List[str] = []
    length = len(literal)
    while True:
        while pos < length and literal[pos].isspace():
            pos += 1
        if pos >= length:
            break
        if literal[pos] != '"':
            raise RoundtripError("expected a C string literal")
        pos += 1
        while pos < length and literal[pos] != '"':
            ch = literal[pos]
            if ch == "\\":
                pos += 1
                if pos >= length:
                    raise RoundtripError("unterminated C escape")
                escaped = literal[pos]
                if escaped in ('"', "\\"):
                    out.append(escaped)
                else:
                    raise RoundtripError(
                        "unsupported C escape \\%s" % escaped
                    )
            else:
                out.append(ch)
            pos += 1
        if pos >= length:
            raise RoundtripError("unterminated C string literal")
        pos += 1  # closing quote
    return "".join(out)


def tokenize_content(content: str) -> List[str]:
    """Turn raw literal content into canonical source tokens."""
    tokens: List[str] = []
    pos = 0
    while pos < len(content):
        ch = content[pos]
        if ch == "{":
            end = content.find("}", pos + 1)
            if end < 0:
                raise RoundtripError("unterminated {constant} in source text")
            inner = content[pos + 1 : end]
            match = BRACKET_RE.match(inner)
            if not match:
                raise RoundtripError("malformed {constant}: %r" % inner)
            name, number = match.group(1), match.group(2)
            if number is None:
                tokens.append("{%s}" % name)
            else:
                tokens.append("{%s(%d)}" % (name, int(number)))
            pos = end + 1
        elif ch == "}":
            raise RoundtripError("unexpected '}' in source text")
        else:
            tokens.append(ch)
            pos += 1
    return tokens


def roundtrip_literal(
    literal: str, preproc: Path, charmap_path: Path, charmap: Charmap
) -> Tuple[List[int], List[str]]:
    """Run the real preproc on one INCTEXT literal and decode the result."""
    expected = tokenize_content(literal_to_content(literal))
    temp_dir = Path(tempfile.mkdtemp(prefix="mf-text-roundtrip-"))
    source = temp_dir / "roundtrip.c"
    source.write_text(
        "/* text_roundtrip:begin */\n"
        "static const u16 sText[] = INCTEXT(%s);\n"
        "/* text_roundtrip:end */\n" % literal,
        encoding="utf-8",
    )
    try:
        output = run_preproc_file(source, preproc, charmap_path)
    finally:
        shutil.rmtree(temp_dir, ignore_errors=True)
    blocks = extract_initializers(output)
    if len(blocks) != 1:
        raise RoundtripError(
            "expected one initializer, preproc emitted %d" % len(blocks)
        )
    words = blocks[0]
    decoded = decode_words(words, charmap)
    if decoded != expected:
        raise RoundtripError(
            "round-trip mismatch\n  expected: %r\n  decoded:  %r"
            % ("".join(expected), "".join(decoded))
        )
    return words, decoded


def _source_literals(path: Path) -> List[str]:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise RoundtripError("cannot read %s: %s" % (path, exc))
    found = [m.group("args") for m in INCTEXT_RE.finditer(text)]
    if not found:
        raise RoundtripError("%s contains no INCTEXT call" % path)
    return found


def check_file(path: Path, preproc: Path, charmap_path: Path, charmap: Charmap):
    """Preprocess a committed content file and decode every INCTEXT block."""
    literals = _source_literals(path)
    output = run_preproc_file(path, preproc, charmap_path)
    blocks = extract_initializers(output)
    if len(blocks) != len(literals):
        raise RoundtripError(
            "%s: %d INCTEXT calls but %d initializers in preproc output"
            % (path, len(literals), len(blocks))
        )
    results = []
    for literal, words in zip(literals, blocks):
        expected = tokenize_content(literal_to_content(literal))
        decoded = decode_words(words, charmap)
        if decoded != expected:
            raise RoundtripError(
                "%s: round-trip mismatch\n  expected: %r\n  decoded:  %r"
                % (path, "".join(expected), "".join(decoded))
            )
        results.append({"words": words, "text": "".join(decoded)})
    return results


def _expect_failure(label: str, func, needle: str) -> None:
    try:
        func()
    except RoundtripError as exc:
        message = str(exc)
        if needle not in message:
            raise RoundtripError(
                "%s: failure was not the expected one (%r missing from %r)"
                % (label, needle, message)
            )
        return
    raise RoundtripError("%s: expected a failure, got success" % label)


def self_check(charmap_path: Path, preproc_path: Path) -> None:
    preproc = ensure_preproc(preproc_path)
    charmap = load_charmap(charmap_path)

    positives = [
        ('"AB A"', "AB A"),
        (
            '"ENTRY LEDGE{NEW_LINE}THE SIGNAL IS WEAK"',
            "ENTRY LEDGE{NEW_LINE}THE SIGNAL IS WEAK",
        ),
        ('"abc xyz"', "abc xyz"),
        (
            '"A{WIDTH(8)}B{INDENT(4)}C"',
            "A{WIDTH(8)}B{INDENT(4)}C",
        ),
        ('"HELLO " "WORLD{NEW_LINE}"', "HELLO WORLD{NEW_LINE}"),
    ]
    for literal, expected in positives:
        words, decoded = roundtrip_literal(
            literal, preproc, charmap_path, charmap
        )
        if "".join(decoded) != expected:
            raise RoundtripError(
                "%s: decoded %r, expected %r"
                % (literal, "".join(decoded), expected)
            )
        print(
            "PASS text-roundtrip: %-48s -> %2d words, terminator 0x%04X"
            % (literal, len(words), words[-1])
        )

    golden = check_file(GOLDEN_PATH, preproc, charmap_path, charmap)
    print(
        "PASS text-roundtrip: %s -> %r"
        % (GOLDEN_PATH.relative_to(ROOT), golden[0]["text"])
    )

    # Negative: unknown characters (including digits) must be preproc errors.
    _expect_failure(
        "unknown char '!'",
        lambda: roundtrip_literal('"AB!A"', preproc, charmap_path, charmap),
        "unknown character",
    )
    print("PASS text-roundtrip: unknown character '!' rejected by preproc")

    _expect_failure(
        "unproven digit '1'",
        lambda: roundtrip_literal('"LEVEL 1"', preproc, charmap_path, charmap),
        "unknown character",
    )
    print("PASS text-roundtrip: unproven digit rejected by preproc")

    # Negative: unknown {CONSTANT} must be a preproc error.
    _expect_failure(
        "unknown constant",
        lambda: roundtrip_literal('"A{NOPE}"', preproc, charmap_path, charmap),
        "unknown constant",
    )
    print("PASS text-roundtrip: unknown {constant} rejected by preproc")

    # Negative: malformed preproc-like output must be rejected by our parser.
    for bad in ("0xC100,", "0xZZZZ", "", "0x00C1, , 0xFF00"):
        _expect_failure(
            "malformed output %r" % bad,
            lambda body=bad: parse_words(body),
            "",
        )
    print("PASS text-roundtrip: malformed output tokens rejected")

    # Negative: decode must require exactly one trailing terminator.
    _expect_failure(
        "missing terminator",
        lambda: decode_words([0x00C1], charmap),
        "missing trailing CHAR_TERMINATOR",
    )
    _expect_failure(
        "mid-string terminator",
        lambda: decode_words(
            [0x00C1, CHAR_TERMINATOR, 0x00C2, CHAR_TERMINATOR], charmap
        ),
        "before the end",
    )
    _expect_failure(
        "unknown word",
        lambda: decode_words([0x1234, CHAR_TERMINATOR], charmap),
        "unknown text word",
    )
    print("PASS text-roundtrip: decode rejects bad word streams")

    print("PASS text_roundtrip self-check (%d positive cases)" % len(positives))


def main(argv: Sequence[str]) -> int:
    parser = argparse.ArgumentParser(
        description="Round-trip MF text through tools/preproc's INCTEXT path."
    )
    parser.add_argument(
        "--self-check",
        action="store_true",
        help="run positive, golden-file and negative cases; no ROM needed",
    )
    parser.add_argument(
        "--file",
        type=Path,
        help="preprocess a C file and decode its INCTEXT blocks",
    )
    parser.add_argument(
        "--text",
        help='raw text body without quotes, e.g. "AB A{NEW_LINE}"',
    )
    parser.add_argument(
        "--preproc",
        type=Path,
        default=DEFAULT_PREPROC,
        help="path to the preproc binary (default: tools/preproc/preproc)",
    )
    parser.add_argument(
        "--charmap",
        type=Path,
        default=DEFAULT_CHARMAP,
        help="path to charmap.txt (default: repository root charmap.txt)",
    )
    parser.add_argument(
        "--json",
        action="store_true",
        help="emit machine-readable JSON instead of the human summary",
    )
    args = parser.parse_args(argv)

    try:
        if args.self_check:
            self_check(args.charmap, args.preproc)
            return 0

        preproc = ensure_preproc(args.preproc)
        charmap = load_charmap(args.charmap)

        if args.file is not None:
            results = check_file(args.file, preproc, args.charmap, charmap)
            payload = {"file": str(args.file), "blocks": results}
        elif args.text is not None:
            if '"' in args.text or "\\" in args.text:
                raise RoundtripError(
                    '--text takes the body only; quotes and backslashes are not allowed'
                )
            words, decoded = roundtrip_literal(
                '"%s"' % args.text, preproc, args.charmap, charmap
            )
            payload = {"text": "".join(decoded), "words": words}
        else:
            parser.print_help(sys.stderr)
            return 2

        if args.json:
            print(json.dumps(payload, indent=2, sort_keys=True))
        elif "blocks" in payload:
            for block in payload["blocks"]:
                print(block["text"])
        else:
            print(payload["text"])
        return 0
    except RoundtripError as exc:
        print("FAIL text_roundtrip: %s" % exc, file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
