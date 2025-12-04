/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     drivers/drivers.h
 Revision: $Id$
 Contents: Easy to use drivers for optimization and nonlinear equations
           (with C and C++ callable interfaces including Fortran
            callable versions).

 Copyright (c) Andrea Walther, Andreas Griewank, Andreas Kowarz,
               Hristo Mitev, Sebastian Schlenkrich, Jean Utke, Olaf Vogel

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file drivers/drivers.h
 * @brief High-level driver functions for derivative computation
 *
 * Provides convenient functions for computing common derivative quantities:
 * - gradient(): First derivative of scalar function (∇f)
 * - jacobian(): First derivative of vector function (∂F/∂x)
 * - hessian(): Second derivative of scalar function (∇²f)
 * - hess_vec(): Hessian-vector product (∇²f · v)
 * - jac_vec(): Jacobian-vector product (J · v)
 * - vec_jac(): Vector-Jacobian product (u^T · J)
 *
 * These drivers wrap the lower-level forward/reverse interfaces and handle
 * memory allocation and mode selection automatically. All functions require
 * a pre-recorded tape (via trace_on/trace_off).
 *
 * @see interfaces.h for low-level forward/reverse mode calls
 * @see tape_interface.h for tape recording functions
 * @see drivers/taylor.h for higher-order Taylor coefficient drivers
 */
#if !defined(ADOLC_DRIVERS_DRIVERS_H)
#define ADOLC_DRIVERS_DRIVERS_H 1

#include <adolc/adolcexport.h>
#include <adolc/internal/common.h>

BEGIN_C_DECLS

/****************************************************************************/
/*                         DRIVERS FOR OPTIMIZATION AND NONLINEAR EQUATIONS */

/*--------------------------------------------------------------------------*/
/*                                                                 function */
/**
 * @brief Evaluate the taped function F: R^n -> R^m at point x
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables (outputs)
 * @param n Number of independent variables (inputs)
 * @param x Input point x[n]
 * @param y Output values y[m] = F(x)
 * @return 0 on success, non-zero on error
 *
 * @see gradient for computing first derivatives
 */
ADOLC_API int function(short, int, int, const double *, double *);
ADOLC_API fint function_(fint *, fint *, fint *, fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                                 gradient */
/**
 * @brief Compute the gradient of a scalar function f: R^n -> R
 *
 * Uses reverse mode AD for efficiency (single reverse sweep).
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param g Output gradient g[n] = ∇f(x)
 * @return 0 on success, non-zero on error
 *
 * @algorithm Reverse mode automatic differentiation
 * @complexity O(c·n) where c = cost of function evaluation (typically c ≈ 4-5)
 *
 * @see jacobian for vector-valued functions
 * @see hessian for second derivatives
 */
ADOLC_API int gradient(short, int, const double *, double *);
ADOLC_API fint gradient_(fint *, fint *, fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                                 jacobian */
/**
 * @brief Compute the Jacobian matrix of F: R^n -> R^m
 *
 * Computes J[i][j] = ∂F_i/∂x_j. Automatically selects forward or reverse
 * mode based on dimensions (forward if n < m, reverse otherwise).
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param J Output Jacobian J[m][n]
 * @return 0 on success, non-zero on error
 *
 * @complexity O(min(m,n) · c) where c = cost of function evaluation
 *
 * @see gradient for scalar functions (m=1)
 * @see vec_jac for vector-Jacobian products
 * @see jac_vec for Jacobian-vector products
 */
ADOLC_API int jacobian(short, int, int, const double *, double **);
ADOLC_API fint jacobian_(fint *, fint *, fint *, fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                           large_jacobian */
/**
 * @brief Compute Jacobian for large-scale problems using strip-mining
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables
 * @param n Number of independent variables
 * @param k Strip size (number of columns computed per forward sweep)
 * @param x Input point x[n]
 * @param y Output function values y[m] = F(x)
 * @param J Output Jacobian J[m][n]
 * @return 0 on success, non-zero on error
 *
 * @note Uses k parallel forward sweeps to reduce memory; k=n is standard jacobian
 */
ADOLC_API int large_jacobian(short, int, int, int, double *, double *,
                             double **);
ADOLC_API fint large_jacobian_(fint *, fint *, fint *, fint *, fdouble *,
                               fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                         vector_jacobian  */
/**
 * @brief Compute vector-Jacobian product v = u^T · J (reverse mode)
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables
 * @param n Number of independent variables
 * @param repeat If non-zero, reuse Taylor coefficients from previous call
 * @param x Input point x[n]
 * @param u Adjoint seed vector u[m]
 * @param v Output vector v[n] = u^T · J = Σ_i u_i · ∇F_i
 * @return 0 on success, non-zero on error
 *
 * @note When repeat=0, performs forward sweep first; when repeat=1, skips forward
 *
 * @see jac_vec for Jacobian-vector product (forward mode)
 */
ADOLC_API int vec_jac(short, int, int, int, const double *, const double *,
                      double *);
ADOLC_API fint vec_jac_(fint *, fint *, fint *, fint *, fdouble *,
                        const fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                          jacobian_vector */
/**
 * @brief Compute Jacobian-vector product u = J · v (forward mode)
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param v Tangent direction vector v[n]
 * @param u Output vector u[m] = J · v (directional derivative)
 * @return 0 on success, non-zero on error
 *
 * @see vec_jac for vector-Jacobian product (reverse mode)
 */
ADOLC_API int jac_vec(short, int, int, const double *, const double *,
                      double *);
ADOLC_API fint jac_vec_(fint *, fint *, fint *, fdouble *, fdouble *,
                        fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                                  hessian */
/**
 * @brief Compute the Hessian matrix of a scalar function f: R^n -> R
 *
 * Uses second-order reverse mode (computing Hessian-vector products with
 * coordinate vectors). Returns lower triangle only since Hessian is symmetric.
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param H Output Hessian H[n][n] (lower triangle filled)
 * @return 0 on success, non-zero on error
 *
 * @complexity O(n · c) where c = cost of gradient computation
 *
 * @see hessian2 for alternative using Hessian-matrix product
 * @see hess_vec for Hessian-vector product only
 */
ADOLC_API int hessian(short, int, const double *, double **);
ADOLC_API fint hessian_(fint *, fint *, fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                                 hessian2 */
/**
 * @brief Compute Hessian using Hessian-matrix product approach
 *
 * Alternative to hessian() that may be more efficient for certain cases.
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param H Output Hessian H[n][n] (lower triangle filled)
 * @return 0 on success, non-zero on error
 *
 * @see hessian for standard approach
 * @see hess_mat for multiple Hessian-vector products
 */
ADOLC_API int hessian2(short, int, double *, double **);
ADOLC_API fint hessian2_(fint *, fint *, fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                           hessian_vector */
/**
 * @brief Compute Hessian-vector product w = ∇²f · v
 *
 * Computes the product of the Hessian with a single direction vector.
 * Uses "forward-over-reverse" second-order mode.
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param v Direction vector v[n]
 * @param w Output vector w[n] = H · v = ∇²f(x) · v
 * @return 0 on success, non-zero on error
 *
 * @complexity O(c) where c = cost of gradient (typically 4-5x function cost)
 *
 * @see hess_mat for multiple directions
 * @see lagra_hess_vec for Lagrangian Hessian-vector product
 */
ADOLC_API int hess_vec(short, int, const double *, const double *, double *);
ADOLC_API fint hess_vec_(fint *, fint *, fdouble *, fdouble *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                           hessian_matrix */
/**
 * @brief Compute multiple Hessian-vector products W = ∇²f · V
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param q Number of direction vectors
 * @param x Input point x[n]
 * @param V Direction matrix V[n][q] (q column vectors)
 * @param W Output matrix W[n][q] where W[:,j] = H · V[:,j]
 * @return 0 on success, non-zero on error
 *
 * @see hess_vec for single direction
 */
ADOLC_API int hess_mat(short, int, int, const double *, const double *const *,
                       double **);
ADOLC_API fint hess_mat_(fint *, fint *, fint *, fdouble *, fdouble **,
                         fdouble **);

/*--------------------------------------------------------------------------*/
/*                                                  lagrange_hessian_vector */
/**
 * @brief Compute Lagrangian Hessian-vector product for constrained optimization
 *
 * Computes w = ∇²L · v where L(x) = Σ_i u_i · F_i(x) is the Lagrangian
 * with multipliers u. Essential for SQP and interior point methods.
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables (constraints)
 * @param n Number of independent variables
 * @param x Input point x[n]
 * @param v Direction vector v[n]
 * @param u Lagrange multipliers u[m]
 * @param w Output vector w[n] = ∇²(Σ u_i F_i) · v
 * @return 0 on success, non-zero on error
 *
 * @see hess_vec for single scalar function
 */
ADOLC_API int lagra_hess_vec(short, int, int, const double *, const double *,
                             const double *, double *);
ADOLC_API fint lagra_hess_vec_(fint *, fint *, fint *, fdouble *, fdouble *,
                               fdouble *, fdouble *);

END_C_DECLS

/****************************************************************************/
#endif
