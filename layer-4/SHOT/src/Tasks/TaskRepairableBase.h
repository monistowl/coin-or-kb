/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskRepairableBase.h
 * @brief Base class for tasks that can repair failures
 *
 * Extension point for failure recovery logic.
 *
 * **TaskRepairableBase Class:**
 * - repair(): Attempt to fix failed task
 *
 * **Usage:**
 * - Subclassed by tasks that can recover from errors
 * - Called when initial run() fails
 *
 * @see TaskRepairInfeasibleDualProblem.h for example
 */
#include "TaskBase.h"

namespace SHOT
{
class TaskRepairableBase : public TaskBase
{
public:
    ~TaskRepairableBase() override;

    virtual void repair();
    std::string getType() override;

private:
};
} // namespace SHOT