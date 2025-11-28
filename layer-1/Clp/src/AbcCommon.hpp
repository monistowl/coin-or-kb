// Copyright (C) 2003, International Business Machines
// Corporation and others, Copyright (C) 2012, FasterCoin.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file AbcCommon.hpp
 * @brief Configuration macros for ABC (A Better Clp) build modes
 * @author John Forrest (FasterCoin, 2012)
 *
 * Controls how the ABC optimized simplex code is built and integrated.
 *
 * CLP_HAS_ABC values:
 * - 0: ABC disabled (use standard ClpSimplex only)
 * - 1: Serial ABC, standalone (no inheritance into ClpSimplex)
 * - 2: Serial ABC with inheritance (ClpSimplex can delegate to ABC)
 * - 3: Cilk parallel ABC, standalone
 * - 4: Cilk parallel ABC with inheritance
 *
 * ABC_PARALLEL values:
 * - 0: No parallelization
 * - 1: Use pthreads for parallelization
 * - 2: Use Intel Cilk Plus for parallelization
 *
 * ABC_INHERIT: When defined, ClpSimplex::initialSolve() can automatically
 * use AbcSimplex when beneficial.
 *
 * @see AbcSimplex for the optimized simplex implementation
 * @see ClpSimplex for the standard implementation
 */

#ifndef AbcCommon_H
#define AbcCommon_H

#include "ClpConfig.h"

/*
  0 - off
  1 - build Abc serial but no inherit code
  2 - build Abc serial and inherit code
  3 - build Abc cilk parallel but no inherit code
  4 - build Abc cilk parallel and inherit code
 */
#ifdef CLP_HAS_ABC
#if CLP_HAS_ABC == 1
#ifndef ABC_PARALLEL
#define ABC_PARALLEL 0
#endif
#ifndef ABC_USE_HOMEGROWN_LAPACK
#define ABC_USE_HOMEGROWN_LAPACK 2
#endif
#elif CLP_HAS_ABC == 2
#ifndef ABC_PARALLEL
#define ABC_PARALLEL 0
#endif
#ifndef ABC_USE_HOMEGROWN_LAPACK
#define ABC_USE_HOMEGROWN_LAPACK 2
#endif
#ifndef ABC_INHERIT
#define ABC_INHERIT
#ifndef CLP_INHERIT_MODE
#define CLP_INHERIT_MODE 2
#endif
#endif
#elif CLP_HAS_ABC == 3
#ifndef ABC_PARALLEL
#define ABC_PARALLEL 2
#endif
#ifndef ABC_USE_HOMEGROWN_LAPACK
#define ABC_USE_HOMEGROWN_LAPACK 2
#endif
#elif CLP_HAS_ABC == 4
#ifndef ABC_PARALLEL
#define ABC_PARALLEL 2
#endif
#ifndef ABC_USE_HOMEGROWN_LAPACK
#define ABC_USE_HOMEGROWN_LAPACK 2
#endif
#ifndef ABC_INHERIT
#define ABC_INHERIT
#endif
#else
#error "Valid values for CLP_HAS_ABC are 0-4"
#endif
#endif
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
