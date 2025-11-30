+++
title = "Duplicate Detection via Random Hashing"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

To find duplicate columns efficiently:
  1. Assign random weight r_i to each row
  2. Compute column hash: h_j = Σ_i r_i · a_ij
  3. Columns with same hash are candidates (verify exactly)

  Duplicate columns (same cost): combine bounds
  - x_j and x_k identical → replace with x_new, l_new = l_j + l_k

  Duplicate rows: keep tighter constraint, remove redundant
  - If row_i ⊆ row_k (interval containment), remove row_k

## Mathematical Formulation

<div class="math-block">

Column equivalence: a_*j = a_*k (element-wise)
  Combined variable: x_new = x_j + x_k
  Postsolve: split x_new* back to feasible (x_j*, x_k*)

</div>

## Complexity

Time: O(nnz) for hashing, O(candidates × nnz) for verification
  Random hashing minimizes false positives
  Common in models with symmetry or copy-paste construction

## Implementations

### CoinUtils

- **[CoinPresolveDupcol.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Detect and remove duplicate columns and rows
