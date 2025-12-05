+++
title = "Simplex Method for Linear Programming"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Simplex Method"
implementation_count = 1
+++

## Why This Matters

The simplex method is *the* algorithm that made linear programming practical. Almost every commercial and open-source LP solver uses it as the primary algorithm. Understanding simplex is essential because:

- **It's everywhere**: Supply chain optimization, airline scheduling, financial portfolio allocation, and countless other applications depend on it
- **Modern solvers build on it**: Dual simplex is the workhorse for MIP solvers during branch-and-bound
- **The concepts transfer**: Basis matrices, reduced costs, and pivot operations appear throughout optimization

When to use simplex vs interior point:
- **Simplex excels at**: warm-starting (reoptimizing after small changes), sparse problems, problems where you need an optimal vertex
- **Interior point excels at**: very large problems, dense problems, problems where any optimal point suffices

---

Maintains a basic feasible solution (BFS) at a vertex of the polytope.
  Each iteration moves along an edge to an adjacent vertex with better objective.
  - Primal simplex: maintains primal feasibility, achieves dual feasibility
  - Dual simplex: maintains dual feasibility, achieves primal feasibility
  Terminates when both primal and dual feasibility achieved (optimality).

## Complexity

O(2^n) worst-case (Klee-Minty), but typically polynomial in practice.
  Per-iteration cost: O(m²) for basis update + O(mn) for pricing.
  Iteration count: typically O(m) to O(3m) for practical problems.

## Implementations

### Clp

- **[ClpSimplex.hpp](/browser/?library=Clp)** - Main simplex solver class - orchestrates primal and dual simplex algorithms

## References

- Dantzig, G.B. (1963). "Linear Programming and Extensions".
  Princeton University Press. [Original simplex method]
- Forrest, J.J. and Goldfarb, D. (1992). "Steepest-edge simplex algorithms
  for linear programming". Math. Programming 57:341-374. [Steepest edge pricing]

@note The algorithm_ member indicates variant: positive=primal, negative=dual
- Wright, S.J. (1997). "Primal-Dual Interior-Point Methods". SIAM.
