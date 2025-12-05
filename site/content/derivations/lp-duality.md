+++
title = "LP Duality"
description = "Strong duality theorem and complementary slackness for linear programming"
weight = 3

[extra]
prerequisites = ["linear_programming", "Lagrangian"]
related_algorithms = ["simplex_method", "dual_simplex", "interior_point_method"]
+++

# LP Duality

LP duality is one of the most beautiful results in optimization. Every linear program has a "dual" LP, and their optimal values coincide. This isn't just theoretical elegance — it's the foundation of the dual simplex method, sensitivity analysis, and economic interpretations of shadow prices.

## Setup

Consider the **primal** LP in standard form:

$$\text{(P)} \quad \min_{x} \quad c^T x \quad \text{subject to} \quad Ax = b, \quad x \geq 0$$

The **dual** LP is:

$$\text{(D)} \quad \max_{y} \quad b^T y \quad \text{subject to} \quad A^T y \leq c$$

**Notation**:
- $x \in \mathbb{R}^n$ (primal variables)
- $y \in \mathbb{R}^m$ (dual variables, one per constraint)
- $A \in \mathbb{R}^{m \times n}$

---

## Weak Duality

**Theorem (Weak Duality)**: For any primal feasible $x$ and dual feasible $y$:

$$b^T y \leq c^T x$$

**Proof**: Since $Ax = b$ and $A^T y \leq c$:

$$b^T y = (Ax)^T y = x^T (A^T y) \leq x^T c = c^T x$$

The inequality uses $A^T y \leq c$ and $x \geq 0$. ∎

**Corollary**: If primal feasible $x^*$ and dual feasible $y^*$ achieve $c^T x^* = b^T y^*$, then both are optimal.

---

## Strong Duality

**Theorem (Strong Duality)**: If (P) has a finite optimum, then (D) also has a finite optimum, and

$$\min_x \{c^T x : Ax = b, x \geq 0\} = \max_y \{b^T y : A^T y \leq c\}$$

**Proof via Simplex**: Suppose the simplex method finds optimal basis $B$ with optimal solution $x^*$. The basic variables are:

$$x_B^* = B^{-1} b \geq 0$$

and non-basic variables $x_N^* = 0$.

Define the dual solution:

$$y^* = (B^{-1})^T c_B = B^{-T} c_B$$

**Claim 1**: $y^*$ is dual feasible.

For any column $j$, the reduced cost is:
$$\bar{c}_j = c_j - c_B^T B^{-1} A_j = c_j - (y^*)^T A_j$$

At optimality, $\bar{c}_j \geq 0$ for all $j$, which means:
$$c_j \geq (y^*)^T A_j \quad \Rightarrow \quad A^T y^* \leq c$$

So $y^*$ is dual feasible. ∎

**Claim 2**: $c^T x^* = b^T y^*$.

$$c^T x^* = c_B^T x_B^* + c_N^T x_N^* = c_B^T B^{-1} b = (y^*)^T b = b^T y^*$$

By weak duality and matching values, both are optimal. ∎

---

## Complementary Slackness

**Theorem**: Primal feasible $x^*$ and dual feasible $y^*$ are both optimal if and only if:

$$x_j^* \cdot (c_j - (A^T y^*)_j) = 0 \quad \text{for all } j$$

Equivalently, defining slack $s^* = c - A^T y^*$:

$$x_j^* \cdot s_j^* = 0 \quad \text{for all } j$$

**Intuition**: For each variable $j$, either:
- $x_j^* = 0$ (variable is non-basic), or
- $s_j^* = 0$ (dual constraint is tight, i.e., $c_j = (A^T y^*)_j$)

**Proof**:

($\Leftarrow$) Assume complementary slackness. Then:

$$c^T x^* = \sum_j c_j x_j^* = \sum_j (A^T y^*)_j x_j^* = (y^*)^T A x^* = (y^*)^T b = b^T y^*$$

By weak duality and matching values, both are optimal.

($\Rightarrow$) Assume both optimal, so $c^T x^* = b^T y^*$. From the proof of weak duality:

$$c^T x^* - b^T y^* = x^T c - x^T A^T y^* = x^T (c - A^T y^*) = \sum_j x_j^* s_j^* = 0$$

Since $x_j^* \geq 0$ and $s_j^* \geq 0$, we must have $x_j^* s_j^* = 0$ for all $j$. ∎

---

## The Lagrangian Derivation

An alternative (and more general) path to duality uses the Lagrangian:

**Step 1**: Form the Lagrangian for (P):

$$L(x, y) = c^T x + y^T (b - Ax) = b^T y + (c - A^T y)^T x$$

**Step 2**: The dual function is:

$$g(y) = \min_{x \geq 0} L(x, y) = \begin{cases} b^T y & \text{if } c - A^T y \geq 0 \\ -\infty & \text{otherwise} \end{cases}$$

The minimum over $x \geq 0$ is achieved at $x = 0$ when $c - A^T y \geq 0$, giving $g(y) = b^T y$.

**Step 3**: The dual problem is:

$$\max_y g(y) = \max_y \{b^T y : A^T y \leq c\}$$

This is exactly (D). Weak duality follows from:

$$\min_x \max_y L(x, y) \geq \max_y \min_x L(x, y)$$

Strong duality for LP says equality holds (under feasibility).

---

## Duality Pairs

Different LP forms have different duals:

| Primal | Dual |
|--------|------|
| min $c^T x$ | max $b^T y$ |
| $Ax = b$ | $y$ unrestricted |
| $Ax \geq b$ | $y \geq 0$ |
| $Ax \leq b$ | $y \leq 0$ |
| $x \geq 0$ | $(A^T y)_j \leq c_j$ |
| $x$ unrestricted | $(A^T y)_j = c_j$ |

**Mnemonic**:
- Equality constraint ↔ unrestricted variable
- Inequality constraint ↔ sign-restricted variable

---

## Connection to Code

### Dual Simplex (Clp)

The dual simplex maintains dual feasibility (reduced costs have correct signs) while working toward primal feasibility:

```cpp
// In ClpSimplexDual.cpp
// At each iteration:
// 1. Current solution may be primal infeasible (some x_i violates bounds)
// 2. But dual feasible: all reduced costs c_j - c_B' B^{-1} A_j >= 0

// The ratio test finds entering variable that maintains dual feasibility:
// theta* = min{ s_j / r_j : r_j has correct sign }
```

### Sensitivity Analysis

Dual variables measure sensitivity of the optimal value to constraint changes:

$$\frac{\partial z^*}{\partial b_i} = y_i^*$$

If constraint $i$ is relaxed by $\delta$, the optimal value changes by approximately $y_i^* \cdot \delta$.

### Reduced Costs

The reduced cost $\bar{c}_j = c_j - y^T A_j$ measures how much the objective would improve (per unit) if variable $x_j$ entered the basis:
- $\bar{c}_j > 0$: increasing $x_j$ would hurt (for minimization)
- $\bar{c}_j = 0$: $x_j$ could be in the optimal basis
- $\bar{c}_j < 0$: increasing $x_j$ would improve (select as entering variable)

---

## Summary

| Result | Significance |
|--------|--------------|
| Weak duality | Dual provides lower bound on primal |
| Strong duality | Bounds match at optimum |
| Complementary slackness | Links primal/dual solutions |
| Dual from Lagrangian | Generalizes to NLP |
| Reduced costs | Guide simplex pivot selection |

Duality transforms the primal problem into an equivalent maximization. The dual simplex exploits this by maintaining dual feasibility, making it ideal for re-optimization after adding constraints (cuts, branching bounds).
