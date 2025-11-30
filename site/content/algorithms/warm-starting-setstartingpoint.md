+++
title = "Warm Starting (setStartingPoint)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Initialize from previous NLP solution or MIP point:
  - Improves convergence for similar subproblems
  - Critical for efficiency in repeated NLP solves

## Mathematical Formulation

<div class="math-block">

l_i = u_i = x̄_i for integer variables i ∈ I
  Ipopt solves reduced-space problem over continuous variables.
  Original bounds restored by unfixVariables().

</div>

## Complexity

O(nnz) vs O(n²) for dense evaluation

## Implementations

### SHOT

- **[NLPSolverIpoptBase.h](/coin-or-kb/browser/?library=SHOT)** - Ipopt implementation of INLPSolver interface

Provides NLP solving for SHOT's primal problem using Ipopt interior point.

**IpoptProblem Class (Ipopt::TNLP):**
- Implements Ipopt's TNLP interface
- Provides callbacks for function/gradient/Hessian evaluation
- Sparse Jacobian/Hessian via index placement maps

**TNLP Callbacks:**
- get_nlp_info(): Problem dimensions and sparsity
- get_bounds_info(): Variable and constraint bounds
- eval_f(): Objective function value
- eval_grad_f(): Objective gradient
- eval_g(): Constraint function values
- eval_jac_g(): Constraint Jacobian (sparse)
- eval_h(): Lagrangian Hessian (sparse)
- finalize_solution(): Store optimal point

**NLPSolverIpoptBase Class:**
- Wraps IpoptApplication for solve control
- Variable fixing for integer-fixed NLP subproblems
- Starting point management

**IpoptJournal:**
- Routes Ipopt output through SHOT logging system

@note Used for fixed-integer NLP subproblems in primal bound computation

## References

- Bonami et al. (2008) - BONMIN algorithm description
- Wächter & Biegler (2006) - Ipopt implementation
- Nocedal & Wright (2006) - Warm starting in IPM
