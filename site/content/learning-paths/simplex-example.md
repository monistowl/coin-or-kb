+++
title = "Interactive Simplex Example"
description = "Step through a complete simplex solve with an interactive tableau"
template = "simplex-interactive.html"
weight = 10
+++

This interactive example walks you through a complete **primal simplex solve**. Click through each iteration to see exactly what happens at every step — the tableau updates, the pivot selection, and the geometric movement along the feasible region.

## The Problem

A small production planning problem:

$$\max \quad 3x_1 + 2x_2$$

Subject to:
$$x_1 + x_2 \leq 4 \quad \text{(resource A)}$$
$$2x_1 + x_2 \leq 6 \quad \text{(resource B)}$$
$$x_1, x_2 \geq 0$$

### Converting to Standard Form

Adding slack variables $s_1, s_2$ to convert inequalities to equalities:

$$\max \quad 3x_1 + 2x_2 + 0s_1 + 0s_2$$
$$x_1 + x_2 + s_1 = 4$$
$$2x_1 + x_2 + s_2 = 6$$

The initial basic feasible solution uses slacks as the basis: $x_1 = x_2 = 0$, $s_1 = 4$, $s_2 = 6$.

This corresponds to the **origin** in the geometric view — we're at the corner where both decision variables are zero.

## What to Watch For

As you step through the iterations, notice:

1. **Entering variable selection**: The most negative reduced cost in the objective row indicates the best direction to improve. In COIN-OR's Clp, this is called "pricing" and happens in [`ClpSimplexPrimal::primalColumn()`](https://github.com/monistowl/coin-or-kb/blob/master/layer-1/Clp/src/ClpSimplexPrimal.hpp).

2. **Ratio test**: For each candidate, we compute RHS ÷ column coefficient. The minimum positive ratio determines which variable leaves. This prevents moving outside the feasible region. See [`ClpSimplexPrimal::primalRow()`](https://github.com/monistowl/coin-or-kb/blob/master/layer-1/Clp/src/ClpSimplexPrimal.hpp).

3. **Pivot operation**: The tableau update uses elementary row operations to make the pivot element = 1 and all other elements in that column = 0. Clp doesn't store the full tableau — it maintains the basis matrix factorization and recomputes columns on demand.

4. **Geometric interpretation**: Each pivot moves us along an edge of the polytope to an adjacent vertex. The objective improves at each step until we reach optimality.

## Connection to COIN-OR Code

The simplex implementation in Clp uses several optimizations not shown in this simple example:

| Concept | Simple Tableau | Clp Implementation |
|---------|----------------|-------------------|
| **Tableau storage** | Dense matrix | Sparse column-wise ([CoinPackedMatrix](@/libraries/coinutils/CoinPackedMatrix.md)) |
| **Basis representation** | Explicit inverse | LU factorization with updates ([CoinFactorization](@/libraries/coinutils/CoinFactorization.md)) |
| **Pivot selection** | Most negative | Steepest edge / Devex ([ClpPrimalColumnSteepest](@/libraries/clp/ClpPrimalColumnSteepest.md)) |
| **Degeneracy handling** | None | Perturbation and anti-cycling |

<div class="code-connection">

**Code Spotlight**: The main primal simplex loop is in `ClpSimplexPrimal::whileIterating()`. Each iteration:
1. Calls `primalColumn()` to select entering variable
2. Calls `primalRow()` to select leaving variable via ratio test
3. Calls `factorization_->updateColumn()` for the pivot operation
4. Updates reduced costs and solution values

</div>

## Try It Below

Use the **Next Step** button to advance through each simplex iteration. The geometric view on the right shows how the solution point moves along the edges of the feasible region toward the optimum.
