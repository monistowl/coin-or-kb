+++
title = "Adaptive Hybrid Node Selection"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

Dynamically switches between search strategies based on solve progress.

Phase 1 (Before first solution):
- weight_ = -1: Fewest infeasibilities (greedy toward integrality)
- weight_ = -2: Breadth-first for 1000 nodes (explore diversity)
- weight_ = -3: Depth-first (find solution fast, low memory)

Phase 2 (After solution found):
- weight_ = 0: Auto-compute from gap to balance exploration/exploitation
- weight_ > 0: Hybrid score = objective + weight × numInfeasibilities
  Higher weight emphasizes depth, lower weight emphasizes best-bound

Adaptive adjustments:
- newSolution(): Recalibrate weight based on improvement
- every1000Nodes(): Check tree size, possibly switch strategy or dive
- Diving: Temporary depth-first from promising node to find solution

## Mathematical Formulation

<div class="math-block">

Node score: S(n) = z(n) + w × k(n)
where z(n) = LP bound, k(n) = number of infeasibilities, w = weight.
Optimal w depends on gap: w ≈ (z* - z_LP) / k_avg

</div>

## Complexity

Comparison: O(1). Strategy switches: O(n log n) for re-heapify.
Adaptive strategies typically 20-50% faster than fixed strategies.

## Implementations

### Cbc

- **[CbcCompareDefault.hpp](/coin-or-kb/browser/?library=Cbc)** - Default adaptive node comparison strategy
Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## References

- Linderoth & Savelsbergh, "A computational study of search strategies",
     INFORMS Journal on Computing 11 (1999) 173-187

CbcCompareDefault: Sophisticated hybrid search strategy.
Adapts behavior based on search phase and solution history.

Strategy phases:
- Before solution: Use depth-first (weight_ < 0) or breadth-first
- After solution: Weight-based hybrid of objective and infeasibilities

weight_ special values:
- 0.0: Auto-compute from first solution
- -1.0: Fewest infeasibilities (before solution)
- -2.0: Breadth-first for first 1000 nodes
- -3.0: Depth-first before solution

Adaptive callbacks:
- newSolution(): Recomputes weight from solution gap
- every1000Nodes(): Adjusts for tree size, triggers diving

Diving support:
- startDive()/cleanDive(): Focused depth search from promising node
