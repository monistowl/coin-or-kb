/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskGoto.h
 * @brief Jump to labeled task in workflow
 *
 * Enables non-linear control flow in task sequences.
 *
 * **TaskGoto Class:**
 * - gotoTaskID: Target task identifier
 * - run(): Signal TaskHandler to jump to target
 *
 * **Usage in SHOT:**
 * - Loop back to iteration start
 * - Jump to termination on error
 *
 * @see TaskHandler.h for jump resolution
 * @see TaskTerminate.h for exit handling
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskGoto : public TaskBase
{
public:
    TaskGoto(EnvironmentPtr envPtr, std::string taskID);
    ~TaskGoto() override;

    void run() override;
    std::string getType() override;

private:
    std::string gotoTaskID;
};
} // namespace SHOT