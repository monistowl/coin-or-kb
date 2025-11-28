/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file NLPSolver/NLPSolverBase.h
 * @brief Base implementation for NLP solver interface
 *
 * Provides shared solve logic for all NLP solvers.
 *
 * **NLPSolverBase Class:**
 * - solveProblem(): Template method calling solveProblemInstance()
 * - Derived classes implement solveProblemInstance() hook
 *
 * **Inheritance:**
 * - Virtually inherits from INLPSolver
 * - Used with multiple inheritance (NLPSolverIpoptRelaxed)
 *
 * @see INLPSolver.h for interface contract
 * @see NLPSolverIpoptBase.h for Ipopt implementation
 */
#pragma once
#include "INLPSolver.h"

namespace SHOT
{
class NLPSolverBase : virtual public INLPSolver
{
private:
protected:
    NLPSolverBase();

public:
    E_NLPSolutionStatus solveProblem() override;
};
} // namespace SHOT