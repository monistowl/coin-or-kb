+++
title = "Sparsity Pattern Extraction (getConstraintsJacobianSparsityPattern)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Identifies nonzero structure for efficient derivative computation:

## Mathematical Formulation

<div class="math-block">

Jacobian ∂g_i/∂x_j: sparse pattern for AD evaluation
  Used by NLP solvers (Ipopt) and for hyperplane construction.

</div>

## Complexity

O(nnz) where nnz = number of variable appearances in constraints

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="Problem.h") }}** - Core problem representation with variables, constraints, and objective

Central data structure holding the optimization problem definition.

**ProblemProperties Struct:**
- Convexity classification (Convex, Nonconvex, NotSet)
- Problem type flags (MINLP, MIQP, MILP, NLP, etc.)
- Variable counts by type (real, binary, integer, auxiliary)
- Constraint counts by type (linear, quadratic, nonlinear)

**SpecialOrderedSet Struct:**
- SOS1 (at most one variable nonzero) or SOS2 (contiguous nonzeros)
- Variables and optional weights

**Problem Class:**
- allVariables, realVariables, binaryVariables, etc.
- linearConstraints, quadraticConstraints, nonlinearConstraints
- objectiveFunction (linear, quadratic, or nonlinear)
- Sparsity patterns for Jacobian and Hessian
- Feasibility bound propagation (FBBT) for tightening bounds

**Key Methods:**
- add(): Add variables, constraints, objective
- finalize(): Compute properties and sparsity patterns
- getMostDeviatingNumericConstraint(): Find worst violation
- createCopy(): Clone for reformulation

## References

- Belotti et al. (2009) - Branching and bounds tightening techniques
- ESH (Extended Supporting Hyperplane) uses this for cut generation
- McCormick (1976) - Convex relaxations via factorable functions
