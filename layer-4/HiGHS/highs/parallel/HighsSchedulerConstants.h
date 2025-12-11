/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file parallel/HighsSchedulerConstants.h
 * @brief Tuning constants for work-stealing scheduler
 *
 * Timing thresholds controlling spin-wait vs blocking behavior.
 *
 * **Constants:**
 * - kNumTryFac (16): Multiplier for steal attempts per worker
 * - kMicroSecsBeforeSleep (5000): Spin duration before blocking
 * - kMicroSecsBeforeGlobalSync (1000): Spin before global coordination
 *
 * These values balance latency (fast response to new work) against
 * CPU usage (avoiding wasteful spinning).
 *
 * @see parallel/HighsBinarySemaphore.h for sleep timing
 * @see parallel/HighsTaskExecutor.h for steal loop timing
 */
#ifndef HIGHS_SCHEDULER_CONSTANTS_H_
#define HIGHS_SCHEDULER_CONSTANTS_H_

struct HighsSchedulerConstants {
  enum Constants {
    kNumTryFac = 16,
    kMicroSecsBeforeSleep = 5000,
    kMicroSecsBeforeGlobalSync = 1000,
  };
};

#endif
