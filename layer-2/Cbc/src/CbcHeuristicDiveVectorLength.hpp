/**
 * @file CbcHeuristicDiveVectorLength.hpp
 * @brief Dive heuristic based on constraint participation
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDiveVectorLength: Selects variables by column density.
 * Variables appearing in many constraints are fixed first.
 *
 * @algorithm Vector Length Variable Selection:
 *   selectVariableToBranch() for fractional integer x_j:
 *   1. Compute column length: len_j = |{i : a_ij ≠ 0}| (nonzeros).
 *   2. Select j* = argmax{len_j : j ∈ fractional integers}.
 *   3. Round based on lock counts (from base CbcHeuristicDive).
 *   Rationale: High-density columns affect many constraints.
 *
 * @math Column density propagation:
 *   Fixing x_j propagates to len_j constraints via bound tightening.
 *   High len_j → more constraint propagation → faster feasibility detection.
 *   Similar logic to "most constrained variable" in constraint programming.
 *   Uses matrix_ from base class for efficient column length lookup.
 *
 * Uses matrix_ from CbcHeuristicDive base class for column lengths.
 *
 * @see CbcHeuristicDive for base class and diving algorithm
 * @see CbcHeuristicDiveFractional for simpler selection
 */

#ifndef CbcHeuristicDiveVectorLength_H
#define CbcHeuristicDiveVectorLength_H

#include "CbcHeuristicDive.hpp"

/** Dive prioritizing high constraint participation
 */

class CBCLIB_EXPORT CbcHeuristicDiveVectorLength : public CbcHeuristicDive {
public:
  // Default Constructor
  CbcHeuristicDiveVectorLength();

  // Constructor with model - assumed before cuts
  CbcHeuristicDiveVectorLength(CbcModel &model);

  // Copy constructor
  CbcHeuristicDiveVectorLength(const CbcHeuristicDiveVectorLength &);

  // Destructor
  ~CbcHeuristicDiveVectorLength();

  /// Clone
  virtual CbcHeuristicDiveVectorLength *clone() const;

  /// Assignment operator
  CbcHeuristicDiveVectorLength &operator=(const CbcHeuristicDiveVectorLength &rhs);

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
