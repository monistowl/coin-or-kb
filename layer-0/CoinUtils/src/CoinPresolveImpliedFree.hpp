// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#ifndef CoinPresolveImpliedFree_H
#define CoinPresolveImpliedFree_H

/**
 * @file CoinPresolveImpliedFree.hpp
 * @brief Detect and process implied free variables
 *
 * @algorithm Implied Free Variable Detection:
 *   For singleton variable x_j (one nonzero a_ij in row i):
 *   1. Compute implied bounds on x_j from constraint i and other var bounds
 *   2. If implied bounds strictly within [l_j, u_j]: x_j is implied free
 *   3. Remove constraint i and variable x_j (neither can be binding)
 *
 *   Non-singleton case: use substitution to reduce to singleton first
 *
 * @math For row: Σ_k a_ik x_k = b_i, with x_j singleton
 *   x_j = (b_i - Σ_{k≠j} a_ik x_k) / a_ij
 *   Implied bounds from other variables' bounds → [l_j^impl, u_j^impl]
 *   If l_j < l_j^impl and u_j > u_j^impl: x_j implied free
 *
 * @complexity Time: O(nnz(row)) per candidate variable
 *   Very effective for network and assignment problems
 *   Reduces problem by one row and one column per implied free
 *
 * @see CoinPresolveSubst for non-singleton case
 * @see CoinPresolveMatrix for the presolve framework
 */

#define IMPLIED_FREE 9

/*! \class implied_free_action
    \brief Detect and process implied free variables

  Consider a singleton variable x (<i>i.e.</i>, a variable involved in only
  one constraint).  Suppose that the bounds on that constraint, combined with
  the bounds on the other variables involved in the constraint, are such that
  even the worst case values of the other variables still imply bounds for x
  which are tighter than the variable's original bounds. Since x can never
  reach its upper or lower bounds, it is an implied free variable. Both x and
  the constraint can be deleted from the problem.

  A similar transform for the case where the variable is not a natural column
  singleton is handled by #subst_constraint_action.
*/
class COINUTILSLIB_EXPORT implied_free_action : public CoinPresolveAction {
  struct action {
    int row, col;
    double clo, cup;
    double rlo, rup;
    const double *rowels;
    const double *costs;
    int ninrow;
  };

  const int nactions_;
  const action *const actions_;

  implied_free_action(int nactions,
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
    const CoinPresolveAction *next,
    int &fillLevel);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~implied_free_action();
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
