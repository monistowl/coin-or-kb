+++
title = "Clique Storage"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Conflict Analysis"
implementation_count = 1
+++

Stores cliques as variable-length arrays with shared element pool
  Operations:
  - addClique(size, elements[]): append new clique
  - cliqueElements(idx): retrieve clique by index
  - computeNodeOccurrences: build inverse index (node → cliques)

  Inverse index enables efficient lookup of which cliques contain a node

## Mathematical Formulation

<div class="math-block">

Clique C ⊆ V is complete subgraph: ∀u,v ∈ C, (u,v) ∈ E
  Used in conflict graphs where edges represent incompatibility
  Clique inequality: Σ_{i∈C} x_i ≤ 1 (at most one var in clique can be 1)

</div>

## Complexity

addClique: O(clique_size) for copying elements
  cliqueElements/cliqueSize: O(1) random access
  computeNodeOccurrences: O(total_elements) one-time setup
  nNodeOccurrences: O(1) after setup

## Implementations

### CoinUtils

- **[CoinCliqueList.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Sequential storage for cliques found in conflict graphs
