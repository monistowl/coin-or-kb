/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file SolutionStrategy/SolutionStrategyNLP.h
 * @brief Direct NLP solver for continuous problems
 *
 * Bypasses ESH for purely continuous NLP problems.
 *
 * **SolutionStrategyNLP Class:**
 * - initializeStrategy(): Configure for direct NLP solve
 * - solveProblem(): Single NLP solver call (Ipopt)
 *
 * **Use Case:**
 * - Problems with no integer variables
 * - Convex NLP where outer approximation is unnecessary
 * - Falls back to standard NLP solvers (Ipopt)
 *
 * **When Selected:**
 * - Problem type is NLP (no discrete variables)
 * - Simpler than ESH for continuous problems
 *
 * @algorithm Direct interior point NLP solve
 * @see NLPSolver/NLPSolverIpoptBase.h for Ipopt wrapper
 */
#pragma once

#include "ISolutionStrategy.h"
#include "../Environment.h"

namespace SHOT
{
class SolutionStrategyNLP : public ISolutionStrategy
{
public:
    SolutionStrategyNLP(EnvironmentPtr envPtr);
    virtual ~SolutionStrategyNLP();

    bool solveProblem() override;
    void initializeStrategy() override;

protected:
};
} // namespace SHOT