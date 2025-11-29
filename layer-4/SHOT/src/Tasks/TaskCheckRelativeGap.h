/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckRelativeGap.h
 * @brief Termination check for relative optimality gap
 *
 * Terminates when |primal - dual| / |primal| < tolerance.
 *
 * **TaskCheckRelativeGap Class:**
 * - taskIDIfTrue: Jump target when gap closed
 * - run(): Check (|bestPrimal - bestDual| / max(1, |bestPrimal|)) < RelativeGapTol
 *
 * **Usage:**
 * - More common than absolute gap for practical problems
 * - Scales with solution magnitude
 *
 * @see TaskCheckAbsoluteGap.h for absolute gap check
 * @see Results.h for bound storage
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckRelativeGap : public TaskBase
{
public:
    TaskCheckRelativeGap(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckRelativeGap() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT