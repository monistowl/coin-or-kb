/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     sparse/sparsedrivers.h
 Revision: $Id$
 Contents: This file contains some "Easy To Use" interfaces of the sparse
package.

 Copyright (c) Andrea Walther

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file sparse/sparsedrivers.h
 * @brief High-level drivers for sparse Jacobian and Hessian computation
 *
 * Provides efficient computation of sparse derivatives by exploiting
 * sparsity structure using graph coloring and compressed computation.
 *
 * @algorithm Sparse Derivative Computation via Graph Coloring:
 * Reduces the number of directional derivative evaluations by exploiting
 * sparsity structure:
 *
 * PHASE 1 - SPARSITY DETECTION (jac_pat, hess_pat):
 * Propagate bit-patterns through the tape to determine structural non-zeros:
 * - Initialize: each input gets unique bit (e.g., x_1 = 0001, x_2 = 0010)
 * - Propagate: output bits = OR of dependent input bits
 * - Result: J[i,j] ≠ 0 iff bit j is set in output i's pattern
 *
 * PHASE 2 - SEED MATRIX via GRAPH COLORING (generate_seed_jac/hess):
 * Construct seed matrix S such that J·S has recoverable columns:
 * - Build column intersection graph: edge (i,j) if columns i,j share a row
 * - Color graph: adjacent columns get different colors
 * - Seed matrix: S[:,c] = sum of unit vectors for columns with color c
 *
 * PHASE 3 - COMPRESSED EVALUATION (sparse_jac, sparse_hess):
 * Compute B = J·S using p directional derivative evaluations (p = #colors)
 * Recover J[i,j] = B[i, color(j)] since non-zero positions are known
 *
 * @math Complexity analysis:
 * Let nnz = number of non-zeros, p = chromatic number of intersection graph
 *
 * For Jacobian (m×n):
 * - Dense: O(min(m,n)) tape evaluations
 * - Sparse: O(p) tape evaluations where p ≤ max_row_degree + 1
 *
 * For Hessian (n×n, symmetric):
 * - Dense: O(n) tape evaluations
 * - Sparse: O(p) where p = chromatic number of adjacency graph
 * - Symmetry exploitation: use symmetric coloring (fewer colors needed)
 *
 * For banded/sparse structures (p = O(1)), cost is O(1) tape evaluations
 * regardless of matrix dimension! This is the key advantage.
 *
 * @complexity
 * - Sparsity detection: O(ops · n/wordsize) for n inputs, ops tape operations
 * - Graph coloring: O(nnz) greedy, optimal coloring is NP-hard
 * - Sparse evaluation: O(p · ops) where p = number of colors
 *
 * @ref Curtis, Powell & Reid (1974). "On the Estimation of Sparse Jacobian
 *   Matrices". J. Inst. Math. Appl. 13:117-119.
 * @ref Gebremedhin, Manne & Pothen (2005). "What Color Is Your Jacobian?
 *   Graph Coloring for Computing Derivatives". SIAM Review 47(4):629-705.
 *
 * @see drivers/drivers.h for dense derivative computation
 * @see sparse/sparse_fo_rev.h for bit-pattern forward/reverse modes
 */
#if !defined(ADOLC_SPARSE_SPARSE_H)
#define ADOLC_SPARSE_SPARSE_H 1

#include <adolc/adolcexport.h>
#include <adolc/internal/common.h>

BEGIN_C_DECLS

/****************************************************************************/

/*--------------------------------------------------------------------------*/
/*                                                         jacobian pattern */
/**
 * @brief Compute sparsity pattern of Jacobian matrix
 *
 * Uses bit-pattern propagation to determine structural non-zeros.
 * Result is stored in compressed row storage (CRS) format.
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables (rows)
 * @param n Number of independent variables (columns)
 * @param x Evaluation point x[n]
 * @param crs Output sparsity pattern crs[m][*], where crs[i][0] = count
 *            and crs[i][1..count] = column indices of non-zeros in row i
 * @param options Control options[3] for propagation mode
 * @return 0 on success
 *
 * @see generate_seed_jac for computing seed matrix from pattern
 * @see sparse_jac for computing values
 */
ADOLC_API int jac_pat(short, int, int, const double *, unsigned int **, int *);

/*--------------------------------------------------------------------------*/
/*                                              abs-normal jacobian pattern */
/* absnormal_jac_pat(tag, m, n, s, argument,                                */
/*         crs[] [ crs[][0] = non-zero independent blocks per row ])        */
/*                                                                          */
ADOLC_API int absnormal_jac_pat(short, int, int, int, const double *,
                                unsigned int **);
/*--------------------------------------------------------------------------*/
/*                                         seed matrix for sparse jacobian  */
/* generate_seed_jac(m, n, crs, &seed, &p, option);                         */

ADOLC_API void generate_seed_jac(int, int, unsigned int **, double ***, int *,
                                 int);

/*--------------------------------------------------------------------------*/
/*                                                         sparse jacobian  */
/**
 * @brief Compute sparse Jacobian matrix values
 *
 * Computes non-zero entries of the Jacobian using graph coloring to
 * minimize the number of directional derivative evaluations.
 *
 * @param tag Tape identifier
 * @param m Number of dependent variables
 * @param n Number of independent variables
 * @param repeat If non-zero, reuse sparsity pattern from previous call
 * @param x Evaluation point x[n]
 * @param nnz Output: number of non-zeros
 * @param row_ind Output: row indices (COO format)
 * @param col_ind Output: column indices (COO format)
 * @param values Output: non-zero values
 * @param options Control options[3]
 * @return 0 on success
 *
 * @note First call (repeat=0) computes pattern; subsequent calls can set repeat=1
 *
 * @see jac_pat for sparsity detection only
 * @see jacobian for dense Jacobian computation
 */
ADOLC_API int sparse_jac(short, int, int, int, const double *, int *,
                         unsigned int **, unsigned int **, double **, int *);

/*--------------------------------------------------------------------------*/
/*                                                          hessian pattern */
/**
 * @brief Compute sparsity pattern of Hessian matrix
 *
 * Uses reverse mode bit-pattern propagation to determine structural
 * non-zeros. Since Hessian is symmetric, only lower triangle is stored.
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param x Evaluation point x[n]
 * @param crs Output sparsity pattern crs[n][*], where crs[i][0] = count
 *            and crs[i][1..count] = column indices of non-zeros in row i
 * @param option Control option for propagation mode
 * @return 0 on success
 *
 * @see generate_seed_hess for computing seed matrix from pattern
 * @see sparse_hess for computing values
 */
ADOLC_API int hess_pat(short, int, const double *, unsigned int **, int);

/*--------------------------------------------------------------------------*/
/*                                          seed matrix for sparse hessian  */
/* generate_seed_hess(n, crs, &seed, &p, option);                           */

ADOLC_API void generate_seed_hess(int, unsigned int **, double ***, int *, int);

/*--------------------------------------------------------------------------*/
/*                                                          sparse hessian  */
/**
 * @brief Compute sparse Hessian matrix values
 *
 * Computes non-zero entries of the Hessian using symmetric graph coloring.
 * Exploits Hessian symmetry to reduce number of Hessian-vector products.
 *
 * @param tag Tape identifier (must have m=1 dependent variable)
 * @param n Number of independent variables
 * @param repeat If non-zero, reuse sparsity pattern from previous call
 * @param x Evaluation point x[n]
 * @param nnz Output: number of non-zeros (lower triangle only)
 * @param row_ind Output: row indices (COO format)
 * @param col_ind Output: column indices (COO format)
 * @param values Output: non-zero values
 * @param options Control options[2]
 * @return 0 on success
 *
 * @note First call (repeat=0) computes pattern; subsequent calls can set repeat=1
 *
 * @see hess_pat for sparsity detection only
 * @see hessian for dense Hessian computation
 */
ADOLC_API int sparse_hess(short, int, int, const double *, int *,
                          unsigned int **, unsigned int **, double **, int *);

ADOLC_API void set_HP(short tag, /* tape identification */
                      int indep, /* number of independent variables */
                      unsigned int **HP);

ADOLC_API void get_HP(short tag, /* tape identification */
                      int indep, /* number of independent variables */
                      unsigned int ***HP);

/*--------------------------------------------------------------------------*/
/*                                                   JACOBIAN BLOCK PATTERN */

/* Max. number of unsigned ints to store the seed / jacobian matrix strips.
   Reduce this value to x if your system happens to run out of memory.
   x < 10 makes no sense. x = 50 or 100 is better
   x stays for ( x * sizeof(size_t) * 8 )
   (block) variables at once                                            */

#define PQ_STRIPMINE_MAX 30

ADOLC_API int bit_vector_propagation(short, int, int, const double *,
                                     unsigned int **, int *);

/****************************************************************************/
END_C_DECLS

#endif
