/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskPresolve.h
 * @brief Initial problem simplification
 *
 * Applies presolve techniques before main algorithm.
 *
 * **TaskPresolve Class:**
 * - isPresolved: Track if presolve completed
 * - run(): Apply presolve routines
 *
 * **Presolve Techniques:**
 * - Bound propagation
 * - Fixed variable removal
 * - Redundant constraint detection
 * - Expression simplification
 *
 * @algorithm MINLP Presolve
 * @math Apply bound propagation: infer l'_j ≥ l_j, u'_j ≤ u_j from constraints.
 *       Remove fixed variables (l_j = u_j), detect infeasibility/redundancy.
 *       Simplify nonlinear expressions via constant folding.
 * @complexity O(constraints × passes). Typically few passes needed.
 * @see TaskReformulateProblem.h for reformulation
 * @see Simplifications.h for expression simplification
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskPresolve : public TaskBase
{
public:
    TaskPresolve(EnvironmentPtr envPtr);
    ~TaskPresolve() override;

    void run() override;
    std::string getType() override;

private:
    bool isPresolved;
};
} // namespace SHOT