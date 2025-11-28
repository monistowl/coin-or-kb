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
 * **IIS Definition:**
 * - Minimal infeasible subsystem: removing any constraint makes it feasible
 * - Helps diagnose why an LP is infeasible
 * - Also identifies which variable bounds participate
 *
 * **IisBoundStatus:**
 * - kDropped: Bound removed from IIS
 * - kNull: Not yet classified
 * - kFree: Variable is free (not in IIS)
 * - kLower/kUpper/kBoxed: Which bound(s) are in IIS
 *
 * **Algorithm:**
 * - compute(): Main IIS computation using simplex iterations
 * - trivial(): Check for obviously infeasible (single row/col)
 * - rowValueBounds(): Check row activity vs bounds
 *
 * **Strategy:**
 * - kIisStrategyMin: Minimize IIS size (more iterations)
 * - Iteratively removes constraints until minimal set remains
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
