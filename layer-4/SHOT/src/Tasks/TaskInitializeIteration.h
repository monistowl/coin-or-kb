/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskInitializeIteration.h
 * @brief Per-iteration setup and housekeeping
 *
 * Prepares state for new iteration cycle.
 *
 * **TaskInitializeIteration Class:**
 * - run(): Reset iteration-local state
 *
 * **Initialization Steps:**
 * - Increment iteration counter
 * - Clear iteration-specific storage
 * - Update timing information
 *
 * @see TaskPrintIterationReport.h for iteration summary
 * @see Timing.h for time tracking
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskInitializeIteration : public TaskBase
{
public:
    TaskInitializeIteration(EnvironmentPtr envPtr);
    ~TaskInitializeIteration() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT