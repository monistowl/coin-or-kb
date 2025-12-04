/**
 * @file Mongoose_GuessCut.hpp
 * @brief Initial partition generation at coarsest level
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * GuessCut creates initial partition for coarsest graph before refinement
 * begins. Strategies include QP relaxation, random assignment, or natural
 * vertex order. Quality of initial guess affects final partition quality
 * despite refinement. Selected via initial_cut_type option.
 *
 * @see Mongoose_EdgeCutOptions.hpp for InitialEdgeCutType selection
 * @see Mongoose_ImproveQP.hpp for QP-based initial cut
 */

/* ========================================================================== */
/* === Include/Mongoose_GuessCut.hpp ======================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_GUESSCUT_HPP
#define MONGOOSE_GUESSCUT_HPP

#include "Mongoose_BoundaryHeap.hpp"
#include "Mongoose_CutCost.hpp"
#include "Mongoose_Graph.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_EdgeCutOptions.hpp"

namespace Mongoose
{

bool guessCut(EdgeCutProblem *, const EdgeCut_Options *);

} // end namespace Mongoose

#endif
