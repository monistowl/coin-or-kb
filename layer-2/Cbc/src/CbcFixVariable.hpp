/**
 * @file CbcFixVariable.hpp
 * @brief Fix variable bounds as branching consequence
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcFixVariable: Concrete CbcConsequence that fixes variable bounds
 * based on branching decisions. Implements state-dependent bound changes
 * that go beyond LP propagation.
 *
 * State encoding:
 * - -9999: Variable at lower bound
 * - +9999: Variable at upper bound
 * - Other: Variable fixed to that specific value
 *
 * For each state, stores arrays of:
 * - Variables to modify (variable_)
 * - New bounds to apply (newBound_)
 * - Ranges for lower vs upper bound changes (startLower_, startUpper_)
 *
 * Example: Binary y controls continuous x. When y=0 (state -9999),
 * fix x to 0; when y=1 (state +9999), x can be in [0, 100].
 *
 * @see CbcConsequence for base class
 * @see CbcObject for objects with consequences
 *
 * Edwin 11/10/2009 carved out of CbcBranchActual
 */

#ifndef CbcFixVariable_H
#define CbcFixVariable_H

#include "CbcBranchBase.hpp"
/** Class for consequent bounds.
    When a variable is branched on it normally interacts with other variables by
    means of equations.  There are cases where we want to step outside LP and do something
    more directly e.g. fix bounds.  This class is for that.

    A state of -9999 means at LB, +9999 means at UB,
    others mean if fixed to that value.

 */

class CBCLIB_EXPORT CbcFixVariable : public CbcConsequence {

public:
  // Default Constructor
  CbcFixVariable();

  // One useful Constructor
  CbcFixVariable(int numberStates, const int *states, const int *numberNewLower, const int **newLowerValue,
    const int **lowerColumn,
    const int *numberNewUpper, const int **newUpperValue,
    const int **upperColumn);

  // Copy constructor
  CbcFixVariable(const CbcFixVariable &rhs);

  // Assignment operator
  CbcFixVariable &operator=(const CbcFixVariable &rhs);

  /// Clone
  virtual CbcConsequence *clone() const;

  /// Destructor
  virtual ~CbcFixVariable();

  /** Apply to an LP solver.  Action depends on state
     */
  virtual void applyToSolver(OsiSolverInterface *solver, int state) const;

protected:
  /// Number of states
  int numberStates_;
  /// Values of integers for various states
  int *states_;
  /// Start of information for each state (setting new lower)
  int *startLower_;
  /// Start of information for each state (setting new upper)
  int *startUpper_;
  /// For each variable new bounds
  double *newBound_;
  /// Variable
  int *variable_;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
