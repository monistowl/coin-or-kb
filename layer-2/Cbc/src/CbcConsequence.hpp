/**
 * @file CbcConsequence.hpp
 * @brief Abstract base for bound implications from branching
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcConsequence: Abstract interface for side effects when branching.
 * When a variable is fixed, other variables may have implied bounds
 * that go beyond what LP constraint propagation would derive.
 *
 * Example: Binary y controls whether continuous x can be nonzero.
 * When y=0, we know x=0 even if the constraint linking them is weak.
 *
 * The applyToSolver() method is called after branching to impose
 * these derived bounds on the solver, based on the branch state.
 *
 * @see CbcFixVariable for concrete implementation
 * @see CbcObject for objects that may have consequences
 *
 * Edwin 11/12/2009 carved from CbcBranchBase
 */

#ifndef CbcConsequence_H
#define CbcConsequence_H

class OsiSolverInterface;

#include "CbcConfig.h"

/** Abstract base class for consequent bounds.
    When a variable is branched on it normally interacts with other variables by
    means of equations.  There are cases where we want to step outside LP and do something
    more directly e.g. fix bounds.  This class is for that.

    At present it need not be virtual as only instance is CbcFixVariable, but ...

 */

class CBCLIB_EXPORT CbcConsequence {

public:
  // Default Constructor
  CbcConsequence();

  // Copy constructor
  CbcConsequence(const CbcConsequence &rhs);

  // Assignment operator
  CbcConsequence &operator=(const CbcConsequence &rhs);

  /// Clone
  virtual CbcConsequence *clone() const = 0;

  /// Destructor
  virtual ~CbcConsequence();

  /** Apply to an LP solver.  Action depends on state
     */
  virtual void applyToSolver(OsiSolverInterface *solver, int state) const = 0;

protected:
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
