/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     drivers/taylor.h
 Revision: $Id$
 Contents: Easy to use drivers for the evaluation of higher order derivative
           tensors and inverse/impicit function differentiation

 Copyright (c) Andrea Walther, Andreas Griewank, Andreas Kowarz, Olaf Vogel

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file drivers/taylor.h
 * @brief Higher-order derivative tensors and implicit function differentiation
 *
 * Provides drivers for computing higher-order derivative tensors and
 * differentiating through implicit/inverse functions.
 *
 * @algorithm Higher-Order Taylor Propagation:
 * Computes arbitrary-order derivative tensors via univariate Taylor arithmetic.
 *
 * TENSOR COMPUTATION:
 * Given f: ℝⁿ → ℝᵐ and p seed directions S ∈ ℝⁿˣᵖ, compute the d-th order
 * derivative tensor containing all mixed partials up to order d:
 *
 * 1. Evaluate f along each direction: f(x + t·S[:,j]) as Taylor series
 * 2. Extract coefficients: [f]_k = (1/k!) · (d^k f/dt^k)|_{t=0}
 * 3. Combine to form symmetric tensor with C(p+d,d) entries per output
 *
 * INVERSE FUNCTION DIFFERENTIATION:
 * Given tape computing y = F(x), compute derivatives of x = F⁻¹(y):
 *
 * For implicit function G(x,y) = F(x) - y = 0:
 * - Jacobian: ∂x/∂y = -(∂G/∂x)⁻¹ · (∂G/∂y) = (∂F/∂x)⁻¹
 * - Higher orders: Propagate Taylor series through linear solve
 *
 * inverse_Taylor_prop(tag, n, d, Y, X):
 * Given Y[i][k] = (1/k!) · y^(k), computes X[i][k] = (1/k!) · x^(k)
 * where x(t) = F⁻¹(y(t)) as Taylor series in parameter t.
 *
 * @math Tensor dimensions:
 * For d-th order tensor with p directions:
 * - Number of entries: C(p+d, d) = (p+d)! / (p! · d!)
 * - Storage: tensor[m][C(p+d,d)] where m = number of outputs
 *
 * Multi-index notation: tensor[i][α] = (1/α!) · ∂^|α| f_i / ∂s^α
 * where α = (α₁,...,α_p) is multi-index with |α| = Σα_j ≤ d
 *
 * @complexity
 * - tensor_eval: O(C(p+d,d) · ops) where ops = tape operations
 * - inverse_tensor_eval: O(C(p+d,d) · n³) includes linear solves
 * - jac_solv: O(n³) for dense LU factorization
 *
 * @ref Griewank, Utke & Walther (2000). "Evaluating Higher Derivative
 *   Tensors by Forward Propagation of Univariate Taylor Series".
 *   Mathematics of Computation 69(231):1117-1130.
 *
 * @note These are advanced drivers for specialized applications
 *
 * @see drivers/drivers.h for standard gradient/Jacobian/Hessian
 * @see drivers/odedrivers.h for ODE-specific Taylor propagation
 */
#if !defined(ADOLC_DRIVERS_TAYLOR_H)
#define ADOLC_DRIVERS_TAYLOR_H 1

#include <adolc/adolcexport.h>
#include <adolc/internal/common.h>

BEGIN_C_DECLS

/****************************************************************************/
/*                                                       TENSOR EVALUATIONS */

/*--------------------------------------------------------------------------*/
/* tensor_eval(tag,m,n,d,p,x[n],tensor[m][dim],S[n][p])
      with dim = ((p+d) over d) */
ADOLC_API int tensor_eval(short tag, int m, int n, int d, int p, double *x,
                          double **tensor, double **S);

/*--------------------------------------------------------------------------*/
/* inverse_tensor_eval(tag,n,d,p,x,tensor[n][dim],S[n][p])
      with dim = ((p+d) over d) */
ADOLC_API int inverse_tensor_eval(short tag, int n, int d, int p, double *x,
                                  double **tensor, double **S);

/*--------------------------------------------------------------------------*/
/*  inverse_Taylor_prop(tag,n,d,Y[n][d+1],X[n][d+1]) */
ADOLC_API int inverse_Taylor_prop(short tag, int n, int d, double **Y,
                                  double **X);

/****************************************************************************/
/*                                                  ACCESS TO TENSOR VALUES */

/*--------------------------------------------------------------------------*/
/* tensor_value(d,m,y[m],tensori[m][dim],multi[d])
      with dim = ((p+d) over d) */
ADOLC_API void tensor_value(int d, int m, double *y, double **tensor,
                            int *multi);

/*--------------------------------------------------------------------------*/
/* void** tensorsetup(m,p,d,tensorig) */
ADOLC_API void **tensorsetup(int m, int p, int d, double **tensorig);

/*--------------------------------------------------------------------------*/
/* void freetensor(m,p,d,tensor) */
ADOLC_API void freetensor(int m, int p, int d, double **tensor);

/*--------------------------------------------------------------------------*/
/* int tensor_address(d, im[d]) */
ADOLC_API int tensor_address(int d, int *im);

/****************************************************************************/
/*                                                                    UTILS */

/*--------------------------------------------------------------------------*/
/* int binomi(a,b)  ---> binomial coefficient to compute tensor dimension */
ADOLC_API long binomi(int a, int b);

/*--------------------------------------------------------------------------*/
/* jac_solv(tag,n,x,b,mode) */
ADOLC_API int jac_solv(unsigned short tag, int n, const double *x, double *b,
                       unsigned short mode);

END_C_DECLS

/****************************************************************************/
#endif
