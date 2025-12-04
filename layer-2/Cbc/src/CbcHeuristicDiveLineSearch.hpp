/**
 * @file CbcHeuristicDiveLineSearch.hpp
 * @brief Dive heuristic along line to LP optimum
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDiveLineSearch: Geometric diving approach.
 * Selects variables along the line from current point to LP optimum.
 *
 * @algorithm Line Search Diving:
 *   Geometric diving that follows ray toward LP optimum:
 *   1. Compute direction: d = x_LP - x_current (vector to LP optimum)
 *   2. For each fractional variable x_j:
 *      - Calculate how rounding affects position along d
 *      - Score: progress toward LP optimum vs integer violation
 *   3. Select x_j* that maximizes progress when rounded
 *   4. Fix x_j* to nearest integer, resolve LP
 *   5. Repeat until integer feasible or stuck
 *
 * @math Selection criterion:
 *   Let f_j = fraction of x_j, d_j = direction component
 *   Round down: progress = f_j · |d_j| toward LP optimum
 *   Round up: progress = (1-f_j) · |d_j| toward LP optimum
 *   Select: argmax_j {progress_j / violation_j}
 *
 * @complexity O(n) per variable selection
 *   Total: O(k · LP) where k = diving depth
 *   Typically faster than branching for finding feasible solutions
 *
 * selectVariableToBranch() considers how rounding affects
 * movement toward the LP optimal solution. Picks variables
 * where rounding makes most progress along this direction.
 *
 * Combines geometric intuition with integer rounding.
 *
 * @see CbcHeuristicDive for base class and diving algorithm
 * @see CbcHeuristicFPump for related LP-based approach
 */

#ifndef CbcHeuristicDiveLineSearch_H
#define CbcHeuristicDiveLineSearch_H

#include "CbcHeuristicDive.hpp"

/** Dive along line toward LP optimum
 */

class CBCLIB_EXPORT CbcHeuristicDiveLineSearch : public CbcHeuristicDive {
public:
  // Default Constructor
  CbcHeuristicDiveLineSearch();

  // Constructor with model - assumed before cuts
  CbcHeuristicDiveLineSearch(CbcModel &model);

  // Copy constructor
  CbcHeuristicDiveLineSearch(const CbcHeuristicDiveLineSearch &);

  // Destructor
  ~CbcHeuristicDiveLineSearch();

  /// Clone
  virtual CbcHeuristicDiveLineSearch *clone() const;

  /// Assignment operator
  CbcHeuristicDiveLineSearch &operator=(const CbcHeuristicDiveLineSearch &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Selects the next variable to branch on
  /** Returns true if all the fractional variables can be trivially
        rounded. Returns false, if there is at least one fractional variable
        that is not trivially roundable. In this case, the bestColumn
        returned will not be trivially roundable.
    */
  virtual bool selectVariableToBranch(OsiSolverInterface *solver,
    const double *newSolution,
    int &bestColumn,
    int &bestRound);
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
