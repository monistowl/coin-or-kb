/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCreateDualProblem.h
 * @brief Build MIP relaxation from reformulated problem
 *
 * Translates SHOT's problem representation to MIP solver format.
 *
 * **TaskCreateDualProblem Class:**
 * - run(): Create initial MIP in DualSolver
 * - createProblem(): Transfer variables, constraints, objective
 *
 * **MIP Construction:**
 * - Linear constraints: Added directly
 * - Quadratic constraints: Added if solver supports MIQCQP
 * - Nonlinear constraints: Omitted (handled via hyperplanes)
 * - Integer variables: Marked as such in MIP
 *
 * @see DualSolver.h for MIP solver interface
 * @see Problem.h for source representation
 */
#pragma once
#include "TaskBase.h"

#include "../MIPSolver/IMIPSolver.h"
#include "../Model/Problem.h"

namespace SHOT
{

class TaskCreateDualProblem : public TaskBase
{
public:
    TaskCreateDualProblem(EnvironmentPtr envPtr);
    ~TaskCreateDualProblem() override;

    void run() override;
    std::string getType() override;

private:
    bool createProblem(MIPSolverPtr destinationProblem, ProblemPtr sourceProblem);
};
} // namespace SHOT