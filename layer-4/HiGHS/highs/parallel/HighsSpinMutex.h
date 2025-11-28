/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file parallel/HighsSpinMutex.h
 * @brief Lightweight spin lock for short critical sections
 *
 * Busy-waits instead of blocking, ideal for short-held locks.
 *
 * **HighsSpinMutex Class:**
 * Simple test-and-set spin lock:
 * - flag: Atomic bool (false = unlocked)
 * - try_lock(): Non-blocking lock attempt
 * - lock(): Spin until acquired
 * - unlock(): Release with release semantics
 *
 * **Spinning Strategy:**
 * - yieldProcessor(): CPU hint during spin wait
 *   - x86: _mm_pause() (reduces power, prevents pipeline stalls)
 *   - Others: std::this_thread::yield()
 *
 * **TTAS Pattern:**
 * Test-and-Test-and-Set for reduced bus traffic:
 * 1. Exchange to try acquiring
 * 2. If failed, spin on load (cache-local)
 * 3. Only retry exchange when flag appears free
 *
 * **When to Use:**
 * Prefer over std::mutex when critical sections are very short
 * and contention is low. Avoids syscall overhead.
 *
 * @see parallel/HighsTaskExecutor.h for task queue locking
 */
#ifndef HIGHS_SPIN_MUTEX_H_
#define HIGHS_SPIN_MUTEX_H_

#include <atomic>

#include "HConfig.h"

#ifdef HIGHS_HAVE_MM_PAUSE
#include <immintrin.h>
#else
#include <thread>
#endif

class HighsSpinMutex {
  std::atomic<bool> flag{false};

 public:
  static void yieldProcessor() {
#ifdef HIGHS_HAVE_MM_PAUSE
    _mm_pause();
#else
    // ToDo: See if this is OK on Mac M1
    std::this_thread::yield();
#endif
  }

  bool try_lock() { return !flag.exchange(true, std::memory_order_acquire); }

  void lock() {
    while (true) {
      if (!flag.exchange(true, std::memory_order_acquire)) return;

      while (flag.load(std::memory_order_relaxed)) yieldProcessor();
    }
  }

  void unlock() { flag.store(false, std::memory_order_release); }
};

#endif
