/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskExecuteSolutionLimitStrategy.h
 * @brief Control MIP solution pool size dynamically
 *
 * Adjusts how many MIP solutions are collected per iteration.
 *
 * **TaskExecuteSolutionLimitStrategy Class:**
 * - solutionLimitStrategy: Strategy implementation
 * - previousSolLimit: Track limit changes
 * - run(): Apply current solution limit
 *
 * **Strategy Control:**
 * - Start with small limit for fast iterations
 * - Increase when MIP optimal to explore pool
 * - Balance speed vs solution diversity
 *
 * @see IMIPSolutionLimitStrategy.h for strategy interface
 * @see MIPSolutionLimitStrategyIncrease.h for default strategy
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class IMIPSolutionLimitStrategy;

class TaskExecuteSolutionLimitStrategy : public TaskBase
{
public:
    TaskExecuteSolutionLimitStrategy(EnvironmentPtr envPtr);
    ~TaskExecuteSolutionLimitStrategy() override;

    void run() override;
    std::string getType() override;

private:
    std::unique_ptr<IMIPSolutionLimitStrategy> solutionLimitStrategy;

    bool isInitialized;
    bool temporaryOptLimitUsed;
    int previousSolLimit;
};
} // namespace SHOT