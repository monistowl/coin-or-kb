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

### Why We Need Cutting Planes

The LP relaxation (ignoring integrality) gives a fractional optimum. Instead of branching immediately, we can add **valid inequalities** that:
- Cut off the fractional LP solution
- Don't eliminate any integer feasible points
- Tighten the relaxation toward the integer hull

This is the key idea behind the **cutting plane method** introduced by Ralph Gomory in the 1950s.

## How Gomory Cuts Work

From an optimal LP tableau with a fractional basic variable:

1. **Select source row** — find a row with fractional RHS $b_i$
2. **Extract fractional parts** — for each coefficient $a_{ij}$, compute $f(a_{ij}) = a_{ij} - \lfloor a_{ij} \rfloor$
3. **Form the cut** — $\sum_j f(a_{ij}) x_j \geq f(b_i)$
4. **Add to tableau** — introduce slack variable, re-solve with dual simplex
5. **Repeat** until the LP solution is integer

### The Mathematics

Given a tableau row for basic variable $x_i$:
$$x_i + \sum_{j \in N} a_{ij} x_j = b_i$$

where $b_i$ is fractional. The Gomory fractional cut is:
$$\sum_{j \in N} f(a_{ij}) x_j \geq f(b_i)$$

where $f(\cdot)$ denotes the fractional part. This cut is valid because:
- If all $x_j$ are integer and satisfy the original row, the cut is satisfied
- But if $x_i$ is fractional at the current LP optimum, the cut is violated

## What to Watch For

As you step through the tableau:

1. **Source row selection**: We pick rows where the basic variable has a fractional value. In practice, heuristics choose rows likely to give strong cuts. See [CglGomory](@/libraries/cgl/CglGomory.md) for the `away_` parameter that skips near-integer values.

2. **Fractional parts computation**: The key insight is that integer variables must satisfy the fractional part inequality. Watch how we compute $f(a_{ij})$ for each coefficient.

3. **Cut addition via slack**: Each cut adds a new row and slack variable. The current solution violates the cut (slack is negative), making dual simplex the natural re-optimization method.

4. **Dual simplex restoration**: After adding a violated cut, we use [dual simplex](@/algorithms/dual-simplex-method.md) to restore feasibility while maintaining optimality of the reduced costs.

5. **Convergence**: Gomory cuts are *finite* — they theoretically solve pure integer programs. In practice, numerical issues limit this, so modern solvers combine cuts with branching.

## Connection to COIN-OR Code

In Cgl (COIN-OR Cut Generator Library), Gomory cuts are implemented in [CglGomory](@/libraries/cgl/CglGomory.md):

| Concept | This Example | Cgl Implementation |
|---------|--------------|-------------------|
| **Source row selection** | First fractional | Parameterized by `away_` threshold |
| **Cut generation** | Pure fractional | Mixed-integer strengthening |
| **Numerical stability** | Exact fractions | Condition number checks |
| **Cut limits** | Unlimited | `limit_` caps nonzeros per cut |

<div class="code-connection">

**Code Spotlight**: The `CglGomory::generateCuts()` method:

```
for each basic integer variable with fractional value:
    if (frac < away_ || frac > 1.0 - away_)
        skip  // Too close to integer, numerically risky

    // Get tableau row from basis factorization
    row = getBasisRow(basicIndex)

    // Compute fractional parts
    for each nonzero coefficient:
        f_coef = fractionalPart(coefficient)

    // Create cut: sum f_j x_j >= f_0
    cut = createGomoryCut(row, f_0)

    // Check cut quality (sparsity, violation)
    if (cut.nonzeros < limit_ && cut.violation > minViolation)
        addCut(cut)
```

The actual implementation handles mixed-integer strengthening, basis conditioning, and cut pool management.

</div>

## Key Numerical Considerations

Gomory cuts are notoriously sensitive to numerical precision:

1. **The `away_` parameter**: Don't generate cuts from rows with $f_0$ very close to 0 or 1 — these lead to weak or numerically unstable cuts. Default is typically 0.05.

2. **Basis conditioning**: Ill-conditioned bases produce unreliable tableau rows. [CglGomory](@/libraries/cgl/CglGomory.md) checks `conditionNumberMultiplier_` before trusting the factorization.

3. **Cut density**: Dense cuts (many nonzeros) are expensive to store and apply. The `limit_` parameter caps cut size.

## Historical Note

Ralph Gomory developed these cuts at IBM in 1958, proving that pure integer programs could be solved in a finite number of steps. However, early implementations suffered from numerical instability. The "revival of GMI cuts" in the 2000s (Cornuéjols et al.) showed that with careful implementation and integration with branch-and-bound, Gomory cuts significantly improve solver performance.

## Try It Below

Use **Next Step** to walk through the cutting plane algorithm. Watch how:
- The **LP objective** decreases as we add cuts (tighter relaxation)
- **Fractional values** move toward integers
- **Cut lines** (dashed) slice off the fractional optimum
- The process converges to an **integer optimal solution**

