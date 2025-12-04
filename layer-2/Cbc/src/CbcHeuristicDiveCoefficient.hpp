/**
 * @file CbcHeuristicDiveCoefficient.hpp
 * @brief Dive heuristic based on objective coefficients
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDiveCoefficient: Selects variables based on objective impact.
 * Prioritizes fractional variables with large objective coefficients.
 *
 * @algorithm Objective Coefficient Variable Selection:
 *   selectVariableToBranch() for fractional integer x_j:
 *   1. Score each fractional variable: score_j = |c_j| × lock_factor_j.
 *   2. Select j* = argmax{score_j : j ∈ fractional integers}.
 *   3. Round to minimize objective (down if c_j > 0 for min).
 *   Rationale: Large |c_j| = high objective impact = resolve early.
 *
 * @math Objective impact heuristic:
 *   For min c^T x: rounding x_j affects objective by c_j × (round - x̄_j).
 *   Variables with large |c_j| have most impact on objective.
 *   Fixing high-impact variables first guides toward good solutions.
 *
 * Useful when objective-driven rounding is desired.
 *
 * @see CbcHeuristicDive for base class and diving algorithm
 * @see CbcHeuristicDivePseudoCost for estimate-based variant
 */

#ifndef CbcHeuristicDiveCoefficient_H
#define CbcHeuristicDiveCoefficient_H

#include "CbcHeuristicDive.hpp"

/** Dive prioritizing large objective coefficients
 */

class CBCLIB_EXPORT CbcHeuristicDiveCoefficient : public CbcHeuristicDive {
public:
  // Default Constructor
  CbcHeuristicDiveCoefficient();

  // Constructor with model - assumed before cuts
  CbcHeuristicDiveCoefficient(CbcModel &model);

  // Copy constructor
  CbcHeuristicDiveCoefficient(const CbcHeuristicDiveCoefficient &);

  // Destructor
  ~CbcHeuristicDiveCoefficient();

  /// Clone
  virtual CbcHeuristicDiveCoefficient *clone() const;

  /// Assignment operator
  CbcHeuristicDiveCoefficient &operator=(const CbcHeuristicDiveCoefficient &rhs);

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
