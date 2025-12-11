/**
 * @file cupdlp_proj.h
 * @brief Projection operations for PDHG algorithm
 *
 * Implements projection onto variable bounds and restart operations:
 * - PDHG_Project_Bounds(): Projects x onto [l, u] box constraints
 * - PDHG_Restart_Iterate(): Resets iterate to current or average point
 *
 * In PDHG, primal projection is: x^{k+1} = proj_{[l,u]}(x̄)
 * where x̄ is the gradient step result.
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
