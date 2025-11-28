/*
 *
 * Name:    exprIf.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the exprIf class that implements the ifnl AMPL operator
 *
 * (C) Carnegie-Mellon University, 2007.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprIf.hpp
 * @brief Conditional (if-then-else) expression operator
 *
 * Implements the AMPL ifnl() operator:
 *   if (condition) then expr1 else expr2
 *
 * **Status:** This is a placeholder/stub class. Full implementation
 * would require handling disjunctive convexification.
 *
 * **Convexification challenge:**
 * Conditional expressions create disjunctive feasible regions.
 * Standard approach would use big-M formulations or disjunctive
 * programming techniques to handle the branching logic.
 *
 * **Usage in AMPL:**
 * Models with if-then-else create nonsmooth, potentially
 * discontinuous functions that are difficult to convexify.
 *
 * @see CouenneDisjCuts for disjunctive cut generation
 * @see exprOp base class
 */
#ifndef EXPRIF_HPP
#define EXPRIF_HPP

#include "CouenneExprOp.hpp"

namespace Couenne {

class COUENNELIB_EXPORT exprIf: public exprOp {

};

}

#endif
