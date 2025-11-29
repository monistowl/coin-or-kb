/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskPerformBoundTightening.h
 * @brief Tighten variable bounds via optimization
 *
 * Uses optimization-based bound tightening (OBBT).
 *
 * **TaskPerformBoundTightening Class:**
 * - POASolver: Polyhedral outer approximation solver
 * - createPOA(): Build relaxed problem for bound tightening
 *
 * **OBBT Algorithm:**
 * - For each variable: min/max subject to relaxation
 * - Tightens bounds beyond constraint propagation
 * - Improves relaxation quality
 *
 * @algorithm Optimization-Based Bound Tightening
 * @see NLPSolverSHOT.h for POA solver
 * @see Problem.h for bound storage
 */
#pragma once
#include "TaskBase.h"

#include <memory>
#include <string>
#include <vector>

#include "../Structs.h"

namespace SHOT
{
class NLPSolverSHOT;

class TaskPerformBoundTightening : public TaskBase
{
public:
    TaskPerformBoundTightening(EnvironmentPtr envPtr, ProblemPtr source);
    ~TaskPerformBoundTightening() override;
    void run() override;
    std::string getType() override;

    std::shared_ptr<NLPSolverSHOT> POASolver;

private:
    virtual void createPOA();

    std::shared_ptr<TaskBase> taskSelectHPPts;

    ProblemPtr sourceProblem;
    ProblemPtr relaxedProblem;
};
} // namespace SHOT