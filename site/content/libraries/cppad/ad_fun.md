+++
title = "ad_fun"
description = "ADFun class - function object storing recorded AD operations"
template = "page.html"

[extra]
layer = 1
library = "CppAD"
header_file = "include/cppad/core/ad_fun.hpp"
+++

ADFun class - function object storing recorded AD operations

ADFun<Base> stores a recorded sequence of operations and provides
methods to evaluate the function and its derivatives.

Key methods:
- **Forward(p, x)**: p-th order forward mode Taylor coefficient
- **Reverse(q, w)**: q-th order reverse mode derivative
- **Jacobian(x)**: Full Jacobian matrix
- **Hessian(x, w)**: Weighted Hessian matrix
- **SparseJacobian/SparseHessian**: Sparse derivative computation

## Algorithm

<div class="algorithm-card">

Forward mode computes derivatives in the direction of inputs.
           Reverse mode computes derivatives from outputs backward.
           Forward: O(n) per direction, Reverse: O(m) per output.
           Use forward when n < m, reverse when n > m.

</div>

## See Also

- AD<Base> for the scalar type that records operations

## Source

Header file: [`include/cppad/core/ad_fun.hpp`](/coin-or-kb/browser/?library=CppAD&file=include/cppad/core/ad_fun.hpp)

