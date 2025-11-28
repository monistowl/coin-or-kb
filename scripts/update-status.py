#!/usr/bin/env python3
"""
Update .kb/status.json with current coverage metrics for a library.

Usage:
    python update-status.py <library_name> [--mark-pass1|--mark-pass2]
"""

import sys
import json
import argparse
from pathlib import Path
from datetime import datetime

# Import from validate.py
sys.path.insert(0, str(Path(__file__).parent))
# Rename module import (file uses hyphen, Python needs underscore)
import importlib.util
spec = importlib.util.spec_from_file_location("coverage_report", Path(__file__).parent / "coverage-report.py")
coverage_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(coverage_module)
generate_report = coverage_module.generate_report

VENDOR_DIR = Path('/home/tom/Code/vendor')
STATUS_FILE = VENDOR_DIR / '.kb' / 'status.json'


def find_library_path(library_name: str) -> Path:
    """Find the library path across layers."""
    for layer in range(5):
        layer_dir = VENDOR_DIR / f'layer-{layer}'
        lib_path = layer_dir / library_name
        if lib_path.exists():
            return lib_path
    raise ValueError(f"Library '{library_name}' not found in any layer")


def find_library_layer(library_name: str) -> str:
    """Find which layer contains the library."""
    for layer in range(5):
        layer_dir = VENDOR_DIR / f'layer-{layer}'
        lib_path = layer_dir / library_name
        if lib_path.exists():
            return f'layer-{layer}'
    raise ValueError(f"Library '{library_name}' not found")


def update_status(library_name: str, mark_pass1: bool = False, mark_pass2: bool = False):
    """Update status.json with current metrics."""

    # Load current status
    with open(STATUS_FILE) as f:
        status = json.load(f)

    # Find library
    lib_path = find_library_path(library_name)
    layer = find_library_layer(library_name)

    # Generate coverage report
    report = generate_report(lib_path / 'src' if (lib_path / 'src').exists() else lib_path)

    # Update status
    lib_status = status['layers'][layer]['libraries'].get(library_name, {})

    lib_status.update({
        'files_total': report['files_analyzed'],
        'symbols_total': report['total_symbols'],
        'symbols_documented': report['total_documented'],
        'coverage_percent': report['coverage_percent'],
        'pass1_tags': report['pass1_tags'],
        'pass2_tags': report['pass2_tags'],
        'last_updated': datetime.now().isoformat()
    })

    if mark_pass1:
        lib_status['pass1_complete'] = True
        lib_status['status'] = 'pass1_complete'

    if mark_pass2:
        lib_status['pass2_complete'] = True
        lib_status['status'] = 'complete'

    status['layers'][layer]['libraries'][library_name] = lib_status

    # Update current focus if this is where we're working
    if status.get('current_focus', {}).get('library') == library_name:
        if mark_pass2:
            status['current_focus']['phase'] = 'complete'
        elif mark_pass1:
            status['current_focus']['phase'] = 'pass2'

    # Save
    with open(STATUS_FILE, 'w') as f:
        json.dump(status, f, indent=2)

    # Print summary
    print(f"\n✅ Updated status for {library_name}")
    print(f"   Coverage: {report['coverage_percent']}%")
    print(f"   Pass 1 tags: {report['pass1_tags']}")
    print(f"   Pass 2 tags: {report['pass2_tags']}")

    if mark_pass1:
        print(f"   ✓ Marked Pass 1 complete")
    if mark_pass2:
        print(f"   ✓ Marked Pass 2 complete")


def main():
    parser = argparse.ArgumentParser(description='Update library status')
    parser.add_argument('library', help='Library name (e.g., CoinUtils)')
    parser.add_argument('--mark-pass1', action='store_true',
                       help='Mark Pass 1 as complete')
    parser.add_argument('--mark-pass2', action='store_true',
                       help='Mark Pass 2 as complete')

    args = parser.parse_args()

    try:
        update_status(args.library, args.mark_pass1, args.mark_pass2)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()
