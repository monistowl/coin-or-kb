// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpCholeskyUfl.hpp
 * @brief SuiteSparse CHOLMOD interface for Cholesky factorization
 *
 * Wraps the CHOLMOD library from SuiteSparse (University of Florida) for
 * Cholesky factorization of normal equations in interior point methods.
 *
 * @algorithm CHOLMOD Supernodal Sparse Cholesky:
 *   Hybrid supernodal/simplicial factorization A = LL':
 *   1. Ordering: Fill-reducing permutation via AMD, COLAMD, or METIS
 *   2. Symbolic: Analyze sparsity of L, allocate memory
 *   3. Numeric: Factor using supernodal method (large fronts) or
 *      simplicial (small problems) - automatically selected
 *   4. Solve: Forward L·z = b, backward L'·x = z
 *
 * @math Supernodal vs simplicial:
 *   Supernodal: Groups consecutive pivots with same sparsity pattern
 *   Uses dense BLAS-3 on column panels for cache efficiency
 *   Simplicial: Classical left-looking algorithm for small/sparse problems
 *   CHOLMOD auto-selects based on estimated flop count
 *
 * @complexity Supernodal: O(nnz(L)·f̄) where f̄ = average supernode size
 *   Typically 5-10x faster than simplicial for large problems
 *   Memory: O(nnz(L)) with efficient compressed storage
 *
 * @ref Davis & Hager (2009). "Dynamic Supernodes in Sparse Cholesky Update/
 *      Downdate and Triangular Solves". ACM TOMS 35:27.
 *
 * CHOLMOD provides:
 * - Supernodal and simplicial Cholesky modes
 * - Automatic fill-reducing ordering (AMD, METIS)
 * - Efficient memory management for sparse factors
 *
 * This is the most portable high-quality option across platforms.
 * Requires SuiteSparse/CHOLMOD library.
 *
 * @see ClpCholeskyBase for the abstract interface
 * @see ClpInterior which uses this factorization
 * @see http://www.cise.ufl.edu/research/sparse/cholmod
 */

#ifndef ClpCholeskyUfl_H
#define ClpCholeskyUfl_H

#include "ClpCholeskyBase.hpp"

class ClpMatrixBase;
class ClpCholeskyDense;

typedef struct cholmod_factor_struct cholmod_factor;
typedef struct cholmod_common_struct cholmod_common;

/** Ufl class for Clp Cholesky factorization

If  you wish to use AMD code from University of Florida see

    http://www.cise.ufl.edu/research/sparse/amd

for terms of use

If  you wish to use CHOLMOD code from University of Florida see

    http://www.cise.ufl.edu/research/sparse/cholmod

for terms of use

*/
class CLPLIB_EXPORT ClpCholeskyUfl : public ClpCholeskyBase {

public:
  /**@name Virtual methods that the derived classes provides  */
  //@{
  /** Orders rows and saves pointer to matrix.and model.
      Returns non-zero if not enough memory */
  virtual int order(ClpInterior *model);
  /** Does Symbolic factorization given permutation using CHOLMOD (if available).
         This is called immediately after order.  If user provides this then
         user must provide factorize and solve.  Otherwise the default factorization is used
         returns non-zero if not enough memory. */
  virtual int symbolic();
  /** Factorize - filling in rowsDropped and returning number dropped using CHOLMOD (if available).
         If return code negative then out of memory */
  virtual int factorize(const double *diagonal, int *rowsDropped);
  /** Uses factorization to solve. Uses CHOLMOD (if available). */
  virtual void solve(double *region);
  //@}

  /**@name Constructors, destructor */
  //@{
  /** Constructor which has dense columns activated.
         Default is off. */
  ClpCholeskyUfl(int denseThreshold = -1);
  /** Destructor  */
  virtual ~ClpCholeskyUfl();
  /// Clone
  virtual ClpCholeskyBase *clone() const;
  //@}

private:
  cholmod_factor *L_;
  cholmod_common *c_;

  // Copy
  ClpCholeskyUfl(const ClpCholeskyUfl &);
  // Assignment
  ClpCholeskyUfl &operator=(const ClpCholeskyUfl &);
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
