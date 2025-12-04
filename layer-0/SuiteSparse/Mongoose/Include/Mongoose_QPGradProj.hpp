/**
 * @file Mongoose_QPGradProj.hpp
 * @brief Projected gradient descent for QP partition optimization
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QPGradProj implements gradient projection for bound-constrained QP:
 * minimizes quadratic cut objective subject to box constraints [0,1]
 * and balance constraint (lo <= a'x <= hi). Projects gradient onto
 * feasible region, iterates until convergence or iteration limit.
 *
 * @see Mongoose_QPDelta.hpp for QP state (x, gradient, free set)
 * @see Mongoose_QPNapsack.hpp for napsack subproblem solver
 */

/* ========================================================================== */
/* === Include/Mongoose_QPGradProj.hpp ====================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_QPGRADPROJ_HPP
#define MONGOOSE_QPGRADPROJ_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_QPDelta.hpp"

namespace Mongoose
{

double QPGradProj(EdgeCutProblem *, const EdgeCut_Options *, QPDelta *);

} // end namespace Mongoose

#endif
