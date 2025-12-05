// Copyright (C) 2002, International Business Machines
// Corporation and others, Copyright (C) 2012, FasterCoin.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinAbcFactorization.hpp
 * @brief ABC optimized LU factorization variants
 * @author John Forrest
 *
 * Template-instantiation header that creates multiple factorization variants
 * from CoinAbcBaseFactorization using preprocessor macros.
 *
 * @algorithm ABC Factorization Variants:
 * Different precision/optimization trade-offs for different problem sizes.
 *
 * @algorithm VARIANTS:
 *
 * 1. CoinAbcFactorization: Standard double precision (64-bit)
 *    Default choice for most problems.
 *
 * 2. CoinAbcLongFactorization: Extended precision (80-bit on x86)
 *    COIN_BIG_DOUBLE=1 enables long double arithmetic.
 *    Use when: Ill-conditioned bases cause numerical instability.
 *    Cost: ~2× slower than standard double.
 *
 * 3. CoinAbcSmallFactorization: Cache-optimized for small m
 *    ABC_SMALL=4 enables dense-like storage patterns.
 *    Use when: m < ~200 rows, dense or nearly dense.
 *    Benefit: Better cache utilization than sparse format.
 *
 * 4. CoinAbcOrderedFactorization: For large ordered problems
 *    Maintains column ordering for better parallelism.
 *    Use when: Very large sparse problems with structure.
 *
 * @algorithm SIMD Optimizations (all variants):
 * - Vectorized scatter/gather for L and U updates
 * - Aligned memory for AVX operations
 * - Parallel factorization via ABC_PARALLEL
 *
 * @see CoinAbcBaseFactorization for the actual implementation
 * @see CoinAbcHelperFunctions for SIMD kernels
 */

#ifndef CoinAbcFactorization_H
#define CoinAbcFactorization_H
#include "CoinAbcCommonFactorization.hpp"
#ifndef ABC_JUST_ONE_FACTORIZATION
#define CoinAbcTypeFactorization CoinAbcFactorization
#define ABC_SMALL -1
#include "CoinAbcBaseFactorization.hpp"
#undef CoinAbcTypeFactorization
#undef ABC_SMALL
#undef COIN_BIG_DOUBLE
#define COIN_BIG_DOUBLE 1
#define CoinAbcTypeFactorization CoinAbcLongFactorization
#define ABC_SMALL -1
#include "CoinAbcBaseFactorization.hpp"
#undef CoinAbcTypeFactorization
#undef ABC_SMALL
#undef COIN_BIG_DOUBLE
#define CoinAbcTypeFactorization CoinAbcSmallFactorization
#define ABC_SMALL 4
#include "CoinAbcBaseFactorization.hpp"
#undef CoinAbcTypeFactorization
#undef ABC_SMALL
#define CoinAbcTypeFactorization CoinAbcOrderedFactorization
#define ABC_SMALL -1
#include "CoinAbcBaseFactorization.hpp"
#undef CoinAbcTypeFactorization
#undef ABC_SMALL
#else
#define CoinAbcTypeFactorization CoinAbcBaseFactorization
#define ABC_SMALL -1
#include "CoinAbcBaseFactorization.hpp"
#endif
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
