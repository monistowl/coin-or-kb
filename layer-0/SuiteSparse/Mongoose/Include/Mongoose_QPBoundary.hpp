/**
 * @file Mongoose_QPBoundary.hpp
 * @brief QP boundary initialization from graph partition
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QPBoundary initializes QP state from discrete partition, setting
 * x values based on partition assignment and identifying boundary
 * vertices (those with neighbors in opposite partition) as the
 * active set for optimization.
 *
 * @see Mongoose_QPDelta.hpp for QP state structure
 * @see Mongoose_QPGradProj.hpp for subsequent optimization
 */

/* ========================================================================== */
/* === Include/Mongoose_QPBoundary.hpp ====================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_QPBOUNDARY_HPP
#define MONGOOSE_QPBOUNDARY_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_QPDelta.hpp"

namespace Mongoose
{

void QPBoundary(EdgeCutProblem *, const EdgeCut_Options *, QPDelta *);

} // end namespace Mongoose

#endif
