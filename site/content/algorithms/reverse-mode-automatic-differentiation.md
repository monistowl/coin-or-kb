+++
title = "Reverse mode automatic differentiation"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

## Complexity

O(c·n) where c = cost of function evaluation (typically c ≈ 4-5)

## Implementations

### ADOL-C

- **{{ link(path="/browser/?library=ADOL-C", text="drivers.h") }}** - High-level driver functions for derivative computation

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
