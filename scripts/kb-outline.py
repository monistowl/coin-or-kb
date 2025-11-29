#!/usr/bin/env python3
"""
kb-outline.py

Produce a lightweight outline of a header/implementation file by pairing each
@brief block with the following signature line. Helpful when skimming a file's
public surface without opening an editor.

Usage:
    python scripts/kb-outline.py path/to/file.hpp
    python scripts/kb-outline.py layer-4/HiGHS/simplex/HEkk.h --limit 30
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path
from typing import List, Tuple


BRIEF_RE = re.compile(r"@brief\s+(.*)")


def parse_outline(lines: List[str], limit: int | None) -> List[Tuple[str, str]]:
    """Extract (@brief, signature) pairs."""
    items: List[Tuple[str, str]] = []
    for idx, line in enumerate(lines):
        m = BRIEF_RE.search(line)
        if not m:
            continue
        brief = m.group(1).strip()
        # look ahead for next non-empty, non-comment line as signature
        signature = ""
        for next_line in lines[idx + 1 :]:
            stripped = next_line.strip()
            if not stripped:
                continue
            if stripped.startswith("*"):
                continue
            signature = stripped
            break
        items.append((brief, signature))
        if limit and len(items) >= limit:
            break
    return items


def main() -> None:
    parser = argparse.ArgumentParser(description="Outline annotated file quickly.")
    parser.add_argument("file", help="Header/implementation file to outline")
    parser.add_argument("--limit", type=int, help="Max items to show")
    args = parser.parse_args()

    path = Path(args.file)
    if not path.exists():
        raise SystemExit(f"File not found: {path}")

    content = path.read_text(errors="replace").splitlines()
    outline = parse_outline(content, args.limit)

    print(f"Outline for {path} ({len(outline)} items):\n")
    for brief, sig in outline:
        print(f"- {brief}")
        if sig:
            print(f"  signature: {sig}")


if __name__ == "__main__":
    main()
