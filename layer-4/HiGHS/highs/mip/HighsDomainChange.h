/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsDomainChange.h
 * @brief Variable bound modifications for MIP branch-and-bound
 *
 * Represents changes to variable bounds during MIP solving.
 *
 * **HighsDomainChange:**
 * - column: Variable index
 * - boundtype: kLower or kUpper
 * - boundval: New bound value
 * - Comparable for storage in sorted containers
 *
 * Used in branching, propagation, and conflict analysis to track
 * and undo bound changes during tree search.
 *
 * **HighsSubstitution:**
 * Records variable substitution: staycol = scale * substcol + offset.
 * Used when presolve eliminates variables.
 *
 * @see mip/HighsDomain.h for domain propagation
 * @see mip/HighsSearch.h for branch-and-bound
 */
#ifndef HIGHS_DOMAIN_CHANGE_H_
#define HIGHS_DOMAIN_CHANGE_H_

#include "util/HighsInt.h"

enum class HighsBoundType { kLower, kUpper };

struct HighsDomainChange {
  double boundval;
  HighsInt column;
  HighsBoundType boundtype;

  bool operator<(const HighsDomainChange& other) const {
    if (column < other.column) return true;
    if (other.column < column) return false;
    if ((HighsInt)boundtype < (HighsInt)other.boundtype) return true;
    if ((HighsInt)other.boundtype < (HighsInt)boundtype) return false;
    if (boundval < other.boundval) return true;
    return false;
  }

  bool operator==(const HighsDomainChange& other) const {
    return boundtype == other.boundtype && column == other.column &&
           boundval == other.boundval;
  }

  bool operator!=(const HighsDomainChange& other) const {
    return boundtype != other.boundtype || column != other.column ||
           boundval != other.boundval;
  }
};

struct HighsSubstitution {
  HighsInt substcol;
  HighsInt staycol;
  double scale;
  double offset;
};

#endif
