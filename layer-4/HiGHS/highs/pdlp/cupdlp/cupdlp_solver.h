/**
 * @file pdlp/cupdlp/cupdlp_solver.h
 * @brief PDHG (Primal-Dual Hybrid Gradient) Solver for Linear Programming
 *
 * Implements the PDLP (Primal-Dual Linear Programming) algorithm using
 * first-order optimization methods instead of traditional simplex or IPM.
 *
 * @algorithm PDHG (Primal-Dual Hybrid Gradient) for LP:
 * A first-order method for solving the saddle-point formulation of LP.
 *
 * LP SADDLE-POINT FORMULATION:
 * min_x max_y  c'x + y'(b - Ax)  s.t. l ≤ x ≤ u
 *
 * Equivalent to: min c'x  s.t. Ax = b, l ≤ x ≤ u
 * The Lagrangian couples primal (x) and dual (y) variables.
 *
 * PDHG ITERATION:
 * Given step sizes τ (primal) and σ (dual):
 *
 *   x̄ = x^k - τ·(c - A'y^k)           // primal gradient step
 *   x^{k+1} = proj_{[l,u]}(x̄)         // project onto bounds
 *
 *   ŷ = y^k + σ·(b - A·(2x^{k+1} - x^k))  // dual gradient with extrapolation
 *   y^{k+1} = ŷ                        // no projection for free dual
 *
 * KEY FEATURE: Extrapolation (2x^{k+1} - x^k) accelerates convergence
 * compared to standard gradient descent.
 *
 * STEP SIZE SELECTION:
 * For convergence: τ·σ·‖A‖² < 1
 * Typically: τ = σ = 1/(‖A‖_2) or adaptive schemes
 *
 * RESTART STRATEGIES:
 * Periodically restart to accelerate when making progress:
 * - Fixed frequency restart
 * - Adaptive restart on normalized duality gap improvement
 * - Restart on primal-dual distance decrease
 *
 * TERMINATION CRITERIA:
 * Check primal/dual feasibility and duality gap:
 * - Primal feasibility: ‖Ax - b‖ / (1 + ‖b‖) ≤ ε
 * - Dual feasibility: ‖c - A'y - zl + zu‖ / (1 + ‖c‖) ≤ ε
 * - Gap: |c'x - b'y| / (1 + |c'x| + |b'y|) ≤ ε
 *
 * @math Convergence rate:
 * - O(1/k) ergodic convergence for duality gap
 * - O(1/k²) with acceleration (momentum/restart)
 * - Not polynomial in problem dimension (unlike IPM)
 * - But: iteration cost is O(nnz) vs O(n³) for IPM
 *
 * Comparison with other LP methods:
 * - Simplex: exact but exponential worst-case
 * - IPM: polynomial O(√n·log(1/ε)) but O(n³) per iteration
 * - PDHG: cheap O(nnz) iterations, good for huge sparse LPs
 *
 * @complexity
 * - Per iteration: O(nnz) for matrix-vector products
 * - Iterations to ε-accuracy: O(‖A‖/ε) without restart
 * - Total for moderate accuracy: competitive with IPM on large sparse problems
 * - Memory: O(n + m) vs O(fill) for factorization methods
 *
 * @ref Chambolle & Pock (2011). "A First-Order Primal-Dual Algorithm for
 *   Convex Problems with Applications to Imaging". J. Math. Imaging Vis.
 * @ref Applegate et al. (2021). "Practical Large-Scale Linear Programming
 *   using Primal-Dual Hybrid Gradient". NeurIPS.
 *
 * @see cupdlp_step.h for step computation details
 * @see cupdlp_restart.h for restart strategies
 */
//
// Created by chuwen on 23-11-27.
//

#ifndef CUPDLP_CUPDLP_SOLVER_H
#define CUPDLP_CUPDLP_SOLVER_H

#include "pdlp/cupdlp/cupdlp_defs.h"
#include "pdlp/cupdlp/glbopts.h"

#ifdef __cplusplus
extern "C" {
#endif
#define CUPDLP_CHECK_TIMEOUT(pdhg)                               \
  {                                                              \
    PDHG_Compute_SolvingTime(pdhg);                              \
    if (pdhg->timers->dSolvingTime > pdhg->settings->dTimeLim) { \
      retcode = RETCODE_FAILED;                                  \
      goto exit_cleanup;                                         \
    }                                                            \
  }

void PDHG_Compute_Primal_Feasibility(CUPDLPwork *work, cupdlp_float *primalResidual,
                                     const cupdlp_float *ax, const cupdlp_float *x,
                                     cupdlp_float *dPrimalFeasibility,
                                     cupdlp_float *dPrimalObj);

void PDHG_Compute_Dual_Feasibility(CUPDLPwork *work, cupdlp_float *dualResidual,
                                   const cupdlp_float *aty, const cupdlp_float *x,
                                   const cupdlp_float *y, cupdlp_float *dDualFeasibility,
                                   cupdlp_float *dDualObj, cupdlp_float *dComplementarity,
                                   cupdlp_float *dSlackPos, cupdlp_float *dSlackNeg);

void PDHG_Compute_Residuals(CUPDLPwork *work);

void PDHG_Compute_Primal_Infeasibility(CUPDLPwork *work, const cupdlp_float *y,
                                       const cupdlp_float *dSlackPos,
                                       const cupdlp_float *dSlackNeg,
                                       const cupdlp_float *aty,
                                       const cupdlp_float dualObj,
                                       cupdlp_float *dPrimalInfeasObj,
                                       cupdlp_float *dPrimalInfeasRes);

void PDHG_Compute_Dual_Infeasibility(CUPDLPwork *work, const cupdlp_float *x,
                                     const cupdlp_float *ax,
                                     const cupdlp_float primalObj,
                                     cupdlp_float *dDualInfeasObj,
                                     cupdlp_float *dDualInfeasRes);

void PDHG_Compute_Infeas_Residuals(CUPDLPwork *work);

void PDHG_Init_Variables(const cupdlp_int* has_variables, CUPDLPwork *work);

void PDHG_Check_Data(CUPDLPwork *work);

cupdlp_bool PDHG_Check_Termination(CUPDLPwork *pdhg, int bool_print);

cupdlp_bool PDHG_Check_Termination_Average(CUPDLPwork *pdhg, int bool_print);

termination_code PDHG_Check_Infeasibility(CUPDLPwork *pdhg, int bool_print);

termination_code PDHG_Check_Primal_Infeasibility(CUPDLPwork *pdhg,
                                                 cupdlp_float dPrimalInfeasObj,
                                                 cupdlp_float dPrimalInfeasRes);
termination_code PDHG_Check_Dual_Infeasibility(CUPDLPwork *pdhg,
                                               cupdlp_float dDualInfeasObj,
                                               cupdlp_float dDualInfeasRes);

void PDHG_Print_Header(CUPDLPwork *pdhg);

void PDHG_Print_Iter(CUPDLPwork *pdhg);

void PDHG_Print_Iter_Average(CUPDLPwork *pdhg);

void PDHG_Compute_SolvingTime(CUPDLPwork *pdhg);

cupdlp_retcode PDHG_Solve(const cupdlp_int* has_variables, CUPDLPwork *pdhg);

cupdlp_retcode PDHG_PostSolve(CUPDLPwork *pdhg, cupdlp_int nCols_origin,
                              cupdlp_int *constraint_new_idx,
                              cupdlp_int *constraint_type,
                              cupdlp_float *col_value, cupdlp_float *col_dual,
                              cupdlp_float *row_value, cupdlp_float *row_dual,
                              cupdlp_int *value_valid, cupdlp_int *dual_valid);

cupdlp_retcode PDHG_PreSolve(CUPDLPwork *pdhg, cupdlp_int nCols_origin,
			     cupdlp_int *constraint_new_idx,
			     cupdlp_int *constraint_type,
			     cupdlp_float *col_value, cupdlp_float *col_dual,
			     cupdlp_float *row_value, cupdlp_float *row_dual,
			     cupdlp_int *value_valid, cupdlp_int *dual_valid);

cupdlp_retcode LP_SolvePDHG(
    CUPDLPwork *pdhg, cupdlp_bool *ifChangeIntParam, cupdlp_int *intParam,
    cupdlp_bool *ifChangeFloatParam, cupdlp_float *floatParam, char *fp,
    cupdlp_int nCols_origin, cupdlp_float *col_value, cupdlp_float *col_dual,
    cupdlp_float *row_value, cupdlp_float *row_dual, cupdlp_int *value_valid,
    cupdlp_int *dual_valid, cupdlp_bool ifSaveSol, char *fp_sol,
    cupdlp_int *constraint_new_idx, cupdlp_int *constraint_type,
    cupdlp_int *model_status, cupdlp_int* num_iter);

#ifdef __cplusplus
}
#endif
#endif  // CUPDLP_CUPDLP_SOLVER_H
