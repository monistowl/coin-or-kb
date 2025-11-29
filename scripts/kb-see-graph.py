#!/usr/bin/env python3
"""
kb-see-graph.py

Extract @see references into pipeable edges `source -> target`.
Can be fed into graph tools (dot, fd) for dependency navigation.

Usage:
    python scripts/kb-see-graph.py
    python scripts/kb-see-graph.py --pattern Highs --path layer-4/HiGHS
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path
from typing import Iterable

SOURCE_PATTERNS = ("*.h", "*.hpp", "*.c", "*.cpp")


def gather_files(paths: Iterable[Path]) -> Iterable[Path]:
    for base in paths:
        for pattern in SOURCE_PATTERNS:
            yield from base.rglob(pattern)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Produce @see reference edges.")
    parser.add_argument("--path", action="append", help="Directories to scan")
    parser.add_argument("--pattern", help="Filter references containing PATTERN")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    scan_paths = [Path(p) for p in args.path] if args.path else [Path(p) for p in Path(".").glob("layer-*")]
    regex = re.compile(r"@see\s+([^\s*]+)")
    for filepath in gather_files(scan_paths):
        try:
            for lineno, line in enumerate(filepath.read_text(errors="replace").splitlines(), start=1):
                for match in regex.finditer(line):
                    target = match.group(1).rstrip(".,;")
                    if args.pattern and args.pattern not in target:
                        continue
                    print(f"{filepath}:{lineno} -> {target}")
        except Exception:
            continue


if __name__ == "__main__":
    main()
