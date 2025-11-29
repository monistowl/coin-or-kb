#!/usr/bin/env python3
"""
Annotation Metrics Dashboard

Quick overview of annotation coverage across the knowledge base.
Shows tag counts per layer/library.

Usage:
    python annotation-metrics.py [path]
"""

import re
import sys
from pathlib import Path
from collections import defaultdict


TAG_PATTERNS = {
    # Pass 1 tags
    'file': r'@file\b',
    'brief': r'@brief\b',
    'param': r'@param\b',
    'return': r'@return\b',
    'see': r'@see\b',
    # Pass 2 tags
    'algorithm': r'@algorithm\b',
    'math': r'@math\b',
    'complexity': r'@complexity\b',
    'ref': r'@ref\b',
    'invariant': r'@invariant\b',
}


def count_tags(content: str) -> dict:
    """Count all tag types in content."""
    counts = {}
    for tag, pattern in TAG_PATTERNS.items():
        counts[tag] = len(re.findall(pattern, content))
    return counts


def get_library_name(filepath: Path, base: Path) -> str:
    """Extract library name from path."""
    rel = filepath.relative_to(base)
    parts = rel.parts
    if len(parts) >= 2:
        return f"{parts[0]}/{parts[1]}"
    return str(rel)


def analyze_path(base_path: Path) -> dict:
    """Analyze all files under path."""
    results = defaultdict(lambda: defaultdict(int))
    file_counts = defaultdict(int)

    for pattern in ['**/*.hpp', '**/*.h', '**/*.cpp']:
        for filepath in base_path.glob(pattern):
            try:
                content = filepath.read_text(errors='replace')
                lib = get_library_name(filepath, base_path)
                counts = count_tags(content)

                file_counts[lib] += 1
                for tag, count in counts.items():
                    results[lib][tag] += count

            except Exception:
                continue

    return dict(results), dict(file_counts)


def main():
    path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('.')

    if not path.is_dir():
        print(f"Error: {path} is not a directory", file=sys.stderr)
        sys.exit(1)

    results, file_counts = analyze_path(path)

    # Print header
    print(f"\n{'Library':<35} {'Files':>6} {'@file':>6} {'@brief':>7} "
          f"{'@param':>7} {'@algo':>6} {'@math':>6} {'@cmplx':>7}")
    print("-" * 90)

    # Sort by layer number
    sorted_libs = sorted(results.keys())

    total_files = 0
    totals = defaultdict(int)

    for lib in sorted_libs:
        counts = results[lib]
        fc = file_counts[lib]
        total_files += fc

        for tag, count in counts.items():
            totals[tag] += count

        print(f"{lib:<35} {fc:>6} {counts['file']:>6} {counts['brief']:>7} "
              f"{counts['param']:>7} {counts['algorithm']:>6} {counts['math']:>6} "
              f"{counts['complexity']:>7}")

    print("-" * 90)
    print(f"{'TOTAL':<35} {total_files:>6} {totals['file']:>6} {totals['brief']:>7} "
          f"{totals['param']:>7} {totals['algorithm']:>6} {totals['math']:>6} "
          f"{totals['complexity']:>7}")

    # Pass 1 vs Pass 2 summary
    p1 = totals['file'] + totals['brief'] + totals['param'] + totals['return'] + totals['see']
    p2 = totals['algorithm'] + totals['math'] + totals['complexity'] + totals['ref']

    print(f"\nPass 1 tags: {p1}   |   Pass 2 tags: {p2}")


if __name__ == '__main__':
    main()
