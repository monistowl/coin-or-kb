+++
title = "LU Factorization with Forrest-Tomlin Updates"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

## Why This Matters

LU factorization is the **computational engine** of the simplex method. Every simplex iteration needs to solve two linear systems with the basis matrix B. Without efficient factorization and updates, simplex would be impractical for anything beyond toy problems.

- **Speed**: Modern LP solvers perform thousands to millions of simplex pivots. Each pivot requires FTRAN (forward solve) and BTRAN (backward solve). The LU factorization makes these O(nnz) instead of O(m³).
- **Memory**: Storing B⁻¹ explicitly would require O(m²) memory. LU factors are typically much sparser, often O(m) for well-structured problems.
- **Updates matter most**: The Forrest-Tomlin update allows updating the factorization in O(m) time when a single column changes. Without this, you'd need to refactorize (O(m²) or worse) every pivot.

**The key insight**: Rather than inverting the basis matrix or refactoring from scratch, Forrest-Tomlin keeps L fixed and updates U with a "spike" column. After many pivots, fill-in accumulates and you refactorize—but this happens every 100-200 iterations, not every single one.

**Why this specific implementation**: Clp's ClpFactorization wraps CoinFactorization and adds solver-specific logic: switching between sparse, dense, and network factorizations based on problem structure, and handling the warm-start workflow that MIP solvers depend on.

---

Maintains factorization B = LU of the basis matrix for simplex operations.
Core operations:
- factorize(): Compute B = LU from scratch using Markowitz pivoting
- FTRAN: Solve Bx = a via Ly = a then Ux = y (forward transformation)
- BTRAN: Solve B^T x = c via U^T y = c then L^T x = y (backward transformation)
- replaceColumn(): Update LU when basis changes via Forrest-Tomlin method

Forrest-Tomlin update maintains L fixed, updates U with spike column.
Alternative Product Form of Inverse (PFI) available but less stable.
Refactorization triggered when fill-in exceeds threshold or numerical error grows.

## Mathematical Formulation

<div class="math-block">

Basis matrix B ∈ ℝ^{m×m} where columns are basic column vectors from [A|I].
LU factorization: PBQ = LU where P,Q are permutation matrices.
FTRAN solves: d = B^{-1}a_j (pivot column for primal simplex)
BTRAN solves: π^T = c_B^T B^{-1} (dual prices for reduced cost calculation)
Update: B_new = B_old + (a_j - Be_i)e_i^T for basis change at position i.

</div>

## Complexity

Factorization: O(m^2) to O(m^3) depending on sparsity and fill-in.
FTRAN/BTRAN: O(nnz(L) + nnz(U)) per solve, typically O(m) for sparse problems.
Forrest-Tomlin update: O(m) average, refactorization every 100-200 pivots.

## Implementations

### Clp

- **[ClpFactorization.hpp](/browser/?library=Clp)** - Wrapper around CoinFactorization for use within Clp simplex

## References

- Forrest & Tomlin, "Updated triangular factors of the basis to maintain
     sparsity in the product form simplex method", Mathematical Programming 2 (1972)
- Suhl & Suhl, "Computing sparse LU factorizations for large-scale LP bases",
     ORSA Journal on Computing 2 (1990)

ClpFactorization adapts CoinFactorization to the Clp solver context,
handling the integration between the simplex algorithm and the LU
factorization of the basis matrix. It also supports special cases
like network bases (ClpNetworkBasis) and dense factorizations.

Key responsibilities:
- Factorize the basis matrix given ClpSimplex model and basic variable info
- Provide FTRAN (forward solve) and BTRAN (backward solve) operations
- Handle basis updates via replaceColumn (Forrest-Tomlin update)
- Switch between factorization types (sparse LU, dense, network)
