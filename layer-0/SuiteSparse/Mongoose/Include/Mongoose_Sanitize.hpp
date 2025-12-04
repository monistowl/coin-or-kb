/**
 * @file Mongoose_Sanitize.hpp
 * @brief Matrix preprocessing for graph partitioning
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Matrix sanitization prepares input for partitioning: sanitizeMatrix
 * handles symmetry and binary weights, removeDiagonal strips self-loops,
 * mirrorTriangular expands triangular to symmetric. Ensures valid
 * undirected graph representation for algorithms.
 *
 * @algorithm Graph Preprocessing Pipeline:
 * Transforms arbitrary sparse matrix into valid undirected graph:
 *
 * sanitizeMatrix steps:
 * 1. Remove diagonal entries (self-loops invalid for partitioning)
 * 2. If triangular: mirror to create symmetric matrix A + A^T
 * 3. If binary requested: set all edge weights to 1
 * 4. Return cleaned CSC matrix
 *
 * @math Symmetry requirement:
 * Graph partitioning requires undirected graphs: A = A^T.
 * If input is lower triangular L, compute A = L + L^T.
 * Diagonal removal: A = A - diag(A).
 *
 * Binary weights useful when only topology matters, not edge strengths.
 *
 * @complexity O(n + nz) for all operations.
 * mirrorTriangular doubles storage to 2×nz.
 *
 * @see Mongoose_IO.hpp for file input using sanitization
 * @see Mongoose_CSparse.hpp for cs matrix operations
 */

/* ========================================================================== */
/* === Include/Mongoose_Sanitize.hpp ======================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_SANITIZE_HPP
#define MONGOOSE_SANITIZE_HPP

#include "Mongoose_CSparse.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

cs *sanitizeMatrix(cs *compressed_A, bool symmetricTriangular,
                   bool makeEdgeWeightsBinary);
void removeDiagonal(cs *A);
// Requires A to be a triangular matrix with no diagonal.
cs *mirrorTriangular(cs *A);

} // end namespace Mongoose

#endif
