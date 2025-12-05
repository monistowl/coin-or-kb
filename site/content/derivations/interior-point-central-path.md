+++
title = "Interior Point Central Path"
description = "Barrier functions, Newton steps, and polynomial convergence"
weight = 4

[extra]
prerequisites = ["convex_optimization", "KKT_conditions", "newton_method"]
related_algorithms = ["interior_point_method"]
+++

# Interior Point Central Path

Interior point methods revolutionized optimization by proving LP could be solved in polynomial time. Unlike simplex (which walks along edges of the feasible polytope), interior point methods traverse the *interior*, following a smooth "central path" to the optimum.

## Setup

Consider the LP in inequality form:

$$\min_{x} \quad c^T x \quad \text{subject to} \quad Ax \leq b$$

Or equivalently with slacks:

$$\min_{x,s} \quad c^T x \quad \text{subject to} \quad Ax + s = b, \quad s \geq 0$$

**Key idea**: Replace the hard constraint $s \geq 0$ with a *barrier function* that penalizes approaching the boundary.

---

## The Barrier Method

### Logarithmic Barrier

Define the **barrier problem**:

$$\min_{x,s} \quad c^T x - \mu \sum_{i=1}^m \ln(s_i) \quad \text{subject to} \quad Ax + s = b$$

where $\mu > 0$ is the **barrier parameter**.

**Properties**:
- As $s_i \to 0^+$, the term $-\mu \ln(s_i) \to +\infty$, preventing $s_i$ from hitting zero
- As $\mu \to 0$, the barrier penalty diminishes, and solutions approach the original LP optimum
- For each $\mu > 0$, the barrier problem has a unique solution (in the interior)

### The Central Path

The **central path** $\mathcal{C}$ is the set of solutions to the barrier problem as $\mu$ varies:

$$\mathcal{C} = \{(x(\mu), s(\mu)) : \mu > 0\}$$

**Theorem**: The central path converges to an optimal solution of the original LP as $\mu \to 0^+$.

**Proof sketch**: Each point on the central path is the unique minimizer of a strictly convex problem (barrier function is strictly convex). As $\mu \to 0$, the barrier penalty vanishes, and the limit point satisfies the original LP constraints and KKT conditions. ∎

---

## KKT Conditions for the Barrier Problem

The Lagrangian for the barrier problem is:

$$L = c^T x - \mu \sum_i \ln(s_i) + y^T (Ax + s - b)$$

Setting gradients to zero:

$$\nabla_x L = c + A^T y = 0 \quad \Rightarrow \quad A^T y = -c$$

$$\nabla_s L = -\mu S^{-1} e + y = 0 \quad \Rightarrow \quad y = \mu S^{-1} e$$

$$\nabla_y L = Ax + s - b = 0$$

Combining these (and writing $\lambda = -y$ to match standard notation):

$$A^T \lambda = c$$
$$Ax + s = b$$
$$S \lambda = \mu e$$

The last equation $S \lambda = \mu e$ (or $s_i \lambda_i = \mu$ for all $i$) is the **perturbed complementarity** condition. As $\mu \to 0$, this becomes $s_i \lambda_i = 0$, the standard complementary slackness.

---

## Newton's Method for the KKT System

Define the **residuals**:

$$r_{\text{dual}} = c - A^T \lambda$$
$$r_{\text{primal}} = b - Ax - s$$
$$r_{\text{cent}} = S \Lambda e - \mu e$$

where $S = \text{diag}(s)$ and $\Lambda = \text{diag}(\lambda)$.

The Newton step solves:

$$\begin{pmatrix} 0 & A^T & 0 \\ A & 0 & I \\ 0 & S & \Lambda \end{pmatrix} \begin{pmatrix} \Delta x \\ \Delta \lambda \\ \Delta s \end{pmatrix} = \begin{pmatrix} r_{\text{dual}} \\ r_{\text{primal}} \\ r_{\text{cent}} \end{pmatrix}$$

### Reducing to the Normal Equations

From the third block: $S \Delta \lambda + \Lambda \Delta s = r_{\text{cent}}$

Solve for $\Delta s$: $\Delta s = \Lambda^{-1}(r_{\text{cent}} - S \Delta \lambda)$

Substitute into the second block:
$$A \Delta x + \Lambda^{-1}(r_{\text{cent}} - S \Delta \lambda) = r_{\text{primal}}$$
$$A \Delta x - \Lambda^{-1} S \Delta \lambda = r_{\text{primal}} - \Lambda^{-1} r_{\text{cent}}$$

Define $D = S \Lambda^{-1} = \text{diag}(s_i / \lambda_i)$. Then:

$$A \Delta x - D \Delta \lambda = r_{\text{primal}} - \Lambda^{-1} r_{\text{cent}}$$

From the first block: $A^T \Delta \lambda = r_{\text{dual}}$

Eliminate $\Delta x$: multiply second equation by $A D^{-1}$ and substitute:

$$(A D^{-1} A^T) \Delta \lambda = A D^{-1} r_{\text{primal}} - A \Lambda^{-1} r_{\text{cent}} + r_{\text{dual}}$$

This is the **normal equations**: a symmetric positive definite system in $\Delta \lambda$ alone.

---

## The Mehrotra Predictor-Corrector

The practical workhorse of interior point methods:

### Step 1: Affine Scaling Direction (Predictor)

Set $\mu = 0$ in the Newton system to get the "pure Newton" direction toward complementarity:

$$S \Delta \lambda^{\text{aff}} + \Lambda \Delta s^{\text{aff}} = -S \Lambda e$$

### Step 2: Compute Step Length

$$\alpha^{\text{aff}} = \max\{\alpha : s + \alpha \Delta s^{\text{aff}} \geq 0, \; \lambda + \alpha \Delta \lambda^{\text{aff}} \geq 0\}$$

### Step 3: Centering Parameter

Compute the duality gap after the affine step:

$$\mu^{\text{aff}} = \frac{(s + \alpha^{\text{aff}} \Delta s^{\text{aff}})^T (\lambda + \alpha^{\text{aff}} \Delta \lambda^{\text{aff}})}{m}$$

Set the centering parameter:

$$\sigma = \left(\frac{\mu^{\text{aff}}}{\mu}\right)^3$$

where $\mu = s^T \lambda / m$ is the current duality gap.

**Intuition**: If the affine step makes good progress ($\mu^{\text{aff}}$ small), use less centering ($\sigma$ small). If progress is poor, center more.

### Step 4: Corrector Direction

Solve the Newton system with:

$$r_{\text{cent}} = S \Lambda e - \sigma \mu e + \Delta S^{\text{aff}} \Delta \Lambda^{\text{aff}} e$$

The last term is the "corrector" that accounts for the quadratic nature of complementarity.

### Step 5: Step Length and Update

$$\alpha = 0.99 \cdot \max\{\alpha : s + \alpha \Delta s \geq 0, \; \lambda + \alpha \Delta \lambda \geq 0\}$$

Update: $(x, s, \lambda) \leftarrow (x, s, \lambda) + \alpha (\Delta x, \Delta s, \Delta \lambda)$

---

## Polynomial Convergence

**Theorem**: Interior point methods converge to an $\epsilon$-optimal solution in $O(\sqrt{n} \ln(1/\epsilon))$ iterations.

**Key lemmas**:

1. **Duality gap decreases**: Each iteration reduces the duality gap $\mu = s^T \lambda / m$ by a constant factor.

2. **Bounded iterates**: The central path keeps iterates bounded, preventing numerical issues.

3. **Newton convergence**: Near the central path, Newton's method converges quadratically.

**Complexity per iteration**:
- Forming $A D^{-1} A^T$: $O(\text{nnz}(A) \cdot m)$
- Cholesky factorization: $O(m^3)$ dense, $O(\text{nnz}(L)^2)$ sparse
- Back-substitution: $O(m^2)$

**Total**: $O(\sqrt{n} \cdot m^3)$ for dense problems, much better for sparse.

---

## Connection to Code

### Clp's Interior Point (ClpInterior)

```cpp
// ClpInterior.hpp implements barrier method for LP
// Two main variants:
// - Predictor-Corrector (Mehrotra-style)
// - PDCO (regularized primal-dual)

// The normal equations are formed as:
//   (A * D * A') * dy = rhs
// where D = diag(x./z) is the scaling matrix

// Multiple Cholesky backends:
// - ClpCholeskyDense (LAPACK)
// - ClpCholeskyMumps (MUMPS)
// - ClpCholeskyWssmp (WSSMP)
```

### Ipopt (Nonlinear Interior Point)

Ipopt extends these ideas to NLP:

```cpp
// The filter line search replaces the ratio test
// Hessian approximations (L-BFGS, exact) replace the simple D
// Inertia correction handles nonconvexity

// IpIpoptAlg.cpp:
// while (not converged) {
//   1. Solve barrier KKT system (via MA27, MA57, MUMPS, ...)
//   2. Line search with filter
//   3. Update barrier parameter
// }
```

---

## Summary

| Component | Role |
|-----------|------|
| Barrier function | Keeps iterates strictly feasible |
| Central path | Smooth trajectory to optimum |
| Newton system | Computes search direction |
| Normal equations | Efficient linear algebra |
| Predictor-corrector | Accelerates convergence |
| $O(\sqrt{n})$ iterations | Polynomial complexity |

Interior point methods are the theoretical gold standard for LP (polynomial time) and the practical standard for NLP. The trade-off vs. simplex: no warm-starting capability, but excellent worst-case complexity.
