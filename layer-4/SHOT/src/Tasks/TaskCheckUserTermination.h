/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckUserTermination.h
 * @brief Check for external termination request
 *
 * Allows user to interrupt solver gracefully.
 *
 * **TaskCheckUserTermination Class:**
 * - taskIDIfTrue: Jump target when user requests stop
 * - run(): Check for CTRL+C, callback termination, etc.
 *
 * **Usage:**
 * - Called every iteration to check for interrupts
 * - Returns best solution found so far
 *
 * @see EventHandler.h for termination callbacks
 * @see TaskTerminate.h for graceful shutdown
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckUserTermination : public TaskBase
{
public:
    TaskCheckUserTermination(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckUserTermination() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT