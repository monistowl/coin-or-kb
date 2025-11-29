/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckTimeLimit.h
 * @brief Termination check for wall-clock time limit
 *
 * Part of termination check sequence.
 *
 * **TaskCheckTimeLimit Class:**
 * - taskIDIfTrue: Jump target when limit exceeded
 * - run(): Compare elapsed vs Settings.TimeLimit
 *
 * **Behavior:**
 * - If exceeded: Jump to termination task
 * - If not: Continue to next task
 *
 * @see Timer.h for elapsed time tracking
 * @see TaskTerminate.h for termination handling
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckTimeLimit : public TaskBase
{
public:
    TaskCheckTimeLimit(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckTimeLimit() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT