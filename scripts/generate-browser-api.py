#!/usr/bin/env python3
"""
Generate browser API files from annotations.json.

Creates:
- source-tree.json: Hierarchical tree of layers/libraries/files for the tree view
- class-briefs.json: Brief descriptions and metadata for all documented classes
- api/{lib}/{class}.json: Individual class detail files

This should be run after annotations.json is updated to keep the browser in sync.
"""

import json
import os
import re
from pathlib import Path
from collections import defaultdict

BASE_DIR = Path(__file__).parent.parent
ANNOTATIONS_PATH = BASE_DIR / 'site' / 'static' / 'api' / 'annotations.json'
OUTPUT_DIR = BASE_DIR / 'site' / 'static' / 'api'

# Layer metadata
LAYER_INFO = {
    'layer-0': {'name': 'Layer 0: Foundation', 'desc': 'Core utilities, sparse linear algebra'},
    'layer-1': {'name': 'Layer 1: LP & Cuts', 'desc': 'Linear programming and cut generation'},
    'layer-2': {'name': 'Layer 2: MIP & NLP', 'desc': 'Mixed-integer and nonlinear programming'},
    'layer-3': {'name': 'Layer 3: MINLP', 'desc': 'Mixed-integer nonlinear programming'},
    'layer-4': {'name': 'Layer 4: Applications', 'desc': 'Application-level solvers'},
}

def get_filename_base(path):
    """Extract base filename without extension."""
    filename = Path(path).stem
    # Handle .hpp files
    if filename.endswith('.hpp') or filename.endswith('.h'):
        filename = Path(filename).stem
    return filename

def generate_source_tree(annotations):
    """Generate the hierarchical source tree for the browser."""
    tree = {
        'name': 'COIN-OR',
        'children': []
    }

    for layer_id in ['layer-0', 'layer-1', 'layer-2', 'layer-3', 'layer-4']:
        layer_data = annotations['layers'].get(layer_id, {})
        layer_info = LAYER_INFO.get(layer_id, {'name': layer_id, 'desc': ''})

        layer_node = {
            'name': layer_info['name'],
            'id': layer_id,
            'desc': layer_info['desc'],
            'children': []
        }

        for lib_name, lib_data in layer_data.get('libraries', {}).items():
            # Get unique file base names
            files = set()
            for file_path in lib_data.get('files', {}).keys():
                base = get_filename_base(file_path)
                files.add(base)

            lib_node = {
                'name': lib_name,
                'id': f'{layer_id}/{lib_name}',
                'children': [],
                'files': sorted(files),
                'desc': lib_data.get('description', '')
            }
            layer_node['children'].append(lib_node)

        # Sort libraries by name
        layer_node['children'].sort(key=lambda x: x['name'])
        tree['children'].append(layer_node)

    return tree

def generate_class_briefs(annotations):
    """Generate brief descriptions for all classes."""
    briefs = {}

    for layer_id, layer_data in annotations['layers'].items():
        for lib_name, lib_data in layer_data.get('libraries', {}).items():
            for file_path, file_data in lib_data.get('files', {}).items():
                filename = get_filename_base(file_path)

                # Count algorithms (files with @algorithm annotation)
                has_algorithm = bool(file_data.get('algorithm'))

                # Extract class info
                brief = file_data.get('brief', '')

                # For each class/file, store its metadata
                briefs[filename] = {
                    'brief': brief,
                    'file': filename,
                    'library': lib_name,
                    'layer': layer_id,
                    'header': file_path,
                    'algorithms': 1 if has_algorithm else 0,
                    'methods': 0,  # Would need to parse for method count
                    'has_pass2': file_data.get('has_pass2', False)
                }

    return briefs

def generate_class_files(annotations):
    """Generate individual class detail JSON files."""
    for layer_id, layer_data in annotations['layers'].items():
        for lib_name, lib_data in layer_data.get('libraries', {}).items():
            lib_slug = lib_name.lower()
            lib_dir = OUTPUT_DIR / lib_slug
            lib_dir.mkdir(exist_ok=True)

            for file_path, file_data in lib_data.get('files', {}).items():
                filename = get_filename_base(file_path)
                class_slug = filename.lower()

                # Build class detail structure
                class_detail = {
                    'name': filename,
                    'library': lib_name,
                    'layer': layer_id,
                    'header': file_path,
                    'brief': file_data.get('brief', ''),
                    'algorithms': [],
                    'methods': []
                }

                # Add algorithm if present
                if file_data.get('algorithm'):
                    algo = {
                        'name': file_data.get('algorithm', ''),
                        'math': file_data.get('math', ''),
                        'complexity': file_data.get('complexity', ''),
                        'ref': file_data.get('ref', '')
                    }
                    class_detail['algorithms'].append(algo)

                # Add see-also references
                if file_data.get('see'):
                    class_detail['see'] = file_data.get('see')

                # Write class file
                class_file = lib_dir / f'{class_slug}.json'
                with open(class_file, 'w') as f:
                    json.dump(class_detail, f, indent=2)

def generate_library_indexes(annotations):
    """Generate library index files."""
    for layer_id, layer_data in annotations['layers'].items():
        for lib_name, lib_data in layer_data.get('libraries', {}).items():
            lib_slug = lib_name.lower()
            lib_dir = OUTPUT_DIR / lib_slug
            lib_dir.mkdir(exist_ok=True)

            classes = []
            for file_path, file_data in lib_data.get('files', {}).items():
                filename = get_filename_base(file_path)
                classes.append({
                    'name': filename,
                    'brief': file_data.get('brief', ''),
                    'has_algorithm': bool(file_data.get('algorithm'))
                })

            index = {
                'library': lib_name,
                'layer': layer_id,
                'classes': sorted(classes, key=lambda x: x['name'])
            }

            index_file = lib_dir / 'index.json'
            with open(index_file, 'w') as f:
                json.dump(index, f, indent=2)

def main():
    print(f"Loading annotations from {ANNOTATIONS_PATH}")
    with open(ANNOTATIONS_PATH) as f:
        annotations = json.load(f)

    print(f"Found {annotations['stats']['total_files']} files across {annotations['stats']['total_libraries']} libraries")

    # Generate source tree
    print("\nGenerating source-tree.json...")
    tree = generate_source_tree(annotations)
    with open(OUTPUT_DIR / 'source-tree.json', 'w') as f:
        json.dump(tree, f, indent=2)

    # Generate class briefs
    print("Generating class-briefs.json...")
    briefs = generate_class_briefs(annotations)
    with open(OUTPUT_DIR / 'class-briefs.json', 'w') as f:
        json.dump(briefs, f, indent=2)
    print(f"  Generated briefs for {len(briefs)} classes")

    # Generate library indexes
    print("Generating library index files...")
    generate_library_indexes(annotations)

    # Generate individual class files
    print("Generating individual class files...")
    generate_class_files(annotations)

    print("\nDone! Browser API files regenerated.")

if __name__ == '__main__':
    main()
