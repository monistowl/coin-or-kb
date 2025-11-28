/**
 * @file cs.h
 * @brief Concise Sparse matrix library - teaching implementation of sparse algorithms
 *
 * CSparse provides a minimal, readable implementation of core sparse matrix
 * operations. It serves as both a standalone library and educational reference
 * for sparse linear algebra algorithms.
 *
 * Key features:
 * - Sparse matrix in triplet or compressed-column (CSC) format
 * - Sparse Cholesky (cs_chol), LU (cs_lu), and QR (cs_qr) factorization
 * - Fill-reducing orderings via AMD
 * - Direct solvers: cs_cholsol, cs_lusol, cs_qrsol
 * - Dulmage-Mendelsohn decomposition (cs_dmperm)
 *
 * @ref Davis (2006). "Direct Methods for Sparse Linear Systems".
 *      SIAM. ISBN: 978-0-898716-13-9
 *
 * @see CXSparse for extended version with complex numbers
 * @see CHOLMOD, UMFPACK for production-quality implementations
 */

// CSparse/cs.h: include file for CSparse
// CSparse, Copyright (c) 2006-2023, Timothy A. Davis. All Rights Reserved.
// SPDX-License-Identifier: LGPL-2.1+
#ifndef _CS_H
#define _CS_H
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#define CS_VER 4  /* CSparse Version */
#define CS_SUBVER 3
#define CS_SUBSUB 2
#define CS_DATE "Mar 22, 2024"        /* CSparse release date */
#define CS_COPYRIGHT "Copyright (c) Timothy A. Davis, 2006-2023"

#ifndef csi
#define csi int64_t
#endif

/** @brief Get CSparse library version numbers */
void csparse_version (int version [3]) ;

/* --- primary CSparse routines and data structures ------------------------- */

/**
 * @brief Sparse matrix in compressed-column (CSC) or triplet (COO) format
 *
 * The interpretation depends on the nz field:
 * - nz == -1: Compressed-column (CSC) format
 *   - p[j] to p[j+1]-1 are indices into i[] and x[] for column j
 *   - p has size n+1, i and x have size p[n]
 * - nz >= 0: Triplet (COO) format
 *   - (i[k], p[k], x[k]) is the k-th entry (row, col, value)
 *   - nz is the number of entries
 *
 * @invariant In CSC format: p[0]==0 and p[j] <= p[j+1] for all j
 * @invariant Row indices may be unsorted within a column
 *
 * @see cs_compress() to convert triplet to CSC
 * @see CS_CSC(), CS_TRIPLET() macros to check format
 */
typedef struct cs_sparse
{
    csi nzmax ;     /**< @brief Maximum number of entries (allocated size) */
    csi m ;         /**< @brief Number of rows */
    csi n ;         /**< @brief Number of columns */
    csi *p ;        /**< @brief Column pointers (CSC) or column indices (triplet) */
    csi *i ;        /**< @brief Row indices, size nzmax */
    double *x ;     /**< @brief Numerical values, size nzmax (may be NULL for pattern) */
    csi nz ;        /**< @brief # entries in triplet form, or -1 for CSC format */
} cs ;

/** @brief Compute C = alpha*A + beta*B (sparse matrix addition) */
cs *cs_add (const cs *A, const cs *B, double alpha, double beta) ;

/** @brief Solve Ax=b using sparse Cholesky (A must be SPD) @param order 0=natural, 1=AMD */
csi cs_cholsol (csi order, const cs *A, double *b) ;

/** @brief Convert triplet matrix T to compressed-column (CSC) format */
cs *cs_compress (const cs *T) ;

/** @brief Remove duplicate entries from a sparse matrix (summing values) */
csi cs_dupl (cs *A) ;

/** @brief Add entry to triplet matrix: T(i,j) = x */
csi cs_entry (cs *T, csi i, csi j, double x) ;

/** @brief Compute y = y + A*x (sparse matrix-vector multiply) */
csi cs_gaxpy (const cs *A, const double *x, double *y) ;

/** @brief Load sparse matrix from file in triplet format */
cs *cs_load (FILE *f) ;

/** @brief Solve Ax=b using sparse LU @param order ordering, @param tol pivot tolerance */
csi cs_lusol (csi order, const cs *A, double *b, double tol) ;

/** @brief Compute C = A*B (sparse matrix multiplication) */
cs *cs_multiply (const cs *A, const cs *B) ;

/** @brief Compute 1-norm of sparse matrix A */
double cs_norm (const cs *A) ;

/** @brief Print sparse matrix (brief=1 for summary only) */
csi cs_print (const cs *A, csi brief) ;

/** @brief Solve min||Ax-b||_2 using sparse QR @param order 0=natural, 1-3=AMD variants */
csi cs_qrsol (csi order, const cs *A, double *b) ;

/** @brief Compute A' (transpose). @param values 1=copy values, 0=pattern only */
cs *cs_transpose (const cs *A, csi values) ;
/* utilities */
void *cs_calloc (csi n, size_t size) ;
void *cs_free (void *p) ;
void *cs_realloc (void *p, csi n, size_t size, csi *ok) ;
cs *cs_spalloc (csi m, csi n, csi nzmax, csi values, csi triplet) ;
cs *cs_spfree (cs *A) ;
csi cs_sprealloc (cs *A, csi nzmax) ;
void *cs_malloc (csi n, size_t size) ;

/* --- secondary CSparse routines and data structures ----------------------- */

/**
 * @brief Symbolic analysis result for Cholesky, LU, or QR factorization
 *
 * Contains the fill-reducing permutation, elimination tree, and storage
 * estimates computed during symbolic analysis (before numerical factorization).
 *
 * @see cs_schol() for symbolic Cholesky analysis
 * @see cs_sqr() for symbolic QR analysis
 */
typedef struct cs_symbolic
{
    csi *pinv ;     /**< @brief Inverse row perm (QR) or fill-reducing perm (Cholesky) */
    csi *q ;        /**< @brief Fill-reducing column permutation for LU and QR */
    csi *parent ;   /**< @brief Elimination tree for Cholesky and QR */
    csi *cp ;       /**< @brief Column pointers for L (Cholesky) or row counts (QR) */
    csi *leftmost ; /**< @brief leftmost[i] = min column in row i, for QR */
    csi m2 ;        /**< @brief # rows for QR after adding fictitious rows */
    double lnz ;    /**< @brief Estimated # entries in L (Cholesky/LU) or V (QR) */
    double unz ;    /**< @brief Estimated # entries in U (LU) or R (QR) */
} css ;

/**
 * @brief Numeric factorization result for Cholesky, LU, or QR
 *
 * Contains the actual sparse factor matrices computed by numerical
 * factorization routines.
 *
 * @see cs_chol() for numeric Cholesky
 * @see cs_lu() for numeric LU
 * @see cs_qr() for numeric QR
 */
typedef struct cs_numeric
{
    cs *L ;         /**< @brief L factor (LU, Cholesky) or V (Householder vectors for QR) */
    cs *U ;         /**< @brief U factor (LU) or R (QR). Unused for Cholesky. */
    csi *pinv ;     /**< @brief Partial pivoting permutation for LU */
    double *B ;     /**< @brief Householder coefficients beta[0..n-1] for QR */
} csn ;

/**
 * @brief Dulmage-Mendelsohn decomposition or strongly connected components
 *
 * @algorithm Dulmage-Mendelsohn permutation finds a block triangular form
 *            that reveals the structural properties of a sparse matrix.
 *
 * @see cs_dmperm() for computing this decomposition
 * @see cs_scc() for strongly connected components
 */
typedef struct cs_dmperm_results
{
    csi *p ;        /**< @brief Row permutation, size m */
    csi *q ;        /**< @brief Column permutation, size n */
    csi *r ;        /**< @brief Row block boundaries, size nb+1 */
    csi *s ;        /**< @brief Column block boundaries, size nb+1 */
    csi nb ;        /**< @brief Number of blocks in fine decomposition */
    csi rr [5] ;    /**< @brief Coarse row decomposition boundaries */
    csi cc [5] ;    /**< @brief Coarse column decomposition boundaries */
} csd ;

csi *cs_amd (csi order, const cs *A) ;
csn *cs_chol (const cs *A, const css *S) ;
csd *cs_dmperm (const cs *A, csi seed) ;
csi cs_droptol (cs *A, double tol) ;
csi cs_dropzeros (cs *A) ;
csi cs_happly (const cs *V, csi i, double beta, double *x) ;
csi cs_ipvec (const csi *p, const double *b, double *x, csi n) ;
csi cs_lsolve (const cs *L, double *x) ;
csi cs_ltsolve (const cs *L, double *x) ;
csn *cs_lu (const cs *A, const css *S, double tol) ;
cs *cs_permute (const cs *A, const csi *pinv, const csi *q, csi values) ;
csi *cs_pinv (const csi *p, csi n) ;
csi cs_pvec (const csi *p, const double *b, double *x, csi n) ;
csn *cs_qr (const cs *A, const css *S) ;
css *cs_schol (csi order, const cs *A) ;
css *cs_sqr (csi order, const cs *A, csi qr) ;
cs *cs_symperm (const cs *A, const csi *pinv, csi values) ;
csi cs_updown (cs *L, csi sigma, const cs *C, const csi *parent) ;
csi cs_usolve (const cs *U, double *x) ;
csi cs_utsolve (const cs *U, double *x) ;
/* utilities */
css *cs_sfree (css *S) ;
csn *cs_nfree (csn *N) ;
csd *cs_dfree (csd *D) ;

/* --- tertiary CSparse routines -------------------------------------------- */
csi *cs_counts (const cs *A, const csi *parent, const csi *post, csi ata) ;
double cs_cumsum (csi *p, csi *c, csi n) ;
csi cs_dfs (csi j, cs *G, csi top, csi *xi, csi *pstack, const csi *pinv) ;
csi cs_ereach (const cs *A, csi k, const csi *parent, csi *s, csi *w) ;
csi *cs_etree (const cs *A, csi ata) ;
csi cs_fkeep (cs *A, csi (*fkeep) (csi, csi, double, void *), void *other) ;
double cs_house (double *x, double *beta, csi n) ;
csi cs_leaf (csi i, csi j, const csi *first, csi *maxfirst, csi *prevleaf,
    csi *ancestor, csi *jleaf) ;
csi *cs_maxtrans (const cs *A, csi seed) ;
csi *cs_post (const csi *parent, csi n) ;
csi *cs_randperm (csi n, csi seed) ;
csi cs_reach (cs *G, const cs *B, csi k, csi *xi, const csi *pinv) ;
csi cs_scatter (const cs *A, csi j, double beta, csi *w, double *x, csi mark,
    cs *C, csi nz) ;
csd *cs_scc (cs *A) ;
csi cs_spsolve (cs *G, const cs *B, csi k, csi *xi, double *x,
    const csi *pinv, csi lo) ;
csi cs_tdfs (csi j, csi k, csi *head, const csi *next, csi *post,
    csi *stack) ;
/* utilities */
csd *cs_dalloc (csi m, csi n) ;
csd *cs_ddone (csd *D, cs *C, void *w, csi ok) ;
cs *cs_done (cs *C, void *w, void *x, csi ok) ;
csi *cs_idone (csi *p, cs *C, void *w, csi ok) ;
csn *cs_ndone (csn *N, cs *C, void *w, void *x, csi ok) ;

#define CS_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define CS_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define CS_FLIP(i) (-(i)-2)
#define CS_UNFLIP(i) (((i) < 0) ? CS_FLIP(i) : (i))
#define CS_MARKED(w,j) (w [j] < 0)
#define CS_MARK(w,j) { w [j] = CS_FLIP (w [j]) ; }
#define CS_CSC(A) (A && (A->nz == -1))
#define CS_TRIPLET(A) (A && (A->nz >= 0))
#endif
