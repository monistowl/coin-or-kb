+++
title = "Clp"
description = "Layer 1 - COIN-OR Linear Programming Solver"
template = "library.html"
sort_by = "title"

[extra]
layer = 1
+++

# Clp — COIN-OR Linear Programming

Clp (COIN-OR Linear Programming) is a high-quality open-source LP solver that rivals commercial solvers. It's the LP engine inside Cbc, meaning every MIP solved by Cbc uses Clp for its LP relaxations.

**Layer 1** | 86 files | 13 with algorithm annotations

---

## Why Clp Matters

Every major optimization solver needs a reliable LP solver at its core:

- **MIP solvers** (like Cbc) solve thousands of LP relaxations during branch-and-bound
- **NLP solvers** (like Ipopt) use LP for subproblems and initialization
- **MINLP solvers** (like Bonmin) need LP for outer approximation

Clp provides this foundation with both **simplex** and **interior point** methods.

---

## Algorithms Implemented

### Dual Simplex Method

The workhorse for re-optimization. Clp's dual simplex maintains dual feasibility while working toward primal feasibility — ideal for:
- **Branch-and-bound**: After branching, only bounds change
- **Adding cuts**: New constraints make current solution infeasible
- **Warm starting**: Reuse basis from similar problems

Key features:
- Steepest edge pricing for pivot selection
- Cost perturbation for degeneracy handling (from OSL heritage)
- Three-nested-loop structure for numerical stability

### Primal Simplex Method

Classic simplex maintaining primal feasibility. Use when:
- Starting from known feasible point
- Removing constraints from solution
- Educational/debugging purposes

### Interior Point (Barrier) Method

Alternative to simplex for very large or dense problems:
- Mehrotra predictor-corrector algorithm
- Multiple Cholesky backends (dense, MUMPS, etc.)
- Good for first solve, but can't warm-start like simplex

---

## Key Classes

| Class | Purpose |
|-------|---------|
| {{ link(path="/browser/?library=Clp", text="ClpSimplex") }} | Main simplex solver class |
| {{ link(path="/browser/?library=Clp", text="ClpSimplexDual") }} | Dual simplex implementation |
| {{ link(path="/browser/?library=Clp", text="ClpSimplexPrimal") }} | Primal simplex implementation |
| {{ link(path="/browser/?library=Clp", text="ClpInterior") }} | Interior point (barrier) solver |
| {{ link(path="/browser/?library=Clp", text="ClpModel") }} | LP model storage |
| {{ link(path="/browser/?library=Clp", text="ClpFactorization") }} | Basis factorization (wraps CoinFactorization) |

---

## Architecture

Clp uses a "mix-in" design where `ClpSimplexDual` and `ClpSimplexPrimal` inherit from `ClpSimplex` but add no data — they're cast types that provide algorithm-specific methods.

```
ClpModel          <- Problem data (A, b, c, bounds)
    |
ClpSimplex        <- Core simplex infrastructure
    |
+---+---+
|       |
Dual  Primal     <- Algorithm-specific pivot rules
```

The solver maintains:
- **Factorization**: $B = LU$ decomposition of basis matrix
- **Pricing**: Reduced costs $\bar{c} = c - c_B^T B^{-1} A$
- **Feasibility**: Primal values and dual multipliers

---

## Usage Example

```cpp
#include "ClpSimplex.hpp"

// Create model and read problem
ClpSimplex model;
model.readMps("problem.mps");

// Solve using dual simplex (default for most problems)
model.dual();

// Or use primal simplex
// model.primal();

// Or interior point
// model.barrier();

// Get solution
const double* solution = model.primalColumnSolution();
double objectiveValue = model.objectiveValue();
```

---

## When to Use Clp

| Scenario | Recommendation |
|----------|----------------|
| Standalone LP | Dual simplex (default) |
| Inside branch-and-bound | Dual simplex with warm start |
| Very large dense LP | Interior point |
| First solve, no warm start | Either; interior point may be faster |
| Re-optimization after cuts | Dual simplex |

---

## Performance Tips

1. **Presolve**: Always use `model.initialSolve()` which includes presolve
2. **Scaling**: Enable scaling for numerically difficult problems
3. **Factorization frequency**: Tune `factorizationFrequency` for stability vs. speed
4. **Crash**: Use `crash` option to find good initial basis quickly

---

## Related Resources

- [LP Fundamentals Learning Path](@/learning-paths/lp-fundamentals.md) — Learn simplex from scratch
- [Dual Simplex Algorithm](@/algorithms/dual-simplex-method.md) — Detailed algorithm page
- [Simplex Convergence Derivation](/derivations/simplex-convergence/) — Why simplex terminates
- [LP Duality Derivation](/derivations/lp-duality/) — Strong duality and complementary slackness
