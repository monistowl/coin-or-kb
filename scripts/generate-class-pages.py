#!/usr/bin/env python3
"""
Generate class documentation pages from annotations.json.

Creates Zola markdown pages for libraries and their documented classes.
Prioritizes files with @algorithm, @math, or @complexity annotations.
"""

import json
import os
import re
import sys
from pathlib import Path

# Map library names to layer numbers
LAYER_MAP = {
    'CoinUtils': 0,
    'Clp': 1, 'Osi': 1, 'Cgl': 1,
    'Cbc': 2, 'Ipopt': 2,
    'Bonmin': 3, 'Couenne': 3,
    'SHOT': 4, 'OS': 4
}

LAYER_DESCRIPTIONS = {
    0: "Foundation utilities for COIN-OR solvers",
    1: "Linear programming and cut generation",
    2: "Mixed-integer and nonlinear programming",
    3: "Mixed-integer nonlinear programming",
    4: "Application-level solvers"
}

def slugify(name: str) -> str:
    """Convert class name to URL-safe slug."""
    return name.replace('::', '-').replace('<', '').replace('>', '').replace(' ', '-').lower()

def escape_markdown(text: str) -> str:
    """Escape special markdown characters."""
    if not text:
        return ""
    # Escape pipe characters for tables
    text = text.replace('|', '\\|')
    return text

def format_math_for_katex(text: str) -> str:
    """Format math expressions for KaTeX rendering."""
    if not text:
        return ""

    # Already has LaTeX delimiters
    if '$$' in text or '$' in text:
        return text

    # Wrap common math patterns
    patterns = [
        (r'O\(([^)]+)\)', r'$O(\1)$'),  # Big-O notation
        (r'(\w+)\^(\w+)', r'$\1^{\2}$'),  # Superscripts
        (r'(\w+)_(\w+)', r'$\1_{\2}$'),  # Subscripts
    ]

    for pattern, replacement in patterns:
        text = re.sub(pattern, replacement, text)

    return text

def generate_library_index(library_name: str, library_data: dict, layer: int) -> str:
    """Generate library _index.md content."""
    brief = library_data.get('brief', f'{library_name} library')

    # Count files with deep annotations
    total_files = len(library_data.get('files', {}))
    annotated = sum(1 for f in library_data.get('files', {}).values()
                    if f.get('algorithm') or f.get('math') or f.get('complexity'))

    content = f"""+++
title = "{library_name}"
description = "Layer {layer} - {LAYER_DESCRIPTIONS.get(layer, 'COIN-OR library')}"
template = "library.html"
sort_by = "title"

[extra]
layer = {layer}
+++

# {library_name}

{brief}

**Layer {layer}** | {total_files} files | {annotated} with algorithm annotations

"""
    return content

def format_refs(refs) -> str:
    """Format references as a proper list."""
    if not refs:
        return ""

    # Handle list format
    if isinstance(refs, list):
        result = []
        for ref in refs:
            # Clean up the reference text
            ref_text = str(ref).strip()
            # Skip if it's just implementation details (contains "Implements the")
            if "Implements the" in ref_text or "This is a" in ref_text:
                continue
            # Format nicely
            ref_text = ref_text.replace('\n', ' ').strip()
            if ref_text:
                result.append(f"- {ref_text}")
        return '\n'.join(result)

    # Handle string format
    return f"- {refs}"

def generate_class_page(file_path: str, file_data: dict, library_name: str, layer: int) -> str:
    """Generate class documentation page."""
    # Extract class name from file path
    filename = os.path.basename(file_path)
    class_name = filename.replace('.hpp', '').replace('.h', '').replace('.cpp', '')

    brief = file_data.get('brief', f'{class_name} class')
    algorithm = file_data.get('algorithm', '')
    math = file_data.get('math', '')
    complexity = file_data.get('complexity', '')
    refs = file_data.get('ref', '')
    see_also = file_data.get('see', '')

    # Build description from brief - first line only, cleaned
    description = brief.split('\n')[0][:200] if brief else f"{class_name} documentation"
    description = description.replace('"', '\\"').strip()

    # Don't repeat the brief if it's short
    brief_content = brief if len(brief) > len(description) + 20 else ""

    content = f"""+++
title = "{class_name}"
description = "{description}"
template = "page.html"

[extra]
layer = {layer}
library = "{library_name}"
header_file = "{file_path}"
+++

"""

    # Only add brief if it adds information
    if brief_content:
        content += f"{brief_content}\n\n"

    # Add algorithm section if present
    if algorithm:
        content += """## Algorithm

<div class="algorithm-card">

"""
        content += f"{algorithm}\n\n"

        if math:
            content += '<div class="math">\n\n'
            content += f"{format_math_for_katex(math)}\n\n"
            content += '</div>\n\n'

        if complexity:
            content += f"**Complexity:** {format_math_for_katex(complexity)}\n\n"

        if refs:
            formatted_refs = format_refs(refs)
            if formatted_refs:
                content += f'<div class="refs">\n\n**References:**\n{formatted_refs}\n\n</div>\n\n'

        content += '</div>\n\n'

    # Add math section if no algorithm but has math
    elif math:
        content += """## Mathematics

<div class="math">

"""
        content += f"{format_math_for_katex(math)}\n\n"
        content += '</div>\n\n'

        if complexity:
            content += f"**Complexity:** {format_math_for_katex(complexity)}\n\n"

    # Add see also links
    if see_also:
        content += """## See Also

"""
        # Handle both list and string formats
        refs_list = see_also if isinstance(see_also, list) else see_also.split(',')
        for ref in refs_list:
            ref = ref.strip() if isinstance(ref, str) else str(ref)
            if ref:
                content += f"- {ref}\n"
        content += "\n"

    # Add source link
    content += f"""## Source

Header file: `{file_path}`

"""

    return content

def main():
    # Load annotations
    annotations_path = Path('site/static/api/annotations.json')
    if not annotations_path.exists():
        print(f"Error: {annotations_path} not found")
        sys.exit(1)

    with open(annotations_path) as f:
        data = json.load(f)

    content_dir = Path('site/content/libraries')
    content_dir.mkdir(parents=True, exist_ok=True)

    # Track statistics
    stats = {'libraries': 0, 'pages': 0, 'skipped': 0}

    # Libraries to skip (already done or not priority)
    skip_libraries = {'CoinUtils'}  # Already has detailed pages

    # Process each layer
    for layer_key, layer_data in data.get('layers', {}).items():
        layer_num = int(layer_key.split('-')[1])

        for lib_name, lib_data in layer_data.get('libraries', {}).items():
            if lib_name in skip_libraries:
                print(f"Skipping {lib_name} (already documented)")
                continue

            lib_dir = content_dir / lib_name.lower()
            lib_dir.mkdir(exist_ok=True)

            # Generate library index
            index_content = generate_library_index(lib_name, lib_data, layer_num)
            index_path = lib_dir / '_index.md'

            with open(index_path, 'w') as f:
                f.write(index_content)
            print(f"Created {index_path}")
            stats['libraries'] += 1

            # Generate class pages for files with annotations
            files = lib_data.get('files', {})
            for file_path, file_data in files.items():
                # Only generate pages for files with semantic annotations
                has_algorithm = bool(file_data.get('algorithm'))
                has_math = bool(file_data.get('math'))
                has_complexity = bool(file_data.get('complexity'))

                if not (has_algorithm or has_math or has_complexity):
                    stats['skipped'] += 1
                    continue

                # Extract class name for the page
                filename = os.path.basename(file_path)
                class_name = filename.replace('.hpp', '').replace('.h', '').replace('.cpp', '')

                # Generate page
                page_content = generate_class_page(file_path, file_data, lib_name, layer_num)
                page_path = lib_dir / f"{class_name}.md"

                with open(page_path, 'w') as f:
                    f.write(page_content)
                print(f"  Created {page_path}")
                stats['pages'] += 1

    print(f"\n=== Summary ===")
    print(f"Libraries: {stats['libraries']}")
    print(f"Class pages: {stats['pages']}")
    print(f"Files skipped (no deep annotations): {stats['skipped']}")

if __name__ == '__main__':
    main()
