#!/usr/bin/env python3
"""Generate and verify a text-only manifest of the extracted data tree.

``tools/extractor.py`` writes ROM-derived bytes into ``data/`` and
``sound/direct_sound_samples/``.  Those trees are ignored by Git, but builds
and caches need to know exactly which bytes they contain.  This tool records
relative POSIX paths, sizes and SHA256 digests in a small JSON file that is
safe to commit; it never reads or writes the ROM itself.

Usage::

    python3 tools/data_manifest.py --write --root data \
        --extra sound/direct_sound_samples
    python3 tools/data_manifest.py --verify --root data \
        --extra sound/direct_sound_samples
    python3 tools/data_manifest.py --cache-key
    python3 tools/data_manifest.py --self-check

The manifest contains a fixed ``schema`` version, the scanned ``roots`` and a
``files`` array sorted by POSIX path.  There are no timestamps, absolute paths
or machine-specific values, so two machines that extract the same baserom
produce byte-identical manifests.

``--verify`` exits 1 when a file is missing, an unexpected file appeared, a
size changed or a SHA256 changed.  Extra files are errors because a cache
restore that leaves stale blobs behind is not the tree the manifest describes.
``--cache-key`` prints one space-free line derived from the baserom SHA1 pin
(``tools/baserom.sha1``) and the manifest file's SHA256.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import sys
import tempfile
from contextlib import contextmanager
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

SCHEMA_VERSION = 1
DEFAULT_MANIFEST = "tools/data-manifest.json"
DEFAULT_ROOT = "data"
BASEROM_PIN = "tools/baserom.sha1"
MAX_REPORT = 10
SHA1_RE = re.compile(r"^[0-9a-f]{40}$")
SHA256_RE = re.compile(r"^[0-9a-f]{64}$")
CHUNK = 1024 * 1024


class ManifestError(Exception):
    """A usage or input error, distinct from a verification mismatch."""


def _posix(path: Path) -> str:
    return path.as_posix()


def _normalize_root(root: str) -> Path:
    """Normalize a CLI root without touching the filesystem.

    Relative roots stay relative to the repository root (the current working
    directory in normal use).  Absolute roots are accepted only when they live
    under that root, because manifest paths must be reproducible.
    """
    path = Path(root)
    if path.is_absolute():
        try:
            path = path.resolve().relative_to(Path.cwd().resolve())
        except ValueError as exc:
            raise ManifestError(
                f"root is outside the repository: {root}") from exc
    else:
        path = Path(os.path.normpath(root))
    if str(path) in (".", ""):
        raise ManifestError("root must name a subdirectory, not the repository root")
    return path


def _normalize_roots(roots: Iterable[str]) -> List[Path]:
    result: List[Path] = []
    seen = set()
    for root in roots:
        path = _normalize_root(root)
        key = _posix(path)
        if key not in seen:
            seen.add(key)
            result.append(path)
    return result


def _hash_file(path: Path) -> Tuple[int, str]:
    digest = hashlib.sha256()
    size = 0
    with path.open("rb") as handle:
        while True:
            chunk = handle.read(CHUNK)
            if not chunk:
                break
            size += len(chunk)
            digest.update(chunk)
    return size, digest.hexdigest()


def scan_tree(roots: Iterable[Path], missing_ok: bool = False) -> Dict[str, Path]:
    """Return ``{path relative to cwd: filesystem path}`` for every file.

    Directory symlinks inside a root are not followed, which keeps a loop from
    hanging the scan.  A root that is itself a symlink to another directory is
    still traversed, because ``os.walk`` opens the top path directly.

    With ``missing_ok`` an absent root contributes no files; the verifier uses
    that so a deleted tree is reported as missing manifest entries (exit 1)
    rather than as a tool error.  A root that exists but is not a directory is
    always an error.
    """
    found: Dict[str, Path] = {}
    for root in roots:
        if not root.exists():
            if missing_ok:
                continue
            raise ManifestError(f"root does not exist: {root}")
        if not root.is_dir():
            raise ManifestError(f"root is not a directory: {root}")
        for dirpath, dirnames, filenames in os.walk(root, followlinks=False):
            dirnames.sort()
            for name in sorted(filenames):
                full = Path(dirpath, name)
                try:
                    if not full.is_file():
                        continue
                except OSError:
                    continue
                relative = full.relative_to(root)
                key = _posix(Path(root, relative))
                found[key] = full
    return found


def build_manifest(roots: Iterable[Path]) -> dict:
    roots = list(roots)
    files = []
    for key, path in sorted(scan_tree(roots).items()):
        size, digest = _hash_file(path)
        files.append({"path": key, "size": size, "sha256": digest})
    return {
        "schema": SCHEMA_VERSION,
        "roots": [_posix(root) for root in roots],
        "files": files,
    }


def manifest_text(manifest: dict) -> str:
    return json.dumps(manifest, indent=2, ensure_ascii=False) + "\n"


def write_manifest(path: Path, roots: Iterable[Path]) -> dict:
    manifest = build_manifest(roots)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    # Explicit newline="" handling keeps the bytes identical on every host;
    # Path.write_text(newline=...) only exists on Python 3.10+ and the repo
    # still supports 3.8.
    with temporary.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write(manifest_text(manifest))
    os.replace(temporary, path)
    return manifest


def load_manifest(path: Path) -> dict:
    try:
        raw = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise ManifestError(f"cannot read manifest {path}: {exc}") from exc
    try:
        manifest = json.loads(raw)
    except json.JSONDecodeError as exc:
        raise ManifestError(f"invalid manifest JSON in {path}: {exc}") from exc
    if not isinstance(manifest, dict):
        raise ManifestError(f"invalid manifest in {path}: top level is not an object")
    if manifest.get("schema") != SCHEMA_VERSION:
        raise ManifestError(
            f"unsupported manifest schema in {path}: "
            f"{manifest.get('schema')!r} (expected {SCHEMA_VERSION})")
    files = manifest.get("files")
    if not isinstance(files, list):
        raise ManifestError(f"invalid manifest in {path}: 'files' is not a list")
    roots = manifest.get("roots")
    if not isinstance(roots, list) or not all(isinstance(item, str) for item in roots):
        raise ManifestError(f"invalid manifest in {path}: 'roots' is not a string list")
    for entry in files:
        if not isinstance(entry, dict):
            raise ManifestError(f"invalid manifest in {path}: file entry is not an object")
        name = entry.get("path")
        if not isinstance(name, str) or not name:
            raise ManifestError(f"invalid manifest in {path}: file entry has no path")
        pure = Path(name)
        if pure.is_absolute() or ".." in pure.parts:
            raise ManifestError(
                f"invalid manifest in {path}: path escapes the repository: {name}")
        if not isinstance(entry.get("size"), int) or entry["size"] < 0:
            raise ManifestError(f"invalid manifest in {path}: bad size for {name}")
        if not isinstance(entry.get("sha256"), str) or not SHA256_RE.match(
                entry["sha256"]):
            raise ManifestError(f"invalid manifest in {path}: bad sha256 for {name}")
    return manifest


def verify_manifest(manifest: dict, roots: Iterable[Path]) -> dict:
    expected = {entry["path"]: entry for entry in manifest["files"]}
    missing: List[str] = []
    size_mismatch: List[dict] = []
    sha_mismatch: List[dict] = []
    checked = 0

    for name in sorted(expected):
        entry = expected[name]
        path = Path(name)
        if not path.is_file():
            missing.append(name)
            continue
        checked += 1
        actual_size = path.stat().st_size
        if actual_size != entry["size"]:
            size_mismatch.append({
                "path": name,
                "expected": entry["size"],
                "actual": actual_size,
            })
            # A different size necessarily changes the digest; do not report
            # the same file twice.
            continue
        _, actual_sha = _hash_file(path)
        if actual_sha != entry["sha256"]:
            sha_mismatch.append({
                "path": name,
                "expected": entry["sha256"],
                "actual": actual_sha,
            })

    scanned = scan_tree(roots, missing_ok=True)
    extra = sorted(set(scanned) - set(expected))
    ok = not (missing or size_mismatch or sha_mismatch or extra)
    return {
        "ok": ok,
        "checked": checked,
        "expected": len(expected),
        "missing": missing,
        "extra": extra,
        "size_mismatch": size_mismatch,
        "sha256_mismatch": sha_mismatch,
    }


def read_baserom_sha1(path: Path) -> str:
    """Read the 40-hex baserom pin, accepting a bare hash or sha1sum output."""
    try:
        raw = path.read_text(encoding="utf-8")
    except OSError as exc:
        raise ManifestError(
            f"cannot read baserom pin {path}: {exc}; restore tools/baserom.sha1 "
            "from Git") from exc
    tokens = raw.split()
    if not tokens:
        raise ManifestError(f"empty baserom pin: {path}")
    value = tokens[0].lower()
    if not SHA1_RE.match(value):
        raise ManifestError(
            f"baserom pin {path} is not a 40-character hex SHA1: {tokens[0]!r}")
    return value


def baserom_pin_path() -> Path:
    local = Path(BASEROM_PIN)
    if local.is_file():
        return local
    # Running from a subdirectory: fall back to the repository containing this
    # script, which keeps --cache-key usable outside the tree root.
    return Path(__file__).resolve().parent.parent / BASEROM_PIN


def compute_cache_key(manifest_path: Path) -> str:
    try:
        raw = manifest_path.read_bytes()
    except OSError as exc:
        raise ManifestError(
            f"cannot read manifest {manifest_path}: {exc}; run "
            "`make data-manifest` first") from exc
    baserom = read_baserom_sha1(baserom_pin_path())
    digest = hashlib.sha256(raw).hexdigest()
    return f"{baserom}-{digest}"


def _print_report(report: dict) -> None:
    for name in report["missing"][:MAX_REPORT]:
        print(f"MISSING    {name}")
    if len(report["missing"]) > MAX_REPORT:
        print(f"MISSING    ... and {len(report['missing']) - MAX_REPORT} more")
    for item in report["size_mismatch"][:MAX_REPORT]:
        print(f"SIZE       {item['path']} expected={item['expected']} "
              f"actual={item['actual']}")
    if len(report["size_mismatch"]) > MAX_REPORT:
        print(f"SIZE       ... and {len(report['size_mismatch']) - MAX_REPORT} more")
    for item in report["sha256_mismatch"][:MAX_REPORT]:
        print(f"SHA256     {item['path']} expected={item['expected']} "
              f"actual={item['actual']}")
    if len(report["sha256_mismatch"]) > MAX_REPORT:
        print(f"SHA256     ... and {len(report['sha256_mismatch']) - MAX_REPORT} more")
    for name in report["extra"][:MAX_REPORT]:
        print(f"EXTRA      {name}")
    if len(report["extra"]) > MAX_REPORT:
        print(f"EXTRA      ... and {len(report['extra']) - MAX_REPORT} more")

    status = "PASS" if report["ok"] else "FAIL"
    print(
        f"data-verify: {status} "
        f"(checked={report['checked']}/{report['expected']} "
        f"missing={len(report['missing'])} "
        f"size={len(report['size_mismatch'])} "
        f"sha256={len(report['sha256_mismatch'])} "
        f"extra={len(report['extra'])})"
    )


def _manifest_roots(manifest: dict) -> List[Path]:
    roots = manifest.get("roots") or [DEFAULT_ROOT]
    return _normalize_roots(roots)


@contextmanager
def _chdir(path: Path):
    previous = Path.cwd()
    os.chdir(path)
    try:
        yield
    finally:
        os.chdir(previous)


def run_self_check() -> int:
    results: List[Tuple[str, bool, str]] = []

    def record(name: str, passed: bool, detail: str = "") -> None:
        results.append((name, passed, detail))

    with tempfile.TemporaryDirectory(prefix="mf-data-manifest-selfcheck-") as tmp:
        root = Path(tmp)
        (root / "tools").mkdir()
        (root / "data" / "sub").mkdir(parents=True)
        (root / "sound" / "direct_sound_samples").mkdir(parents=True)
        (root / "data" / "a.bin").write_bytes(b"abc")
        (root / "data" / "sub" / "b.bin").write_bytes(b"defg")
        (root / "sound" / "direct_sound_samples" / "c.bin").write_bytes(b"hijkl")
        (root / BASEROM_PIN).write_text(
            "0123456789abcdef0123456789abcdef01234567\n", encoding="utf-8")

        with _chdir(root):
            roots = _normalize_roots([DEFAULT_ROOT, "sound/direct_sound_samples"])
            manifest_path = Path(DEFAULT_MANIFEST)
            manifest = write_manifest(manifest_path, roots)

            names = [entry["path"] for entry in manifest["files"]]
            record("write records every file", len(names) == 3,
                   f"got {names}")
            record("paths are repository-relative POSIX paths",
                   names == sorted(names) and
                   names[0] == "data/a.bin" and
                   names[1] == "data/sub/b.bin" and
                   names[2] == "sound/direct_sound_samples/c.bin")
            record("manifest has schema and roots",
                   manifest["schema"] == SCHEMA_VERSION and
                   manifest["roots"] == ["data", "sound/direct_sound_samples"])

            loaded = load_manifest(manifest_path)
            report = verify_manifest(loaded, roots)
            record("verify accepts an untouched tree", report["ok"],
                   str(report))
            record("verify checks every expected file", report["checked"] == 3)

            second_path = Path("tools/data-manifest-second.json")
            write_manifest(second_path, roots)
            record("write is byte-deterministic",
                   second_path.read_bytes() == manifest_path.read_bytes())

            # Same-size mutation: only the digest can detect it.
            target = root / "data" / "sub" / "b.bin"
            target.write_bytes(b"DEFG")
            report = verify_manifest(load_manifest(manifest_path), roots)
            record("verify rejects a same-size mutation",
                   not report["ok"] and len(report["sha256_mismatch"]) == 1,
                   str(report))
            target.write_bytes(b"defg")

            # Shorter mutation: size mismatch.
            target.write_bytes(b"de")
            report = verify_manifest(load_manifest(manifest_path), roots)
            record("verify rejects a size change",
                   not report["ok"] and len(report["size_mismatch"]) == 1,
                   str(report))
            target.write_bytes(b"defg")

            removed = root / "sound" / "direct_sound_samples" / "c.bin"
            removed.unlink()
            report = verify_manifest(load_manifest(manifest_path), roots)
            record("verify rejects a missing file",
                   not report["ok"] and report["missing"] == [
                       "sound/direct_sound_samples/c.bin"], str(report))
            removed.write_bytes(b"hijkl")

            extra = root / "data" / "unexpected.bin"
            extra.write_bytes(b"stale")
            report = verify_manifest(load_manifest(manifest_path), roots)
            record("verify rejects an extra file",
                   not report["ok"] and report["extra"] == ["data/unexpected.bin"],
                   str(report))
            extra.unlink()

            report = verify_manifest(load_manifest(manifest_path), roots)
            record("verify recovers after restoring the tree", report["ok"],
                   str(report))

            first_key = compute_cache_key(manifest_path)
            second_key = compute_cache_key(manifest_path)
            record("cache key is deterministic one line",
                   first_key == second_key and
                   re.match(r"^[0-9a-f]{40}-[0-9a-f]{64}$", first_key) is not None,
                   first_key)

            # A root that is itself a symlink to another tree is traversed.
            outside = root / "outside"
            outside.mkdir()
            (outside / "one.bin").write_bytes(b"one")
            (root / "linkroot").symlink_to("outside", target_is_directory=True)
            linked = build_manifest([Path("linkroot")])
            record("symlinked root is traversed",
                   [entry["path"] for entry in linked["files"]] == [
                       "linkroot/one.bin"],
                   str(linked["files"]))

            # A directory symlink cycle inside a root must not hang or add files.
            (root / "data" / "loop").symlink_to("..", target_is_directory=True)
            looped = build_manifest(roots)
            record("symlink loop is not followed",
                   len(looped["files"]) == 3,
                   str([entry["path"] for entry in looped["files"]]))

    failed = 0
    for name, passed, detail in results:
        status = "PASS" if passed else "FAIL"
        suffix = f": {detail}" if detail else ""
        print(f"[{status}] self-check: {name}{suffix}")
        if not passed:
            failed += 1
    total = len(results)
    print(f"DATA-MANIFEST-SELF-CHECK: {'PASS' if failed == 0 else 'FAIL'} "
          f"({total - failed}/{total} passed)")
    return 0 if failed == 0 else 1


def main(argv: Optional[List[str]] = None) -> int:
    parser = argparse.ArgumentParser(
        description="Generate or verify the extracted-data manifest.")
    action = parser.add_mutually_exclusive_group()
    action.add_argument("--write", action="store_true",
                        help="scan --root/--extra and write --manifest")
    action.add_argument("--verify", action="store_true",
                        help="check --root/--extra against --manifest (exit 1 on mismatch)")
    action.add_argument("--cache-key", action="store_true",
                        help="print baserom-SHA1 + manifest-SHA256 as one line")
    action.add_argument("--self-check", action="store_true",
                        help="run synthetic write/verify/mutation/cache-key tests")
    parser.add_argument("--root", action="append", metavar="DIR",
                        help=f"tree to scan, relative to the repo root "
                             f"(default: {DEFAULT_ROOT})")
    parser.add_argument("--extra", action="append", default=[], metavar="DIR",
                        help="extra tree to scan (repeatable)")
    parser.add_argument("--manifest", default=DEFAULT_MANIFEST, metavar="FILE",
                        help=f"manifest path (default: {DEFAULT_MANIFEST})")
    parser.add_argument("--quiet", action="store_true",
                        help="suppress success output")
    parser.add_argument("--json", action="store_true",
                        help="print a machine-readable JSON report")
    args = parser.parse_args(argv)

    if not (args.write or args.verify or args.cache_key or args.self_check):
        parser.error("choose one of --write, --verify, --cache-key, --self-check")

    if args.self_check:
        return run_self_check()

    manifest_path = Path(args.manifest)

    if args.cache_key:
        try:
            print(compute_cache_key(manifest_path))
        except ManifestError as exc:
            print(f"data-cache-key: ERROR {exc}", file=sys.stderr)
            return 2
        return 0

    explicit_roots = args.root is not None or bool(args.extra)
    try:
        if args.write:
            root_names = args.root if args.root else [DEFAULT_ROOT]
            roots = _normalize_roots(list(root_names) + list(args.extra))
            manifest = write_manifest(manifest_path, roots)
            summary = {
                "manifest": _posix(manifest_path),
                "roots": manifest["roots"],
                "files": len(manifest["files"]),
                "bytes": sum(entry["size"] for entry in manifest["files"]),
            }
            if args.json:
                print(json.dumps(summary, indent=2, sort_keys=True))
            elif not args.quiet:
                print(f"data-manifest: wrote {summary['files']} files "
                      f"({summary['bytes']} bytes) to {manifest_path}")
            return 0

        manifest = load_manifest(manifest_path)
        if explicit_roots:
            roots = _normalize_roots(
                list(args.root if args.root else [DEFAULT_ROOT]) + list(args.extra))
        else:
            roots = _manifest_roots(manifest)
        report = verify_manifest(manifest, roots)
        if args.json:
            print(json.dumps(report, indent=2, sort_keys=True))
        elif not report["ok"]:
            _print_report(report)
        elif not args.quiet:
            print(f"data-verify: PASS (checked={report['checked']}/"
                  f"{report['expected']} missing=0 size=0 sha256=0 extra=0)")
        return 0 if report["ok"] else 1
    except ManifestError as exc:
        print(f"data-manifest: ERROR {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
