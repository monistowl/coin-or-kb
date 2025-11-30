// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPresolveDual.hpp
 * @brief Fix variables using dual bounds and reduced cost analysis
 *
 * @algorithm Dual Bound Propagation:
 *   Use dual feasibility to fix primal variables:
 *   1. For slacks s_i: d_{n+i} = -y_i, bound y_i from slack bounds
 *   2. For singletons x_j: d_j = c_j - y_i·a_ij, bound y_i from d_j sign
 *   3. Propagate bounds through reduced cost equation d_j = c_j - y'a_j
 *   4. If d_j > 0 at optimality: x_j at lower bound (minimization)
 *   5. If d_j < 0 at optimality: x_j at upper bound
 *
 * @math Reduced cost: d_j = c_j - Σ_i y_i a_ij
 *   Dual feasibility (min): d_j ≥ 0 if x_j at lower, d_j ≤ 0 if at upper
 *   Bound propagation: y_i^L ≤ y_i ≤ y_i^U → d_j^L ≤ d_j ≤ d_j^U
 *
 * @complexity Time: O(iterations × nnz) for bound propagation
 *   Very powerful for detecting fixed variables without solving LP
 *   Can prove unboundedness when required bound is missing
 *
 * @see CoinPresolveMatrix for the presolve framework
 */

#ifndef CoinPresolveDual_H
#define CoinPresolveDual_H

/*! \class remove_dual_action
    \brief Attempt to fix variables by bounding reduced costs

  The reduced cost of x_j is d_j = c_j - y*a_j (1). Assume minimization,
  so that at optimality d_j >= 0 for x_j nonbasic at lower bound, and
  d_j <= 0 for x_j nonbasic at upper bound.
 
  For a slack variable s_i, c_(n+i) = 0 and a_(n+i) is a unit vector, hence
  d_(n+i) = -y_i. If s_i has a finite lower bound and no upper bound, we
  must have y_i <= 0 at optimality. Similarly, if s_i has no lower bound and a
  finite upper bound, we must have y_i >= 0.

  For a singleton variable x_j, d_j = c_j - y_i*a_ij. Given x_j with a
  single finite bound, we can bound d_j greater or less than 0 at
  optimality, and that allows us to calculate an upper or lower bound on y_i
  (depending on the bound on d_j and the sign of a_ij).

  Now we have bounds on some subset of the y_i, and we can use these to
  calculate upper and lower bounds on the d_j, using bound propagation on
  (1). If we can manage to bound some d_j as strictly positive or strictly
  negative, then at optimality the corresponding variable must be nonbasic
  at its lower or upper bound, respectively. If the required bound is lacking,
  the problem is unbounded.
*/

class COINUTILSLIB_EXPORT remove_dual_action : public CoinPresolveAction {

public:
  /// Destructor
  ~remove_dual_action();

  /// Name
  inline const char *name() const { return ("remove_dual_action"); }

  /*! \brief Attempt to fix variables by bounding reduced costs

    Always scans all variables. Propagates bounds on reduced costs until there's
    no change or until some set of variables can be fixed.
  */
  static const CoinPresolveAction *presolve(CoinPresolveMatrix *prob,
    const CoinPresolveAction *next);

  /*! \brief Postsolve

    In addition to fixing variables (handled by make_fixed_action), we may
    need use our own postsolve to restore constraint bounds.
  */
  void postsolve(CoinPostsolveMatrix *prob) const;

private:
  /// Postsolve (bound restore) instruction
  struct action {
    double rlo_; ///< restored row lower bound
    double rup_; ///< restored row upper bound
    int ndx_; ///< row index
  };

  /// Constructor with postsolve actions.
  remove_dual_action(int nactions, const action *actions,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , nactions_(nactions)
    , actions_(actions)
  {
  }

  /// Count of bound restore entries
  const int nactions_;
  /// Bound restore entries
  const action *actions_;
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
