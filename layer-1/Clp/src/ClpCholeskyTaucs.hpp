// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpCholeskyTaucs.hpp
 * @brief TAUCS sparse solver interface for Cholesky factorization
 *
 * Wraps Sivan Toledo's TAUCS library for Cholesky factorization of normal
 * equations in interior point methods.
 *
 * @algorithm TAUCS Left-Looking Supernodal Cholesky:
 *   Left-looking factorization with supernodal blocking:
 *   1. Ordering: AMD, METIS, or GENMMD fill-reducing permutation
 *   2. Symbolic: Build elimination tree, identify supernodes
 *   3. Numeric left-looking: For each supernode j:
 *      - Assemble: Gather column j from A and previous L updates
 *      - Factor: Dense Cholesky on diagonal block
 *      - Scatter: Distribute updates to later columns
 *   4. Store L in CCS format with supernode structure
 *
 * @math Left-looking vs right-looking:
 *   Left-looking: L_j computed from A_j and L_{<j} (memory efficient)
 *   Right-looking: Updates distributed immediately (more parallelism)
 *   TAUCS uses left-looking for lower memory footprint
 *
 * @complexity O(nnz(L)·f̄) where f̄ = average supernode front size
 *   Memory: O(nnz(L)) for factor storage
 *   Well-suited for medium-size interior point problems
 *
 * @ref Toledo (2003). "TAUCS: A Library of Sparse Linear Solvers".
 *      Tel-Aviv University. http://www.tau.ac.il/~stoledo/taucs/
 *
 * TAUCS provides:
 * - Left-looking supernodal factorization
 * - Multiple ordering methods (AMD, METIS, GENMMD)
 * - Research-quality implementation with educational focus
 *
 * Note: Requires modifications to taucs.h for C++ linkage and LAPACK
 * dpotf2.f for singularity handling (see class documentation).
 *
 * @see ClpCholeskyBase for the abstract interface
 * @see ClpInterior which uses this factorization
 * @see http://www.tau.ac.il/~stoledo/taucs/
 */

#ifndef ClpCholeskyTaucs_H
#define ClpCholeskyTaucs_H
#include "taucs.h"
#include "ClpCholeskyBase.hpp"
class ClpMatrixBase;

/** Taucs class for Clp Cholesky factorization

If  you wish to use Sivan Toledo's TAUCS code see

http://www.tau.ac.il/~stoledo/taucs/

for terms of use

The taucs.h file was modified to put

#ifdef __cplusplus
extern "C"{
#endif
               after line 440 (#endif) and
#ifdef __cplusplus
          }
#endif
               at end

I also modified LAPACK dpotf2.f (two places) to change the GO TO 30 on AJJ.Lt.0.0

to

            IF( AJJ.LE.1.0e-20 ) THEN
               AJJ = 1.0e100;
            ELSE
               AJJ = SQRT( AJJ )
            END IF

*/
class ClpCholeskyTaucs : public ClpCholeskyBase {

public:
  /**@name Virtual methods that the derived classes provides  */
  //@{
  /** Orders rows and saves pointer to matrix.and model.
      Returns non-zero if not enough memory */
  virtual int order(ClpInterior *model);
  /// Dummy
  virtual int symbolic();
  /** Factorize - filling in rowsDropped and returning number dropped.
         If return code negative then out of memory */
  virtual int factorize(const double *diagonal, int *rowsDropped);
  /** Uses factorization to solve. */
  virtual void solve(double *region);
  //@}

  /**@name Constructors, destructor */
  //@{
  /** Default constructor. */
  ClpCholeskyTaucs();
  /** Destructor  */
  virtual ~ClpCholeskyTaucs();
  // Copy
  ClpCholeskyTaucs(const ClpCholeskyTaucs &);
  // Assignment
  ClpCholeskyTaucs &operator=(const ClpCholeskyTaucs &);
  /// Clone
  virtual ClpCholeskyBase *clone() const;
  //@}

private:
  /**@name Data members */
  //@{
  /// Taucs matrix (== sparseFactor etc)
  taucs_ccs_matrix *matrix_;
  /// Taucs factor
  void *factorization_;
  /// sparseFactor.
  double *sparseFactorT_;
  /// choleskyStart
  CoinBigIndex *choleskyStartT_;
  /// choleskyRow
  int *choleskyRowT_;
  /// sizeFactor.
  CoinBigIndex sizeFactorT_;
  /// Row copy of matrix
  ClpMatrixBase *rowCopyT_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
