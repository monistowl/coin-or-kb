/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskExecuteRelaxationStrategy.h
 * @brief Execute LP/MIP relaxation strategy step
 *
 * Controls transition from LP to MIP solving.
 *
 * **TaskExecuteRelaxationStrategy Class:**
 * - run(): Invoke current relaxation strategy
 *
 * **Strategy Control:**
 * - Calls IRelaxationStrategy to decide LP vs MIP
 * - May enable/disable integer constraints
 * - Affects DualSolver solve behavior
 *
 * @see IRelaxationStrategy.h for strategy interface
 * @see RelaxationStrategyStandard.h for default strategy
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskExecuteRelaxationStrategy : public TaskBase
{
public:
    TaskExecuteRelaxationStrategy(EnvironmentPtr envPtr);
    ~TaskExecuteRelaxationStrategy() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT