/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file presolve/ICrashX.h
 * @brief Crossover from interior point to basic solution
 *
 * Provides simplex crossover after IPM solve to obtain vertex solution.
 *
 * **callCrossover():**
 * Converts interior point solution to basic feasible solution:
 * - Input: IPM solution (may be interior to polytope)
 * - Output: Basis + vertex solution for post-processing
 *
 * **Why Crossover:**
 * - IPM returns interior solutions, not vertices
 * - Basic solutions needed for warm-starting, sensitivity analysis
 * - Crossover pushes solution to vertex via simplex pivots
 *
 * **Process:**
 * 1. Identify near-bound variables
 * 2. Construct initial basis from binding constraints
 * 3. Run simplex cleanup to reach vertex
 *
 * @algorithm IPM-to-Simplex Crossover:
 *   Convert interior point solution to basic feasible solution:
 *   @math Given interior x*: identify active set A(x*) = {i : |g_i(x*)| < ε}
 *         Construct basis B from nearly-active constraints
 *         Simplex pivots: move to vertex while maintaining feasibility
 *   Three phases: (1) identify near-bound vars, (2) build initial basis,
 *   (3) run primal/dual simplex to optimal vertex.
 *   @complexity O(m²) typical, O(m³) worst case for crossover
 *   @ref Andersen, E. and Ye, Y. (1999). "A computational study of the
 *        homogeneous algorithm for large-scale convex optimization".
 *        Computational Optimization and Applications 10:243-269.
 *
 * @see ipm/IpxWrapper.h for IPM solver calling crossover
 * @see simplex/HEkk.h for simplex cleanup phase
 */
#ifndef PRESOLVE_ICRASHX_H_
#define PRESOLVE_ICRASHX_H_

#include <iostream>

#include "HConfig.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsSolution.h"

HighsStatus callCrossover(const HighsOptions& options, const HighsLp& lp,
                          HighsBasis& highs_basis,
                          HighsSolution& highs_solution,
                          HighsModelStatus& model_status, HighsInfo& highs_info,
                          HighsCallback& highs_callback);

#endif
