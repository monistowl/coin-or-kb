// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinWarmStart.hpp
 * @brief Abstract interfaces for warm start information in optimization solvers
 *
 * Defines abstract base classes for storing and manipulating warm start
 * information. Warm starts allow solvers to resume from a previous solution
 * state, potentially reducing solution time significantly. The diff mechanism
 * allows efficient incremental updates to warm start information.
 *
 * Derived classes implement solver-specific warm start data (e.g., basis
 * status for simplex, barrier iterates for interior point methods).
 *
 * @see CoinWarmStartBasis for a common implementation (simplex basis)
 */

#ifndef CoinWarmStart_H
#define CoinWarmStart_H

#include "CoinUtilsConfig.h"

//#############################################################################

class COINUTILSLIB_EXPORT CoinWarmStartDiff;

/**
 * @brief Abstract base class for warm start information
 *
 * Provides the interface for warm start objects that store solver state
 * enabling faster re-optimization. Derived classes implement solver-specific
 * storage (e.g., variable/constraint basis status for simplex methods).
 *
 * The class supports a diff mechanism for efficient incremental updates:
 * - generateDiff() computes changes from another warm start
 * - applyDiff() applies a diff to update this warm start
 *
 * @see CoinWarmStartDiff, CoinWarmStartBasis
 */
class COINUTILSLIB_EXPORT CoinWarmStart {
public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes
   */
  virtual ~CoinWarmStart() {}

  /**
   * @brief Create a deep copy of this warm start object
   * @return Pointer to newly allocated copy (caller owns memory)
   */
  virtual CoinWarmStart *clone() const = 0;

  /**
   * @brief Generate a diff representing changes from another warm start
   *
   * Computes the difference between this warm start and another, enabling
   * efficient storage of incremental changes.
   *
   * @param oldWarmStart The baseline warm start to compare against
   * @return Pointer to diff object (caller owns memory), or nullptr if not supported
   *
   * @see applyDiff()
   */
  virtual CoinWarmStartDiff *
  generateDiff(const CoinWarmStart *const oldWarmStart) const { return 0; }

  /**
   * @brief Apply a diff to update this warm start
   *
   * Modifies this warm start by applying changes encoded in the diff object.
   *
   * @param diff The diff to apply
   *
   * @see generateDiff()
   */
  virtual void
  applyDiff(const CoinWarmStartDiff *const diff) {}
};

/**
 * @brief Abstract base class for warm start diff objects
 *
 * Represents the difference between two warm start states. Used for
 * efficient incremental updates when the warm start changes only slightly
 * between solves (common in branch-and-bound or sensitivity analysis).
 *
 * @see CoinWarmStart::generateDiff(), CoinWarmStart::applyDiff()
 */
class COINUTILSLIB_EXPORT CoinWarmStartDiff {
public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes
   */
  virtual ~CoinWarmStartDiff() {}

  /**
   * @brief Create a deep copy of this diff object
   * @return Pointer to newly allocated copy (caller owns memory)
   */
  virtual CoinWarmStartDiff *clone() const = 0;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
