/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckDualStagnation.h
 * @brief Detect stalled dual bound improvement
 *
 * Triggers countermeasures when dual bound stops improving.
 *
 * **TaskCheckDualStagnation Class:**
 * - taskIDIfTrue: Jump target when stagnation detected
 * - run(): Check if dual bound unchanged for N iterations
 *
 * **Stagnation Recovery:**
 * - May trigger stronger cuts or reformulation
 * - Indicates outer approximation isn't tightening
 *
 * @see TaskCheckPrimalStagnation.h for primal stagnation
 * @see DualSolver.h for dual bound computation
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckDualStagnation : public TaskBase
{
public:
    TaskCheckDualStagnation(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckDualStagnation() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT