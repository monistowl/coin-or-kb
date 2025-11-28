// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinDistance.hpp
 * @brief Platform-independent iterator distance utilities
 *
 * Provides wrapper functions around std::distance to ensure consistent
 * behavior across different compilers and platforms. These utilities are
 * used throughout COIN-OR for iterator-based calculations.
 */

#ifndef CoinDistance_H
#define CoinDistance_H

#include <iterator>

/**
 * @brief Calculate distance between iterators (output parameter version)
 *
 * Computes the number of increments needed to get from first to last,
 * storing the result in the output parameter n.
 *
 * @tparam ForwardIterator Iterator type (must satisfy ForwardIterator requirements)
 * @tparam Distance Integral type to store the result
 * @param first Iterator to the beginning of the range
 * @param last Iterator to the end of the range
 * @param[out] n Output parameter receiving the distance
 *
 * @see coinDistance(ForwardIterator, ForwardIterator)
 */
template < class ForwardIterator, class Distance >
void coinDistance(ForwardIterator first, ForwardIterator last,
  Distance &n)
{
  n = std::distance(first, last);
}

/**
 * @brief Calculate distance between iterators (return value version)
 *
 * Computes the number of increments needed to get from first to last.
 *
 * @tparam ForwardIterator Iterator type (must satisfy ForwardIterator requirements)
 * @param first Iterator to the beginning of the range
 * @param last Iterator to the end of the range
 * @return Number of elements between first and last
 *
 * @see coinDistance(ForwardIterator, ForwardIterator, Distance&)
 */
template < class ForwardIterator >
size_t coinDistance(ForwardIterator first, ForwardIterator last)
{
  return std::distance(first, last);
}

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
