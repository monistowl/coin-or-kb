+++
title = "Greedy Cover Heuristic (findGreedyCover)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Primal Heuristics"
implementation_count = 1
+++

Order variables by a_j/x̄_j ratio (LP solution weighted):

## Mathematical Formulation

<div class="math-block">

Add variables greedily until ∑_{j∈C} a_j > b
  Fast but may miss most violated cover.

</div>

## Complexity

O(2^n) worst case, often O(n * c) practical

## Implementations

### Cgl

- **[CglKnapsackCover.hpp](/coin-or-kb/browser/?library=Cgl)** - Knapsack cover cuts for binary packing constraints

Generates cover inequalities for knapsack constraints of the form
sum_j a_j * x_j <= b where x_j are binary. A cover C is a subset
where sum_{j in C} a_j > b, making x_j = 1 for all j in C infeasible.

Cover inequality: sum_{j in C} x_j <= |C| - 1

Algorithm phases:
1. deriveAKnapsack(): Convert constraint to canonical binary knapsack
2. Find minimal violated cover using:
   - findExactMostViolatedMinCover(): Exact via Horowitz-Sahni
   - findLPMostViolatedMinCover(): LP relaxation heuristic
   - findGreedyCover(): Simple greedy heuristic
3. Lifting: Strengthen cover to full-dimensional inequality
   - liftCoverCut(): Sequence-independent lifting
   - seqLiftAndUncomplementAndAdd(): Sequence-dependent lifting
   - liftUpDownAndUncomplementAndAdd(): Up/down lifting for binaries

Additional features:
- createCliques(): Build clique structure for probing
- Horowitz-Sahni algorithm for exact knapsack solving
- John-Ellis cover finding from OSL (IBM's solver)

Key parameters:
- maxInKnapsack_: Maximum variables in processed knapsack
- expensiveCuts_: Enable/disable costly exact methods
- rowsToCheck_: Restrict which rows to examine

## References

- Balas & Zemel (1978) - Facets of the knapsack polytope
- Crowder, Johnson, Padberg (1983) - Solving large-scale 0-1 LPs
- Zemel (1989) - Easily computable facets of the knapsack polytope
- Horowitz & Sahni (1974) - Computing partitions
- Martello & Toth (1990) - Knapsack Problems (p. 30)
