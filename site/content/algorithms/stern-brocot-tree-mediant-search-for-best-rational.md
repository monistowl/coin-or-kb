+++
title = "Stern-Brocot tree / mediant search for best rational approximation"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

Given lower bound a/b and upper bound c/d, the mediant (a+c)/(b+d)
      is the simplest rational between them. Binary search narrows to
      the best approximation within tolerance.

</div>

## Complexity

O(log(maxdnom)) iterations

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinRational.hpp") }}** - Rational number representation with double-to-rational conversion

Provides a simple rational number class that can convert floating-point
values to rational approximations. Useful in optimization for converting
floating-point coefficients to exact rational form when needed.

## References

- Stern (1858), Brocot (1861). See also: Graham, Knuth, Patashnik
     "Concrete Mathematics" Ch. 4.5 for Stern-Brocot tree theory.
