// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpQuadraticObjective.hpp
 * @brief Quadratic objective function for convex QP (x'Qx/2 + c'x)
 *
 * Implements convex quadratic objectives for quadratic programming.
 * The quadratic term is stored as a CoinPackedMatrix Q, supporting
 * both full symmetric and half (lower triangular) storage.
 *
 * @algorithm Convex Quadratic Programming:
 * Extends LP to handle quadratic objectives while preserving convexity.
 *
 * @math PROBLEM FORMULATION:
 *   minimize    (1/2)x'Qx + c'x
 *   subject to  Ax = b, l ≤ x ≤ u
 *
 * where Q ∈ ℝⁿˣⁿ is symmetric positive semi-definite (PSD).
 * Q PSD ⟺ x'Qx ≥ 0 for all x ⟺ all eigenvalues ≥ 0.
 *
 * @algorithm Gradient and Hessian:
 *   ∇f(x) = Qx + c     (gradient)
 *   ∇²f(x) = Q         (Hessian, constant)
 *
 * @algorithm Reduced Gradient for Simplex:
 * For basic/nonbasic partition with B = basic indices:
 *   Reduced cost of nonbasic j: d_j = c_j + (Qx)_j - π'A_j
 *   where π = (A_B)⁻ᵀ(c_B + (Qx)_B)
 *
 * @algorithm Line Search for QP:
 * Given direction Δx, find θ* = argmin_{θ≥0} f(x + θΔx):
 *   f(x + θΔx) = f(x) + θ·∇f(x)'Δx + (θ²/2)·Δx'Q·Δx
 *
 * If Δx'QΔx > 0 (descent in strictly convex direction):
 *   θ* = -∇f(x)'Δx / (Δx'QΔx)
 * Else (linear along Δx):
 *   θ* = maximumTheta (go to bound)
 *
 * MATRIX STORAGE:
 *   fullMatrix_ = false: Lower triangular only (Q_ij stored for i ≥ j)
 *   fullMatrix_ = true: Full symmetric (both Q_ij and Q_ji stored)
 *
 * @complexity Gradient evaluation: O(nnz(Q)) per iteration
 *   Line search: O(nnz(Q)) for computing Δx'QΔx
 *
 * @see ClpObjective for the abstract objective interface
 * @see ClpLinearObjective for linear-only objectives
 * @see ClpSimplexNonlinear for QP simplex variants
 * @see ClpInterior for interior point QP solving
 */

#ifndef ClpQuadraticObjective_H
#define ClpQuadraticObjective_H

#include "ClpConfig.h"
#include "ClpObjective.hpp"
#include "CoinPackedMatrix.hpp"

//#############################################################################

/** Quadratic Objective Class

*/

class CLPLIB_EXPORT ClpQuadraticObjective : public ClpObjective {

public:
  ///@name Stuff
  //@{

  /** Returns gradient.  If Quadratic then solution may be NULL,
         also returns an offset (to be added to current one)
         If refresh is false then uses last solution
         Uses model for scaling
         includeLinear 0 - no, 1 as is, 2 as feasible
     */
  virtual double *gradient(const ClpSimplex *model,
    const double *solution, double &offset, bool refresh,
    int includeLinear = 2);
  /// Resize objective
  /** Returns reduced gradient.Returns an offset (to be added to current one).
     */
  virtual double reducedGradient(ClpSimplex *model, double *region,
    bool useFeasibleCosts);
  /** Returns step length which gives minimum of objective for
         solution + theta * change vector up to maximum theta.

         arrays are numberColumns+numberRows
         Also sets current objective, predicted and at maximumTheta
     */
  virtual double stepLength(ClpSimplex *model,
    const double *solution,
    const double *change,
    double maximumTheta,
    double &currentObj,
    double &predictedObj,
    double &thetaObj);
  /// Return objective value (without any ClpModel offset) (model may be NULL)
  virtual double objectiveValue(const ClpSimplex *model, const double *solution) const;
  virtual void resize(int newNumberColumns);
  /// Delete columns in  objective
  virtual void deleteSome(int numberToDelete, const int *which);
  /// Scale objective
  virtual void reallyScale(const double *columnScale);
  /** Given a zeroed array sets nonlinear columns to 1.
         Returns number of nonlinear columns
      */
  virtual int markNonlinear(char *which);

  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpQuadraticObjective();

  /// Constructor from objective
  ClpQuadraticObjective(const double *linearObjective, int numberColumns,
    const CoinBigIndex *start,
    const int *column, const double *element,
    int numberExtendedColumns_ = -1);

  /** Copy constructor .
         If type is -1 then make sure half symmetric,
         if +1 then make sure full
     */
  ClpQuadraticObjective(const ClpQuadraticObjective &rhs, int type = 0);
  /** Subset constructor.  Duplicates are allowed
         and order is as given.
     */
  ClpQuadraticObjective(const ClpQuadraticObjective &rhs, int numberColumns,
    const int *whichColumns);

  /// Assignment operator
  ClpQuadraticObjective &operator=(const ClpQuadraticObjective &rhs);

  /// Destructor
  virtual ~ClpQuadraticObjective();

  /// Clone
  virtual ClpObjective *clone() const;
  /** Subset clone.  Duplicates are allowed
         and order is as given.
     */
  virtual ClpObjective *subsetClone(int numberColumns,
    const int *whichColumns) const;

  /** Load up quadratic objective.  This is stored as a CoinPackedMatrix */
  void loadQuadraticObjective(const int numberColumns,
    const CoinBigIndex *start,
    const int *column, const double *element,
    int numberExtendedColumns = -1);
  void loadQuadraticObjective(const CoinPackedMatrix &matrix);
  /// Get rid of quadratic objective
  void deleteQuadraticObjective();
  //@}
  ///@name Gets and sets
  //@{
  /// Quadratic objective
  inline CoinPackedMatrix *quadraticObjective() const
  {
    return quadraticObjective_;
  }
  /// Linear objective
  inline double *linearObjective() const
  {
    return objective_;
  }
  /// Length of linear objective which could be bigger
  inline int numberExtendedColumns() const
  {
    return numberExtendedColumns_;
  }
  /// Number of columns in quadratic objective
  inline int numberColumns() const
  {
    return numberColumns_;
  }
  /// If a full or half matrix
  inline bool fullMatrix() const
  {
    return fullMatrix_;
  }
  //@}

  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  /// Quadratic objective
  CoinPackedMatrix *quadraticObjective_;
  /// Objective
  double *objective_;
  /// Gradient
  double *gradient_;
  /// Useful to have number of columns about
  int numberColumns_;
  /// Also length of linear objective which could be bigger
  int numberExtendedColumns_;
  /// True if full symmetric matrix, false if half
  bool fullMatrix_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
