// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPresolveTighten.hpp
 * @brief Tighten variable bounds using constraint propagation
 *
 * @algorithm Bound Tightening:
 *   For each constraint Σ a_ij x_j ≤ b_i:
 *   1. Compute max activity without x_k: M_k = Σ_{j≠k} max(a_ij l_j, a_ij u_j)
 *   2. New upper bound: x_k ≤ (b_i - M_k) / a_ik (if a_ik > 0)
 *   3. New lower bound: x_k ≥ (b_i - M_k) / a_ik (if a_ik < 0)
 *   4. Iterate until no bound changes or fixed point reached
 *
 *   tighten_zero_cost: fix variables with zero objective at bounds
 *
 * @math Implied bound: given Σa_j x_j ≤ b and x_j ∈ [l_j, u_j]
 *   x_k ≤ (b - Σ_{j≠k} a_j l_j) / a_k when a_k > 0
 *   Dual bound tightening uses similar logic from reduced costs
 *
 * @complexity Time: O(iterations × nnz) for propagation
 *   Very effective for tightly constrained problems
 *   May prove infeasibility or fix variables
 *
 * @see CoinPresolveMatrix for the presolve framework
 */

#ifndef CoinPresolveTighten_H
#define CoinPresolveTighten_H

#include "CoinPresolveMatrix.hpp"

// This action has no separate class;
// instead, it decides which columns can be made fixed
// and calls make_fixed_action::presolve.
const CoinPresolveAction *tighten_zero_cost(CoinPresolveMatrix *prob,
  const CoinPresolveAction *next);

#define DO_TIGHTEN 30

class COINUTILSLIB_EXPORT do_tighten_action : public CoinPresolveAction {
  do_tighten_action();
  do_tighten_action(const do_tighten_action &rhs);
  do_tighten_action &operator=(const do_tighten_action &rhs);

  struct action {
    int *rows;
    double *lbound;
    double *ubound;
    int col;
    int nrows;
    int direction; // just for assertions
  };

  const int nactions_;
  const action *const actions_;

  do_tighten_action(int nactions,
    const action *actions,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , nactions_(nactions)
    , actions_(actions)
  {
  }

public:
  const char *name() const;

  static const CoinPresolveAction *presolve(CoinPresolveMatrix *prob,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~do_tighten_action();
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
