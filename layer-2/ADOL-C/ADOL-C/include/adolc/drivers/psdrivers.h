/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     drivers/psdrivers.h
 Revision: $Id$
 Contents: Easy to use drivers for piecewise smooth functions
           (with C and C++ callable interfaces including Fortran
           callable versions).

 Copyright (c) Andrea Walther, Sabrina Fiege

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file drivers/psdrivers.h
 * @brief Drivers for piecewise smooth (PS) functions with abs-normal form
 *
 * Provides differentiation tools for functions containing absolute values
 * and other piecewise linear operations. These functions are not classically
 * differentiable at kink points, but have well-defined generalized derivatives.
 *
 * @algorithm Abs-Normal Form for Piecewise Smooth Functions:
 * Represents piecewise linear functions in a canonical form enabling
 * algorithmic computation of generalized derivatives.
 *
 * REPRESENTATION:
 * A function f: ℝⁿ → ℝᵐ containing s absolute value operations can be
 * written in abs-normal form:
 *
 *   z = cz + Z·x + L·|z|    (switching equation)
 *   y = cy + Y·x + J·z      (output equation)
 *
 * where:
 * - z ∈ ℝˢ are "switching variables" (arguments to |·|)
 * - cz ∈ ℝˢ, cy ∈ ℝᵐ are constant offsets
 * - Z ∈ ℝˢˣⁿ, Y ∈ ℝᵐˣⁿ are input Jacobians
 * - L ∈ ℝˢˣˢ is strictly lower triangular (coupling between switches)
 * - J ∈ ℝᵐˣˢ maps switching variables to outputs
 *
 * KEY PROPERTY: L being strictly lower triangular ensures the implicit
 * equation for z has a unique solution (can be solved by forward substitution).
 *
 * GENERALIZED DERIVATIVES:
 * At a kink (where some zᵢ = 0), classical derivative doesn't exist.
 * Instead, compute directional derivative along direction d:
 *
 *   σ = sign(Z·d + L·σ·|Z·d + L·σ|)  (signature equation)
 *   ∇_d f = Y + J·diag(σ)·(I - L·diag(σ))⁻¹·Z
 *
 * where σ ∈ {-1, 0, +1}ˢ encodes which branch of each |·| is active.
 *
 * @math Bouligand subdifferential:
 * The set of all limiting Jacobians as we approach a kink from different
 * directions forms the Bouligand subdifferential ∂_B f. For piecewise
 * linear f, this is a finite set with at most 2ˢ elements (one per sign
 * combination of the s switching variables).
 *
 * Clarke generalized gradient: conv(∂_B f) - convex hull
 *
 * @complexity
 * - abs_normal: O(ops) to extract form, where ops = tape operations
 * - directional_active_gradient: O(s²) for forward substitution
 * - Space: O(s²) for L matrix, O(s·n) for Z matrix
 *
 * @ref Griewank (2013). "On Stable Piecewise Linearization and Generalized
 *   Algorithmic Differentiation". Optimization Methods and Software.
 * @ref Griewank & Walther (2016). "First- and Second-Order Optimality
 *   Conditions for Piecewise Smooth Objective Functions".
 *
 * @see drivers/drivers.h for smooth function derivatives
 * @see interfaces.h for underlying forward/reverse modes
 */
#if !defined(ADOLC_DRIVERS_PSDRIVERS_H)
#define ADOLC_DRIVERS_PSDRIVERS_H 1

#include <adolc/adolcexport.h>
#include <adolc/interfaces.h>
#include <adolc/internal/common.h>

BEGIN_C_DECLS

/****************************************************************************/
/*                                                 DRIVERS FOR PS FUNCTIONS */

/*--------------------------------------------------------------------------*/
/*                                             directional_active_gradient_ */
/*                                                                          */
ADOLC_API fint directional_active_gradient_(fint, fint, double *, double *,
                                            double *, double **, short *);
/*--------------------------------------------------------------------------*/
/**
 * @brief Compute directional derivative for piecewise smooth functions
 *
 * Computes a generalized directional derivative at a point where the
 * function may have kinks (non-differentiable points). Returns both
 * the directional gradient and a signature indicating the active piece.
 *
 * @param tag Tape identifier
 * @param n Number of independent variables
 * @param x Evaluation point x[n]
 * @param d Direction vector d[n]
 * @param g Output directional active gradient g[n]
 * @param sigma_g Output signature indicating which piece is active
 * @return 0 on success
 *
 * @note The signature sigma_g encodes which branch of each abs() is taken
 */
ADOLC_API int
directional_active_gradient(short tag,     /* trace identifier */
                            int n,         /* number of independents */
                            double *x,     /* value of independents */
                            double *d,     /* direction */
                            double *g,     /* directional active gradient */
                            short *sigma_g /* sigma of g */
);

/*--------------------------------------------------------------------------*/
/**
 * @brief Extract abs-normal form of a piecewise linear function
 *
 * Computes the abs-normal representation at a base point, expressing
 * the function as:
 *   y = cy + Y*x + J*z
 *   z = cz + Z*x + L*|z|
 *
 * where s = swchk is the number of switching variables (abs operations).
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables (outputs)
 * @param n Number of independent variables (inputs)
 * @param swchk Number of switching variables s (abs operations in tape)
 * @param x Base point x[n] for linearization
 * @param y Output function value y[m] at base point
 * @param z Output switching variable values z[s]
 * @param cz Output constant vector cz[s] for z equation
 * @param cy Output constant vector cy[m] for y equation
 * @param Y Output Jacobian Y[m][n] of y w.r.t. x
 * @param J Output Jacobian J[m][s] of y w.r.t. z
 * @param Z Output Jacobian Z[s][n] of z (before abs) w.r.t. x
 * @param L Output lower triangular L[s][s] coupling between switching vars
 * @return 0 on success
 *
 * @note L is strictly lower triangular, ensuring unique solution for z
 */
ADOLC_API fint abs_normal_(fint *, fint *, fint *, fint *, fdouble *, fdouble *,
                           fdouble *, fdouble *, fdouble *, fdouble *,
                           fdouble *, fdouble *, fdouble *);
ADOLC_API int abs_normal(short tag,   /* tape identifier */
                         int m,       /* number od dependents   */
                         int n,       /* number of independents */
                         int swchk,   /* number of switches (check) */
                         double *x,   /* base point */
                         double *y,   /* function value */
                         double *z,   /* switching variables */
                         double *cz,  /* first constant */
                         double *cy,  /* second constant */
                         double **Y,  /* m times n */
                         double **J,  /* m times s */
                         double **Z,  /* s times n */
                         double **L); /* s times s (lowtri) */

END_C_DECLS

/****************************************************************************/

#endif
