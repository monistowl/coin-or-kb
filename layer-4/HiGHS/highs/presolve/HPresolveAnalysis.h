/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file presolve/HPresolveAnalysis.h
 * @brief Presolve statistics and rule control
 *
 * Tracks presolve reductions and controls which rules are enabled.
 *
 * **HPresolveAnalysis Class:**
 * - model, options: References to problem being presolved
 * - allow_rule_[]: Per-rule enable flags (from options->presolve_rule_off)
 * - numDeletedRows, numDeletedCols: Reduction counts
 * - presolve_log_: Detailed reduction history
 *
 * **Rule Control:**
 * - setup(): Initialize rule flags from options
 * - allow_rule_[]: Boolean array indexed by PresolveRuleType
 * - Disabled rules are skipped during presolve passes
 *
 * **Logging:**
 * - allow_logging_/logging_on_: Control verbosity
 * - startPresolveRuleLog()/stopPresolveRuleLog(): Bracket rule execution
 * - analysePresolveRuleLog(): Summarize effectiveness of rules
 * - presolveReductionTypeToString(): Convert rule type to name
 *
 * **Statistics:**
 * - original_num_col_/row_: Problem size before presolve
 * - num_deleted_rows0_/cols0_: Running deletion counts
 *
 * @see presolve/HPresolve.h for presolve engine using this
 * @see lp_data/HConst.h for PresolveRuleType enum
 */
#ifndef PRESOLVE_HIGHS_PRESOLVE_ANALYSIS_H_
#define PRESOLVE_HIGHS_PRESOLVE_ANALYSIS_H_

class HPresolveAnalysis {
  const HighsLp* model;
  const HighsOptions* options;
  const bool* allow_rule;
  const HighsInt* numDeletedRows;
  const HighsInt* numDeletedCols;

  // store original problem sizes for reference
  HighsInt original_num_col_;
  HighsInt original_num_row_;

 public:
  std::vector<bool> allow_rule_;

  bool allow_logging_;
  bool logging_on_;

  int log_rule_type_;
  HighsInt num_deleted_rows0_;
  HighsInt num_deleted_cols0_;
  HighsPresolveLog presolve_log_;

  // for LP presolve
  //
  // Transform options->presolve_rule_off into logical settings in
  // allow_rule_[*], commenting on the rules switched off
  void setup(const HighsLp* model_, const HighsOptions* options_,
             const HighsInt& numDeletedRows_, const HighsInt& numDeletedCols_);
  void resetNumDeleted();

  std::string presolveReductionTypeToString(const HighsInt reduction_type);
  void startPresolveRuleLog(const HighsInt rule_type);
  void stopPresolveRuleLog(const HighsInt rule_type);
  bool analysePresolveRuleLog(const bool report = false);
  friend class HPresolve;
};

#endif
