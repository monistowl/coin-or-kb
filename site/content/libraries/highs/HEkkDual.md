+++
title = "HEkkDual"
description = "Dual simplex solver for HiGHS"
template = "page.html"

[extra]
layer = 4
library = "HiGHS"
header_file = "highs/simplex/HEkkDual.h"
+++

Dual simplex solver for HiGHS

Implements dual simplex algorithm with CHUZR (row selection), PRICE
(pivot row computation), CHUZC (column selection), and basis update.

**Parallelization Strategies:**
- Plain: Serial dual simplex (kSimplexStrategyDualPlain)
- SIP: Suboptimization with Independent Parallelism (Tasks)
- PAMI: Parallel Minor Iterations (Multi)

**Key Phases:**
- Phase 1: Minimize sum of infeasibilities to find feasible basis
- Phase 2: Optimize objective maintaining dual feasibility

**Edge Weight Modes:**
- Dantzig: Simple pricing
- Devex: Approximate steepest edge
- Steepest Edge: Exact steepest edge with DSE vector updates

**PAMI Data Structures:**
- MChoice: Multiple row candidates from CHUZR
- MFinish: Minor iteration data for parallel updates
- slice_*: Partitioned matrix for parallel PRICE

## Algorithm

<div class="algorithm-card">

PAMI - Parallel Minor Iterations (iterateMulti):
  Exploit parallelism by batching multiple pivots:
  1. majorChooseRow: Select k candidate leaving rows in parallel
  2. majorChooseRowBtran: Parallel BTRAN for all k row_ep vectors
  3. For each minor iteration i = 1..k:
     a. minorChooseRow: Pick best from remaining candidates
     b. chooseColumnSlice: Parallel PRICE across matrix slices
     c. minorUpdate: Update data structures locally
  4. majorUpdate: Apply all k updates to LU factors at once

<div class="math">

$$Edge weight γ_{i} = ||B^{-1} e_{i}||² = ||τ_{i}||²$$
After basis change with pivot row r and column s:
$$- Compute τ_{s} = B^{-1} e_{s} (FTRAN of unit vector)$$
$$- Update weights: γ_{i}' = γ_{i} - 2(τ_{r} · a_{q})α_{i}/α_{r} + γ_{r}(α_{i}/α_{r})²$$
Cost: one extra FTRAN per iteration, but ~40% fewer iterations.

</div>

**Complexity:** Serial iteration: $O(nnz)$ for BTRAN/FTRAN, $O(m)$ for ratio test
  PAMI: $O(k × nnz/p + k² × m)$ for k pivots on p processors
  Total iterations: typically $O(m)$ to $O(2m)$ for dual simplex

<div class="refs">

**References:**
- Maros, I. (2003). "Computational Techniques of the Simplex Method".        Springer, Chapters 9-10.
- Forrest, J.J. and Goldfarb, D. (1992). "Steepest-edge simplex        algorithms for linear programming". Math. Programming 57:341-374.
- Harris, P.M.J. (1973). "Pivot selection methods of the Devex        LP code". Math. Programming Study 4:30-57.
- Hall, J.A.J. and McKinnon, K.I.M. (2005). "Hyper-sparsity in the        revised simplex method and how to exploit it". CMS 2(1):21-40.

</div>

</div>

## See Also

- simplex/HEkk.h for main simplex class
- simplex/HEkkDualRow.h for pivot row handling
- simplex/HEkkDualRHS.h for RHS management

## Source

Header file: {{ link(path="/browser/?library=HiGHS&file=highs/simplex/HEkkDual.h", text="`highs/simplex/HEkkDual.h`") }}

