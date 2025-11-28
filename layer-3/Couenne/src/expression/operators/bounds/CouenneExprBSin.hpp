/* */
/*
 * Name:    exprBSin.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of operators to compute lower/upper bounds of sines
 *
 * (C) Carnegie-Mellon University, 2006.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprBSin.hpp
 * @brief Bound operators for sine expressions
 *
 * Computes tight bounds for sin(x) given bounds [l, u] on x.
 * Used by FBBT (feasibility-based bound tightening) to propagate
 * bounds through trigonometric expressions.
 *
 * **exprLBSin (lower bound):**
 * - Returns -1 if interval spans full period (u - l >= 2π)
 * - Returns -1 if interval contains 3π/2 + 2kπ (minimum of sin)
 * - Otherwise returns min(sin(l), sin(u))
 *
 * **exprUBSin (upper bound):**
 * - Returns +1 if interval spans full period
 * - Returns +1 if interval contains π/2 + 2kπ (maximum of sin)
 * - Otherwise returns max(sin(l), sin(u))
 *
 * **Period handling:**
 * Uses floor(l/2π - offset) < floor(u/2π - offset) to detect
 * if critical points lie within [l, u]:
 * - offset = 0.75 for min (3π/2)
 * - offset = 0.25 for max (π/2)
 *
 * @see CouenneExprSin for the sine expression itself
 * @see CouenneExprBCos for cosine bound computation
 */
#ifndef COUENNE_EXPRBSIN_HPP
#define COUENNE_EXPRBSIN_HPP

#include "CouenneExprOp.hpp"
#include "CoinHelperFunctions.hpp"

#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

namespace Couenne {

///  class to compute lower bound of a sine based on the bounds on its
///  arguments

class COUENNELIB_EXPORT exprLBSin: public exprOp {

 public:

  /// Constructors, destructor
  exprLBSin (expression *lb, expression *ub):
    exprOp (new expression * [2], 2) {
    arglist_ [0] = lb;
    arglist_ [1] = ub;
  } //< non-leaf expression, with argument list

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprLBSin (arglist_ [0] -> clone (d),
			 arglist_ [1] -> clone (d));}

  /// function for the evaluation of the expression
  CouNumber operator () ();

  /// print position (PRE, INSIDE, POST)
  enum pos printPos () const
    {return PRE;}

  /// print operator
  std::string printOp () const
    {return "LB_Sin";}
};


/// compute sum

inline CouNumber exprLBSin::operator () () {

  CouNumber
    l = (*(arglist_ [0])) (),
    u = (*(arglist_ [1])) ();

  CouNumber pi2 = 2 * M_PI;

  if ((u - l >= pi2) ||        // 1) interval spans whole cycle
      (floor (l/pi2 - 0.75) < // 2) there is a 3/2 pi + 2k pi between l and u
       floor (u/pi2 - 0.75)))
    return -1.;

  return CoinMin (sin (l), sin (u));
}


///////////////////////////////////////////////////////////////////////////////

///  class to compute lower bound of a sine based on the bounds on its
///  arguments

class COUENNELIB_EXPORT exprUBSin: public exprOp {

 public:

  /// Constructors, destructor
  exprUBSin (expression *lb, expression *ub):
    exprOp (new expression * [2], 2) {
    arglist_ [0] = lb;
    arglist_ [1] = ub;
  } //< non-leaf expression, with argument list

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprUBSin (arglist_ [0] -> clone (d),
			 arglist_ [1] -> clone (d));}

  /// function for the evaluation of the expression
  CouNumber operator () ();

  /// print operator
  std::string printOp () const
    {return "UB_Sin";}

  /// print position (PRE, INSIDE, POST)
  enum pos printPos () const
    {return PRE;}
};


/// compute sum

inline CouNumber exprUBSin::operator () () {

  CouNumber
    l = (*(arglist_ [0])) (),
    u = (*(arglist_ [1])) ();

  CouNumber pi2 = 2 * M_PI;

  if ((u - l >= pi2) ||       // 1) interval spans whole cycle
      (floor (l/pi2 - 0.25) < // 2) there is a pi/2 + 2k pi between l and u
       floor (u/pi2 - 0.25)))
    return 1.;

  return CoinMax (sin (l), sin (u));
}

}

#endif
