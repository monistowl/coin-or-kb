/*
 *
 * Name:    exprPWLinear.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the exprPWLinear class implementing piecewise linear functions
 *
 * (C) Carnegie-Mellon University, 2007.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprPWLinear.hpp
 * @brief Piecewise linear function expression
 *
 * Represents piecewise linear (PWL) functions defined by breakpoints
 * and slopes or by point sequences.
 *
 * **Status:** This is a placeholder/stub class.
 *
 * **Mathematical form:**
 * f(x) = aᵢ * x + bᵢ  for  xᵢ ≤ x < xᵢ₊₁
 *
 * **Convexification:**
 * - If convex (slopes increasing): trivial envelope
 * - If concave (slopes decreasing): trivial envelope
 * - If neither: requires disjunctive handling
 *
 * **Standard MIP formulation:**
 * Uses binary variables to select active segment:
 * - λᵢ ∈ [0,1], Σλᵢ = 1, at most 2 adjacent λᵢ positive (SOS2)
 * - x = Σλᵢxᵢ, y = Σλᵢyᵢ
 *
 * **Usage:**
 * Common in approximating nonlinear functions or modeling
 * costs with quantity discounts.
 *
 * @see CouenneExprAbs for a simple PWL function (V-shape)
 * @see exprOp base class
 */
#ifndef EXPRPWLINEAR_HPP
#define EXPRPWLINEAR_HPP

#include "CouenneExprOp.hpp"

namespace Couenne {

class COUENNELIB_EXPORT exprPWLinear: public exprOp {

};

}

#endif
