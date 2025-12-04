+++
title = "cppad"
description = "Contains all variables and functions defined by CppAD package"
template = "page.html"

[extra]
layer = 1
library = "CppAD"
header_file = "include/cppad/cppad.hpp"
+++

## Algorithm

<div class="algorithm-card">

Operator overloading records a "tape" of operations.
           Forward mode: propagates derivatives from inputs to outputs.
           Reverse mode: propagates derivatives from outputs to inputs.
           Reverse mode is more efficient for many inputs, few outputs.

<div class="refs">

**References:**
- Griewank, Walther (2008). "Evaluating Derivatives: Principles and      Techniques of Algorithmic Differentiation", 2nd ed. SIAM.

</div>

</div>

## See Also

- AD for the automatic differentiation scalar type
- ADFun for the recorded function object
- Ipopt for nonlinear optimization using CppAD derivatives

@namespace CppAD

## Source

Header file: [`include/cppad/cppad.hpp`](/coin-or-kb/browser/?library=CppAD&file=include/cppad/cppad.hpp)

