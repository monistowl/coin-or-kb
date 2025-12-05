+++
title = "ClpSimplexPrimal"
description = "Primal simplex algorithm implementation"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpSimplexPrimal.hpp"
+++

## Algorithm

<div class="algorithm-card">

Primal Simplex Method:
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

<div class="math">

$$\min\;c^{T} x \text{ s.t. }Ax=b, l≤x≤u$$
$$Basic solution: x_{B} = B^{-1}b - B^{-1}N x_{N}, with x_{N} \text{ at }bounds.$$
$$\text{Reduced cost: }s_{j} = c_{j} - c_{B}^{T} B^{-1} a_{j} (computed via BTRAN then dot product)$$
$$\text{Ratio test: }θ* = \min\{(x_{B}[i]-l_{i})/d_{i}, (u_{i}-x_{B}[i])/(-d_{i})} \text{ for }feasible step.$$
Primal feasible when l ≤ x ≤ u. Optimal when also s_j ≥ 0 for vars at lower bound.

</div>

**Complexity:** $O(m^{2} n)$ per iteration typical (dominated by FTRAN/BTRAN).
Iteration count varies widely. Often slower than dual simplex but useful
when starting from feasible solution or for problems with few constraints.

<div class="refs">

**References:**
- Dantzig, "Linear Programming and Extensions", Princeton (1963)

</div>

</div>

## See Also

- [ClpSimplex](/libraries/clp/clpsimplex/) for the base simplex class
- [ClpSimplexDual](/libraries/clp/clpsimplexdual/) for dual simplex variant (often faster)
- ClpPrimalColumnPivot for pivot column selection strategies
- [ClpPrimalColumnSteepest](/libraries/clp/clpprimalcolumnsteepest/), ClpPrimalColumnDantzig for specific strategies

## Source

Header file: [`src/ClpSimplexPrimal.hpp`](/browser/?library=Clp&file=src/ClpSimplexPrimal.hpp)

