+++
title = "MIP Primal Heuristics Framework"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Primal Heuristics"
implementation_count = 1
+++

Primal heuristics find feasible integer solutions during B&C search.
Good solutions improve the upper bound, enabling more pruning.

Heuristic Categories:
1. Construction: Build solution from scratch (rounding, greedy)
2. Improvement: Refine existing solution (local search, RINS)
3. Diving: Fix variables sequentially toward integrality
4. Large Neighborhood Search: Fix subset, re-optimize remainder

Included heuristics:
- CbcRounding: Round LP solution using constraint "locks"
  Lock = coefficient sign × bound direction. Round toward locked side.
- CbcHeuristicPartial: Fix high-priority variables, solve sub-MIP
- CbcSerendipity: Capture solutions found incidentally by solver

Scheduling via when_/whereFrom_/howOften_ controls invocation frequency
and timing (root vs tree, before/after cuts).

## Mathematical Formulation

<div class="math-block">

Rounding with locks: For x_j fractional, count constraints where
rounding down vs up would help feasibility. Round toward majority vote.
Quality vs speed tradeoff: quick heuristics often, expensive ones rarely.

</div>

## Complexity

Rounding: O(nnz). Sub-MIP heuristics: depends on time limit.
Heuristics typically limited to fraction of total solve time.

## Implementations

### Cbc

- **{{ link(path="/browser/?library=Cbc", text="CbcHeuristic.hpp") }}** - Base class for MIP primal heuristics
Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## References

- Berthold, "Primal heuristics for mixed integer programs", PhD thesis (2006)
- Achterberg, "Constraint Integer Programming", TU Berlin (2007), Ch. 7

CbcHeuristic: Abstract base for primal heuristics that find feasible
solutions during branch-and-cut search. Key method is solution() which
returns 1 if a valid solution is found, 0 otherwise.

Execution control:
- when_: 0=off, 1=root only, 2=non-root, 3=always
- whereFrom_: Bit field for timing (before/during/after cuts)
- howOften_: Frequency of invocation

Includes several concrete heuristics:
- CbcRounding: Simple rounding with lock-based feasibility
- CbcHeuristicPartial: Fix priority-based partial solution
- CbcSerendipity: Capture solver-found solutions
- CbcHeuristicJustOne: Randomly select one from multiple heuristics

Also includes CbcHeuristicNode/NodeList for tracking where heuristics
have been invoked (distance-based diversification).
