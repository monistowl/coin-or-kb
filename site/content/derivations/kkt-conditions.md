+++
title = "KKT Conditions"
description = "Deriving the Karush-Kuhn-Tucker optimality conditions"
weight = 2

[extra]
prerequisites = ["Lagrangian", "convexity"]
related_algorithms = ["interior_point_method", "newton_method", "active_set_method"]
+++

# Karush-Kuhn-Tucker Conditions

The KKT conditions are the foundation of constrained optimization. They provide necessary conditions for a point to be optimal, and under convexity, sufficient conditions as well. Every serious optimization algorithm ultimately solves some form of KKT system.

## Setup

Consider the general nonlinear program (NLP):

$$\min_{x} \quad f(x) \quad \text{subject to} \quad g_i(x) \leq 0, \; i = 1, \ldots, m \quad h_j(x) = 0, \; j = 1, \ldots, p$$

where $f, g_i, h_j : \mathbb{R}^n \to \mathbb{R}$ are continuously differentiable.

**Key insight**: At a constrained optimum, the gradient of the objective must be "blocked" by the gradients of the active constraints. The KKT conditions make this precise.

---

## The Lagrangian

Define the **Lagrangian function**:

$$L(x, \lambda, \mu) = f(x) + \sum_{i=1}^m \lambda_i g_i(x) + \sum_{j=1}^p \mu_j h_j(x)$$

where $\lambda_i \geq 0$ are multipliers for inequality constraints and $\mu_j$ (unrestricted) are multipliers for equality constraints.

**Interpretation**: The Lagrangian relaxes constraints by adding penalty terms. The multipliers $\lambda_i, \mu_j$ measure how much each constraint "costs" at optimum.

---

## The KKT Conditions

**Theorem (Karush-Kuhn-Tucker)**: Let $x^*$ be a local minimum satisfying a constraint qualification (e.g., LICQ). Then there exist multipliers $\lambda^* \geq 0$ and $\mu^*$ such that:

1. **Stationarity**:
$$\nabla_x L(x^*, \lambda^*, \mu^*) = \nabla f(x^*) + \sum_{i=1}^m \lambda_i^* \nabla g_i(x^*) + \sum_{j=1}^p \mu_j^* \nabla h_j(x^*) = 0$$

2. **Primal Feasibility**:
$$g_i(x^*) \leq 0 \quad \forall i, \qquad h_j(x^*) = 0 \quad \forall j$$

3. **Dual Feasibility**:
$$\lambda_i^* \geq 0 \quad \forall i$$

4. **Complementary Slackness**:
$$\lambda_i^* \cdot g_i(x^*) = 0 \quad \forall i$$

---

## Key Lemmas

### Lemma 1: Farkas' Lemma (Alternative Theorem)

**Statement**: Exactly one of the following has a solution:
- System I: $Ax = b$, $x \geq 0$
- System II: $A^T y \geq 0$, $b^T y < 0$

**Proof sketch**: Follows from LP duality. If the primal $\min\{0^T x : Ax = b, x \geq 0\}$ is feasible, its dual has value 0, blocking System II. ∎

**Significance**: Farkas' lemma characterizes when a linear system has a nonnegative solution — the core tool for deriving KKT conditions.

### Lemma 2: Linear Independence Constraint Qualification (LICQ)

**Definition**: LICQ holds at $x^*$ if the gradients of active constraints are linearly independent:
$$\{\nabla g_i(x^*) : g_i(x^*) = 0\} \cup \{\nabla h_j(x^*)\}$$ are linearly independent.

**Why it matters**: Without a constraint qualification, the KKT conditions may fail. For example, if $g_1 = g_2$ (redundant constraints), their gradients are parallel, and the "right" multipliers become non-unique or unbounded.

---

## Proof of KKT Conditions

**Setup**: Let $x^*$ be a local minimum satisfying LICQ. Define:
- Active inequality indices: $\mathcal{A} = \{i : g_i(x^*) = 0\}$
- Linearized feasible cone: $\mathcal{F} = \{d : \nabla g_i(x^*)^T d \leq 0 \, \forall i \in \mathcal{A}, \; \nabla h_j(x^*)^T d = 0 \, \forall j\}$

**Step 1**: At a local minimum, no feasible descent direction exists.

A direction $d$ is a descent direction if $\nabla f(x^*)^T d < 0$.

A direction $d$ is feasible (to first order) if $d \in \mathcal{F}$.

Claim: $\nabla f(x^*)^T d \geq 0$ for all $d \in \mathcal{F}$.

*Proof*: If $\nabla f(x^*)^T d < 0$ for some $d \in \mathcal{F}$, then for small $t > 0$:
- $f(x^* + td) < f(x^*)$ (descent)
- $g_i(x^* + td) < 0$ for $i \notin \mathcal{A}$ (inactive constraints stay inactive)
- $g_i(x^* + td) \approx g_i(x^*) + t \nabla g_i(x^*)^T d \leq 0$ for $i \in \mathcal{A}$
- $h_j(x^* + td) \approx 0$

This contradicts local optimality. ∎

**Step 2**: Apply Farkas' lemma.

We've shown that the system:
$$\nabla f(x^*)^T d < 0, \quad \nabla g_i(x^*)^T d \leq 0 \; (i \in \mathcal{A}), \quad \nabla h_j(x^*)^T d = 0$$
has no solution.

By Farkas' lemma (extended to mixed inequalities/equalities), this is equivalent to the existence of $\lambda_i^* \geq 0$ (for $i \in \mathcal{A}$) and $\mu_j^*$ such that:

$$\nabla f(x^*) + \sum_{i \in \mathcal{A}} \lambda_i^* \nabla g_i(x^*) + \sum_j \mu_j^* \nabla h_j(x^*) = 0$$

**Step 3**: Set $\lambda_i^* = 0$ for $i \notin \mathcal{A}$.

This gives complementary slackness: $\lambda_i^* g_i(x^*) = 0$ for all $i$.

For inactive constraints ($g_i(x^*) < 0$), we have $\lambda_i^* = 0$.
For active constraints ($g_i(x^*) = 0$), the product is zero regardless of $\lambda_i^*$. ∎

---

## KKT for Convex Problems

**Theorem**: If $f$ and $g_i$ are convex, and $h_j$ are affine, then the KKT conditions are both necessary and sufficient for global optimality.

**Proof of sufficiency**: Suppose $(x^*, \lambda^*, \mu^*)$ satisfies KKT. For any feasible $x$:

$$f(x) \geq f(x^*) + \nabla f(x^*)^T(x - x^*) \quad \text{(convexity of } f\text{)}$$

From stationarity:
$$\nabla f(x^*) = -\sum_i \lambda_i^* \nabla g_i(x^*) - \sum_j \mu_j^* \nabla h_j(x^*)$$

Substituting:
$$f(x) \geq f(x^*) - \sum_i \lambda_i^* \nabla g_i(x^*)^T(x - x^*) - \sum_j \mu_j^* \nabla h_j(x^*)^T(x - x^*)$$

By convexity of $g_i$: $g_i(x) \geq g_i(x^*) + \nabla g_i(x^*)^T(x - x^*)$

So: $\nabla g_i(x^*)^T(x - x^*) \leq g_i(x) - g_i(x^*) \leq g_i(x)$ (using $g_i(x^*) \leq 0$)

Similarly for equalities: $\nabla h_j(x^*)^T(x - x^*) = h_j(x) - h_j(x^*) = h_j(x) = 0$.

Thus:
$$f(x) \geq f(x^*) - \sum_i \lambda_i^* g_i(x) \geq f(x^*)$$

since $\lambda_i^* \geq 0$ and $g_i(x) \leq 0$. ∎

---

## Connection to Code

### Interior Point Methods (Ipopt)

Ipopt solves KKT systems at each iteration. The barrier subproblem:

$$\min_x \quad f(x) - \mu \sum_i \ln(s_i) \quad \text{s.t.} \quad g(x) + s = 0, \; h(x) = 0$$

has KKT conditions (dropping the barrier interpretation):
```
∇f(x) + ∇g(x)λ + ∇h(x)μ = 0     (stationarity)
g(x) + s = 0                     (primal feasibility)
h(x) = 0                         (primal feasibility)
SΛe = μe                         (perturbed complementarity)
```

Newton's method is applied to this system. See `IpIpoptNLP.hpp` for the interface.

### Active Set Methods (qpOASES)

Active set methods explicitly track which constraints are active:
```cpp
// Working set W = {i : constraint i treated as equality}
// At each iteration, solve the equality-constrained subproblem:
//   min ½x'Hx + g'x  s.t.  A_W x = b_W
// Then check KKT multipliers to add/drop constraints
```

The multiplier $\lambda_i$ tells us whether to drop constraint $i$ from the working set (if $\lambda_i < 0$ for an inequality constraint).

---

## Summary

| Condition | Intuition |
|-----------|-----------|
| Stationarity | Gradient of objective balanced by constraint gradients |
| Primal feasibility | Solution satisfies constraints |
| Dual feasibility | Inequality multipliers nonnegative |
| Complementary slackness | Either constraint inactive OR multiplier zero |

The KKT conditions unify LP, QP, and NLP. Every optimization algorithm is ultimately solving $\nabla_x L = 0$ plus the complementarity conditions.
