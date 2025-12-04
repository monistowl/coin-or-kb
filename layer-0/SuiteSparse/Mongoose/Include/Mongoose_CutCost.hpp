/**
 * @file Mongoose_CutCost.hpp
 * @brief Partition quality metrics structure
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * CutCost struct holds partition quality metrics: heuCost (cut + balance
 * penalty), cutCost (edge weight sum), W[2] (partition weights), and
 * imbalance (deviation from target split). Used internally to evaluate
 * and compare partitions during refinement.
 *
 * @algorithm Partition Quality Evaluation:
 * Tracks two competing objectives during partitioning:
 *
 * Fields:
 * - cutCost: Σ w_ij for edges (i,j) crossing the partition
 * - W[0], W[1]: Total vertex weight in each partition
 * - imbalance: target_split - W[0]/W (deviation from ideal)
 * - heuCost: Combined cost = cutCost + penalty(imbalance)
 *
 * @math Heuristic cost with balance penalty:
 * $$heuCost = cutCost + \lambda \cdot (imbalance)^2$$
 *
 * Penalty term ensures algorithm finds balanced partitions.
 * λ trades off cut quality vs balance: higher λ → more balanced.
 *
 * @complexity O(1) to store and compare; O(|E|) to recompute from scratch.
 * Incremental updates during FM: O(degree) per vertex move.
 *
 * @see Mongoose_EdgeCut.hpp for public partition result
 * @see Mongoose_ImproveFM.hpp for gain calculations
 */

/* ========================================================================== */
/* === Include/Mongoose_CutCost.hpp ========================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_CUTCOST_HPP
#define MONGOOSE_CUTCOST_HPP

namespace Mongoose
{

/* A partitioning has the following metrics: */
struct CutCost
{
    double heuCost;   /* Sum of cutCost and balance penalty       */
    double cutCost;   /* Sum of edge weights in the cut set.      */
    double W[2];      /* Sum of vertex weights in each partition. */
    double imbalance; /* target_split - (W[0] / W)                 */
};

} // end namespace Mongoose

#endif
