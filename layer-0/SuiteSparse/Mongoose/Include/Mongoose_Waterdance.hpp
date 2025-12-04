/**
 * @file Mongoose_Waterdance.hpp
 * @brief Alternating FM/QP refinement passes for partition improvement
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Waterdance alternates between FM (discrete swaps) and QP (continuous
 * optimization) refinement passes. The interplay ("dance") between methods
 * escapes local minima that either method alone would get stuck in.
 * Number of dances controlled by num_dances option.
 *
 * @algorithm Waterdance (Hybrid FM/QP Refinement):
 * Alternates discrete and continuous optimization to escape local minima:
 * for i = 1 to num_dances:
 *   1. Run QP gradient projection (continuous relaxation)
 *   2. Round QP solution to discrete partition
 *   3. Run FM passes (discrete vertex swaps)
 *   4. If no improvement in both, terminate early
 *
 * @math Intuition for hybrid approach:
 * - FM: fast local moves, explores discrete neighborhood
 * - QP: smooth objective, can "jump over" discrete barriers
 * - Alternating: FM finds local minimum → QP perturbs → FM refines
 *
 * The "waterdance" metaphor: like water finding lowest point via
 * different flow patterns (discrete drops vs continuous flow).
 *
 * @complexity O(num_dances × |E|) per coarsening level.
 * Default num_dances = 1-2; more for difficult graphs.
 *
 * @see Mongoose_ImproveFM.hpp for Fiduccia-Mattheyses refinement
 * @see Mongoose_ImproveQP.hpp for quadratic programming refinement
 */

/* ========================================================================== */
/* === Include/Mongoose_Waterdance.hpp ====================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_WATERDANCE_HPP
#define MONGOOSE_WATERDANCE_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

void waterdance(EdgeCutProblem *, const EdgeCut_Options *);

} // end namespace Mongoose

#endif
