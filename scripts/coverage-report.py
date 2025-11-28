#!/usr/bin/env python3
"""
Generate annotation coverage report for a library or the whole project.

Usage:
    python coverage-report.py [library_path] [--by-file] [--json]
"""

import sys
import json
import argparse
from pathlib import Path
from collections import defaultdict

# Import from validate.py
sys.path.insert(0, str(Path(__file__).parent))
from validate import validate_path, AnnotationParser


def get_file_stats(filepath: Path) -> dict:
    """Get coverage stats for a single file."""
    try:
        content = filepath.read_text(errors='replace')
        parser = AnnotationParser(content, str(filepath))
        comments = parser.parse_comments()
        symbols = parser.parse_symbols()
        parser.associate_comments(comments, symbols)

        public_symbols = [s for s in symbols if s.is_public]
        documented = [s for s in public_symbols if s.comment is not None]

        # Count specific tags
        all_tags = defaultdict(int)
        for comment in comments:
            for tag in comment.tags:
                all_tags[tag.name] += 1

        return {
            'file': str(filepath),
            'symbols_total': len(public_symbols),
            'symbols_documented': len(documented),
            'coverage': len(documented) / len(public_symbols) * 100 if public_symbols else 100,
            'tags': dict(all_tags)
        }
    except Exception as e:
        return {
            'file': str(filepath),
            'error': str(e)
        }


def generate_report(path: Path, by_file: bool = False) -> dict:
    """Generate coverage report for path."""

    # Collect files
    if path.is_file():
        files = [path]
    else:
        files = list(path.rglob('*.hpp')) + list(path.rglob('*.h'))
        # Optionally include .cpp files
        # files += list(path.rglob('*.cpp'))

    # Gather stats
    file_stats = []
    total_symbols = 0
    total_documented = 0
    total_tags = defaultdict(int)

    for filepath in sorted(files):
        stats = get_file_stats(filepath)
        if 'error' not in stats:
            file_stats.append(stats)
            total_symbols += stats['symbols_total']
            total_documented += stats['symbols_documented']
            for tag, count in stats.get('tags', {}).items():
                total_tags[tag] += count

    report = {
        'path': str(path),
        'files_analyzed': len(file_stats),
        'total_symbols': total_symbols,
        'total_documented': total_documented,
        'coverage_percent': round(total_documented / total_symbols * 100, 1) if total_symbols else 100,
        'tag_counts': dict(total_tags),
        'pass1_tags': sum(total_tags.get(t, 0) for t in ['brief', 'param', 'return', 'see', 'invariant']),
        'pass2_tags': sum(total_tags.get(t, 0) for t in ['algorithm', 'math', 'complexity', 'ref', 'note']),
    }

    if by_file:
        report['files'] = sorted(file_stats, key=lambda x: x.get('coverage', 0))

    return report


def print_report(report: dict, by_file: bool = False):
    """Print human-readable report."""

    print(f"\n{'='*70}")
    print(f"COVERAGE REPORT: {report['path']}")
    print(f"{'='*70}")

    print(f"\n📊 SUMMARY")
    print(f"   Files analyzed:     {report['files_analyzed']}")
    print(f"   Total symbols:      {report['total_symbols']}")
    print(f"   Documented:         {report['total_documented']}")
    print(f"   Coverage:           {report['coverage_percent']}%")

    print(f"\n📝 TAG COUNTS")
    print(f"   Pass 1 tags:        {report['pass1_tags']}")
    print(f"   Pass 2 tags:        {report['pass2_tags']}")

    if report['tag_counts']:
        print(f"\n   Breakdown:")
        for tag, count in sorted(report['tag_counts'].items(), key=lambda x: -x[1]):
            print(f"      @{tag}: {count}")

    if by_file and 'files' in report:
        print(f"\n{'─'*70}")
        print(f"FILES BY COVERAGE (lowest first)")
        print(f"{'─'*70}")

        for stats in report['files'][:20]:  # Show worst 20
            pct = stats.get('coverage', 0)
            bar = '█' * int(pct / 5) + '░' * (20 - int(pct / 5))
            fname = Path(stats['file']).name
            print(f"   {pct:5.1f}% {bar} {fname}")

        if len(report['files']) > 20:
            print(f"   ... and {len(report['files']) - 20} more files")

    print(f"\n{'='*70}\n")


def main():
    parser = argparse.ArgumentParser(description='Generate coverage report')
    parser.add_argument('path', type=Path, nargs='?',
                       default=Path('/home/tom/Code/vendor'),
                       help='Library path (default: whole project)')
    parser.add_argument('--by-file', action='store_true',
                       help='Show per-file breakdown')
    parser.add_argument('--json', action='store_true',
                       help='Output as JSON')

    args = parser.parse_args()

    report = generate_report(args.path, args.by_file)

    if args.json:
        print(json.dumps(report, indent=2))
    else:
        print_report(report, args.by_file)


if __name__ == '__main__':
    main()
