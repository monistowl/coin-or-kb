/**
 * @file Mongoose_QPLinks.hpp
 * @brief QP free set rounding and partition conversion
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QPLinks converts continuous QP solution to discrete partition by
 * rounding fractional variables and updating free set. Handles the
 * interface between continuous relaxation and discrete partition
 * representation in the waterdance refinement cycle.
 *
 * @algorithm QP Solution Rounding:
 * Converts continuous x ∈ [0,1]^n to discrete partition {0,1}^n:
 * 1. For each vertex v:
 *    - If x_v already 0 or 1: keep as is
 *    - If x_v ∈ (0,1): round to nearest (0 if x_v < 0.5, else 1)
 * 2. Update partition arrays and cut cost
 * 3. Identify new boundary vertices (neighbors across cut)
 * 4. Update free set status for subsequent QP iterations
 *
 * @math Rounding preserves cut quality intuition:
 * QP minimizes ½x'Lx which penalizes edges (i,j) by w_ij·(x_i - x_j)².
 * Fractional values indicate "uncertain" assignment; rounding to
 * nearest integer preserves the QP's preference.
 *
 * @complexity O(|E|) to scan edges and update cut cost.
 *
 * @see Mongoose_QPDelta.hpp for QP state representation
 * @see Mongoose_ImproveQP.hpp for QP improvement workflow
 */

/* ========================================================================== */
/* === Include/Mongoose_QPLinks.hpp ========================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_QPLINKS_HPP
#define MONGOOSE_QPLINKS_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_QPDelta.hpp"

namespace Mongoose
{

bool QPLinks(EdgeCutProblem *, const EdgeCut_Options *, QPDelta *);

} // end namespace Mongoose

#endif
