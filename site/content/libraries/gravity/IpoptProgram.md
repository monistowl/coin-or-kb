+++
title = "IpoptProgram"
description = "Ipopt solver interface implementing TNLP callbacks"
template = "page.html"

[extra]
layer = 4
library = "Gravity"
header_file = "include/gravity/IpoptProgram.h"
+++

Ipopt solver interface implementing TNLP callbacks

Adapts Gravity models to Ipopt's TNLP (Templated NLP) interface.

**IpoptProgram<type> Class:**
- Inherits from Ipopt::TNLP and Program<type>
- _model: Pointer to Gravity Model

**Required TNLP Callbacks:**
- get_nlp_info(): Return problem dimensions (n, m, nnz_jac, nnz_hess)
- get_bounds_info(): Variable and constraint bounds
- get_starting_point(): Initial x, z_L, z_U, lambda
- eval_f(): Objective function value
- eval_grad_f(): Objective gradient
- eval_g(): Constraint values
- eval_jac_g(): Jacobian values and structure
- eval_h(): Hessian of Lagrangian
- finalize_solution(): Copy solution back to model

**Sparsity Pattern:**
- First call to eval_jac_g/eval_h: return structure (iRow, jCol)
- Subsequent calls: return values only
- Gravity tracks via _first_call_jac, _first_call_hess

**Solution Recovery:**
- finalize_solution() copies x values to model variables
- Retrieves dual values (lambda) for constraints
- Retrieves bound multipliers (z_L, z_U)

## Algorithm

<div class="algorithm-card">

Interior Point Method via Ipopt

</div>

## See Also

- gravity/solver.h for unified solver interface
- layer-2/Ipopt/ for Ipopt implementation details

## Source

Header file: [`include/gravity/IpoptProgram.h`](/coin-or-kb/browser/?library=Gravity&file=include/gravity/IpoptProgram.h)

