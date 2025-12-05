+++
title = "Simplex Convergence"
description = "Why the simplex method converges to an optimal solution"
weight = 1

[extra]
prerequisites = ["linear_programming", "basis"]
related_algorithms = ["simplex_method", "primal_simplex", "dual_simplex"]
+++

# Simplex Convergence

This derivation proves that the simplex method converges to an optimal solution (or detects unboundedness) in finite time. We'll build up through the geometry of LP, the structure of basic feasible solutions, and finally the convergence proof itself.

## Setup

Consider the linear program in standard form:

$$\min \quad c^T x \quad \text{subject to} \quad Ax = b, \quad x \geq 0$$

where $A \in \mathbb{R}^{m \times n}$ has full row rank ($\text{rank}(A) = m$), $b \in \mathbb{R}^m$, and $c \in \mathbb{R}^n$.

**Key insight**: The feasible region $\{x : Ax = b, x \geq 0\}$ is a *polyhedron* (intersection of halfspaces). The simplex method exploits the fact that if an optimum exists, it occurs at a *vertex* of this polyhedron.

---

## Key Lemmas

### Lemma 1: Basic Feasible Solutions = Vertices

**Statement**: A point $x$ is a vertex of the feasible polyhedron if and only if $x$ is a *basic feasible solution* (BFS) — meaning the columns of $A$ corresponding to positive components of $x$ are linearly independent.

**Proof**:

($\Rightarrow$) Let $x$ be a vertex. Suppose the columns $\{A_j : x_j > 0\}$ are linearly dependent. Then there exists nonzero $d$ with $A d = 0$ and $d_j = 0$ for all $j$ with $x_j = 0$.

For small $\epsilon > 0$, both $x + \epsilon d$ and $x - \epsilon d$ are feasible (they satisfy $Ax = b$ and remain nonnegative for small enough $\epsilon$). But then:

$$x = \frac{1}{2}(x + \epsilon d) + \frac{1}{2}(x - \epsilon d)$$

This contradicts $x$ being a vertex (not a convex combination of other feasible points). ∎

($\Leftarrow$) Let $x$ be a BFS with basis $B$. Suppose $x = \lambda y + (1-\lambda) z$ for feasible $y, z$ and $0 < \lambda < 1$. For any $j \notin B$, we have $x_j = 0$. Since $y_j \geq 0$ and $z_j \geq 0$, and $\lambda y_j + (1-\lambda) z_j = 0$, we must have $y_j = z_j = 0$.

So $y$ and $z$ are both supported on $B$, meaning $y = B^{-1} b = z = x$. Thus $x$ cannot be written as a proper convex combination — it's a vertex. ∎

### Lemma 2: Finite Number of BFS

**Statement**: There are at most $\binom{n}{m}$ basic feasible solutions.

**Proof**: Each BFS corresponds to a choice of $m$ columns of $A$ to form the basis. There are $\binom{n}{m}$ such choices. (Most choices won't give a feasible solution, but this bounds the total.) ∎

### Lemma 3: Optimum at a Vertex (if it exists)

**Statement**: If the LP has a finite optimum, it is attained at a vertex.

**Proof**: Let $P = \{x : Ax = b, x \geq 0\}$ be the feasible polyhedron (assumed non-empty and bounded below in the objective direction).

Let $x^*$ be an optimal solution. If $x^*$ is a vertex, we're done. Otherwise, $x^*$ lies in the relative interior of some face $F$ of $P$. Moving along any direction in $F$ must preserve the objective (otherwise we could improve), so all of $F$ is optimal. The face $F$ itself is a polyhedron, so by induction on dimension, it contains a vertex — which is also a vertex of $P$. ∎

---

## Main Theorem: Finite Convergence

**Theorem (Simplex Convergence)**: The simplex method terminates in at most $\binom{n}{m}$ iterations, either finding an optimal BFS or detecting unboundedness.

**Proof**:

The simplex method maintains a BFS $x$ with basis $B$. At each iteration:

1. **Compute reduced costs**: $\bar{c}_j = c_j - c_B^T B^{-1} A_j$ for non-basic $j$.

2. **Check optimality**: If $\bar{c}_j \geq 0$ for all non-basic $j$, the current BFS is optimal. (This is the dual feasibility condition — see [LP Duality](@/derivations/lp-duality.md).)

3. **Select entering variable**: Choose $j$ with $\bar{c}_j < 0$ (improving direction).

4. **Compute direction**: $d = B^{-1} A_j$ (the $j$-th column expressed in the basis).

5. **Check unboundedness**: If $d \leq 0$, the objective is unbounded below. (We can increase $x_j$ indefinitely while staying feasible.)

6. **Ratio test**: Otherwise, $\theta^* = \min\{x_{B_i}/d_i : d_i > 0\}$ gives the maximum step length.

7. **Pivot**: The variable achieving the minimum leaves the basis; $j$ enters.

**Key observation**: After pivoting, the objective value changes by $\theta^* \cdot \bar{c}_j < 0$ (since $\theta^* > 0$ and $\bar{c}_j < 0$). So the objective strictly decreases (assuming $\theta^* > 0$, i.e., non-degenerate pivot).

Since there are finitely many BFS (Lemma 2), and we visit each at most once (strict improvement), the algorithm terminates. ∎

---

## Handling Degeneracy

**Problem**: If $\theta^* = 0$ (degenerate pivot), the objective doesn't decrease, and we might cycle through bases indefinitely.

**Solution (Bland's Rule)**: Always choose the entering and leaving variables with the *smallest index* among eligible candidates. This anti-cycling rule guarantees termination.

**Alternative (Perturbation)**: Add small perturbations to $b$ to make all BFS non-degenerate. Clp uses *cost perturbation* (inherited from OSL) — perturbing $c$ instead of $b$.

---

## Connection to Code

In Clp's dual simplex (`ClpSimplexDual.cpp`):

```cpp
// Ratio test - finds leaving variable
// The "updatedDualBound_" is the fake bound for handling
// dual infeasibility in a single-phase approach
int ClpSimplexDual::dualColumn(CoinIndexedVector* rowArray, ...)
{
    // ... pivotRow = argmin ratio test ...
}
```

The three nested loops in `ClpSimplexDual::dual()` correspond to:
- **Outer loop**: Adjust fake bounds for dual feasibility
- **Middle loop**: Refactorize when numerical errors accumulate
- **Inner loop**: Pivot iterations

Anti-cycling is handled via perturbation (`perturbation_` flag) rather than Bland's rule, as perturbation is faster in practice.

---

## Summary

| Result | Significance |
|--------|--------------|
| BFS ↔ Vertex | Restricts search to finitely many points |
| Optimum at vertex | Justifies searching only vertices |
| Strict improvement | Each iteration makes progress |
| Finite BFS | Bounds iteration count |
| Anti-cycling rules | Handles degenerate cases |

The simplex method's practical efficiency comes from the fact that it typically visits far fewer than $\binom{n}{m}$ bases — the worst-case bound is almost never achieved.
