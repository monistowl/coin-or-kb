/**
 * @file Mongoose_Graph.hpp
 * @brief Graph data structure for Mongoose partitioning
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Graph class stores adjacency in CSC format (p, i arrays) with optional
 * edge weights (x) and vertex weights (w). Factory methods create from
 * raw arrays or CSparse matrices. Shallow copy flags track ownership.
 *
 * @algorithm Compressed Sparse Column (CSC) Graph Representation:
 * Standard sparse matrix format optimized for column access:
 *
 * Arrays:
 * - p[n+1]: Column pointers. Neighbors of vertex j are at i[p[j]..p[j+1]-1]
 * - i[nz]: Row indices (neighbor IDs for each edge)
 * - x[nz]: Edge weights (optional, default 1)
 * - w[n]: Vertex weights (optional, default 1)
 *
 * @math CSC interpretation for graphs:
 * For undirected graph, store symmetric adjacency matrix A:
 * A[i,j] = edge weight between i and j (0 if no edge).
 * p[j+1] - p[j] = degree of vertex j.
 *
 * Memory ownership: shallow_* flags indicate borrowed vs owned arrays.
 * Factory methods from CSparse matrices share data when possible.
 *
 * @complexity O(n + nz) storage.
 * Neighbor iteration: O(degree) per vertex.
 *
 * @see Mongoose_EdgeCutProblem.hpp for extended graph with partition state
 * @see Mongoose_CSparse.hpp for CSparse matrix format
 */

/* ========================================================================== */
/* === Include/Mongoose_Graph.hpp =========================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_GRAPH_HPP
#define MONGOOSE_GRAPH_HPP

#include "Mongoose_CSparse.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

class Graph
{
public:
    /** Graph Data ***********************************************************/
    Int n;     /** # vertices                      */
    Int nz;    /** # edges                         */
    Int *p;    /** Column pointers                 */
    Int *i;    /** Row indices                     */
    double *x; /** Edge weight                     */
    double *w; /** Node weight                     */

    /* Constructors & Destructor */
    static Graph *create(const Int _n, const Int _nz, Int *_p = NULL,
                         Int *_i = NULL, double *_x = NULL, double *_w = NULL);
    static Graph *create(cs *matrix);
    static Graph *create(cs *matrix, bool free_when_done);
    ~Graph();

private:
    Graph();

    /** Memory Management Flags ***********************************************/
    bool shallow_p;
    bool shallow_i;
    bool shallow_x;
    bool shallow_w;
};

} // end namespace Mongoose

#endif
