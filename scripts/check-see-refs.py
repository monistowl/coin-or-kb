#!/usr/bin/env python3
"""
Cross-Reference Checker

Validates that @see references point to existing files.
Helps catch broken cross-references in annotations.

Usage:
    python check-see-refs.py <directory> [--fix]
"""

import re
import sys
import argparse
from pathlib import Path
from typing import List, Tuple, Set


def extract_see_refs(content: str) -> List[str]:
    """Extract all @see references from file content."""
    refs = []
    # Match @see followed by a file path (e.g., @see CoinModel.hpp)
    for match in re.finditer(r'@see\s+(\S+\.(?:hpp|h|cpp|c))', content):
        refs.append(match.group(1))
    return refs


def find_all_headers(base_dir: Path) -> Set[str]:
    """Find all header files in the directory tree."""
    headers = set()
    for pattern in ['**/*.hpp', '**/*.h']:
        for path in base_dir.glob(pattern):
            headers.add(path.name)
    return headers


def check_file(filepath: Path, known_headers: Set[str]) -> List[Tuple[str, str]]:
    """Check @see references in a file.

    Returns list of (ref, status) tuples.
    """
    issues = []
    try:
        content = filepath.read_text(errors='replace')
        refs = extract_see_refs(content)

        for ref in refs:
            # Get just the filename (strip path components)
            ref_name = Path(ref).name
            if ref_name not in known_headers:
                issues.append((ref, "NOT_FOUND"))
    except Exception as e:
        issues.append((str(filepath), f"ERROR: {e}"))

    return issues


def check_directory(dirpath: Path) -> dict:
    """Check all files in directory for broken @see references."""
    # First, collect all known headers
    known_headers = find_all_headers(dirpath)

    results = {
        'total_files': 0,
        'files_with_issues': 0,
        'total_refs': 0,
        'broken_refs': [],
    }

    for pattern in ['**/*.hpp', '**/*.h', '**/*.cpp']:
        for filepath in dirpath.glob(pattern):
            results['total_files'] += 1

            content = filepath.read_text(errors='replace')
            refs = extract_see_refs(content)
            results['total_refs'] += len(refs)

            issues = check_file(filepath, known_headers)
            if issues:
                results['files_with_issues'] += 1
                for ref, status in issues:
                    results['broken_refs'].append({
                        'file': str(filepath),
                        'ref': ref,
                        'status': status
                    })

    return results


def main():
    parser = argparse.ArgumentParser(description='Check @see cross-references')
    parser.add_argument('path', type=Path, help='Directory to check')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')

    args = parser.parse_args()

    if not args.path.is_dir():
        print(f"Error: {args.path} is not a directory", file=sys.stderr)
        sys.exit(1)

    results = check_directory(args.path)

    print(f"\n{'='*60}")
    print("CROSS-REFERENCE CHECK")
    print(f"{'='*60}")
    print(f"Files checked:       {results['total_files']}")
    print(f"Total @see refs:     {results['total_refs']}")
    print(f"Files with issues:   {results['files_with_issues']}")
    print(f"Broken references:   {len(results['broken_refs'])}")

    if results['broken_refs']:
        print(f"\n{'='*60}")
        print("BROKEN REFERENCES")
        print(f"{'='*60}")
        for item in results['broken_refs'][:20]:
            print(f"  {item['file']}")
            print(f"    @see {item['ref']} → {item['status']}")

    if len(results['broken_refs']) > 20:
        print(f"\n  ... and {len(results['broken_refs']) - 20} more")

    # Exit with error code if broken refs found
    sys.exit(1 if results['broken_refs'] else 0)


if __name__ == '__main__':
    main()
