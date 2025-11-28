// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinUtility.hpp
 * @brief Factory functions for CoinPair and CoinTriple
 *
 * Provides convenience functions for creating CoinPair and CoinTriple objects
 * with automatic template argument deduction, similar to std::make_pair.
 *
 * @see CoinSort.hpp for CoinPair and CoinTriple definitions
 */

#ifndef CoinUtility_h_
#define CoinUtility_h_

#include "CoinSort.hpp"

/**
 * @brief Create a CoinPair with automatic type deduction
 *
 * Factory function that creates a CoinPair without requiring explicit
 * template arguments.
 *
 * @tparam S Type of the first element
 * @tparam T Type of the second element
 * @param s First element value
 * @param t Second element value
 * @return A CoinPair containing copies of s and t
 *
 * @see CoinPair, CoinMakeTriple()
 */
template < typename S, typename T >
CoinPair< S, T > CoinMakePair(const S &s, const T &t)
{
  return CoinPair< S, T >(s, t);
}

/**
 * @brief Create a CoinTriple with automatic type deduction
 *
 * Factory function that creates a CoinTriple without requiring explicit
 * template arguments.
 *
 * @tparam S Type of the first element
 * @tparam T Type of the second element
 * @tparam U Type of the third element
 * @param s First element value
 * @param t Second element value
 * @param u Third element value
 * @return A CoinTriple containing copies of s, t, and u
 *
 * @see CoinTriple, CoinMakePair()
 */
template < typename S, typename T, typename U >
CoinTriple< S, T, U > CoinMakeTriple(const S &s, const T &t, const U &u)
{
  return CoinTriple< S, T, U >(s, t, u);
}

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
