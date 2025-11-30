// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#ifndef CoinPresolveForcing_H
#define CoinPresolveForcing_H

#include "CoinPresolveMatrix.hpp"

/**
 * @file CoinPresolveForcing.hpp
 * @brief Forcing and useless constraint detection
 *
 * @algorithm Forcing Constraint Detection:
 *   Compute implied bounds on row activity: LB_i ≤ Σ a_ij x_j ≤ UB_i
 *   using variable bounds l_j ≤ x_j ≤ u_j
 *
 *   Useless constraint: LB_i ≥ row_lb and UB_i ≤ row_ub
 *   - Constraint can never be violated → remove it
 *
 *   Forcing constraint: LB_i = row_ub or UB_i = row_lb
 *   - All variables forced to bounds that achieve the activity limit
 *   - Fix variables, remove constraint
 *
 * @math Activity bounds: LB_i = Σ_{a_ij>0} a_ij l_j + Σ_{a_ij<0} a_ij u_j
 *   UB_i = Σ_{a_ij>0} a_ij u_j + Σ_{a_ij<0} a_ij l_j
 *   Forcing: if UB_i = row_lb, then each term must achieve its min
 *
 * @complexity Time: O(nnz) to compute activity bounds for all rows
 *   Very effective for tightly bounded problems
 *   Can fix many variables simultaneously
 *
 * @see CoinPresolveMatrix for the presolve framework
 */

#define IMPLIED_BOUND 7

/*! \class forcing_constraint_action
    \brief Detect and process forcing constraints and useless constraints

  A constraint is useless if the bounds on the variables prevent the constraint
  from ever being violated.

  A constraint is a forcing constraint if the bounds on the constraint force
  the value of an involved variable to one of its bounds. A constraint can
  force more than one variable.
*/
class COINUTILSLIB_EXPORT forcing_constraint_action : public CoinPresolveAction {
  forcing_constraint_action();
  forcing_constraint_action(const forcing_constraint_action &rhs);
  forcing_constraint_action &operator=(const forcing_constraint_action &rhs);

public:
  struct action {
    const int *rowcols;
    const double *bounds;
    int row;
    int nlo;
    int nup;
  };

private:
  const int nactions_;
  // actions_ is owned by the class and must be deleted at destruction
  const action *const actions_;

public:
  forcing_constraint_action(int nactions,
    const action *actions,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , nactions_(nactions)
    , actions_(actions)
  {
  }

  const char *name() const;

  static const CoinPresolveAction *presolve(CoinPresolveMatrix *prob,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~forcing_constraint_action();
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
