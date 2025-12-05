// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpCholeskyWssmp.hpp
 * @brief WSSMP sparse direct solver interface for Cholesky factorization
 *
 * Wraps IBM's Watson Sparse Matrix Package (WSSMP) for Cholesky factorization
 * of normal equations in interior point methods.
 *
 * @algorithm Normal Equations Factorization:
 * For interior point, need to solve the system at each iteration.
 * This class factors the normal equations matrix M = A·D·A'.
 *
 * @math NORMAL EQUATIONS:
 * Given step direction system:  [D  A'] [Δx]   [r₁]
 *                               [A  0 ] [Δy] = [r₂]
 *
 * Eliminate Δx: (A·D⁻¹·A')·Δy = r₂ - A·D⁻¹·r₁
 *               M·Δy = rhs  where M = A·D⁻¹·A'
 *
 * Then: Δx = D⁻¹·(r₁ - A'·Δy)
 *
 * @algorithm WSSMP Features:
 * - Multifrontal sparse Cholesky: O(n^1.5 to n^2) for 2D/3D problems
 * - Shared memory parallelism (OpenMP)
 * - Dense column handling: columns with >threshold nonzeros
 *   treated as dense for cache efficiency
 * - Symbolic factorization reuse: factor pattern once, update numerics
 *
 * @complexity Symbolic: O(nnz²/n) typical for sparse
 * Numeric: O(nnz(L)·n_ops) where L is Cholesky factor
 * Solve: O(nnz(L)) triangular solves
 *
 * Requires WSSMP library to be installed and linked.
 *
 * @see ClpCholeskyBase for the abstract interface
 * @see ClpCholeskyWssmpKKT for KKT system variant
 * @see ClpInterior which uses this factorization
 */

#ifndef ClpCholeskyWssmp_H
#define ClpCholeskyWssmp_H

#include "ClpCholeskyBase.hpp"
class ClpMatrixBase;
class ClpCholeskyDense;

/** Wssmp class for Clp Cholesky factorization

*/
class CLPLIB_EXPORT ClpCholeskyWssmp : public ClpCholeskyBase {

public:
  /**@name Virtual methods that the derived classes provides  */
  //@{
  /** Orders rows and saves pointer to matrix.and model.
      Returns non-zero if not enough memory */
  virtual int order(ClpInterior *model);
  /** Does Symbolic factorization given permutation.
         This is called immediately after order.  If user provides this then
         user must provide factorize and solve.  Otherwise the default factorization is used
         returns non-zero if not enough memory */
  virtual int symbolic();
  /** Factorize - filling in rowsDropped and returning number dropped.
         If return code negative then out of memory */
  virtual int factorize(const double *diagonal, int *rowsDropped);
  /** Uses factorization to solve. */
  virtual void solve(double *region);
  //@}

  /**@name Constructors, destructor */
  //@{
  /** Constructor which has dense columns activated.
         Default is off. */
  ClpCholeskyWssmp(int denseThreshold = -1);
  /** Destructor  */
  virtual ~ClpCholeskyWssmp();
  // Copy
  ClpCholeskyWssmp(const ClpCholeskyWssmp &);
  // Assignment
  ClpCholeskyWssmp &operator=(const ClpCholeskyWssmp &);
  /// Clone
  virtual ClpCholeskyBase *clone() const;
  //@}

private:
  /**@name Data members */
  //@{
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
