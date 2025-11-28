/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file presolve/PresolveComponent.h
 * @brief Presolve component for HiGHS pipeline integration
 *
 * Encapsulates presolve as a modular component with data and statistics.
 *
 * **PresolveComponentData:**
 * State managed by presolve component:
 * - reduced_lp_: Presolved LP (smaller problem)
 * - postSolveStack: Operations to undo presolve
 * - recovered_solution_/recovered_basis_: Original-space solution
 * - presolve_log_: Reduction history
 *
 * **PresolveComponentInfo:**
 * Statistics exposed for reporting:
 * - n_rows_removed, n_cols_removed, n_nnz_removed: Reduction counts
 * - Timing information from HighsComponentInfo base
 *
 * **PresolveComponentOptions:**
 * Component-specific settings (extends HighsComponentOptions):
 * - iteration_limit: Maximum presolve passes
 * - Timeout and other controls
 *
 * **PresolveComponent Class:**
 * Main component implementing HighsComponent interface:
 * - init(): Setup with options
 * - run(): Execute presolve
 * - has_run_: Track execution state
 *
 * @see presolve/HPresolve.h for presolve engine
 * @see util/HighsComponent.h for component base class
 * @see presolve/HighsPostsolveStack.h for solution recovery
 */
#ifndef PRESOLVE_PRESOLVE_COMPONENT_H_
#define PRESOLVE_PRESOLVE_COMPONENT_H_

// Not all necessary, but copied from Presolve.h to avoid non-Linux
// failures
#include <list>
#include <map>
#include <stack>
#include <string>
#include <utility>

#include "lp_data/HighsLp.h"
#include "presolve/HighsPostsolveStack.h"
#include "util/HighsComponent.h"
#include "util/HighsTimer.h"

// Class defining the Presolve Component to be used in HiGHS.
// What used to be in Presolve.h but allowing for further testing and dev.

// The structure of component is general, of the presolve component - presolve
// specific.

struct PresolveComponentData : public HighsComponentData {
  HighsLp reduced_lp_;
  presolve::HighsPostsolveStack postSolveStack;
  HighsSolution recovered_solution_;
  HighsBasis recovered_basis_;
  HighsPresolveLog presolve_log_;

  void clear() {
    is_valid = false;

    postSolveStack = presolve::HighsPostsolveStack();

    reduced_lp_.clear();
    recovered_solution_.clear();
    recovered_basis_.clear();
  }

  virtual ~PresolveComponentData() = default;
};

// HighsComponentInfo is a placeholder for details we want to query from outside
// of HiGHS like execution information. Times are recorded at the end of
// Highs::run()
struct PresolveComponentInfo : public HighsComponentInfo {
  HighsInt n_rows_removed = 0;
  HighsInt n_cols_removed = 0;
  HighsInt n_nnz_removed = 0;

  double presolve_time = 0;
  double postsolve_time = 0;

  virtual ~PresolveComponentInfo() = default;
};

class PresolveComponent : public HighsComponent {
 public:
  void clear() override;

  HighsStatus init(const HighsLp& lp, HighsTimer& timer, bool mip = false);

  HighsPresolveStatus run();

  HighsLp& getReducedProblem() { return data_.reduced_lp_; }
  HighsPresolveLog& getPresolveLog() { return data_.presolve_log_; }

  void negateReducedLpColDuals();

  PresolveComponentInfo info_;
  PresolveComponentData data_;
  const HighsOptions* options_;
  HighsTimer* timer;

  HighsPresolveStatus presolve_status_ = HighsPresolveStatus::kNotPresolved;
  HighsPostsolveStatus postsolve_status_ = HighsPostsolveStatus::kNotPresolved;

  virtual ~PresolveComponent() = default;
};
#endif
