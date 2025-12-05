+++
title = "Conflict Graph Construction"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Conflict Analysis"
implementation_count = 1
+++

For binary variables x_i ∈ {0,1}, build graph G where:
  - Nodes: original variables x_i and complements x̄_i = 1 - x_i
  - Edges: (u,v) if u=1 and v=1 simultaneously infeasible
  Sources of conflicts:
  1. Set packing constraints: x_i + x_j ≤ 1 → edge (x_i, x_j)
  2. Variable bounds: x_i ≤ x_j → edge (x_i, x̄_j)
  3. Clique constraints: Σx_i ≤ 1 → complete subgraph

## Mathematical Formulation

<div class="math-block">

Independent set in conflict graph ↔ feasible partial assignment.
  Clique C in conflict graph → valid inequality Σ_{i∈C} x_i ≤ 1.
  Maximum clique gives strongest clique cut.

</div>

## Complexity

Space: O(n²) worst case, but typically sparse O(n + m)
  Conflict check: O(1) with adjacency matrix, O(degree) with lists
  Clique storage: large cliques stored explicitly to save space

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinConflictGraph.hpp") }}** - Conflict graph for binary variable incompatibilities in MIP
