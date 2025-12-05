+++
title = "LP Presolve (Preprocessing)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

## Why This Matters

Presolve is one of the most underappreciated techniques in optimization. It can reduce problem size by 50-90% in many cases, sometimes turning hours-long solves into seconds. Key benefits:

- **Smaller is faster**: A problem with half the variables and constraints solves much more than twice as fast
- **Tighter bounds**: Bound tightening catches fixed variables and removes numerical noise
- **Better LP relaxation**: Removing redundancy often improves the MIP gap

**Example impact**: A 10,000-row LP might presolve to 3,000 rows. That's not just 3x faster — it's potentially 27x faster for simplex (roughly cubic in problem size for dense problems).

**Critical for MIP**: Presolve runs at the root node before branch-and-cut. A smaller, tighter root LP means:
- Fewer branch-and-bound nodes (better bounds enable more pruning)
- Faster LP solves at every node
- Stronger cuts (less degeneracy)

**The catch**: You must postsolve to recover the solution to the original problem. The `CoinPresolveAction` chain stores all transformations in reverse order.

---

Applies reversible transformations to simplify LP before solving:
- Singleton rows/columns: substitute and eliminate
- Doubleton: eliminate free column in 2-element row
- Forcing/dominated constraints: fix variables
- Duplicate rows/columns: merge or eliminate
- Implied free: detect columns with implied bounds from constraints
- Bound tightening: propagate bounds through constraints

Transformations saved as list of CoinPresolveAction objects.
After solving presolved model, postsolve applies actions in reverse
to recover solution to original model.

Multiple passes until no more reductions. Each transformation must
preserve optimal solution recovery.

## Mathematical Formulation

<div class="math-block">

Presolve operations:
Singleton row a_j x_j = b: fix x_j = b/a_j, eliminate row
Doubleton col in a_i x_i + a_j x_j = b with x_j free: x_j = (b - a_i x_i)/a_j
Forcing: if all coeffs same sign and bound known, may fix variables
Implied free: if x_j bounded by constraints, can treat as free
Bound tightening: l_x = max{l_j : a_ij > 0} helps detect fixed vars

</div>

## Complexity

Each pass O(nnz) for most transformations. Total typically
O(passes × nnz) with 3-10 passes common. Can reduce problem size 50-90%.

## Implementations

### Clp

- **{{ link(path="/browser/?library=Clp", text="ClpPresolve.hpp") }}** - Clp interface to CoinPresolve for LP preprocessing

## References

- Andersen & Andersen, "Presolving in LP", Mathematical Programming 71 (1995)
- Gondzio, "Presolve analysis of LP problems prior to IPM",
     Optimization Methods and Software 10 (1997)

Wraps the CoinPresolve framework for use with Clp models. Presolve
simplifies an LP before solving by applying reversible transformations:
removing fixed variables, empty rows/columns, redundant constraints, etc.

The typical workflow is:
1. presolvedModel() - create simplified model
2. Solve the presolved model
3. postsolve() - recover solution to original model
