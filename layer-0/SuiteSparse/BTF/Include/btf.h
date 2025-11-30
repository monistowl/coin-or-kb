/**
 * @file btf.h
 * @brief Block Triangular Form permutation for sparse matrices
 *
 * BTF computes permutations to transform a sparse matrix into block upper
 * triangular form (BTF). This decomposes the matrix into independent blocks
 * that can be processed separately, improving efficiency for factorization.
 *
 * Three main routines:
 * - btf_maxtrans: Maximum transversal (zero-free diagonal matching)
 * - btf_strongcomp: Strongly connected components (block decomposition)
 * - btf_order: Combined BTF ordering (calls both above)
 *
 * @algorithm Maximum Transversal (Duff's Algorithm MC21):
 *   Find a permutation Q such that A*Q has a zero-free diagonal.
 *   Uses depth-first search with augmenting paths to build maximum matching.
 *   1. Cheap matching: greedily match rows with unmatched columns
 *   2. Augmenting path search: find alternating paths to extend matching
 *
 * @algorithm Tarjan's Strongly Connected Components:
 *   Find permutation P such that P*A*P' is block upper triangular.
 *   1. Build directed graph: edge i→j if A(i,j) ≠ 0 and i ≠ j
 *   2. Find SCCs using depth-first search with low-link values
 *   3. Order SCCs in reverse topological order
 *
 * @math Structural rank: max # nonzeros achievable on diagonal = sprank(A)
 *   If sprank(A) < n, matrix is structurally singular.
 *   BTF form: P*A*Q = | B_11  B_12 ... | with square diagonal blocks B_ii
 *                     |  0   B_22 ... |
 *
 * @complexity Maximum transversal: O(nnz + n) time and O(n) space
 *   SCC decomposition: O(nnz + n) time (single DFS pass)
 *   Total BTF ordering: O(nnz + n) time and space
 *
 * @ref Duff (1981). "On Algorithms for Obtaining a Maximum Transversal".
 *      ACM Trans. Math. Software 7(3):315-330.
 * @ref Tarjan (1972). "Depth-first search and linear graph algorithms".
 *      SIAM J. Computing 1(2):146-160.
 *
 * @see klu.h for sparse LU factorization using BTF
 */

//------------------------------------------------------------------------------
// BTF/Include/btf.h: include file for BTF
//------------------------------------------------------------------------------

// BTF, Copyright (c) 2004-2024, University of Florida.  All Rights Reserved.
// Author: Timothy A. Davis.
// SPDX-License-Identifier: LGPL-2.1+

//------------------------------------------------------------------------------

/* BTF_MAXTRANS:  find a column permutation Q to give A*Q a zero-free diagonal
 * BTF_STRONGCOMP:  find a symmetric permutation P to put P*A*P' into block
 *      upper triangular form.
 * BTF_ORDER: do both of the above (btf_maxtrans then btf_strongcomp).
 */

/* ========================================================================== */
/* === BTF_MAXTRANS ========================================================= */
/* ========================================================================== */

/* BTF_MAXTRANS: finds a permutation of the columns of a matrix so that it has a
 * zero-free diagonal.  The input is an m-by-n sparse matrix in compressed
 * column form.  The array Ap of size n+1 gives the starting and ending
 * positions of the columns in the array Ai.  Ap[0] must be zero. The array Ai
 * contains the row indices of the nonzeros of the matrix A, and is of size
 * Ap[n].  The row indices of column j are located in Ai[Ap[j] ... Ap[j+1]-1].
 * Row indices must be in the range 0 to m-1.  Duplicate entries may be present
 * in any given column.  The input matrix  is not checked for validity (row
 * indices out of the range 0 to m-1 will lead to an undeterminate result -
 * possibly a core dump, for example).  Row indices in any given column need
 * not be in sorted order.  However, if they are sorted and the matrix already
 * has a zero-free diagonal, then the identity permutation is returned.
 *
 * The output of btf_maxtrans is an array Match of size n.  If row i is matched
 * with column j, then A(i,j) is nonzero, and then Match[i] = j.  If the matrix
 * is structurally nonsingular, all entries in the Match array are unique, and
 * Match can be viewed as a column permutation if A is square.  That is, column
 * k of the original matrix becomes column Match[k] of the permuted matrix.  In
 * MATLAB, this can be expressed as (for non-structurally singular matrices):
 *
 *      Match = maxtrans (A) ;
 *      B = A (:, Match) ;
 *
 * except of course here the A matrix and Match vector are all 0-based (rows
 * and columns in the range 0 to n-1), not 1-based (rows/cols in range 1 to n).
 * The MATLAB dmperm routine returns a row permutation.  See the maxtrans
 * mexFunction for more details.
 *
 * If row i is not matched to any column, then Match[i] is == -1.  The
 * btf_maxtrans routine returns the number of nonzeros on diagonal of the
 * permuted matrix.
 *
 * In the MATLAB mexFunction interface to btf_maxtrans, 1 is added to the Match
 * array to obtain a 1-based permutation.  Thus, in MATLAB where A is m-by-n:
 *
 *      q = maxtrans (A) ;      % has entries in the range 0:n
 *      q                       % a column permutation (only if sprank(A)==n)
 *      B = A (:, q) ;          % permuted matrix (only if sprank(A)==n)
 *      sum (q > 0) ;           % same as "sprank (A)"
 *
 * This behaviour differs from p = dmperm (A) in MATLAB, which returns the
 * matching as p(j)=i if row i and column j are matched, and p(j)=0 if column j
 * is unmatched.
 *
 *      p = dmperm (A) ;        % has entries in the range 0:m
 *      p                       % a row permutation (only if sprank(A)==m)
 *      B = A (p, :) ;          % permuted matrix (only if sprank(A)==m)
 *      sum (p > 0) ;           % definition of sprank (A)
 *
 * This algorithm is based on the paper "On Algorithms for obtaining a maximum
 * transversal" by Iain Duff, ACM Trans. Mathematical Software, vol 7, no. 1,
 * pp. 315-330, and "Algorithm 575: Permutations for a zero-free diagonal",
 * same issue, pp. 387-390.  Algorithm 575 is MC21A in the Harwell Subroutine
 * Library.  This code is not merely a translation of the Fortran code into C.
 * It is a completely new implementation of the basic underlying method (depth
 * first search over a subgraph with nodes corresponding to columns matched so
 * far, and cheap matching).  This code was written with minimal observation of
 * the MC21A/B code itself.  See comments below for a comparison between the
 * maxtrans and MC21A/B codes.
 *
 * This routine operates on a column-form matrix and produces a column
 * permutation.  MC21A uses a row-form matrix and produces a row permutation.
 * The difference is merely one of convention in the comments and interpretation
 * of the inputs and outputs.  If you want a row permutation, simply pass a
 * compressed-row sparse matrix to this routine and you will get a row
 * permutation (just like MC21A).  Similarly, you can pass a column-oriented
 * matrix to MC21A and it will happily return a column permutation.
 */

#ifndef _BTF_H
#define _BTF_H

#include "SuiteSparse_config.h"

/* make it easy for C++ programs to include BTF */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find maximum transversal (column permutation for zero-free diagonal)
 *
 * @algorithm Maximum transversal via depth-first search and cheap matching.
 *            Based on Duff's MC21 algorithm but completely reimplemented.
 *
 * Finds a column permutation Q such that A*Q has a zero-free diagonal
 * (if one exists). This is equivalent to finding a maximum matching in
 * the bipartite graph representation of A.
 *
 * @param nrow Number of rows in A
 * @param ncol Number of columns in A
 * @param Ap Column pointers array of size ncol+1
 * @param Ai Row indices array of size Ap[ncol]
 * @param maxwork Max work limit as multiple of nnz(A); <= 0 for no limit
 * @param work Output: actual work done, or -1 if limit reached
 * @param Match Output: Match[i]=j if row i matched with column j, -1 if unmatched
 * @param Work Workspace array of size 5*ncol
 * @return Number of columns matched (structural rank)
 *
 * @see btf_order() for combined BTF ordering
 */
int32_t btf_maxtrans
(
    int32_t nrow,
    int32_t ncol,
    int32_t Ap [ ],
    int32_t Ai [ ],
    double maxwork,
    double *work,
    int32_t Match [ ],
    int32_t Work [ ]
) ;

/** @brief Maximum transversal (64-bit version) @see btf_maxtrans() */
int64_t btf_l_maxtrans (int64_t, int64_t,
    int64_t *, int64_t *, double, double *,
    int64_t *, int64_t *) ;


/* ========================================================================== */
/* === BTF_STRONGCOMP ======================================================= */
/* ========================================================================== */

/* BTF_STRONGCOMP finds the strongly connected components of a graph, returning
 * a symmetric permutation.  The matrix A must be square, and is provided on
 * input in compressed-column form (see BTF_MAXTRANS, above).  The diagonal of
 * the input matrix A (or A*Q if Q is provided on input) is ignored.
 *
 * If Q is not NULL on input, then the strongly connected components of A*Q are
 * found.  Q may be flagged on input, where Q[k] < 0 denotes a flagged column k.
 * The permutation is j = BTF_UNFLIP (Q [k]).  On output, Q is modified (the
 * flags are preserved) so that P*A*Q is in block upper triangular form.
 *
 * If Q is NULL, then the permutation P is returned so that P*A*P' is in upper
 * block triangular form.
 *
 * The vector R gives the block boundaries, where block b is in rows/columns
 * R[b] to R[b+1]-1 of the permuted matrix, and where b ranges from 1 to the
 * number of strongly connected components found.
 */

/**
 * @brief Find strongly connected components for block triangular form
 *
 * @algorithm Tarjan's algorithm for strongly connected components.
 *
 * Finds a symmetric permutation P such that P*A*P' (or P*A*Q if Q provided)
 * is in block upper triangular form. Each diagonal block is a strongly
 * connected component.
 *
 * @param n Matrix dimension (A is n-by-n)
 * @param Ap Column pointers array of size n+1
 * @param Ai Row indices array of size Ap[n]
 * @param Q Optional input column permutation (may be NULL). Modified on output.
 * @param P Output: row/col permutation. P[k]=j means j is the k-th row/col.
 * @param R Output: block boundaries. Block b is rows/cols R[b] to R[b+1]-1.
 * @param Work Workspace array of size 4*n
 * @return Number of strongly connected components (blocks)
 *
 * @see btf_order() for combined BTF ordering
 */
int32_t btf_strongcomp
(
    int32_t n,
    int32_t Ap [ ],
    int32_t Ai [ ],
    int32_t Q [ ],
    int32_t P [ ],
    int32_t R [ ],
    int32_t Work [ ]
) ;

/** @brief Strongly connected components (64-bit version) @see btf_strongcomp() */
int64_t btf_l_strongcomp (int64_t, int64_t *,
    int64_t *, int64_t *, int64_t *,
    int64_t *, int64_t *) ;


/* ========================================================================== */
/* === BTF_ORDER ============================================================ */
/* ========================================================================== */

/* BTF_ORDER permutes a square matrix into upper block triangular form.  It
 * does this by first finding a maximum matching (or perhaps a limited matching
 * if the work is limited), via the btf_maxtrans function.  If a complete
 * matching is not found, BTF_ORDER completes the permutation, but flags the
 * columns of P*A*Q to denote which columns are not matched.  If the matrix is
 * structurally rank deficient, some of the entries on the diagonal of the
 * permuted matrix will be zero.  BTF_ORDER then calls btf_strongcomp to find
 * the strongly-connected components.
 *
 * On output, P and Q are the row and column permutations, where i = P[k] if
 * row i of A is the kth row of P*A*Q, and j = BTF_UNFLIP(Q[k]) if column j of
 * A is the kth column of P*A*Q.  If Q[k] < 0, then the (k,k)th entry in P*A*Q
 * is structurally zero.
 *
 * The vector R gives the block boundaries, where block b is in rows/columns
 * R[b] to R[b+1]-1 of the permuted matrix, and where b ranges from 1 to the
 * number of strongly connected components found.
 */

/**
 * @brief Compute complete BTF ordering (maximum transversal + SCC)
 *
 * Combines btf_maxtrans and btf_strongcomp to compute a complete block
 * triangular form. This is the main entry point for BTF.
 *
 * The output permutations P and Q satisfy: P*A*Q is in block upper
 * triangular form. If the matrix is structurally singular, Q[k] < 0
 * indicates that the (k,k) diagonal entry is structurally zero.
 *
 * @param n Matrix dimension (A is n-by-n)
 * @param Ap Column pointers array of size n+1
 * @param Ai Row indices array of size Ap[n]
 * @param maxwork Max work limit for maxtrans; <= 0 for no limit
 * @param work Output: work done in maxtrans, -1 if limit reached
 * @param P Output: row permutation of size n
 * @param Q Output: column permutation of size n (may be flagged negative)
 * @param R Output: block boundaries of size n+1
 * @param nmatch Output: number of nonzeros on diagonal of P*A*Q
 * @param Work Workspace array of size 5*n
 * @return Number of blocks in the BTF decomposition
 *
 * @see btf_maxtrans(), btf_strongcomp()
 */
int32_t btf_order
(
    int32_t n,
    int32_t Ap [ ],
    int32_t Ai [ ],
    double maxwork,
    double *work,
    int32_t P [ ],
    int32_t Q [ ],
    int32_t R [ ],
    int32_t *nmatch,
    int32_t Work [ ]
) ;

/** @brief Complete BTF ordering (64-bit version) @see btf_order() */
int64_t btf_l_order (int64_t, int64_t *, int64_t *, double , double *,
    int64_t *, int64_t *, int64_t *, int64_t *, int64_t *) ;

/**
 * @brief Get BTF library version numbers
 * @param version Output array filled with [major, minor, patch]
 */
void btf_version (int version [3]) ;

#ifdef __cplusplus
}
#endif


/* ========================================================================== */
/* === BTF marking of singular columns ====================================== */
/* ========================================================================== */

/* BTF_FLIP is a "negation about -1", and is used to mark an integer j
 * that is normally non-negative.  BTF_FLIP (-1) is -1.  BTF_FLIP of
 * a number > -1 is negative, and BTF_FLIP of a number < -1 is positive.
 * BTF_FLIP (BTF_FLIP (j)) = j for all integers j.  UNFLIP (j) acts
 * like an "absolute value" operation, and is always >= -1.  You can test
 * whether or not an integer j is "flipped" with the BTF_ISFLIPPED (j)
 * macro.
 */

#define BTF_FLIP(j) (-(j)-2)
#define BTF_ISFLIPPED(j) ((j) < -1)
#define BTF_UNFLIP(j) ((BTF_ISFLIPPED (j)) ? BTF_FLIP (j) : (j))

/* ========================================================================== */
/* === BTF version ========================================================== */
/* ========================================================================== */

/* All versions of BTF include these definitions.
 * As an example, to test if the version you are using is 1.2 or later:
 *
 *      if (BTF_VERSION >= BTF_VERSION_CODE (1,2)) ...
 *
 * This also works during compile-time:
 *
 *      #if (BTF_VERSION >= BTF_VERSION_CODE (1,2))
 *          printf ("This is version 1.2 or later\n") ;
 *      #else
 *          printf ("This is an early version\n") ;
 *      #endif
 */

#define BTF_DATE "July 25, 2025"
#define BTF_MAIN_VERSION   2
#define BTF_SUB_VERSION    3
#define BTF_SUBSUB_VERSION 3

#define BTF_VERSION_CODE(main,sub) SUITESPARSE_VER_CODE(main,sub)
#define BTF_VERSION BTF_VERSION_CODE(2,3)

#define BTF__VERSION SUITESPARSE__VERCODE(2,3,3)
#if !defined (SUITESPARSE__VERSION) || \
    (SUITESPARSE__VERSION < SUITESPARSE__VERCODE(7,11,0))
#error "BTF 2.3.3 requires SuiteSparse_config 7.11.0 or later"
#endif

#endif
