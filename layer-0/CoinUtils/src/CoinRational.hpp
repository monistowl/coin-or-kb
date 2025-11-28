// Authors: Matthew Saltzman and Ted Ralphs
// Copyright 2015, Matthew Saltzman and Ted Ralphs
// Licensed under the Eclipse Public License

/**
 * @file CoinRational.hpp
 * @brief Rational number representation with double-to-rational conversion
 *
 * Provides a simple rational number class that can convert floating-point
 * values to rational approximations. Useful in optimization for converting
 * floating-point coefficients to exact rational form when needed.
 */

#ifndef CoinRational_H
#define CoinRational_H

#include <cmath>

#include "CoinUtilsConfig.h"

#if defined(COINUTILS_HAS_CSTDINT)
#include <cstdint>
#elif defined(COINUTILS_HAS_STDINT_H)
#include <stdint.h>
#endif

/**
 * @brief Simple rational number class with numerator and denominator
 *
 * Stores a rational number as a ratio of two 64-bit integers. Can be
 * constructed directly from numerator/denominator or by finding the
 * nearest rational approximation to a floating-point value.
 */
class COINUTILSLIB_EXPORT CoinRational
{

public:
  /**
   * @brief Get the denominator of this rational
   * @return The denominator value
   */
  int64_t getDenominator() { return denominator_; }

  /**
   * @brief Get the numerator of this rational
   * @return The numerator value
   */
  int64_t getNumerator() { return numerator_; }

  /**
   * @brief Default constructor creating rational 0/1
   */
  CoinRational()
    : numerator_(0)
    , denominator_(1) {};

  /**
   * @brief Construct rational from explicit numerator and denominator
   *
   * @param n Numerator
   * @param d Denominator (must not be zero)
   */
  CoinRational(int64_t n, int64_t d)
    : numerator_(n)
    , denominator_(d) {};

  /**
   * @brief Construct by finding nearest rational to a double value
   *
   * Finds a rational p/q such that |val - p/q| <= maxdelta and q <= maxdnom.
   * If no such rational exists within constraints, sets value to 0/1.
   *
   * @param val The floating-point value to approximate
   * @param maxdelta Maximum allowed absolute error
   * @param maxdnom Maximum allowed denominator
   *
   * @algorithm Stern-Brocot tree / mediant search for best rational approximation
   * @math Given lower bound a/b and upper bound c/d, the mediant (a+c)/(b+d)
   *       is the simplest rational between them. Binary search narrows to
   *       the best approximation within tolerance.
   * @complexity O(log(maxdnom)) iterations
   * @ref Stern (1858), Brocot (1861). See also: Graham, Knuth, Patashnik
   *      "Concrete Mathematics" Ch. 4.5 for Stern-Brocot tree theory.
   */
  CoinRational(double val, double maxdelta, int64_t maxdnom)
  {
    if (!nearestRational_(val, maxdelta, maxdnom)) {
      numerator_ = 0;
      denominator_ = 1;
    }
  };

private:
  int64_t numerator_;    ///< The numerator of the rational
  int64_t denominator_;  ///< The denominator of the rational

  /**
   * @brief Find nearest rational approximation to a double
   *
   * @param val Value to approximate
   * @param maxdelta Maximum error tolerance
   * @param maxdnom Maximum denominator allowed
   * @return true if a valid approximation was found, false otherwise
   *
   * @algorithm Stern-Brocot mediant search
   * @math Maintains interval [a/b, c/d] containing val. Each step computes
   *       mediant m = (a+c)/(b+d) and narrows interval. Terminates when
   *       |val - m| <= maxdelta or denominator exceeds maxdnom.
   * @complexity O(log(maxdnom)) - each step at least doubles denominator
   */
  bool nearestRational_(double val, double maxdelta, int64_t maxdnom);
};

//#############################################################################
/**
 * @brief Unit test for CoinRational class
 *
 * Tests the rational number methods including construction, conversion,
 * and the nearest rational approximation algorithm. Defined outside the
 * class so it can be compiled with debug flags while the library uses
 * optimization.
 */
void CoinRationalUnitTest();

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
