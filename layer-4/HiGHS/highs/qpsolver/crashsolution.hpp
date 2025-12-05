/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file crashsolution.hpp
 * @brief HiGHS QP crash solution
 *
 * Initial solution heuristic for QP solver.
 * Generates starting point for active set method.
 *
 * @algorithm Crash Start for QP Active Set
 * @math Identify free variables (no finite bounds) as potential basis.
 *       Free variables can be nonbasic at zero or basic at any value.
 *       Provides initial active set guess before main solve.
 * @complexity O(n) for variable classification.
 */
#ifndef __SRC_LIB_CRASHSOLUTION_HPP__
#define __SRC_LIB_CRASHSOLUTION_HPP__

#include <cstdlib>

#include "runtime.hpp"

inline bool isfreevar(Instance& instance, HighsInt idx) {
  return instance.var_lo[idx] == -std::numeric_limits<double>::infinity() &&
         instance.var_up[idx] == std::numeric_limits<double>::infinity();
}

#endif
