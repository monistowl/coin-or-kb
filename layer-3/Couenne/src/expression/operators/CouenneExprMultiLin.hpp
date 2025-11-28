/*
 *
 * Name:    CouenneExprMultilin.hpp
 * Author:  Pietro Belotti
 * Purpose: Multilinear terms
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprMultiLin.hpp
 * @brief Multilinear product w = x1 * x2 * ... * xn
 *
 * Product of n expressions. Generalizes bilinear (n=2) and trilinear (n=3)
 * to arbitrary number of factors.
 *
 * **Standardization approaches:**
 * 1. Recursive bilinear: w = ((x1*x2)*x3)*... using nested aux variables
 * 2. Trilinear grouping: group into triplets when n >= 3
 * 3. Direct multilinear relaxation (more complex cuts)
 *
 * **Convexification complexity:**
 * - Bilinear (n=2): 4 McCormick cuts
 * - Trilinear (n=3): 8 Meyer-Floudas cuts
 * - n-linear: 2^n cuts (exponential in n)
 *
 * For large n, recursive bilinear decomposition is preferred despite
 * introducing auxiliary variables.
 *
 * **Bound propagation:**
 * Product of intervals requires considering all 2^n corner combinations
 * to find the true bounds. Simplified by interval arithmetic.
 *
 * **Implied bounds (impliedBoundMul):**
 * From w = x1*x2*...*xn and bounds on w, derive bounds on factors.
 * More complex than bilinear case.
 *
 * **Branching:**
 * balancedMul() selects branching point to balance the relaxation
 * improvement across all factors.
 *
 * @see exprMul for bilinear terms (base class)
 * @see exprTrilinear for direct trilinear relaxation
 */
#ifndef COUENNE_EXPRMULTILIN_H
#define COUENNE_EXPRMULTILIN_H

#include <vector>

#include "CouenneExprOp.hpp"

namespace Couenne {

  /// another class for multiplications, \f$ \prod_{i=1}^n f_i(x) \f$

  class exprMultiLin: public exprMul {

  public:

    /// Constructor
    exprMultiLin (expression **, int);

    /// Constructor with two arguments
    exprMultiLin (expression *, expression *);

    /// return l-2 norm of gradient at given point
    CouNumber gradientNorm (const double *x);

    /// differentiation
    expression *differentiate (int index);

    /// simplification
    expression *simplify ();

    /// get a measure of "how linear" the expression is:
    virtual int Linearity ();

    /// Get lower and upper bound of an expression (if any)
    virtual void getBounds (expression *&, expression *&);

    /// Get value of lower and upper bound of an expression (if any)
    virtual void getBounds (CouNumber &lb, CouNumber &ub);

    /// reduce expression in standard form, creating additional aux
    /// variables (and constraints)
    virtual exprAux *standardize (CouenneProblem *p, bool addAux = true);

    /// generate equality between *this and *w
    void generateCuts (expression *w, //const OsiSolverInterface &si,
		       OsiCuts &cs, const CouenneCutGenerator *cg,
		       t_chg_bounds * = NULL, int = -1,
		       CouNumber = -COUENNE_INFINITY,
		       CouNumber =  COUENNE_INFINITY);

    /// code for comparison
    virtual enum expr_type code ()
    {return COU_EXPRMUL;}

    /// implied bound processing
    bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *, enum Couenne::expression::auxSign = Couenne::expression::AUX_EQ);

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
  protected:

    /// inferring bounds on factors of a product
    int impliedBoundMul (CouNumber wl,
			 CouNumber wu,
			 std::vector <CouNumber> &xl,
			 std::vector <CouNumber> &xu,
			 std::vector <std::pair <int, CouNumber> > &nl,
			 std::vector <std::pair <int, CouNumber> > &nu);

    /// balanced strategy for branching point selection in products
    CouNumber balancedMul (const OsiBranchingInformation *info, int index, int wind);

    /// can this expression be further linearized or are we on its
    /// concave ("bad") side
    virtual bool isCuttable (CouenneProblem *problem, int index) const
    {return false;} // concave on both sides, as for products
  };
}

#endif
