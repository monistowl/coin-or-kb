+++
title = "Primal Simplex Method"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

Solves LP by maintaining primal feasibility (variables within bounds)
while iterating toward dual feasibility (optimality). Each iteration:
1. Choose entering variable (pivot column) - with negative reduced cost
2. Compute pivot column of tableau: d = B^{-1} a_j (via FTRAN)
3. Choose leaving variable (pivot row) - via ratio test on bounds
4. Update basis: swap entering/leaving variables
5. Update primal solution and reduced costs

Uses single-phase approach with infeasibilityCost_ weighting for handling
infeasible starting points. Steepest edge or Dantzig strategies for pivot
selection. Anti-degeneracy via cost perturbation (OSL heritage).

Three nested loops: outer handles fake bounds, middle handles refactorization,
inner performs pivots until optimality or unboundedness detected.

## Mathematical Formulation

<div class="math-block">

min c^T x s.t. Ax=b, l≤x≤u
Basic solution: x_B = B^{-1}b - B^{-1}N x_N, with x_N at bounds.
Reduced cost: s_j = c_j - c_B^T B^{-1} a_j (computed via BTRAN then dot product)
Ratio test: θ* = min{(x_B[i]-l_i)/d_i, (u_i-x_B[i])/(-d_i)} for feasible step.
Primal feasible when l ≤ x ≤ u. Optimal when also s_j ≥ 0 for vars at lower bound.

</div>

## Complexity

O(m^2 n) per iteration typical (dominated by FTRAN/BTRAN).
Iteration count varies widely. Often slower than dual simplex but useful
when starting from feasible solution or for problems with few constraints.

## Implementations

### Clp

- **[ClpSimplexPrimal.hpp](/coin-or-kb/browser/?library=Clp)** - Primal simplex algorithm implementation

## References

- Dantzig, "Linear Programming and Extensions", Princeton (1963)
- Forrest & Goldfarb, "Steepest-edge simplex algorithms for LP",
     Mathematical Programming 57 (1992) 341-374

Implements the primal simplex method for LP. This is a "mix-in" class that
inherits from ClpSimplex but adds no data - ClpSimplex objects are cast
to this type when running primal simplex.

The primal simplex maintains primal feasibility (variables within bounds)
while iterating toward dual feasibility (optimality). Useful when starting
from a feasible solution or when dual simplex struggles.

Key algorithmic features:
- Single-phase approach with infeasibilityCost_ weighting
- Explicit bounds on reduced costs for feasibility handling
- Sparse data structures exploiting problem sparsity
- Steepest edge or Dantzig pivot selection for entering variable
- Anti-degeneracy via cost perturbation
- Supports nonlinear costs (though not heavily tested)
