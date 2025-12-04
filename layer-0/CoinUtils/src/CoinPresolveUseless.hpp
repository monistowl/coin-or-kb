// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPresolveUseless.hpp
 * @brief Remove useless (redundant) constraints
 *
 * @algorithm Redundant Constraint Identification:
 *   Greedy algorithm identifying constraints implied by variable bounds:
 *   1. Initialize column bounds from original variable bounds
 *   2. For each constraint, compute implied bounds on variables
 *      - If constraint tightens some bound, mark as "necessary"
 *      - Update working column bounds with tighter values
 *   3. After processing all constraints, for non-necessary rows:
 *      - Compute row activity bounds: L_i = Σ min{a_ij·l_j, a_ij·u_j}
 *      - If l_i ≤ L_i and U_i ≤ u_i, constraint is redundant
 *   4. Remove redundant constraints, save for postsolve
 *
 * @math Redundancy condition:
 *   Row i redundant if: l_i ≤ min(a_i'x) and max(a_i'x) ≤ u_i
 *   where min/max over x ∈ [l, u] (variable bounds)
 *   No feasible point can violate such a constraint
 *
 * @complexity O(m · avg_row_length) for full scan
 *   Each constraint checked once; bound implications propagated
 *   Effective at removing slack constraints from reformulations
 *
 * @see CoinPresolveForcing for related forcing constraint detection
 * @see CoinPresolveMatrix for the presolve framework
 */

#ifndef CoinPresolveUseless_H
#define CoinPresolveUseless_H
#define USELESS 20

class COINUTILSLIB_EXPORT useless_constraint_action : public CoinPresolveAction {
  struct action {
    double rlo;
    double rup;
    const int *rowcols;
    const double *rowels;
    int row;
    int ninrow;
  };

  const int nactions_;
  const action *const actions_;

  useless_constraint_action(int nactions,
    const action *actions,
    const CoinPresolveAction *next);

public:
  const char *name() const;

  // These rows are asserted to be useless,
  // that is, given a solution the row activity
  // must be in range.
  static const CoinPresolveAction *presolve(CoinPresolveMatrix *prob,
    const int *useless_rows,
    int nuseless_rows,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~useless_constraint_action();
};

/*! \relates useless_constraint_action
    \brief Scan constraints looking for useless constraints

  A front end to identify useless constraints and hand them to
  useless_constraint_action::presolve() for processing.

  In a bit more detail, the routine implements a greedy algorithm that
  identifies a set of necessary constraints. A constraint is necessary if it
  implies a tighter bound on a variable than the original column bound. These
  tighter column bounds are then used to calculate row activity and identify
  constraints that are useless given the presence of the necessary
  constraints. 
*/

COINUTILSLIB_EXPORT
const CoinPresolveAction* testRedundant(CoinPresolveMatrix *prob,
  const CoinPresolveAction *next);

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
