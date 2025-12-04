/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     drivers/odedrivers.h
 Revision: $Id$
 Contents: Easy to use drivers for ordinary differential equations (ODE)
           (with C and C++ callable interfaces including Fortran
            callable versions).

 Copyright (c) Andrea Walther, Andreas Griewank, Andreas Kowarz,
               Hristo Mitev, Sebastian Schlenkrich, Jean Utke, Olaf Vogel

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file drivers/odedrivers.h
 * @brief Taylor-based ODE integration drivers
 *
 * Provides drivers for solving and differentiating ODEs of the form
 * x' = f(x) using Taylor series expansion. The tape records f(x),
 * then these drivers compute higher-order Taylor coefficients.
 *
 * @algorithm Taylor Series ODE Integration:
 * Computes Taylor coefficients of ODE solution via automatic differentiation
 * of the right-hand side.
 *
 * PROBLEM: Given autonomous ODE x'(t) = f(x(t)) with initial condition x(0) = x₀,
 * compute Taylor expansion: x(t) = Σₖ x[k] · tᵏ
 *
 * METHOD (forode):
 * 1. Record tape of f(x) = x' mapping state to derivative
 * 2. Given x[0] = x₀, iteratively compute higher coefficients:
 *
 *    x[k+1] = (1/(k+1)) · f[k]
 *
 * where f[k] is the k-th Taylor coefficient of f(x(t)), computed by
 * propagating x[0..k] through the tape.
 *
 * RECURRENCE RELATION:
 * For x' = f(x): x[k+1] = (τ/(k+1)) · [f(x)]_k
 * where τ is a time scaling factor and [·]_k denotes k-th Taylor coefficient.
 *
 * The coefficients are computed via the composition rule:
 * [f(g)]_k = Σᵢ (∂f/∂xᵢ)[k] · [gᵢ]_k + lower order terms
 *
 * @math Taylor coefficient extraction:
 * For function y = f(x), the Taylor coefficient relationship:
 * y(t) = f(x(t)) where x(t) = Σₖ x[k] · tᵏ
 * yields y[k] = (1/k!) · (dᵏy/dtᵏ)|_{t=0}
 *
 * SENSITIVITY COMPUTATION (accode):
 * Given partial Jacobians A[i][j][k] = ∂x[k]_i/∂x[0]_j at each order,
 * accumulate total Jacobians B via the chain rule:
 *
 * B[i][j][k] = A[i][j][k] + Σₗ (∂x[k]_i/∂x[ℓ]) · B[ℓ][j][k-1]
 *
 * @complexity
 * - forode: O(d · ops) for d Taylor coefficients, ops = tape operations
 * - accode: O(d · n²) for n-dimensional state with d coefficients
 *
 * @ref Jorba & Zou (2005). "A Software Package for the Numerical Integration
 *   of ODEs by Means of High-Order Taylor Methods".
 * @ref Griewank & Walther (2008). "Evaluating Derivatives", Section 13.2.
 *
 * @param tau Time scaling factor (default 1.0)
 * @param dold Previous Taylor degree computed (default 0)
 * @param dnew New target Taylor degree
 *
 * @see interfaces.h for forward/reverse mode primitives
 * @see drivers/taylor.h for general tensor computation
 */
#if !defined(ADOLC_DRIVERS_ODEDRIVERS_H)
#define ADOLC_DRIVERS_ODEDRIVERS_H 1

#include <adolc/adolcexport.h>
#include <adolc/interfaces.h>
#include <adolc/internal/common.h>

BEGIN_C_DECLS

/****************************************************************************/
/*                                                         DRIVERS FOR ODEs */

/*--------------------------------------------------------------------------*/
/*                                                                  forodec */
/* forodec(tag, n, tau, dold, dnew, X[n][d+1])                              */
ADOLC_API int forodec(short, int, double, int, int, double **);
ADOLC_API fint forodec_(fint *, fint *, fdouble *, fint *, fint *, fdouble *);

/*--------------------------------------------------------------------------*/
/*                                                                  accodec */
/* accodec(n, tau, d, Z[n][n][d+1], B[n][n][d+1], nz[n][n])                 */
ADOLC_API void accodec(int, double, int, double ***, double ***, short **);
ADOLC_API fint accodec_(fint *, fdouble *, fint *, fdouble *, fdouble *);

END_C_DECLS

/****************************************************************************/
/****************************************************************************/
/*                                                       Now the C++ THINGS */
#if defined(__cplusplus)

/****************************************************************************/
/*                                       DRIVERS FOR ODEs, overloaded calls */

/*--------------------------------------------------------------------------*/
/*                                                                   forode */
/* forode(tag, n, tau, dold, dnew, X[n][d+1])                               */
ADOLC_API inline int forode(short tag,  // tape identifier
                            int n,      // space dimension
                            double tau, // scaling
                            int dold,   // previous degree defaults to zero
                            int dnew,   // New degree of consistency
                            double **X) // Taylor series
{
  return forodec(tag, n, tau, dold, dnew, X);
}

/*--------------------------------------------------------------------------*/
/*                                                                   forode */
/*        the scaling tau defaults to 1                                     */
/*                                                                          */
/*  forode(tag, n, dold, dnew, X[n][d+1])                                   */
ADOLC_API inline int forode(short tag, int n, int dold, int dnew, double **X) {
  return forodec(tag, n, 1.0, dold, dnew, X);
}

/*--------------------------------------------------------------------------*/
/*                                                                   forode */
/*        previous order defaults to 0                                      */
/*                                                                          */
/* forode(tag, n, tau, dnew, X[n][d+1])                                     */
ADOLC_API inline int forode(short tag, int n, double tau, int deg, double **X) {
  return forodec(tag, n, tau, 0, deg, X);
}

/*--------------------------------------------------------------------------*/
/*                                                                   forode */
/*        both tau and dold default                                         */
/*                                                                          */
/* forode(tag, n, dnew, X[n][d+1])                                          */
ADOLC_API inline int forode(short tag, int n, int deg, double **X) {
  return forode(tag, n, 1.0, 0, deg, X);
}

/*--------------------------------------------------------------------------*/
/*                                                                   accode */
/* accode(n, tau, d, Z[n][n][d+1], B[n][n][d+1], nz[n][n])                  */
ADOLC_API inline void
accode(int n,               // space dimension
       double tau,          // scaling defaults to 1.0
       int deg,             // highest degree
       double ***A,         // input tensor of "partial" Jacobians
       double ***B,         // output tensor of "total" Jacobians
       short **nonzero = 0) // optional sparsity characterization
{
  accodec(n, tau, deg, A, B, nonzero);
}

/*--------------------------------------------------------------------------*/
/*                                                                   accode */
/*       scaling defaults to 1                                              */
/*                                                                          */
/* accode(n, d, Z[n][n][d+1], B[n][n][d+1], nz[n][n])                       */
ADOLC_API inline void
accode(int n,               // space dimension
       int deg,             // highest degree
       double ***A,         // input tensor of "partial" Jacobians
       double ***B,         // output tensor of "total" Jacobians
       short **nonzero = 0) // optional sparsity characterization
{
  accodec(n, 1.0, deg, A, B, nonzero);
}

#endif

/****************************************************************************/
#endif
