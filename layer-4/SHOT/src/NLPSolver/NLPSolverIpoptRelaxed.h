/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file NLPSolver/NLPSolverIpoptRelaxed.h
 * @brief Ipopt solver for continuous relaxation problems
 *
 * Solves NLP with integer variables relaxed to continuous.
 *
 * **NLPSolverIpoptRelaxed Class:**
 * - Multiple inheritance: NLPSolverBase + NLPSolverIpoptBase
 * - setSolverSpecificInitialSettings(): Configure for relaxed solve
 * - getSolution(): Return continuous solution values
 *
 * **Use Case:**
 * - Find interior points for ESH algorithm
 * - Check feasibility of relaxed problem
 * - Generate starting points for primal heuristics
 *
 * @see NLPSolverIpoptBase.h for fixed-integer variant
 */
#pragma once
#include "NLPSolverIpoptBase.h"

namespace SHOT
{
class NLPSolverIpoptRelaxed : public NLPSolverBase, public NLPSolverIpoptBase
{
public:
    NLPSolverIpoptRelaxed(EnvironmentPtr envPtr, ProblemPtr source);
    ~NLPSolverIpoptRelaxed() override = default;

    VectorDouble getSolution() override;

protected:
    void setSolverSpecificInitialSettings() override;

private:
};
} // namespace SHOT