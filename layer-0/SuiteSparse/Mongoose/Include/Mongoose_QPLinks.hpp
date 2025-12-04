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
