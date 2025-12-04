/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file a_quass.hpp
 * @brief HiGHS QUASS QP algorithm
 *
 * QUASS (QUadratic Active Set Solver) main algorithm.
 * Primal active set method for convex QP.
 *
 * @algorithm QUASS (Quadratic Active Set Solver):
 *   Solves convex QP: min ½x'Qx + c'x s.t. Ax ≤ b using active set method:
 *   1. Start with feasible point and initial active set (working set)
 *   2. Solve equality-constrained QP on current active set for direction p
 *   3. If p = 0: compute Lagrange multipliers λ
 *      - If all λ correct sign: optimal
 *      - Else: drop constraint with most negative λ, goto 2
 *   4. If p ≠ 0: ratio test to find step length α
 *      - If α = ∞: unbounded
 *      - Else: x ← x + α·p, add blocking constraint to active set, goto 2
 *
 * @math KKT system for active set A:
 *   [Q  A'] [p ]   [-g]
 *   [A  0 ] [λ ] = [0 ]
 *   where g = Qx + c is gradient. Solve via basis factorization.
 *
 * @complexity O(m·n²) per iteration for dense problems.
 *   Iteration count varies widely; finite for convex QP.
 *   Warm start from LP basis dramatically reduces iterations.
 *
 * @ref Goldfarb & Idnani (1983). "A numerically stable dual method for solving
 *      strictly convex quadratic programs". Math. Programming 27:1-33.
 *
 * @see Settings for algorithm parameters
 * @see Statistics for performance metrics
 */
#ifndef __SRC_LIB_QPSOLVER_QUASS_HPP__
#define __SRC_LIB_QPSOLVER_QUASS_HPP__

#include "Highs.h"
#include "qpsolver/a_asm.hpp"
#include "qpsolver/instance.hpp"
#include "qpsolver/qpconst.hpp"
#include "qpsolver/settings.hpp"

QpAsmStatus solveqp(Instance& instance, Settings& settings, Statistics& stats,
                    HighsModelStatus& highs_model_status,
                    HighsBasis& highs_basis, HighsSolution& highs_solution,
                    HighsTimer& timer);

#endif
