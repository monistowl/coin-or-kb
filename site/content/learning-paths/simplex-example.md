+++
title = "Interactive Simplex Example"
description = "Step through a complete simplex solve with an interactive tableau"
template = "simplex-interactive.html"
weight = 10
+++

This interactive example walks you through a complete primal simplex solve. Click through each iteration to see exactly what happens at every step.

## The Problem

A small production planning problem:

$$\max \quad 3x_1 + 2x_2$$

Subject to:
$$x_1 + x_2 \leq 4 \quad \text{(resource A)}$$
$$2x_1 + x_2 \leq 6 \quad \text{(resource B)}$$
$$x_1, x_2 \geq 0$$

Adding slack variables $s_1, s_2$ to convert to standard form:

$$\max \quad 3x_1 + 2x_2 + 0s_1 + 0s_2$$
$$x_1 + x_2 + s_1 = 4$$
$$2x_1 + x_2 + s_2 = 6$$

The initial basic feasible solution uses slacks: $x_1 = x_2 = 0$, $s_1 = 4$, $s_2 = 6$.
