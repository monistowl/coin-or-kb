// Copyright (C) 2007, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpConstraintQuadratic.hpp
 * @brief Quadratic constraint implementation: x'Qx + c'x ≤ b
 *
 * Implements ClpConstraint for quadratic constraints. The constraint
 * function is: 0.5 * sum_{ij}(Q_ij * x_i * x_j) + sum_j(c_j * x_j) ≤ b
 *
 * @algorithm Quadratic Constraints for QCQP:
 * Handles constraints that are quadratic in the decision variables.
 *
 * @math CONSTRAINT FORM:
 *   g(x) = (1/2)x'Qx + c'x - b ≤ 0
 *
 * where Q is symmetric (but not necessarily PSD for constraints).
 *
 * @algorithm Gradient Computation:
 *   ∇g(x) = Qx + c
 *
 * Unlike linear constraints, gradient depends on current point x.
 * Must recompute each time solution changes.
 *
 * @algorithm Function Value:
 *   g(x) = (1/2)Σᵢⱼ Qᵢⱼxᵢxⱼ + Σⱼ cⱼxⱼ - b
 *
 * Storage encodes both quadratic and linear terms:
 *   column[k] = -1: Linear coefficient for variable in position
 *   column[k] ≥ 0: Quadratic coefficient Q_{row,col}
 *
 * SPARSITY MARKING:
 *   markNonzero(): All variables with non-zero gradient coefficient
 *   markNonlinear(): Variables appearing in quadratic terms (Q entries)
 *
 * @algorithm Use in SLP (Sequential Linear Programming):
 * At point x̄, linearize: g(x) ≈ g(x̄) + ∇g(x̄)'(x - x̄)
 * Constraint becomes: ∇g(x̄)'x ≤ -g(x̄) + ∇g(x̄)'x̄
 *
 * Trust region limits step size to control linearization error.
 * For convex constraints (Q PSD), linearization underestimates
 * true constraint, maintaining feasibility.
 *
 * @see ClpConstraint for the abstract interface
 * @see ClpConstraintLinear for purely linear constraints
 * @see ClpSimplexNonlinear for the SLP solver
 */

#ifndef ClpConstraintQuadratic_H
#define ClpConstraintQuadratic_H

#include "ClpConstraint.hpp"

//#############################################################################

/** Quadratic Constraint Class

*/

class CLPLIB_EXPORT ClpConstraintQuadratic : public ClpConstraint {

public:
  ///@name Stuff
  //@{

  /** Fills gradient.  If Quadratic then solution may be NULL,
         also returns true value of function and offset so we can use x not deltaX in constraint
         If refresh is false then uses last solution
         Uses model for scaling
         Returns non-zero if gradient udefined at current solution
     */
  virtual int gradient(const ClpSimplex *model,
    const double *solution,
    double *gradient,
    double &functionValue,
    double &offset,
    bool useScaling = false,
    bool refresh = true) const;
  /// Resize constraint
  virtual void resize(int newNumberColumns);
  /// Delete columns in  constraint
  virtual void deleteSome(int numberToDelete, const int *which);
  /// Scale constraint
  virtual void reallyScale(const double *columnScale);
  /** Given a zeroed array sets nonquadratic columns to 1.
         Returns number of nonquadratic columns
      */
  virtual int markNonlinear(char *which) const;
  /** Given a zeroed array sets possible nonzero coefficients to 1.
         Returns number of nonzeros
      */
  virtual int markNonzero(char *which) const;
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpConstraintQuadratic();

  /// Constructor from quadratic
  ClpConstraintQuadratic(int row, int numberQuadraticColumns, int numberColumns,
    const CoinBigIndex *start,
    const int *column, const double *element);

  /** Copy constructor .
     */
  ClpConstraintQuadratic(const ClpConstraintQuadratic &rhs);

  /// Assignment operator
  ClpConstraintQuadratic &operator=(const ClpConstraintQuadratic &rhs);

  /// Destructor
  virtual ~ClpConstraintQuadratic();

  /// Clone
  virtual ClpConstraint *clone() const;
  //@}
  ///@name Gets and sets
  //@{
  /// Number of coefficients
  virtual int numberCoefficients() const;
  /// Number of columns in constraint
  inline int numberColumns() const
  {
    return numberColumns_;
  }
  /// Column starts
  inline CoinBigIndex *start() const
  {
    return start_;
  }
  /// Columns
  inline const int *column() const
  {
    return column_;
  }
  /// Coefficients
  inline const double *coefficient() const
  {
    return coefficient_;
  }
  //@}

  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  /// Column starts
  CoinBigIndex *start_;
  /// Column (if -1 then linear coefficient)
  int *column_;
  /// Coefficients
  double *coefficient_;
  /// Useful to have number of columns about
  int numberColumns_;
  /// Number of coefficients in gradient
  int numberCoefficients_;
  /// Number of quadratic columns
  int numberQuadraticColumns_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
