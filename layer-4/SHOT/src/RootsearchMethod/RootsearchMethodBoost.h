/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file RootsearchMethod/RootsearchMethodBoost.h
 * @brief Boost.Math rootfinding for constraint boundaries
 *
 * Finds constraint boundary points using TOMS 748 or bisection.
 *
 * **RootsearchMethodBoost Class:**
 * - findZero(ptA, ptB, constraints): Find boundary between points
 * - findZero(pt, objLB, objUB, objective): Objective rootsearch
 *
 * **Helper Classes:**
 * - Test: Functor for constraint max-violation evaluation
 * - TestObjective: Functor for objective function evaluation
 * - TerminationCondition: Convergence criterion
 *
 * **Algorithm:**
 * - TOMS 748: Optimal bracketing algorithm (4th order)
 * - Bisection: Fallback for difficult cases
 * - Returns boundary point for hyperplane generation
 *
 * @algorithm TOMS 748 / Bisection Rootfinding
 * @math Find λ* ∈ [0,1] such that max_i g_i(λ*x° + (1-λ*)x̂) = 0.
 *       TOMS 748: 4th-order bracketing, optimal among bracketing methods.
 *       Bisection fallback: halve interval each step, guaranteed O(log(1/ε)).
 * @complexity TOMS 748: superlinear convergence. Bisection: O(log₂(1/ε)) evals.
 * @ref Alefeld, Potra, Shi (1995). "TOMS 748: Enclosing zeros of continuous
 *      functions". ACM Trans. Math. Software.
 * @see IRootsearchMethod.h for interface contract
 * @see Boost.Math TOMS 748 documentation
 */
#pragma once
#include "IRootsearchMethod.h"
#include "../Environment.h"

namespace SHOT
{
class Test
{
private:
    EnvironmentPtr env;

public:
    Problem* problem;

    VectorDouble firstPt;
    VectorDouble secondPt;

    double valFirstPt;
    double valSecondPt;

    Test(EnvironmentPtr envPtr);
    ~Test();

    void setActiveConstraints(const std::vector<NumericConstraint*>& constraints);
    std::vector<NumericConstraint*> getActiveConstraints();
    void clearActiveConstraints();
    void addActiveConstraint(NumericConstraint* constraint);

    double operator()(const double x);
};

class TestObjective
{
private:
    EnvironmentPtr env;

public:
    VectorDouble solutionPoint;
    double cachedObjectiveValue;

    double firstPt;
    double secondPt;

    TestObjective(EnvironmentPtr envPtr);
    ~TestObjective();

    double operator()(const double x);
};

class TerminationCondition
{
private:
    double tol;

public:
    TerminationCondition(double tolerance) { tol = tolerance; }

    bool operator()(double min, double max) { return (abs(min - max) <= tol); }
};

class RootsearchMethodBoost : public IRootsearchMethod
{
public:
    RootsearchMethodBoost(EnvironmentPtr envPtr);
    ~RootsearchMethodBoost() override;

    std::pair<VectorDouble, VectorDouble> findZero(const VectorDouble& ptA, const VectorDouble& ptB, int Nmax,
        double lambdaTol, double constrTol, const NonlinearConstraints constraints, bool addPrimalCandidate) override;

    std::pair<VectorDouble, VectorDouble> findZero(const VectorDouble& ptA, const VectorDouble& ptB, int Nmax,
        double lambdaTol, double constrTol, const std::vector<NumericConstraint*> constraints,
        bool addPrimalCandidate) override;

    std::pair<double, double> findZero(const VectorDouble& pt, double objectiveLB, double objectiveUB, int Nmax,
        double lambdaTol, double constrTol, ObjectiveFunctionPtr objectiveFunction) override;

private:
    std::unique_ptr<Test> test;
    std::unique_ptr<TestObjective> testObjective;
    EnvironmentPtr env;
};
} // namespace SHOT