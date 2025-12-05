+++
title = "Simplex Basis Warm Start"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

For LP with m constraints and n variables, a basis B identifies
  m basic variables. Restarting from a known basis avoids Phase I.
  Status encoding (2 bits per variable):
  - 00 (isFree): nonbasic at zero
  - 01 (basic): in the basis (value determined by constraints)
  - 10 (atUpperBound): nonbasic at upper bound
  - 11 (atLowerBound): nonbasic at lower bound

## Mathematical Formulation

<div class="math-block">

Basis matrix B is m×m submatrix of A with basic columns.
  Basic solution: x_B = B⁻¹b, x_N = 0 (or at bounds)
  Warm start restores this basis without recomputing from scratch.

</div>

## Complexity

Space: O((m+n)/4) bytes using 2-bit packing (4 vars per byte)
  Diff operations for B&B: O(changed variables) instead of O(m+n)
  generateDiff/applyDiff enable efficient tree-based warm starting

## Implementations

### CoinUtils

- **[CoinWarmStartBasis.hpp](/browser/?library=CoinUtils)** - Simplex basis warm start with variable status (basic/nonbasic)

Stores status of each variable (structural and artificial) using
2 bits per variable. Includes diff capability for branch-and-bound.
