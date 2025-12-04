/**
 * @file Mongoose_Coarsening.hpp
 * @brief Graph coarsening via vertex matching for multilevel partitioning
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Coarsening reduces graph size while preserving structure by contracting
 * matched vertices. Given a matching (HEM, random, etc.), creates coarser
 * graph with merged vertices and aggregated edge weights. Essential for
 * multilevel partitioning to handle large graphs efficiently.
 *
 * @see Mongoose_Matching.hpp for vertex matching algorithms
 * @see Mongoose_Refinement.hpp for uncoarsening/projection
 */

/* ========================================================================== */
/* === Include/Mongoose_Coarsening.hpp ====================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_COARSENING_HPP
#define MONGOOSE_COARSENING_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_Matching.hpp"

namespace Mongoose
{

EdgeCutProblem *coarsen(EdgeCutProblem *, const EdgeCut_Options *);

} // end namespace Mongoose

#endif
