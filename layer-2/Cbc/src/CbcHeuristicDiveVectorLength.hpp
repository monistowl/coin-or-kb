/**
 * @file CbcHeuristicDiveVectorLength.hpp
 * @brief Dive heuristic based on constraint participation
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDiveVectorLength: Selects variables by column density.
 * Variables appearing in many constraints are fixed first.
 *
 * selectVariableToBranch() prioritizes variables with longer
 * columns (more nonzeros in constraint matrix). Fixing high-density
 * variables propagates more and reveals feasibility faster.
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
