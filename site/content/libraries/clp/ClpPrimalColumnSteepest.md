+++
title = "ClpPrimalColumnSteepest"
description = "Steepest edge and Devex pivot selection for primal simplex"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpPrimalColumnSteepest.hpp"
+++

## Algorithm

<div class="algorithm-card">

Steepest Edge and Devex Primal Pivot Selection:
Selects entering variable (pivot column) by normalizing reduced cost by weight.
Instead of choosing most negative reduced cost (Dantzig), computes:
  score_j = (reduced_cost_j)² / weight_j
Steepest edge: weight_j = ||d_j||² = ||B^{-1}a_j||² (exact column norm)
Devex: approximate weights, reference framework tracks recent pivots.

Modes: 0=exact Devex, 1=full steepest, 2=partial Devex (sparse scan),
3=auto-switch 0/2, 4=partial Dantzig then switch. Mode 3 is default.

Weight update after pivot: uses FTRAN result d = B^{-1}a_j directly.
Steepest: weight_k := ||d_k||² computed from tableau column.
Devex: weight_k := max(weight_k, (d_k/d_p)² * weight_p) for columns in ref set.

<div class="math">

$$Column weight: γ_{j} = ||B^{-1}a_{j}||² = d_{j}^{T} d_{j} \text{ where }d_{j} is FTRAN of a_{j}.$$
Normalized ratio: |c̄_j|/√γ_j gives steepest descent direction in primal space.
Devex approximation: track reference set R, update γ_j ≈ max over iterations.

</div>

**Complexity:** Steepest: $O(m²)$ per iteration (FTRAN for each candidate column).
Devex: $O(m)$ per pivot with reference framework. Typically 30-50% fewer
iterations than Dantzig at modest extra cost per iteration.

<div class="refs">

**References:**
- Forrest & Goldfarb, "Steepest-edge simplex algorithms for LP",      Mathematical Programming 57 (1992) 341-374
- Harris, "Pivot selection methods of the Devex LP code",      Mathematical Programming 5 (1973) 1-28  Implements advanced pivot column selection strategies for primal simplex: - Steepest Edge: normalizes reduced costs by column norms for faster convergence - Devex: approximate steepest edge with cheaper weight updates  The mode parameter controls behavior: - 0: Exact Devex - 1: Full steepest edge - 2: Partial exact Devex (only scans some nonbasics) - 3: Switches between 0 and 2 based on factorization (default) - 4: Starts partial Dantzig/Devex, may switch to 0 or 2

</div>

</div>

## See Also

- "Implementing the Dantzig-Wolfe decomposition" by Forrest & Goldfarb
- ClpPrimalColumnPivot for the base interface
- ClpPrimalColumnDantzig for simpler Dantzig rule
- [ClpSimplexPrimal](/coin-or-kb/libraries/clp/clpsimplexprimal/) for the primal simplex algorithm

## Source

Header file: [`src/ClpPrimalColumnSteepest.hpp`](/coin-or-kb/browser/?library=Clp&file=src/ClpPrimalColumnSteepest.hpp)

