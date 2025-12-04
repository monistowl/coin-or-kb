// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpBlas.hpp
 * @brief C++ wrappers for BLAS (Basic Linear Algebra Subprograms)
 *
 * Provides platform-independent access to BLAS Level 1, 2, and 3 routines.
 *
 * @math BLAS Level 1 (vector-vector, O(n)):
 *   - Dot: x^T·y (inner product)
 *   - Nrm2: ||x||_2 = √(Σx_i²)
 *   - Asum: ||x||_1 = Σ|x_i|
 *   - Scal: x ← αx
 *   - Axpy: y ← αx + y
 *   - Copy: y ← x
 *   - Iamax: arg max_i |x_i|
 *
 * @math BLAS Level 2 (matrix-vector, O(n²)):
 *   - Gemv: y ← αAx + βy (or A^T)
 *   - Symv: y ← αAx + βy (A symmetric)
 *
 * @math BLAS Level 3 (matrix-matrix, O(n³)):
 *   - Gemm: C ← αA·B + βC
 *   - Syrk: C ← αA·A^T + βC (rank-k update)
 *   - Trsm: B ← α·L⁻¹·B (triangular solve)
 *
 * @complexity Level 1: O(n), Level 2: O(n²), Level 3: O(n³)
 *   All operations are cache-optimized in vendor BLAS libraries.
 *
 * @ref Lawson et al. (1979). "Basic Linear Algebra Subprograms for Fortran Usage".
 *      ACM TOMS 5(3):308-323.
 *
 * @see IpLapack.hpp for higher-level linear algebra (factorization, solve)
 */

#ifndef __IPBLAS_HPP__
#define __IPBLAS_HPP__

#include "IpUtils.hpp"

namespace Ipopt
{
/** Wrapper for BLAS function XDOT.
 *
 * Compute dot product of vector x and vector y.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT Number IpBlasDot(
   Index         size,
   const Number* x,
   Index         incX,
   const Number* y,
   Index         incY
);

/** Wrapper for BLAS function DDOT.
 *
 * Compute dot product of vector x and vector y.
 *
 * @deprecated Use IpBlasDot() instead.
 */
IPOPT_DEPRECATED
inline Number IpBlasDdot(
   Index         size,
   const Number* x,
   Index         incX,
   const Number* y,
   Index         incY
)
{
   return IpBlasDot(size, x, incX, y, incY);
}

/** Wrapper for BLAS function XNRM2.
 *
 * Compute 2-norm of vector x.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT Number IpBlasNrm2(
   Index         size,
   const Number* x,
   Index         incX
);

/** Wrapper for BLAS function DNRM2.
 *
 * Compute 2-norm of vector x.
 *
 * @deprecated Use IpBlasNrm2() instead.
 */
IPOPT_DEPRECATED
inline Number IpBlasDnrm2(
   Index         size,
   const Number* x,
   Index         incX
)
{
   return IpBlasNrm2(size, x, incX);
}

/** Wrapper for BLAS function XASUM.
 *
 * Compute 1-norm of vector x.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT Number IpBlasAsum(
   Index         size,
   const Number* x,
   Index         incX
);

/** Wrapper for BLAS function DASUM.
 *
 * Compute 1-norm of vector x.
 *
 * @deprecated Use IpBlasAsum() instead.
 */
IPOPT_DEPRECATED
inline Number IpBlasDasum(
   Index         size,
   const Number* x,
   Index         incX
)
{
   return IpBlasAsum(size, x, incX);
}

/** Wrapper for BLAS function IXAMAX.
 *
 * Compute index for largest absolute element of vector x.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT Index IpBlasIamax(
   Index         size,
   const Number* x,
   Index         incX
);

/** Wrapper for BLAS function IDAMAX.
 *
 * Compute index for largest absolute element of vector x.
 *
 * @deprecated Use IpBlasIamax() instead.
 */
IPOPT_DEPRECATED
inline int IpBlasIdamax(
   Index         size,
   const Number* x,
   Index         incX
)
{
   return (int)IpBlasIamax(size, x, incX);
}

/** Wrapper for BLAS subroutine XCOPY.
 *
 * Copying vector x into vector y.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasCopy(
   Index         size,
   const Number* x,
   Index         incX,
   Number*       y,
   Index         incY
);

/** Wrapper for BLAS subroutine DCOPY.
 *
 * Copying vector x into vector y.
 *
 * @deprecated Use IpBlasCopy() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDcopy(
   Index         size,
   const Number* x,
   Index         incX,
   Number*       y,
   Index         incY
)
{
   IpBlasCopy(size, x, incX, y, incY);
}

/** Wrapper for BLAS subroutine XAXPY.
 *
 * Adding the alpha multiple of vector x to vector y.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasAxpy(
   Index         size,
   Number        alpha,
   const Number* x,
   Index         incX,
   Number*       y,
   Index         incY
);

/** Wrapper for BLAS subroutine DAXPY.
 *
 * Adding the alpha multiple of vector x to vector y.
 *
 * @deprecated Use IpBlasAxpy() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDaxpy(
   Index         size,
   Number        alpha,
   const Number* x,
   Index         incX,
   Number*       y,
   Index         incY
)
{
   IpBlasAxpy(size, alpha, x, incX, y, incY);
}

/** Wrapper for BLAS subroutine XSCAL.
 *
 * Scaling vector x by scalar alpha.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasScal(
   Index   size,
   Number  alpha,
   Number* x,
   Index   incX
);

/** Wrapper for BLAS subroutine DSCAL.
 *
 * Scaling vector x by scalar alpha.
 *
 * @deprecated Use IpBlasScal() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDscal(
   Index   size,
   Number  alpha,
   Number* x,
   Index   incX
)
{
   IpBlasScal(size, alpha, x, incX);
}

/** Wrapper for BLAS subroutine XGEMV.
 *
 * Multiplying a matrix with a vector.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasGemv(
   bool          trans,
   Index         nRows,
   Index         nCols,
   Number        alpha,
   const Number* A,
   Index         ldA,
   const Number* x,
   Index         incX,
   Number        beta,
   Number*       y,
   Index         incY
);

/** Wrapper for BLAS subroutine DGEMV.
 *
 * Multiplying a matrix with a vector.
 *
 * @deprecated Use IpBlasGemv() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDgemv(
   bool          trans,
   Index         nRows,
   Index         nCols,
   Number        alpha,
   const Number* A,
   Index         ldA,
   const Number* x,
   Index         incX,
   Number        beta,
   Number*       y,
   Index         incY
)
{
   IpBlasGemv(trans, nRows, nCols, alpha, A, ldA, x, incX, beta, y, incY);
}

/** Wrapper for BLAS subroutine XSYMV.
 *
 * Multiplying a symmetric matrix with a vector.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasSymv(
   Index         n,
   Number        alpha,
   const Number* A,
   Index         ldA,
   const Number* x,
   Index         incX,
   Number        beta,
   Number*       y,
   Index         incY
);

/** Wrapper for BLAS subroutine DSYMV.
 *
 * Multiplying a symmetric matrix with a vector.
 *
 * @deprecated Use IpBlasSymv() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDsymv(
   Index         n,
   Number        alpha,
   const Number* A,
   Index         ldA,
   const Number* x,
   Index         incX,
   Number        beta,
   Number*       y,
   Index         incY
)
{
   IpBlasSymv(n, alpha, A, ldA, x, incX, beta, y, incY);
}

/** Wrapper for BLAS subroutine XGEMM.
 *
 * Multiplying two matrices.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasGemm(
   bool          transa,
   bool          transb,
   Index         m,
   Index         n,
   Index         k,
   Number        alpha,
   const Number* A,
   Index         ldA,
   const Number* B,
   Index         ldB,
   Number        beta,
   Number*       C,
   Index         ldC
);

/** Wrapper for BLAS subroutine DGEMM.
 *
 * Multiplying two matrices.
 *
 * @deprecated Use IpBlasGemm() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDgemm(
   bool          transa,
   bool          transb,
   Index         m,
   Index         n,
   Index         k,
   Number        alpha,
   const Number* A,
   Index         ldA,
   const Number* B,
   Index         ldB,
   Number        beta,
   Number*       C,
   Index         ldC
)
{
   IpBlasGemm(transa, transb, m, n, k, alpha, A, ldA, B, ldB, beta, C, ldC);
}

/** Wrapper for BLAS subroutine XSYRK.
 *
 * Adding a high-rank update to a matrix.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasSyrk(
   bool          trans,
   Index         ndim,
   Index         nrank,
   Number        alpha,
   const Number* A,
   Index         ldA,
   Number        beta,
   Number*       C,
   Index         ldC
);

/** Wrapper for BLAS subroutine DSYRK.
 *
 * Adding a high-rank update to a matrix.
 *
 * @deprecated Use IpBlasSyrk() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDsyrk(
   bool          trans,
   Index         ndim,
   Index         nrank,
   Number        alpha,
   const Number* A,
   Index         ldA,
   Number        beta,
   Number*       C,
   Index         ldC
)
{
   IpBlasSyrk(trans, ndim, nrank, alpha, A, ldA, beta, C, ldC);
}

/** Wrapper for BLAS subroutine XTRSM.
 *
 * Backsolve for a lower triangular matrix.
 * @since 3.14.0
 */
IPOPTLIB_EXPORT void IpBlasTrsm(
   bool          trans,
   Index         ndim,
   Index         nrhs,
   Number        alpha,
   const Number* A,
   Index         ldA,
   Number*       B,
   Index         ldB
);

/** Wrapper for BLAS subroutine DTRSM.
 *
 * Backsolve for a lower triangular matrix.
 *
 * @deprecated Use IpBlasTrsm() instead.
 */
IPOPT_DEPRECATED
inline void IpBlasDtrsm(
   bool          trans,
   Index         ndim,
   Index         nrhs,
   Number        alpha,
   const Number* A,
   Index         ldA,
   Number*       B,
   Index         ldB
)
{
   IpBlasTrsm(trans, ndim, nrhs, alpha, A, ldA, B, ldB);
}

} // namespace Ipopt

#endif
