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

def is_formula_line(line: str) -> bool:
    """Detect if a line is primarily a mathematical formula."""
    line = line.strip()
    if not line:
        return False

    # Lines starting with math keywords
    math_starters = ['min', 'max', 'L(', 'Dual:', 'Primal:', 's.t.', 'subject to']
    for starter in math_starters:
        if line.lower().startswith(starter.lower()):
            return True

    # Lines that are mostly equations (have = and math symbols)
    has_equation = '=' in line and any(c in line for c in ['^', '_', '≤', '≥', '∈', '∑', '∏'])

    # Lines with variable patterns like "x_j = ..." or "γ_i = ..."
    if re.match(r'^[a-zA-Zα-ωΑ-Ω][_^]', line):
        return True

    # High density of math symbols suggests formula
    math_chars = set('^_=≤≥≠∈∉⊆⊇∪∩∑∏∫√±×÷')
    math_density = sum(1 for c in line if c in math_chars) / max(len(line), 1)
    if math_density > 0.05 and has_equation:
        return True

    return False

def ascii_to_latex(text: str) -> str:
    """Convert ASCII math notation to LaTeX."""
    # Already has LaTeX delimiters - return as-is
    if '$$' in text or (text.count('$') >= 2):
        return text

    # Convert common patterns
    result = text

    # Transpose: c^T -> c^{T}
    result = re.sub(r'\^T\b', r'^{T}', result)
    result = re.sub(r'\^{-T}\b', r'^{-T}', result)

    # Inverse: B^-1 -> B^{-1}
    result = re.sub(r'\^-1\b', r'^{-1}', result)
    result = re.sub(r'\^{-1}', r'^{-1}', result)

    # Subscripts: x_j -> x_{j}, but not x_jk (leave multi-char)
    result = re.sub(r'_([a-zA-Z0-9])\b', r'_{\1}', result)

    # Superscripts with numbers: n^2 -> n^{2}
    result = re.sub(r'\^(\d+)\b', r'^{\1}', result)

    # Greek letters are already Unicode, no conversion needed

    # Text annotations in formulas with proper spacing
    result = re.sub(r'\bs\.t\.\s*', r'\\text{ s.t. }', result)
    result = re.sub(r'\bwhere\s+', r'\\text{ where }', result)
    result = re.sub(r'\bfor\s+', r'\\text{ for }', result)
    result = re.sub(r'\bat\s+', r'\\text{ at }', result)
    result = re.sub(r'\bupper\b', r'\\text{upper}', result)
    result = re.sub(r'\blower\b', r'\\text{lower}', result)
    result = re.sub(r'\bdetermines\s+', r'\\text{ determines }', result)
    result = re.sub(r'\bentering\s+', r'\\text{entering }', result)
    result = re.sub(r'\bvar\.\s*', r'\\text{var.}', result)
    result = re.sub(r'\bhas\s+', r'\\text{ has }', result)
    result = re.sub(r'\bcorrect\s+', r'\\text{correct }', result)
    result = re.sub(r'\bsign\b', r'\\text{sign}', result)

    # Common math labels
    result = re.sub(r'^min\s+', r'\\min\\;', result)
    result = re.sub(r'^max\s+', r'\\max\\;', result)
    result = re.sub(r'\bmin\{', r'\\min\\{', result)
    result = re.sub(r'Dual:\s*', r'\\text{Dual: }', result)
    result = re.sub(r'Reduced cost:\s*', r'\\text{Reduced cost: }', result)
    result = re.sub(r'Ratio test:\s*', r'\\text{Ratio test: }', result)

    # Parenthetical notes at end: (primal) -> \text{(primal)}
    result = re.sub(r'\(primal\)', r'\\text{ (primal)}', result)
    result = re.sub(r'\(dual\)', r'\\text{ (dual)}', result)

    return result

def format_math_block(text: str) -> str:
    """Format a math block for display with KaTeX rendering.

    Identifies formula lines and wraps them in display math.
    Prose lines are left as-is for readability.
    """
    if not text:
        return ""

    # Already has LaTeX delimiters - return as-is
    if '$$' in text:
        return text

    lines = text.split('\n')
    result_lines = []

    for line in lines:
        stripped = line.strip()
        if not stripped:
            result_lines.append('')
            continue

        if is_formula_line(stripped):
            # Convert to LaTeX and wrap
            latex_line = ascii_to_latex(stripped)
            result_lines.append(f'$${latex_line}$$')
        else:
            # Keep as prose, but convert any inline math tokens
            result_lines.append(stripped)

    return '\n'.join(result_lines)

def format_complexity(text: str) -> str:
    """Format complexity notation with proper LaTeX for Big-O.

    Wraps O(...) expressions in inline math for proper rendering.
    """
    if not text:
        return ""

    # Already has $ delimiters - return as-is
    if '$' in text:
        return text

    def convert_big_o(match):
        inner = match.group(1)
        # Convert exponents: n^2 -> n^{2}
        inner = re.sub(r'\^(\d+)', r'^{\1}', inner)
        # Convert multiplication implied by space: m^2 n -> m^{2} n
        inner = re.sub(r'\^(\d+)\s+', r'^{\1} \\cdot ', inner)
        return f'$O({inner})$'

    # Wrap Big-O notation
    result = re.sub(r'O\(([^)]+)\)', convert_big_o, text)

    return result

def format_math_for_katex(text: str) -> str:
    """Pass through text without modification.

    Previously tried to auto-convert ASCII math to LaTeX which created
    broken nested delimiters. Now we preserve source text as-is.
    """
    if not text:
        return ""
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
            content += f"{format_math_block(math)}\n\n"
            content += '</div>\n\n'

        if complexity:
            content += f"**Complexity:** {format_complexity(complexity)}\n\n"

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
        content += f"{format_math_block(math)}\n\n"
        content += '</div>\n\n'

        if complexity:
            content += f"**Complexity:** {format_complexity(complexity)}\n\n"

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
