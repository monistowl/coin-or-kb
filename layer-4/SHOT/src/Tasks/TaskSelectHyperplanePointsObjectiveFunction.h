/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectHyperplanePointsObjectiveFunction.h
 * @brief Hyperplane selection for nonlinear objective
 *
 * Generates cuts for epigraph of nonlinear objective.
 *
 * **TaskSelectHyperplanePointsObjectiveFunction Class:**
 * - run(): Process objective at current solutions
 * - run(solPoints): Process specific solution points
 *
 * **Epigraph Linearization:**
 * - Nonlinear objective reformulated as: min t, f(x) <= t
 * - Generates cuts to approximate f(x) <= t constraint
 *
 * @algorithm Epigraph Objective Cut Generation
 * @math For nonlinear objective min f(x), SHOT uses epigraph reformulation:
 *       min t  s.t. f(x) ≤ t (treated as additional constraint)
 *       At solution x̄ with f(x̄) > t̄ (objective cut violated):
 *       - Use rootsearch to find boundary point x*
 *       - Generate cut: f(x*) + ∇f(x*)·(x - x*) ≤ t
 *       Improves objective bound approximation as MIP explores.
 * @see AuxiliaryVariables.h for epigraph variable
 * @see TaskSelectHyperplanePointsESH.h for constraint cuts
 */
#pragma once
#include "TaskBase.h"

#include "../Structs.h"

#include <vector>

namespace SHOT
{
class TaskSelectHyperplanePointsObjectiveFunction : public TaskBase
{
public:
    TaskSelectHyperplanePointsObjectiveFunction(EnvironmentPtr envPtr);
    ~TaskSelectHyperplanePointsObjectiveFunction() override;

    void run() override;
    virtual void run(std::vector<SolutionPoint> solPoints);
    std::string getType() override;
};
} // namespace SHOT