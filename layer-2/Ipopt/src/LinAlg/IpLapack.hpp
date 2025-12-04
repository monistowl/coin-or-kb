// Copyright (C) 2005, 2009 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter              IBM    2005-12-25

/**
 * @file IpLapack.hpp
 * @brief C++ wrappers for LAPACK (Linear Algebra PACKage) routines
 *
 * Provides platform-independent access to LAPACK for dense matrices.
 *
 * @algorithm Dense Matrix Factorization Methods:
 *   - Cholesky: A = L·L^T for symmetric positive definite (SPD)
 *   - LU: A = P·L·U with partial pivoting for general matrices
 *   - Symmetric indefinite: A = L·D·L^T with Bunch-Kaufman pivoting
 *
 * @math Cholesky factorization (Potrf/Potrs):
 *   For SPD matrix A, compute lower triangular L such that A = L·L^T.
 *   Solve: L·y = b (forward), L^T·x = y (backward).
 *   Used for normal equations in least squares.
 *
 * @math Eigenvalue decomposition (Syev):
 *   For symmetric A, compute A = V·Λ·V^T where Λ = diag(λ_1,...,λ_n).
 *   Returns eigenvalues in ascending order. Eigenvectors in columns of V.
 *
 * @complexity Cholesky: O(n³/3), LU: O(2n³/3), Eigenvalues: O(n³)
 *   Dense methods - use sparse solvers for large problems.
 *
 * @ref Anderson et al. (1999). "LAPACK Users' Guide". 3rd ed. SIAM.
 *
 * @see IpBlas.hpp for lower-level vector operations
 * @see Linear solver interfaces for sparse factorization
 */

#ifndef __IPLAPACK_HPP__
#define __IPLAPACK_HPP__

#include "IpUtils.hpp"
#include "IpException.hpp"

namespace Ipopt
{
DECLARE_STD_EXCEPTION(LAPACK_NOT_INCLUDED);

/** Wrapper for LAPACK subroutine XPOTRS.
 *
 *  Solving a linear system given a Cholesky factorization.
 *  We assume that the Cholesky factor is lower traiangular.
 *  @since 3.14.0
 */
IPOPTLIB_EXPORT void IpLapackPotrs(
   Index         ndim,
   Index         nrhs,
   const Number* a,
   Index         lda,
   Number*       b,
   Index         ldb
);

/** Wrapper for LAPACK subroutine DPOTRS.
 *
 *  Solving a linear system given a Cholesky factorization.
 *  We assume that the Cholesky factor is lower traiangular.
 *
 *  @deprecated Use IpLapackPotrs() instead.
 */
IPOPT_DEPRECATED
inline void IpLapackDpotrs(
   Index         ndim,
   Index         nrhs,
   const Number* a,
   Index         lda,
   Number*       b,
   Index         ldb
)
{
   IpLapackPotrs(ndim, nrhs, a, lda, b, ldb);
}

/** Wrapper for LAPACK subroutine XPOTRF.
 *
 *  Compute Cholesky factorization (lower triangular factor).
 *  info is the return value from the LAPACK routine.
 *  @since 3.14.0
 */
IPOPTLIB_EXPORT void IpLapackPotrf(
   Index   ndim,
   Number* a,
   Index   lda,
   Index&  info
);

/** Wrapper for LAPACK subroutine DPOTRF.
 *
 *  Compute Cholesky factorization (lower triangular factor).
 *  info is the return value from the LAPACK routine.
 *
 *  @deprecated Use IpLapackPotrf() instead.
 */
IPOPT_DEPRECATED
inline void IpLapackDpotrf(
   Index   ndim,
   Number* a,
   Index   lda,
   Index&  info
)
{
   IpLapackPotrf(ndim, a, lda, info);
}

/** Wrapper for LAPACK subroutine XSYEV.
 *
 *  Compute the Eigenvalue decomposition for a given matrix.
 *  If compute_eigenvectors is true, a will contain the eigenvectors
 *  in its columns on return.
 *  @since 3.14.0
 */
IPOPTLIB_EXPORT void IpLapackSyev(
   bool    compute_eigenvectors,
   Index   ndim,
   Number* a,
   Index   lda,
   Number* w,
   Index&  info
);

/** Wrapper for LAPACK subroutine DSYEV.
 *
 *  Compute the Eigenvalue decomposition for a given matrix.
 *  If compute_eigenvectors is true, a will contain the eigenvectors
 *  in its columns on return.
 *
 *  @deprecated Use IpLapackSyev() instead
 */
IPOPT_DEPRECATED
inline void IpLapackDsyev(
   bool    compute_eigenvectors,
   Index   ndim,
   Number* a,
   Index   lda,
   Number* w,
   Index&  info
)
{
   IpLapackSyev(compute_eigenvectors, ndim, a, lda, w, info);
}

/** Wrapper for LAPACK subroutine XGETRF.
 *
 *  Compute LU factorization.
 *  info is the return value from the LAPACK routine.
 *  @since 3.14.0
 */
IPOPTLIB_EXPORT void IpLapackGetrf(
   Index   ndim,
   Number* a,
   Index*  ipiv,
   Index   lda,
   Index&  info
);

/** Wrapper for LAPACK subroutine DGETRF.
 *
 *  Compute LU factorization.
 *  info is the return value from the LAPACK routine.
 *
 *  @deprecated Use IpLapackGetrf() instead.
 */
IPOPT_DEPRECATED
inline void IpLapackDgetrf(
   Index   ndim,
   Number* a,
   Index*  ipiv,
   Index   lda,
   Index&  info
)
{
   IpLapackGetrf(ndim, a, ipiv, lda, info);
}

/** Wrapper for LAPACK subroutine XGETRS.
 *
 * Solving a linear system given a LU factorization.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpLapackGetrs(
   Index         ndim,
   Index         nrhs,
   const Number* a,
   Index         lda,
   Index*        ipiv,
   Number*       b,
   Index         ldb
);

/** Wrapper for LAPACK subroutine DGETRS.
 *
 * Solving a linear system given a LU factorization.
 *
 * @deprecated Use IpLapackGetrs() instead.
 */
IPOPT_DEPRECATED
inline void IpLapackDgetrs(
   Index         ndim,
   Index         nrhs,
   const Number* a,
   Index         lda,
   Index*        ipiv,
   Number*       b,
   Index         ldb
)
{
   IpLapackGetrs(ndim, nrhs, a, lda, ipiv, b, ldb);
}

/** Wrapper for LAPACK subroutine XPPSV.
 *
 *  Solves a symmetric positive
 *  definite linear system in packed storage format (upper triangular).
 *  info is the return value from the LAPACK routine.
 *  @since 3.14.0
 */
IPOPTLIB_EXPORT void IpLapackPpsv(
   Index         ndim,
   Index         nrhs,
   const Number* a,
   Number*       b,
   Index         ldb,
   Index&        info
);

/** Wrapper for LAPACK subroutine DPPSV.
 *
 *  Solves a symmetric positive
 *  definite linear system in packed storage format (upper triangular).
 *  info is the return value from the LAPACK routine.
 *
 *  @deprecated Use IpLapackPpsv() instead.
 */
IPOPT_DEPRECATED
inline void IpLapackDppsv(
   Index         ndim,
   Index         nrhs,
   const Number* a,
   Number*       b,
   Index         ldb,
   Index&        info
)
{
   IpLapackPpsv(ndim, nrhs, a, b, ldb, info);
}

} // namespace Ipopt

#endif
