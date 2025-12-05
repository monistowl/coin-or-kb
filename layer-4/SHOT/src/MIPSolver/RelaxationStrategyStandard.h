/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/RelaxationStrategyStandard.h
 * @brief Standard LP-to-MIP relaxation strategy
 *
 * Implements the default relaxation phase behavior.
 *
 * **RelaxationStrategyStandard Class:**
 * - executeStrategy(): Decide LP vs MIP solve
 * - setActive()/setInactive(): Control strategy state
 * - setInitial(): Reset for new problem
 *
 * **LP Phase Termination:**
 * - isIterationLimitReached(): Max LP iterations
 * - isTimeLimitReached(): LP time budget
 * - isLPStepFinished(): Convergence detection
 * - isObjectiveStagnant(): No bound improvement
 *
 * **Algorithm:**
 * - Initial iterations solve LP for fast hyperplanes
 * - Switch to MIP after LP phase completion
 * - LPFinished flag tracks phase transition
 *
 * @algorithm LP-to-MIP Phase Transition Strategy
 * @math LP phase: Solve LP relaxation (fast) to generate hyperplanes quickly.
 *       Transition to MIP when: iteration limit reached, time budget exceeded,
 *       or dual bound improvement stagnates (|z^LP_k - z^LP_{k-1}| < ε).
 *       MIP phase: Solve full MILP for valid dual bounds.
 * @complexity O(phase detection). LP phase typically 10-100 iterations.
 * @see IRelaxationStrategy.h for interface
 */
#pragma once
#include "RelaxationStrategyBase.h"
#include "../Environment.h"
#include "../Enums.h"

namespace SHOT
{
class RelaxationStrategyStandard : public IRelaxationStrategy, public RelaxationStrategyBase
{
public:
    RelaxationStrategyStandard(EnvironmentPtr envPtr);
    ~RelaxationStrategyStandard() override;

    void executeStrategy() override;

    void setActive() override;

    void setInactive() override;

    void setInitial() override;

private:
    bool isIterationLimitReached();
    bool isTimeLimitReached();
    bool isLPStepFinished();
    bool isObjectiveStagnant();

    bool LPFinished;
};

} // namespace SHOT