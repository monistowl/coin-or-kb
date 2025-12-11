/**
 * @file lu_def.h
 * @brief Basic definitions, macros, and inline utilities for BasicLU
 *
 * Provides foundational types and helper functions used throughout BasicLU:
 * - Standard library includes (stdlib, math, stdint, assert)
 * - MIN/MAX macros for value comparisons
 * - Inline swap functions for lu_int and double arrays
 * - Task enumeration for factorization phases
 * - BASICLU_HASH constant for instance validation
 *
 * @see basiclu.h for the public interface
 * @see lu_internal.h for the main internal data structure
 */
#ifndef _LU_DEF_H
#define _LU_DEF_H

/* -------------------------------------------------------------------------- */
/* ANSI standard include files */
/* -------------------------------------------------------------------------- */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>

#include "ipm/basiclu/basiclu.h"

#define BASICLU_HASH 7743090    /* hash in istore[0], xstore[0] */

enum { NO_TASK, SINGLETONS, SETUP_BUMP, FACTORIZE_BUMP, BUILD_FACTORS };

/* -------------------------------------------------------------------------- */
/* standard macros and inlines */
/* -------------------------------------------------------------------------- */

#define MAX(a,b) ((a)>=(b) ? (a):(b))
#define MIN(a,b) ((a)<=(b) ? (a):(b))

static inline void lu_iswap(lu_int *x, lu_int i, lu_int j)
{
    lu_int t = x[i]; x[i] = x[j]; x[j] = t;
}

static inline void lu_fswap(double *x, lu_int i, lu_int j)
{
    double t = x[i]; x[i] = x[j]; x[j] = t;
}

#endif
