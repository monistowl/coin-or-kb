+++
title = "Interactive Branch and Bound Example"
description = "Step through a complete branch-and-bound solve for integer programming"
template = "branch-bound-interactive.html"
weight = 20
+++

This interactive example walks you through Branch and Bound for solving an Integer Linear Program (ILP). Click through each step to see node selection, branching decisions, and pruning.

## The Problem

A small investment problem with integer constraints:

$$\max \quad 5x_1 + 4x_2$$

Subject to:
$$x_1 + x_2 \leq 5 \quad \text{(budget)}$$
$$10x_1 + 6x_2 \leq 45 \quad \text{(resource)}$$
$$x_1, x_2 \geq 0 \text{ and integer}$$

The LP relaxation (ignoring integrality) yields fractional solutions. Branch and Bound systematically explores integer solutions by:

1. **Solve LP relaxation** at each node
2. **Branch** on fractional variables (create two subproblems)
3. **Bound** using LP objective to prune unpromising branches
4. **Prune** when LP bound ≤ best known integer solution

