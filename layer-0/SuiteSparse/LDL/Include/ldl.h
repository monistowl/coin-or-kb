/**
 * @file ldl.h
 * @brief Simple sparse LDL' factorization for symmetric matrices
 *
 * LDL computes a sparse LDL' factorization of a symmetric matrix A:
 *   A = L * D * L'
 * where L is unit lower triangular and D is diagonal. This factorization
 * works for symmetric indefinite matrices (D may have negative entries).
 *
 * The factorization is performed in two phases:
 * 1. ldl_symbolic: Compute elimination tree and allocate storage
 * 2. ldl_numeric: Compute numerical values of L and D
 *
 * Triangular solves (ldl_lsolve, ldl_dsolve, ldl_ltsolve) complete the
 * solution of Ax = b.
 *
 * @math A = L * D * L' where L is unit lower triangular, D is diagonal.
 *       Unlike Cholesky (A = L*L'), LDL' handles indefinite matrices.
 *
 * @see cholmod.h for more sophisticated Cholesky implementation
 * @see amd.h for fill-reducing orderings to use with LDL
 */

//------------------------------------------------------------------------------
// LDL/Include/ldl.h: include file for the LDL package
//------------------------------------------------------------------------------

// LDL, Copyright (c) 2005-2024 by Timothy A. Davis. All Rights Reserved.
// SPDX-License-Identifier: LGPL-2.1+

//------------------------------------------------------------------------------

#ifndef LDL_H
#define LDL_H

#include "SuiteSparse_config.h"

#ifdef LDL_LONG
#define LDL_int int64_t
#define LDL_ID  "%" PRId64

#define LDL_symbolic ldl_l_symbolic
#define LDL_numeric ldl_l_numeric
#define LDL_lsolve ldl_l_lsolve
#define LDL_dsolve ldl_l_dsolve
#define LDL_ltsolve ldl_l_ltsolve
#define LDL_perm ldl_l_perm
#define LDL_permt ldl_l_permt
#define LDL_valid_perm ldl_l_valid_perm
#define LDL_valid_matrix ldl_l_valid_matrix

#else
#define LDL_int int32_t
#define LDL_ID "%d"

#define LDL_symbolic ldl_symbolic
#define LDL_numeric ldl_numeric
#define LDL_lsolve ldl_lsolve
#define LDL_dsolve ldl_dsolve
#define LDL_ltsolve ldl_ltsolve
#define LDL_perm ldl_perm
#define LDL_permt ldl_permt
#define LDL_valid_perm ldl_valid_perm
#define LDL_valid_matrix ldl_valid_matrix

#endif

/* make it easy for C++ programs to include LDL */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief Get LDL library version numbers */
void ldl_version (int version [3]) ;

/* ========================================================================== */
/* === int32_t version ====================================================== */
/* ========================================================================== */

/**
 * @brief Symbolic analysis phase of LDL' factorization
 *
 * Computes the elimination tree, storage requirements, and column pointers
 * for L. Must be called before ldl_numeric.
 *
 * @param n Matrix dimension
 * @param Ap Column pointers for A (size n+1)
 * @param Ai Row indices for A
 * @param Lp Output: column pointers for L (size n+1)
 * @param Parent Output: elimination tree (size n)
 * @param Lnz Output: # nonzeros in each column of L (size n)
 * @param Flag Workspace (size n)
 * @param P Fill-reducing permutation (size n, or NULL for natural order)
 * @param Pinv Inverse permutation (size n, or NULL)
 */
void ldl_symbolic (int32_t n, int32_t Ap [ ], int32_t Ai [ ], int32_t Lp [ ],
    int32_t Parent [ ], int32_t Lnz [ ], int32_t Flag [ ], int32_t P [ ],
    int32_t Pinv [ ]) ;

/**
 * @brief Numeric phase of LDL' factorization
 *
 * Computes the numerical values of L and D given the symbolic analysis.
 *
 * @param n Matrix dimension
 * @param Ap,Ai,Ax Sparse matrix A in CSC format
 * @param Lp,Parent,Lnz From ldl_symbolic
 * @param Li,Lx Output: row indices and values of L
 * @param D Output: diagonal matrix D (size n)
 * @param Y,Pattern,Flag Workspace arrays (size n each)
 * @param P,Pinv Permutation and inverse (or NULL)
 * @return n if successful, k if D[k] is zero (matrix singular at column k)
 */
int32_t ldl_numeric (int32_t n, int32_t Ap [ ], int32_t Ai [ ], double Ax [ ],
    int32_t Lp [ ], int32_t Parent [ ], int32_t Lnz [ ], int32_t Li [ ],
    double Lx [ ], double D [ ], double Y [ ], int32_t Pattern [ ],
    int32_t Flag [ ], int32_t P [ ], int32_t Pinv [ ]) ;

/** @brief Solve Lx = b in place (L is unit lower triangular) */
void ldl_lsolve (int32_t n, double X [ ], int32_t Lp [ ], int32_t Li [ ],
    double Lx [ ]) ;

/** @brief Solve Dx = b in place (D is diagonal) */
void ldl_dsolve (int32_t n, double X [ ], double D [ ]) ;

/** @brief Solve L'x = b in place */
void ldl_ltsolve (int32_t n, double X [ ], int32_t Lp [ ], int32_t Li [ ],
    double Lx [ ]) ;

/** @brief Apply permutation: X = B(P) */
void ldl_perm  (int32_t n, double X [ ], double B [ ], int32_t P [ ]) ;

/** @brief Apply inverse permutation: X(P) = B */
void ldl_permt (int32_t n, double X [ ], double B [ ], int32_t P [ ]) ;

/** @brief Check if P is a valid permutation */
int32_t ldl_valid_perm (int32_t n, int32_t P [ ], int32_t Flag [ ]) ;

/** @brief Check if sparse matrix structure is valid */
int32_t ldl_valid_matrix ( int32_t n, int32_t Ap [ ], int32_t Ai [ ]) ;

/* ========================================================================== */
/* === int64_t version ====================================================== */
/* ========================================================================== */

void ldl_l_symbolic (int64_t n, int64_t Ap [ ], int64_t Ai [ ], int64_t Lp [ ],
    int64_t Parent [ ], int64_t Lnz [ ], int64_t Flag [ ], int64_t P [ ],
    int64_t Pinv [ ]) ;

int64_t ldl_l_numeric (int64_t n, int64_t Ap [ ], int64_t Ai [ ], double Ax [ ],
    int64_t Lp [ ], int64_t Parent [ ], int64_t Lnz [ ], int64_t Li [ ],
    double Lx [ ], double D [ ], double Y [ ], int64_t Pattern [ ],
    int64_t Flag [ ], int64_t P [ ], int64_t Pinv [ ]) ;

void ldl_l_lsolve (int64_t n, double X [ ], int64_t Lp [ ], int64_t Li [ ],
    double Lx [ ]) ;

void ldl_l_dsolve (int64_t n, double X [ ], double D [ ]) ;

void ldl_l_ltsolve (int64_t n, double X [ ], int64_t Lp [ ], int64_t Li [ ],
    double Lx [ ]) ;

void ldl_l_perm  (int64_t n, double X [ ], double B [ ], int64_t P [ ]) ;
void ldl_l_permt (int64_t n, double X [ ], double B [ ], int64_t P [ ]) ;

int64_t ldl_l_valid_perm (int64_t n, int64_t P [ ], int64_t Flag [ ]) ;

int64_t ldl_l_valid_matrix ( int64_t n, int64_t Ap [ ], int64_t Ai [ ]) ;

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/* === LDL version ========================================================== */
/* ========================================================================== */

#define LDL_DATE "July 25, 2025"
#define LDL_MAIN_VERSION   3
#define LDL_SUB_VERSION    3
#define LDL_SUBSUB_VERSION 3

#define LDL_VERSION_CODE(main,sub) SUITESPARSE_VER_CODE(main,sub)
#define LDL_VERSION LDL_VERSION_CODE(3,3)

#define LDL__VERSION SUITESPARSE__VERCODE(3,3,3)
#if !defined (SUITESPARSE__VERSION) || \
    (SUITESPARSE__VERSION < SUITESPARSE__VERCODE(7,11,0))
#error "LDL 3.3.3 requires SuiteSparse_config 7.11.0 or later"
#endif

#endif
