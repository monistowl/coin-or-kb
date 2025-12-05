+++
title = "Objective Propagation"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Given incumbent z* and objective c'x:
  For each variable, derive bound from c'x < z* constraint.
  Particularly effective when objective has large coefficients.

## Complexity

propagate(): O(nnz × propagation_rounds) amortized
  conflictAnalysis(): O(conflict_clause_length × reason_chain_depth)
  backtrack(): O(number_of_bound_changes_to_undo)

## Implementations

### HiGHS

- **[HighsDomain.h](/browser/?library=HiGHS)** - Bound tracking, propagation, and conflict analysis for MIP

**HighsDomain Class:**
Manages variable bounds during MIP branch-and-bound with:
- col_lower_[], col_upper_[]: Current variable bounds
- domchgstack_[]: Stack of bound changes (for backtracking)
- domchgreason_[]: Reason for each bound change (branching, row, clique)

**Bound Propagation:**
- propagate(): Deduce implied bounds from constraints
- activitymin_[]/activitymax_[]: Row activity bounds for propagation
- markPropagate(): Queue row for propagation
- ObjectivePropagation: Deduce bounds from objective cutoff

**Reason Tracking:**
Each bound change records its cause:
- kBranching: B&B branching decision
- kModelRowUpper/Lower: Implied by constraint
- kCliqueTable: Clique conflict
- kObjective: Objective bound
- cut(pool,index): Cut from cut pool

**Conflict Analysis (ConflictSet):**
Learns from infeasibility:
- conflictAnalysis(): Build conflict clause from infeasibility proof
- reasonSideFrontier: Domain changes causing infeasibility
- Generates learned conflicts for HighsConflictPool

**Cut Pool Integration (CutpoolPropagation):**
- Tracks activity of cuts for cut-based propagation
- Updates when bounds change

**Backtracking:**
- backtrack(): Undo bound changes
- backtrackToGlobal(): Reset to root node bounds
- branchPos_[]: Positions of branching decisions in stack

## References

- Achterberg, T. (2007). "Conflict analysis in mixed integer
  programming". Discrete Optimization 4:4-20.
