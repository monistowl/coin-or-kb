+++
title = "Interactive Presolve Example"
description = "Step through presolve transformations on a small LP"
template = "presolve-interactive.html"
weight = 50
+++

This interactive example demonstrates **presolve transformations** applied to a small LP. Step through each reduction to see how the problem shrinks before solving.

## The Problem

A small production planning LP:

$$\max \quad 3x_1 + 2x_2 + x_3 + 4x_4 + 2x_5 + 0x_6$$

Subject to:
$$2x_1 + x_2 + 3x_4 + x_5 \leq 10 \quad \text{(R1: capacity)}$$
$$x_1 + x_2 = 4 \quad \text{(R2: demand)}$$
$$x_3 + x_4 \leq 6 \quad \text{(R3: material)}$$
$$x_6 \leq 5 \quad \text{(R4: singleton)}$$
$$2x_4 + x_5 = 6 \quad \text{(R5: process balance)}$$
$$x_1, x_2, x_3, x_4, x_5, x_6 \geq 0$$

### Why This Problem?

This LP is small enough to visualize but contains several structures that presolve exploits:

1. **Singleton column** ($x_6$) — appears in only one constraint with zero objective
2. **Doubleton equalities** (R2, R5) — allow variable substitution
3. **Bound propagation opportunities** — constraints imply tighter bounds
4. **Redundant elements** — get removed after substitutions

## What Presolve Will Do

Watch as presolve applies these transformations:

| Step | Transformation | Effect |
|------|---------------|--------|
| 1 | Singleton column | Remove $x_6$ (set to 0, remove R4) |
| 2 | Doubleton R5 | Substitute $x_5 = 6 - 2x_4$ |
| 3 | Bound tightening | Propagate implications |
| 4 | Doubleton R2 | Substitute $x_2 = 4 - x_1$ |
| 5 | Simplification | Remove redundant constraints |

The problem shrinks from 6 variables / 5 constraints to just 3 variables / 2 constraints!

## Understanding the Matrix View

The visualization shows:

- **Before**: The constraint matrix before applying the current transformation
- **After**: The matrix after applying the transformation
- **Bounds**: Variable bounds $[l_j, u_j]$
- **Objective**: Coefficients $c_j$
- **Highlighted cells**: Elements affected by the current transformation

### The Status Bar

Track the reduction progress:
- **Variables**: How many columns remain
- **Constraints**: How many rows remain
- **Nonzeros**: Total matrix entries (affects solve time)
- **Reduction**: Percentage of original problem eliminated

## Connection to COIN-OR Code

Each transformation in this example corresponds to a `CoinPresolveAction` subclass:

| Transformation | Action Class | File |
|----------------|--------------|------|
| Singleton column | `slack_singleton_action` | CoinPresolveZeros.cpp |
| Doubleton row | [doubleton_action](@/libraries/coinutils/doubleton_action.md) | CoinPresolveDoubleton.cpp |
| Bound tightening | `do_tighten_action` | CoinPresolveTighten.cpp |
| Fixed variable | `make_fixed_action` | CoinPresolveFixed.cpp |

<div class="code-connection">

**Code Spotlight**: The presolve loop in `CoinPresolve::presolvedModel()`:

```
while (changed) {
    changed = false;

    // Simple reductions first
    changed |= removeEmptyRows();
    changed |= removeFixedCols();
    changed |= removeSingletonRows();
    changed |= removeSingletonCols();

    // Substitutions
    changed |= removeDoubletonRows();
    changed |= removeTripletonRows();

    // Bound propagation
    changed |= doBoundTightening();

    // Advanced
    changed |= removeDuplicateRows();
    changed |= removeDuplicateCols();
}
```

Each reduction that succeeds creates an action object for later postsolve.

</div>

## The Postsolve Guarantee

Every transformation is **reversible**. After solving the reduced problem, postsolve walks the action list in reverse order:

1. Each action knows what was removed and how to restore it
2. Primal values are recovered: $x_5 = 6 - 2x_4$
3. Dual values are computed for eliminated constraints
4. The full solution to the original problem emerges

This is why presolve is "free" — the cost of transformation is repaid many times over by the smaller solve.

## Key Insights

As you step through:

1. **Order matters** — Removing the singleton first exposes new structure
2. **Cascading effects** — Each reduction may enable more reductions
3. **Fill-in trade-offs** — Substitution adds coefficients elsewhere
4. **Postsolve is recorded** — Every step notes what must be undone

## Try It Below

Use **Next Step** to walk through each presolve transformation:

- Watch the **matrix shrink** as variables and constraints disappear
- See **highlighted cells** showing what changes at each step
- Track the **reduction percentage** in the status bar
- Read the **explanation** to understand the mathematics
- Note the **postsolve** description for reversing each step

