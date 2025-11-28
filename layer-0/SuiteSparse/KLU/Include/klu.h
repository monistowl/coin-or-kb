/**
 * @file klu.h
 * @brief Sparse LU factorization optimized for circuit simulation matrices
 *
 * KLU computes a sparse LU factorization of a square matrix A:
 *   P*A*Q = L*U
 * where P and Q are permutation matrices, L is unit lower triangular,
 * and U is upper triangular.
 *
 * KLU is specifically designed for matrices arising from circuit simulation,
 * which tend to be sparse and nearly block-triangular. The factorization
 * proceeds in three phases:
 * 1. klu_analyze: BTF pre-ordering + fill-reducing ordering (AMD/COLAMD)
 * 2. klu_factor: Numerical LU factorization (left-looking, column-by-column)
 * 3. klu_solve: Forward/back substitution to solve Ax = b
 *
 * @algorithm Left-looking LU with BTF preprocessing and partial pivoting
 * @ref Davis, Palamadai (2010). "KLU: A Direct Sparse Solver for Circuit
 *      Simulation Problems". ACM Trans. Math. Software.
 *
 * @see btf.h for BTF decomposition
 * @see amd.h, colamd.h for fill-reducing orderings
 * @see umfpack.h for general-purpose multifrontal LU
 */

//------------------------------------------------------------------------------
// KLU/Source/klu.h: include file for KLU
//------------------------------------------------------------------------------

// KLU, Copyright (c) 2004-2024, University of Florida.  All Rights Reserved.
// Authors: Timothy A. Davis and Ekanathan Palamadai.
// SPDX-License-Identifier: LGPL-2.1+

//------------------------------------------------------------------------------

/* Include file for user programs that call klu_* routines */

#ifndef _KLU_H
#define _KLU_H

#include "amd.h"
#include "colamd.h"
#include "btf.h"

/* make it easy for C++ programs to include KLU */
#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/* Symbolic object - contains the pre-ordering computed by klu_analyze */
/* -------------------------------------------------------------------------- */

/**
 * @brief Result of symbolic analysis phase (klu_analyze)
 *
 * Contains the BTF block structure and fill-reducing permutations computed
 * during symbolic analysis. This object is reusable: once computed, it can
 * be used for multiple factorizations of matrices with the same sparsity pattern.
 *
 * The permutations P and Q transform A into block upper triangular form:
 *   P*A*Q = | B11  B12  B13 ... |
 *           |  0   B22  B23 ... |
 *           |  0    0   B33 ... |
 * where each Bkk is factored independently.
 *
 * @see klu_analyze() to create this object
 * @see klu_factor() to use this for numerical factorization
 */
typedef struct
{
    /* A (P,Q) is in upper block triangular form.  The kth block goes from
     * row/col index R [k] to R [k+1]-1.  The estimated number of nonzeros
     * in the L factor of the kth block is Lnz [k].
     */

    /* only computed if the AMD ordering is chosen: */
    double symmetry ;   /**< @brief Symmetry ratio of largest block (1.0 = symmetric) */
    double est_flops ;  /**< @brief Estimated factorization flop count */
    double lnz, unz ;   /**< @brief Estimated nz in L and U, including diagonals */
    double *Lnz ;       /**< @brief Estimated nz in L for each block (size nblocks) */

    /* computed for all orderings: */
    int32_t
        n,              /**< @brief Matrix dimension (A is n-by-n) */
        nz,             /**< @brief Number of entries in input matrix */
        *P,             /**< @brief Row permutation (size n) */
        *Q,             /**< @brief Column permutation (size n) */
        *R,             /**< @brief Block boundaries: block k is rows/cols R[k] to R[k+1]-1 */
        nzoff,          /**< @brief Number of nonzeros in off-diagonal blocks */
        nblocks,        /**< @brief Number of diagonal blocks in BTF form */
        maxblock,       /**< @brief Dimension of largest diagonal block */
        ordering,       /**< @brief Ordering used: 0=AMD, 1=COLAMD, 2=user-provided */
        do_btf ;        /**< @brief Whether BTF preordering was applied */

    /* only computed if BTF preordering requested */
    int32_t structural_rank ;   /**< @brief Structural rank: n if full rank, 0 to n-1 if deficient */

} klu_symbolic ;

typedef struct          /* 64-bit version (otherwise same as above) */
{
    double symmetry, est_flops, lnz, unz ;
    double *Lnz ;
    int64_t n, nz, *P, *Q, *R, nzoff, nblocks, maxblock, ordering,
        do_btf, structural_rank ;

} klu_l_symbolic ;

/* -------------------------------------------------------------------------- */
/* Numeric object - contains the factors computed by klu_factor */
/* -------------------------------------------------------------------------- */

/**
 * @brief Result of numerical factorization phase (klu_factor)
 *
 * Contains the computed L and U factors, pivot permutation, row scaling,
 * and off-diagonal block entries. The factors are stored in a block-wise
 * format corresponding to the BTF structure.
 *
 * The factorization satisfies: P*R*A*Q = L*U
 * where P combines BTF row permutation with pivot permutation,
 * Q is the BTF column permutation, R is diagonal scaling, and
 * L*U are the sparse triangular factors.
 *
 * @see klu_factor() to create this object
 * @see klu_solve() to use for solving linear systems
 * @see klu_refactor() to update with new numerical values
 */
typedef struct
{
    /* LU factors of each block, the pivot row permutation, and the
     * entries in the off-diagonal blocks */

    int32_t n ;             /**< @brief Matrix dimension (A is n-by-n) */
    int32_t nblocks ;       /**< @brief Number of diagonal blocks */
    int32_t lnz ;           /**< @brief Actual nonzeros in L (including diagonal) */
    int32_t unz ;           /**< @brief Actual nonzeros in U (including diagonal) */
    int32_t max_lnz_block ; /**< @brief Max nz in L for any single block */
    int32_t max_unz_block ; /**< @brief Max nz in U for any single block */
    int32_t *Pnum ;         /**< @brief Final pivot permutation (size n) */
    int32_t *Pinv ;         /**< @brief Inverse of pivot permutation (size n) */

    /* LU factors of each block */
    int32_t *Lip ;          /**< @brief Pointers into LUbx for L columns (size n) */
    int32_t *Uip ;          /**< @brief Pointers into LUbx for U columns (size n) */
    int32_t *Llen ;         /**< @brief Number of entries in each L column (size n) */
    int32_t *Ulen ;         /**< @brief Number of entries in each U column (size n) */
    void **LUbx ;           /**< @brief L and U indices/values for each block */
    size_t *LUsize ;        /**< @brief Size of each LUbx[block] in Units */
    void *Udiag ;           /**< @brief Diagonal entries of U (size n) */

    /* scale factors; can be NULL if no scaling */
    double *Rs ;            /**< @brief Row scale factors: Rs[i] for row i (size n) */

    /* permanent workspace for factorization and solve */
    size_t worksize ;       /**< @brief Size of Work array in bytes */
    void *Work ;            /**< @brief Workspace for factorization and solve */
    void *Xwork ;           /**< @brief Alias into Work for numerical workspace */
    int32_t *Iwork ;        /**< @brief Alias into Work for integer workspace */

    /* off-diagonal entries in a conventional compressed-column sparse matrix */
    int32_t *Offp ;         /**< @brief Column pointers for off-diagonal blocks (size n+1) */
    int32_t *Offi ;         /**< @brief Row indices for off-diagonal blocks */
    void *Offx ;            /**< @brief Numerical values for off-diagonal blocks */
    int32_t nzoff ;         /**< @brief Number of off-diagonal entries */

} klu_numeric ;

typedef struct          /* 64-bit version (otherwise same as above) */
{
    int64_t n, nblocks, lnz, unz, max_lnz_block, max_unz_block, *Pnum,
        *Pinv, *Lip, *Uip, *Llen, *Ulen ;
    void **LUbx ;
    size_t *LUsize ;
    void *Udiag ;
    double *Rs ;
    size_t worksize ;
    void *Work, *Xwork ;
    int64_t *Iwork ;
    int64_t *Offp, *Offi ;
    void *Offx ;
    int64_t nzoff ;

} klu_l_numeric ;

/* -------------------------------------------------------------------------- */
/* KLU control parameters and statistics */
/* -------------------------------------------------------------------------- */

/* Common->status values */
#define KLU_OK 0                    /**< @brief Factorization successful */
#define KLU_SINGULAR (1)            /**< @brief Matrix is singular (warning, not error) */
#define KLU_OUT_OF_MEMORY (-2)      /**< @brief Memory allocation failed */
#define KLU_INVALID (-3)            /**< @brief Invalid input parameters */
#define KLU_TOO_LARGE (-4)          /**< @brief Integer overflow occurred */

/**
 * @brief Control parameters and output statistics for KLU
 *
 * Contains all control parameters for factorization (pivot tolerance,
 * ordering selection, scaling options) and output statistics (condition
 * estimates, flop counts, memory usage).
 *
 * Initialize with klu_defaults() before first use.
 *
 * @see klu_defaults() to initialize
 */
typedef struct klu_common_struct
{

    /* ---------------------------------------------------------------------- */
    /* parameters */
    /* ---------------------------------------------------------------------- */

    double tol ;            /**< @brief Pivot tolerance for diagonal preference (default 0.001) */
    double memgrow ;        /**< @brief Realloc memory growth factor for LU factors */
    double initmem_amd ;    /**< @brief Initial memory estimate multiplier with AMD */
    double initmem ;        /**< @brief Initial memory estimate multiplier without AMD */
    double maxwork ;        /**< @brief Max work for BTF (<=0 for no limit) */

    int btf ;               /**< @brief Use BTF pre-ordering (1) or not (0) */
    int ordering ;          /**< @brief Fill-reducing ordering: 0=AMD, 1=COLAMD, 2=user P/Q, 3=user function */
    int scale ;             /**< @brief Row scaling: -1=none (no check), 0=none, 1=sum, 2=max */

    /** @brief User-provided ordering function (optional, for ordering=3) */
    int32_t (*user_order) (int32_t, int32_t *, int32_t *, int32_t *,
        struct klu_common_struct *) ;

    /** @brief User data passed to user_order function (optional) */
    void *user_data ;

    int halt_if_singular ;      /**< @brief If TRUE, stop on singular matrix; if FALSE, continue */
    /* how to handle a singular matrix:
        * FALSE: keep going.  Return a Numeric object with a zero U(k,k).  A
        *   divide-by-zero may occur when computing L(:,k).  The Numeric object
        *   can be passed to klu_solve (a divide-by-zero will occur).  It can
        *   also be safely passed to klu_refactor.
        * TRUE: stop quickly.  klu_factor will free the partially-constructed
        *   Numeric object.  klu_refactor will not free it, but will leave the
        *   numerical values only partially defined.  This is the default. */

    /* ---------------------------------------------------------------------- */
    /* statistics */
    /* ---------------------------------------------------------------------- */

    int status ;                /**< @brief Result status: KLU_OK, KLU_SINGULAR, or error code */
    int nrealloc ;              /**< @brief Number of memory reallocations during factorization */

    int32_t structural_rank ;   /**< @brief Structural rank from BTF analysis (n if full rank) */

    int32_t numerical_rank ;    /**< @brief Column k where first zero pivot found, or n if full rank */

    int32_t singular_col ;      /**< @brief Original column index of singular column, or n */

    int32_t noffdiag ;          /**< @brief Number of off-diagonal pivots selected */

    double flops ;              /**< @brief Factorization flop count (from klu_flops) */
    double rcond ;              /**< @brief Crude reciprocal condition estimate (from klu_rcond) */
    double condest ;            /**< @brief Accurate 1-norm condition estimate (from klu_condest) */
    double rgrowth ;            /**< @brief Reciprocal pivot growth (from klu_rgrowth) */
    double work ;               /**< @brief Work done in BTF phase (from klu_analyze) */

    size_t memusage ;           /**< @brief Current memory usage in bytes */
    size_t mempeak ;            /**< @brief Peak memory usage in bytes */

} klu_common ;

typedef struct klu_l_common_struct /* 64-bit version (otherwise same as above)*/
{

    double tol, memgrow, initmem_amd, initmem, maxwork ;
    int btf, ordering, scale ;
    int64_t (*user_order) (int64_t, int64_t *, int64_t *, int64_t *,
        struct klu_l_common_struct *) ;
    void *user_data ;
    int halt_if_singular, status, nrealloc ;
    int64_t structural_rank, numerical_rank, singular_col, noffdiag ;
    double flops, rcond, condest, rgrowth, work ;
    size_t memusage, mempeak ;

} klu_l_common ;

/* -------------------------------------------------------------------------- */
/* klu_defaults: sets default control parameters */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize KLU control parameters to default values
 *
 * Must be called before any other KLU routine to initialize Common.
 * Default settings: tol=0.001, BTF on, AMD ordering, max scaling.
 *
 * @param Common Control/statistics structure to initialize
 * @return TRUE on success, FALSE if Common is NULL
 */
int klu_defaults
(
    klu_common *Common
) ;

/** @brief Initialize parameters (64-bit version) @see klu_defaults() */
int klu_l_defaults (klu_l_common *Common) ;

/* -------------------------------------------------------------------------- */
/* klu_analyze:  orders and analyzes a matrix */
/* -------------------------------------------------------------------------- */

/**
 * @brief Symbolic analysis: compute fill-reducing ordering and BTF decomposition
 *
 * Performs symbolic analysis of matrix A:
 * 1. Optionally computes BTF decomposition to find independent blocks
 * 2. Computes fill-reducing ordering (AMD or COLAMD) for each block
 * 3. Estimates memory requirements for numerical factorization
 *
 * The returned Symbolic object is reusable for multiple factorizations
 * of matrices with the same sparsity pattern (but different values).
 *
 * @param n Matrix dimension (A is n-by-n)
 * @param Ap Column pointers array of size n+1
 * @param Ai Row indices array of size Ap[n]
 * @param Common Control parameters and output statistics
 * @return Symbolic object, or NULL on error
 *
 * @see klu_factor() to perform numerical factorization
 * @see klu_free_symbolic() to free the returned object
 */
klu_symbolic *klu_analyze
(
    /* inputs, not modified */
    int32_t n,              /* A is n-by-n */
    int32_t Ap [ ],         /* size n+1, column pointers */
    int32_t Ai [ ],         /* size nz, row indices */
    klu_common *Common
) ;

/** @brief Symbolic analysis (64-bit version) @see klu_analyze() */
klu_l_symbolic *klu_l_analyze (int64_t, int64_t *, int64_t *,
    klu_l_common *Common) ;


/* -------------------------------------------------------------------------- */
/* klu_analyze_given: analyzes a matrix using given P and Q */
/* -------------------------------------------------------------------------- */

/**
 * @brief Symbolic analysis with user-provided permutations
 *
 * Like klu_analyze, but uses user-provided row (P) and column (Q)
 * permutations instead of computing fill-reducing orderings.
 * Useful when a good ordering is already known.
 *
 * @param n Matrix dimension (A is n-by-n)
 * @param Ap Column pointers array of size n+1
 * @param Ai Row indices array of size Ap[n]
 * @param P User's row permutation (size n, NULL for identity)
 * @param Q User's column permutation (size n, NULL for identity)
 * @param Common Control parameters and output statistics
 * @return Symbolic object, or NULL on error
 *
 * @see klu_analyze() for automatic ordering
 */
klu_symbolic *klu_analyze_given
(
    /* inputs, not modified */
    int32_t n,              /* A is n-by-n */
    int32_t Ap [ ],         /* size n+1, column pointers */
    int32_t Ai [ ],         /* size nz, row indices */
    int32_t P [ ],          /* size n, user's row permutation (may be NULL) */
    int32_t Q [ ],          /* size n, user's column permutation (may be NULL) */
    klu_common *Common
) ;

/** @brief Symbolic analysis with given permutations (64-bit) @see klu_analyze_given() */
klu_l_symbolic *klu_l_analyze_given (int64_t, int64_t *, int64_t *, int64_t *,
    int64_t *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_factor:  factors a matrix using the klu_analyze results */
/* -------------------------------------------------------------------------- */

/**
 * @brief Numerical LU factorization using symbolic analysis results
 *
 * Computes the LU factorization P*R*A*Q = L*U using the ordering and
 * BTF structure from klu_analyze. Uses left-looking column-by-column
 * factorization with partial pivoting.
 *
 * @param Ap Column pointers array of size n+1
 * @param Ai Row indices array of size Ap[n]
 * @param Ax Numerical values array of size Ap[n]
 * @param Symbolic Symbolic analysis from klu_analyze
 * @param Common Control parameters and output statistics
 * @return Numeric object containing L,U factors, or NULL on error
 *
 * @note Check Common->status for KLU_OK, KLU_SINGULAR, or error code
 * @see klu_solve() to solve linear systems using the factorization
 * @see klu_refactor() to update factorization with new values
 */
klu_numeric *klu_factor /* returns KLU_OK if OK, < 0 if error */
(
    /* inputs, not modified */
    int32_t Ap [ ],         /* size n+1, column pointers */
    int32_t Ai [ ],         /* size nz, row indices */
    double Ax [ ],      /* size nz, numerical values */
    klu_symbolic *Symbolic,
    klu_common *Common
) ;

/** @brief Complex LU factorization @see klu_factor() */
klu_numeric *klu_z_factor      /* returns KLU_OK if OK, < 0 if error */
(
     /* inputs, not modified */
     int32_t Ap [ ],        /* size n+1, column pointers */
     int32_t Ai [ ],        /* size nz, row indices */
     double Ax [ ],     /* size 2*nz, numerical values (real,imag pairs) */
     klu_symbolic *Symbolic,
     klu_common *Common
) ;

/** @brief LU factorization (64-bit version) @see klu_factor() */
klu_l_numeric *klu_l_factor (int64_t *, int64_t *, double *,
    klu_l_symbolic *, klu_l_common *) ;

/** @brief Complex LU factorization (64-bit) @see klu_factor() */
klu_l_numeric *klu_zl_factor (int64_t *, int64_t *, double *,
    klu_l_symbolic *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_solve: solves Ax=b using the Symbolic and Numeric objects */
/* -------------------------------------------------------------------------- */

/**
 * @brief Solve Ax = b using computed LU factorization
 *
 * Solves one or more systems Ax = b using forward/back substitution
 * with the L and U factors. The solution overwrites the right-hand side.
 *
 * @param Symbolic Symbolic analysis from klu_analyze
 * @param Numeric LU factors from klu_factor
 * @param ldim Leading dimension of B (>= n for column-major storage)
 * @param nrhs Number of right-hand sides
 * @param B Input: right-hand side(s). Output: solution(s). Size ldim*nrhs
 * @param Common Control parameters
 * @return TRUE on success, FALSE on error
 *
 * @see klu_tsolve() for transpose solve A'x = b
 */
int klu_solve
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    int32_t ldim,               /* leading dimension of B */
    int32_t nrhs,               /* number of right-hand-sides */

    /* right-hand-side on input, overwritten with solution to Ax=b on output */
    double B [ ],           /* size ldim*nrhs */
    klu_common *Common
) ;

/** @brief Complex solve Ax = b @see klu_solve() */
int klu_z_solve
(
     /* inputs, not modified */
     klu_symbolic *Symbolic,
     klu_numeric *Numeric,
     int32_t ldim,               /* leading dimension of B */
     int32_t nrhs,               /* number of right-hand-sides */

     /* right-hand-side on input, overwritten with solution to Ax=b on output */
     double B [ ],          /* size 2*ldim*nrhs */
     klu_common *Common
) ;

/** @brief Solve Ax = b (64-bit version) @see klu_solve() */
int klu_l_solve (klu_l_symbolic *, klu_l_numeric *,
    int64_t, int64_t, double *, klu_l_common *) ;

/** @brief Complex solve (64-bit) @see klu_solve() */
int klu_zl_solve (klu_l_symbolic *, klu_l_numeric *,
    int64_t, int64_t, double *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_tsolve: solves A'x=b using the Symbolic and Numeric objects */
/* -------------------------------------------------------------------------- */

/**
 * @brief Solve A'x = b (transpose system) using LU factorization
 *
 * Solves the transpose system A'x = b. For complex matrices, can solve
 * either A^T*x = b or A^H*x = b (conjugate transpose).
 *
 * @param Symbolic Symbolic analysis from klu_analyze
 * @param Numeric LU factors from klu_factor
 * @param ldim Leading dimension of B
 * @param nrhs Number of right-hand sides
 * @param B Input: right-hand side(s). Output: solution(s)
 * @param Common Control parameters
 * @return TRUE on success, FALSE on error
 *
 * @see klu_solve() for standard solve Ax = b
 */
int klu_tsolve
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    int32_t ldim,               /* leading dimension of B */
    int32_t nrhs,               /* number of right-hand-sides */

    /* right-hand-side on input, overwritten with solution to Ax=b on output */
    double B [ ],           /* size ldim*nrhs */
    klu_common *Common
) ;

int klu_z_tsolve
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    int32_t ldim,               /* leading dimension of B */
    int32_t nrhs,               /* number of right-hand-sides */

    /* right-hand-side on input, overwritten with solution to Ax=b on output */
    double B [ ],           /* size 2*ldim*nrhs */
    int conj_solve,         /* TRUE: conjugate solve, FALSE: solve A.'x=b */
    klu_common *Common
     
) ;

int klu_l_tsolve (klu_l_symbolic *, klu_l_numeric *,
    int64_t, int64_t, double *, klu_l_common *) ;

int klu_zl_tsolve (klu_l_symbolic *, klu_l_numeric *,
    int64_t, int64_t, double *, int, klu_l_common * ) ;


/* -------------------------------------------------------------------------- */
/* klu_refactor: refactorizes matrix with same ordering as klu_factor */
/* -------------------------------------------------------------------------- */

/**
 * @brief Refactorize with new values but same sparsity pattern
 *
 * Updates the numerical factorization when matrix values change but the
 * sparsity pattern remains identical. Much faster than klu_factor because
 * it reuses the symbolic analysis and memory allocation.
 *
 * Common use case: time-stepping simulations where matrix structure is
 * constant but values change each step.
 *
 * @param Ap Column pointers (must match original pattern)
 * @param Ai Row indices (must match original pattern)
 * @param Ax New numerical values
 * @param Symbolic Symbolic analysis from klu_analyze
 * @param Numeric Existing numeric object (modified in place)
 * @param Common Control parameters
 * @return TRUE on success, FALSE on error
 *
 * @note Sparsity pattern must be identical to original klu_factor call
 */
int klu_refactor            /* return TRUE if successful, FALSE otherwise */
(
    /* inputs, not modified */
    int32_t Ap [ ],         /* size n+1, column pointers */
    int32_t Ai [ ],         /* size nz, row indices */
    double Ax [ ],      /* size nz, numerical values */
    klu_symbolic *Symbolic,
    /* input, and numerical values modified on output */
    klu_numeric *Numeric,
    klu_common *Common
) ;

int klu_z_refactor          /* return TRUE if successful, FALSE otherwise */
(
     /* inputs, not modified */
     int32_t Ap [ ],        /* size n+1, column pointers */
     int32_t Ai [ ],        /* size nz, row indices */
     double Ax [ ],     /* size 2*nz, numerical values */
     klu_symbolic *Symbolic,
     /* input, and numerical values modified on output */
     klu_numeric *Numeric,
     klu_common *Common
) ;

int klu_l_refactor (int64_t *, int64_t *,
    double *, klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;

int klu_zl_refactor (int64_t *, int64_t *,
    double *, klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_free_symbolic: destroys the Symbolic object */
/* -------------------------------------------------------------------------- */

/**
 * @brief Free a klu_symbolic object
 *
 * @param Symbolic Pointer to Symbolic object pointer (set to NULL on return)
 * @param Common Control parameters
 * @return TRUE on success, FALSE on error
 */
int klu_free_symbolic
(
    klu_symbolic **Symbolic,
    klu_common *Common
) ;

/** @brief Free symbolic object (64-bit) @see klu_free_symbolic() */
int klu_l_free_symbolic (klu_l_symbolic **, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_free_numeric: destroys the Numeric object */
/* -------------------------------------------------------------------------- */

/**
 * @brief Free a klu_numeric object
 *
 * Note: klu_free_numeric and klu_z_free_numeric are identical and can
 * free both real and complex Numeric objects.
 *
 * @param Numeric Pointer to Numeric object pointer (set to NULL on return)
 * @param Common Control parameters
 * @return TRUE on success, FALSE on error
 */
int klu_free_numeric
(
    klu_numeric **Numeric,
    klu_common *Common
) ;

int klu_z_free_numeric
(
     klu_numeric **Numeric,
     klu_common *Common
) ;

int klu_l_free_numeric (klu_l_numeric **, klu_l_common *) ;
int klu_zl_free_numeric (klu_l_numeric **, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_sort: sorts the columns of the LU factorization */
/* -------------------------------------------------------------------------- */

/* this is not needed except for the MATLAB interface */

int klu_sort
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    /* input/output */
    klu_numeric *Numeric,
    klu_common *Common
) ;

int klu_z_sort
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    /* input/output */
    klu_numeric *Numeric,
    klu_common *Common
) ;

int klu_l_sort  (klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;
int klu_zl_sort (klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_flops: determines # of flops performed in numeric factorzation */
/* -------------------------------------------------------------------------- */

int klu_flops
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    /* input/output */
    klu_common *Common
) ;

int klu_z_flops
(
    /* inputs, not modified */
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    /* input/output */
    klu_common *Common
) ;

int klu_l_flops  (klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;
int klu_zl_flops (klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_rgrowth : compute the reciprocal pivot growth */
/* -------------------------------------------------------------------------- */

/* Pivot growth is computed after the input matrix is permuted, scaled, and
 * off-diagonal entries pruned.  This is because the LU factorization of each
 * block takes as input the scaled diagonal blocks of the BTF form.  The
 * reciprocal pivot growth in column j of an LU factorization of a matrix C
 * is the largest entry in C divided by the largest entry in U; then the overall
 * reciprocal pivot growth is the smallest such value for all columns j.  Note
 * that the off-diagonal entries are not scaled, since they do not take part in
 * the LU factorization of the diagonal blocks.
 *
 * In MATLAB notation:
 *
 * rgrowth = min (max (abs ((R \ A(p,q)) - F)) ./ max (abs (U))) */

int klu_rgrowth
(
    int32_t Ap [ ],
    int32_t Ai [ ],
    double Ax [ ],
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    klu_common *Common          /* Common->rgrowth = reciprocal pivot growth */
) ;

int klu_z_rgrowth
(
    int32_t Ap [ ],
    int32_t Ai [ ],
    double Ax [ ],
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    klu_common *Common          /* Common->rgrowth = reciprocal pivot growth */
) ;

int klu_l_rgrowth (int64_t *, int64_t *,
    double *, klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;

int klu_zl_rgrowth (int64_t *, int64_t *,
    double *, klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_condest */
/* -------------------------------------------------------------------------- */

/**
 * @brief Estimate 1-norm condition number using Hager's method
 *
 * Computes a reasonably accurate estimate of the 1-norm condition number
 * using Hager's method as modified by Higham and Tisseur (same method as
 * MATLAB's condest). Result stored in Common->condest.
 *
 * @algorithm Hager-Higham-Tisseur 1-norm condition estimation
 *
 * @param Ap Column pointers array
 * @param Ax Numerical values array
 * @param Symbolic Symbolic analysis from klu_analyze
 * @param Numeric LU factors from klu_factor
 * @param Common Result stored in Common->condest
 * @return TRUE on success, FALSE on error
 */
int klu_condest
(
    int32_t Ap [ ],         /* size n+1, column pointers, not modified */
    double Ax [ ],          /* size nz = Ap[n], numerical values, not modified*/
    klu_symbolic *Symbolic, /* symbolic analysis, not modified */
    klu_numeric *Numeric,   /* numeric factorization, not modified */
    klu_common *Common      /* result returned in Common->condest */
) ;

int klu_z_condest
(
    int32_t Ap [ ],
    double Ax [ ],          /* size 2*nz */
    klu_symbolic *Symbolic,
    klu_numeric *Numeric,
    klu_common *Common      /* result returned in Common->condest */
) ;

int klu_l_condest (int64_t *, double *, klu_l_symbolic *,
    klu_l_numeric *, klu_l_common *) ;

int klu_zl_condest (int64_t *, double *, klu_l_symbolic *,
    klu_l_numeric *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_rcond: compute min(abs(diag(U))) / max(abs(diag(U))) */
/* -------------------------------------------------------------------------- */

/**
 * @brief Compute crude reciprocal condition estimate from U diagonal
 *
 * Computes min(|diag(U)|) / max(|diag(U)|), a crude but fast estimate
 * of the reciprocal condition number. Result stored in Common->rcond.
 *
 * @param Symbolic Symbolic analysis from klu_analyze
 * @param Numeric LU factors from klu_factor
 * @param Common Result stored in Common->rcond
 * @return TRUE on success, FALSE on error
 *
 * @see klu_condest() for a more accurate (but slower) condition estimate
 */
int klu_rcond
(
    klu_symbolic *Symbolic,         /* input, not modified */
    klu_numeric *Numeric,           /* input, not modified */
    klu_common *Common              /* result in Common->rcond */
) ;

int klu_z_rcond
(
    klu_symbolic *Symbolic,         /* input, not modified */
    klu_numeric *Numeric,           /* input, not modified */
    klu_common *Common              /* result in Common->rcond */
) ;

int klu_l_rcond  (klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;
int klu_zl_rcond (klu_l_symbolic *, klu_l_numeric *, klu_l_common *) ;

/* -------------------------------------------------------------------------- */
/* klu_scale */
/* -------------------------------------------------------------------------- */

int klu_scale           /* return TRUE if successful, FALSE otherwise */
(
    /* inputs, not modified */
    int scale,          /* <0: none, no error check; 0: none, 1: sum, 2: max */
    int32_t n,
    int32_t Ap [ ],         /* size n+1, column pointers */
    int32_t Ai [ ],         /* size nz, row indices */
    double Ax [ ],
    /* outputs, not defined on input */
    double Rs [ ],
    /* workspace, not defined on input or output */
    int32_t W [ ],          /* size n, can be NULL */
    klu_common *Common
) ;

int klu_z_scale         /* return TRUE if successful, FALSE otherwise */
(
    /* inputs, not modified */
    int scale,          /* <0: none, no error check; 0: none, 1: sum, 2: max */
    int32_t n,
    int32_t Ap [ ],         /* size n+1, column pointers */
    int32_t Ai [ ],         /* size nz, row indices */
    double Ax [ ],
    /* outputs, not defined on input */
    double Rs [ ],
    /* workspace, not defined on input or output */
    int32_t W [ ],          /* size n, can be NULL */
    klu_common *Common
) ;

int klu_l_scale (int, int64_t, int64_t *, int64_t *, double *,
    double *, int64_t *, klu_l_common *) ;

int klu_zl_scale (int, int64_t, int64_t *, int64_t *, double *,
    double *, int64_t *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* klu_extract  */
/* -------------------------------------------------------------------------- */

int klu_extract     /* returns TRUE if successful, FALSE otherwise */
(
    /* inputs: */
    klu_numeric *Numeric,
    klu_symbolic *Symbolic,

    /* outputs, either allocated on input, or ignored otherwise */

    /* L */
    int32_t *Lp,        /* size n+1 */
    int32_t *Li,        /* size Numeric->lnz */
    double *Lx,     /* size Numeric->lnz */

    /* U */
    int32_t *Up,        /* size n+1 */
    int32_t *Ui,        /* size Numeric->unz */
    double *Ux,     /* size Numeric->unz */

    /* F */
    int32_t *Fp,        /* size n+1 */
    int32_t *Fi,        /* size Numeric->nzoff */
    double *Fx,     /* size Numeric->nzoff */

    /* P, row permutation */
    int32_t *P,         /* size n */

    /* Q, column permutation */
    int32_t *Q,         /* size n */

    /* Rs, scale factors */
    double *Rs,     /* size n */

    /* R, block boundaries */
    int32_t *R,         /* size Symbolic->nblocks+1 (nblocks is at most n) */

    klu_common *Common
) ;


int klu_z_extract           /* returns TRUE if successful, FALSE otherwise */
(
    /* inputs: */
    klu_numeric *Numeric,
    klu_symbolic *Symbolic,

    /* outputs, all of which must be allocated on input */

    /* L */
    int32_t *Lp,        /* size n+1 */
    int32_t *Li,        /* size nnz(L) */
    double *Lx,     /* size nnz(L) */
    double *Lz,     /* size nnz(L) for the complex case, ignored if real */

    /* U */
    int32_t *Up,        /* size n+1 */
    int32_t *Ui,        /* size nnz(U) */
    double *Ux,     /* size nnz(U) */
    double *Uz,     /* size nnz(U) for the complex case, ignored if real */

    /* F */
    int32_t *Fp,        /* size n+1 */
    int32_t *Fi,        /* size nnz(F) */
    double *Fx,     /* size nnz(F) */
    double *Fz,     /* size nnz(F) for the complex case, ignored if real */

    /* P, row permutation */
    int32_t *P,         /* size n */

    /* Q, column permutation */
    int32_t *Q,         /* size n */

    /* Rs, scale factors */
    double *Rs,     /* size n */

    /* R, block boundaries */
    int32_t *R,         /* size Symbolic->nblocks+1 (nblocks is at most n) */

    klu_common *Common
) ;

int klu_l_extract (klu_l_numeric *, klu_l_symbolic *,
    int64_t *, int64_t *, double *,
    int64_t *, int64_t *, double *,
    int64_t *, int64_t *, double *,
    int64_t *, int64_t *, double *,
    int64_t *, klu_l_common *) ;

int klu_zl_extract (klu_l_numeric *, klu_l_symbolic *,
    int64_t *, int64_t *, double *, double *,
    int64_t *, int64_t *, double *, double *,
    int64_t *, int64_t *, double *, double *,
    int64_t *, int64_t *, double *,
    int64_t *, klu_l_common *) ;


/* -------------------------------------------------------------------------- */
/* KLU memory management routines */
/* -------------------------------------------------------------------------- */

void *klu_malloc        /* returns pointer to the newly malloc'd block */
(
    /* ---- input ---- */
    size_t n,           /* number of items */
    size_t size,        /* size of each item */
    /* --------------- */
    klu_common *Common
) ;

void *klu_free          /* always returns NULL */
(
    /* ---- in/out --- */
    void *p,            /* block of memory to free */
    size_t n,           /* number of items */
    size_t size,        /* size of each item */
    /* --------------- */
    klu_common *Common
) ;

void *klu_realloc       /* returns pointer to reallocated block */
(
    /* ---- input ---- */
    size_t nnew,        /* requested # of items in reallocated block */
    size_t nold,        /* current size of block, in # of items */
    size_t size,        /* size of each item */
    /* ---- in/out --- */
    void *p,            /* block of memory to realloc */
    /* --------------- */
    klu_common *Common
) ;

void *klu_l_malloc (size_t, size_t, klu_l_common *) ;

void *klu_l_free (void *, size_t, size_t, klu_l_common *) ;

void *klu_l_realloc (size_t, size_t, size_t, void *, klu_l_common *) ;

//------------------------------------------------------------------------------
// klu_version: return KLU version
//------------------------------------------------------------------------------

/**
 * @brief Get KLU library version numbers
 * @param version Output array filled with [major, minor, patch]
 */
void klu_version (int version [3]) ;

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/* === KLU version ========================================================== */
/* ========================================================================== */

/* All versions of KLU include these definitions.
 * As an example, to test if the version you are using is 1.2 or later:
 *
 *      if (KLU_VERSION >= KLU_VERSION_CODE (1,2)) ...
 *
 * This also works during compile-time:
 *
 *      #if (KLU >= KLU_VERSION_CODE (1,2))
 *          printf ("This is version 1.2 or later\n") ;
 *      #else
 *          printf ("This is an early version\n") ;
 *      #endif
 */

#define KLU_DATE "July 25, 2025"
#define KLU_MAIN_VERSION   2
#define KLU_SUB_VERSION    3
#define KLU_SUBSUB_VERSION 6

#define KLU_VERSION_CODE(main,sub) SUITESPARSE_VER_CODE(main,sub)
#define KLU_VERSION KLU_VERSION_CODE(2,3)

#define KLU__VERSION SUITESPARSE__VERCODE(2,3,6)
#if !defined (SUITESPARSE__VERSION) || \
    (SUITESPARSE__VERSION < SUITESPARSE__VERCODE(7,11,0))
#error "KLU 2.3.6 requires SuiteSparse_config 7.11.0 or later"
#endif

#if !defined (AMD__VERSION) || \
    (AMD__VERSION < SUITESPARSE__VERCODE(3,3,4))
#error "KLU 2.3.6 requires AMD 3.3.4 or later"
#endif

#if !defined (COLAMD__VERSION) || \
    (COLAMD__VERSION < SUITESPARSE__VERCODE(3,3,5))
#error "KLU 2.3.6 requires COLAMD 3.3.5 or later"
#endif

#if !defined (BTF__VERSION) || \
    (BTF__VERSION < SUITESPARSE__VERCODE(2,3,3))
#error "KLU 2.3.6 requires BTF 2.3.3 or later"
#endif

#endif

