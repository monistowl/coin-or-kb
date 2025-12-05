/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsSeparator.h
 * @brief Abstract base class for cut separators
 *
 * @algorithm Cut Separator Interface
 *
 * Defines interface for generating cutting planes from LP relaxation.
 *
 * **Separator Types (string constants):**
 * - kImplboundSepaString: Implied bound cuts from VUB/VLB
 * - kCliqueSepaString: Clique cuts from conflict graph
 * - kTableauSepaString: Tableau-based cuts (Gomory)
 * - kPathAggrSepaString: Path aggregation cuts
 * - kModKSepaString: Mod-k cuts
 *
 * **Abstract Interface:**
 * - separateLpSolution(): Generate cuts from current LP solution
 *   - lpRelaxation: Access to LP solution and basis
 *   - lpAggregator: Row aggregation helper
 *   - transLp: Transformed LP with bound substitutions
 *   - cutpool: Destination for generated cuts
 *
 * **Statistics:**
 * - numCutsFound: Total cuts generated
 * - numCalls: Times separator was invoked
 * - clockIndex: Timer index for profiling
 *
 * **Usage:**
 * - run(): Wrapper that times and counts separateLpSolution()
 * - Subclasses implement specific cut types
 *
 * @see mip/HighsSeparation.h for separator orchestration
 * @see mip/HighsCutPool.h for cut storage
 */

#ifndef MIP_HIGHS_SEPARATOR_H_
#define MIP_HIGHS_SEPARATOR_H_

#include <string>

#include "util/HighsInt.h"

const std::string kImplboundSepaString = "Separation: Implied bounds";
const std::string kCliqueSepaString = "Separation: Clique";
const std::string kTableauSepaString = "Separation: Tableau";
const std::string kPathAggrSepaString = "Separation: Path aggregation";
const std::string kModKSepaString = "Separation: Mod-k";

class HighsLpRelaxation;
class HighsTransformedLp;
class HighsCutPool;
class HighsLpAggregator;
class HighsMipSolver;

/// Helper class to compute single-row relaxations from the current LP
/// relaxation by substituting bounds and aggregating rows
class HighsSeparator {
 private:
  HighsInt numCutsFound;
  HighsInt numCalls;
  int clockIndex;

 public:
  HighsSeparator(const HighsMipSolver& mipsolver, const std::string& name);

  virtual void separateLpSolution(HighsLpRelaxation& lpRelaxation,
                                  HighsLpAggregator& lpAggregator,
                                  HighsTransformedLp& transLp,
                                  HighsCutPool& cutpool) = 0;

  void run(HighsLpRelaxation& lpRelaxation, HighsLpAggregator& lpAggregator,
           HighsTransformedLp& transLp, HighsCutPool& cutpool);

  HighsInt getNumCutsFound() const { return numCutsFound; }

  HighsInt getNumCalls() const { return numCalls; }

  HighsInt getClockIndex() const { return clockIndex; }

  virtual ~HighsSeparator() {}
};

#endif
