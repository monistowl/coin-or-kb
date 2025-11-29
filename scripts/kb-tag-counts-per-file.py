#!/usr/bin/env python3
"""
kb-tag-counts-per-file.py

Count annotation tags per file so you can pipe the hottest files into `head`
or `sort`. Runs over headers/sources in layer directories by default.

Usage:
    python scripts/kb-tag-counts-per-file.py
    python scripts/kb-tag-counts-per-file.py --tag algorithm --limit 20
    python scripts/kb-tag-counts-per-file.py --path layer-4/HiGHS --sort desc
"""

from __future__ import annotations

import argparse
import re
from collections import Counter
from pathlib import Path
from typing import Iterable, List, Tuple

SOURCE_PATTERNS = ("*.h", "*.hpp", "*.c", "*.cpp")


def gather_files(paths: Iterable[Path]) -> Iterable[Path]:
    for base in paths:
        for pattern in SOURCE_PATTERNS:
            yield from base.rglob(pattern)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Count annotation tags per file.")
    parser.add_argument("--tag", help="Tag name without '@' (counts only that tag)")
    parser.add_argument("--path", action="append", help="Paths to scan (repeatable)")
    parser.add_argument("--sort", choices=("asc", "desc"), default="desc", help="Sort by count")
    parser.add_argument("--limit", type=int, help="Limit output rows")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    scan_paths = [Path(p) for p in args.path] if args.path else [Path(p) for p in Path(".").glob("layer-*")]
    pattern = re.compile(r"@([A-Za-z]+)")
    rows: List[Tuple[int, str, Path]] = []

    for filepath in gather_files(scan_paths):
        try:
            text = filepath.read_text(errors="replace")
        except Exception:
            continue
        tags = Counter(match.group(1) for match in pattern.finditer(text))
        if args.tag:
            tags = Counter({args.tag: tags.get(args.tag, 0)}) if tags.get(args.tag) else Counter()
        if not tags:
            continue
        for tag, count in tags.items():
            rows.append((count, tag, filepath))

    reverse = args.sort == "desc"
    rows.sort(key=lambda row: row[0], reverse=reverse)

    for idx, (count, tag, filepath) in enumerate(rows):
        if args.limit and idx >= args.limit:
            break
        print(f"{count}\t@{tag}\t{filepath}")


if __name__ == "__main__":
    main()
