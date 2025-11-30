#!/usr/bin/env python3
"""
Transform Doxygen XML output to JSON + Markdown for Zola.

Usage:
    python3 transform-doxygen.py build/doxygen/xml site/content site/static/api

This script parses Doxygen XML and generates:
- JSON files in site/static/api/ for machine consumption
- Markdown files in site/content/ for Zola rendering
"""

import argparse
import json
import os
import re
import sys
from pathlib import Path
from xml.etree import ElementTree as ET
from dataclasses import dataclass, field, asdict
from typing import Optional

# Layer mapping based on directory structure
LAYER_MAP = {
    'CoinUtils': 0,
    'Osi': 1,
    'Clp': 1,
    'Cgl': 1,
    'Cbc': 2,
    'Ipopt': 2,
    'Bonmin': 3,
    'Couenne': 3,
    'SHOT': 4,
    'OS': 4,
}


@dataclass
class Parameter:
    name: str
    type: str
    description: str = ""
    default: str = ""


@dataclass
class Method:
    name: str
    brief: str = ""
    detailed: str = ""
    return_type: str = ""
    return_desc: str = ""
    parameters: list = field(default_factory=list)
    source_file: str = ""
    source_line: int = 0
    source_code: str = ""
    algorithm: str = ""
    complexity: str = ""
    math: str = ""
    refs: list = field(default_factory=list)
    access: str = "public"


@dataclass
class ClassDoc:
    name: str
    qualified_name: str
    brief: str = ""
    detailed: str = ""
    header_file: str = ""
    source_file: str = ""
    library: str = ""
    layer: int = 0
    algorithms: list = field(default_factory=list)
    base_classes: list = field(default_factory=list)
    derived_classes: list = field(default_factory=list)
    methods: list = field(default_factory=list)
    members: list = field(default_factory=list)
    source_code: str = ""


def extract_text(elem, default=""):
    """Extract text content from an XML element, handling nested elements."""
    if elem is None:
        return default

    parts = []
    if elem.text:
        parts.append(elem.text)

    for child in elem:
        # Handle special elements
        if child.tag == 'ref':
            parts.append(child.text or "")
        elif child.tag == 'computeroutput':
            parts.append(f"`{child.text or ''}`")
        elif child.tag == 'formula':
            # LaTeX formula
            parts.append(f"${child.text or ''}$")
        elif child.tag == 'para':
            parts.append(extract_text(child))
        elif child.tag in ('simplesect', 'parameterlist'):
            # Skip these, handled separately
            pass
        else:
            parts.append(extract_text(child))

        if child.tail:
            parts.append(child.tail)

    return ''.join(parts).strip()


def extract_custom_sections(detailed_elem):
    """Extract @algorithm, @complexity, @math, @ref from detailed description."""
    result = {
        'algorithm': '',
        'complexity': '',
        'math': '',
        'refs': []
    }

    if detailed_elem is None:
        return result

    for para in detailed_elem.findall('.//para'):
        text = extract_text(para)

        # Check for custom section markers
        for simplesect in para.findall('simplesect'):
            kind = simplesect.get('kind', '')
            content = extract_text(simplesect)

            if 'Algorithm' in content or kind == 'par':
                title = simplesect.find('title')
                if title is not None and 'Algorithm' in (title.text or ''):
                    result['algorithm'] = extract_text(simplesect.find('para'))
                elif title is not None and 'Complexity' in (title.text or ''):
                    result['complexity'] = extract_text(simplesect.find('para'))
                elif title is not None and 'Math' in (title.text or ''):
                    result['math'] = extract_text(simplesect.find('para'))
                elif title is not None and 'Reference' in (title.text or ''):
                    ref_text = extract_text(simplesect.find('para'))
                    if ref_text:
                        result['refs'].append(ref_text)

        # Also look for inline patterns like @algorithm in the text
        if '@algorithm' in text.lower() or 'algorithm:' in text.lower():
            result['algorithm'] = text
        elif '@complexity' in text.lower() or 'complexity:' in text.lower():
            result['complexity'] = text
        elif '@math' in text.lower():
            result['math'] = text

    return result


def parse_memberdef(memberdef, compound_name):
    """Parse a memberdef element (function/method)."""
    name = memberdef.findtext('name', '')
    kind = memberdef.get('kind', '')

    if kind != 'function':
        return None

    method = Method(name=name)
    method.brief = extract_text(memberdef.find('briefdescription'))
    method.detailed = extract_text(memberdef.find('detaileddescription'))
    method.return_type = extract_text(memberdef.find('type'))
    method.access = memberdef.get('prot', 'public')

    # Location info
    location = memberdef.find('location')
    if location is not None:
        method.source_file = location.get('file', '')
        method.source_line = int(location.get('line', 0))

    # Parameters
    for param in memberdef.findall('param'):
        p = Parameter(
            name=param.findtext('declname', ''),
            type=extract_text(param.find('type')),
            default=param.findtext('defval', '')
        )
        method.parameters.append(p)

    # Parameter descriptions from detailed
    param_list = memberdef.find('.//parameterlist')
    if param_list is not None:
        for item in param_list.findall('parameteritem'):
            pname = item.findtext('.//parametername', '')
            pdesc = extract_text(item.find('.//parameterdescription'))
            for p in method.parameters:
                if p.name == pname:
                    p.description = pdesc

    # Return description
    return_sect = memberdef.find('.//simplesect[@kind="return"]')
    if return_sect is not None:
        method.return_desc = extract_text(return_sect)

    # Custom sections
    custom = extract_custom_sections(memberdef.find('detaileddescription'))
    method.algorithm = custom['algorithm']
    method.complexity = custom['complexity']
    method.math = custom['math']
    method.refs = custom['refs']

    # Source code
    inbody = memberdef.find('inbodydescription')
    if inbody is not None:
        method.source_code = extract_text(inbody)

    return method


def parse_compound(xml_path: Path) -> Optional[ClassDoc]:
    """Parse a compound XML file (class, struct, etc.)."""
    try:
        tree = ET.parse(xml_path)
        root = tree.getroot()
    except ET.ParseError as e:
        print(f"Warning: Could not parse {xml_path}: {e}", file=sys.stderr)
        return None

    compounddef = root.find('compounddef')
    if compounddef is None:
        return None

    kind = compounddef.get('kind', '')
    if kind not in ('class', 'struct'):
        return None

    name = compounddef.findtext('compoundname', '')

    doc = ClassDoc(
        name=name.split('::')[-1],
        qualified_name=name
    )

    doc.brief = extract_text(compounddef.find('briefdescription'))
    doc.detailed = extract_text(compounddef.find('detaileddescription'))

    # Location
    location = compounddef.find('location')
    if location is not None:
        doc.header_file = location.get('file', '')
        doc.source_file = location.get('bodyfile', doc.header_file)

    # Determine library and layer from file path
    if doc.header_file:
        for lib, layer in LAYER_MAP.items():
            if lib.lower() in doc.header_file.lower():
                doc.library = lib
                doc.layer = layer
                break

    # Base classes
    for base in compounddef.findall('basecompoundref'):
        doc.base_classes.append(extract_text(base))

    # Derived classes
    for derived in compounddef.findall('derivedcompoundref'):
        doc.derived_classes.append(extract_text(derived))

    # Methods
    for section in compounddef.findall('sectiondef'):
        for memberdef in section.findall('memberdef'):
            method = parse_memberdef(memberdef, name)
            if method:
                doc.methods.append(method)
                # Collect algorithms
                if method.algorithm:
                    doc.algorithms.append(method.algorithm)

    # Custom sections from class description
    custom = extract_custom_sections(compounddef.find('detaileddescription'))
    if custom['algorithm'] and custom['algorithm'] not in doc.algorithms:
        doc.algorithms.insert(0, custom['algorithm'])

    return doc


def generate_json(doc: ClassDoc, output_dir: Path):
    """Generate JSON API file for a class."""
    output_dir.mkdir(parents=True, exist_ok=True)

    # Convert to dict, handling nested dataclasses
    def to_dict(obj):
        if hasattr(obj, '__dataclass_fields__'):
            return {k: to_dict(v) for k, v in asdict(obj).items()}
        elif isinstance(obj, list):
            return [to_dict(i) for i in obj]
        return obj

    data = to_dict(doc)

    # Add metadata
    data['_schema_version'] = '1.0'
    data['_generator'] = 'transform-doxygen.py'

    # Organize by library
    lib_dir = output_dir / doc.library.lower() if doc.library else output_dir / 'unknown'
    lib_dir.mkdir(parents=True, exist_ok=True)

    output_file = lib_dir / f"{doc.name}.json"
    with open(output_file, 'w') as f:
        json.dump(data, f, indent=2)

    return output_file


def generate_markdown(doc: ClassDoc, output_dir: Path):
    """Generate Markdown file with YAML frontmatter for Zola."""
    # Determine output path
    lib_name = doc.library.lower() if doc.library else 'unknown'
    lib_dir = output_dir / 'libraries' / lib_name
    lib_dir.mkdir(parents=True, exist_ok=True)

    # Build frontmatter
    frontmatter = {
        'title': doc.name,
        'description': doc.brief or f"{doc.name} class documentation",
        'template': 'page.html',
    }

    if doc.algorithms:
        # Extract algorithm names for taxonomy
        algo_names = []
        for algo in doc.algorithms:
            # Try to extract algorithm name from description
            match = re.search(r'(\w+(?:\s+\w+)?)\s+(?:algorithm|method)', algo, re.I)
            if match:
                algo_names.append(match.group(1).lower().replace(' ', '-'))
        if algo_names:
            frontmatter['taxonomies'] = {'algorithms': algo_names}

    frontmatter['extra'] = {
        'layer': doc.layer,
        'library': doc.library,
        'header_file': doc.header_file,
        'api_url': f"/api/{lib_name}/{doc.name}.json"
    }

    # Build markdown content
    lines = [
        '+++',
    ]

    # Manual TOML generation for frontmatter
    for key, value in frontmatter.items():
        if key == 'taxonomies':
            lines.append('[taxonomies]')
            for tax_name, tax_values in value.items():
                lines.append(f'{tax_name} = {json.dumps(tax_values)}')
        elif key == 'extra':
            lines.append('[extra]')
            for k, v in value.items():
                if isinstance(v, str):
                    lines.append(f'{k} = "{v}"')
                else:
                    lines.append(f'{k} = {json.dumps(v)}')
        elif isinstance(value, str):
            lines.append(f'{key} = "{value}"')
        else:
            lines.append(f'{key} = {json.dumps(value)}')

    lines.append('+++')
    lines.append('')

    # Content
    if doc.brief:
        lines.append(doc.brief)
        lines.append('')

    # API link
    lines.append(f'<div class="api-link"><a href="/api/{lib_name}/{doc.name}.json">JSON API</a></div>')
    lines.append('')

    # Inheritance
    if doc.base_classes:
        lines.append('## Inheritance')
        lines.append('')
        lines.append(f'Inherits from: {", ".join(f"`{b}`" for b in doc.base_classes)}')
        lines.append('')

    if doc.derived_classes:
        lines.append(f'Derived classes: {", ".join(f"`{d}`" for d in doc.derived_classes)}')
        lines.append('')

    # Detailed description
    if doc.detailed:
        lines.append('## Description')
        lines.append('')
        lines.append(doc.detailed)
        lines.append('')

    # Algorithms
    if doc.algorithms:
        lines.append('## Algorithms')
        lines.append('')
        for algo in doc.algorithms:
            lines.append(f'<div class="algorithm-card">')
            lines.append(algo)
            lines.append('</div>')
            lines.append('')

    # Methods
    public_methods = [m for m in doc.methods if m.access == 'public']
    if public_methods:
        lines.append('## Public Methods')
        lines.append('')

        for method in public_methods:
            lines.append(f'### `{method.name}`')
            lines.append('')

            if method.brief:
                lines.append(method.brief)
                lines.append('')

            # Signature
            params_str = ', '.join(
                f"{p.type} {p.name}" + (f" = {p.default}" if p.default else "")
                for p in method.parameters
            )
            lines.append(f'```cpp')
            lines.append(f'{method.return_type} {method.name}({params_str})')
            lines.append('```')
            lines.append('')

            # Parameters
            if method.parameters:
                lines.append('**Parameters:**')
                lines.append('')
                for p in method.parameters:
                    desc = f" - {p.description}" if p.description else ""
                    lines.append(f'- `{p.name}` ({p.type}){desc}')
                lines.append('')

            # Return
            if method.return_desc:
                lines.append(f'**Returns:** {method.return_desc}')
                lines.append('')

            # Algorithm info
            if method.algorithm:
                lines.append('<div class="method-card">')
                lines.append(f'**Algorithm:** {method.algorithm}')
                if method.complexity:
                    lines.append(f'**Complexity:** {method.complexity}')
                if method.math:
                    lines.append(f'**Math:** {method.math}')
                lines.append('</div>')
                lines.append('')

            # References
            if method.refs:
                lines.append('**References:**')
                for ref in method.refs:
                    lines.append(f'- {ref}')
                lines.append('')

    # Source location
    if doc.header_file:
        lines.append('## Source')
        lines.append('')
        lines.append(f'Header: `{doc.header_file}`')
        if doc.source_file and doc.source_file != doc.header_file:
            lines.append(f'Implementation: `{doc.source_file}`')
        lines.append('')

    # Write file
    output_file = lib_dir / f"{doc.name}.md"
    with open(output_file, 'w') as f:
        f.write('\n'.join(lines))

    return output_file


def process_index(xml_dir: Path):
    """Process the Doxygen index.xml to find all compounds."""
    index_path = xml_dir / 'index.xml'
    if not index_path.exists():
        print(f"Error: {index_path} not found", file=sys.stderr)
        return []

    tree = ET.parse(index_path)
    root = tree.getroot()

    compounds = []
    for compound in root.findall('compound'):
        kind = compound.get('kind', '')
        if kind in ('class', 'struct'):
            refid = compound.get('refid', '')
            if refid:
                compounds.append(xml_dir / f"{refid}.xml")

    return compounds


def ensure_library_index(content_dir: Path, library: str, layer: int):
    """Ensure a library has an _index.md file."""
    lib_dir = content_dir / 'libraries' / library.lower()
    index_file = lib_dir / '_index.md'

    if not index_file.exists():
        lib_dir.mkdir(parents=True, exist_ok=True)
        content = f"""+++
title = "{library}"
description = "Layer {layer} - {library} documentation"
template = "section.html"
sort_by = "title"

[taxonomies]
layer = ["layer-{layer}"]
+++

{library} library documentation.
"""
        with open(index_file, 'w') as f:
            f.write(content)


def main():
    parser = argparse.ArgumentParser(description='Transform Doxygen XML to JSON + Markdown')
    parser.add_argument('xml_dir', help='Path to Doxygen XML output directory')
    parser.add_argument('content_dir', help='Path to Zola content directory')
    parser.add_argument('api_dir', help='Path to JSON API output directory')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')

    args = parser.parse_args()

    xml_dir = Path(args.xml_dir)
    content_dir = Path(args.content_dir)
    api_dir = Path(args.api_dir)

    if not xml_dir.exists():
        print(f"Error: XML directory {xml_dir} does not exist", file=sys.stderr)
        sys.exit(1)

    # Process all compounds
    compounds = process_index(xml_dir)
    print(f"Found {len(compounds)} classes/structs to process")

    libraries_seen = set()
    processed = 0

    for xml_file in compounds:
        if not xml_file.exists():
            if args.verbose:
                print(f"Warning: {xml_file} not found", file=sys.stderr)
            continue

        doc = parse_compound(xml_file)
        if doc is None:
            continue

        # Track libraries
        if doc.library:
            libraries_seen.add((doc.library, doc.layer))

        # Generate outputs
        json_file = generate_json(doc, api_dir)
        md_file = generate_markdown(doc, content_dir)

        if args.verbose:
            print(f"Generated: {json_file} and {md_file}")

        processed += 1

    # Ensure library indexes exist
    for library, layer in libraries_seen:
        ensure_library_index(content_dir, library, layer)

    print(f"Processed {processed} classes/structs")
    print(f"Libraries: {', '.join(lib for lib, _ in sorted(libraries_seen))}")


if __name__ == '__main__':
    main()
