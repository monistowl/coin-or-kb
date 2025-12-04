/**
 * @file Mongoose_EdgeCut.hpp
 * @brief Edge cut result structure and partitioning entry points
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * EdgeCut struct holds partitioning results: boolean partition array,
 * cut_cost (edge weight sum), cut_size (edge count), partition weights
 * (w0, w1), and imbalance metric. edge_cut() functions are main entry
 * points for computing graph partitions.
 *
 * @algorithm Edge Cut Computation Entry Point:
 * Main driver executing multilevel partitioning pipeline:
 * 1. Build coarsening hierarchy (Mongoose_Coarsening)
 * 2. Compute initial partition on coarsest graph
 * 3. Uncoarsen with FM/QP refinement at each level
 * 4. Return EdgeCut with partition[], cut_cost, imbalance
 *
 * @math Cut quality metrics:
 * - cut_cost = ∑_{(i,j)∈cut} w_{ij} (minimize this)
 * - imbalance = |0.5 - W₀/W| where W = W₀ + W₁
 * - Target: imbalance ≤ soft_split_tolerance
 *
 * @see Mongoose_EdgeCutOptions.hpp for algorithm parameters
 * @see Mongoose_EdgeCutProblem.hpp for internal problem representation
 */

/* ========================================================================== */
/* === Include/Mongoose_EdgeCut.hpp ========================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_EDGECUT_HPP
#define MONGOOSE_EDGECUT_HPP

#include "Mongoose_Graph.hpp"
#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"

namespace Mongoose
{

struct EdgeCut
{
    bool *partition;     /** T/F denoting partition side     */
    Int n;               /** # vertices                      */

    /** Cut Cost Metrics *****************************************************/
    double cut_cost;    /** Sum of edge weights in cut set    */
    Int cut_size;       /** Number of edges in cut set        */
    double w0;          /** Sum of partition 0 vertex weights */
    double w1;          /** Sum of partition 1 vertex weights */
    double imbalance;   /** Degree to which the partitioning
                            is imbalanced, and this is
                            computed as (0.5 - W0/W).         */

    // desctructor (no constructor)
    ~EdgeCut();
};

EdgeCut *edge_cut(const Graph *);
EdgeCut *edge_cut(const Graph *, const EdgeCut_Options *);
EdgeCut *edge_cut(EdgeCutProblem *problem, const EdgeCut_Options *options);

} // end namespace Mongoose

#endif
