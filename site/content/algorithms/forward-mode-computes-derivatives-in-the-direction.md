+++
title = "Forward mode computes derivatives in the direction of inputs."
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Reverse mode computes derivatives from outputs backward.
           Forward: O(n) per direction, Reverse: O(m) per output.
           Use forward when n < m, reverse when n > m.

## Implementations

### CppAD

- **[ad_fun.hpp](/coin-or-kb/browser/?library=CppAD)** - ADFun class - function object storing recorded AD operations

ADFun<Base> stores a recorded sequence of operations and provides
methods to evaluate the function and its derivatives.

Key methods:
- **Forward(p, x)**: p-th order forward mode Taylor coefficient
- **Reverse(q, w)**: q-th order reverse mode derivative
- **Jacobian(x)**: Full Jacobian matrix
- **Hessian(x, w)**: Weighted Hessian matrix
- **SparseJacobian/SparseHessian**: Sparse derivative computation
