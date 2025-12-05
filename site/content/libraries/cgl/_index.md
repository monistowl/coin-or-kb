+++
title = "Cgl"
description = "Layer 1 - Cut Generator Library for MIP"
template = "library.html"
sort_by = "title"

[extra]
layer = 1
+++

# Cgl — Cut Generator Library

Cgl (Cut Generator Library) provides cutting plane generators for mixed-integer programming. These cuts strengthen the LP relaxation, making branch-and-bound more effective by pruning more of the search tree.

**Layer 1** | 37 files | 6 with algorithm annotations

---

## Why Cgl Matters

The LP relaxation of a MIP often has fractional solutions that violate integrality. **Cutting planes** are valid inequalities that cut off these fractional points without removing any integer-feasible solutions.

Good cuts = tighter LP bounds = faster MIP solving

Cgl provides the cuts used by:
- **Cbc** (COIN-OR branch-and-cut)
- **SYMPHONY**
- **BCP** (Branch, Cut, and Price)
- Many other MIP frameworks

---

## Types of Cuts

Cgl implements many cut families, each exploiting different problem structure:

### Gomory Cuts

Derived from the simplex tableau. If $x_i$ is basic with fractional value, the tableau row gives:
$$x_i + \sum_{j \in N} \bar{a}_{ij} x_j = \bar{b}_i$$

The **Gomory fractional cut** is:
$$\sum_{j \in N} f_{ij} x_j \geq f_i$$

where $f_i = \bar{b}_i - \lfloor \bar{b}_i \rfloor$ and $f_{ij}$ are fractional parts of $\bar{a}_{ij}$.

**Class**: `CglGomory`

### Mixed-Integer Rounding (MIR) Cuts

Generalize Gomory cuts by considering the structure of mixed-integer constraints. Given:
$$\sum_j a_j x_j \leq b$$

with some $x_j$ integer, MIR derives tighter cuts by rounding.

**Class**: `CglMixedIntegerRounding`, `CglMixedIntegerRounding2`

### Clique Cuts

Exploit binary variable conflicts. If $x_i + x_j \leq 1$ (at most one can be 1), they form a **clique**. Larger cliques give stronger cuts:
$$\sum_{i \in \text{clique}} x_i \leq 1$$

**Class**: `CglClique`

### Knapsack Covers

For knapsack constraints $\sum_j a_j x_j \leq b$ with binary $x_j$, find **covers** (subsets that exceed $b$) and generate **cover cuts**.

**Class**: `CglKnapsackCover`

### Flow Covers

Cuts from fixed-charge network structures:
$$y_j \leq x_j \cdot u_j \quad \text{(flow} \leq \text{capacity if open)}$$

**Class**: `CglFlowCover`

### Lift-and-Project

Generate cuts by solving auxiliary LPs for each disjunction. Most general but expensive.

**Class**: `CglLiftAndProject`

### Other Cut Types

| Class | Cut Type |
|-------|----------|
| `CglProbing` | Implications from variable fixing |
| `CglTwomir` | Two-constraint MIR |
| `CglRedSplit` | Reduce-and-split cuts |
| `CglLandP` | Lift-and-project |
| `CglOddHole` | Odd hole inequalities |
| `CglZeroHalf` | {0, ½} Chvátal-Gomory |

---

## Key Classes

| Class | Purpose |
|-------|---------|
| [CglCutGenerator](/browser/?library=Cgl) | Base class for all cut generators |
| [CglGomory](/browser/?library=Cgl) | Gomory fractional cuts |
| [CglMixedIntegerRounding](/browser/?library=Cgl) | MIR cuts |
| [CglClique](/browser/?library=Cgl) | Clique cuts from conflict graph |
| [CglKnapsackCover](/browser/?library=Cgl) | Knapsack cover cuts |
| [CglProbing](/browser/?library=Cgl) | Probing-based cuts |

---

## Architecture

All cut generators inherit from `CglCutGenerator`:

```cpp
class CglCutGenerator {
public:
    // Generate cuts for the given solver interface
    virtual void generateCuts(const OsiSolverInterface& si,
                              OsiCuts& cuts,
                              const CglTreeInfo& info = CglTreeInfo()) = 0;
};
```

The `OsiCuts` object collects the generated cuts, which can then be added to the LP relaxation.

---

## Usage Example

```cpp
#include "CglGomory.hpp"
#include "CglMixedIntegerRounding.hpp"
#include "OsiClpSolverInterface.hpp"

// Create LP solver
OsiClpSolverInterface solver;
solver.readMps("problem.mps");
solver.initialSolve();

// Create cut generators
CglGomory gomory;
CglMixedIntegerRounding mir;

// Generate cuts
OsiCuts cuts;
gomory.generateCuts(solver, cuts);
mir.generateCuts(solver, cuts);

// Add cuts to the problem
for (int i = 0; i < cuts.sizeRowCuts(); i++) {
    solver.addCut(cuts.rowCut(i));
}

// Re-solve LP
solver.resolve();
```

---

## Cut Generation Strategy

### Root Node vs. Tree

- **Root node**: Generate many cuts aggressively (one-time investment)
- **In tree**: Generate fewer cuts (amortized over many nodes)

Most cuts are only generated at the root because:
1. Cuts added early benefit all descendants
2. Tree cuts have diminishing returns
3. Cut generation is expensive

### Cut Selection

Not all generated cuts are useful. Selection criteria:
- **Violation**: How much does the cut remove?
- **Density**: Sparse cuts are cheaper to store
- **Orthogonality**: Diverse cuts improve together
- **Parallelism**: Avoid near-duplicate cuts

---

## Performance Tips

1. **Use multiple generators**: Different cuts find different violations
2. **Limit rounds**: Diminishing returns after 5-10 rounds
3. **Aging**: Remove cuts that haven't been tight recently
4. **Global vs. local**: Some cuts valid everywhere, others only in subtree

---

## When to Use Which Cuts

| Problem Structure | Recommended Cuts |
|-------------------|------------------|
| General MIP | Gomory, MIR, Probing |
| Set covering/packing | Clique, Knapsack Cover |
| Network design | Flow Cover |
| Tight LP relaxation | Gomory, Twomir |
| Hard instances | Lift-and-Project (expensive) |

---

## Related Resources

- [MIP Journey Learning Path](/learning-paths/mip-journey/) — Branch-and-cut from scratch
- [Cutting Planes Algorithm](/algorithms/cutting-planes/) — How cuts work
- [Gomory Cuts](/algorithms/gomory-cuts/) — Tableau-derived cuts
- [Branch and Bound Correctness](/derivations/branch-and-bound-correctness/) — Why pruning works
