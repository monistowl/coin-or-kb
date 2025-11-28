/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsSeparation.h
 * @brief Cut generation orchestration for MIP solver
 *
 * Coordinates multiple separators to generate cutting planes.
 *
 * **Separation Management:**
 * - separators[]: Collection of HighsSeparator instances
 * - cutset: HighsCutSet accumulating generated cuts
 * - implBoundClock, cliqueClock: Timing for specific separator types
 *
 * **Key Methods:**
 * - separationRound(): Run all separators once
 * - separate(): Multiple rounds until no more cuts found
 * - setLpRelaxation(): Bind to LP for solution access
 *
 * **Separator Types (via HighsSeparator subclasses):**
 * - Gomory cuts from optimal basis
 * - MIR (mixed-integer rounding)
 * - Clique cuts from conflict graph
 * - Implied bound cuts from VUB/VLB
 * - Flow cover cuts
 *
 * @see mip/HighsSeparator.h for separator base class
 * @see mip/HighsCutPool.h for cut storage
 * @see mip/HighsLpRelaxation.h for LP interface
 */
#ifndef HIGHS_SEPARATION_H_
#define HIGHS_SEPARATION_H_

#include <cstdint>
#include <vector>

#include "mip/HighsCutPool.h"
#include "mip/HighsLpRelaxation.h"
#include "mip/HighsSeparator.h"

class HighsMipSolver;
class HighsImplications;
class HighsCliqueTable;

class HighsSeparation {
 public:
  HighsInt separationRound(HighsDomain& propdomain,
                           HighsLpRelaxation::Status& status);

  void separate(HighsDomain& propdomain);

  void setLpRelaxation(HighsLpRelaxation* lp) { this->lp = lp; }

  HighsSeparation(const HighsMipSolver& mipsolver);

 private:
  HighsInt implBoundClock;
  HighsInt cliqueClock;
  std::vector<std::unique_ptr<HighsSeparator>> separators;
  HighsCutSet cutset;
  HighsLpRelaxation* lp;
};

#endif
