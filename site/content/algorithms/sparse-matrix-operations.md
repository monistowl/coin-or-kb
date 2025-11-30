+++
title = "Sparse Matrix Operations"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Data Structures"
implementation_count = 1
+++

- Compressed-column (CSC): column pointers + row indices + values
  - cs_compress: O(nnz) triplet to CSC conversion
  - cs_multiply: sparse matrix-matrix product using symbolic + numeric phases
  - cs_chol/cs_lu/cs_qr: left-looking factorization algorithms

## Mathematical Formulation

<div class="math-block">

Sparse formats:
  CSC: A stored as (p, i, x) where p[j]..p[j+1]-1 index column j entries
  Triplet (COO): (row[k], col[k], val[k]) for k = 0..nz-1

</div>

## Complexity

Space: O(nnz + n) for CSC format
  cs_compress: O(nnz) time for triplet → CSC
  cs_multiply: O(flops) where flops depends on sparsity pattern
  cs_chol/cs_lu: O(nnz(L)²/n) typical for sparse factors

## Implementations

### SuiteSparse

- **[cs.h](/coin-or-kb/browser/?library=SuiteSparse)** - Concise Sparse matrix library - teaching implementation of sparse algorithms

CSparse provides a minimal, readable implementation of core sparse matrix
operations. It serves as both a standalone library and educational reference
for sparse linear algebra algorithms.

Key features:
- Sparse matrix in triplet or compressed-column (CSC) format
- Sparse Cholesky (cs_chol), LU (cs_lu), and QR (cs_qr) factorization
- Fill-reducing orderings via AMD
- Direct solvers: cs_cholsol, cs_lusol, cs_qrsol
- Dulmage-Mendelsohn decomposition (cs_dmperm)

## References

- Davis (2006). "Direct Methods for Sparse Linear Systems".
     SIAM. ISBN: 978-0-898716-13-9
