#!/usr/bin/env python3
"""
Build knowledge graph JSON from seed file and annotations.

Reads:
  - data/concepts-seed.yaml (hand-authored concepts)
  - site/static/api/annotations.json (source annotations)

Writes:
  - site/static/api/knowledge-graph/index.json (full graph)
  - site/static/api/knowledge-graph/categories.json (grouped concepts)
"""

import json
import yaml
from pathlib import Path
from collections import defaultdict


def load_seed(path: Path) -> list[dict]:
    """Load concepts from YAML seed file."""
    with open(path) as f:
        data = yaml.safe_load(f)
    return data.get('concepts', [])


def load_annotations(path: Path) -> dict:
    """Load annotations JSON."""
    if not path.exists():
        return {}
    with open(path) as f:
        return json.load(f)


def extract_implementations(annotations: dict) -> dict[str, list[dict]]:
    """Extract concept -> implementation mappings from annotations.

    Returns dict mapping concept keywords to list of implementing files.
    """
    implementations = defaultdict(list)

    # Keywords to look for in algorithm/math fields
    # More comprehensive mapping with multiple patterns per concept
    keyword_map = {
        # Simplex variants
        'simplex': 'simplex_method',
        'dual simplex': 'dual_simplex',
        'primal simplex': 'primal_simplex',
        'steepest edge': 'simplex_method',
        'pivot': 'simplex_method',
        'reduced cost': 'simplex_method',
        'ratio test': 'simplex_method',

        # Interior point
        'interior point': 'interior_point_method',
        'ipm': 'interior_point_method',
        'barrier': 'interior_point_method',
        'central path': 'interior_point_method',
        'log barrier': 'barrier_function',
        'barrier function': 'barrier_function',

        # Branch and bound
        'branch and bound': 'branch_and_bound',
        'branch-and-bound': 'branch_and_bound',
        'b&b': 'branch_and_bound',
        'search tree': 'branch_and_bound',
        'node selection': 'node_selection',
        'best first': 'node_selection',
        'depth first': 'node_selection',
        'spatial b&b': 'spatial_branch_and_bound',
        'spatial branch': 'spatial_branch_and_bound',
        'global optimization': 'spatial_branch_and_bound',

        # Branching
        'branching': 'branching',
        'variable selection': 'branching',
        'strong branching': 'branching',
        'pseudocost': 'branching',
        'reliability branching': 'branching',

        # Cutting planes
        'cutting plane': 'cutting_planes',
        'cut generator': 'cutting_planes',
        'valid inequality': 'cutting_planes',
        'gomory': 'Gomory_cuts',
        'mir cut': 'MIR_cuts',
        'mixed integer rounding': 'MIR_cuts',
        'clique cut': 'cutting_planes',
        'knapsack cover': 'cutting_planes',
        'lift and project': 'cutting_planes',
        'disjunctive cut': 'cutting_planes',

        # MINLP
        'outer approximation': 'outer_approximation',
        'oa cut': 'outer_approximation',
        'linearization': 'outer_approximation',
        'nlp subproblem': 'outer_approximation',
        'convex minlp': 'mixed_integer_nonlinear_programming',
        'minlp': 'mixed_integer_nonlinear_programming',

        # Optimality / theory
        'kkt': 'KKT_conditions',
        'karush': 'KKT_conditions',
        'kuhn-tucker': 'KKT_conditions',
        'stationarity': 'KKT_conditions',
        'complementarity': 'complementary_slackness',
        'complementary slackness': 'complementary_slackness',
        'lagrangian': 'Lagrangian',
        'lagrange multiplier': 'Lagrangian',
        'dual': 'LP_duality',
        'duality': 'LP_duality',
        'reduced cost': 'LP_duality',

        # Factorization
        'lu factor': 'LU_factorization',
        'factorization': 'LU_factorization',
        'basis update': 'LU_factorization',
        'eta file': 'LU_factorization',
        'refactorization': 'LU_factorization',
        'ftran': 'LU_factorization',
        'btran': 'LU_factorization',

        # Presolve
        'presolve': 'presolve',
        'preprocessing': 'presolve',
        'presolver': 'presolve',
        'probing': 'presolve',
        'implied bound': 'presolve',
        'redundant constraint': 'presolve',

        # Warm start
        'warm start': 'warm_start',
        'hot start': 'warm_start',
        'basis': 'basis',
        'basic solution': 'basis',
        'basic variable': 'basis',

        # Bound tightening
        'bound tightening': 'bound_tightening',
        'domain reduction': 'bound_tightening',
        'fbbt': 'FBBT',
        'feasibility based': 'FBBT',
        'obbt': 'bound_tightening',
        'optimization based': 'bound_tightening',

        # Convexification
        'mccormick': 'McCormick_envelopes',
        'convexification': 'convexification',
        'convex envelope': 'convexification',
        'convex relaxation': 'convexification',
        'underestimator': 'convexification',
        'overestimator': 'convexification',

        # Newton / Hessian
        'newton': 'newton_method',
        'newton-raphson': 'newton_method',
        'hessian': 'hessian',
        'second derivative': 'hessian',

        # Automatic differentiation
        'automatic differentiation': 'automatic_differentiation',
        'autodiff': 'automatic_differentiation',
        'algorithmic differentiation': 'automatic_differentiation',
        'tape': 'automatic_differentiation',
        'adjoint': 'automatic_differentiation',

        # Heuristics
        'feasibility pump': 'feasibility_pump',
        'rounding': 'feasibility_pump',
        'diving': 'feasibility_pump',
        'rins': 'feasibility_pump',
        'local branching': 'feasibility_pump',

        # QP
        'active set': 'active_set_method',
        'working set': 'active_set_method',
        'quadratic program': 'quadratic_programming',
        'qp': 'quadratic_programming',

        # Problem classes
        'linear program': 'linear_programming',
        'lp solver': 'linear_programming',
        'nonlinear program': 'nonlinear_programming',
        'nlp solver': 'nonlinear_programming',
        'mixed integer': 'mixed_integer_programming',
        'mip solver': 'mixed_integer_programming',

        # Structure
        'sparse': 'sparsity',
        'sparsity': 'sparsity',
        'convex': 'convexity',
        'convexity': 'convexity',
        'relaxation': 'LP_relaxation',
        'lp relaxation': 'LP_relaxation',
    }

    # Track seen (concept, library, file) to avoid duplicates
    seen = set()

    for layer_name, layer in annotations.get('layers', {}).items():
        for lib_name, lib in layer.get('libraries', {}).items():
            for file_path, file_data in lib.get('files', {}).items():
                text = (file_data.get('algorithm', '') + ' ' +
                       file_data.get('math', '')).lower()

                for keyword, concept_id in keyword_map.items():
                    if keyword in text:
                        key = (concept_id, lib_name, file_path)
                        if key not in seen:
                            seen.add(key)
                            implementations[concept_id].append({
                                'library': lib_name,
                                'file': file_path,
                                'brief': file_data.get('brief', ''),
                            })

    return dict(implementations)


def build_graph(concepts: list[dict], implementations: dict) -> dict:
    """Build the full knowledge graph."""

    # Index concepts by ID
    concept_index = {c['id']: c for c in concepts}

    # Collect all relationships (both directions for some)
    all_relationships = []

    for concept in concepts:
        concept_id = concept['id']

        for rel in concept.get('relationships', []):
            rel_type = rel['type']
            target = rel['target']

            all_relationships.append({
                'from': concept_id,
                'to': target,
                'type': rel_type,
            })

            # Add reverse relationships for bidirectional types
            if rel_type == 'alternative_to':
                all_relationships.append({
                    'from': target,
                    'to': concept_id,
                    'type': rel_type,
                })

    # Add implementation relationships from annotations
    for concept_id, impls in implementations.items():
        for impl in impls:
            file_ref = f"{impl['library']}/{impl['file']}"
            all_relationships.append({
                'from': concept_id,
                'to': file_ref,
                'type': 'implemented_in',
                'meta': {'brief': impl['brief']},
            })

    # Build output structure
    graph = {
        'version': '1.0',
        'concepts': {},
        'relationships': all_relationships,
        'stats': {
            'concept_count': len(concepts),
            'relationship_count': len(all_relationships),
        }
    }

    # Process each concept
    for concept in concepts:
        cid = concept['id']

        # Clean up for JSON output
        entry = {
            'id': cid,
            'name': concept['name'],
            'category': concept['category'],
            'definition': concept.get('definition', '').strip(),
            'intuition': concept.get('intuition', '').strip(),
        }

        if concept.get('aliases'):
            entry['aliases'] = concept['aliases']

        if concept.get('key_equations'):
            entry['key_equations'] = concept['key_equations']

        # Gather relationships for this concept
        entry['relationships'] = {
            'requires': [],
            'solves': [],
            'contains': [],
            'generalizes': [],
            'alternative_to': [],
            'implemented_in': [],
        }

        for rel in all_relationships:
            if rel['from'] == cid:
                rel_type = rel['type']
                if rel_type in entry['relationships']:
                    target_info = {'id': rel['to']}
                    if rel.get('meta'):
                        target_info['meta'] = rel['meta']
                    entry['relationships'][rel_type].append(target_info)

        # Remove empty relationship lists
        entry['relationships'] = {
            k: v for k, v in entry['relationships'].items() if v
        }

        graph['concepts'][cid] = entry

    return graph


def build_categories(concepts: list[dict]) -> dict:
    """Group concepts by category."""
    categories = defaultdict(list)

    for concept in concepts:
        cat = concept['category']
        categories[cat].append({
            'id': concept['id'],
            'name': concept['name'],
            'brief': concept.get('definition', '')[:100] + '...' if concept.get('definition') else '',
        })

    return {
        'categories': dict(categories),
        'category_descriptions': {
            'problem_class': 'Types of optimization problems (LP, QP, NLP, MIP, MINLP)',
            'algorithm': 'Solution methods and procedures',
            'optimality': 'Conditions, theorems, and duality theory',
            'structure': 'Mathematical properties and structures',
            'technique': 'Implementation techniques and computational methods',
        }
    }


def main():
    base = Path(__file__).parent.parent

    # Load inputs
    seed_path = base / 'data/concepts-seed.yaml'
    annotations_path = base / 'site/static/api/annotations.json'

    print(f"Loading seed from {seed_path}")
    concepts = load_seed(seed_path)
    print(f"  Loaded {len(concepts)} concepts")

    print(f"Loading annotations from {annotations_path}")
    annotations = load_annotations(annotations_path)

    print("Extracting implementations from annotations...")
    implementations = extract_implementations(annotations)
    print(f"  Found implementations for {len(implementations)} concepts")

    # Build outputs
    print("Building knowledge graph...")
    graph = build_graph(concepts, implementations)

    print("Building category index...")
    categories = build_categories(concepts)

    # Write outputs
    out_dir = base / 'site/static/api/knowledge-graph'
    out_dir.mkdir(parents=True, exist_ok=True)

    index_path = out_dir / 'index.json'
    print(f"Writing {index_path}")
    with open(index_path, 'w') as f:
        json.dump(graph, f, indent=2)

    categories_path = out_dir / 'categories.json'
    print(f"Writing {categories_path}")
    with open(categories_path, 'w') as f:
        json.dump(categories, f, indent=2)

    print(f"\nDone! Generated:")
    print(f"  {graph['stats']['concept_count']} concepts")
    print(f"  {graph['stats']['relationship_count']} relationships")


if __name__ == '__main__':
    main()
