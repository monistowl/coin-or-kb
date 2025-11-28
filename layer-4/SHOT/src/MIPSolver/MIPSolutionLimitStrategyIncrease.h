/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/MIPSolutionLimitStrategyIncrease.h
 * @brief Solution limit strategy with gradual increase
 *
 * Increases MIP solution pool limit over iterations.
 *
 * **MIPSolutionLimitStrategyIncrease Class:**
 * - updateLimit(): Increase limit when MIP finds optimal
 * - getNewLimit()/getInitialLimit(): Current and start values
 *
 * **State Tracking:**
 * - lastIterSolLimIncreased: When limit was last raised
 * - numSolLimIncremented: Total increases performed
 * - lastIterOptimal: Last iteration with optimal MIP
 *
 * **Algorithm:**
 * - Start with low limit for fast initial iterations
 * - Increase when solver proves optimality
 * - More solutions = more hyperplane generation points
 *
 * @see IMIPSolutionLimitStrategy.h for interface
 */
#pragma once

#include "IMIPSolutionLimitStrategy.h"
#include "Environment.h"

namespace SHOT
{
class MIPSolutionLimitStrategyIncrease : public IMIPSolutionLimitStrategy
{
public:
    MIPSolutionLimitStrategyIncrease(EnvironmentPtr envPtr);
    ~MIPSolutionLimitStrategyIncrease() override = default;

    bool updateLimit() override;
    int getNewLimit() override;
    int getInitialLimit() override;

    int lastIterSolLimIncreased;
    int numSolLimIncremented;
    int lastIterOptimal;
};
} // namespace SHOT