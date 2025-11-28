/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file simplex/HSimplexDebug.h
 * @brief Debug utilities for simplex algorithm validation
 *
 * Functions to detect numerical issues and algorithm failures.
 *
 * **CHUZC Failure Diagnosis:**
 * - debugDualChuzcFailNorms(): Compute norms for failure analysis
 * - debugDualChuzcFailQuad0/1(): Check quadratic pricing failures
 * - debugDualChuzcFailHeap(): Check heap-based pricing failures
 *
 * **Basis Validation:**
 * - debugNonbasicFlagConsistent(): Verify nonbasicFlag matches basis
 *
 * **Usage:**
 * Called when simplex encounters unexpected conditions:
 * - Ratio test returns no candidate
 * - Basis becomes numerically unstable
 * - Iteration cycling detected
 *
 * **Return Type:**
 * HighsDebugStatus indicates severity:
 * - kOk: No issues detected
 * - kWarning: Potential numerical concern
 * - kError: Algorithmic failure
 *
 * @see simplex/HEkkDual.h for dual simplex CHUZC
 * @see simplex/HEkkPrimal.h for primal simplex CHUZR
 */
#ifndef SIMPLEX_HSIMPLEXDEBUG_H_
#define SIMPLEX_HSIMPLEXDEBUG_H_

#include <set>

#include "lp_data/HighsLpSolverObject.h"

// Methods for Ekk

void debugDualChuzcFailNorms(
    const HighsInt workCount,
    const std::vector<std::pair<HighsInt, double>>& workData,
    double& workDataNorm, const HighsInt numVar, const double* workDual,
    double& workDualNorm);

HighsDebugStatus debugDualChuzcFailQuad0(
    const HighsOptions& options, const HighsInt workCount,
    const std::vector<std::pair<HighsInt, double>>& workData,
    const HighsInt numVar, const double* workDual, const double selectTheta,
    const double remainTheta, const bool force = false);

HighsDebugStatus debugDualChuzcFailQuad1(
    const HighsOptions& options, const HighsInt workCount,
    const std::vector<std::pair<HighsInt, double>>& workData,
    const HighsInt numVar, const double* workDual, const double selectTheta,
    const bool force = false);

HighsDebugStatus debugDualChuzcFailHeap(
    const HighsOptions& options, const HighsInt workCount,
    const std::vector<std::pair<HighsInt, double>>& workData,
    const HighsInt numVar, const double* workDual, const double selectTheta,
    const bool force = false);

HighsDebugStatus debugNonbasicFlagConsistent(const HighsOptions& options,
                                             const HighsLp& lp,
                                             const SimplexBasis& basis);

#endif  // SIMPLEX_HSIMPLEXDEBUG_H_
