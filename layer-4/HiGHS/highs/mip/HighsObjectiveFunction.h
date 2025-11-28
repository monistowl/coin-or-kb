/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsObjectiveFunction.h
 * @brief Objective function analysis for MIP solving
 *
 * Analyzes objective structure to enable specialized bound propagation.
 *
 * **Objective Structure:**
 * - objectiveNonzeros[]: Columns with nonzero objective (binaries first)
 * - objectiveVals[]: Packed objective coefficients
 * - numBinary/numIntegral: Variable counts by type
 *
 * **Integrality Detection:**
 * - objIntScale: Scale factor making all integer coefficients integral
 * - isIntegral(): True if objective is integer for integer solutions
 * - checkIntegrality(): Verify/update integrality with epsilon
 * - Enables objective cutoff rounding
 *
 * **Clique Partitioning:**
 * Partitions binary objective variables into cliques:
 * - cliquePartitionStart[]: Start indices per partition
 * - colToPartition[]: Maps column to its partition
 * - At most one variable per clique can be 1
 * - Enables tighter objective bounds from clique constraints
 *
 * **Usage:**
 * - Objective bound computation during propagation
 * - Detecting integral objectives for cutoff strengthening
 * - Clique-based objective probing
 *
 * @see mip/HighsCliqueTable.h for clique detection
 * @see mip/HighsDomain.h for bound propagation using objective
 */
#ifndef HIGHS_OBJECTIVE_FUNCTION_H_
#define HIGHS_OBJECTIVE_FUNCTION_H_

#include <algorithm>
#include <cassert>
#include <vector>

#include "util/HighsInt.h"

class HighsCliqueTable;
class HighsDomain;
class HighsLp;
class HighsMipSolver;

class HighsObjectiveFunction {
  const HighsLp* model;
  double objIntScale;
  HighsInt numIntegral;
  HighsInt numBinary;
  std::vector<HighsInt> objectiveNonzeros;
  std::vector<double> objectiveVals;
  std::vector<HighsInt> cliquePartitionStart;
  std::vector<HighsInt> colToPartition;

 public:
  HighsObjectiveFunction(const HighsMipSolver& mipsolver);

  void setupCliquePartition(const HighsDomain& globaldom,
                            HighsCliqueTable& cliqueTable);

  void checkIntegrality(double epsilon);

  /// returns the vector of column indices with nonzero objective value
  /// They will be ordered so that binary columns come first
  const std::vector<HighsInt>& getObjectiveNonzeros() const {
    return objectiveNonzeros;
  }

  const std::vector<double>& getObjectiveValuesPacked() const {
    return objectiveVals;
  }

  HighsInt getNumBinariesInObjective() const { return numBinary; }

  const std::vector<HighsInt>& getCliquePartitionStarts() const {
    return cliquePartitionStart;
  }

  HighsInt getNumCliquePartitions() const {
    return cliquePartitionStart.size() - 1;
  }

  HighsInt getColCliquePartition(HighsInt col) const {
    return colToPartition[col];
  }

  double integralScale() const { return objIntScale; }

  bool isIntegral() const { return objIntScale != 0.0; }

  bool isZero() const { return objectiveNonzeros.empty(); }
};

#endif
