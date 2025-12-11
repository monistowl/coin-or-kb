+++
title = "SHOT"
description = "Supporting Hyperplane Optimization Toolkit for convex MINLP"
template = "library.html"
sort_by = "title"

[extra]
layer = 4
+++

# SHOT

The **Supporting Hyperplane Optimization Toolkit** - a solver for convex mixed-integer nonlinear programming (MINLP) problems. Developed at Åbo Akademi University.

**Layer 4** | 573 files | 26 with algorithm annotations

## Core Algorithms

### Extended Supporting Hyperplane (ESH)
The signature algorithm of SHOT. Given a nonlinear constraint $g(x) \leq 0$:

1. **Find interior point** $x°$ where $g(x°) < 0$
2. **Rootsearch**: Find boundary point $x^*$ on line between $x°$ and infeasible $\hat{x}$
3. **Generate cut**: Supporting hyperplane $\nabla g(x^*) \cdot (x - x^*) \leq 0$

ESH cuts are **tighter** than traditional Extended Cutting Plane (ECP) cuts because they're generated at the boundary rather than at infeasible points.

### Outer Approximation Framework
- **MIP relaxation**: Replace nonlinear constraints with linear approximation
- **Iterative refinement**: Add hyperplanes as solutions violate nonlinear constraints
- **Single-tree** and **multi-tree** strategies

### Cut Generation
- **ECP cuts**: Gradient linearization at infeasible points
- **ESH cuts**: Supporting hyperplanes via rootsearch
- **No-good cuts**: Exclude visited integer assignments
- **Objective cuts**: Tighten dual bound

### Primal Heuristics
- **NLP solves** at integer-feasible points (via Ipopt)
- **Solution pool** management
- **Rootsearch** for feasible boundary points

## Annotated Components

| Component | Description |
|-----------|-------------|
| `DualSolver.h` | MIP-based dual bound computation |
| `Tasks/TaskSelectHyperplanePointsESH.h` | ESH cut generation |
| `Tasks/TaskSelectHyperplanePointsECP.h` | ECP cut generation |
| `Tasks/TaskFindInteriorPoint.h` | Interior point via slack maximization |
| `Tasks/TaskAddIntegerCuts.h` | No-good cuts (Balas-Jeroslow) |
| `Tasks/TaskPerformBoundTightening.h` | OBBT (optimization-based) |
| `Tasks/TaskReformulateProblem.h` | McCormick envelopes, auxiliary variables |
| `RootsearchMethod/` | Bisection for boundary points |
| `NLPSolver/` | Ipopt integration, minimax solver |

## Mathematical Foundation

**Outer approximation** of convex set $\{x : g(x) \leq 0\}$:

$$\bigcap_{k=1}^{K} \{x : \nabla g(x^k) \cdot (x - x^k) \leq 0\}$$

where $x^k$ are points on the boundary of the feasible region.

## References

- Kronqvist et al. (2016). "The extended supporting hyperplane algorithm for convex MINLP"
- Kronqvist et al. (2019). "A review and comparison of solvers for convex MINLP"
- Westerlund & Pettersson (1995). "An extended cutting plane method"

