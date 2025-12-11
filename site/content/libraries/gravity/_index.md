+++
title = "Gravity"
description = "Mathematical modeling library for nonlinear optimization"
template = "library.html"
sort_by = "title"

[extra]
layer = 4
+++

# Gravity

A modern C++ mathematical modeling library for nonlinear optimization, with particular strengths in power systems and network optimization. Features automatic differentiation and convexity analysis.

**Layer 4** | 103 files | 7 with algorithm annotations

## Key Features

### Expression System
- **Symbolic automatic differentiation** on expression DAGs
- **Convexity analysis** via Disciplined Convex Programming (DCP) rules
- **Parallel evaluation** of constraints and derivatives
- Support for polynomial, monomial, and signomial terms

### Network Optimization
- **Graph data structures** for power system networks
- **Cycle basis computation** via Horton's algorithm
- **Chordal extension** for sparse SDP relaxations
- **Tree decomposition** for exploiting problem structure

### Solver Integration
- **Ipopt** for nonlinear programming
- **MOSEK** for semidefinite programming
- **Gurobi/CPLEX** for LP/QP/MIP
- **Bonmin** for MINLP

## Annotated Components

| Component | Description |
|-----------|-------------|
| `gravity/func.h` | Expression system with symbolic AD and DCP rules |
| `gravity/model.h` | Parallel constraint/Jacobian/Hessian evaluation |
| `gravity/solver.h` | Multi-solver adapter pattern |
| `gravity/Net.h` | Graph algorithms (Dijkstra, Kruskal, Horton) |

## Key Algorithms

### Graph Algorithms in Net.h
- **Dijkstra's shortest path**: O((V+E) log V) for cycle basis
- **Kruskal's MST**: O(E log E) for spanning trees
- **Horton's minimum cycle basis**: O(VE²/log V) for Kirchhoff constraints
- **Chordal extension**: Perfect elimination ordering for SDP

### DCP Convexity Rules
```
linear × anything = linear
convex + convex = convex
x² = convex
exp(linear) = convex
log(linear) = concave
positive × convex = convex
negative × convex = concave
```

## Applications

- **Optimal Power Flow (OPF)** with SDP relaxations
- **Unit commitment** problems
- **Network design** optimization
- **Energy systems** modeling

## References

- Hijazi et al. (2017). "Gravity: A Mathematical Modeling Language for Optimization"
- Horton (1987). "A polynomial-time algorithm for minimum cycle basis"

