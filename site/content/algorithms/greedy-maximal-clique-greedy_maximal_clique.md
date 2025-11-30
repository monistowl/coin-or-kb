+++
title = "Greedy Maximal Clique (greedy_maximal_clique)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Conflict Analysis"
implementation_count = 1
+++

When candidate list exceeds threshold:

## Mathematical Formulation

<div class="math-block">

Greedily add highest-degree nodes until no more fit
  Fast but may miss maximum violated clique.

</div>

## Complexity

O(n² * d) for greedy approach

## Implementations

### Cgl

- **[CglClique.hpp](/coin-or-kb/browser/?library=Cgl)** - Clique cuts from set packing structure

Generates clique inequalities by finding maximal cliques in the
conflict graph of binary variables. Two binaries conflict if they
cannot both be 1 in any feasible solution.

Clique inequality: sum_{j in C} x_j <= 1 (or = 1 if equality)

Graph construction (frac_graph):
- Nodes: Binary variables at fractional LP values
- Edges: Variables that conflict (appear in same set packing row)
- Edge costs: 1 - x_i - x_j (for odd hole detection)

Two clique-finding methods:
1. Star clique (do_star_clique):
   - Pick a center node, find all neighbors (star)
   - Enumerate maximal cliques in the star
   - SCL_MIN_DEGREE/MAX_DEGREE/MAX_XJ_MAX_DEG selection rules
2. Row clique (do_row_clique):
   - Start from existing set packing row
   - Extend to larger clique using adjacent variables

Thresholds:
- scl_candidate_length_threshold: Max size for exact enumeration
- rcl_candidate_length_threshold: Same for row clique method
- Beyond threshold: use greedy heuristic

CglFakeClique (derived class):
- Works on "fake" solver with invented rows from probing
- Integrates with CglProbing for stronger implications

## References

- Padberg (1973) - On the facial structure of set packing
- Bron-Kerbosch (1973) - Algorithm for finding all cliques
