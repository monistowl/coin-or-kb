+++
title = "LP File Parsing"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "File I/O"
implementation_count = 1
+++

Sections: Minimize/Maximize, Subject To, Bounds, Integers/Generals/Binaries, End
  Algebraic format: constraint_name: coeff1*var1 + coeff2*var2 <= rhs

  Constraint types: <= (L), >= (G), = (E)
  Bound keywords: Free, Inf, -Inf
  Variable types: Integers, Generals (same), Binaries, Semi-Continuous

## Mathematical Formulation

<div class="math-block">

Reads: min/max c'x s.t. Ax ≤ b, Ax ≥ b, Ax = b
  Bounds: lb ≤ x ≤ ub or x free
  Integrality: x ∈ Z or x ∈ {0,1}

</div>

## Complexity

Parsing: O(file_size), token-based lexer
  More human-readable than MPS but less standardized

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinLpIO.hpp") }}** - LP file format reader/writer for linear programming problems

Reads/writes CPLEX LP format with Min/Max objective, constraints,
bounds, and integer/binary variable declarations.
