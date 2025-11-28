/* */
/*
 * Name:    exprBDiv.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of operators to compute lower/upper bounds of divisions
 *
 * (C) Carnegie-Mellon University, 2006.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprBDiv.hpp
 * @brief Bound operators for division expressions
 *
 * Computes tight bounds for n/d given bounds [n, N] on numerator
 * and [d, D] on denominator. Handles singularity at d = 0.
 *
 * **safeDiv():**
 * Utility for safe division avoiding NaN:
 * - Returns 0 if numerator is ~0
 * - Returns ±∞ if denominator is ~0 (sign-aware)
 * - Otherwise returns a/b
 *
 * **exprLBDiv (lower bound):**
 * Case analysis on signs:
 * - d > 0: positive denominator → lb = n/D or n/d
 * - d ≤ 0, D > 0: crosses zero → -∞ (unbounded)
 * - d ≤ 0, D ≤ 0: negative denominator → lb = N/D or N/d
 *
 * **exprUBDiv (upper bound):**
 * Symmetric case analysis:
 * - d > 0: ub = N/D or N/d
 * - d ≤ 0, D > 0: crosses zero → +∞
 * - d ≤ 0, D ≤ 0: ub = n/D or n/d
 *
 * @see CouenneExprDiv for the division expression
 * @see CouenneExprBMul for multiplication bounds
 */
#ifndef COUENNE_EXPRBDIV_H
#define COUENNE_EXPRBDIV_H

#include "CouenneExprOp.hpp"

namespace Couenne {

/// division that avoids NaN's and considers a sign when returning infinity
static inline CouNumber safeDiv (CouNumber a, CouNumber b, int sign) {

  if (fabs (a) < COUENNE_EPS) return 0;
  //    if (fabs (b) < COUENNE_EPS)) return 0;
  //    else return 0

  if (fabs (b) < COUENNE_EPS) return ((sign < 0) ? -COUENNE_INFINITY :  COUENNE_INFINITY);

  if (a >  COUENNE_INFINITY) return ((sign < 0) ? -COUENNE_INFINITY :  COUENNE_INFINITY);
  if (a < -COUENNE_INFINITY) return ((sign < 0) ? -COUENNE_INFINITY :  COUENNE_INFINITY);

  return a/b;
}


///  class to compute lower bound of a fraction based on the bounds of
///  both numerator and denominator

class COUENNELIB_EXPORT exprLBDiv: public exprOp {

 public:

  /// Constructors, destructor
  exprLBDiv  (expression **al, int n):
    exprOp (al, n) {} //< non-leaf expression, with argument list

  /// cloning method
  expression *clone (Domain *d = NULL) const
    {return new exprLBDiv (clonearglist (d), nargs_);}

  /// function for the evaluation of the expression
  CouNumber operator () ();

  /// print position (PRE, INSIDE, POST)
  enum pos printPos () const
    {return PRE;}

  /// print operator
  std::string printOp () const
    {return "LB_Div";}
};


/// compute sum

inline CouNumber exprLBDiv::operator () () {

  CouNumber n = (*(arglist_ [0])) ();
  CouNumber N = (*(arglist_ [1])) ();
  CouNumber d = (*(arglist_ [2])) ();
  CouNumber D = (*(arglist_ [3])) ();
                                               // (n,N,d,D)     lb
  if (d > 0)                                   // (?,?,+,+)
    if   (n > 0)    return safeDiv (n,D,-1);      // (+,+,+,+) --> n/D
    else            return safeDiv (n,d,-1);      // (-,?,+,+) --> n/d
  else { // d <= 0
    if      (D > 0) return - COUENNE_INFINITY; // (?,?,-,+) --> unbounded
    else if (N > 0) return safeDiv (N,D,-1);      // (?,+,-,-) --> N/D
    else            return safeDiv (N,d,-1);      // (-,-,-,-) --> N/d
  }
}


/// class to compute upper bound of a fraction based on the bounds of
/// both numerator and denominator

class COUENNELIB_EXPORT exprUBDiv: public exprOp {

 public:

  /// Constructors, destructor
  exprUBDiv  (expression **al, int n):
    exprOp (al, n) {} //< non-leaf expression, with argument list

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprUBDiv (clonearglist (d), nargs_);}

  /// function for the evaluation of the expression
  CouNumber operator () ();

  /// print position (PRE, INSIDE, POST)
  enum pos printPos () const
    {return PRE;}

  /// print operator
  std::string printOp () const
    {return "UB_Div";}
};


/// compute sum

inline CouNumber exprUBDiv::operator () () {

  CouNumber n = (*(arglist_ [0])) ();
  CouNumber N = (*(arglist_ [1])) ();
  CouNumber d = (*(arglist_ [2])) ();
  CouNumber D = (*(arglist_ [3])) ();

  if (d > 0)                                     // (n,N,d,D)     lb
    if   (N < 0) return safeDiv (N,D,1);         // (-,-,+,+) --> N/D
    else         return safeDiv (N,d,1);         // (?,+,+,+) --> N/d
  else { // d <= 0
    if      (D > 0) return + COUENNE_INFINITY;   // (?,?,-,+) --> unbounded
    else if (n < 0) return safeDiv (n,D,1);      // (-,?,-,-) --> n/D
    else            return safeDiv (n,d,1);      // (+,+,-,-) --> n/d
  }
}

}

#endif
