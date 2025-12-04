// Copyright (C) 2009, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpCholeskyMumps.hpp
 * @brief MUMPS sparse direct solver interface for Cholesky factorization
 *
 * Wraps the MUMPS (MUltifrontal Massively Parallel sparse direct Solver)
 * library for Cholesky factorization of normal equations in interior point.
 *
 * @algorithm MUMPS Multifrontal Sparse Cholesky:
 *   Parallel sparse direct factorization A = LL':
 *   1. Analyze phase: Fill-reducing ordering (AMD/METIS/SCOTCH)
 *   2. Build elimination tree and allocate frontal matrices
 *   3. Factor via multifrontal method:
 *      - Assemble contributions into frontal matrix F_k
 *      - Factor dense block: F_k = L_k · L_k'
 *      - Form update matrix (Schur complement) for parent
 *   4. Solve via forward/backward substitution through tree
 *
 * @math Multifrontal factorization:
 *   Elimination tree defines partial ordering of pivots.
 *   Frontal matrix F_k contains all fill-in for subtree rooted at k.
 *   Dense BLAS-3 operations on fronts for efficiency.
 *
 * @complexity O(n·f²) where f = max frontal matrix size.
 *   Parallel: O(n·f²/p) with p MPI processes.
 *   Memory: O(n·f) for frontal storage.
 *
 * @ref Amestoy et al. (2001). "A Fully Asynchronous Multifrontal Solver Using
 *      Distributed Dynamic Scheduling". SIAM J. Matrix Anal. Appl. 23:15-41.
 *
 * MUMPS provides:
 * - Multifrontal factorization with supernodes
 * - Distributed memory parallelism (MPI)
 * - Dense column handling for improved performance
 *
 * Requires MUMPS library to be installed and linked. The DMUMPS_STRUC_C
 * structure is forward-declared as void for compilation without MUMPS headers.
 *
 * @see ClpCholeskyBase for the abstract interface
 * @see ClpInterior which uses this factorization
 * @see http://mumps.enseeiht.fr/ for MUMPS documentation
 */

#ifndef ClpCholeskyMumps_H
#define ClpCholeskyMumps_H
#include "ClpCholeskyBase.hpp"
class ClpMatrixBase;
class ClpCholeskyDense;

// unfortunately, DMUMPS_STRUC_C is an anonymous struct in MUMPS, so we define it to void for everyone outside ClpCholeskyMumps
// if this file is included by ClpCholeskyMumps.cpp, then after dmumps_c.h has been included, which defines MUMPS_VERSION
#ifndef MUMPS_VERSION
typedef void DMUMPS_STRUC_C;
#endif

/** Mumps class for Clp Cholesky factorization

*/
class CLPLIB_EXPORT ClpCholeskyMumps : public ClpCholeskyBase {

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
  ClpCholeskyMumps(int denseThreshold = -1, int logLevel = 0);
  /** Destructor  */
  virtual ~ClpCholeskyMumps();
  /// Clone
  virtual ClpCholeskyBase *clone() const;
  //@}

private:
  // Mumps structure
  DMUMPS_STRUC_C *mumps_;

  // Copy
  ClpCholeskyMumps(const ClpCholeskyMumps &);
  // Assignment
  ClpCholeskyMumps &operator=(const ClpCholeskyMumps &);
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
