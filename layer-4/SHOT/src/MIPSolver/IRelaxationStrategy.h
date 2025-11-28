/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/IRelaxationStrategy.h
 * @brief Interface for LP relaxation control strategies
 *
 * Manages when to solve LP relaxation vs full MIP.
 *
 * **IRelaxationStrategy Interface:**
 * - executeStrategy(): Apply relaxation decision
 * - setActive()/setInactive(): Enable/disable strategy
 * - setInitial(): Reset to initial state
 *
 * **Implementations:**
 * - RelaxationStrategyStandard: Periodic LP solves
 * - RelaxationStrategyNone: Always solve full MIP
 *
 * **Use Case:**
 * - LP relaxations generate more hyperplanes quickly
 * - MIP solves provide better candidate points
 * - Strategy balances cut generation vs exploration
 *
 * @see RelaxationStrategyBase.h for base implementation
 */
#pragma once

#include "../Enums.h"

namespace SHOT
{
class IRelaxationStrategy
{
public:
    virtual ~IRelaxationStrategy() = default;

    virtual void executeStrategy() = 0;

    virtual void setActive() = 0;
    virtual void setInactive() = 0;

    virtual void setInitial() = 0;
};
} // namespace SHOT