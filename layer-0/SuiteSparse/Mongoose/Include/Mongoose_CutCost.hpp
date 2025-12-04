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
