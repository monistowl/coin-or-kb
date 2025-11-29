/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckIterationError.h
 * @brief Detect errors during iteration
 *
 * Handles solver failures and numerical issues.
 *
 * **TaskCheckIterationError Class:**
 * - taskIDIfTrue: Jump target when error detected
 * - run(): Check for MIP solver errors, infeasibility, etc.
 *
 * **Error Types:**
 * - MIP solver failure or timeout
 * - Numerical issues in cut generation
 * - Unexpected infeasibility
 *
 * @see TaskTerminate.h for error termination
 * @see DualSolver.h for MIP solve status
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckIterationError : public TaskBase
{
public:
    TaskCheckIterationError(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckIterationError() override;

    void run() override;

    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT