/**
 * @file Mongoose_ImproveQP.hpp
 * @brief Quadratic programming partition improvement via continuous relaxation
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QP improvement relaxes discrete partition to continuous [0,1] variables,
 * optimizes via gradient projection with balance constraints, then rounds
 * to discrete partition. Complements FM by exploring continuous solution
 * space; combined in waterdance for best results.
 *
 * @algorithm Quadratic Programming Partition Refinement:
 * Continuous relaxation approach for edge cut minimization:
 * 1. Relax discrete x_i ∈ {0,1} to continuous x_i ∈ [0,1]
 * 2. Formulate QP: min ½xᵀLx s.t. ∑w_i·x_i = W/2, 0≤x≤1
 * 3. Solve via gradient projection (projected gradient descent)
 * 4. Round continuous solution to discrete partition
 * 5. Use rounded solution to warm-start FM
 *
 * @math Graph Laplacian QP formulation:
 * $$\min_{x} \frac{1}{2} x^T L x = \frac{1}{4} \sum_{(i,j)\in E} w_{ij}(x_i - x_j)^2$$
 * where L = D - A is the graph Laplacian (D = degree matrix, A = adjacency).
 *
 * Balance constraint as equality: ∑ w_i·x_i = W·target_split
 * Box constraints: 0 ≤ x_i ≤ 1 (relaxation of binary)
 *
 * @complexity O(k·|E|) where k = gradient projection iterations.
 * Matrix-vector product Lx costs O(|E|).
 *
 * @ref Hager et al. (2018). "A graph partitioning algorithm based on
 *   continuous quadratic programming". SIAM J. Sci. Comput.
 *
 * @see Mongoose_QPGradProj.hpp for gradient projection solver
 * @see Mongoose_ImproveFM.hpp for discrete FM alternative
 */

/* ========================================================================== */
/* === Include/Mongoose_ImproveQP.hpp ======================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_IMPROVEQP_HPP
#define MONGOOSE_IMPROVEQP_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_QPDelta.hpp"
#include "Mongoose_QPGradProj.hpp"

namespace Mongoose
{

bool improveCutUsingQP(EdgeCutProblem *, const EdgeCut_Options *, bool isInitial = false);

} // end namespace Mongoose

#endif
