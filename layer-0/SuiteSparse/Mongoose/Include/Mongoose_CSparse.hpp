/**
 * @file Mongoose_CSparse.hpp
 * @brief Sparse matrix operations subset from CSparse library
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Provides CSparse subset for sparse matrix operations: cs struct
 * (compressed column/triplet format), cs_add (matrix addition),
 * cs_transpose, cs_compress (triplet to CSC), and allocation.
 * Uses int64_t (csi) matching Mongoose's Int type.
 *
 * @algorithm CSparse Subset for Graph I/O:
 * Minimal CSparse operations needed for graph construction:
 *
 * Data structure (cs):
 * - CSC mode (nz == -1): p[n+1] column pointers, i[nzmax] row indices
 * - Triplet mode (nz >= 0): p[nzmax] col indices, i[nzmax] row indices
 *
 * Operations:
 * - cs_compress: Convert triplet to CSC, O(n + nz)
 * - cs_transpose: Compute A^T, O(n + nz)
 * - cs_add: Compute αA + βB, O(nnz(A) + nnz(B))
 *
 * @math Triplet to CSC conversion:
 * 1. Count column lengths: O(nz)
 * 2. Cumulative sum → column pointers: O(n)
 * 3. Scatter entries into CSC: O(nz)
 *
 * @complexity All operations O(n + nz) time and space.
 *
 * @ref Davis (2006). "Direct Methods for Sparse Linear Systems".
 *   SIAM, Chapters 1-2 for CSparse design.
 *
 * @see Mongoose_Graph.hpp for graph representation using cs format
 * @see Mongoose_IO.hpp for reading matrices from files
 */

/* ========================================================================== */
/* === Include/Mongoose_CSparse.hpp ========================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Libraryb Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_CSPARSE_HPP
#define MONGOOSE_CSPARSE_HPP

#include "Mongoose_Internal.hpp"
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* same as Int in Mongoose */
typedef int64_t csi;

/* CSparse Macros */
#ifndef CS_CSC
#define CS_CSC(A) ((A) && ((A)->nz == -1))
#endif
#ifndef CS_TRIPLET
#define CS_TRIPLET(A) ((A) && ((A)->nz >= 0))
#endif

namespace Mongoose
{

/* --- primary CSparse routines and data structures ------------------------- */
typedef struct cs_sparse /* matrix in compressed-column or triplet form */
{
    csi nzmax; /* maximum number of entries */
    csi m;     /* number of rows */
    csi n;     /* number of columns */
    csi *p;    /* column pointers (size n+1) or col indices (size nzmax) */
    csi *i;    /* row indices, size nzmax */
    double *x; /* numerical values, size nzmax */
    csi nz;    /* # of entries in triplet matrix, -1 for compressed-col */
} cs;

cs *cs_add(const cs *A, const cs *B, double alpha, double beta);
cs *cs_transpose(const cs *A, csi values);

cs *cs_compress(const cs *T);

cs *cs_spalloc(csi m, csi n, csi nzmax, csi values, csi triplet);
cs *cs_spfree(cs *A);

} // end namespace Mongoose

#endif
