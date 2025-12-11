/**
 * @file cupdlp_scaling.h
 * @brief Matrix scaling for PDHG numerical stability
 *
 * Implements equilibration scaling to improve PDHG convergence by
 * balancing row and column norms of the constraint matrix A.
 *
 * @algorithm Ruiz Equilibration:
 *   Iteratively scale rows and columns to unit infinity norm:
 *   @math D_r^{(k)} = diag(1/max_j |A^{(k)}_{ij}|)  (row scaling)
 *         D_c^{(k)} = diag(1/max_i |A^{(k)}_{ij}|)  (column scaling)
 *         A^{(k+1)} = D_r^{(k)} · A^{(k)} · D_c^{(k)}
 *         Converges to matrix with all row/col ∞-norms equal to 1.
 *   @complexity O(k · nnz) for k iterations (typically 10-20).
 *   @ref Ruiz (2001). "A scaling algorithm to equilibrate both rows and
 *        columns norms in matrices".
 *
 * @algorithm Pock-Chambolle Degree Scaling:
 *   Scale based on matrix sparsity pattern:
 *   @math τ_j = 1/√(Σ_i A_{ij}²), σ_i = 1/√(Σ_j A_{ij}²)
 *         Makes step sizes τσ‖A‖² < 1 automatically satisfied.
 *   @complexity O(nnz) single pass.
 *   @ref Pock & Chambolle (2011). "Diagonal preconditioning for first order
 *        primal-dual algorithms in convex optimization".
 *
 * **Scaling Methods:**
 * - Ruiz equilibration: Iterative row/column scaling to unit ∞-norms
 * - L2 scaling: Scale to unit 2-norms
 * - PC (Pock-Chambolle) scaling: Scale based on degree
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
