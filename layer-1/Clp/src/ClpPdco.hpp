// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpPdco.hpp
 * @brief PDCO (Primal-Dual interior point for Convex Objectives) algorithm
 * @author John Tomlin
 *
 * Implements the PDCO algorithm for convex optimization problems, an
 * alternative to Mehrotra's predictor-corrector method.
 *
 * @algorithm PDCO - Primal-Dual Interior Point for Convex Objectives:
 * Solves separable convex programs using iterative linear algebra.
 *
 * @math PROBLEM FORMULATION:
 *   minimize    φ(x) + (1/2)||D₁x||² + c'x
 *   subject to  Ax = b
 *               l ≤ x ≤ u
 *
 * where φ(x) = Σᵢ φᵢ(xᵢ) is separable convex (diagonal Hessian).
 * Regularization terms ||D₁x||², ||D₂y||² make system nonsingular.
 *
 * @algorithm Augmented System Formulation:
 * Instead of normal equations (A·D²·A')Δy = rhs, PDCO solves:
 *
 *   | -D²  A' | | Δx |   | r₁ |
 *   |  A   δI | | Δy | = | r₂ |
 *
 * where D² = diag(H(x) + d₁²) with H(x) = diagonal Hessian of φ.
 * The δI term (d₂²·I) regularizes the (2,2) block.
 *
 * @algorithm LSQR Iterative Solver:
 * For large sparse problems, direct Cholesky may be expensive.
 * PDCO uses LSQR (iterative least squares) to solve the augmented system:
 *   - Handles ill-conditioned matrices better than Cholesky
 *   - Convergence controlled by tolerance and iteration limits
 *   - Preconditioned by diagonal scaling
 *
 * @math Matrix-Vector Products:
 *   mode=1: y = y + A·x   (multiply by A)
 *   mode=2: x = x + A'·y  (multiply by A transpose)
 *
 * @algorithm Preconditioning:
 * Diagonal preconditioner improves LSQR convergence:
 *   M = diag(A·D²·A' + d₂²I)^{-1/2}
 *
 * @complexity LSQR per iteration: O(nnz(A)) for sparse A.
 *   Number of LSQR iterations depends on condition number.
 *   Total: O(IPM_iters × LSQR_iters × nnz(A))
 *
 * Advantages over Mehrotra predictor-corrector:
 * - Better for ill-conditioned normal equations
 * - Handles dense columns without fill-in
 * - Natural for separable convex objectives
 *
 * This is a mix-in class - ClpInterior objects are cast to this type at
 * algorithm time. No additional data is stored.
 *
 * @ref Saunders (2003). "PDCO: A primal-dual interior method for convex
 *   objectives". http://stanford.edu/group/SOL/software/pdco/
 *
 * @see ClpPdcoBase for user-customizable objective/Hessian
 * @see ClpLsqr for the iterative linear solver
 * @see ClpPredictorCorrector for the alternative direct method
 */

#ifndef ClpPdco_H
#define ClpPdco_H

#include "ClpInterior.hpp"

/** This solves problems in Primal Dual Convex Optimization

    It inherits from ClpInterior.  It has no data of its own and
    is never created - only cast from a ClpInterior object at algorithm time.

*/
class ClpPdco : public ClpInterior {

public:
  /**@name Description of algorithm */
  //@{
  /** Pdco algorithm

         Method


     */

  int pdco();
  // ** Temporary version
  int pdco(ClpPdcoBase *stuff, Options &options, Info &info, Outfo &outfo);

  //@}

  /**@name Functions used in pdco */
  //@{
  /// LSQR
  void lsqr();

  void matVecMult(int, double *, double *);

  void matVecMult(int, CoinDenseVector< double > &, double *);

  void matVecMult(int, CoinDenseVector< double > &, CoinDenseVector< double > &);

  void matVecMult(int, CoinDenseVector< double > *, CoinDenseVector< double > *);

  void getBoundTypes(int *, int *, int *, int **);

  void getGrad(CoinDenseVector< double > &x, CoinDenseVector< double > &grad);

  void getHessian(CoinDenseVector< double > &x, CoinDenseVector< double > &H);

  double getObj(CoinDenseVector< double > &x);

  void matPrecon(double, double *, double *);

  void matPrecon(double, CoinDenseVector< double > &, double *);

  void matPrecon(double, CoinDenseVector< double > &, CoinDenseVector< double > &);

  void matPrecon(double, CoinDenseVector< double > *, CoinDenseVector< double > *);
  //@}
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
