#!/usr/bin/env python3
"""
kb-tag-search.py

Greps for annotation tags or free-text keywords and shows compact snippets.
Useful for locating algorithms, math notes, or todos without opening files.

Examples:
    python scripts/kb-tag-search.py --tag @algorithm "Markowitz"
    python scripts/kb-tag-search.py --tag @todo
    python scripts/kb-tag-search.py "Forrest-Tomlin"
"""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path
from typing import List


def run_rg(pattern: str, paths: List[str]) -> str:
    """Run ripgrep and return stdout. Falls back to Python search if rg missing."""
    try:
        result = subprocess.run(
            ["rg", "-n", "-C", "2", "--pcre2", pattern, *paths],
            check=False,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
        )
        if result.returncode in (0, 1):  # 1 => no matches
            return result.stdout
    except FileNotFoundError:
        pass

    return python_search(pattern, paths)


def python_search(pattern: str, paths: List[str]) -> str:
    """Simple Python fallback search."""
    compiled = re.compile(pattern)
    lines = []
    for base in paths:
        for path in Path(base).rglob("*.[ch]pp"):
            try:
                content = path.read_text(errors="replace").splitlines()
            except Exception:
                continue
            for idx, line in enumerate(content, start=1):
                if compiled.search(line):
                    prefix = content[idx - 2] if idx >= 2 else ""
                    suffix = content[idx] if idx < len(content) else ""
                    lines.append(f"{path}:{idx-1}\n  {prefix}\n> {line}\n  {suffix}\n")
    return "\n".join(lines)


def build_pattern(tag: str | None, keywords: List[str]) -> str:
    """Construct a PCRE pattern for rg."""
    parts = []
    if tag:
        parts.append(re.escape(tag))
    for kw in keywords:
        parts.append(re.escape(kw))
    return "(?i)" + ".*".join(parts)


def main() -> None:
    parser = argparse.ArgumentParser(description="Search annotations quickly.")
    parser.add_argument("keywords", nargs="*", help="Keywords to search for")
    parser.add_argument("--tag", help="Tag to anchor on (e.g., @algorithm, @math, @todo)")
    parser.add_argument("--path", action="append", default=[], help="Paths to search (default: layer-*/)")
    args = parser.parse_args()

    paths = args.path or [str(p) for p in Path(".").glob("layer-*")]
    pattern = build_pattern(args.tag, args.keywords)
    output = run_rg(pattern, paths)
    print(output.strip())


if __name__ == "__main__":
    main()
