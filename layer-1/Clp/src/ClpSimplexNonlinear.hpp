// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpSimplexNonlinear.hpp
 * @brief Nonlinear LP solver using reduced gradient and SLP methods
 * @author John Forrest
 *
 * Extends ClpSimplexPrimal to handle nonlinear objectives and constraints.
 *
 * @algorithm Reduced Gradient Method:
 * For problems with nonlinear objective but LINEAR constraints.
 *
 * @math PROBLEM: minimize f(x) subject to Ax = b, l ≤ x ≤ u
 *
 * Partition variables: B (basic), N (nonbasic)
 *   x_B = B⁻¹(b - N·x_N)  (basic expressed via nonbasic)
 *
 * @algorithm Reduced Gradient Computation:
 *   Full gradient: ∇f(x) = [∇f_B, ∇f_N]
 *   Reduced gradient: r = ∇f_N - N'B⁻ᵀ∇f_B
 *
 * r[j] < 0 and x_j at lower bound → can improve by increasing x_j
 * r[j] > 0 and x_j at upper bound → can improve by decreasing x_j
 *
 * @algorithm SLP (Sequential Linear Programming):
 * For problems with NONLINEAR constraints.
 *
 * @math PROBLEM: minimize f(x) subject to g(x) ≤ 0, Ax = b
 *
 * ITERATION:
 *   1. At current point x̄, linearize constraints:
 *      g(x) ≈ g(x̄) + ∇g(x̄)'(x - x̄)
 *
 *   2. Solve LP subproblem with trust region:
 *      minimize ∇f(x̄)'x
 *      subject to ∇g(x̄)'x ≤ -g(x̄) + ∇g(x̄)'x̄
 *                 |x - x̄| ≤ Δ (trust region)
 *
 *   3. Update: x̄ ← solution of LP
 *   4. Adjust trust region Δ based on actual vs predicted improvement
 *
 * @algorithm Trust Region Management:
 *   deltaTolerance parameter controls initial trust region size.
 *   Expands when LP solution improves nonlinear objective.
 *   Contracts when linearization gives poor approximation.
 *
 * @algorithm Pivot Modes:
 *   mode=0: Consider all dual infeasible variables
 *   mode=1: Select only largest reduced cost
 *   mode≥10: Startup phase (finding initial feasible point)
 *
 * RETURN CODES from pivotColumn:
 *   0: Normal iteration (basis change)
 *   1: No basis change (line search)
 *   2: Singleton pivot
 *   3: Refactorization needed
 *
 * Implementation note: This class has no data members - it's a "behavior"
 * class that is cast from ClpSimplexPrimal at algorithm time.
 *
 * @see ClpSimplexPrimal for the base primal simplex
 * @see ClpConstraint for nonlinear constraint interface
 * @see ClpQuadraticObjective for quadratic objectives
 */

#ifndef ClpSimplexNonlinear_H
#define ClpSimplexNonlinear_H

class ClpNonlinearInfo;
class ClpQuadraticObjective;
class ClpConstraint;

#include "ClpSimplexPrimal.hpp"

/** This solves non-linear LPs using the primal simplex method

    It inherits from ClpSimplexPrimal.  It has no data of its own and
    is never created - only cast from a ClpSimplexPrimal object at algorithm time.
    If needed create new class and pass around

*/

class CLPLIB_EXPORT ClpSimplexNonlinear : public ClpSimplexPrimal {

public:
  /**@name Description of algorithm */
  //@{
  /** Primal algorithms for reduced gradient
         At present we have two algorithms:

     */
  /// A reduced gradient method.
  int primal();
  /** Primal algorithm for quadratic
         Using a semi-trust region approach as for pooling problem
         This is in because I have it lying around
     */
  int primalSLP(int numberPasses, double deltaTolerance,
    int otherOptions = 0);
  /// May use a cut approach for solving any LP
  int primalDualCuts(char *rowsIn, int startUp, int algorithm);
  /** Primal algorithm for nonlinear constraints
         Using a semi-trust region approach as for pooling problem
         This is in because I have it lying around

     */
  int primalSLP(int numberConstraints, ClpConstraint **constraints,
    int numberPasses, double deltaTolerance);

  /** Creates direction vector.  note longArray is long enough
         for rows and columns.  If numberNonBasic 0 then is updated
         otherwise mode is ignored and those are used.
         Norms are only for those > 1.0e3*dualTolerance
         If mode is nonzero then just largest dj */
  void directionVector(CoinIndexedVector *longArray,
    CoinIndexedVector *spare1, CoinIndexedVector *spare2,
    int mode,
    double &normFlagged, double &normUnflagged,
    int &numberNonBasic);
  /// Main part.
  int whileIterating(int &pivotMode);
  /**
         longArray has direction
         pivotMode -
               0 - use all dual infeasible variables
           1 - largest dj
           while >= 10 trying startup phase
         Returns 0 - can do normal iteration (basis change)
         1 - no basis change
         2 - if wants singleton
         3 - if time to re-factorize
         If sequenceIn_ >=0 then that will be incoming variable
     */
  int pivotColumn(CoinIndexedVector *longArray,
    CoinIndexedVector *rowArray,
    CoinIndexedVector *columnArray,
    CoinIndexedVector *spare,
    int &pivotMode,
    double &solutionError,
    double *array1);
  /**  Refactorizes if necessary
          Checks if finished.  Updates status.
          lastCleaned refers to iteration at which some objective/feasibility
          cleaning too place.

          type - 0 initial so set up save arrays etc
               - 1 normal -if good update save
           - 2 restoring from saved
     */
  void statusOfProblemInPrimal(int &lastCleaned, int type,
    ClpSimplexProgress *progress,
    bool doFactorization,
    double &bestObjectiveWhenFlagged);
  /** Do last half of an iteration.
         Return codes
         Reasons to come out normal mode
         -1 normal
         -2 factorize now - good iteration
         -3 slight inaccuracy - refactorize - iteration done
         -4 inaccuracy - refactorize - no iteration
         -5 something flagged - go round again
         +2 looks unbounded
         +3 max iterations (iteration done)

     */
  int pivotNonlinearResult();
  //@}
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
