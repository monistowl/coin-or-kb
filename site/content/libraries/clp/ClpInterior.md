+++
title = "ClpInterior"
description = "Interior point (barrier) method for LP"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpInterior.hpp"
+++

## Algorithm

<div class="algorithm-card">

Interior Point Method (Barrier Method):
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

<div class="math">

Barrier problem: min c^Tx - μ∑log(x_j-l_j) - μ∑log(u_j-x_j)
$$KKT conditions: Ax=b, A^Ty+s=c, XSe=μe (complementarity)$$
$$Normal equations: (ADA^{T})Δy = A(D*r_{c} - X^{-1}r_xs) + r_{b}$$
$$\text{ where }D = X/S diagonal, r_{b}, r_{c}, r_xs are residuals.$$

</div>

**Complexity:** $O(√n log(1/ε)$) iterations for ε-optimality.
Per iteration: $O(nnz(A)$m) to form ADA^T, $O(m³)$ for dense Cholesky,
or $O(nnz(L)$²) for sparse Cholesky. Total typically $O(n^{1.5})$ to $O(n³)$.

<div class="refs">

**References:**
- Mehrotra, "On the implementation of a primal-dual interior point method",      SIAM Journal on Optimization 2 (1992) 575-601
- Andersen & Andersen, "The MOSEK interior point optimizer for LP",      High Performance Optimization, Kluwer (2000)  Implements interior point methods as an alternative to simplex for LP. Interior point follows a central path through the interior of the feasible region, converging to optimality. Often faster than simplex for very large or dense problems.  Two main variants supported: - Predictor-Corrector: Standard Mehrotra-style algorithm - PDCO: Primal-Dual Barrier method with regularization  Requires Cholesky factorization for the normal equations A*D*A'. Multiple Cholesky backends available (dense, MUMPS, TAUCS, etc.)

</div>

</div>

## See Also

- ClpPredictorCorrector for the predictor-corrector implementation
- ClpPdco for PDCO variant
- ClpCholeskyBase for Cholesky factorization interface
- [ClpSimplex](/coin-or-kb/libraries/clp/clpsimplex/) for the alternative simplex method

## Source

Header file: [`src/ClpInterior.hpp`](/coin-or-kb/browser/?library=Clp&file=src/ClpInterior.hpp)

