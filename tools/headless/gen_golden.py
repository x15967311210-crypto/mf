#!/usr/bin/env python3
"""Generate golden_manifest.json from a BizHawk parity reference directory."""
import hashlib
import json
import pathlib
import sys

base = pathlib.Path(sys.argv[1]) if len(sys.argv) > 1 else pathlib.Path(
    r"C:\Users\x1596\Proj\mf\work\playtest")
ref = base / "m0f-2026-10-17/tas/bizhawk_parity"
frames = [300, 600, 900, 1059, 4000, 30000, 339001]
regions = ["oam", "pal", "vram", "io", "iwram", "ewram"]


def sha1(path):
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


manifest = {
    "core": "mGBA 0.6.1 / TASVideos/mgba db0041340ff260424f38772df4f286fc3907c1c8 (bizhawk-0.6)",
    "bizhawk": "2.3.0.1 / mgba.dll 4109E16135B2F44A4E8EF046ACD99EAB8600AC4A",
    "rom_sha1": sha1(base / "m0f-2026-10-17/mf_us_m0f_normal.gba"),
    "bios_sha1": sha1(base / "m0-2026-10-17/tools/BizHawk-2.3.2/Firmware/gba_bios.bin"),
    "movie_sha1": sha1(base / "m0f-2026-10-17/tas/reserenv2-metroidfusion-100.bk2"),
    "log_sha1": sha1(ref / "normal_log.txt"),
    "regions": regions,
    "checkpoints": {},
}
for frame in frames:
    manifest["checkpoints"][str(frame)] = {
        region: sha1(ref / f"normal_{frame:06d}_{region}.bin") for region in regions
    }

log_lines = {}
for line in (ref / "normal_log.txt").read_text(encoding="utf-8", errors="replace").splitlines():
    if line and not line.startswith("#"):
        log_lines[line.split()[0]] = line
manifest["log_lines"] = log_lines

out = pathlib.Path(__file__).with_name("golden_manifest.json")
out.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
print(out)
