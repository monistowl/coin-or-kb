#!/usr/bin/env python3
"""
kb-todo-list.py

List outstanding @todo items with surrounding context. Default search scope is
layer-* directories. Useful for Pass 2 planning.

Usage:
    python scripts/kb-todo-list.py
    python scripts/kb-todo-list.py --path layer-0/CoinUtils --limit 50
"""

from __future__ import annotations

import argparse
import subprocess
from pathlib import Path
from typing import List


def collect_paths(user_paths: List[str]) -> List[str]:
    """Return paths to scan."""
    if user_paths:
        return user_paths
    return [str(p) for p in Path(".").glob("layer-*")]


def main() -> None:
    parser = argparse.ArgumentParser(description="List outstanding @todo annotations.")
    parser.add_argument("--path", action="append", default=[], help="Path(s) to scan")
    parser.add_argument("--limit", type=int, help="Maximum matches to show")
    args = parser.parse_args()

    paths = collect_paths(args.path)
    cmd = ["rg", "-n", "-C", "1", "@todo", *paths]
    if args.limit:
        cmd.insert(1, f"--max-count={args.limit}")

    result = subprocess.run(cmd, stdout=subprocess.PIPE, text=True, check=False)
    print(result.stdout.strip())


if __name__ == "__main__":
    main()
