+++
title = "ClpFactorization"
description = "Wrapper around CoinFactorization for use within Clp simplex"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpFactorization.hpp"
+++

## Algorithm

<div class="algorithm-card">

LU Factorization with Forrest-Tomlin Updates:
Maintains factorization B = LU of the basis matrix for simplex operations.
Core operations:
- factorize(): Compute B = LU from scratch using Markowitz pivoting
- FTRAN: Solve Bx = a via Ly = a then Ux = y (forward transformation)
- BTRAN: Solve B^T x = c via U^T y = c then L^T x = y (backward transformation)
- replaceColumn(): Update LU when basis changes via Forrest-Tomlin method

Forrest-Tomlin update maintains L fixed, updates U with spike column.
Alternative Product Form of Inverse (PFI) available but less stable.
Refactorization triggered when fill-in exceeds threshold or numerical error grows.

<div class="math">

Basis matrix B ∈ ℝ^{m×m} where columns are basic column vectors from [A|I].
LU factorization: PBQ = LU where P,Q are permutation matrices.
FTRAN solves: d = B^{-1}a_j (pivot column for primal simplex)
BTRAN solves: π^T = c_B^T B^{-1} (dual prices for reduced cost calculation)
Update: B_new = B_old + (a_j - Be_i)e_i^T for basis change at position i.

</div>

**Complexity:** Factorization: O(m^2) to O(m^3) depending on sparsity and fill-in.
FTRAN/BTRAN: O(nnz(L) + nnz(U)) per solve, typically O(m) for sparse problems.
Forrest-Tomlin update: O(m) average, refactorization every 100-200 pivots.

<div class="refs">

**References:**
- Forrest & Tomlin, "Updated triangular factors of the basis to maintain      sparsity in the product form simplex method", Mathematical Programming 2 (1972)
- Suhl & Suhl, "Computing sparse LU factorizations for large-scale LP bases",      ORSA Journal on Computing 2 (1990)  ClpFactorization adapts CoinFactorization to the Clp solver context, handling the integration between the simplex algorithm and the LU factorization of the basis matrix. It also supports special cases like network bases (ClpNetworkBasis) and dense factorizations.  Key responsibilities: - Factorize the basis matrix given ClpSimplex model and basic variable info - Provide FTRAN (forward solve) and BTRAN (backward solve) operations - Handle basis updates via replaceColumn (Forrest-Tomlin update) - Switch between factorization types (sparse LU, dense, network)

</div>

</div>

## See Also

- CoinFactorization in CoinUtils for the underlying LU implementation
- ClpNetworkBasis for special network structure handling
- ClpSimplex for how factorization integrates with simplex iterations

## Source

Header file: `src/ClpFactorization.hpp`

