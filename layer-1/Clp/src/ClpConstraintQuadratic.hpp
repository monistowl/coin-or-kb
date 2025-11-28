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
 * Storage (sparse symmetric Q):
 * - start_[i]: Column i's entries start at this index
 * - column_[k]: Column index j for Q_ij (or -1 for linear term c_i)
 * - coefficient_[k]: Value Q_ij or c_i
 *
 * Key methods:
 * - gradient(): Returns Qx + c (linear in x, unlike the quadratic function)
 * - markNonlinear(): Returns columns appearing in quadratic terms
 *
 * Used in quadratically constrained quadratic programs (QCQP) with
 * ClpSimplexNonlinear's SLP (sequential linear programming) approach.
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
