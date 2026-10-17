#!/usr/bin/env python3
"""Plan relocatable C expressions for hardcoded ROM literals.

The C sources write ROM addresses in the short seven-digit form
(``0x8017bd9`` is ``0x08017BD9``), so the old eight-digit asm regex missed
1034 references.  This tool scans ``src/**/*.c`` and ``include/**/*.h`` with
the same literal/comment/string rules as ``check_relocs.py``, resolves every
target through ``SymbolMap`` plus the baseline ELF, and plans a replacement:

    (Func_T)0x8017bd9              -> (Func_T)SaXElevator
    (MusicFunc_T)0x8004a3d         -> (MusicFunc_T)unk_4a3c
    (const u16*)0x85dfd6c          -> (const u16*)((u8*)&sIntro...+0x5C0)
    DMA3_COPY_16(0x83e799c, ...)   -> DMA3_COPY_16(&sMissileIconGfx, ...)

Only the literal token is replaced; the surrounding cast, macro arguments,
comments and whitespace are preserved byte-for-byte.

Resolution rules
----------------
* A literal is a function reference when the ELF symbol at the address (or at
  the address with the Thumb bit) is ``STT_FUNC``.  Function ELF values in the
  baseline already carry bit 0, and the planned symbol expression keeps that
  value exactly.
* Everything else is a data reference.  A global/weak symbol is referenced
  directly.  A static (``STB_LOCAL``) symbol is not link-visible from another
  object, so the same same-section global-anchor rule as ``apply_refs.py`` and
  ``gen_blob_tables.py`` applies: emit ``&global_anchor + byte_delta``.
* Data expressions use the address of the object (``&Symbol``).  This is
  correct for arrays and scalar objects alike; a bare array name would be
  wrong for scalar pointer variables such as ``sTitleScreenDebugTextPointer``.
* An unknown or unmapped target is an error.  The tool never guesses.

SHIFT-005c is planning-only: run it with ``--dry-run`` (the default) and
``--report work/shift/c_refs_report.md``.  ``--write`` exists for SHIFT-006b6
and is not used here.  The tool is deterministic: sorted files, sorted
symbols, fixed sample selection and no timestamps.

Examples
--------
    python3 tools/shift/rewrite_c_refs.py --dry-run
    python3 tools/shift/rewrite_c_refs.py --dry-run \
        --report work/shift/c_refs_report.md
    python3 tools/shift/rewrite_c_refs.py --check
    python3 tools/shift/rewrite_c_refs.py --write
    python3 tools/shift/rewrite_c_refs.py --self-check
"""

from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from check_relocs import (  # noqa: E402
    c_source_files,
    is_whitelisted,
    mask_c,
    scan_c_text,
)
from gen_blob_tables import ElfSymbols, GenError  # noqa: E402
from map_symbols import SymbolMap  # noqa: E402

STT_NOTYPE = 0
STT_OBJECT = 1
STT_FUNC = 2
BINDING_LOCAL = 0
BINDING_GLOBAL = 1
BINDING_WEAK = 2

C_IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
# A cast is a parenthesised C type: letters, digits, whitespace and asterisks.
CAST_RE = re.compile(r"^[\sA-Za-z_0-9][\w\s*]*$")

WANTED_SAMPLE_FILES = (
    ("src/data/sprite_pointers.c", 2),
    ("src/new_file_intro.c", 2),
    ("src/hud.c", 1),
    ("src/data/audio.c", 1),
    ("src/menus/pause_screen_map.c", 1),
    ("src/sprites_AI/security_pad.c", 1),
    ("src/menus/title_screen.c", 1),
    ("src/sprites_AI/bubbles.c", 1),
)


class RefError(Exception):
    """A C ROM literal cannot be rewritten safely."""


@dataclass(frozen=True)
class Resolution:
    """A resolved C ROM literal.

    ``symbol``/``symbol_addr`` describe the ELF symbol.  ``anchor_name`` and
    ``anchor_addr`` are set only when a local symbol needs a link-visible
    global anchor in the same output section.
    """

    kind: str  # "func" or "data"
    symbol: str
    symbol_addr: int
    value: int
    section: str
    object: str
    binding: int | None
    anchor_name: str | None = None
    anchor_addr: int | None = None

    @property
    def anchored(self) -> bool:
        return self.anchor_name is not None


def checked_symbol(name: str) -> str:
    if not C_IDENT_RE.match(name):
        raise RefError(f"{name!r} is not a C identifier")
    return name


def data_expression(name: str, base_addr: int, value: int) -> str:
    """Address of *name* plus the byte delta to *value*."""
    checked_symbol(name)
    delta = value - base_addr
    if delta == 0:
        return f"&{name}"
    if delta > 0:
        return f"((u8*)&{name} + 0x{delta:X})"
    return f"((u8*)&{name} - 0x{-delta:X})"


def function_expression(name: str, base_addr: int, value: int) -> str:
    """Function symbol *name* plus the byte delta to *value*."""
    checked_symbol(name)
    delta = value - base_addr
    if delta == 0:
        return name
    if delta > 0:
        return f"((u8*){name} + 0x{delta:X})"
    return f"((u8*){name} - 0x{-delta:X})"


def render_expression(res: Resolution) -> str:
    if res.kind == "func":
        if res.anchor_name is not None:
            assert res.anchor_addr is not None
            return function_expression(
                res.anchor_name, res.anchor_addr, res.value
            )
        return function_expression(res.symbol, res.symbol_addr, res.value)
    if res.anchor_name is not None:
        assert res.anchor_addr is not None
        return data_expression(res.anchor_name, res.anchor_addr, res.value)
    return data_expression(res.symbol, res.symbol_addr, res.value)


def same_object(ref_file: str, object_name: str) -> bool:
    """True when a reference and a symbol belong to the same translation unit."""
    with_suffix = Path(ref_file).with_suffix(".o")
    return with_suffix.as_posix() == object_name


def elf_symbol_type(
    elf: ElfSymbols, name: str, addr: int
) -> tuple[int | None, int]:
    """Find the ELF type for *name*, allowing a Thumb-bit address variant."""
    for candidate in (addr, addr | 1, addr & ~1):
        sym_type = elf.symbol_type(name, candidate)
        if sym_type is not None:
            return sym_type, candidate
    return None, addr


def elf_binding(
    elf: ElfSymbols, name: str, addr: int
) -> int | None:
    for candidate in (addr, addr | 1, addr & ~1):
        binding = elf.any_binding(name, candidate)
        if binding is not None:
            return binding
    return None


def build_function_lookup(
    sm: SymbolMap, elf: ElfSymbols
) -> dict[int, Resolution]:
    """Map a literal value (Thumb bit included) to an ELF STT_FUNC symbol."""
    candidates: dict[int, list[Resolution]] = defaultdict(list)
    seen: set[tuple[int, str]] = set()
    for sym in sm.symbols:
        section = sm.sections[sym.section].name
        if not section.startswith(".text"):
            continue
        sym_type, canonical = elf_symbol_type(elf, sym.name, sym.addr)
        if sym_type != STT_FUNC:
            continue
        binding = elf_binding(elf, sym.name, canonical)
        key = (canonical, sym.name)
        if key in seen:
            continue
        seen.add(key)
        for literal in {canonical, canonical & ~1, canonical | 1}:
            candidates[literal].append(
                Resolution(
                    "func",
                    sym.name,
                    canonical,
                    literal,
                    section,
                    sym.object,
                    binding,
                )
            )

    lookup: dict[int, Resolution] = {}
    for literal, items in candidates.items():
        items.sort(
            key=lambda res: (
                0 if res.symbol_addr == res.value else 1,
                0 if res.binding in (BINDING_GLOBAL, BINDING_WEAK) else 1,
                1 if res.symbol.startswith("_") else 0,
                res.symbol,
            )
        )
        lookup[literal] = items[0]
    return lookup


def build_global_functions(
    sm: SymbolMap, elf: ElfSymbols
) -> list[Resolution]:
    """Sorted global/weak STT_FUNC symbols, used as .text anchors."""
    functions: list[Resolution] = []
    seen: set[tuple[int, str]] = set()
    for sym in sm.symbols:
        section = sm.sections[sym.section].name
        if not section.startswith(".text"):
            continue
        sym_type, canonical = elf_symbol_type(elf, sym.name, sym.addr)
        if sym_type != STT_FUNC:
            continue
        binding = elf_binding(elf, sym.name, canonical)
        if binding not in (BINDING_GLOBAL, BINDING_WEAK):
            continue
        key = (canonical, sym.name)
        if key in seen:
            continue
        seen.add(key)
        functions.append(
            Resolution(
                "func",
                sym.name,
                canonical,
                canonical,
                section,
                sym.object,
                binding,
            )
        )
    functions.sort(key=lambda res: (res.symbol_addr, res.symbol))
    return functions


def find_function_anchor(
    functions: list[Resolution], value: int
) -> Resolution | None:
    if not functions:
        return None
    preceding = [res for res in functions if res.symbol_addr <= value]
    if preceding:
        return max(
            preceding, key=lambda res: (res.symbol_addr, res.symbol)
        )
    return min(functions, key=lambda res: (res.symbol_addr, res.symbol))


def make_function_resolution(
    symbol: str,
    symbol_addr: int,
    value: int,
    section: str,
    object_name: str,
    binding: int | None,
    global_functions: list[Resolution],
    ref_file: str,
) -> Resolution:
    # A global function is directly link-visible.  A static function can only
    # be named in its own translation unit; otherwise use a nearby global
    # function in .text plus the byte delta (same-section rule).
    if (
        binding is None
        or binding in (BINDING_GLOBAL, BINDING_WEAK)
        or same_object(ref_file, object_name)
    ):
        return Resolution(
            "func",
            symbol,
            symbol_addr,
            value,
            section,
            object_name,
            binding,
        )
    anchor = find_function_anchor(global_functions, value)
    if anchor is None:
        raise RefError(
            f"0x{value:08X}: local function {symbol} has no global "
            ".text anchor"
        )
    return Resolution(
        "func",
        symbol,
        symbol_addr,
        value,
        section,
        object_name,
        binding,
        anchor.symbol,
        anchor.symbol_addr,
    )


def make_data_resolution(
    elf: ElfSymbols,
    symbol: str,
    symbol_addr: int,
    value: int,
    section: str,
    object_name: str,
    binding: int | None,
    ref_file: str,
) -> Resolution:
    if (
        binding is None
        or binding in (BINDING_GLOBAL, BINDING_WEAK)
        or same_object(ref_file, object_name)
    ):
        return Resolution(
            "data",
            symbol,
            symbol_addr,
            value,
            section,
            object_name,
            binding,
        )
    anchor = elf.anchor(value, section)
    if anchor is None:
        raise RefError(
            f"0x{value:08X}: local data symbol {symbol} has no global "
            f"anchor in {section or '?'}"
        )
    return Resolution(
        "data",
        symbol,
        symbol_addr,
        value,
        section,
        object_name,
        binding,
        anchor.name,
        anchor.value,
    )


def resolve_literal(
    ref: dict,
    sm: SymbolMap,
    elf: ElfSymbols,
    function_lookup: dict[int, Resolution],
    global_functions: list[Resolution],
) -> Resolution:
    value = int(ref["value"], 16)
    ref_file = ref["file"]
    target = sm.resolve(value)
    symbol = target.get("symbol") if target.get("known") else None
    offset = target.get("offset") or 0
    section = target.get("section") or ""
    object_name = target.get("object") or ""

    if symbol:
        symbol_addr = value - offset
        sym_type, canonical = elf_symbol_type(elf, symbol, symbol_addr)
        binding = elf_binding(elf, symbol, canonical)
        if binding is None:
            binding = elf_binding(elf, symbol, symbol_addr)
        if sym_type == STT_FUNC:
            return make_function_resolution(
                symbol,
                canonical,
                value,
                section,
                object_name,
                binding,
                global_functions,
                ref_file,
            )
        if target.get("exact"):
            # An exact non-function symbol is a data symbol even at an odd
            # address (the pause-debug flag bytes are an example).
            return make_data_resolution(
                elf,
                symbol,
                symbol_addr,
                value,
                section,
                object_name,
                binding,
                ref_file,
            )

    # No exact object symbol.  The function index covers an ELF function whose
    # st_value carries the Thumb bit while a map label may be even.
    indexed = function_lookup.get(value)
    if indexed is not None:
        return make_function_resolution(
            indexed.symbol,
            indexed.symbol_addr,
            value,
            indexed.section,
            indexed.object,
            indexed.binding,
            global_functions,
            ref_file,
        )

    if symbol:
        return make_data_resolution(
            elf,
            symbol,
            value - offset,
            value,
            section,
            object_name,
            binding,
            ref_file,
        )

    raise RefError(
        f"0x{value:08X}: address is not mapped to a ROM section/symbol"
    )


def cast_prefix(line: str, start: int) -> str:
    """Return the immediately preceding ``(type)`` cast, if any."""
    i = start - 1
    while i >= 0 and line[i] in " \t":
        i -= 1
    if i < 0 or line[i] != ")":
        return ""
    depth = 1
    j = i - 1
    while j >= 0:
        if line[j] == ")":
            depth += 1
        elif line[j] == "(":
            depth -= 1
            if depth == 0:
                inner = line[j + 1 : i]
                return line[j : i + 1] if CAST_RE.match(inner) else ""
        j -= 1
    return ""


def paren_balance(line: str) -> int:
    masked = mask_c(line)
    return masked.count("(") - masked.count(")")


def plan_file(
    path: Path,
    text: str,
    sm: SymbolMap,
    elf: ElfSymbols,
    function_lookup: dict[int, Resolution],
    global_functions: list[Resolution],
) -> tuple[list[dict], list[str], list[dict], str]:
    """Return (changes, errors, refs, new_text) for one source file."""
    refs = [
        ref
        for ref in scan_c_text(path.as_posix(), text)
        if not is_whitelisted(ref)
    ]
    if not refs:
        return [], [], [], text

    raw_lines = text.split("\n")
    changes: list[dict] = []
    errors: list[str] = []

    for ref in refs:
        lineno = ref["line"]
        if lineno < 1 or lineno > len(raw_lines):
            errors.append(f"{path}:{lineno}: line no longer exists")
            continue
        line = raw_lines[lineno - 1]
        start = ref["column"]
        end = start + len(ref["literal"])
        if line[start:end] != ref["literal"]:
            errors.append(
                f"{path}:{lineno}: literal moved "
                f"({ref['literal']!r} not at column {start + 1})"
            )
            continue

        try:
            resolution = resolve_literal(
                ref, sm, elf, function_lookup, global_functions
            )
            expression = render_expression(resolution)
        except RefError as exc:
            errors.append(f"{path}:{lineno}: {exc}")
            continue

        cast = cast_prefix(line, start)
        new_line = line[:start] + expression + line[end:]
        changes.append(
            {
                "file": path.as_posix(),
                "line": lineno,
                "column": start,
                "literal": ref["literal"],
                "hex_digits": ref["hex_digits"],
                "value": ref["value"],
                "kind": resolution.kind,
                "anchored": resolution.anchored,
                "symbol": resolution.symbol,
                "expression": expression,
                "old_expression": cast + ref["literal"],
                "new_expression": cast + expression,
                "old_line": line,
                "new_line": new_line,
            }
        )

    if errors:
        # Do not attempt a partial file; the caller refuses the whole plan.
        return changes, errors, refs, text

    new_lines = raw_lines[:]
    by_line: dict[int, list[dict]] = defaultdict(list)
    for change in changes:
        by_line[change["line"]].append(change)

    for lineno, line_changes in sorted(by_line.items()):
        original = new_lines[lineno - 1]
        rewritten = original
        # Right-to-left keeps every earlier column valid.
        for change in sorted(
            line_changes, key=lambda item: item["column"], reverse=True
        ):
            start = change["column"]
            end = start + len(change["literal"])
            rewritten = (
                rewritten[:start]
                + change["expression"]
                + rewritten[end:]
            )
        if paren_balance(original) != paren_balance(rewritten):
            errors.append(
                f"{path}:{lineno}: parentheses became unbalanced after "
                "rewrite"
            )
            continue
        new_lines[lineno - 1] = rewritten

    new_text = "\n".join(new_lines)
    if not errors:
        leftover = [
            ref
            for ref in scan_c_text(path.as_posix(), new_text)
            if not is_whitelisted(ref)
        ]
        if leftover:
            for ref in leftover[:10]:
                errors.append(
                    f"{path}:{ref['line']}: {ref['literal']} still present "
                    "after rewrite"
                )
            if len(leftover) > 10:
                errors.append(
                    f"{path}: {len(leftover) - 10} more literal(s) still "
                    "present after rewrite"
                )
    return changes, errors, refs, new_text


def pick_samples(changes: list[dict]) -> list[dict]:
    """Deterministic ten-sample selection covering the requested files."""
    by_file: dict[str, list[dict]] = defaultdict(list)
    for change in changes:
        by_file[change["file"]].append(change)

    picked: list[dict] = []
    picked_ids: set[int] = set()

    def take(name: str, count: int) -> None:
        for change in by_file.get(name, ())[:count]:
            if len(picked) >= 10 or id(change) in picked_ids:
                continue
            picked.append(change)
            picked_ids.add(id(change))

    for name, count in WANTED_SAMPLE_FILES:
        take(name, count)
    for change in changes:
        if len(picked) >= 10:
            break
        if id(change) not in picked_ids:
            picked.append(change)
            picked_ids.add(id(change))
    return picked[:10]


def summarize(
    refs: list[dict], changes: list[dict], errors: list[str]
) -> dict:
    file_counts = Counter(ref["file"] for ref in refs)
    forms = Counter(ref["hex_digits"] for ref in refs)
    functions = [ch for ch in changes if ch["kind"] == "func"]
    data = [ch for ch in changes if ch["kind"] == "data"]
    return {
        "refs": len(refs),
        "files": len(file_counts),
        "file_counts": sorted(
            file_counts.items(), key=lambda item: (-item[1], item[0])
        ),
        "forms": forms,
        "functions": len(functions),
        "function_direct": sum(
            1 for ch in functions if not ch["anchored"]
        ),
        "function_anchored": sum(
            1 for ch in functions if ch["anchored"]
        ),
        "data": len(data),
        "data_direct": sum(1 for ch in data if not ch["anchored"]),
        "data_anchored": sum(1 for ch in data if ch["anchored"]),
        "unknown": len(errors),
    }


def render_report(
    args: argparse.Namespace,
    refs: list[dict],
    changes: list[dict],
    errors: list[str],
    stats: dict,
) -> str:
    lines: list[str] = []
    lines.append("# C ROM literal rewrite plan (SHIFT-005c)")
    lines.append("")
    lines.append(
        "Generated by `python3 tools/shift/rewrite_c_refs.py --dry-run "
        "--report work/shift/c_refs_report.md`."
    )
    lines.append(
        "Planning only: no file under `src/`, `include/`, `asm/`, `data/` or "
        "`sound/` was modified."
    )
    lines.append("")
    lines.append(f"- Map: `{args.map}`")
    lines.append(f"- ELF: `{args.elf}`")
    lines.append(f"- C roots: {', '.join(f'`{r}`' for r in args.roots)}")
    lines.append(f"- Total C ROM refs: **{stats['refs']}**")
    lines.append(
        f"- Literal forms: 7-digit **{stats['forms'].get(7, 0)}**, "
        f"8-digit **{stats['forms'].get(8, 0)}**, "
        f"other **{sum(v for k, v in stats['forms'].items() if k not in (7, 8))}**"
    )
    lines.append(
        f"- Function refs: **{stats['functions']}** "
        f"(direct {stats['function_direct']}, "
        f"anchored {stats['function_anchored']})"
    )
    lines.append(
        f"- Data refs: **{stats['data']}** "
        f"(direct {stats['data_direct']}, "
        f"anchored {stats['data_anchored']})"
    )
    lines.append(f"- Unknown/refused: **{stats['unknown']}**")
    lines.append(f"- Files with refs: **{stats['files']}**")
    lines.append("")

    # Per-file function/data split.  A ref that failed resolution is counted
    # in the total but not in either kind.
    kind_by_file: dict[str, Counter] = defaultdict(Counter)
    for change in changes:
        kind_by_file[change["file"]][change["kind"]] += 1
    lines.append("## Counts by file")
    lines.append("")
    lines.append("| File | Refs | Function | Data |")
    lines.append("|---|---:|---:|---:|")
    for name, count in stats["file_counts"]:
        kinds = kind_by_file.get(name, Counter())
        lines.append(
            f"| `{name}` | {count} | {kinds.get('func', 0)} | "
            f"{kinds.get('data', 0)} |"
        )
    lines.append("")

    if errors:
        lines.append("## Unresolved refs")
        lines.append("")
        for error in errors:
            lines.append(f"- {error}")
        lines.append("")

    lines.append("## Sample rewrite expressions")
    lines.append("")
    lines.append(
        "The surrounding cast is preserved; only the literal token changes. "
        "Local static data symbols use a global same-section anchor plus the "
        "byte delta, so the expression stays link-visible."
    )
    lines.append("")
    for index, change in enumerate(pick_samples(changes), 1):
        lines.append(
            f"{index}. `{change['file']}:{change['line']}` "
            f"({change['kind']}"
            f"{', anchored' if change['anchored'] else ''})"
        )
        lines.append(f"   - old: `{change['old_expression']}`")
        lines.append(f"   - new: `{change['new_expression']}`")
    lines.append("")
    lines.append(
        "Data expressions use `&Symbol` so a scalar object such as "
        "`sTitleScreenDebugTextPointer` is addressed rather than dereferenced. "
        "Function symbols are ELF `STT_FUNC` names; SHIFT-006b6 must provide "
        "declarations for asm-defined names such as `unk_4a3c` when it applies "
        "the plan."
    )
    lines.append("")
    return "\n".join(lines)


def self_check() -> int:
    """Deterministic checks that need no map or ELF file."""
    cases: list[tuple[str, object, object]] = [
        ("data offset zero", data_expression("sFoo", 0x1000, 0x1000), "&sFoo"),
        (
            "data positive offset",
            data_expression("sFoo", 0x1000, 0x1030),
            "((u8*)&sFoo + 0x30)",
        ),
        (
            "data negative offset",
            data_expression("sFoo", 0x1000, 0xFF0),
            "((u8*)&sFoo - 0x10)",
        ),
        (
            "function exact",
            function_expression("SaXElevator", 0x08017BD9, 0x08017BD9),
            "SaXElevator",
        ),
        (
            "function Thumb delta",
            function_expression("Func", 0x08017BD8, 0x08017BD9),
            "((u8*)Func + 0x1)",
        ),
        (
            "function negative delta",
            function_expression("Func", 0x08017BDA, 0x08017BD9),
            "((u8*)Func - 0x1)",
        ),
    ]

    line = "\t[PSPRITE_SA_X_ELEVATOR] = (Func_T)0x8017bd9,"
    start = line.index("0x")
    cases.extend(
        [
            ("Func_T cast", cast_prefix(line, start), "(Func_T)"),
            (
                "multi-word cast",
                cast_prefix(
                    "p = *(const u8** const)0x879c2c8;",
                    "p = *(const u8** const)0x879c2c8;".index("0x"),
                ),
                "(const u8** const)",
            ),
            (
                "macro argument has no cast",
                cast_prefix(
                    "DMA3_COPY_16(0x83e799c, dst, 4);",
                    "DMA3_COPY_16(0x83e799c, dst, 4);".index("0x"),
                ),
                "",
            ),
            (
                "balanced parentheses",
                paren_balance("(u8*)&Foo + 0x10"),
                0,
            ),
        ]
    )

    # The shared scanner must accept the seven-digit form and ignore comments
    # and strings.  This mirrors check_relocs.py's self-check and guards the
    # import contract between the two tools.
    scan_cases = [
        ("7-digit scan", "(Func_T)0x8017bd9,", 1),
        ("commented scan", "// (Func_T)0x8017bd9,", 0),
        ("string scan", 's = "0x8017bd9";', 0),
        ("out-of-range scan", "x = 0x1234567;", 0),
    ]
    for name, text, expected in scan_cases:
        got = len(scan_c_text("src/a.c", text))
        cases.append((name, got, expected))

    cases.extend(
        [
            (
                "span round-trip",
                scan_c_text(
                    "src/a.c", "(Func_T)0x8017bd9,"
                )[0]["literal"],
                "0x8017bd9",
            ),
            ("identifier accepted", checked_symbol("SaXElevator"), "SaXElevator"),
        ]
    )

    failed = 0
    for name, got, expected in cases:
        if got != expected:
            failed += 1
            print(f"  FAIL {name}: expected {expected!r}, got {got!r}")
        else:
            print(f"  ok   {name}: {got!r}")

    try:
        checked_symbol("not-a-c-identifier")
    except RefError:
        print("  ok   invalid identifier refused")
    else:
        failed += 1
        print("  FAIL invalid identifier was accepted")

    total = len(cases) + 1
    if failed:
        print(f"self-check: {failed}/{total} failed")
        return 1
    print(f"self-check: {total}/{total} passed")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument(
        "files",
        nargs="*",
        help="explicit C files to process (default: --root src --root include)",
    )
    ap.add_argument(
        "--root",
        action="append",
        default=[],
        help="C source root (repeatable; default: src, include)",
    )
    ap.add_argument("--map", default="mf_us.map", help="baseline linker map")
    ap.add_argument("--elf", default="mf_us.elf", help="baseline ELF")
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument(
        "--dry-run",
        action="store_true",
        help="show the plan without writing (the default)",
    )
    mode.add_argument(
        "--write", action="store_true", help="apply the plan to the C files"
    )
    mode.add_argument(
        "--check",
        action="store_true",
        help="fail while any C ROM literal still needs rewriting",
    )
    ap.add_argument(
        "--report", default="", help="write a deterministic Markdown report"
    )
    ap.add_argument(
        "--self-check",
        action="store_true",
        help="run pure parser/expression checks and exit",
    )
    args = ap.parse_args()

    if args.self_check:
        return self_check()

    roots = args.root or ["src", "include"]
    args.roots = roots
    if args.files:
        paths = [Path(name) for name in args.files]
        missing = [name for name in args.files if not Path(name).exists()]
        if missing:
            for name in missing:
                print(
                    f"rewrite_c_refs: missing input file {name}",
                    file=sys.stderr,
                )
            return 1
    else:
        paths = c_source_files([Path(root) for root in roots])

    map_path = Path(args.map)
    elf_path = Path(args.elf)
    if not map_path.exists():
        print(
            f"rewrite_c_refs: missing map {map_path}; run "
            "`make -f Makefile.shift symbols`",
            file=sys.stderr,
        )
        return 1
    if not elf_path.exists():
        print(
            f"rewrite_c_refs: missing ELF {elf_path}; run "
            "`make -f Makefile.shift audit`",
            file=sys.stderr,
        )
        return 1

    try:
        elf = ElfSymbols.load(elf_path)
        sm = SymbolMap.load(map_path, elf_path)
    except (OSError, GenError) as exc:
        print(f"rewrite_c_refs: {exc}", file=sys.stderr)
        return 1

    function_lookup = build_function_lookup(sm, elf)
    global_functions = build_global_functions(sm, elf)

    all_changes: list[dict] = []
    all_errors: list[str] = []
    all_refs: list[dict] = []
    file_plans: list[tuple[Path, str]] = []
    for path in paths:
        try:
            text = path.open(
                "r", encoding="utf-8", errors="replace", newline=""
            ).read()
        except OSError as exc:
            all_errors.append(f"{path}: cannot read: {exc}")
            continue
        changes, errors, refs, new_text = plan_file(
            path, text, sm, elf, function_lookup, global_functions
        )
        all_changes.extend(changes)
        all_errors.extend(errors)
        all_refs.extend(refs)
        if changes and not errors:
            file_plans.append((path, new_text))

    stats = summarize(all_refs, all_changes, all_errors)
    files = sorted({ref["file"] for ref in all_refs})

    print(
        f"rewrite_c_refs: {stats['refs']} C ROM ref(s) in "
        f"{len(files)} file(s)"
    )
    print(
        f"  function: {stats['functions']} "
        f"(direct {stats['function_direct']}, "
        f"anchored {stats['function_anchored']})"
    )
    print(
        f"  data:     {stats['data']} "
        f"(direct {stats['data_direct']}, "
        f"anchored {stats['data_anchored']})"
    )
    print(f"  unknown/refused: {stats['unknown']}")

    for change in all_changes:
        print(
            f"  {change['file']}:{change['line']}: "
            f"{change['old_expression']} -> {change['new_expression']}"
        )

    if all_errors:
        for message in all_errors:
            print(f"rewrite_c_refs: ERROR: {message}", file=sys.stderr)
        print(
            f"rewrite_c_refs: refusing to apply ({len(all_errors)} error(s))",
            file=sys.stderr,
        )

    if args.report:
        report_path = Path(args.report)
        report_path.parent.mkdir(parents=True, exist_ok=True)
        report_path.write_text(
            render_report(args, all_refs, all_changes, all_errors, stats),
            encoding="utf-8",
        )
        print(f"rewrite_c_refs: report -> {report_path}")

    if all_errors:
        return 1

    if args.check:
        if all_changes:
            for change in all_changes[:20]:
                print(
                    f"  {change['file']}:{change['line']}: "
                    f"{change['old_expression']} -> "
                    f"{change['new_expression']}"
                )
            if len(all_changes) > 20:
                print(f"  ... {len(all_changes) - 20} more")
            print(
                f"FAIL: {len(all_changes)} of {stats['refs']} C ROM "
                "literal(s) still need rewriting"
            )
            return 1
        print("PASS: no hardcoded ROM literals in C")
        return 0

    if args.write:
        for path, new_text in file_plans:
            with path.open(
                "w", encoding="utf-8", newline=""
            ) as handle:
                handle.write(new_text)
        print(
            f"rewrite_c_refs: {len(all_changes)} rewritten, "
            f"{len(file_plans)} file(s)"
        )
        return 0

    print(
        f"dry-run: {len(all_changes)} to rewrite, 0 already applied, "
        f"{len(files)} file(s)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
