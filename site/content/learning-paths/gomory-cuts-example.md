+++
title = "Interactive Gomory Cutting Planes"
description = "Step through Gomory cut generation for integer programming"
template = "gomory-cuts-interactive.html"
weight = 30
+++

This interactive example demonstrates **Gomory fractional cuts**, a foundational cutting plane technique for Integer Programming. Step through as we iteratively add cuts to tighten the LP relaxation.

## The Problem

A small integer program:

$$\max \quad 4x_1 + 5x_2$$

Subject to:
$$2x_1 + 3x_2 \leq 12 \quad \text{(constraint 1)}$$
$$2x_1 + x_2 \leq 6 \quad \text{(constraint 2)}$$
$$x_1, x_2 \geq 0 \text{ and integer}$$

## How Gomory Cuts Work

1. **Solve LP relaxation** — get optimal tableau
2. **Find fractional basic variable** — row with fractional RHS
3. **Generate cut** from tableau row:
   - Take fractional parts of all coefficients
   - Create new constraint: Σ frac(aᵢⱼ)xⱼ ≥ frac(bᵢ)
4. **Add cut and re-solve** — repeat until integer solution

