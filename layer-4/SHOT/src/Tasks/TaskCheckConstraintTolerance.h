/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckConstraintTolerance.h
 * @brief Termination check for constraint feasibility
 *
 * Verifies primal solution satisfies all constraints.
 *
 * **TaskCheckConstraintTolerance Class:**
 * - taskIDIfTrue: Jump target when feasible
 * - run(): Check max constraint violation < ConstraintTolerance
 *
 * **Usage:**
 * - Validates feasibility of best primal solution
 * - Required for declaring optimality
 *
 * @see Results.h for constraint violation tracking
 * @see TaskCheckAbsoluteGap.h for gap check
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckConstraintTolerance : public TaskBase
{
public:
    TaskCheckConstraintTolerance(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckConstraintTolerance() override;

    void run() override;

    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT