#!/usr/bin/env python3
"""
Generate algorithm cross-reference pages from JSON API data.

Creates Zola content pages for each algorithm found in @algorithm annotations,
with cross-links to all files that implement or use that algorithm.
"""

import json
import re
import os
from pathlib import Path
from collections import defaultdict
from urllib.parse import urlparse
import unicodedata


def get_base_path(config_path):
    """Extract base path from Zola config.toml base_url."""
    with open(config_path) as f:
        for line in f:
            if line.startswith('base_url'):
                # Parse: base_url = "https://domain.com/path"
                match = re.search(r'=\s*"([^"]+)"', line)
                if match:
                    url = match.group(1)
                    parsed = urlparse(url)
                    # Return path, ensuring it doesn't end with /
                    return parsed.path.rstrip('/') or ''
    return ''

def slugify(text):
    """Convert text to URL-safe slug."""
    text = unicodedata.normalize('NFKD', text)
    text = text.encode('ascii', 'ignore').decode('ascii')
    text = re.sub(r'[^\w\s-]', '', text.lower())
    text = re.sub(r'[-\s]+', '-', text).strip('-')
    return text[:50]  # Limit length

def extract_algorithm_name(alg_text):
    """Extract clean algorithm name from @algorithm annotation."""
    # Get first line as the name
    first_line = alg_text.split('\n')[0].strip()
    # Remove trailing colon
    name = re.sub(r':$', '', first_line)
    return name

def categorize_algorithm(name):
    """Assign algorithm to a category based on keywords."""
    name_lower = name.lower()

    if any(k in name_lower for k in ['presolve', 'elimination', 'reduction', 'bound', 'forcing', 'singleton', 'doubleton', 'tripleton']):
        return 'Presolve Reductions'
    elif any(k in name_lower for k in ['factorization', 'lu ', 'ldl', 'cholesky', 'decomposition']):
        return 'Matrix Factorization'
    elif any(k in name_lower for k in ['simplex', 'pivot', 'pricing']):
        return 'Simplex Method'
    elif any(k in name_lower for k in ['interior point', 'barrier', 'ipm']):
        return 'Interior Point Methods'
    elif any(k in name_lower for k in ['branch', 'bound', 'tree', 'node', 'cut']):
        return 'Branch and Bound'
    elif any(k in name_lower for k in ['heuristic', 'rounding', 'pump', 'dive', 'rins', 'rens']):
        return 'Primal Heuristics'
    elif any(k in name_lower for k in ['clique', 'conflict', 'graph']):
        return 'Conflict Analysis'
    elif any(k in name_lower for k in ['sparse', 'matrix', 'vector', 'storage']):
        return 'Data Structures'
    elif any(k in name_lower for k in ['file', 'parse', 'mps', 'lp ']):
        return 'File I/O'
    else:
        return 'Other Algorithms'

def build_algorithm_index(json_path):
    """Build inverse index: algorithm -> list of implementations."""
    with open(json_path) as f:
        data = json.load(f)

    algorithms = defaultdict(lambda: {
        'name': '',
        'description': '',
        'math': '',
        'complexity': '',
        'refs': [],
        'files': [],
        'category': ''
    })

    for layer_id, layer in data['layers'].items():
        for lib_name, lib in layer['libraries'].items():
            for file_path, file_info in lib['files'].items():
                if not file_info.get('algorithm'):
                    continue

                alg_text = file_info['algorithm']
                name = extract_algorithm_name(alg_text)
                slug = slugify(name)

                if not slug:
                    continue

                alg = algorithms[slug]

                # Set name and description from first occurrence
                if not alg['name']:
                    alg['name'] = name
                    # Description is everything after first line
                    lines = alg_text.split('\n')
                    if len(lines) > 1:
                        alg['description'] = '\n'.join(lines[1:]).strip()

                # Accumulate math, complexity, refs from all sources
                if file_info.get('math') and not alg['math']:
                    alg['math'] = file_info['math']

                if file_info.get('complexity') and not alg['complexity']:
                    alg['complexity'] = file_info['complexity']

                if file_info.get('ref'):
                    refs = file_info['ref']
                    if isinstance(refs, list):
                        for r in refs:
                            if r not in alg['refs']:
                                alg['refs'].append(r)
                    elif refs not in alg['refs']:
                        alg['refs'].append(refs)

                # Add file reference
                alg['files'].append({
                    'path': file_info['path'],
                    'filename': file_info['filename'],
                    'library': lib_name,
                    'layer': layer_id,
                    'brief': file_info.get('brief', '')
                })

                # Set category
                if not alg['category']:
                    alg['category'] = categorize_algorithm(name)

    return dict(algorithms)

def escape_toml_string(s):
    """Escape a string for use in TOML."""
    return s.replace('\\', '\\\\').replace('"', '\\"')

def generate_algorithm_page(slug, alg, base_path=''):
    """Generate Zola markdown content for an algorithm page."""
    content = []

    # Escape title for TOML
    safe_title = escape_toml_string(alg["name"])
    safe_category = escape_toml_string(alg["category"])

    # Front matter
    content.append('+++')
    content.append(f'title = "{safe_title}"')
    content.append(f'description = "Algorithm documentation and implementations"')
    content.append(f'template = "algorithm.html"')
    content.append('')
    content.append('[extra]')
    content.append(f'category = "{safe_category}"')
    content.append(f'implementation_count = {len(alg["files"])}')
    content.append('+++')
    content.append('')

    # Main description
    if alg['description']:
        content.append(alg['description'])
        content.append('')

    # Mathematical formulation
    if alg['math']:
        content.append('## Mathematical Formulation')
        content.append('')
        content.append('<div class="math-block">')
        content.append('')
        content.append(alg['math'])
        content.append('')
        content.append('</div>')
        content.append('')

    # Complexity
    if alg['complexity']:
        content.append('## Complexity')
        content.append('')
        content.append(alg['complexity'])
        content.append('')

    # Implementations
    content.append('## Implementations')
    content.append('')

    # Group by library
    by_library = defaultdict(list)
    for f in alg['files']:
        by_library[f['library']].append(f)

    for lib, files in sorted(by_library.items()):
        content.append(f'### {lib}')
        content.append('')
        for f in files:
            link = f'{base_path}/browser/?library={lib}'
            content.append(f'- **[{f["filename"]}]({link})** - {f["brief"]}')
        content.append('')

    # References
    if alg['refs']:
        content.append('## References')
        content.append('')
        for ref in alg['refs']:
            # Clean up reference text
            ref = ref.strip()
            content.append(f'- {ref}')
        content.append('')

    return '\n'.join(content)

def generate_index_page(algorithms, base_path=''):
    """Generate the algorithms index page."""
    content = []

    content.append('+++')
    content.append('title = "Algorithms"')
    content.append('description = "Cross-reference of algorithms implemented in COIN-OR"')
    content.append('template = "algorithms-index.html"')
    content.append('sort_by = "title"')
    content.append('+++')
    content.append('')
    content.append('# Algorithm Index')
    content.append('')
    content.append('This page provides a cross-reference of algorithms documented across the COIN-OR libraries.')
    content.append('Click any algorithm to see its mathematical formulation, complexity analysis, and all implementations.')
    content.append('')

    # Group by category
    by_category = defaultdict(list)
    for slug, alg in algorithms.items():
        by_category[alg['category']].append((slug, alg))

    # Sort categories
    category_order = [
        'Presolve Reductions',
        'Matrix Factorization',
        'Simplex Method',
        'Interior Point Methods',
        'Branch and Bound',
        'Primal Heuristics',
        'Conflict Analysis',
        'Data Structures',
        'File I/O',
        'Other Algorithms'
    ]

    for category in category_order:
        if category not in by_category:
            continue

        algs = by_category[category]
        content.append(f'## {category}')
        content.append('')

        for slug, alg in sorted(algs, key=lambda x: x[1]['name']):
            impl_count = len(alg['files'])
            libs = set(f['library'] for f in alg['files'])
            libs_str = ', '.join(sorted(libs)[:3])
            if len(libs) > 3:
                libs_str += f' +{len(libs)-3}'

            content.append(f'- **[{alg["name"]}]({base_path}/algorithms/{slug}/)** ({impl_count} impl) - {libs_str}')
        content.append('')

    return '\n'.join(content)

def main():
    base_dir = Path(__file__).parent.parent
    json_path = base_dir / 'site' / 'static' / 'api' / 'files.json'
    output_dir = base_dir / 'site' / 'content' / 'algorithms'
    config_path = base_dir / 'site' / 'config.toml'

    # Read base path from config for proper link generation
    base_path = get_base_path(config_path)
    print(f"Using base path: '{base_path}'")

    print(f"Reading from {json_path}")
    algorithms = build_algorithm_index(json_path)

    print(f"Found {len(algorithms)} unique algorithms")

    # Create output directory
    output_dir.mkdir(parents=True, exist_ok=True)

    # Generate index page
    index_content = generate_index_page(algorithms, base_path)
    index_path = output_dir / '_index.md'
    with open(index_path, 'w') as f:
        f.write(index_content)
    print(f"Generated {index_path}")

    # Generate individual algorithm pages
    for slug, alg in algorithms.items():
        page_content = generate_algorithm_page(slug, alg, base_path)
        page_path = output_dir / f'{slug}.md'
        with open(page_path, 'w') as f:
            f.write(page_content)

    print(f"Generated {len(algorithms)} algorithm pages in {output_dir}")

    # Summary by category
    print("\nAlgorithms by category:")
    by_category = defaultdict(int)
    for alg in algorithms.values():
        by_category[alg['category']] += 1
    for cat, count in sorted(by_category.items(), key=lambda x: -x[1]):
        print(f"  {cat}: {count}")

if __name__ == '__main__':
    main()
