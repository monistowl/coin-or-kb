/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSolveIteration.h
 * @brief Solve MIP relaxation for current iteration
 *
 * Core MIP solve step in outer approximation loop.
 *
 * **TaskSolveIteration Class:**
 * - run(): Call DualSolver to solve MIP with current cuts
 *
 * **Iteration Flow:**
 * 1. MIP has linear approximation of nonlinear constraints
 * 2. Solve gives candidate solution + dual bound
 * 3. Candidate checked for feasibility
 * 4. New cuts generated at infeasible points
 *
 * @see DualSolver.h for MIP solve call
 * @see TaskSelectHyperplanePointsESH.h for cut generation
 */
#pragma once
#include "TaskBase.h"

#include "../Structs.h"

namespace SHOT
{
class TaskSolveIteration : public TaskBase
{
public:
    TaskSolveIteration(EnvironmentPtr envPtr);
    ~TaskSolveIteration() override;

    void run() override;
    std::string getType() override;

private:
    VectorString variableNames;
};
} // namespace SHOT