/**
 * @file colamd.h
 * @brief Column Approximate Minimum Degree ordering for sparse LU factorization
 *
 * COLAMD computes a column permutation Q that reduces fill-in during LU
 * factorization of an unsymmetric matrix A. The ordering minimizes the
 * fill-in of A*Q when factored as LU.
 *
 * SYMAMD computes a symmetric ordering for a symmetric matrix, using COLAMD
 * on the matrix's structure. Both are related to the minimum degree family
 * of algorithms.
 *
 * @algorithm Column Approximate Minimum Degree (COLAMD)
 * @ref Davis, Gilbert, Larimore, Ng (2004). "A Column Approximate Minimum
 *      Degree Ordering Algorithm". ACM Trans. Math. Software 30(3):353-376.
 *
 * @see amd.h for symmetric matrix ordering
 * @see umfpack.h for sparse LU factorization using COLAMD
 */

//------------------------------------------------------------------------------
// COLAMD/Include/colamd.h: include file for COLAMD
//------------------------------------------------------------------------------

// COLAMD, Copyright (c) 1998-2024, Timothy A. Davis and Stefan Larimore,
// All Rights Reserved.
// SPDX-License-Identifier: BSD-3-clause

//------------------------------------------------------------------------------

/* COLAMD / SYMAMD include file

    You must include this file (colamd.h) in any routine that uses colamd,
    symamd, or the related macros and definitions.

    Authors:

        The authors of the code itself are Stefan I. Larimore and Timothy A.
        Davis (DrTimothyAldenDavis@gmail.com).  The algorithm was
        developed in collaboration with John Gilbert, Xerox PARC, and Esmond
        Ng, Oak Ridge National Laboratory.

    Acknowledgements:

        This work was supported by the National Science Foundation, under
        grants DMS-9504974 and DMS-9803599.

    Availability:

        The colamd/symamd library is available at http://www.suitesparse.com
        This file is required by the colamd.c, colamdmex.c, and symamdmex.c
        files, and by any C code that calls the routines whose prototypes are
        listed below, or that uses the colamd/symamd definitions listed below.

*/

#ifndef COLAMD_H
#define COLAMD_H

/* ========================================================================== */
/* === Include files ======================================================== */
/* ========================================================================== */

#include "SuiteSparse_config.h"

/* ========================================================================== */
/* === COLAMD version ======================================================= */
/* ========================================================================== */

/* COLAMD Version 2.4 and later will include the following definitions.
 * As an example, to test if the version you are using is 2.4 or later:
 *
 * #ifdef COLAMD_VERSION
 *     if (COLAMD_VERSION >= COLAMD_VERSION_CODE (2,4)) ...
 * #endif
 *
 * This also works during compile-time:
 *
 *  #if defined(COLAMD_VERSION) && (COLAMD_VERSION >= COLAMD_VERSION_CODE (2,4))
 *    printf ("This is version 2.4 or later\n") ;
 *  #else
 *    printf ("This is an early version\n") ;
 *  #endif
 *
 * Versions 2.3 and earlier of COLAMD do not include a #define'd version number.
 */

#define COLAMD_DATE "July 25, 2025"
#define COLAMD_MAIN_VERSION   3
#define COLAMD_SUB_VERSION    3
#define COLAMD_SUBSUB_VERSION 5

#define COLAMD_VERSION_CODE(main,sub) SUITESPARSE_VER_CODE(main,sub)
#define COLAMD_VERSION COLAMD_VERSION_CODE(3,3)

#define COLAMD__VERSION SUITESPARSE__VERCODE(3,3,5)
#if !defined (SUITESPARSE__VERSION) || \
    (SUITESPARSE__VERSION < SUITESPARSE__VERCODE(7,11,0))
#error "COLAMD 3.3.5 requires SuiteSparse_config 7.11.0 or later"
#endif

/* ========================================================================== */
/* === Knob and statistics definitions ====================================== */
/* ========================================================================== */

/* size of the knobs [ ] array.  Only knobs [0..1] are currently used. */
#define COLAMD_KNOBS 20

/* number of output statistics.  Only stats [0..6] are currently used. */
#define COLAMD_STATS 20

/* knobs [0] and stats [0]: dense row knob and output statistic. */
#define COLAMD_DENSE_ROW 0

/* knobs [1] and stats [1]: dense column knob and output statistic. */
#define COLAMD_DENSE_COL 1

/* knobs [2]: aggressive absorption */
#define COLAMD_AGGRESSIVE 2

/* stats [2]: memory defragmentation count output statistic */
#define COLAMD_DEFRAG_COUNT 2

/* stats [3]: colamd status:  zero OK, > 0 warning or notice, < 0 error */
#define COLAMD_STATUS 3

/* stats [4..6]: error info, or info on jumbled columns */ 
#define COLAMD_INFO1 4
#define COLAMD_INFO2 5
#define COLAMD_INFO3 6

/* error codes returned in stats [3]: */
#define COLAMD_OK                               (0)
#define COLAMD_OK_BUT_JUMBLED                   (1)
#define COLAMD_ERROR_A_not_present              (-1)
#define COLAMD_ERROR_p_not_present              (-2)
#define COLAMD_ERROR_nrow_negative              (-3)
#define COLAMD_ERROR_ncol_negative              (-4)
#define COLAMD_ERROR_nnz_negative               (-5)
#define COLAMD_ERROR_p0_nonzero                 (-6)
#define COLAMD_ERROR_A_too_small                (-7)
#define COLAMD_ERROR_col_length_negative        (-8)
#define COLAMD_ERROR_row_index_out_of_bounds    (-9)
#define COLAMD_ERROR_out_of_memory              (-10)
#define COLAMD_ERROR_internal_error             (-999)


/* ========================================================================== */
/* === Prototypes of user-callable routines ================================= */
/* ========================================================================== */

/* make it easy for C++ programs to include COLAMD */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute recommended size for COLAMD workspace array
 *
 * Returns the minimum size of the A array needed for colamd().
 * The array must be at least this size to hold both the input matrix
 * and workspace for the ordering algorithm.
 *
 * @param nnz Number of nonzeros in the matrix
 * @param n_row Number of rows in the matrix
 * @param n_col Number of columns in the matrix
 * @return Recommended array size, or 0 if inputs are invalid
 *
 * @see colamd()
 */
size_t colamd_recommended
(
    int32_t nnz,
    int32_t n_row,
    int32_t n_col
) ;

/** @brief Compute recommended workspace size (64-bit version) @see colamd_recommended() */
size_t colamd_l_recommended
(
    int64_t nnz,
    int64_t n_row,
    int64_t n_col
) ;

/**
 * @brief Initialize COLAMD parameters to default values
 *
 * Sets default thresholds for dense row/column detection and
 * enables aggressive absorption by default.
 *
 * @param knobs Output array of size COLAMD_KNOBS to initialize
 */
void colamd_set_defaults
(
    double knobs [COLAMD_KNOBS]
) ;

/** @brief Initialize parameters (64-bit version) @see colamd_set_defaults() */
void colamd_l_set_defaults
(
    double knobs [COLAMD_KNOBS]
) ;

/**
 * @brief Compute column ordering for sparse LU factorization
 *
 * Computes a column permutation Q that reduces fill-in when factoring A*Q
 * by LU. The input matrix A is destroyed and replaced with the permutation.
 *
 * @param n_row Number of rows in A
 * @param n_col Number of columns in A
 * @param Alen Size of array A (use colamd_recommended to compute)
 * @param A Input: row indices in CSC format. Output: destroyed, replaced with permutation
 * @param p Input: column pointers. Output: column permutation Q
 * @param knobs Control parameters (NULL uses defaults)
 * @param stats Output statistics and error codes
 * @return 1 on success, 0 on failure (check stats[COLAMD_STATUS])
 *
 * @note The A array is modified in place and serves as workspace
 * @see colamd_recommended(), colamd_set_defaults()
 */
int colamd
(
    int32_t n_row,
    int32_t n_col,
    int32_t Alen,
    int32_t A [],
    int32_t p [],
    double knobs [COLAMD_KNOBS],
    int32_t stats [COLAMD_STATS]
) ;

/** @brief Compute column ordering (64-bit version) @see colamd() */
int colamd_l
(
    int64_t n_row,
    int64_t n_col,
    int64_t Alen,
    int64_t A [],
    int64_t p [],
    double knobs [COLAMD_KNOBS],
    int64_t stats [COLAMD_STATS]
) ;

/**
 * @brief Compute symmetric ordering using COLAMD on matrix structure
 *
 * Computes a symmetric permutation P for a symmetric matrix A such that
 * P*A*P' has reduced fill-in during Cholesky factorization. Internally
 * converts to COLAMD's representation and calls COLAMD.
 *
 * @param n Matrix dimension (A is n-by-n symmetric)
 * @param A Row indices array (CSC format, lower triangle only)
 * @param p Column pointers array of size n+1
 * @param perm Output permutation array of size n+1
 * @param knobs Control parameters (NULL uses defaults)
 * @param stats Output statistics and error codes
 * @param allocate Memory allocator function (calloc signature)
 * @param release Memory release function (free signature)
 * @return 1 on success, 0 on failure
 *
 * @see amd_order() for alternative symmetric ordering
 */
int symamd
(
    int32_t n,
    int32_t A [],
    int32_t p [],
    int32_t perm [],
    double knobs [COLAMD_KNOBS],
    int32_t stats [COLAMD_STATS],
    void * (*allocate) (size_t, size_t),
    void (*release) (void *)
) ;

/** @brief Compute symmetric ordering (64-bit version) @see symamd() */
int symamd_l
(
    int64_t n,
    int64_t A [],
    int64_t p [],
    int64_t perm [],
    double knobs [COLAMD_KNOBS],
    int64_t stats [COLAMD_STATS],
    void * (*allocate) (size_t, size_t),
    void (*release) (void *)
) ;

/**
 * @brief Print COLAMD statistics and error information
 * @param stats Statistics array from colamd() call
 */
void colamd_report
(
    int32_t stats [COLAMD_STATS]
) ;

/** @brief Print statistics (64-bit version) @see colamd_report() */
void colamd_l_report
(
    int64_t stats [COLAMD_STATS]
) ;

/**
 * @brief Print SYMAMD statistics and error information
 * @param stats Statistics array from symamd() call
 */
void symamd_report
(
    int32_t stats [COLAMD_STATS]
) ;

/** @brief Print SYMAMD statistics (64-bit version) @see symamd_report() */
void symamd_l_report
(
    int64_t stats [COLAMD_STATS]
) ;

/**
 * @brief Get COLAMD library version numbers
 * @param version Output array filled with [major, minor, patch]
 */
void colamd_version (int version [3]) ;

#ifdef __cplusplus
}
#endif

#endif /* COLAMD_H */
