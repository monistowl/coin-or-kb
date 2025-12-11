/**
 * @file cupdlp_scaling.h
 * @brief Matrix scaling for PDHG numerical stability
 *
 * Implements equilibration scaling to improve PDHG convergence by
 * balancing row and column norms of the constraint matrix A.
 *
 * **Scaling Methods:**
 * - Ruiz equilibration: Iterative row/column scaling to unit ∞-norms
 * - L2 scaling: Scale to unit 2-norms
 * - PC (Pock-Chambolle) scaling: Scale based on degree
 *
 * Scaling affects step size selection: τσ‖A‖² < 1 becomes easier
 * to satisfy when ‖A‖ is reduced through scaling.
 *
 * @see cupdlp_step.h for step size computation using scaled matrix
 * @see cupdlp_defs.h for CUPDLPscaling structure
 */
//
// Created by LJS on 23-11-30.
//

#ifndef CUPDLP_SCALING_H
#define CUPDLP_SCALING_H

#include "cupdlp_defs.h"
#include "glbopts.h"
#ifdef __cplusplus
extern "C" {
#endif

cupdlp_retcode PDHG_Scale_Data(cupdlp_int log_level, CUPDLPcsc* csc,
                               cupdlp_int ifScaling, CUPDLPscaling* scaling,
                               cupdlp_float* cost, cupdlp_float* lower,
                               cupdlp_float* upper, cupdlp_float* rhs);

cupdlp_retcode Init_Scaling(cupdlp_int log_level, CUPDLPscaling* scaling,
                            cupdlp_int ncols, cupdlp_int nrows,
                            cupdlp_float* cost, cupdlp_float* rhs);

#ifdef __cplusplus
}
#endif
#endif  // CUPDLP_CUPDLP_SCALING_H
