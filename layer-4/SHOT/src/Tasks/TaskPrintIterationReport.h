/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskPrintIterationReport.h
 * @brief Output iteration progress to console
 *
 * Formatted progress line for each iteration.
 *
 * **TaskPrintIterationReport Class:**
 * - lastNumHyperplane: Track hyperplanes added
 * - run(): Format and print iteration status
 *
 * **Report Contents:**
 * - Iteration number, elapsed time
 * - Primal bound, dual bound, gap
 * - Number of hyperplanes added
 *
 * @see Report.h for output formatting
 * @see Results.h for bound information
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskPrintIterationReport : public TaskBase
{
public:
    TaskPrintIterationReport(EnvironmentPtr envPtr);
    ~TaskPrintIterationReport() override;

    void run() override;
    std::string getType() override;

private:
    int lastNumHyperplane;
};
} // namespace SHOT