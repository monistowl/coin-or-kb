+++
title = "Cutting Stock Example"
description = "1D bin packing via Dantzig-Wolfe decomposition and column generation"
template = "class.html"

[extra]
library = "bcp"
header = "Applications/Csp/include/"
+++

# Cutting Stock: Column Generation in Action

The Cutting Stock Problem (CSP) example demonstrates **column generation**, one of BCP's most powerful features. Instead of enumerating all possible cutting patterns upfront, we generate them dynamically via pricing subproblems.

---

## Problem Definition

**Given:**
- Stock rolls of length $L$
- Demanded piece widths $w_1, \ldots, w_m$ with quantities $d_1, \ldots, d_m$

**Find:** Cutting patterns that satisfy all demands using minimum stock rolls.

### Example

Stock length $L = 100$. Demands:
- 30 pieces of width 45
- 20 pieces of width 36
- 15 pieces of width 31

A **pattern** specifies how many of each width to cut from one stock roll. For example:
- Pattern A: 2 pieces of width 45 (uses 90, wastes 10)
- Pattern B: 1 piece of width 45 + 1 piece of width 36 (uses 81, wastes 19)
- Pattern C: 3 pieces of width 31 (uses 93, wastes 7)

<div class="key-insight">

**The challenge:** With $m$ piece types and maximum $\lfloor L/w_i \rfloor$ of each, there can be exponentially many valid patterns. We can't enumerate them all, so we generate only the useful ones.

</div>

---

## Dantzig-Wolfe Decomposition

### Master Problem

Let $x_j$ be the number of times we use pattern $j$. The master LP:

$$\min \sum_j x_j$$

Subject to:
$$\sum_j a_{ij} x_j \geq d_i \quad \forall i \quad \text{(meet demands)}$$
$$x_j \geq 0$$

Where $a_{ij}$ is how many pieces of width $i$ pattern $j$ produces.

### Pricing Subproblem

Given dual values $\pi_i$ from the master LP, find a new pattern with negative reduced cost:

$$\text{Reduced cost} = 1 - \sum_i \pi_i a_i < 0$$

This is equivalent to finding a pattern maximizing $\sum_i \pi_i a_i > 1$.

**This is a knapsack problem:**
$$\max \sum_i \pi_i a_i \quad \text{s.t.} \quad \sum_i w_i a_i \leq L, \quad a_i \in \{0, 1, \ldots, \lfloor L/w_i \rfloor\}$$

---

## Horowitz-Sahni Knapsack Solver

The CSP example includes an exact branch-and-bound knapsack solver:

### Algorithm Steps

1. **Sort by efficiency:** Order items by profit/weight ratio (Dantzig ordering)
2. **Compute LP bound:** Greedy fractional fill gives upper bound
3. **Forward step:** Greedily add items while capacity permits
4. **Backtrack:** When LP bound proves no improvement possible, backtrack

```cpp
// Dantzig ordering: sort by pi[i]/w[i] ratio
struct triplet {
    double c;  // profit (dual value)
    double w;  // weight
    int i;     // original index
};

bool ratioComp(const triplet& t0, const triplet& t1) {
    return t0.c/t0.w > t1.c/t1.w;
}
```

### Why Branch-and-Bound?

For pricing subproblems:
- Dual values change each iteration
- Need fast re-optimization
- Integer coefficients allow efficient bounding
- Typically small (dozens of item types)

**Reference:** Martello & Toth, "Knapsack Problems" (1990), pp. 30-31

---

## Column Generation Loop

```
1. Start with initial patterns (e.g., one width per pattern)
2. Solve master LP to get dual values π
3. Solve knapsack pricing: max Σ πᵢaᵢ s.t. Σ wᵢaᵢ ≤ L
4. If optimal value > 1: add pattern as new column, goto 2
5. If optimal value ≤ 1: LP optimal, check integrality
6. If fractional: branch, goto 2 for each child
7. If integer: feasible solution found
```

### Pattern Diversity

The implementation includes **perturbation** to generate diverse patterns:
- Slightly modify dual values
- Get alternative near-optimal patterns
- Improves branching behavior

---

## Implementation Structure

### Data Classes

| Class | Purpose |
|-------|---------|
| `CSPROBLEM` | Problem data: stock length, widths, demands |
| `PATTERN` | Cutting pattern: which widths, how many each |
| `CSP_packedVector` | Sparse representation of patterns |
| `Knapsack` | Horowitz-Sahni solver for pricing |

### BCP Integration

| Class | BCP Base | Role |
|-------|----------|------|
| `CSP_tm` | `BCP_tm_user` | Tree manager: problem setup |
| `CSP_lp` | `BCP_lp_user` | LP worker: column generation |
| `CSP_var` | `BCP_var_algo` | Pattern as algorithmic variable |

### Variable Generation

```cpp
// In CSP_lp: generate improving patterns
void generate_vars_in_lp(const BCP_lp_result& lpres,
                         const BCP_vec<BCP_var*>& vars,
                         const BCP_vec<BCP_cut*>& cuts,
                         const bool before_fathom,
                         BCP_vec<BCP_var*>& new_vars,
                         BCP_vec<BCP_col*>& new_cols) {
    // Get dual values from LP
    const double* pi = lpres.pi();

    // Solve knapsack pricing subproblem
    knapsack.setCosts(pi);
    knapsack.optimize();

    // If reduced cost < 0, add new pattern
    if (knapsack.getBestVal() > 1.0 + eps) {
        // Create new pattern from knapsack solution
        new_vars.push_back(new CSP_var(knapsack.getBestSol()));
    }
}
```

---

## Source Files

| File | Description |
|------|-------------|
| [CSP.hpp](/browser/?library=Bcp&path=Applications/Csp/include/CSP.hpp) | Problem and pattern data structures |
| [KS.hpp](/browser/?library=Bcp&path=Applications/Csp/include/KS.hpp) | Horowitz-Sahni knapsack solver |
| [CSP_colgen.hpp](/browser/?library=Bcp&path=Applications/Csp/include/CSP_colgen.hpp) | Column generation with perturbation |
| [CSP_lp.hpp](/browser/?library=Bcp&path=Applications/Csp/include/CSP_lp.hpp) | LP process with pricing |
| [CSP_var.hpp](/browser/?library=Bcp&path=Applications/Csp/include/CSP_var.hpp) | Pattern variable definition |

---

## Advanced Features

### Knife Constraints
Physical cutting machines have limited "knives" (blades). The implementation supports constraints on total distinct widths per pattern.

### MIR Cuts
The example can generate **Mixed Integer Rounding** cuts to strengthen the LP relaxation and reduce branching.

### Exclusion Constraints
Force certain patterns to be used together or apart based on operational requirements.

---

## References

- Gilmore, P.C., Gomory, R.E. (1961). "A Linear Programming Approach to the Cutting Stock Problem", Operations Research
- Vanderbeck, F. (2000). "On Dantzig-Wolfe Decomposition in Integer Programming and ways to Perform Branching in a Branch-and-Price Algorithm", Operations Research

