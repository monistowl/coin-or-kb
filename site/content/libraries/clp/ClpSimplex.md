+++
title = "ClpSimplex"
description = "Main simplex solver class - orchestrates primal and dual simplex algorithms"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpSimplex.hpp"
+++

## Algorithm

<div class="algorithm-card">

Simplex Method for Linear Programming:
  Maintains a basic feasible solution (BFS) at a vertex of the polytope.
  Each iteration moves along an edge to an adjacent vertex with better objective.
  - Primal simplex: maintains primal feasibility, achieves dual feasibility
  - Dual simplex: maintains dual feasibility, achieves primal feasibility
  Terminates when both primal and dual feasibility achieved (optimality).

**Complexity:** $O(2^n)$ worst-case (Klee-Minty), but typically polynomial in practice.
  Per-iteration cost: $O(m²)$ for basis update + $O(mn)$ for pricing.
  Iteration count: typically $O(m)$ to $O(3m)$ for practical problems.

<div class="refs">

**References:**
- Dantzig, G.B. (1963). "Linear Programming and Extensions".   Princeton University Press. [Original simplex method]
- Forrest, J.J. and Goldfarb, D. (1992). "Steepest-edge simplex algorithms   for linear programming". Math. Programming 57:341-374. [Steepest edge pricing]  @note The algorithm_ member indicates variant: positive=primal, negative=dual
- Wright, S.J. (1997). "Primal-Dual Interior-Point Methods". SIAM.

</div>

</div>

## See Also

- ClpModel for problem data storage
- [ClpSimplexDual](/libraries/clp/clpsimplexdual/) for dual simplex implementation
- [ClpSimplexPrimal](/libraries/clp/clpsimplexprimal/) for primal simplex implementation
- [ClpFactorization](/libraries/clp/clpfactorization/) for basis factorization
- ClpDualRowPivot, ClpPrimalColumnPivot for pivot selection strategies
- [CoinFactorization](/libraries/coinutils/coinfactorization/) in CoinUtils for the underlying LU factorization

## Source

Header file: [`src/ClpSimplex.hpp`](/browser/?library=Clp&file=src/ClpSimplex.hpp)

