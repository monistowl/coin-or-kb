/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/RelaxationStrategyNone.h
 * @brief No-op relaxation strategy (always MIP)
 *
 * Disables LP relaxation phase, always solves full MIP.
 *
 * **RelaxationStrategyNone Class:**
 * - executeStrategy(): No-op (MIP always active)
 * - setActive()/setInactive()/setInitial(): State management
 *
 * **Use Case:**
 * - Problems where LP phase doesn't help
 * - When integer solutions are needed immediately
 * - Benchmarking MIP-only performance
 *
 * **Behavior:**
 * - Every iteration solves full MIP problem
 * - No LP warm-start phase for hyperplane generation
 *
 * @see RelaxationStrategyStandard.h for LP-then-MIP
 */
#pragma once
#include "RelaxationStrategyBase.h"
#include "../Environment.h"
#include "../Enums.h"

namespace SHOT
{
class RelaxationStrategyNone : public IRelaxationStrategy, public RelaxationStrategyBase
{
public:
    RelaxationStrategyNone(EnvironmentPtr envPtr);
    ~RelaxationStrategyNone() override;

    void executeStrategy() override;

    void setActive() override;

    void setInactive() override;

    void setInitial() override;

private:
};

} // namespace SHOT