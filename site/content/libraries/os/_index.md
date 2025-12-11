+++
title = "OS"
description = "Optimization Services - Web services framework with column generation"
template = "library.html"
sort_by = "title"

[extra]
layer = 4
+++

# OS

**Optimization Services** - A framework for optimization as a web service, with implementations of advanced decomposition algorithms. Developed at Northwestern University.

**Layer 4** | 59 files | 1 with algorithm annotations

## Key Features

### Web Services Framework
- **OSiL**: Optimization Services instance Language (XML problem representation)
- **OSrL**: Optimization Services result Language
- **OSSolverService**: SOAP-based remote solver invocation

### Column Generation Framework
The `columnGen` application provides a virtual base class for implementing Dantzig-Wolfe decomposition:

- **Master problem**: LP relaxation over convex combinations
- **Pricing subproblem**: Generate columns with negative reduced cost
- **Branch-and-price**: Column generation within branch-and-bound

## Annotated Components

| Component | Description |
|-----------|-------------|
| `OSDecompSolver.h` | Virtual base for Dantzig-Wolfe decomposition |

## Dantzig-Wolfe Decomposition

For structured problems with block-diagonal constraints:

$$\min c'x \quad \text{s.t.} \quad Ax = b, \quad x \in X_1 \cup X_2 \cup \ldots \cup X_K$$

The decomposition reformulates as:

$$\min c'\theta \quad \text{s.t.} \quad A\theta = b, \quad \theta \in \text{conv}(X_k)$$

**Pricing subproblem** for block $k$:
$$\min (c - \pi A)x \quad \text{s.t.} \quad x \in X_k$$

If reduced cost < 0, add column to master.

## Key Methods in OSDecompSolver

| Method | Description |
|--------|-------------|
| `getInitialRestrictedMaster()` | Create initial master LP |
| `getColumns()` | Solve pricing, return new columns |
| `getCutsTheta()` | Generate cuts in theta space |
| `getCutsMultiCommod()` | Multi-commodity flow cuts |
| `getBranchingCut()` | Variable branching constraints |

## Applications

- Vehicle routing problems (VRP)
- Bin packing and cutting stock
- Crew scheduling
- Network design

## References

- Dantzig & Wolfe (1960). "Decomposition Principle for Linear Programs"
- Barnhart et al. (1998). "Branch-and-Price: Column Generation for Solving Huge Integer Programs"

