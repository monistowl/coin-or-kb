+++
title = "Steepest Edge Dual Pivot Selection"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

## Why This Matters

Steepest edge is a **pivoting strategy** that dramatically reduces the number of simplex iterations—typically 30-50% fewer than the naive Dantzig rule. On degenerate problems (where many pivots make zero progress), the improvement can be even larger.

- **Fewer iterations = faster solves**: Each simplex iteration has a fixed cost (FTRAN, BTRAN, ratio test). Cutting iteration count by 30% is a direct 30% speedup.
- **Degeneracy resistance**: Degenerate pivots (θ = 0) are the bane of simplex. Steepest edge's normalized selection helps escape degenerate cycles faster.
- **Modern default**: Virtually all production LP solvers (Clp, CPLEX, Gurobi, Xpress) use steepest edge or its approximation (Devex) as the default pivot rule.

**The key insight**: Dantzig rule picks the "most infeasible" row, but this ignores *geometry*. A row might be highly infeasible but also "steep" in the sense that fixing it doesn't improve the objective much. Steepest edge normalizes by the squared length of the tableau row (||B⁻¹eᵢ||²), picking the direction of steepest *improvement* in the dual objective.

**The cost tradeoff**: Maintaining edge weights requires O(m) work per pivot. This is worth it because it typically saves many more pivots than the overhead costs. Devex is a cheaper approximation that recomputes weights periodically.

---

Selects leaving variable (pivot row) by normalizing infeasibility by edge weight.
Instead of choosing most infeasible basic variable (Dantzig), computes:
  score_i = (infeasibility_i)² / weight_i
where weight_i = ||r_i||² = ||e_i^T B^{-1}||² is squared norm of i-th row of B^{-1}.

Weight update after pivot in row p with column entering:
  weight_i := weight_i - 2*(r_ip/r_pp)*v_i + (r_ip/r_pp)²*weight_p
where r is pivot row and v is BTRAN of pivot column. This preserves sparsity.

Three modes: uninitialized (1s), full (exact weights), partial (sparse scan).
Maintains infeasibility list for efficient scanning of only violated rows.

## Mathematical Formulation

<div class="math-block">

Edge weight: γ_i = ||B^{-T}e_i||² = (i-th row of B^{-1})^T(i-th row of B^{-1})
Normalized ratio: d_i/γ_i where d_i is dual infeasibility of row i.
Update formula from BTRAN column: v = B^{-T}a_j gives γ_i' = γ_i - 2α_i v_i + α_i² γ_p
where α_i = r_ip/r_pp is multiplier for row i in elimination.

</div>

## Complexity

O(m) per pivot for weight updates (sparse operations).
Full recomputation O(m²) but rare. Typically 30-50% fewer iterations than Dantzig.

## Implementations

### Clp

- **[ClpDualRowSteepest.hpp](/browser/?library=Clp)** - Steepest edge pivot selection for dual simplex

## References

- Forrest & Goldfarb, "Steepest-edge simplex algorithms for LP",
     Mathematical Programming 57 (1992) 341-374
- Harris, "Pivot selection methods of the Devex LP code",
     Mathematical Programming 5 (1973) 1-28

Implements the steepest edge algorithm for choosing the leaving variable
in dual simplex. Instead of choosing the most infeasible row (Dantzig),
steepest edge normalizes by the squared norm of the tableau row, selecting
the direction of steepest improvement in the dual objective.

This is the recommended pivot strategy - it typically requires fewer
iterations than Dantzig, especially on degenerate problems.
