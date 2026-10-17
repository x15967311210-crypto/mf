#!/usr/bin/env python3
"""Parse an arm-none-eabi linker map into a queryable symbol database.

The map is the stable, cheap source of truth for the baseline.  Ghidra/REA can
add names later, but address classification must work before either is online.
"""

from __future__ import annotations

import argparse
import json
import re
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Optional

SECTION_RE = re.compile(
    r"^\s*([A-Za-z_.$][\w.$]*)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)(?:\s+(\S+))?\s*$"
)
SYMBOL_RE = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_.$][\w.$@]*)\s*$")
ASSIGN_RE = re.compile(
    r"^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_.$][\w.$@]*)\s*=\s*\.\s*$"
)

ROM_START = 0x08000000
ROM_END = 0x0A000000
EWRAM_START, EWRAM_END = 0x02000000, 0x02040000
IWRAM_START, IWRAM_END = 0x03000000, 0x03008000
MMIO_START, MMIO_END = 0x04000000, 0x04000400
PALETTE_START, PALETTE_END = 0x05000000, 0x05000400
VRAM_START, VRAM_END = 0x06000000, 0x06018000
OAM_START, OAM_END = 0x07000000, 0x07000400


@dataclass
class Section:
    index: int
    name: str
    start: int
    size: int
    object: str

    @property
    def end(self) -> int:
        return self.start + self.size


@dataclass
class Symbol:
    name: str
    addr: int
    size: int
    section: int
    object: str

    @property
    def end(self) -> int:
        return self.addr + self.size


class SymbolMap:
    def __init__(self) -> None:
        self.sections: list[Section] = []
        self.symbols: list[Symbol] = []
        self._by_addr: dict[int, Symbol] = {}
        self._by_section: dict[int, list[Symbol]] = {}

    @classmethod
    def load(cls, path: Path) -> "SymbolMap":
        sm = cls()
        current: Optional[Section] = None
        in_map = False
        for line in path.read_text(errors="replace").splitlines():
            if "Linker script and memory map" in line:
                in_map = True
                continue
            if not in_map:
                continue

            m = SECTION_RE.match(line)
            if m:
                current = Section(
                    index=len(sm.sections),
                    name=m.group(1),
                    start=int(m.group(2), 16),
                    size=int(m.group(3), 16),
                    object=m.group(4) or "",
                )
                sm.sections.append(current)
                continue

            m = ASSIGN_RE.match(line)
            if m and current is not None:
                addr = int(m.group(1), 16)
                name = m.group(2)
                if current.start <= addr < current.end or current.size == 0:
                    sm.symbols.append(
                        Symbol(name, addr, 0, current.index, current.object)
                    )
                continue

            m = SYMBOL_RE.match(line)
            if m and current is not None:
                addr = int(m.group(1), 16)
                name = m.group(2)
                # Ignore a symbol that falls outside the current section: the
                # map has occasional zero-size or duplicate section blocks.
                if current.start <= addr < current.end or current.size == 0:
                    sm.symbols.append(
                        Symbol(name, addr, 0, current.index, current.object)
                    )
                continue

        sm.sections.sort(key=lambda s: (s.start, s.size))
        sm.symbols.sort(key=lambda s: (s.addr, s.name))
        for sym in sm.symbols:
            sm._by_addr.setdefault(sym.addr, sym)
            sm._by_section.setdefault(sym.section, []).append(sym)

        for sec in sm.sections:
            syms = sm._by_section.get(sec.index, [])
            for i, sym in enumerate(syms):
                nxt = syms[i + 1].addr if i + 1 < len(syms) else sec.end
                sym.size = max(0, nxt - sym.addr)
        return sm

    def section_at(self, addr: int) -> Optional[Section]:
        # The map contains an aggregate `.rodata`/`.text` section plus the
        # per-object sub-sections.  Prefer the most specific (smallest)
        # containing section, otherwise a blob pointer resolves against the
        # aggregate section that has no symbols.
        containing = [s for s in self.sections if s.start <= addr < s.end]
        if not containing:
            return None
        return min(containing, key=lambda s: (s.size, s.start))

    def resolve(self, addr: int) -> dict:
        """Return the best symbol (or section+offset) for an address."""
        exact = self._by_addr.get(addr)
        if exact is not None:
            return {
                "addr": f"0x{addr:08X}",
                "symbol": exact.name,
                "offset": 0,
                "section": self.sections[exact.section].name,
                "object": exact.object,
                "exact": True,
                "known": True,
            }

        sec = self.section_at(addr)
        if sec is None:
            return {
                "addr": f"0x{addr:08X}",
                "symbol": None,
                "offset": None,
                "section": None,
                "object": None,
                "exact": False,
                "known": False,
            }

        candidates = [
            s
            for s in self._by_section.get(sec.index, [])
            if s.addr <= addr < s.end or s.addr <= addr
        ]
        best = max(candidates, key=lambda s: s.addr) if candidates else None
        if best is None:
            return {
                "addr": f"0x{addr:08X}",
                "symbol": None,
                "offset": addr - sec.start,
                "section": sec.name,
                "object": sec.object,
                "exact": False,
                "known": True,
            }
        return {
            "addr": f"0x{addr:08X}",
            "symbol": best.name,
            "offset": addr - best.addr,
            "section": sec.name,
            "object": sec.object,
            "exact": False,
            "known": True,
        }

    def to_dict(self) -> dict:
        return {
            "sections": [asdict(s) for s in self.sections],
            "symbols": [asdict(s) for s in self.symbols],
            "summary": {
                "sections": len(self.sections),
                "symbols": len(self.symbols),
            },
        }


def category(addr: int) -> str:
    if ROM_START <= addr < ROM_END:
        return "rom"
    if EWRAM_START <= addr < EWRAM_END:
        return "ewram"
    if IWRAM_START <= addr < IWRAM_END:
        return "iwram"
    if MMIO_START <= addr < MMIO_END:
        return "mmio"
    if PALETTE_START <= addr < PALETTE_END:
        return "palette"
    if VRAM_START <= addr < VRAM_END:
        return "vram"
    if OAM_START <= addr < OAM_END:
        return "oam"
    return "other"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--map", default="mf_us.map")
    ap.add_argument("--out", default="work/shift/symbols.json")
    args = ap.parse_args()

    sm = SymbolMap.load(Path(args.map))
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(sm.to_dict(), indent=2) + "\n")
    print(
        f"symbols: {len(sm.symbols)} symbols, {len(sm.sections)} sections -> {out}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
