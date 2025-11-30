+++
title = "MPS File Parsing"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "File I/O"
implementation_count = 1
+++

Sections: NAME, ROWS, COLUMNS, RHS, RANGES, BOUNDS, ENDATA
  Fixed format: columns 1-2 (type), 5-12 (name1), 15-22 (name2), etc.
  Free format: whitespace-separated fields

  Row types: N (free/objective), E (equality), L (≤), G (≥)
  Bound types: LO, UP, FX, FR, MI, PL, BV (binary), UI/LI (integer)
  Extensions: QUADOBJ (Hessian), SOS (special ordered sets)

## Mathematical Formulation

<div class="math-block">

Reads: min c'x s.t. l ≤ Ax ≤ u, lb ≤ x ≤ ub
  RANGES section: row_i has both lower and upper when range specified
  Integer markers: 'MARKER' 'INTORG'/'INTEND' for integer variables

</div>

## Complexity

Parsing: O(file_size), single pass with hash tables for names
  Supports gzip/bzip2 compression via CoinFileIO abstraction

## Implementations

### CoinUtils

- **[CoinMpsIO.hpp](/coin-or-kb/browser/?library=CoinUtils)** - MPS file format reader/writer for LP and MIP problems

Reads/writes standard MPS format including extensions for quadratic,
conic, and SOS constraints. Supports free format and compression.
