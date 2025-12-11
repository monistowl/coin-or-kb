/**
 * @file cupdlp_step.h
 * @brief Step size selection and PDHG iterate updates
 *
 * Core PDHG iteration logic including step size computation and updates.
 *
 * @algorithm Primal-Dual Hybrid Gradient (PDHG):
 *   First-order method for LP: min{c'x : Ax=b, l≤x≤u}:
 *   @math Each iteration performs:
 *         x̄ = x - τ·(c - A'y)           (primal gradient)
 *         x⁺ = proj_{[l,u]}(x̄)          (projection onto bounds)
 *         y⁺ = y + σ·(b - A·(2x⁺ - x))  (dual gradient with extrapolation)
 *   @complexity O(nnz(A)) per iteration. Converges O(1/k) ergodically.
 *   @ref Chambolle & Pock (2011). "A first-order primal-dual algorithm
 *        for convex problems with applications to imaging".
 *
 * @algorithm Power Method for Spectral Norm:
 *   Compute ‖A‖₂ to set step sizes τ, σ satisfying τσ‖A‖² < 1:
 *   @math Iterate: v ← A'Av / ‖A'Av‖, λ ← v'A'Av
 *         Converges to largest eigenvalue of A'A.
 *   @complexity O(k·nnz(A)) for k iterations.
 *
 * @algorithm Malitsky-Pock Adaptive Steps:
 *   Update step sizes based on actual primal-dual coupling:
 *   @math θ = τ_k/τ_{k-1}, τ_{k+1} = τ_k·√(1 + θ),
 *         σ_{k+1} = τ_{k+1}/(τ_k·σ_k·‖A‖²)
 *   @ref Malitsky & Pock (2018). "A first-order primal-dual algorithm
 *        with linesearch".
 *
 * **Step Size Methods:**
 * - Constant: τ = σ = 1/‖A‖, computed via power method
 * - Malitsky-Pock: Adaptive based on primal-dual interaction
 * - Adaptive linesearch: Backtracking with growth/reduction
 *
 * @see cupdlp_solver.h for main iteration loop
 * @see cupdlp_linalg.h for matrix-vector products
 */
//
// Created by chuwen on 23-11-28.
//

#ifndef CUPDLP_CUPDLP_STEP_H
#define CUPDLP_CUPDLP_STEP_H

#include "pdlp/cupdlp/cupdlp_defs.h"
// #include "cupdlp_scaling.h"
#include "pdlp/cupdlp/glbopts.h"

cupdlp_retcode PDHG_Power_Method(CUPDLPwork *work, double *lambda);

void PDHG_Compute_Step_Size_Ratio(CUPDLPwork *pdhg);

void PDHG_Update_Iterate_Constant_Step_Size(CUPDLPwork *pdhg);

void PDHG_Update_Iterate_Malitsky_Pock(CUPDLPwork *pdhg);

cupdlp_retcode PDHG_Update_Iterate_Adaptive_Step_Size(CUPDLPwork *pdhg);

cupdlp_retcode PDHG_Init_Step_Sizes(CUPDLPwork *pdhg);

void PDHG_Compute_Average_Iterate(CUPDLPwork *work);

void PDHG_Update_Average(CUPDLPwork *work);

cupdlp_retcode PDHG_Update_Iterate(CUPDLPwork *pdhg);

void PDHG_primalGradientStep(CUPDLPwork *work, CUPDLPvec *xUpdate,
                             const CUPDLPvec *x, const CUPDLPvec *ATy,
                             cupdlp_float dPrimalStepSize);
void PDHG_dualGradientStep(CUPDLPwork *work, CUPDLPvec *yUpdate,
                           const CUPDLPvec *y, const CUPDLPvec *Ax,
                           const CUPDLPvec *AxUpdate, cupdlp_float dDualStepSize);

#endif  // CUPDLP_CUPDLP_STEP_H
