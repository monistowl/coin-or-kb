/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskUpdateInteriorPoint.h
 * @brief Update interior point during optimization
 *
 * Improves ESH quality by updating interior point.
 *
 * **TaskUpdateInteriorPoint Class:**
 * - run(): Recompute or update interior point
 *
 * **Update Strategy:**
 * - Use new primal solutions as interior candidates
 * - Average with existing interior point
 * - Improves cut quality as algorithm progresses
 *
 * @algorithm Dynamic Interior Point Update for ESH
 * @math ESH requires interior point x° in convex feasible region.
 *       As algorithm progresses, update x° for better cuts:
 *       - New primal solution x̄ feasible → candidate for x°
 *       - Convex combination: x°_new = α·x°_old + (1-α)·x̄
 *       Better interior point → tighter hyperplane cuts.
 *       Particularly valuable when initial x° was near boundary.
 * @see TaskFindInteriorPoint.h for initial computation
 * @see TaskSelectHyperplanePointsESH.h for usage
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskUpdateInteriorPoint : public TaskBase
{
public:
    TaskUpdateInteriorPoint(EnvironmentPtr envPtr);
    ~TaskUpdateInteriorPoint() override;
    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT