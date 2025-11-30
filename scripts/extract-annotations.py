#!/usr/bin/env python3
"""
Lightweight annotation extractor for COIN-OR Knowledge Base.

Extracts @algorithm, @math, @complexity, @ref, @file, @brief, @see tags
from C/C++ headers without requiring Doxygen.

Outputs a single monolithic JSON file suitable for MCP serving.
"""

import json
import os
import re
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Any


# Tags to extract (order matters for multiline parsing)
TAGS = [
    'file', 'brief', 'algorithm', 'math', 'complexity', 'ref', 'see',
    'tparam', 'param', 'return', 'author', 'date'
]

# Regex to match Doxygen-style comment blocks
COMMENT_BLOCK_RE = re.compile(
    r'/\*\*(.+?)\*/',
    re.DOTALL
)

# Regex to match individual tags within a comment block
TAG_RE = re.compile(
    r'@(' + '|'.join(TAGS) + r')\s+(.+?)(?=@(?:' + '|'.join(TAGS) + r')|\*/|$)',
    re.DOTALL
)


def clean_comment_text(text: str) -> str:
    """Remove comment formatting artifacts."""
    lines = text.split('\n')
    cleaned = []
    for line in lines:
        # Remove leading * and whitespace
        line = re.sub(r'^\s*\*\s?', '', line)
        # Remove trailing whitespace
        line = line.rstrip()
        cleaned.append(line)

    # Join and clean up
    result = '\n'.join(cleaned).strip()
    # Collapse multiple blank lines
    result = re.sub(r'\n{3,}', '\n\n', result)
    return result


def extract_tags_from_block(block: str) -> Dict[str, Any]:
    """Extract all tags from a comment block."""
    tags = {}

    # Find all tag matches
    for match in TAG_RE.finditer(block):
        tag_name = match.group(1)
        tag_content = clean_comment_text(match.group(2))

        # Some tags can appear multiple times (see, param, ref)
        if tag_name in ('see', 'param', 'tparam', 'ref'):
            if tag_name not in tags:
                tags[tag_name] = []
            if tag_content:
                tags[tag_name].append(tag_content)
        else:
            # Single-value tags
            if tag_content:
                tags[tag_name] = tag_content

    return tags


def extract_file_annotations(filepath: Path) -> Optional[Dict[str, Any]]:
    """Extract annotations from a single header file."""
    try:
        content = filepath.read_text(encoding='utf-8', errors='ignore')
    except Exception as e:
        print(f"  Warning: Could not read {filepath}: {e}", file=sys.stderr)
        return None

    # Find all comment blocks
    blocks = COMMENT_BLOCK_RE.findall(content)

    if not blocks:
        return None

    # Aggregate tags from all blocks
    file_tags = {
        'path': str(filepath),
        'filename': filepath.name,
    }

    # Track which semantic tags we found
    has_semantic_tags = False

    for block in blocks:
        tags = extract_tags_from_block(block)

        for key, value in tags.items():
            # Check for Pass 2 semantic tags
            if key in ('algorithm', 'math', 'complexity', 'ref'):
                has_semantic_tags = True

            # Merge tags
            if key in ('see', 'param', 'tparam', 'ref'):
                # List tags: extend
                if key not in file_tags:
                    file_tags[key] = []
                if isinstance(value, list):
                    file_tags[key].extend(value)
                else:
                    file_tags[key].append(value)
            else:
                # Single tags: first one wins (usually file-level)
                if key not in file_tags:
                    file_tags[key] = value

    # Only include files that have at least some documentation
    if len(file_tags) <= 2:  # Only path and filename
        return None

    file_tags['has_pass2'] = has_semantic_tags
    return file_tags


def scan_library(lib_path: Path) -> Dict[str, Any]:
    """Scan a library directory for annotated headers."""
    lib_name = lib_path.name
    files = {}

    # Find all header files
    for pattern in ['**/*.hpp', '**/*.h']:
        for header in lib_path.glob(pattern):
            # Skip test files and examples
            if 'test' in str(header).lower() or 'example' in str(header).lower():
                continue

            annotations = extract_file_annotations(header)
            if annotations:
                # Use relative path within library as key
                rel_path = str(header.relative_to(lib_path))
                files[rel_path] = annotations

    return {
        'name': lib_name,
        'file_count': len(files),
        'pass2_count': sum(1 for f in files.values() if f.get('has_pass2', False)),
        'files': files
    }


def scan_layer(layer_path: Path) -> Dict[str, Any]:
    """Scan a layer directory for all libraries."""
    layer_name = layer_path.name
    libraries = {}

    # Each subdirectory is a library
    for lib_dir in sorted(layer_path.iterdir()):
        if lib_dir.is_dir() and not lib_dir.name.startswith('.'):
            print(f"  Scanning {lib_dir.name}...", file=sys.stderr)
            lib_data = scan_library(lib_dir)
            if lib_data['file_count'] > 0:
                libraries[lib_dir.name] = lib_data

    return {
        'name': layer_name,
        'library_count': len(libraries),
        'libraries': libraries
    }


def main():
    import argparse

    parser = argparse.ArgumentParser(description='Extract annotations from COIN-OR headers')
    parser.add_argument('--output', '-o', default='site/static/api/annotations.json',
                        help='Output JSON file path')
    parser.add_argument('--pretty', '-p', action='store_true',
                        help='Pretty-print JSON output')
    parser.add_argument('--layers', '-l', nargs='*',
                        help='Specific layers to scan (default: all)')
    args = parser.parse_args()

    project_root = Path(__file__).parent.parent
    os.chdir(project_root)

    print("COIN-OR Knowledge Base - Annotation Extractor", file=sys.stderr)
    print("=" * 50, file=sys.stderr)

    # Find all layer directories
    if args.layers:
        layer_dirs = [Path(f'layer-{l}') if not l.startswith('layer-') else Path(l)
                      for l in args.layers]
    else:
        layer_dirs = sorted(Path('.').glob('layer-*'))

    # Build the knowledge base
    kb = {
        'version': '1.0',
        'generated': datetime.now().isoformat(),
        'project': 'coin-or-knowledge-base',
        'description': 'Annotated optimization solver library documentation',
        'layers': {}
    }

    total_files = 0
    total_pass2 = 0

    for layer_path in layer_dirs:
        if layer_path.is_dir():
            print(f"\nScanning {layer_path.name}...", file=sys.stderr)
            layer_data = scan_layer(layer_path)
            kb['layers'][layer_path.name] = layer_data

            # Tally stats
            for lib in layer_data['libraries'].values():
                total_files += lib['file_count']
                total_pass2 += lib['pass2_count']

    # Add summary stats
    kb['stats'] = {
        'total_layers': len(kb['layers']),
        'total_libraries': sum(l['library_count'] for l in kb['layers'].values()),
        'total_files': total_files,
        'total_pass2_files': total_pass2
    }

    # Write output
    output_path = Path(args.output)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with open(output_path, 'w', encoding='utf-8') as f:
        if args.pretty:
            json.dump(kb, f, indent=2, ensure_ascii=False)
        else:
            json.dump(kb, f, ensure_ascii=False)

    # Print summary
    print(f"\n{'=' * 50}", file=sys.stderr)
    print(f"Extraction complete!", file=sys.stderr)
    print(f"  Layers: {kb['stats']['total_layers']}", file=sys.stderr)
    print(f"  Libraries: {kb['stats']['total_libraries']}", file=sys.stderr)
    print(f"  Files with annotations: {total_files}", file=sys.stderr)
    print(f"  Files with Pass 2 (semantic): {total_pass2}", file=sys.stderr)
    print(f"  Output: {output_path} ({output_path.stat().st_size / 1024:.1f} KB)", file=sys.stderr)


if __name__ == '__main__':
    main()
