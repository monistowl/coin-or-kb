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
 * @algorithm Gradient Projection for Bound-Constrained QP:
 * Projected gradient descent with active set management:
 * 1. Compute gradient: g = Lx (graph Laplacian times current x)
 * 2. Identify active constraints (x_i = 0 or x_i = 1)
 * 3. Project gradient onto feasible region (box + balance)
 * 4. Line search along projected direction
 * 5. Update x, repeat until ||projected_grad|| < tolerance
 *
 * @math Gradient projection iteration:
 * $$x_{k+1} = P_C(x_k - \alpha_k \nabla f(x_k))$$
 * where P_C projects onto feasible set C = {x : 0≤x≤1, lo≤a'x≤hi}.
 *
 * Balance constraint projection uses continuous knapsack solver.
 *
 * @complexity O(|E|) per iteration for gradient Lx.
 * Typically O(10-100) iterations for convergence.
 *
 * @ref Hager & Zhang (2006). "Algorithm 851: CG_DESCENT, a conjugate
 *   gradient method with guaranteed descent". ACM TOMS 32(1):113-137.
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
