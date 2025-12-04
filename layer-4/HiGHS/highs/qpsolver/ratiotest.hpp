/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file ratiotest.hpp
 * @brief HiGHS QP ratio test for step length determination
 *
 * Ratio test for QP active set step length.
 * Determines how far to move before hitting a constraint.
 *
 * @algorithm Ratio Test for QP Active Set Method:
 *   Computes maximum step α along direction p without violating constraints:
 *   1. For each inactive constraint i with a_i·p > 0 (moving toward bound):
 *      α_i = (b_i - a_i·x) / (a_i·p) = slack_i / rowmove_i
 *   2. Select α* = min_i { α_i : α_i > 0 } and record limiting constraint
 *   3. Track whether hitting lower or upper bound (nowactiveatlower)
 *   4. Special handling for starting step (alphastart parameter)
 *
 * @math Step length computation:
 *   Current: a_i·x ≤ b_i with slack s_i = b_i - a_i·x ≥ 0
 *   After step: a_i·(x + α·p) = a_i·x + α·(a_i·p)
 *   Constraint active when: α·(a_i·p) = s_i → α = s_i / (a_i·p)
 *
 * @complexity O(m) to check all constraints.
 *
 * @see RatiotestResult for return structure (alpha, constraint, bound type)
 */
#ifndef __SRC_LIB_RATIOTEST_HPP__
#define __SRC_LIB_RATIOTEST_HPP__

#include <limits>

#include "runtime.hpp"

struct RatiotestResult {
  double alpha;
  HighsInt limitingconstraint;
  bool nowactiveatlower;
};

RatiotestResult ratiotest(Runtime& runtime, const QpVector& p,
                          const QpVector& rowmove, double alphastart);

Instance ratiotest_relax_instance(Runtime& runtime);

#endif
