/*
 *
 * Name:    CouenneExprTrilinear.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of product of three terms
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprTrilinear.hpp
 * @brief Trilinear product expression w = x*y*z
 *
 * Specialized handling for products of exactly three terms.
 * Trilinear terms are common in pooling problems and arise
 * from reformulation of bilinear products with parameters.
 *
 * **Standardization options:**
 * A trilinear term x*y*z can be reformulated as:
 * 1. w1 = x*y, w = w1*z (two bilinear terms)
 * 2. Direct trilinear relaxation
 *
 * **Convexification:**
 * Uses direct trilinear relaxation when available, which can
 * provide tighter bounds than cascaded bilinear products.
 * Generates 8 linear constraints forming a polyhedral relaxation.
 *
 * **Implied bounds:**
 * Given w in [wl,wu] and bounds on x,y,z, tightens bounds
 * by considering all 8 corners of the 3D box.
 *
 * @see CouenneExprMul for general n-ary products
 * @see CouenneExprBinProd for binary products
 */
#ifndef COUENNE_EXPRTRILINEAR_H
#define COUENNE_EXPRTRILINEAR_H

#include <vector>

#include "CouenneExprMul.hpp"

namespace Couenne {

  /// class for multiplications

  class COUENNELIB_EXPORT exprTrilinear: public exprMul {

  public:

    /// Constructor
    exprTrilinear (expression **, int);

    /// Constructor with two arguments
    exprTrilinear (expression *, expression *, expression *);

    /// Cloning method
    expression *clone (Domain *d = NULL) const
    {return new exprTrilinear (clonearglist (d), nargs_);}

    /// return l-2 norm of gradient at given point
    CouNumber gradientNorm (const double *x);

    /// Get lower and upper bound of an expression (if any)
    virtual void getBounds (expression *&, expression *&);

    /// Get value of lower and upper bound of an expression (if any)
    virtual void getBounds (CouNumber &lb, CouNumber &ub);

    /// generate equality between *this and *w
    void generateCuts (expression *w, //const OsiSolverInterface &si,
		       OsiCuts &cs, const CouenneCutGenerator *cg,
		       t_chg_bounds * = NULL, int = -1,
		       CouNumber = -COUENNE_INFINITY,
		       CouNumber =  COUENNE_INFINITY);

    /// code for comparison
    virtual enum expr_type code ()
    {return COU_EXPRTRILINEAR;}

    /// implied bound processing
    bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *,
		       enum Couenne::expression::auxSign = Couenne::expression::AUX_EQ);

    /// set up branching object by evaluating many branching points for
    /// each expression's arguments
    virtual CouNumber selectBranch (const CouenneObject *obj,
				    const OsiBranchingInformation *info,
				    expression * &var,
				    double * &brpts,
				    double * &brDist, // distance of current LP
				    // point to new convexifications
				    int &way);

    /// compute \f$y^{lv}\f$ and \f$y^{uv}\f$ for Violation Transfer algorithm
    virtual void closestFeasible (expression *varind,
				  expression *vardep,
				  CouNumber &left,
				  CouNumber &right) const;
  };
}

#endif
