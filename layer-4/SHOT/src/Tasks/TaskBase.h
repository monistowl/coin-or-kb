/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskBase.h
 * @brief Base class for modular algorithm tasks
 *
 * Foundation for task-based algorithm composition.
 *
 * **TaskBase Class:**
 * - isActive(), activate(), deactivate(): Enable/disable tasks
 * - initialize(): Setup before first run
 * - run(): Execute the task logic
 * - getType(): Task identifier for debugging
 *
 * **Task Categories:**
 * - Termination: TimeLimit, IterationLimit, Gap checks
 * - Hyperplane: SelectHyperplanePointsESH/ECP, AddHyperplanes
 * - Primal: SelectPrimalCandidates, NLP solving
 * - Dual: SolveIteration, CreateDualProblem
 * - Control: Sequential, Conditional, Goto
 *
 * **Task Composition:**
 * - TaskSequential: Run tasks in order
 * - TaskConditional: Branch on conditions
 * - TaskGoto: Jump to labeled task
 *
 * @see TaskHandler.h for task scheduling
 * @see SolutionStrategy/ for task workflow definition
 */
#pragma once

#include "../Environment.h"

#include <string>

namespace SHOT
{

class TaskBase
{
public:
    virtual bool isActive();
    virtual void activate();
    virtual void deactivate();

    virtual void initialize();

    virtual std::string getType();

    virtual void run();

    TaskBase(EnvironmentPtr envPtr);
    virtual ~TaskBase() = default;

protected:
    EnvironmentPtr env;

private:
    bool m_isActive;
};

using TaskPtr =std::shared_ptr<TaskBase> ;

} // namespace SHOT