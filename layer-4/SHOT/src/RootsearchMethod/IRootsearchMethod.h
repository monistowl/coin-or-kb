/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file RootsearchMethod/IRootsearchMethod.h
 * @brief Interface for constraint boundary rootsearch algorithms
 *
 * Finds points on constraint boundaries for ESH hyperplane generation.
 *
 * **Purpose:**
 * Given interior point A and exterior point B, find point on boundary
 * where constraint function equals zero (feasibility boundary).
 *
 * **Constraint Rootsearch:**
 * - findZero(ptA, ptB, ...): Search along line segment A→B
 * - Returns (boundary point, exterior point) pair
 * - lambdaTol: Tolerance on line parameter
 * - constrTol: Tolerance on constraint violation
 *
 * **Objective Rootsearch:**
 * - findZero(pt, objLB, objUB, ...): Find objective level set
 * - Used for objective function cuts
 *
 * **Algorithm:**
 * - Uses bisection or hybrid methods (TOMS 748)
 * - Requires f(A) < 0 (feasible) and f(B) > 0 (infeasible)
 *
 * **Implementations:**
 * - RootsearchMethodBoost: Boost.Math TOMS 748 or bisection
 *
 * @algorithm Essential for Extended Supporting Hyperplane (ESH) method
 * @see DualSolver.h for hyperplane generation workflow
 */
#pragma once
#include "../Environment.h"
#include "../Structs.h"

#include "../Model/Constraints.h"
#include "../Model/ObjectiveFunction.h"

namespace SHOT
{

class IRootsearchMethod
{
public:
    IRootsearchMethod() = default;
    IRootsearchMethod(EnvironmentPtr envPtr [[maybe_unused]]) {};
    virtual ~IRootsearchMethod() = default;

    virtual std::pair<VectorDouble, VectorDouble> findZero(const VectorDouble& ptA, const VectorDouble& ptB, int Nmax,
        double lambdaTol, double constrTol, const std::vector<NumericConstraint*> constraints, bool addPrimalCandidate)
        = 0;

    virtual std::pair<VectorDouble, VectorDouble> findZero(const VectorDouble& ptA, const VectorDouble& ptB, int Nmax,
        double lambdaTol, double constrTol, const NonlinearConstraints constraints, bool addPrimalCandidate)
        = 0;

    virtual std::pair<double, double> findZero(const VectorDouble& pt, double objectiveLB, double objectiveUB, int Nmax,
        double lambdaTol, double constrTol, ObjectiveFunctionPtr objectiveFunction)
        = 0;

protected:
    EnvironmentPtr env;
};
} // namespace SHOT