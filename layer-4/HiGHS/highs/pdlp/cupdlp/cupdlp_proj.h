/**
 * @file cupdlp_proj.h
 * @brief Projection operations for PDHG algorithm
 *
 * Implements projection onto variable bounds and restart operations.
 *
 * @algorithm Box Constraint Projection:
 *   Project x onto bounds [l, u] in O(n):
 *   @math proj_{[l,u]}(x)_i = max(l_i, min(x_i, u_i))
 *         Closed-form projection onto convex box constraints.
 *   @complexity O(n) elementwise operations, GPU-parallelizable.
 *
 * @algorithm Restart Strategy for PDHG:
 *   Reset iterate to improve practical convergence:
 *   @math On restart: (x^new, y^new) ← (x̄^avg, ȳ^avg) or (x^curr, y^curr)
 *         Triggered when progress stagnates or residuals increase.
 *         Ergodic average x̄ = Σ w_k x_k / Σ w_k has O(1/k) convergence.
 *   @ref Applegate et al. (2021). "Practical Large-Scale Linear Programming
 *        using Primal-Dual Hybrid Gradient" (Google OR-Tools PDLP).
 *
 * **Functions:**
 * - PDHG_Project_Bounds(): Projects x onto [l, u] box constraints
 * - PDHG_Restart_Iterate(): Resets iterate to current or average point
 *
 * @see cupdlp_step.h for PDHG update using projections
 * @see cupdlp_restart.h for restart decision logic
 */
//
// Created by chuwen on 23-11-28.
//

#ifndef CUPDLP_CUPDLP_PROJ_H
#define CUPDLP_CUPDLP_PROJ_H

#include "pdlp/cupdlp/cupdlp_defs.h"
#include "pdlp/cupdlp/glbopts.h"

void PDHG_Project_Bounds(CUPDLPwork *work, double *r);

// void PDHG_Project_Row_Duals(CUPDLPwork *work, double *r);

void PDHG_Restart_Iterate(CUPDLPwork *pdhg);

void PDHG_Restart_Iterate_GPU(CUPDLPwork *pdhg);

#endif  // CUPDLP_CUPDLP_PROJ_H
