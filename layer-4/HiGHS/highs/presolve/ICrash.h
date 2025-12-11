/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file presolve/ICrash.h
 * @brief Iterative crash procedure for LP starting points
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 *
 * Finds feasible starting points by solving penalized/regularized subproblems.
 *
 * **ICrashStrategy Enum:**
 * - kPenalty: Penalty method for constraint violations
 * - kAdmm: Alternating Direction Method of Multipliers
 * - kICA: Iterative Constraint Activation
 * - kUpdatePenalty/kUpdateAdmm: Variants with parameter updates
 *
 * **ICrashIterationDetails:**
 * Per-iteration statistics for analysis:
 * - num, weight, lambda_norm_2: Iteration metadata
 * - lp_objective, quadratic_objective: Objective values
 * - residual_norm_2: Constraint violation
 *
 * **ICrashInfo:**
 * Overall crash procedure results:
 * - num_iterations, total_time: Execution stats
 * - final_lp_objective, final_quadratic_objective: Terminal objectives
 * - x_values[]: Final solution vector
 *
 * **ICrashOptions:**
 * Configuration for crash procedure:
 * - dualize: Work with dual LP
 * - Strategy selection and parameters
 *
 * @algorithm Penalty Method for Crash:
 *   Find approximately feasible point by penalizing violations:
 *   @math min c'x + μ · ||Ax - b||₂² subject to l ≤ x ≤ u
 *         As μ → ∞, solution approaches feasibility
 *   Quadratic term makes subproblem have closed-form solution.
 *   @complexity O(m·n) per iteration (matrix-vector products)
 *   @ref Nocedal, J. and Wright, S. (2006). "Numerical Optimization".
 *        Springer, Chapter 17.
 *
 * @algorithm ADMM for Crash:
 *   Alternating Direction Method of Multipliers:
 *   @math Split: min c'x + μ·||z||₂² s.t. Ax - z = b, l ≤ x ≤ u
 *         x-update: separable QP with box constraints
 *         z-update: soft thresholding z = (Ax-b+λ/ρ)/(1+μ/ρ)
 *         λ-update: λ += ρ(Ax - z - b)
 *   Converges to feasible point with bounded multipliers.
 *   @complexity O(m·n) per iteration
 *   @ref Boyd, S. et al. (2011). "Distributed optimization and statistical
 *        learning via ADMM". Foundations and Trends in ML 3(1):1-122.
 *
 * @algorithm Iterative Constraint Activation (ICA):
 *   Progressively activate constraints during crash:
 *   @math Start with bounds only, iteratively add most violated constraints
 *         Each subproblem is easier (fewer constraints)
 *   Combines well with warm-starting from previous iteration.
 *   @complexity O(k·n) where k is constraints added per iteration
 *
 * @algorithm Crossover to Basic Solution:
 *   Convert crash point to basic feasible solution:
 *   @math Given x_crash, find basis B such that x_B = B⁻¹b is feasible
 *         Uses primal/dual simplex pivots from crash point
 *   callCrossover() integrates with HiGHS simplex.
 *   @complexity O(m²) typical for crossover phase
 *
 * @see presolve/ICrashUtil.h for helper functions
 * @see presolve/ICrashX.h for extended crash variants
 */
#ifndef PRESOLVE_QUADRATIC_CRASH_H_
#define PRESOLVE_QUADRATIC_CRASH_H_

#include <vector>

#include "io/HighsIO.h"
#include "lp_data/HStruct.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsOptions.h"
#include "lp_data/HighsStatus.h"

enum class ICrashStrategy {
  kPenalty,
  kAdmm,
  kICA,
  kUpdatePenalty,
  kUpdateAdmm
};

struct ICrashIterationDetails {
  int num;
  double weight;
  double lambda_norm_2;

  double lp_objective;
  double quadratic_objective;
  double residual_norm_2;

  double time;
};

struct ICrashInfo {
  int num_iterations;

  double final_lp_objective;
  double final_quadratic_objective;
  double final_residual_norm_2;

  double starting_weight;
  double final_weight;

  std::vector<ICrashIterationDetails> details;
  std::vector<double> x_values;

  double total_time;
};

struct ICrashOptions {
  bool dualize;
  ICrashStrategy strategy;
  double starting_weight;
  HighsInt iterations;
  HighsInt approximate_minimization_iterations;
  bool exact;
  bool breakpoints;  // gets ignored if exact is set to true
  HighsLogOptions log_options;
};

struct Quadratic {
  const HighsLp lp;
  const ICrashOptions options;
  std::vector<ICrashIterationDetails> details;

  HighsSolution xk;

  double lp_objective;
  double quadratic_objective;
  std::vector<double> residual;
  double residual_norm_2;

  double mu;
  std::vector<double> lambda;

  Quadratic(HighsLp lp_, ICrashOptions options_)
      : lp(lp_),
        options(options_),
        lp_objective(0.0),
        quadratic_objective(0.0),
        residual_norm_2(0.0),
        mu(0.0) {}
};

// Functions: Call.
HighsStatus callICrash(const HighsLp& lp, const ICrashOptions& options,
                       ICrashInfo& result);

// Functions: Options.
bool checkOptions(const HighsLp& lp, const ICrashOptions options);
Quadratic parseOptions(const HighsLp& lp, const ICrashOptions options);
bool parseICrashStrategy(const std::string& strategy,
                         ICrashStrategy& icrash_strategy);
std::string ICrashtrategyToString(const ICrashStrategy strategy);

// Functions: Crash.
bool initialize(Quadratic& idata, const ICrashOptions& options);
void update(Quadratic& idata);
void updateParameters(Quadratic& idata, const ICrashOptions& options,
                      const int iteration);
bool solveSubproblem(Quadratic& idata, const ICrashOptions& options);

// Functions: Util.
double getQuadraticObjective(const Quadratic& idata);
ICrashIterationDetails fillDetails(const int num, const Quadratic& idata);
void fillICrashInfo(const int n_iterations, ICrashInfo& result);
void reportSubproblem(const ICrashOptions options, const Quadratic& idata,
                      const int iteration);
void reportOptions(const ICrashOptions& options);

bool callCrossover(const HighsLp& lp, const HighsOptions& options,
                   const std::vector<double>& x_values, HighsSolution& solution,
                   HighsBasis& basis, HighsCallback& callback);

#endif
