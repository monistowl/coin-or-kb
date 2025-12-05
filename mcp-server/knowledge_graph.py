"""
Knowledge Graph query module for COIN-OR Knowledge Base.

Provides graph traversal and concept exploration functions.
"""

import json
import yaml
from pathlib import Path
from collections import deque


class KnowledgeGraph:
    """Query interface for the mathematical concept knowledge graph."""

    def __init__(self, json_path: Path = None):
        if json_path is None:
            # Try common locations
            for p in [
                Path(__file__).parent.parent / 'site/static/api/knowledge-graph/index.json',
                Path('site/static/api/knowledge-graph/index.json'),
                Path('knowledge-graph/index.json'),
            ]:
                if p.exists():
                    json_path = p
                    break

        self.data = {'concepts': {}, 'relationships': []}
        self.categories_data = {}

        if json_path and json_path.exists():
            with open(json_path) as f:
                self.data = json.load(f)

            # Load categories too
            cat_path = json_path.parent / 'categories.json'
            if cat_path.exists():
                with open(cat_path) as f:
                    self.categories_data = json.load(f)

        # Load algorithm guidance
        self.guidance = {}
        for guidance_path in [
            Path(__file__).parent.parent / 'data/algorithm-guidance.yaml',
            Path('data/algorithm-guidance.yaml'),
        ]:
            if guidance_path.exists():
                with open(guidance_path) as f:
                    self.guidance = yaml.safe_load(f)
                break

        # Build reverse index for faster lookups
        self._build_indices()

    def _build_indices(self):
        """Build indices for efficient querying."""
        # Index: concept_id -> list of relationships where it's the source
        self.outgoing = {}
        # Index: concept_id -> list of relationships where it's the target
        self.incoming = {}

        for rel in self.data.get('relationships', []):
            src = rel['from']
            tgt = rel['to']

            if src not in self.outgoing:
                self.outgoing[src] = []
            self.outgoing[src].append(rel)

            if tgt not in self.incoming:
                self.incoming[tgt] = []
            self.incoming[tgt].append(rel)

    def explore_concept(self, concept_id: str) -> dict:
        """Get concept details plus immediate relationships.

        Returns the concept definition, intuition, and all direct relationships
        including what it requires, solves, contains, etc.
        """
        concept = self.data['concepts'].get(concept_id)
        if not concept:
            # Try fuzzy match
            for cid, c in self.data['concepts'].items():
                if concept_id.lower() in cid.lower():
                    concept = c
                    concept_id = cid
                    break
                if c.get('aliases'):
                    for alias in c['aliases']:
                        if concept_id.lower() == alias.lower():
                            concept = c
                            concept_id = cid
                            break

        if not concept:
            return {'error': f'Concept "{concept_id}" not found'}

        # Enrich with incoming relationships (what depends on this)
        result = dict(concept)
        result['used_by'] = []

        for rel in self.incoming.get(concept_id, []):
            if rel['type'] == 'requires':
                result['used_by'].append({
                    'id': rel['from'],
                    'name': self.data['concepts'].get(rel['from'], {}).get('name', rel['from']),
                })

        return result

    def find_path(self, from_concept: str, to_concept: str, max_depth: int = 5) -> dict:
        """Find relationship chain between two concepts.

        Uses BFS to find shortest path through the relationship graph.
        """
        if from_concept not in self.data['concepts']:
            return {'error': f'Source concept "{from_concept}" not found'}
        if to_concept not in self.data['concepts']:
            return {'error': f'Target concept "{to_concept}" not found'}

        # BFS
        queue = deque([(from_concept, [])])
        visited = {from_concept}

        while queue:
            current, path = queue.popleft()

            if len(path) >= max_depth:
                continue

            for rel in self.outgoing.get(current, []):
                target = rel['to']

                # Skip file references for pathfinding
                if '/' in target:
                    continue

                new_path = path + [{
                    'from': current,
                    'from_name': self.data['concepts'].get(current, {}).get('name', current),
                    'relationship': rel['type'],
                    'to': target,
                    'to_name': self.data['concepts'].get(target, {}).get('name', target),
                }]

                if target == to_concept:
                    return {
                        'found': True,
                        'path': new_path,
                        'length': len(new_path),
                    }

                if target not in visited and target in self.data['concepts']:
                    visited.add(target)
                    queue.append((target, new_path))

        return {
            'found': False,
            'message': f'No path found from {from_concept} to {to_concept} within {max_depth} hops',
        }

    def prerequisites_for(self, concept_id: str, depth: int = 3) -> dict:
        """Recursively gather all 'requires' relationships.

        Returns a tree of prerequisites needed to understand a concept.
        """
        if concept_id not in self.data['concepts']:
            return {'error': f'Concept "{concept_id}" not found'}

        def gather_prereqs(cid, current_depth, visited):
            if current_depth > depth or cid in visited:
                return None

            visited.add(cid)
            concept = self.data['concepts'].get(cid, {})

            prereqs = []
            for rel in concept.get('relationships', {}).get('requires', []):
                target_id = rel['id'] if isinstance(rel, dict) else rel
                # Skip file references
                if '/' in str(target_id):
                    continue

                target_concept = self.data['concepts'].get(target_id, {})
                prereq_entry = {
                    'id': target_id,
                    'name': target_concept.get('name', target_id),
                    'category': target_concept.get('category', 'unknown'),
                }

                # Recursively get sub-prerequisites
                sub_prereqs = gather_prereqs(target_id, current_depth + 1, visited.copy())
                if sub_prereqs and sub_prereqs.get('requires'):
                    prereq_entry['requires'] = sub_prereqs['requires']

                prereqs.append(prereq_entry)

            return {'requires': prereqs} if prereqs else {}

        concept = self.data['concepts'][concept_id]
        result = {
            'concept': concept_id,
            'name': concept.get('name', concept_id),
            'depth': depth,
        }
        result.update(gather_prereqs(concept_id, 0, set()))

        return result

    def implementations_of(self, concept_id: str) -> dict:
        """Find all source files implementing a concept."""
        if concept_id not in self.data['concepts']:
            # Try fuzzy match
            matched = None
            for cid in self.data['concepts']:
                if concept_id.lower() in cid.lower():
                    matched = cid
                    break
            if matched:
                concept_id = matched
            else:
                return {'error': f'Concept "{concept_id}" not found'}

        concept = self.data['concepts'][concept_id]
        implementations = []

        for rel in concept.get('relationships', {}).get('implemented_in', []):
            impl = {
                'reference': rel['id'] if isinstance(rel, dict) else rel,
            }
            if isinstance(rel, dict) and rel.get('meta'):
                impl['brief'] = rel['meta'].get('brief', '')
            implementations.append(impl)

        return {
            'concept': concept_id,
            'name': concept.get('name', concept_id),
            'implementation_count': len(implementations),
            'implementations': implementations,
        }

    def list_concepts(self, category: str = None) -> list[dict]:
        """List all concepts, optionally filtered by category."""
        results = []

        for cid, concept in self.data['concepts'].items():
            if category and concept.get('category') != category:
                continue

            results.append({
                'id': cid,
                'name': concept.get('name', cid),
                'category': concept.get('category', 'unknown'),
                'aliases': concept.get('aliases', []),
            })

        return sorted(results, key=lambda x: x['name'])

    def get_categories(self) -> dict:
        """Get all concept categories with descriptions."""
        return self.categories_data

    def search_concepts(self, query: str) -> list[dict]:
        """Search concepts by name, alias, or definition."""
        query_lower = query.lower()
        results = []

        for cid, concept in self.data['concepts'].items():
            score = 0

            # Check ID
            if query_lower in cid.lower():
                score += 3

            # Check name
            if query_lower in concept.get('name', '').lower():
                score += 3

            # Check aliases
            for alias in concept.get('aliases', []):
                if query_lower in alias.lower():
                    score += 2

            # Check definition
            if query_lower in concept.get('definition', '').lower():
                score += 1

            # Check intuition
            if query_lower in concept.get('intuition', '').lower():
                score += 1

            if score > 0:
                results.append({
                    'id': cid,
                    'name': concept.get('name', cid),
                    'category': concept.get('category', 'unknown'),
                    'score': score,
                    'definition': concept.get('definition', '')[:200],
                })

        return sorted(results, key=lambda x: -x['score'])

    def solvers_for(self, problem_class: str) -> dict:
        """Find all algorithms that solve a given problem class."""
        # Normalize problem class name - check id, name, and aliases
        problem_id = None
        query = problem_class.lower().strip()

        for cid, concept in self.data['concepts'].items():
            if concept.get('category') == 'problem_class':
                # Check ID
                if query in cid.lower():
                    problem_id = cid
                    break
                # Check name
                if query in concept.get('name', '').lower():
                    problem_id = cid
                    break
                # Check aliases
                for alias in concept.get('aliases', []):
                    if query == alias.lower():
                        problem_id = cid
                        break
                if problem_id:
                    break

        if not problem_id:
            return {'error': f'Problem class "{problem_class}" not found'}

        problem = self.data['concepts'][problem_id]
        solvers = []

        # Find all algorithms that solve this problem
        for rel in self.data.get('relationships', []):
            if rel['type'] == 'solves' and rel['to'] == problem_id:
                solver_id = rel['from']
                if solver_id in self.data['concepts']:
                    solver = self.data['concepts'][solver_id]
                    solvers.append({
                        'id': solver_id,
                        'name': solver.get('name', solver_id),
                        'intuition': solver.get('intuition', ''),
                        'alternatives': [
                            a['id'] for a in solver.get('relationships', {}).get('alternative_to', [])
                        ],
                    })

        return {
            'problem_class': problem_id,
            'problem_name': problem.get('name', problem_id),
            'solvers': solvers,
        }

    def compare_algorithms(self, algo1: str, algo2: str) -> dict:
        """Compare two algorithms - what they solve, require, and how they differ."""
        # Find both algorithms
        c1 = self.data['concepts'].get(algo1)
        c2 = self.data['concepts'].get(algo2)

        if not c1:
            for cid, c in self.data['concepts'].items():
                if algo1.lower() in cid.lower():
                    c1 = c
                    algo1 = cid
                    break
        if not c2:
            for cid, c in self.data['concepts'].items():
                if algo2.lower() in cid.lower():
                    c2 = c
                    algo2 = cid
                    break

        if not c1:
            return {'error': f'Algorithm "{algo1}" not found'}
        if not c2:
            return {'error': f'Algorithm "{algo2}" not found'}

        def get_targets(concept, rel_type):
            return [r['id'] if isinstance(r, dict) else r
                   for r in concept.get('relationships', {}).get(rel_type, [])]

        solves1 = set(get_targets(c1, 'solves'))
        solves2 = set(get_targets(c2, 'solves'))
        requires1 = set(get_targets(c1, 'requires'))
        requires2 = set(get_targets(c2, 'requires'))

        return {
            'algorithm_1': {
                'id': algo1,
                'name': c1.get('name', algo1),
                'intuition': c1.get('intuition', ''),
            },
            'algorithm_2': {
                'id': algo2,
                'name': c2.get('name', algo2),
                'intuition': c2.get('intuition', ''),
            },
            'both_solve': list(solves1 & solves2),
            'only_1_solves': list(solves1 - solves2),
            'only_2_solves': list(solves2 - solves1),
            'shared_requirements': list(requires1 & requires2),
            'unique_to_1': list(requires1 - requires2),
            'unique_to_2': list(requires2 - requires1),
            'are_alternatives': algo2 in get_targets(c1, 'alternative_to'),
        }

    def get_algorithm_guidance(self, algorithm_id: str) -> dict:
        """Get practical guidance for an algorithm - complexity, when to use, etc."""
        algos = self.guidance.get('algorithms', {})

        # Try exact match first
        if algorithm_id in algos:
            return {'algorithm': algorithm_id, **algos[algorithm_id]}

        # Try fuzzy match
        for aid, data in algos.items():
            if algorithm_id.lower() in aid.lower():
                return {'algorithm': aid, **data}

        return {'error': f'No guidance found for "{algorithm_id}"'}

    def suggest_approach(self, problem_type: str, characteristics: list[str] = None) -> dict:
        """Suggest algorithms based on problem type and characteristics.

        Args:
            problem_type: LP, MIP, NLP, MINLP, etc.
            characteristics: List like ["large", "sparse", "reoptimization", "convex"]
        """
        characteristics = characteristics or []
        char_lower = [c.lower() for c in characteristics]
        problem_lower = problem_type.lower()

        suggestions = []

        # Check problem characteristic rules
        rules = self.guidance.get('problem_characteristics', {})
        for rule_name, rule in rules.items():
            indicators = [i.lower() for i in rule.get('indicators', [])]

            # Score how well this rule matches
            score = 0
            matched_indicators = []

            for indicator in indicators:
                # Check if any characteristic matches this indicator
                for char in char_lower:
                    if char in indicator or indicator in char:
                        score += 1
                        matched_indicators.append(indicator)
                        break

                # Check if problem type matches
                if problem_lower in indicator:
                    score += 2
                    matched_indicators.append(indicator)

            if score > 0:
                suggestions.append({
                    'rule': rule_name,
                    'algorithm': rule.get('recommendation'),
                    'rationale': rule.get('rationale'),
                    'score': score,
                    'matched': matched_indicators,
                })

        # Sort by score
        suggestions.sort(key=lambda x: -x['score'])

        # Also get direct algorithm guidance for top suggestions
        detailed = []
        seen_algos = set()
        for s in suggestions[:3]:
            algo_id = s['algorithm']
            if algo_id and algo_id not in seen_algos:
                seen_algos.add(algo_id)
                guidance = self.get_algorithm_guidance(algo_id)
                if not guidance.get('error'):
                    detailed.append({
                        'algorithm': algo_id,
                        'rationale': s['rationale'],
                        'when_to_use': guidance.get('when_to_use', []),
                        'strengths': guidance.get('strengths', [])[:3],
                        'complexity': guidance.get('complexity', {}),
                    })

        # Fallback: suggest based on problem type alone
        if not detailed:
            problem_to_algo = {
                'lp': ['simplex_method', 'interior_point_method'],
                'qp': ['active_set_method', 'interior_point_method'],
                'nlp': ['interior_point_method'],
                'mip': ['branch_and_bound'],
                'milp': ['branch_and_bound'],
                'minlp': ['outer_approximation', 'spatial_branch_and_bound'],
            }

            for algo_id in problem_to_algo.get(problem_lower, []):
                guidance = self.get_algorithm_guidance(algo_id)
                if not guidance.get('error'):
                    detailed.append({
                        'algorithm': algo_id,
                        'rationale': f'Standard approach for {problem_type}',
                        'when_to_use': guidance.get('when_to_use', []),
                        'strengths': guidance.get('strengths', [])[:3],
                        'complexity': guidance.get('complexity', {}),
                    })

        return {
            'problem_type': problem_type,
            'characteristics': characteristics,
            'suggestions': detailed,
            'rules_matched': len(suggestions),
        }
