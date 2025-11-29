/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectHyperplanePointsECP.h
 * @brief Extended Cutting Plane point selection
 *
 * Classic outer approximation: linearize at infeasible points.
 *
 * **TaskSelectHyperplanePointsECP Class:**
 * - run(): Process current MIP solutions
 * - run(solPoints): Process specific solution points
 *
 * **ECP Algorithm:**
 * - Generate gradient cut at infeasible solution
 * - Simpler than ESH but may converge slower
 * - Used as fallback when ESH rootsearch fails
 *
 * @algorithm Extended Cutting Plane (Westerlund-Pettersson)
 * @see TaskSelectHyperplanePointsESH.h for ESH variant
 * @see TaskAddHyperplanes.h for cut addition
 */
#pragma once
#include "TaskBase.h"

#include "../Structs.h"

namespace SHOT
{
class TaskSelectHyperplanePointsECP : public TaskBase
{
public:
    TaskSelectHyperplanePointsECP(EnvironmentPtr envPtr);
    ~TaskSelectHyperplanePointsECP() override;

    void run() override;
    virtual void run(std::vector<SolutionPoint> solPoints);

    std::string getType() override;

private:
};
} // namespace SHOT