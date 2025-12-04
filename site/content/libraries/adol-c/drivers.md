+++
title = "drivers"
description = "High-level driver functions for derivative computation"
template = "page.html"

[extra]
layer = 2
library = "ADOL-C"
header_file = "ADOL-C/include/adolc/drivers/drivers.h"
+++

High-level driver functions for derivative computation

Provides convenient functions for computing common derivative quantities:
- gradient(): First derivative of scalar function (∇f)
- jacobian(): First derivative of vector function (∂F/∂x)
- hessian(): Second derivative of scalar function (∇²f)
- hess_vec(): Hessian-vector product (∇²f · v)
- jac_vec(): Jacobian-vector product (J · v)
- vec_jac(): Vector-Jacobian product (u^T · J)

These drivers wrap the lower-level forward/reverse interfaces and handle
memory allocation and mode selection automatically. All functions require
a pre-recorded tape (via trace_on/trace_off).

## Algorithm

<div class="algorithm-card">

Reverse mode automatic differentiation

**Complexity:** $O(c·n)$ where c = cost of function evaluation (typically c ≈ 4-5)

</div>

## See Also

- interfaces.h for low-level forward/reverse mode calls
- tape_interface.h for tape recording functions
- drivers/taylor.h for higher-order Taylor coefficient drivers
- gradient for computing first derivatives
- jacobian for vector-valued functions
- hessian for second derivatives
- gradient for scalar functions (m=1)
- vec_jac for vector-Jacobian products
- jac_vec for Jacobian-vector products
- jac_vec for Jacobian-vector product (forward mode)
- vec_jac for vector-Jacobian product (reverse mode)
- hessian2 for alternative using Hessian-matrix product
- hess_vec for Hessian-vector product only
- hessian for standard approach
- hess_mat for multiple Hessian-vector products
- hess_mat for multiple directions
- lagra_hess_vec for Lagrangian Hessian-vector product
- hess_vec for single direction
- hess_vec for single scalar function

## Source

Header file: [`ADOL-C/include/adolc/drivers/drivers.h`](/coin-or-kb/browser/?library=ADOL-C&file=ADOL-C/include/adolc/drivers/drivers.h)

