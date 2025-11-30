// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPresolveDoubleton.hpp
 * @brief Doubleton row presolve: substitute y from ax+by=c
 *
 * @algorithm Doubleton Elimination:
 *   Given equality constraint ax + by = c with two variables:
 *   1. Solve for y: y = (c - ax) / b
 *   2. Substitute y in objective: c_x x + c_y y → c_x x + c_y(c-ax)/b
 *   3. Substitute y in all constraints containing y
 *   4. Transfer bounds: l_y ≤ y ≤ u_y becomes bounds on x
 *   5. Remove row and column y from problem
 *
 * @math Original: min c_x·x + c_y·y s.t. ax + by = c, bounds
 *   After: min (c_x - c_y·a/b)x + c_y·c/b, modified bounds on x
 *   Postsolve recovers y = (c - ax)/b from optimal x*
 *
 * @complexity Time: O(nnz(col_y)) per doubleton - updating all rows with y
 *   Typically reduces problem size significantly when equality rows exist
 *   Cascading effect: may create new singletons or doubletons
 *
 * @see CoinPresolveMatrix for the presolve framework
 * @see CoinPresolveTripleton for three-variable equations
 * @see CoinPresolveSingleton for single-variable equations
 */

#ifndef CoinPresolveDoubleton_H
#define CoinPresolveDoubleton_H

#define DOUBLETON 5

/*! \class doubleton_action
    \brief Solve ax+by=c for y and substitute y out of the problem.

  This moves the bounds information for y onto x, making y free and allowing
  us to substitute it away.
  \verbatim
	   a x + b y = c
	   l1 <= x <= u1
	   l2 <= y <= u2	==>
	  
	   l2 <= (c - a x) / b <= u2
	   b/-a > 0 ==> (b l2 - c) / -a <= x <= (b u2 - c) / -a
	   b/-a < 0 ==> (b u2 - c) / -a <= x <= (b l2 - c) / -a
  \endverbatim
*/
class COINUTILSLIB_EXPORT doubleton_action : public CoinPresolveAction {
public:
  struct action {

    double clox;
    double cupx;
    double costx;

    double costy;

    double rlo;

    double coeffx;
    double coeffy;

    double *colel;

    int icolx;
    int icoly;
    int row;
    int ncolx;
    int ncoly;
  };

  const int nactions_;
  const action *const actions_;

private:
  doubleton_action(int nactions,
    const action *actions,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , nactions_(nactions)
    , actions_(actions)
  {
  }

public:
  const char *name() const { return ("doubleton_action"); }

  static const CoinPresolveAction *presolve(CoinPresolveMatrix *,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~doubleton_action();
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
