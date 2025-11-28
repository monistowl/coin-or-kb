/**
 * @file CbcHeuristicPivotAndFix.hpp
 * @brief Pivot and Fix heuristic using simplex pivots
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicPivotAndFix: Exploits LP basis structure.
 * Performs simplex pivots to explore nearby basic solutions,
 * then fixes integer variables at their current values.
 *
 * Uses the LP optimal basis and pivots to find integer-feasible
 * solutions nearby in the simplex sense.
 *
 * @see CbcHeuristic for base class
 * @see CbcHeuristicRandRound for randomized rounding
 */

#ifndef CbcHeuristicPivotAndFix_H
#define CbcHeuristicPivotAndFix_H

#include "CbcHeuristic.hpp"
/** Pivot-based local search heuristic
 */

class CBCLIB_EXPORT CbcHeuristicPivotAndFix : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicPivotAndFix();

  /* Constructor with model - assumed before cuts
       Initial version does not do Lps
    */
  CbcHeuristicPivotAndFix(CbcModel &model);

  // Copy constructor
  CbcHeuristicPivotAndFix(const CbcHeuristicPivotAndFix &);

  // Destructor
  ~CbcHeuristicPivotAndFix();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicPivotAndFix &operator=(const CbcHeuristicPivotAndFix &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Sets solution values if good, sets objective value (only if good)
        needs comments
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);

protected:
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
