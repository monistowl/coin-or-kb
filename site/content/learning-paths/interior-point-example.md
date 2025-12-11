+++
title = "Interactive Interior Point Method"
description = "Step through a primal-dual interior point solve with barrier visualization"
template = "interior-point-interactive.html"
weight = 40
+++

This interactive example demonstrates the **Primal-Dual Interior Point Method** for Linear Programming. Watch as iterates follow the central path toward optimality.

## The Problem

The same LP used in the simplex example:

$$\max \quad 3x_1 + 2x_2$$

Subject to:
$$x_1 + x_2 \leq 4 \quad \text{(resource A)}$$
$$2x_1 + x_2 \leq 6 \quad \text{(resource B)}$$
$$x_1, x_2 \geq 0$$

### Interior Point vs. Simplex

While simplex walks along edges of the polytope, interior point methods take a fundamentally different approach:

| Aspect | Simplex | Interior Point |
|--------|---------|----------------|
| **Path** | Along edges (vertices) | Through interior |
| **Iterations** | Can be exponential (rare) | Polynomial guaranteed |
| **Per-iteration cost** | Cheap pivots | Expensive (linear algebra) |
| **Best for** | Sparse, warm-starting | Large, dense problems |

## How Interior Point Works

The key idea is the **logarithmic barrier**:

1. **Barrier function** — add $-\mu \sum_j \log(x_j)$ to prevent variables from hitting zero
2. **Central path** — the set of optimal solutions as $\mu$ varies from $\infty$ to $0$
3. **Newton's method** — solve KKT conditions for the barrier problem
4. **Path following** — reduce $\mu$ gradually, staying near the central path

### The Mathematics

The barrier problem converts inequality constraints to smooth penalties:

$$\min \quad c^T x - \mu \sum_j \log(x_j)$$

subject to $Ax = b$. As $\mu \to 0$, the solution approaches the LP optimum.

The **KKT conditions** for this barrier problem are:
$$Ax = b \quad \text{(primal feasibility)}$$
$$A^T y + s = c \quad \text{(dual feasibility)}$$
$$X S e = \mu e \quad \text{(perturbed complementarity)}$$

where $X = \text{diag}(x)$, $S = \text{diag}(s)$, and $e$ is the all-ones vector.

## What to Watch For

As you step through the iterations:

1. **Central path behavior**: Notice how the iterates stay "centered" — they don't hug the boundary. The barrier term $-\mu \log(x_j)$ creates a repulsive force from the boundary.

2. **Newton direction**: The purple arrow shows the combined predictor-corrector direction. It balances progress toward optimality against staying near the central path.

3. **Barrier reduction**: Watch μ decrease: 2.0 → 1.0 → 0.3 → 0.01 → 0. Each reduction allows the iterate to move closer to the optimal vertex.

4. **Duality gap**: The gap between primal and dual objectives decreases geometrically. This is the key to the polynomial complexity guarantee.

5. **Convergence**: Unlike simplex (which jumps between vertices), interior point smoothly approaches the optimum from inside the feasible region.

## Connection to COIN-OR Code

In Clp, the interior point method is implemented in [ClpInterior](@/libraries/clp/ClpInterior.md):

| Concept | This Example | Clp Implementation |
|---------|--------------|-------------------|
| **Algorithm** | Simple Newton | Mehrotra predictor-corrector |
| **Linear algebra** | Direct solve | Cholesky factorization of $ADA^T$ |
| **Step length** | Fixed α | Line search with safeguards |
| **μ update** | Halving | Adaptive centering parameter |

<div class="code-connection">

**Code Spotlight**: The Mehrotra predictor-corrector in `ClpPredictorCorrector`:

```
// Main iteration loop
while (gap > tolerance && iter < maxIter) {
    // 1. Affine-scaling direction (predictor)
    //    Solve Newton system with μ = 0
    solveKKTSystem(rhs_affine, delta_affine);

    // 2. Compute centering parameter
    //    Based on how much progress affine step makes
    alpha_affine = maxStepLength(delta_affine);
    mu_affine = computeComplementarity(x + alpha*dx, s + alpha*ds);
    sigma = (mu_affine / mu)^3;  // Centering parameter

    // 3. Corrector direction
    //    Re-solve with centering and second-order correction
    rhs_corrector = sigma * mu * e - Δx_aff * Δs_aff;
    solveKKTSystem(rhs_corrector, delta_corrector);

    // 4. Combined step
    delta = delta_affine + delta_corrector;
    alpha = maxStepLength(delta);
    update(x, y, s, alpha * delta);

    mu = computeComplementarity(x, s) / n;
}
```

The normal equations $(ADA^T)\Delta y = \text{rhs}$ are the computational bottleneck. Clp supports multiple Cholesky backends: dense, MUMPS, CHOLMOD, etc.

</div>

## Key Algorithmic Insights

### Why Polynomial Complexity?

Interior point methods guarantee $O(\sqrt{n} \log(1/\epsilon))$ iterations because:
1. Each Newton step approximately halves the duality gap
2. The barrier prevents "zigzagging" that plagues simplex on pathological problems
3. The central path is smooth and well-conditioned

### When to Use Interior Point

Interior point often beats simplex for:
- **Large problems** (millions of variables) — fewer iterations matter more
- **Dense problems** — Cholesky exploits dense structure well
- **Ill-conditioned problems** — less sensitive to degeneracy
- **Parallel solving** — linear algebra parallelizes easily

Simplex often wins for:
- **Sparse problems** — cheap pivots, sparse updates
- **Re-optimization** — warm starting from previous basis
- **Integer programming** — need basis information for branching

## The Central Path Concept

The central path is the curve traced by optimal solutions as μ decreases:

$$\mathcal{C} = \{(x(\mu), y(\mu), s(\mu)) : \mu > 0\}$$

Key properties:
- Always stays strictly feasible (all variables positive)
- Converges to optimal vertex as $\mu \to 0$
- Smooth and analytic — Newton's method converges rapidly
- Natural parametrization of "how close" to optimality

## Try It Below

Use **Next Step** to watch the interior point method in action:
- The **yellow dot** is the current iterate
- The **dashed line** shows the central path
- The **purple arrow** shows the Newton direction
- Watch the **barrier μ** decrease and **duality gap** shrink
- The iterate **smoothly approaches** the optimal corner from inside

