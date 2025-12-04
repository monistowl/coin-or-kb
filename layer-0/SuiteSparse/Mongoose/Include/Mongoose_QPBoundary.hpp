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
 * @algorithm QP Initialization from Discrete Partition:
 * Converts binary partition to QP starting point:
 * 1. Set x_v = 0 for vertices in partition A, x_v = 1 for partition B
 * 2. Compute initial gradient g = Lx (graph Laplacian times x)
 * 3. Identify boundary vertices: those with edges crossing cut
 * 4. Add boundary vertices to free set (can move in [0,1])
 * 5. Mark interior vertices as bound (fixed at 0 or 1)
 *
 * @math Boundary-only optimization:
 * Interior vertices have all neighbors in same partition, so
 * moving them always increases cut. Only boundary vertices can
 * improve cut, so we optimize only over them (free set).
 *
 * Reduces effective problem size from n to |boundary| << n.
 *
 * @complexity O(|E|) to identify boundary vertices via edge scan.
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
