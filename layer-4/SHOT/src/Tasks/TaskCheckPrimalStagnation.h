/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckPrimalStagnation.h
 * @brief Detect stalled primal bound improvement
 *
 * Triggers NLP solves when primal bound stops improving.
 *
 * **TaskCheckPrimalStagnation Class:**
 * - taskIDIfTrue/False: Branch targets for stagnation state
 * - run(): Check if primal bound unchanged for N iterations
 *
 * **Stagnation Recovery:**
 * - May trigger fixed-integer NLP to find better solutions
 * - Indicates MIP solutions aren't improving primal
 *
 * @see TaskCheckDualStagnation.h for dual stagnation
 * @see PrimalSolver.h for primal bound computation
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckPrimalStagnation : public TaskBase
{
public:
    TaskCheckPrimalStagnation(EnvironmentPtr envPtr, std::string taskIDTrue, std::string taskIDFalse);
    ~TaskCheckPrimalStagnation() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
    std::string taskIDIfFalse;
};
} // namespace SHOT