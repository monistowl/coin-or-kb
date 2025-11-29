/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskTerminate.h
 * @brief Signals end of optimization algorithm
 *
 * Final task that stops the main loop.
 *
 * **TaskTerminate Class:**
 * - run(): Set termination flag in TaskHandler
 *
 * **Called When:**
 * - Optimal solution found (gap closed)
 * - Resource limit exceeded (time, iteration)
 * - Infeasibility proven
 *
 * @see TaskGoto.h for jump to termination
 * @see TaskHandler.h for loop control
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskTerminate : public TaskBase
{
public:
    TaskTerminate(EnvironmentPtr envPtr);
    ~TaskTerminate() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT