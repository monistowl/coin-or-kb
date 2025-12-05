/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsMipSolver.h
 * @brief Branch-and-cut MIP solver
 *
 * @algorithm Branch-and-Cut for Mixed-Integer Programming:
 * Combines branch-and-bound with cutting planes for MIP.
 *
 * OVERALL FLOW:
 *   1. PRESOLVE: Reduce problem size and tighten formulation
 *   2. ROOT NODE: Solve LP relaxation, add cuts, find initial solutions
 *   3. BRANCH-AND-BOUND: Explore tree until proven optimal
 *   4. POSTSOLVE: Restore original solution space
 *
 * ROOT NODE PROCESSING:
 *   while (progress):
 *     Solve LP relaxation
 *     Add violated cuts (Gomory, MIR, clique, cover)
 *     Run primal heuristics (diving, RINS, RENS)
 *     Update bounds
 *
 * BRANCH-AND-BOUND TREE:
 *   Initialize: dual_bound = root_LP_obj, primal_bound = +inf
 *   while (open_nodes and gap > tolerance):
 *     Select node (best-first, depth-first, hybrid)
 *     Solve LP relaxation
 *     if (LP_infeasible or LP_obj >= primal_bound):
 *       Prune node
 *     elif (solution is integer):
 *       Update primal_bound if better
 *       Prune node
 *     else:
 *       Add cuts if violated
 *       Branch on fractional integer variable
 *
 * @math Optimality gap: gap = (primal_bound - dual_bound) / |primal_bound|
 *   Termination when gap <= mip_rel_gap tolerance (default 0.01%)
 *
 * @complexity
 * - Worst case: exponential in number of integer variables
 * - Practice: often polynomial due to pruning and cuts
 * - Root processing: O(cuts * LP_iterations)
 *
 * @ref Achterberg, Bixby, Gu, Rothberg & Weninger (2020).
 *   "Presolve Reductions in Mixed Integer Programming". INFORMS J. Computing.
 *
 * **HighsMipSolver Class:**
 * Main MIP solver using branch-and-cut with LP relaxations.
 *
 * **Key State:**
 * - model_/orig_model_: Problem LP with integrality constraints
 * - solution_: Best incumbent solution found
 * - dual_bound_/primal_bound_: Bounds on optimal value
 * - gap_: Optimality gap (primal_bound - dual_bound) / primal_bound
 * - node_count_: Number of B&B nodes explored
 *
 * **Sub-MIP Support:**
 * - submip/submip_level: For recursive sub-MIP solves (e.g., in heuristics)
 * - rootbasis: Starting basis from parent MIP
 * - pscostinit: Warm-start pseudocosts
 * - clqtableinit/implicinit: Warm-start conflict graph structures
 *
 * **HighsTerminator:**
 * Parallel termination coordination for concurrent MIP instances.
 *
 * **Main Entry:**
 * - run(): Execute MIP solve (presolve, root LP, branch-and-cut)
 * - runMipPresolve(): Standalone presolve for warm-start scenarios
 *
 * @see mip/HighsMipSolverData.h for internal B&B data
 * @see mip/HighsCutPool.h for cutting plane management
 * @see mip/HighsCliqueTable.h for clique detection
 */
#ifndef MIP_HIGHS_MIP_SOLVER_H_
#define MIP_HIGHS_MIP_SOLVER_H_

#include "Highs.h"
#include "lp_data/HighsCallback.h"
#include "lp_data/HighsOptions.h"
#include "mip/HighsMipAnalysis.h"

struct HighsMipSolverData;
class HighsCutPool;
struct HighsPseudocostInitialization;
class HighsCliqueTable;
class HighsImplications;

struct HighsTerminator {
  HighsInt num_instance;
  HighsInt my_instance;
  HighsModelStatus* record;
  void clear();
  void initialise(HighsInt num_instance_, HighsInt my_instance_,
                  HighsModelStatus* record_);
  HighsInt concurrency() const;
  void terminate();
  bool terminated() const;
  HighsModelStatus terminationStatus() const;
  void report(const HighsLogOptions log_options) const;
};

class HighsMipSolver {
 public:
  HighsCallback* callback_;
  const HighsOptions* options_mip_;
  const HighsLp* model_;
  const HighsLp* orig_model_;
  HighsModelStatus modelstatus_;
  std::vector<double> solution_;
  double solution_objective_;
  double bound_violation_;
  double integrality_violation_;
  double row_violation_;
  // The following are only to return data to HiGHS, and are set in
  // HighsMipSolver::cleanupSolve
  double dual_bound_;
  double primal_bound_;
  double gap_;
  int64_t node_count_;
  int64_t total_lp_iterations_;
  double primal_dual_integral_;

  FILE* improving_solution_file_;
  std::vector<HighsObjectiveSolution> saved_objective_and_solution_;

  bool submip;
  HighsInt submip_level;
  HighsInt max_submip_level;
  const HighsBasis* rootbasis;
  const HighsPseudocostInitialization* pscostinit;
  const HighsCliqueTable* clqtableinit;
  const HighsImplications* implicinit;

  std::unique_ptr<HighsMipSolverData> mipdata_;

  HighsMipAnalysis analysis_;

  HighsModelStatus termination_status_;
  HighsTerminator terminator_;

  void run();

  HighsInt numCol() const { return model_->num_col_; }

  HighsInt numRow() const { return model_->num_row_; }

  HighsInt numNonzero() const { return model_->a_matrix_.numNz(); }

  const double* colCost() const { return model_->col_cost_.data(); }

  double colCost(HighsInt col) const { return model_->col_cost_[col]; }

  const double* rowLower() const { return model_->row_lower_.data(); }

  double rowLower(HighsInt col) const { return model_->row_lower_[col]; }

  const double* rowUpper() const { return model_->row_upper_.data(); }

  double rowUpper(HighsInt col) const { return model_->row_upper_[col]; }

  const HighsVarType* variableType() const {
    return model_->integrality_.data();
  }

  HighsVarType variableType(HighsInt col) const {
    return model_->integrality_[col];
  }

  HighsMipSolver(HighsCallback& callback, const HighsOptions& options,
                 const HighsLp& lp, const HighsSolution& solution,
                 bool submip = false, HighsInt submip_level = 0);

  ~HighsMipSolver();

  void setModel(const HighsLp& model) {
    model_ = &model;
    solution_objective_ = kHighsInf;
  }

  mutable HighsTimer timer_;
  mutable HighsSubSolverCallTime sub_solver_call_time_;

  void cleanupSolve();

  void runMipPresolve(const HighsInt presolve_reduction_limit);
  const HighsLp& getPresolvedModel() const;
  HighsPresolveStatus getPresolveStatus() const;
  presolve::HighsPostsolveStack getPostsolveStack() const;

  void callbackGetCutPool() const;
  bool solutionFeasible(const HighsLp* lp, const std::vector<double>& col_value,
                        const std::vector<double>* pass_row_value,
                        double& bound_violation, double& row_violation,
                        double& integrality_violation, HighsCDouble& obj) const;

  std::vector<HighsModelStatus> initialiseTerminatorRecord(
      HighsInt num_instance) const;
  void initialiseTerminator(HighsInt num_instance_ = 0,
                            HighsInt my_instance_ = kNoThreadInstance,
                            HighsModelStatus* record_ = nullptr);
  void initialiseTerminator(const HighsMipSolver& mip_solver);
  bool terminate() const {
    return this->termination_status_ != HighsModelStatus::kNotset;
  }
  HighsModelStatus terminationStatus() const {
    return this->termination_status_;
  }
};

std::array<char, 128> getGapString(const double gap_,
                                   const double primal_bound_,
                                   const HighsOptions* options_mip_);
#endif
