+++
title = "CoinRational"
description = "Simple rational number class with numerator and denominator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinRational.hpp"
api_url = "/api/coinutils/CoinRational.json"
+++

Simple rational number class with numerator and denominator.


## Description

Stores a rational number as a ratio of two 64-bit integers. Can be constructed directly from numerator/denominator or by finding the nearest rational approximation to a floating-point value.

## Algorithms

<div class="algorithm-card">
@algorithm Stern-Brocot tree / mediant search for best rational approximation @math Given lower bound a/b and upper bound c/d, the mediant (a+c)/(b+d) is the simplest rational between them. Binary search narrows to the best approximation within tolerance. @complexity O(log(maxdnom)) iterations Stern (1858), Brocot (1861). See also: Graham, Knuth, Patashnik "Concrete Mathematics" Ch. 4.5 for Stern-Brocot tree theory.
</div>

<div class="algorithm-card">
@algorithm Stern-Brocot mediant search @math Maintains interval [a/b, c/d] containing val. Each step computes mediant m = (a+c)/(b+d) and narrows interval. Terminates when |val - m| <= maxdelta or denominator exceeds maxdnom. @complexity O(log(maxdnom)) - each step at least doubles denominator
</div>

## Public Methods

### `getDenominator`

Get the denominator of this rational.

```cpp
int64_t getDenominator()
```

**Returns:** The denominator value

### `getNumerator`

Get the numerator of this rational.

```cpp
int64_t getNumerator()
```

**Returns:** The numerator value

### `CoinRational`

Default constructor creating rational 0/1.

```cpp
 CoinRational()
```

### `CoinRational`

Construct rational from explicit numerator and denominator.

```cpp
 CoinRational(int64_t n, int64_t d)
```

**Parameters:**

- `n` (int64_t) - Numerator
- `d` (int64_t) - Denominator (must not be zero)

### `CoinRational`

Construct by finding nearest rational to a double value.

```cpp
 CoinRational(double val, double maxdelta, int64_t maxdnom)
```

**Parameters:**

- `val` (double) - The floating-point value to approximate
- `maxdelta` (double) - Maximum allowed absolute error
- `maxdnom` (int64_t) - Maximum allowed denominator

<div class="method-card">
**Algorithm:** @algorithm Stern-Brocot tree / mediant search for best rational approximation @math Given lower bound a/b and upper bound c/d, the mediant (a+c)/(b+d) is the simplest rational between them. Binary search narrows to the best approximation within tolerance. @complexity O(log(maxdnom)) iterations Stern (1858), Brocot (1861). See also: Graham, Knuth, Patashnik "Concrete Mathematics" Ch. 4.5 for Stern-Brocot tree theory.
</div>

## Source

Header: `layer-0/CoinUtils/src/CoinRational.hpp`
