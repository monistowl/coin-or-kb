+++
title = "cs"
description = "Concise Sparse matrix library - teaching implementation of sparse algorithms"
template = "page.html"

[extra]
layer = 0
library = "SuiteSparse"
header_file = "CSparse/Include/cs.h"
+++

Concise Sparse matrix library - teaching implementation of sparse algorithms

CSparse provides a minimal, readable implementation of core sparse matrix
operations. It serves as both a standalone library and educational reference
for sparse linear algebra algorithms.

Key features:
- Sparse matrix in triplet or compressed-column (CSC) format
- Sparse Cholesky (cs_chol), LU (cs_lu), and QR (cs_qr) factorization
- Fill-reducing orderings via AMD
- Direct solvers: cs_cholsol, cs_lusol, cs_qrsol
- Dulmage-Mendelsohn decomposition (cs_dmperm)

## Algorithm

<div class="algorithm-card">

Sparse Matrix Operations:
  - Compressed-column (CSC): column pointers + row indices + values
  - cs_compress: O(nnz) triplet to CSC conversion
  - cs_multiply: sparse matrix-matrix product using symbolic + numeric phases
  - cs_chol/cs_lu/cs_qr: left-looking factorization algorithms

<div class="math">

Sparse formats:
CSC: A stored as (p, i, x) where p[j]..p[j+1]-1 index column j entries
Triplet (COO): (row[k], col[k], val[k]) for k = 0..nz-1

</div>

**Complexity:** Space: $O(nnz + n)$ for CSC format
  cs_compress: $O(nnz)$ time for triplet → CSC
  cs_multiply: $O(flops)$ where flops depends on sparsity pattern
  cs_chol/cs_lu: $O(nnz(L)$²/n) typical for sparse factors

<div class="refs">

**References:**
- Davis (2006). "Direct Methods for Sparse Linear Systems".      SIAM. ISBN: 978-0-898716-13-9

</div>

</div>

## See Also

- CXSparse for extended version with complex numbers
- CHOLMOD, UMFPACK for production-quality implementations
- cs_compress() to convert triplet to CSC
- CS_CSC(), CS_TRIPLET() macros to check format
- cs_schol() for symbolic Cholesky analysis
- cs_sqr() for symbolic QR analysis
- cs_chol() for numeric Cholesky
- cs_lu() for numeric LU
- cs_qr() for numeric QR
- cs_dmperm() for computing this decomposition
- cs_scc() for strongly connected components

## Source

Header file: `CSparse/Include/cs.h`

