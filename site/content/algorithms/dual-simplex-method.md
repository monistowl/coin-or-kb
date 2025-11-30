+++
title = "Dual Simplex Method"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

Solves LP by maintaining dual feasibility (reduced costs have correct signs)
while iterating toward primal feasibility. Each iteration:
1. Choose leaving variable (pivot row) - infeasible basic variable
2. Compute pivot row of tableau: r^T = e_i^T B^{-1} A
3. Choose entering variable (pivot column) - via ratio test on reduced costs
4. Update basis: swap entering/leaving variables
5. Update dual solution and reduced costs

Uses single-phase approach with fake bounds (updatedDualBound_) to handle
dual infeasibility. Steepest edge or Dantzig strategies for pivot selection.
Anti-degeneracy via cost perturbation (OSL heritage).

Three nested loops: outer handles fake bounds, middle handles refactorization,
inner performs pivots until optimality or infeasibility detected.

## Mathematical Formulation

<div class="math-block">

min c^T x s.t. Ax=b, l≤x≤u (primal)
Dual: max b^T y s.t. A^T y + s = c, s_j≥0 for x_j at lower, s_j≤0 for x_j at upper
Reduced cost: s_j = c_j - a_j^T y where y = B^{-T} c_B
Dual feasible when reduced costs have correct signs for non-basic variables.
Ratio test: θ* = min{s_j/r_j : r_j has correct sign} determines entering var.

</div>

## Complexity

O(m^2 n) per iteration typical (dominated by BTRAN/FTRAN).
Iteration count highly problem-dependent. Often faster than primal simplex
for problems with many constraints, especially after adding cuts in B&B.

## Implementations

### Clp

- **[ClpSimplexDual.hpp](/coin-or-kb/browser/?library=Clp)** - Dual simplex algorithm implementation

## References

- Forrest & Goldfarb, "Steepest-edge simplex algorithms for LP",
     Mathematical Programming 57 (1992) 341-374
- Koberstein, "Progress in the dual simplex algorithm",
     Computers & Operations Research 35 (2008) 2297-2320

Implements the dual simplex method for LP. This is a "mix-in" class that
inherits from ClpSimplex but adds no data - ClpSimplex objects are cast
to this type when running dual simplex.

The dual simplex maintains dual feasibility (reduced costs have correct signs)
while iterating toward primal feasibility. It's typically faster than primal
simplex for most problems, especially after adding cuts in branch-and-bound.

Key algorithmic features:
- Single-phase approach with weighted objective for dual feasibility
- Fake bounds (updatedDualBound_) to handle dual infeasibility
- Sparse data structures to exploit problem sparsity
- Steepest edge or Dantzig pivot selection for choosing leaving variable
- Anti-degeneracy via cost perturbation (from OSL heritage)
