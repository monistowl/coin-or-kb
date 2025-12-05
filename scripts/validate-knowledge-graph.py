#!/usr/bin/env python3
"""
Validate knowledge graph consistency.

Checks:
1. All relationship targets exist (no dangling references)
2. Required fields are present on concepts
3. Category assignments are valid
4. No circular requires dependencies
5. Algorithm guidance covers all algorithm concepts
6. Implementation references exist in annotations

Usage: python scripts/validate-knowledge-graph.py [--fix]
"""

import json
import yaml
import sys
from pathlib import Path
from collections import defaultdict


def load_data(base: Path) -> tuple[dict, dict, dict]:
    """Load knowledge graph, annotations, and guidance."""
    kg_path = base / 'site/static/api/knowledge-graph/index.json'
    ann_path = base / 'site/static/api/annotations.json'
    guidance_path = base / 'data/algorithm-guidance.yaml'

    with open(kg_path) as f:
        kg = json.load(f)

    ann = {}
    if ann_path.exists():
        with open(ann_path) as f:
            ann = json.load(f)

    guidance = {}
    if guidance_path.exists():
        with open(guidance_path) as f:
            guidance = yaml.safe_load(f)

    return kg, ann, guidance


def check_dangling_references(kg: dict) -> list[str]:
    """Check that all relationship targets exist."""
    errors = []
    concept_ids = set(kg['concepts'].keys())

    for rel in kg['relationships']:
        target = rel['to']
        # Skip file references (contain /)
        if '/' in target:
            continue
        if target not in concept_ids:
            errors.append(f"Dangling reference: {rel['from']} -> {target} ({rel['type']})")

    return errors


def check_required_fields(kg: dict) -> list[str]:
    """Check that concepts have required fields."""
    errors = []
    required = ['id', 'name', 'category']
    recommended = ['definition', 'intuition']

    for cid, concept in kg['concepts'].items():
        for field in required:
            if field not in concept:
                errors.append(f"Missing required field '{field}' on {cid}")

        for field in recommended:
            if field not in concept or not concept[field]:
                errors.append(f"Warning: Missing recommended field '{field}' on {cid}")

    return errors


def check_categories(kg: dict) -> list[str]:
    """Check that categories are valid."""
    errors = []
    valid_categories = {'problem_class', 'algorithm', 'optimality', 'structure', 'technique'}

    for cid, concept in kg['concepts'].items():
        cat = concept.get('category')
        if cat not in valid_categories:
            errors.append(f"Invalid category '{cat}' on {cid}")

    return errors


def check_circular_requires(kg: dict) -> list[str]:
    """Check for circular dependencies in requires relationships."""
    errors = []

    # Build requires graph
    requires = defaultdict(set)
    for rel in kg['relationships']:
        if rel['type'] == 'requires':
            requires[rel['from']].add(rel['to'])

    # DFS for cycles
    def has_cycle(node, visited, path):
        if node in path:
            return list(path) + [node]
        if node in visited:
            return None
        visited.add(node)
        path.add(node)
        for neighbor in requires.get(node, []):
            cycle = has_cycle(neighbor, visited, path)
            if cycle:
                return cycle
        path.remove(node)
        return None

    visited = set()
    for cid in kg['concepts']:
        if cid not in visited:
            cycle = has_cycle(cid, visited, set())
            if cycle:
                cycle_str = ' -> '.join(cycle)
                errors.append(f"Circular requires dependency: {cycle_str}")

    return errors


def check_guidance_coverage(kg: dict, guidance: dict) -> list[str]:
    """Check that all algorithms have guidance."""
    errors = []

    algorithm_concepts = {
        cid for cid, c in kg['concepts'].items()
        if c.get('category') == 'algorithm'
    }

    guidance_algos = set(guidance.get('algorithms', {}).keys())

    missing = algorithm_concepts - guidance_algos
    for cid in sorted(missing):
        errors.append(f"Warning: Algorithm '{cid}' has no guidance entry")

    return errors


def check_implementation_refs(kg: dict, annotations: dict) -> list[str]:
    """Check that implementation references point to annotated files.

    Note: Implementation refs are aspirational - they point to where code
    should be found, even if not yet annotated. Returns warnings, not errors.
    """
    errors = []

    # Build set of annotated files
    annotated = set()
    for layer in annotations.get('layers', {}).values():
        for lib_name, lib in layer.get('libraries', {}).items():
            for file_path in lib.get('files', {}):
                annotated.add(f"{lib_name}/{file_path}")

    # Check implementation refs (as warnings since these are aspirational)
    for rel in kg['relationships']:
        if rel['type'] == 'implemented_in':
            target = rel['to']
            if target not in annotated:
                errors.append(f"Warning: Implementation ref not yet annotated: {rel['from']} -> {target}")

    return errors


def check_solves_consistency(kg: dict) -> list[str]:
    """Check that 'solves' relationships are from algorithms to problem_classes."""
    errors = []

    for rel in kg['relationships']:
        if rel['type'] == 'solves':
            src = rel['from']
            tgt = rel['to']

            src_concept = kg['concepts'].get(src, {})
            tgt_concept = kg['concepts'].get(tgt, {})

            if src_concept.get('category') != 'algorithm':
                errors.append(f"'solves' source should be algorithm: {src} ({src_concept.get('category')})")

            if tgt_concept.get('category') != 'problem_class':
                errors.append(f"'solves' target should be problem_class: {tgt} ({tgt_concept.get('category')})")

    return errors


def main():
    base = Path(__file__).parent.parent

    print("Loading data...")
    kg, annotations, guidance = load_data(base)

    print(f"Knowledge graph: {len(kg['concepts'])} concepts, {len(kg['relationships'])} relationships")

    all_errors = []
    warnings = []

    # Run all checks
    checks = [
        ("Dangling references", check_dangling_references(kg)),
        ("Required fields", check_required_fields(kg)),
        ("Categories", check_categories(kg)),
        ("Circular requires", check_circular_requires(kg)),
        ("Guidance coverage", check_guidance_coverage(kg, guidance)),
        ("Implementation refs", check_implementation_refs(kg, annotations)),
        ("Solves consistency", check_solves_consistency(kg)),
    ]

    for name, errors in checks:
        real_errors = [e for e in errors if not e.startswith("Warning:")]
        warns = [e for e in errors if e.startswith("Warning:")]

        if real_errors:
            print(f"\n❌ {name}: {len(real_errors)} errors")
            for e in real_errors[:10]:  # Limit output
                print(f"   {e}")
            if len(real_errors) > 10:
                print(f"   ... and {len(real_errors) - 10} more")
            all_errors.extend(real_errors)
        else:
            print(f"✓ {name}: OK")

        if warns:
            warnings.extend(warns)

    # Summary
    print(f"\n{'='*50}")
    print(f"Summary: {len(all_errors)} errors, {len(warnings)} warnings")

    if warnings and '--verbose' in sys.argv:
        print(f"\nWarnings:")
        for w in warnings[:20]:
            print(f"  {w}")
        if len(warnings) > 20:
            print(f"  ... and {len(warnings) - 20} more")

    if all_errors:
        sys.exit(1)
    else:
        print("\n✓ Knowledge graph is valid!")
        sys.exit(0)


if __name__ == '__main__':
    main()
