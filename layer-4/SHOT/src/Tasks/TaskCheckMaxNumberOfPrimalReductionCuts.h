/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckMaxNumberOfPrimalReductionCuts.h
 * @brief Limit number of objective cutoff updates
 *
 * Prevents excessive cutoff constraint modifications.
 *
 * **TaskCheckMaxNumberOfPrimalReductionCuts Class:**
 * - taskIDIfTrue: Jump target when limit reached
 * - run(): Check cutoff update count
 *
 * **Usage:**
 * - Limit objective bound updates per iteration
 * - Avoid MIP solver overhead from repeated bound changes
 *
 * @see TaskAddPrimalReductionCut.h for cutoff addition
 * @see Settings.h for limit configuration
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckMaxNumberOfPrimalReductionCuts : public TaskBase
{
public:
    TaskCheckMaxNumberOfPrimalReductionCuts(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckMaxNumberOfPrimalReductionCuts() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT