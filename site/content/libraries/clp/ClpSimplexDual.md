+++
title = "ClpSimplexDual"
description = "Dual simplex algorithm implementation"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpSimplexDual.hpp"
+++

## Algorithm

<div class="algorithm-card">

Dual Simplex Method:
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

<div class="math">

min $c^{T}$ x s.t. Ax=b, l≤x≤u (primal)
Dual: max $b^{T}$ y s.t. $A^{T}$ y + s = c, $s_{j}$≥0 for $x_{j}$ at lower, $s_{j}$≤0 for $x_{j}$ at upper
Reduced cost: $s_{j}$ = $c_{j}$ - $$a_{j}$^{T}$ y where y = B^{-T} $c_{B}$
Dual feasible when reduced costs have correct signs for non-basic variables.
Ratio test: θ* = min{$s_{j}$/$r_{j}$ : $r_{j}$ has correct sign} determines entering var.

</div>

**Complexity:** $O($m^{2}$ n)$ per iteration typical (dominated by BTRAN/FTRAN).
Iteration count highly problem-dependent. Often faster than primal simplex
for problems with many constraints, especially after adding cuts in B&B.

<div class="refs">

**References:**
- Forrest & Goldfarb, "Steepest-edge simplex algorithms for LP",      Mathematical Programming 57 (1992) 341-374

</div>

</div>

## See Also

- ClpSimplex for the base simplex class
- ClpSimplexPrimal for primal simplex variant
- ClpDualRowPivot for pivot row selection strategies
- ClpDualRowSteepest, ClpDualRowDantzig for specific strategies

## Source

Header file: `src/ClpSimplexDual.hpp`

