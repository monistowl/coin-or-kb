/**
 * @file CbcHeuristicDiveFractional.hpp
 * @brief Dive heuristic selecting most fractional variable
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDiveFractional: Simplest diving strategy.
 * Selects the variable with value closest to 0.5 (most fractional).
 *
 * @algorithm Most Fractional Variable Selection:
 *   selectVariableToBranch() for fractional integer x_j:
 *   1. Compute fractionality: f_j = min(x̄_j - ⌊x̄_j⌋, ⌈x̄_j⌉ - x̄_j).
 *   2. Select j* = argmax{f_j : j ∈ fractional integers}.
 *   3. Round toward nearest integer (bestRound from f_j comparison).
 *   Rationale: Most fractional = hardest to round = fix early.
 *
 * @math Fractionality measure:
 *   f(x) = min(x - floor(x), ceil(x) - x).
 *   f(x) ∈ [0, 0.5], with f(x) = 0.5 being maximally fractional.
 *   Breaking hardest decisions first often finds feasibility faster.
 *
 * Simple but effective for breaking ties and finding feasibility.
 *
 * @see CbcHeuristicDive for base class and diving algorithm
 * @see CbcHeuristicDivePseudoCost for pseudocost-guided variant
 */

#ifndef CbcHeuristicDiveFractional_H
#define CbcHeuristicDiveFractional_H

#include "CbcHeuristicDive.hpp"

/** Dive on most fractional variable
 */

class CBCLIB_EXPORT CbcHeuristicDiveFractional : public CbcHeuristicDive {
public:
  // Default Constructor
  CbcHeuristicDiveFractional();

  // Constructor with model - assumed before cuts
  CbcHeuristicDiveFractional(CbcModel &model);

  // Copy constructor
  CbcHeuristicDiveFractional(const CbcHeuristicDiveFractional &);

  // Destructor
  ~CbcHeuristicDiveFractional();

  /// Clone
  virtual CbcHeuristicDiveFractional *clone() const;

  /// Assignment operator
  CbcHeuristicDiveFractional &operator=(const CbcHeuristicDiveFractional &rhs);

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
