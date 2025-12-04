/**
 * @file Mongoose_IO.hpp
 * @brief Matrix Market file I/O for graphs and matrices
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * File I/O for Mongoose: read_graph creates Graph from Matrix Market file,
 * read_matrix creates cs struct. Handles symmetrization (A+A')/2 for
 * asymmetric matrices, extracts largest connected component, removes
 * diagonal. Accepts C string or std::string filenames.
 *
 * @algorithm Matrix Market Import Pipeline:
 * Reads standard sparse matrix format into Mongoose graph:
 *
 * 1. Parse Matrix Market header (format, type, symmetry)
 * 2. Read coordinate entries into triplet form
 * 3. Convert triplet to CSC via cs_compress
 * 4. Symmetrize if needed: A = (A + A^T)/2
 * 5. Remove diagonal (self-loops)
 * 6. Extract largest connected component (via BFS)
 * 7. Return Graph or cs struct
 *
 * @math Connected component extraction:
 * BFS from arbitrary vertex marks reachable set.
 * If not all vertices reached, restart BFS from unmarked vertex.
 * Keep only largest component for partitioning.
 *
 * @complexity O(n + nz) for parsing and preprocessing.
 *
 * @see Mongoose_Graph.hpp for Graph class
 * @see Mongoose_CSparse.hpp for cs matrix struct
 */

/* ========================================================================== */
/* === Include/Mongoose_IO.hpp ============================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_IO_HPP
#define MONGOOSE_IO_HPP

#include "Mongoose_CSparse.hpp"
#include "Mongoose_Graph.hpp"
#include "Mongoose_Internal.hpp"
#include <string>

extern "C"
{
#include "mmio.h"
}

namespace Mongoose
{

/**
 * Generate a Graph from a Matrix Market file.
 *
 * Generate a Graph class instance from a Matrix Market file. The matrix
 * contained in the file must be sparse, real, and square. If the matrix
 * is not symmetric, it will be made symmetric with (A+A')/2. If the matrix has
 * more than one connected component, the largest will be found and the rest
 * discarded. If a diagonal is present, it will be removed.
 *
 * @param filename the filename or path to the Matrix Market File.
 */
Graph *read_graph(const std::string &filename);

/**
 * Generate a CSparse matrix from a Matrix Market file.
 *
 * Generate a cs struct instance from a Matrix Market file. The matrix
 * contained in the file must be sparse, real, and square. If the matrix
 * is not symmetric, it will be made symmetric with (A+A')/2. If the matrix has
 * more than one connected component, the largest will be found and the rest
 * discarded. If a diagonal is present, it will be removed.
 *
 * @param filename the filename or path to the Matrix Market File.
 * @param matcode the four character Matrix Market type code.
 */
cs *read_matrix(const std::string &filename, MM_typecode &matcode);

/**
 * Generate a Graph from a Matrix Market file.
 *
 * Generate a Graph class instance from a Matrix Market file. The matrix
 * contained in the file must be sparse, real, and square. If the matrix
 * is not symmetric, it will be made symmetric with (A+A')/2. If the matrix has
 * more than one connected component, the largest will be found and the rest
 * discarded. If a diagonal is present, it will be removed.
 *
 * @param filename the filename or path to the Matrix Market File.
 */
Graph *read_graph(const char *filename);

/**
 * Generate a CSparse matrix from a Matrix Market file.
 *
 * Generate a cs struct instance from a Matrix Market file. The matrix
 * contained in the file must be sparse, real, and square. If the matrix
 * is not symmetric, it will be made symmetric with (A+A')/2. If the matrix has
 * more than one connected component, the largest will be found and the rest
 * discarded. If a diagonal is present, it will be removed.
 *
 * @param filename the filename or path to the Matrix Market File.
 * @param matcode the four character Matrix Market type code.
 */
cs *read_matrix(const char *filename, MM_typecode &matcode);

} // end namespace Mongoose

#endif
