/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/IMIPSolutionLimitStrategy.h
 * @brief Interface for MIP solution pool limit strategies
 *
 * Controls how many solutions MIP solver collects per iteration.
 *
 * **IMIPSolutionLimitStrategy Interface:**
 * - updateLimit(): Adjust limit based on progress
 * - getNewLimit(): Current solution limit value
 * - getInitialLimit(): Starting limit
 *
 * **Implementations:**
 * - MIPSolutionLimitStrategyIncrease: Grow limit over time
 * - MIPSolutionLimitStrategyUnlimited: No limit
 * - MIPSolutionLimitStrategyAdaptive: Adjust based on gap
 *
 * **Purpose:**
 * - Balance cut generation vs solver time per iteration
 * - More solutions = more hyperplane generation points
 * - Fewer solutions = faster MIP solves
 *
 * @see TaskExecuteSolutionLimitStrategy for strategy execution
 */
#pragma once
#include "../Environment.h"

namespace SHOT
{
class IMIPSolutionLimitStrategy
{
public:
    virtual ~IMIPSolutionLimitStrategy() = default;

    virtual bool updateLimit() = 0;

    virtual int getNewLimit() = 0;

    virtual int getInitialLimit() = 0;

    EnvironmentPtr env;

protected:
};
} // namespace SHOT