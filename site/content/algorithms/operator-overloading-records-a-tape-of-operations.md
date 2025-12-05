+++
title = "Operator overloading records a \"tape\" of operations."
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Forward mode: propagates derivatives from inputs to outputs.
           Reverse mode: propagates derivatives from outputs to inputs.
           Reverse mode is more efficient for many inputs, few outputs.

## Implementations

### CppAD

- **[cppad.hpp](/browser/?library=CppAD)** - Contains all variables and functions defined by CppAD package

## References

- Griewank, Walther (2008). "Evaluating Derivatives: Principles and
     Techniques of Algorithmic Differentiation", 2nd ed. SIAM.
