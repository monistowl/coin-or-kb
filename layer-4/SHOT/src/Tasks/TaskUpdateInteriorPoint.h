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