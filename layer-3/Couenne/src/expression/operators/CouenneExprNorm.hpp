/*
 *
 * Name:    exprNorm.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the exprNorm class implementing $l_k$ norms
 *
 * (C) Carnegie-Mellon University, 2007.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprNorm.hpp
 * @brief p-norm expression: ||f(x)||_p
 *
 * Represents the ℓₚ norm: ||f(x)||_p = (Σᵢ |fᵢ(x)|^p)^(1/p)
 *
 * **Status:** This is a placeholder/stub class.
 *
 * **Special cases:**
 * - p = 1: Sum of absolute values (piecewise linear)
 * - p = 2: Euclidean norm (convex, smooth except at origin)
 * - p = ∞: Maximum absolute value (convex, nonsmooth)
 *
 * **Convexity:**
 * All ℓₚ norms with p ≥ 1 are convex functions.
 * This makes overestimation straightforward (tangent planes),
 * but underestimation requires handling the non-negativity
 * and norm structure.
 *
 * **Common usage:**
 * - Distance constraints: ||x - a||₂ ≤ r
 * - Regularization: minimize f(x) + λ||x||₁
 *
 * @see exprAbs for absolute value (used in p=1 norm)
 * @see exprOp base class
 */
#ifndef EXPRNORM_HPP
#define EXPRNORM_HPP

#include "CouenneExprOp.hpp"

namespace Couenne {

  /// Class for \f$ p \f$-norms, \f$ || f(x)||_p = \left(\sum_{i=1}^n f_i(x)^p\right)^{\frac{1}{p}} \f$

  class COUENNELIB_EXPORT exprNorm: public exprOp {

  };

}

#endif
