/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectHyperplanePointsESH.h
 * @brief Extended Supporting Hyperplane point selection
 *
 * Core ESH algorithm: finds boundary points for hyperplane generation.
 *
 * **TaskSelectHyperplanePointsESH Class:**
 * - run(): Process current MIP solutions
 * - run(solPoints): Process specific solution points
 *
 * **ESH Algorithm:**
 * 1. Take infeasible MIP solution point
 * 2. Use rootsearch to find boundary with feasible region
 * 3. Generate supporting hyperplane at boundary
 *
 * **Extends ECP:**
 * - ESH uses interior point + rootsearch
 * - ECP generates cuts at infeasible point directly
 *
 * @algorithm Extended Supporting Hyperplane (ESH)
 * @math Given infeasible x̂ and interior x°, find boundary point x* via:
 *       x* = argmin_{0≤λ≤1} {λ : g(λx° + (1-λ)x̂) ≤ 0}
 *       Generate cut: ∇g(x*)·(x - x*) ≤ 0 (supporting hyperplane)
 *       Tighter than ECP cuts generated at x̂.
 * @complexity O(rootsearch iterations × gradient eval) per cut.
 * @ref Kronqvist et al. (2016). "The extended supporting hyperplane algorithm
 *      for convex mixed-integer nonlinear programming". J. Global Optim.
 * @see RootsearchMethod/ for boundary finding
 * @see TaskAddHyperplanes.h for cut addition
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{

class Constraint;
class TaskSelectHyperplanePointsECP;

class TaskSelectHyperplanePointsESH : public TaskBase
{
public:
    TaskSelectHyperplanePointsESH(EnvironmentPtr envPtr);
    ~TaskSelectHyperplanePointsESH() override;

    void run() override;
    virtual void run(std::vector<SolutionPoint> solPoints);

    std::string getType() override;

private:
    std::unique_ptr<TaskSelectHyperplanePointsECP> tSelectHPPts;
    std::vector<Constraint*> nonlinearConstraints;
};
} // namespace SHOT