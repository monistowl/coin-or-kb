/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCalculateSolutionChangeNorm.h
 * @brief Compute solution movement between iterations
 *
 * Tracks convergence via solution change magnitude.
 *
 * **TaskCalculateSolutionChangeNorm Class:**
 * - run(): Compute ||x_new - x_old|| norm
 *
 * **Usage:**
 * - Detect solution stagnation
 * - Used in convergence criteria
 * - May trigger algorithm strategy changes
 *
 * @see Utilities.h for L2Norm computation
 * @see TaskCheckDualStagnation.h for stagnation handling
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCalculateSolutionChangeNorm : public TaskBase
{
public:
    TaskCalculateSolutionChangeNorm(EnvironmentPtr envPtr);
    ~TaskCalculateSolutionChangeNorm() override;

    void run() override;

    std::string getType() override;

private:
};
} // namespace SHOT