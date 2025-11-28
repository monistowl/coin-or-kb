/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file simplex/HSimplexReport.h
 * @brief Simplex iteration progress reporting
 *
 * Functions for logging simplex solve progress.
 *
 * **reportSimplexPhaseIterations():**
 * Reports iteration counts and phase transitions:
 * - iteration_count: Total simplex iterations
 * - info: HighsSimplexInfo with infeasibility counts
 * - initialise: Reset counters for new phase
 *
 * **Output Includes:**
 * - Phase 1/2 transition points
 * - Iteration milestones
 * - Infeasibility reduction progress
 *
 * @see simplex/HEkk.h for simplex solver using this
 * @see simplex/HighsSimplexAnalysis.h for detailed analysis
 */
#ifndef SIMPLEX_HSIMPLEXREPORT_H_
#define SIMPLEX_HSIMPLEXREPORT_H_

#include "lp_data/HighsOptions.h"
#include "simplex/HSimplex.h"

void reportSimplexPhaseIterations(const HighsLogOptions& log_options,
                                  const HighsInt iteration_count,
                                  HighsSimplexInfo& info,
                                  const bool initialise = false);
#endif  // SIMPLEX_HSIMPLEXREPORT_H_
