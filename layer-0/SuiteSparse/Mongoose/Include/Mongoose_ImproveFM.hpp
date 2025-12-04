/**
 * @file Mongoose_ImproveFM.hpp
 * @brief Fiduccia-Mattheyses partition refinement algorithm
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * FM algorithm improves partitions via gain-based vertex swapping.
 * SwapCandidate tracks vertex, partition side, weight, gain, and heap
 * position. Algorithm maintains boundary heaps, selects highest-gain
 * boundary vertex, swaps, and updates neighbor gains. Allows non-positive
 * moves within search_depth to escape local minima.
 *
 * @algorithm Fiduccia-Mattheyses (FM) Partition Refinement:
 * Local search improving edge cut via gain-based vertex moves:
 * 1. Initialize boundary heaps (vertices with cross-partition edges)
 * 2. Select vertex v with maximum gain = external_deg - internal_deg
 * 3. Move v to other partition, lock it (can't move again this pass)
 * 4. Update gains of v's neighbors
 * 5. Repeat until all vertices locked
 * 6. Roll back to best partition seen during pass
 * 7. Iterate until no improvement or max_refinements reached
 *
 * @math Gain of moving vertex v from partition A to B:
 * $$gain(v) = \sum_{u \in N(v) \cap B} w_{uv} - \sum_{u \in N(v) \cap A} w_{uv}$$
 * = (edges to B) - (edges to A) = benefit of moving v.
 *
 * Non-positive moves allowed within search_depth to escape local minima.
 * Balance constraint: |W_A - W_B| ≤ tolerance enforced during moves.
 *
 * @complexity O(|E|) per pass: each vertex moved once, gains updated in O(deg).
 * Typically 2-5 passes needed for convergence.
 *
 * @ref Fiduccia & Mattheyses (1982). "A Linear-Time Heuristic for Improving
 *   Network Partitions". DAC '82, pp. 175-181. [Original FM algorithm]
 *
 * @see Mongoose_BoundaryHeap.hpp for boundary vertex management
 * @see Mongoose_ImproveQP.hpp for QP-based alternative refinement
 */

/* ========================================================================== */
/* === Include/Mongoose_ImproveFM.hpp ======================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_IMPROVEFM_HPP
#define MONGOOSE_IMPROVEFM_HPP

#include "Mongoose_CutCost.hpp"
#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

/* Swap candidates have the following features: */
struct SwapCandidate
{
    Int vertex;
    bool partition;
    double vertexWeight;
    double gain;
    double heuCost;
    Int bhPosition;
    double imbalance;

    SwapCandidate()
    {
        vertex       = 0;
        partition    = false;
        vertexWeight = 0.0;
        gain         = -INFINITY;
        heuCost      = INFINITY;
        bhPosition   = -1;
        imbalance    = 0.0;
    }
};

void improveCutUsingFM(EdgeCutProblem *, const EdgeCut_Options *);

void fmSwap(EdgeCutProblem *, const EdgeCut_Options *, Int vertex, double gain,
            bool oldPartition);
void fmRefine_worker(EdgeCutProblem *graph, const EdgeCut_Options *options);
void calculateGain(EdgeCutProblem *, const EdgeCut_Options *, Int vertex, double *out_gain,
                   Int *out_externalDegree);

} // end namespace Mongoose

#endif
