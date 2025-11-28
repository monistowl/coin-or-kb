/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file parallel/HighsRaceTimer.h
 * @brief Lock-free timer for parallel algorithm racing
 *
 * Allows multiple threads to race, with early termination when limit reached.
 *
 * **HighsRaceTimer<T> Class:**
 * Atomic limit value that can only decrease:
 * - Constructor: Initialize limit to max value (no limit)
 * - decreaseLimit(newLimit): Atomically reduce limit (CAS loop)
 * - limitReached(currentTime): Check if time exceeds limit
 *
 * **Memory Ordering:**
 * Uses relaxed ordering since:
 * - Only one direction (decrease) of updates
 * - Eventual consistency sufficient for early termination
 * - No happens-before relationships required
 *
 * **Usage:**
 * Multiple solvers race; first to find solution decreases limit.
 * Slower solvers check limitReached() and abort early.
 *
 * @see mip/HighsSearch.h for parallel node processing
 */
#ifndef HIGHS_RACE_TIMER_H_
#define HIGHS_RACE_TIMER_H_

#include <atomic>
#include <limits>

template <typename T>
class HighsRaceTimer {
  std::atomic<T> limit;

 public:
  HighsRaceTimer() : limit(std::numeric_limits<T>::max()) {}

  void decreaseLimit(T newLimit) {
    T current = limit.load(std::memory_order_relaxed);

    while (current > newLimit) {
      if (limit.compare_exchange_weak(current, newLimit,
                                      std::memory_order_relaxed,
                                      std::memory_order_relaxed))
        break;
    }
  }

  bool limitReached(const T currentTime) const {
    return currentTime > limit.load(std::memory_order_relaxed);
  }
};

#endif
