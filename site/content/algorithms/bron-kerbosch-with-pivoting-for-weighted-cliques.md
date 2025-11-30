+++
title = "Bron-Kerbosch with pivoting for weighted cliques"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

BK(R, P, X):  R = clique being built, P = candidates, X = excluded
  1. If P ∪ X = ∅: report R as maximal clique
  2. Choose pivot u ∈ P ∪ X maximizing |N(u) ∩ P|
  3. For each v ∈ P \ N(u):
     - BK(R ∪ {v}, P ∩ N(v), X ∩ N(v))
     - P := P \ {v}; X := X ∪ {v}
  Pivoting prunes branches that cannot produce new maximal cliques.

## Mathematical Formulation

<div class="math-block">

Clique: complete subgraph where all vertices are pairwise adjacent.
  Weight threshold: only enumerate cliques with Σw(v) > minWeight.
  Pivoting strategies: degree, weight, or modified degree×weight.

</div>

## Complexity

Time: O(3^(n/3)) worst case for all maximal cliques
  With pivoting: much faster in practice, especially for sparse graphs.
  Space: O(n) for recursion stack

## Implementations

### CoinUtils

- **[CoinBronKerbosch.hpp](/browser/?library=CoinUtils)** - Bron-Kerbosch Algorithm for maximal clique enumeration

## References

- Bron, Kerbosch (1973). "Algorithm 457: Finding all cliques of an
     undirected graph". CACM 16(9):575-577.
- Tomita, Tanaka, Takahashi (2006). "The worst-case time complexity
     for generating all maximal cliques". Theoretical Computer Science.

\copyright{Copyright 2020 Brito, S.S. and Santos, H.G.}
\license{This This code is licensed under the terms of the Eclipse Public License (EPL).}
