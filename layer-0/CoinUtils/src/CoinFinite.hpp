// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinFinite.hpp
 * @brief Numeric limit constants and floating-point validation functions
 *
 * Provides platform-independent definitions for numeric limits (COIN_DBL_MAX,
 * COIN_INT_MAX, etc.) and functions to check for special floating-point values
 * (infinity, NaN). These are fundamental utilities used throughout COIN-OR
 * for bounds checking and numerical validation.
 *
 * @see CoinIsnan(), CoinFinite()
 */

#ifndef CoinFinite_H
#define CoinFinite_H

#include "CoinUtilsConfig.h"
#include <limits>

//=============================================================================
/**
 * @name Numeric Limit Constants
 * @brief Platform-independent numeric limits for double and int types
 *
 * These constants wrap std::numeric_limits to provide consistent names
 * across the COIN-OR codebase. The extra parentheses around min()/max()
 * prevent macro expansion issues on Windows where min/max may be defined.
 * @{
 */

#if 1
/** @brief Smallest positive normalized double value */
const double COIN_DBL_MIN = (std::numeric_limits< double >::min)();

/** @brief Largest finite double value (used as "infinity" bound) */
const double COIN_DBL_MAX = (std::numeric_limits< double >::max)();

/** @brief Largest int value */
const int COIN_INT_MAX = (std::numeric_limits< int >::max)();

/** @brief Largest int value as double (for mixed int/double comparisons) */
const double COIN_INT_MAX_AS_DOUBLE = (std::numeric_limits< int >::max)();
#else
#define COIN_DBL_MIN (std::numeric_limits< double >::min())
#define COIN_DBL_MAX (std::numeric_limits< double >::max())
#define COIN_INT_MAX (std::numeric_limits< int >::max())
#define COIN_INT_MAX_AS_DOUBLE (std::numeric_limits< int >::max())
#endif

/** @} */

/**
 * @brief Check if a double value is finite (not infinity and not NaN)
 *
 * @param val The value to test
 * @return true if val is a finite number, false if infinity or NaN
 *
 * @see CoinIsnan()
 */
extern COINUTILSLIB_EXPORT bool CoinFinite(double val);

/**
 * @brief Check if a double value is NaN (Not a Number)
 *
 * @param val The value to test
 * @return true if val is NaN, false otherwise
 *
 * @see CoinFinite()
 */
extern COINUTILSLIB_EXPORT bool CoinIsnan(double val);

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
