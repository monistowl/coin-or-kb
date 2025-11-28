/*
 *
 * Name:    exprCeil.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of ceiling
 *
 * (C) Pietro Belotti, 2011.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprCeil.hpp
 * @brief Ceiling function w = ceil(x)
 *
 * Returns the smallest integer not less than x. Piecewise constant
 * function with jump discontinuities at each integer.
 *
 * **Convexification challenge:**
 * ceil(x) is neither convex nor concave nor continuous. The function
 * is constant on intervals (n-1, n] with value n.
 *
 * **Bound propagation:**
 * - lb(w) = ceil(lb(x))
 * - ub(w) = ceil(ub(x))
 *
 * **Integrality:**
 * Result is always integer-valued. Can be used in MINLP constraints
 * that round up quantities.
 *
 * **Relationship to floor:**
 * ceil(x) = -floor(-x), so implementations can share code.
 *
 * @see exprFloor for the complementary floor function
 */
#ifndef COUENNE_EXPRCEIL_HPP
#define COUENNE_EXPRCEIL_HPP

#include "CouenneExpression.hpp"

namespace Couenne {

/// class ceiling, \f$ \lceil f(x) \rceil \f$

class exprCeil: public exprUnary {

 public:

  /// constructor, destructor
  exprCeil (expression *arg):
    exprUnary (arg) {}

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprCeil (argument_ -> clone (d));}

  //// the operator's function
  inline unary_function F ()
  {return ceil;}

  /// print operator
  std::string printOp () const
  {return "ceil";}

  /// return l-2 norm of gradient at given point
  inline CouNumber gradientNorm (const double *x) {
    return (argument_ -> Index () < 0) ?
      0. : fabs (x [argument_ -> Index ()]);
  }

  /// obtain derivative of expression
  expression *differentiate (int index);

  /// Get lower and upper bound of an expression (if any)
  void getBounds (expression *&, expression *&);

  /// Get value of lower and upper bound of an expression
  void getBounds (CouNumber &lb, CouNumber &ub);

  /// generate equality between *this and *w
  void generateCuts (expression *w, //const OsiSolverInterface &si,
		     OsiCuts &cs, const CouenneCutGenerator *cg,
		     t_chg_bounds * = NULL, int = -1,
		     CouNumber = -COUENNE_INFINITY,
		     CouNumber =  COUENNE_INFINITY);

  /// code for comparisons
  virtual enum expr_type code ()
  {return COU_EXPRCEIL;}

  /// implied bound processing
  bool impliedBound (int index, CouNumber *l, CouNumber *u, t_chg_bounds *chg, enum auxSign = expression::AUX_EQ) {

    bool impl = true;
    return impl;
  }

  /// Set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj,
				  const OsiBranchingInformation *info,
				  expression * &var,
				  double * &brpts,
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way)
  {return 0.;}

  /// closest feasible points in function in both directions
  virtual void closestFeasible (expression *varind, expression *vardep,
				CouNumber& left, CouNumber& right) const;

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side?
  virtual bool isCuttable (CouenneProblem *problem, int index) const
  {return false;}

  /// either CONVEX, CONCAVE, AFFINE, or NONCONVEX
  //virtual enum convexity convexity () const;
};

}

#endif
