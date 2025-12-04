// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#ifndef CoinPresolveZeros_H
#define CoinPresolveZeros_H

/**
 * @file CoinPresolveZeros.hpp
 * @brief Drop and reintroduce explicit zero coefficients
 *
 * @algorithm Explicit Zero Removal:
 *   Cleans matrix by removing zero coefficients:
 *   1. Scan specified columns for zero coefficients (|a_ij| < tolerance)
 *   2. Record (row, col) positions of zeros for postsolve
 *   3. Remove zeros from sparse storage
 *   4. Update row/column counts and pointers
 *   5. Postsolve: Reinsert explicit zeros at recorded positions
 *
 * @math Why explicit zeros exist:
 *   From numerical cancellation during presolve transformations
 *   Or from user input with sparse format containing zeros
 *   Removing improves efficiency of subsequent operations
 *
 * @complexity O(nnz in checked columns) to scan and remove
 *   Memory: O(nzeros) to store positions for postsolve
 *   Called after transformations that may introduce zeros
 *
 * @see CoinPresolveMatrix for the presolve framework
 */

#define DROP_ZERO 8

/*! \brief Tracking information for an explicit zero coefficient

  \todo Why isn't this a nested class in drop_zero_coefficients_action?
	That would match the structure of other presolve classes.
*/

struct dropped_zero {
  int row;
  int col;
};

/*! \brief Removal of explicit zeros

  The presolve action for this class removes explicit zeros from the constraint
  matrix. The postsolve action puts them back.
*/
class COINUTILSLIB_EXPORT drop_zero_coefficients_action : public CoinPresolveAction {

  const int nzeros_;
  const dropped_zero *const zeros_;

  drop_zero_coefficients_action(int nzeros,
    const dropped_zero *zeros,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , nzeros_(nzeros)
    , zeros_(zeros)
  {
  }

public:
  const char *name() const { return ("drop_zero_coefficients_action"); }

  static const CoinPresolveAction *presolve(CoinPresolveMatrix *prob,
    int *checkcols,
    int ncheckcols,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~drop_zero_coefficients_action() { deleteAction(zeros_, dropped_zero *); }
};

COINUTILSLIB_EXPORT
const CoinPresolveAction *drop_zero_coefficients(CoinPresolveMatrix *prob,
  const CoinPresolveAction *next);

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
