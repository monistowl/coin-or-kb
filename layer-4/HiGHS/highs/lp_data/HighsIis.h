/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file lp_data/HighsIis.h
 * @brief Irreducible Infeasible Set (IIS) computation for infeasible LPs
 *
 * Identifies minimal subset of constraints that cannot be satisfied.
 *
 * @algorithm IIS Computation via Deletion Filter:
 *   Find minimal infeasible subsystem by iterative constraint removal:
 *   @math Given infeasible Ax ≤ b, find minimal I ⊆ {1,...,m}
 *         such that A_I x ≤ b_I infeasible, but removing any row makes feasible.
 *         Deletion: For each row i in current set, check if feasible without i.
 *         If feasible: keep row in IIS. If infeasible: row not essential.
 *   @complexity O(k·LP) where k ≤ m is IIS size. Each check is one LP solve.
 *   @ref Gleeson & Ryan (1990). "Identifying minimally infeasible subsystems
 *        of inequalities". ORSA Journal on Computing.
 *
 * @algorithm Elastic Filter Enhancement:
 *   Speed up IIS identification using elastic variables:
 *   @math Add elastic variables e_i ≥ 0 to each constraint: a_i'x ≤ b_i + e_i
 *         Minimize Σ e_i. Constraints with e_i > 0 in optimal are candidates.
 *         Reduces number of LP solves needed for deletion filter.
 *   @ref Chinneck & Dravnieks (1991). "Locating minimal infeasible constraint
 *        sets in linear programs".
 *
 * **IIS Definition:**
 * - Minimal infeasible subsystem: removing any constraint makes it feasible
 * - Helps diagnose why an LP is infeasible
 * - Also identifies which variable bounds participate
 *
 * **Output:**
 * - col_index_/row_index_: Variables/constraints in IIS
 * - col_bound_/row_bound_: Which bounds contribute
 * - info_: Simplex stats per iteration
 *
 * @see Highs.h for getIis() API
 */
#ifndef LP_DATA_HIGHSIIS_H_
#define LP_DATA_HIGHSIIS_H_

#include "model/HighsModel.h"

const bool kIisDevReport = false;

enum IisBoundStatus {
  kIisBoundStatusDropped = -1,
  kIisBoundStatusNull,   // 0
  kIisBoundStatusFree,   // 1
  kIisBoundStatusLower,  // 2
  kIisBoundStatusUpper,  // 3
  kIisBoundStatusBoxed   // 4
};

struct HighsIisInfo {
  double simplex_time = 0;
  HighsInt simplex_iterations = 0;
};

class HighsIis {
 public:
  HighsIis() {}

  void invalidate();
  std::string iisBoundStatusToString(HighsInt bound_status) const;
  void report(const std::string message, const HighsLp& lp) const;
  void addCol(const HighsInt col, const HighsInt status = kIisBoundStatusNull);
  void addRow(const HighsInt row, const HighsInt status = kIisBoundStatusNull);
  void removeCol(const HighsInt col);
  void removeRow(const HighsInt row);
  HighsStatus getData(const HighsLp& lp, const HighsOptions& options,
                      const HighsBasis& basis,
                      const std::vector<HighsInt>& infeasible_row);
  void getLp(const HighsLp& lp);
  void getStatus(const HighsLp& lp);

  HighsStatus compute(const HighsLp& lp, const HighsOptions& options,
                      const HighsBasis* basis = nullptr);

  bool trivial(const HighsLp& lp, const HighsOptions& options);
  bool rowValueBounds(const HighsLp& lp, const HighsOptions& options);

  bool lpDataOk(const HighsLp& lp, const HighsOptions& options) const;
  bool lpOk(const HighsOptions& options) const;

  // Data members
  bool valid_ = false;
  HighsInt strategy_ = kIisStrategyMin;
  std::vector<HighsInt> col_index_;
  std::vector<HighsInt> row_index_;
  std::vector<HighsInt> col_bound_;
  std::vector<HighsInt> row_bound_;
  std::vector<HighsInt> col_status_;
  std::vector<HighsInt> row_status_;
  std::vector<HighsIisInfo> info_;
  HighsModel model_;
};

#endif  // LP_DATA_HIGHSIIS_H_
