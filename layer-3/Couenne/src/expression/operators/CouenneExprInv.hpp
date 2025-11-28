/*
 *
 * Name:    exprInv.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of inverse of a function (1/f(x))
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprInv.hpp
 * @brief Reciprocal function w = 1/x
 *
 * Hyperbolic function that is convex on (0, ∞) and (-∞, 0) separately.
 * Singular at x = 0, so domain handling is critical.
 *
 * **Convexification by domain:**
 * - x > 0: 1/x is convex, use secant overestimator and tangent underestimators
 * - x < 0: 1/x is convex, same approach
 * - If x can cross zero: must handle carefully, possible branching
 *
 * **Tangent line at x = a:**
 * w = 1/a - (x - a)/a² = 2/a - x/a²
 *
 * **Secant between (a, 1/a) and (b, 1/b):**
 * w = 1/a + (1/b - 1/a)/(b - a) * (x - a) = 1/a - (x - a)/(ab)
 *
 * **Properties:**
 * - Bijective: inverse of 1/x is 1/x (self-inverse)
 * - Used in division: x/y reformulated as x * (1/y)
 * - Derivatives: d(1/x)/dx = -1/x², d²(1/x)/dx² = 2/x³
 *
 * @see exprDiv which uses exprInv internally
 * @see exprMul for the multiplication component
 */
#ifndef COUENNE_EXPRINV_H
#define COUENNE_EXPRINV_H

#include "CouenneExprUnary.hpp"

namespace Couenne {

/// the operator itself
inline CouNumber inv (CouNumber arg)
{return 1. / arg;}


/// derivative of inv (x)
inline CouNumber oppInvSqr (CouNumber x)
{return (- inv (x*x));}


/// inv_dblprime, second derivative of inv (x)
inline CouNumber inv_dblprime (CouNumber x)
{return (2 * inv (x*x*x));}


/// class inverse: \f$ 1/f(x) \f$

class COUENNELIB_EXPORT exprInv: public exprUnary {

 public:

  /// Constructors, destructor
  exprInv (expression *al):
    exprUnary (al) {} //< non-leaf expression, with argument list

  /// cloning method
  expression *clone (Domain *d = NULL) const
    {return new exprInv (argument_ -> clone (d));}

  /// the operator's function
  inline unary_function F () {return inv;}

  /// output "1/argument"
  virtual void print (std::ostream &out = std::cout, bool = false) const;

  /// return l-2 norm of gradient at given point
  CouNumber gradientNorm (const double *x);

  /// differentiation
  expression *differentiate (int index);

  /// get a measure of "how linear" the expression is (see CouenneTypes.h)
  virtual inline int Linearity () {
    if (argument_ -> Type () == CONST) return CONSTANT;
    else                               return NONLINEAR;
  }

  /// Get lower and upper bound of an expression (if any)
  void getBounds (expression *&, expression *&);

  /// Get value of lower and upper bound of an expression (if any)
  void getBounds (CouNumber &lb, CouNumber &ub);

  /// generate equality between *this and *w
  void generateCuts (expression *w, //const OsiSolverInterface &si,
		     OsiCuts &cs, const CouenneCutGenerator *cg,
		     t_chg_bounds * = NULL, int = -1,
		     CouNumber = -COUENNE_INFINITY,
		     CouNumber =  COUENNE_INFINITY);

  /// code for comparisons
  virtual enum expr_type code () {return COU_EXPRINV;}

  /// implied bound processing
  bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *, enum auxSign = expression::AUX_EQ);

  /// set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj,
				  const OsiBranchingInformation *info,
				  expression * &var,
				  double * &brpts,
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way);

  /// return true if bijective
  virtual bool isBijective() const {return true;}

  /// return inverse of y=f(x)=1/x, i.e., x=1/y
  virtual CouNumber inverse(expression *vardep) const
  {
    return 1./((*vardep)());
  }

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side
  virtual bool isCuttable (CouenneProblem *problem, int index) const;
};

}

#endif
