+++
title = "Implied Free Variable Detection"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

For singleton variable x_j (one nonzero a_ij in row i):
  1. Compute implied bounds on x_j from constraint i and other var bounds
  2. If implied bounds strictly within [l_j, u_j]: x_j is implied free
  3. Remove constraint i and variable x_j (neither can be binding)

  Non-singleton case: use substitution to reduce to singleton first

## Mathematical Formulation

<div class="math-block">

For row: Σ_k a_ik x_k = b_i, with x_j singleton
  x_j = (b_i - Σ_{k≠j} a_ik x_k) / a_ij
  Implied bounds from other variables' bounds → [l_j^impl, u_j^impl]
  If l_j < l_j^impl and u_j > u_j^impl: x_j implied free

</div>

## Complexity

Time: O(nnz(row)) per candidate variable
  Very effective for network and assignment problems
  Reduces problem by one row and one column per implied free

## Implementations

### CoinUtils

- **[CoinPresolveImpliedFree.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Detect and process implied free variables
