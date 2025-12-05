+++
title = "Interior Point Method (Barrier Method)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Interior Point Methods"
implementation_count = 1
+++

## Why This Matters

Interior point methods are the theoretical breakthrough that proved LP could be solved in polynomial time. While simplex has exponential worst-case complexity (though excellent average case), interior point is *guaranteed* to converge quickly.

**When to use interior point**:
- **Very large problems**: Interior point iteration count grows as $O(\sqrt{n})$, not $O(m)$ like simplex
- **Dense problems**: When the constraint matrix is dense, interior point's matrix operations are competitive
- **No warm-start needed**: If you're solving one problem from scratch, interior point may be faster

**When NOT to use interior point**:
- **Re-optimization**: Interior point can't warm-start from a previous solution the way simplex can
- **Branch-and-bound**: The inability to warm-start makes interior point impractical for MIP
- **Vertex solutions needed**: Interior point finds points in the interior; you need crossover to get a vertex

**The key insight**: Interior point replaces the "walk along edges" of simplex with a smooth path through the middle of the feasible region. Mathematically elegant, but the lack of warm-starting limits its applications.

---

Solves LP by following central path through interior of feasible region.
Main variant is Mehrotra predictor-corrector:
1. Affine scaling direction: solve Newton system for complementarity
2. Centering direction: correct toward central path with adaptive μ
3. Combined step: predictor + corrector with step length limiting
4. Update (x, y, s) and reduce barrier parameter μ

Per iteration solves normal equations: (ADA^T)Δy = rhs
where D is diagonal scaling matrix from current iterate.
Cholesky factorization of ADA^T is computational bottleneck.

Converges in O(√n log(1/ε)) iterations (polynomial complexity).
Each iteration O(m²n + m³) for forming/factoring normal equations.

## Mathematical Formulation

<div class="math-block">

Barrier problem: min c^Tx - μ∑log(x_j-l_j) - μ∑log(u_j-x_j)
KKT conditions: Ax=b, A^Ty+s=c, XSe=μe (complementarity)
Normal equations: (ADA^T)Δy = A(D*r_c - X^{-1}r_xs) + r_b
where D = X/S diagonal, r_b, r_c, r_xs are residuals.

</div>

## Complexity

O(√n log(1/ε)) iterations for ε-optimality.
Per iteration: O(nnz(A)m) to form ADA^T, O(m³) for dense Cholesky,
or O(nnz(L)²) for sparse Cholesky. Total typically O(n^{1.5}) to O(n³).

## Implementations

### Clp

- **[ClpInterior.hpp](/browser/?library=Clp)** - Interior point (barrier) method for LP

## References

- Mehrotra, "On the implementation of a primal-dual interior point method",
     SIAM Journal on Optimization 2 (1992) 575-601
- Andersen & Andersen, "The MOSEK interior point optimizer for LP",
     High Performance Optimization, Kluwer (2000)

Implements interior point methods as an alternative to simplex for LP.
Interior point follows a central path through the interior of the feasible
region, converging to optimality. Often faster than simplex for very large
or dense problems.

Two main variants supported:
- Predictor-Corrector: Standard Mehrotra-style algorithm
- PDCO: Primal-Dual Barrier method with regularization

Requires Cholesky factorization for the normal equations A*D*A'.
Multiple Cholesky backends available (dense, MUMPS, TAUCS, etc.)
