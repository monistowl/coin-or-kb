/**
 * @file cupdlp_restart.h
 * @brief Adaptive restart strategies for PDHG convergence acceleration
 *
 * Implements restart heuristics that periodically reset iterates to
 * accelerate PDHG convergence from O(1/k) to O(1/k²).
 *
 * @algorithm Adaptive Restart for First-Order Methods:
 *   Accelerate convergence by detecting when to reset momentum:
 *   @math Merit function M(x,y) = w²·(‖r_p‖² + ‖r_d‖² + gap²)
 *         where r_p = Ax - b (primal residual), r_d = c - A'y (dual residual)
 *         Restart when M increases or improvement rate drops below threshold.
 *   @complexity O(n+m) to evaluate merit function.
 *   @ref O'Donoghue & Candes (2015). "Adaptive restart for accelerated
 *        gradient schemes".
 *
 * @algorithm Restart Decision Logic:
 *   Three options based on current vs average iterate quality:
 *   @math If M(x^curr, y^curr) < M(x^avg, y^avg): restart to current
 *         Else if M(x^avg, y^avg) < β·M_prev: restart to average
 *         Else: no restart (continue averaging)
 *         Typically β ≈ 0.8 for sufficient improvement.
 *
 * **Restart Strategies:**
 * - PDHG_NO_RESTART: Continue without restart
 * - PDHG_RESTART_TO_CURRENT: Reset to current iterate
 * - PDHG_RESTART_TO_AVERAGE: Reset to running average
 *
 * @see cupdlp_solver.h for restart integration in main loop
 * @see cupdlp_proj.h for restart execution
 */
//
// Created by chuwen on 23-11-28.
//

#ifndef CUPDLP_CUPDLP_RESTART_H
#define CUPDLP_CUPDLP_RESTART_H

#include "pdlp/cupdlp/cupdlp_defs.h"
#include "pdlp/cupdlp/cupdlp_linalg.h"
#include "pdlp/cupdlp/cupdlp_proj.h"
// #include "cupdlp_scaling.h"
#include "pdlp/cupdlp/cupdlp_step.h"
#include "pdlp/cupdlp/cupdlp_utils.h"
#include "pdlp/cupdlp/glbopts.h"

typedef enum {
  PDHG_NO_RESTART = 0,
  PDHG_RESTART_TO_CURRENT,
  PDHG_RESTART_TO_AVERAGE
} PDHG_restart_choice;

cupdlp_bool PDHG_Check_Restart_Merit_Function(CUPDLPwork *work);

PDHG_restart_choice PDHG_Check_Restart_GPU(CUPDLPwork *work);

cupdlp_float PDHG_Restart_Score_GPU(cupdlp_float weightSquared,
                                    cupdlp_float dPrimalFeas,
                                    cupdlp_float dDualFeas,
                                    cupdlp_float dDualityGap);

#endif  // CUPDLP_CUPDLP_RESTART_H
