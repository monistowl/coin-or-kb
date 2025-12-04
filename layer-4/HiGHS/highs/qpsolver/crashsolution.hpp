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
