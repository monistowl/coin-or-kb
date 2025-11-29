/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckIterationLimit.h
 * @brief Termination check for iteration count limit
 *
 * Part of termination check sequence.
 *
 * **TaskCheckIterationLimit Class:**
 * - taskIDIfTrue: Jump target when limit reached
 * - run(): Compare iteration count vs Settings.IterationLimit
 *
 * **Behavior:**
 * - If exceeded: Jump to termination task
 * - If not: Continue to next task
 *
 * @see TaskCheckTimeLimit.h for time-based termination
 * @see TaskTerminate.h for termination handling
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckIterationLimit : public TaskBase
{
public:
    TaskCheckIterationLimit(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckIterationLimit() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT