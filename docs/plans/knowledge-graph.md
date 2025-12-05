# Mathematical Concept Knowledge Graph

## Goal

Create a navigational backbone for AI agents to explore optimization mathematics—not just find "where is X implemented" but understand "what does X require", "what problems does X solve", and "how does X relate to Y".

## Design Decisions

- **Use case**: Full-featured optimization oracle (search, explain, derive, validate)
- **Deployment**: Hybrid—hosted JSON/markdown + local MCP with source access
- **Mathematical depth**: Three layers (source annotations, derivation docs, knowledge graph)
- **Priority**: Knowledge graph first as navigational backbone

## Data Model

### Concepts

```json
{
  "id": "interior_point_method",
  "name": "Interior Point Method",
  "aliases": ["IPM", "barrier method"],
  "category": "algorithm",
  "definition": "Solves optimization by traversing interior of feasible region",
  "intuition": "Stay inside constraints using barrier functions, follow central path to optimum",
  "key_equations": ["x + s = b", "Xs = μe", "μ → 0"]
}
```

### Relationships

| Type | Meaning | Example |
|------|---------|---------|
| `requires` | Mathematical prerequisite | interior_point → newton_method |
| `contains` | Has sub-concept | branch_and_bound → node_selection |
| `generalizes` | More general form | LP ← QP ← NLP |
| `solves` | Algorithm for problem | simplex → LP |
| `implemented_in` | Code location | factorization → CoinFactorization.hpp |
| `alternative_to` | Different approach | simplex ↔ interior_point (both solve LP) |

### Categories

- `problem_class`: LP, QP, NLP, MIP, MINLP
- `algorithm`: simplex, interior_point, branch_and_bound
- `optimality`: KKT, duality, complementary_slackness
- `structure`: sparsity, convexity, separability
- `technique`: presolve, warm_start, cutting_planes

## MCP Tools

### New Tools

1. **`explore_concept(concept_id)`** - Get concept + immediate relationships
2. **`find_path(from, to)`** - Navigate between concepts via relationships
3. **`prerequisites_for(concept_id, depth)`** - Recursive `requires` traversal
4. **`implementations_of(concept_id)`** - All source files for a concept

### Integration

- `search_algorithms` → keyword search, then `explore_concept` for depth
- `get_file` → after `implementations_of` identifies files
- `get_library` → overview, then knowledge graph for mathematical structure

## File Structure

```
site/static/api/
├── knowledge-graph/
│   ├── index.json              # All concepts + relationships
│   └── categories.json         # Concept groupings
└── annotations.json            # Existing (unchanged)

data/
└── concepts-seed.yaml          # Hand-authored core concepts

mcp-server/
├── coin_or_kb_server.py        # Extended with new tools
└── knowledge_graph.py          # Graph queries module

scripts/
├── build-knowledge-graph.py    # Generate from seed + annotations
└── validate-graph.py           # Check consistency
```

## Build Process

1. **Seed file** - Hand-author ~40 core concepts with relationships
2. **Extraction** - Scan `@algorithm` annotations, link to concepts
3. **Merge** - Combine seed + extracted into index.json
4. **Validation** - Check all links resolve, no orphans

## Initial Scope (~40 concepts)

**Problem classes**: LP, QP, NLP, MIP, MINLP, convex_optimization, nonconvex_optimization

**Algorithms**: simplex, dual_simplex, interior_point, branch_and_bound, spatial_branch_and_bound, cutting_planes, outer_approximation

**Theory**: KKT_conditions, duality, LP_duality, Lagrangian, complementary_slackness, convexification

**Techniques**: LU_factorization, presolve, warm_start, bound_tightening, FBBT, branching

**Structures**: sparsity, convexity, McCormick_envelopes, relaxation

## Implementation Order

1. Create `data/concepts-seed.yaml` with core concepts
2. Write `scripts/build-knowledge-graph.py` to generate JSON
3. Extend `mcp-server/coin_or_kb_server.py` with new tools
4. Test with example queries
5. Iterate on concept coverage
