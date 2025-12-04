// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPresolveIsolated.hpp
 * @brief Handle isolated constraints (connected only by free variables)
 *
 * @algorithm Isolated Constraint Removal:
 *   Removes constraints connected to rest of problem only through free variables:
 *   1. Identify constraint where all variables are free (no bounds) or
 *      appear only in this constraint
 *   2. Such constraints can be satisfied independently
 *   3. Store constraint data for postsolve restoration
 *   4. Remove row from problem (reduces problem size)
 *   5. Postsolve: Compute variable values to satisfy stored constraint
 *
 * @math Isolated constraint feasibility:
 *   Constraint: l_i ≤ Σ a_ij·x_j ≤ u_i where all x_j are free
 *   Since x_j unbounded, can always find values satisfying constraint
 *   Remove row, set x_j values in postsolve to achieve feasibility
 *
 * @complexity O(nnz in row) to detect and remove
 *   Uncommon but provides clean removal when found
 *
 * @see CoinPresolveMatrix for the presolve framework
 */

#ifndef CoinPresolveIsolated_H
#define CoinPresolveIsolated_H

#include "CoinPresolveMatrix.hpp"

class COINUTILSLIB_EXPORT isolated_constraint_action : public CoinPresolveAction {
  isolated_constraint_action();
  isolated_constraint_action(const isolated_constraint_action &rhs);
  isolated_constraint_action &operator=(const isolated_constraint_action &rhs);

  double rlo_;
  double rup_;
  int row_;
  int ninrow_;
  // the arrays are owned by the class and must be deleted at destruction
  const int *rowcols_;
  const double *rowels_;
  const double *costs_;

  isolated_constraint_action(double rlo,
    double rup,
    int row,
    int ninrow,
    const int *rowcols,
    const double *rowels,
    const double *costs,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , rlo_(rlo)
    , rup_(rup)
    , row_(row)
    , ninrow_(ninrow)
    , rowcols_(rowcols)
    , rowels_(rowels)
    , costs_(costs)
  {
  }

public:
  const char *name() const;

  static const CoinPresolveAction *presolve(CoinPresolveMatrix *prob,
    int row,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~isolated_constraint_action();
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
