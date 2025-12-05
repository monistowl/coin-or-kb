/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/MIPSolutionLimitStrategyAdaptive.h
 * @brief Adaptive solution limit based on solver progress
 *
 * Adjusts limit based on optimization state.
 *
 * **MIPSolutionLimitStrategyAdaptive Class:**
 * - lastIterSolLimIncreased: Track when limit changed
 * - numSolLimIncremented: Count of increases
 *
 * **Adaptive Logic:**
 * - Increase when finding good solutions
 * - Decrease when solver is struggling
 * - Balances exploration vs speed
 *
 * @algorithm Adaptive MIP Solution Limit Control
 * @math Adjust solution limit L_k dynamically:
 *       - If finding good solutions (gap improving): L_{k+1} = L_k + δ
 *       - If stagnating (gap unchanged): L_{k+1} = max(L_min, L_k - δ)
 *       Balances cut generation speed vs MIP solver exploration.
 * @complexity O(1) per limit update. Heuristic based on solver feedback.
 * @see IMIPSolutionLimitStrategy.h for interface
 * @see MIPSolutionLimitStrategyIncrease.h for simpler strategy
 */
#pragma once

#include "IMIPSolutionLimitStrategy.h"
#include "Environment.h"

namespace SHOT
{
class MIPSolutionLimitStrategyAdaptive : public IMIPSolutionLimitStrategy
{
public:
    MIPSolutionLimitStrategyAdaptive(EnvironmentPtr envPtr);
    ~MIPSolutionLimitStrategyAdaptive() override = default;

    bool updateLimit() override;
    int getNewLimit() override;
    int getInitialLimit() override;

    int lastIterSolLimIncreased;
    int numSolLimIncremented;
};
} // namespace SHOT