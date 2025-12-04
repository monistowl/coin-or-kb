/**
 * @file CbcHeuristicDiveGuided.hpp
 * @brief Dive heuristic guided by incumbent solution
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDiveGuided: Uses existing incumbent to guide diving.
 * Requires a feasible solution (canHeuristicRun checks this).
 *
 * @algorithm Guided Dive Variable Selection (Danna, Rothberg, Le Pape):
 *   selectVariableToBranch() given incumbent x*:
 *   1. For each fractional integer x_j, compute distance to x*_j.
 *   2. Select j* with largest discrepancy: |x̄_j - x*_j|.
 *   3. Round toward incumbent: bestRound = round(x̄_j toward x*_j).
 *   Requires incumbent: canHeuristicRun() returns false if none.
 *
 * @math Incumbent-guided rounding:
 *   Score_j = |x̄_j - x*_j| for fractional j.
 *   Intuition: Variables far from incumbent are "wrong"; fix them first.
 *   Rounds toward x*_j to stay in proven-good neighborhood.
 *   Similar to RINS but integrated into diving framework.
 *
 * Part of the "Guided Dive" approach from Danna et al.
 *
 * @see CbcHeuristicDive for base class and diving algorithm
 * @see CbcHeuristicRINS for related incumbent-guided search
 */

#ifndef CbcHeuristicDiveGuided_H
#define CbcHeuristicDiveGuided_H

#include "CbcHeuristicDive.hpp"

/** Dive guided by incumbent solution
 */

class CBCLIB_EXPORT CbcHeuristicDiveGuided : public CbcHeuristicDive {
public:
  // Default Constructor
  CbcHeuristicDiveGuided();

  // Constructor with model - assumed before cuts
  CbcHeuristicDiveGuided(CbcModel &model);

  // Copy constructor
  CbcHeuristicDiveGuided(const CbcHeuristicDiveGuided &);

  // Destructor
  ~CbcHeuristicDiveGuided();

  /// Clone
  virtual CbcHeuristicDiveGuided *clone() const;

  /// Assignment operator
  CbcHeuristicDiveGuided &operator=(const CbcHeuristicDiveGuided &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Tests if the heuristic can run
  virtual bool canHeuristicRun();

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
