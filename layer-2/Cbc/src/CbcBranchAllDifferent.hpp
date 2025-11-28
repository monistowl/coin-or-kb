/**
 * @file CbcBranchAllDifferent.hpp
 * @brief All-different constraint for integer variables
 * Copyright (C) 2004, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcBranchAllDifferent: Enforces that a set of integer variables
 * must all have different values. When two variables i,j have the
 * same value, creates branching disjunction:
 *   x_i <= x_j - 1  OR  x_i >= x_j + 1
 *
 * Common in constraint programming problems:
 * - Scheduling: No two tasks at same time
 * - Assignment: No two agents assigned same job
 * - Sudoku: No repeated digits in row/column/box
 *
 * Not as efficient as specialized CP propagation but integrates
 * with MIP framework for hybrid approaches.
 *
 * @see CbcBranchCut for base class
 * @see CbcClique for related set constraints
 *
 * Edwin 11/13/2009 carved out of CbcBranchCut
 */

#ifndef CbcBranchAllDifferent_H
#define CbcBranchAllDifferent_H

#include "CbcBranchBase.hpp"
#include "OsiRowCut.hpp"
#include "CoinPackedMatrix.hpp"
#include "CbcBranchCut.hpp"

/** Define a branch class that branches so that it is only satsified if all
    members have different values
    So cut is x <= y-1 or x >= y+1
*/

class CBCLIB_EXPORT CbcBranchAllDifferent : public CbcBranchCut {

public:
  // Default Constructor
  CbcBranchAllDifferent();

  /** Useful constructor - passed set of integer variables which must all be different
    */
  CbcBranchAllDifferent(CbcModel *model, int number, const int *which);

  // Copy constructor
  CbcBranchAllDifferent(const CbcBranchAllDifferent &);

  /// Clone
  virtual CbcObject *clone() const;

  // Assignment operator
  CbcBranchAllDifferent &operator=(const CbcBranchAllDifferent &rhs);

  // Destructor
  ~CbcBranchAllDifferent();

  /// Infeasibility - large is 0.5
  virtual double infeasibility(const OsiBranchingInformation *info,
    int &preferredWay) const;

  /// Creates a branching object
  virtual CbcBranchingObject *createCbcBranch(OsiSolverInterface *solver, const OsiBranchingInformation *info, int way);

protected:
  /// data

  /// Number of entries
  int numberInSet_;
  /// Which variables
  int *which_;
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
