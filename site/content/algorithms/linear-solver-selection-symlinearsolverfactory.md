+++
title = "Linear Solver Selection (SymLinearSolverFactory)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

HSL solvers (preferred): MA27/57 (multifrontal), MA77/86/97 (out-of-core)
  Alternatives: MUMPS (parallel), Pardiso (MKL/project), WSMP, SPRAL
  Key requirement: handle indefinite symmetric matrices with inertia detection.

## Mathematical Formulation

<div class="math-block">

[W + Σ  A'] [Δx]   [r_x]
        [A      0 ] [Δy] = [r_c]
  where W = ∇²L (Hessian of Lagrangian), Σ = X⁻¹Z (diagonal),
  A = ∇c(x)' (Jacobian). Solve via sparse symmetric factorization.

</div>

## Complexity

Per iteration: O(n³) for dense, O(nnz^{1.5-2}) for sparse
  Total: O(iterations × linear_solve_cost) where iterations ~ O(√n) typical

## Implementations

### Ipopt

- **[IpAlgBuilder.hpp](/browser/?library=Ipopt)** - Builder pattern for constructing configured IpoptAlgorithm

AlgorithmBuilder assembles a complete IpoptAlgorithm from components
based on user options. This implements the Builder design pattern,
centralizing the complex construction logic.

Build order (with dependency chain):
1. SymLinearSolver (MA27/57/77/86/97, MUMPS, Pardiso, WSMP, etc.)
2. AugSystemSolver (wraps SymLinearSolver for augmented system)
3. PDSystemSolver (solves full primal-dual system)
4. SearchDirectionCalculator, EqMultiplierCalculator
5. IterateInitializer, LineSearch, MuUpdate, ConvergenceCheck

Customization: Subclass and override virtual Build* methods,
or provide custom_solver in constructor.

## References

- Nocedal, J. and Wright, S.J. (2006). "Numerical Optimization".
       Springer, Chapter 19 (Interior-Point Methods).
- Fiacco, A.V. and McCormick, G.P. (1968). "Nonlinear Programming:
       Sequential Unconstrained Minimization Techniques". Wiley.
- Mehrotra, S. (1992). "On the implementation of a primal-dual
       interior point method". SIAM J. Optimization 2(4):575-601.
- Wächter, A. and Biegler, L.T. (2006). "On the implementation
       of an interior-point filter line-search algorithm for large-scale
       nonlinear programming". Math. Programming 106(1):25-57.
