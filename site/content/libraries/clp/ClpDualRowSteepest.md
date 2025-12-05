+++
title = "ClpDualRowSteepest"
description = "Steepest edge pivot selection for dual simplex"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpDualRowSteepest.hpp"
+++

## Algorithm

<div class="algorithm-card">

Steepest Edge Dual Pivot Selection:
Selects leaving variable (pivot row) by normalizing infeasibility by edge weight.
Instead of choosing most infeasible basic variable (Dantzig), computes:
  score_i = (infeasibility_i)² / weight_i
where weight_i = ||r_i||² = ||e_i^T B^{-1}||² is squared norm of i-th row of B^{-1}.

Weight update after pivot in row p with column entering:
  weight_i := weight_i - 2*(r_ip/r_pp)*v_i + (r_ip/r_pp)²*weight_p
where r is pivot row and v is BTRAN of pivot column. This preserves sparsity.

Three modes: uninitialized (1s), full (exact weights), partial (sparse scan).
Maintains infeasibility list for efficient scanning of only violated rows.

<div class="math">

$$Edge weight: γ_{i} = ||B^{-T}e_{i}||² = (i-th row of B^{-1})^{T}(i-th row of B^{-1})$$
Normalized ratio: d_i/γ_i where d_i is dual infeasibility of row i.
$$Update formula from BTRAN column: v = B^{-T}a_{j} gives γ_{i}' = γ_{i} - 2α_{i} v_{i} + α_i² γ_{p}$$
$$\text{ where }α_{i} = r_ip/r_pp is multiplier \text{ for }row i in elimination.$$

</div>

**Complexity:** $O(m)$ per pivot for weight updates (sparse operations).
Full recomputation $O(m²)$ but rare. Typically 30-50% fewer iterations than Dantzig.

<div class="refs">

**References:**
- Forrest & Goldfarb, "Steepest-edge simplex algorithms for LP",      Mathematical Programming 57 (1992) 341-374

</div>

</div>

## See Also

- "Implementing the Dantzig-Wolfe decomposition" by Forrest & Goldfarb
     for the steepest edge algorithm
- ClpDualRowPivot for the base interface
- ClpDualRowDantzig for simpler but often slower alternative
- [ClpSimplexDual](/libraries/clp/clpsimplexdual/) for the dual simplex algorithm

## Source

Header file: [`src/ClpDualRowSteepest.hpp`](/browser/?library=Clp&file=src/ClpDualRowSteepest.hpp)

