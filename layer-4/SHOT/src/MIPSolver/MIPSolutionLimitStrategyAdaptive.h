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