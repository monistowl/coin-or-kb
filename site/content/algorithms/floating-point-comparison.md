+++
title = "Floating-Point Comparison"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

CoinAbsFltEq: |f1 - f2| < ε (absolute tolerance)
  CoinRelFltEq: |f1 - f2| ≤ ε(1 + max(|f1|, |f2|)) (relative tolerance)

  Special cases:
  - NaN: never equal to anything (including itself)
  - Infinity: inf == inf returns true (practical choice)
  - Exact equality: checked first to handle ±0

## Mathematical Formulation

<div class="math-block">

Absolute: suitable when values are O(1) magnitude
  Relative: suitable when values span orders of magnitude
  Default ε = 1e-10 (double), 1e-6 (float)

</div>

## Complexity

O(1) per comparison

<p>
Example usage:
@verbatim
  double d1 = 3.14159 ;
  double d2 = d1 ;
  double d3 = d1+.0001 ;

  CoinAbsFltEq eq1 ;
  CoinAbsFltEq eq2(.001) ;

  assert(  eq1(d1,d2) ) ;
  assert( !eq1(d1,d3) ) ;
  assert(  eq2(d1,d3) ) ;
@endverbatim
CoinRelFltEq follows the same pattern.

## Implementations

### CoinUtils

- **[CoinFloatEqual.hpp](/browser/?library=CoinUtils)** - Function objects for testing equality of real numbers

Two objects are provided; one tests for equality to an absolute tolerance,
one to a scaled tolerance. The tests will handle IEEE floating point, but
note that infinity == infinity. Mathematicians are rolling in their graves,
but this matches the behaviour for the common practice of using
<code>DBL_MAX</code> (<code>numeric_limits<double>::max()</code>, or similar
large finite number) as infinity.
