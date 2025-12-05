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

## How Interior Point Works

Unlike simplex (which walks along edges), interior point methods:

1. **Start inside** the feasible region (not at a vertex)
2. **Add barrier terms** μ·log(xⱼ) to keep variables positive
3. **Solve KKT system** to find Newton direction
4. **Step toward optimum** while staying interior
5. **Reduce barrier μ → 0** as we converge

The iterates trace the **central path** — the set of optimal solutions as μ varies from ∞ to 0.

