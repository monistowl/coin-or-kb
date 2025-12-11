/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskCheckAbsoluteGap.h
 * @brief Termination check for absolute optimality gap
 *
 * Terminates when |primal - dual| < tolerance.
 *
 * **TaskCheckAbsoluteGap Class:**
 * - taskIDIfTrue: Jump target when gap closed
 * - run(): Check |bestPrimal - bestDual| < AbsoluteGapTol
 *
 * **Optimality Gap:**
 * - Primal bound: Best feasible solution value
 * - Dual bound: Relaxation optimal value
 * - Gap closed = provably optimal
 *
 * @algorithm Absolute Optimality Gap Termination Criterion
 * @math For minimization, let z̄ = primal bound, z̲ = dual bound:
 *       - Absolute gap: |z̄ - z̲|
 *       - Terminate when |z̄ - z̲| ≤ ε_abs
 *       - Proves solution within ε_abs of optimal
 *       Dual bound from MIP relaxation, primal from feasible solutions.
 *       Complements relative gap check for problems near zero optimal.
 * @see TaskCheckRelativeGap.h for relative gap check
 * @see Results.h for bound storage
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskCheckAbsoluteGap : public TaskBase
{
public:
    TaskCheckAbsoluteGap(EnvironmentPtr envPtr, std::string taskIDTrue);
    ~TaskCheckAbsoluteGap() override;

    void run() override;

    std::string getType() override;

private:
    std::string taskIDIfTrue;
};
} // namespace SHOT