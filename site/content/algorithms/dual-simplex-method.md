+++
title = "Dual Simplex Method"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

## Why This Matters

Dual simplex is the algorithm that makes modern MIP solvers fast. While primal simplex moves from feasible vertex to feasible vertex, dual simplex moves from *infeasible* vertices with correct pricing. This turns out to be exactly what you need for:

- **Branch-and-bound**: After branching (adding a bound constraint), primal feasibility is lost but dual feasibility often remains. Dual simplex can re-optimize in a few iterations.
- **Adding cuts**: When you add a violated cut, you're making the current solution infeasible. Dual simplex handles this naturally.
- **Warm starting**: If you have the optimal basis from a similar problem, dual simplex can verify optimality or find the new optimum quickly.

**The key insight**: Dual simplex treats constraint violations as the "objective" to minimize, while keeping reduced costs feasible. This is often much faster than primal simplex when bounds change.

---

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

- **{{ link(path="/browser/?library=Clp", text="ClpSimplexDual.hpp") }}** - Dual simplex algorithm implementation

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
