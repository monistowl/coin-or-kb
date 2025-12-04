/**
 * @file GB_cuda_apply.hpp
 * @brief CUDA JIT kernel launchers for GraphBLAS apply operations
 * SPDX-License-Identifier: Apache-2.0
 *
 * GPU apply operations: GB_cuda_apply_unop_jit (unary operator with optional
 * flipij), GB_cuda_apply_bind1st_jit (binary op with scalar bound to first),
 * GB_cuda_apply_bind2nd_jit (scalar bound to second). All take stream, grid
 * and block size parameters for kernel launch.
 *
 * @see GB_cuda.hpp for common CUDA utilities
 */

//------------------------------------------------------------------------------
// GB_cuda_apply.hpp: CPU definitions for CUDA apply operations
//------------------------------------------------------------------------------

// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

#ifndef GB_CUDA_APPLY_H
#define GB_CUDA_APPLY_H

#include "GB_cuda.hpp"

GrB_Info GB_cuda_apply_unop_jit
(
    // output:
    GB_void *Cx,
    // input:
    const GrB_Type ctype,
    const GB_Operator op,
    const bool flipij,
    const GrB_Matrix A,
    const GB_void *ythunk,
    // CUDA stream and launch parameters:
    cudaStream_t stream,
    int32_t gridsz,
    int32_t blocksz
) ;

GrB_Info GB_cuda_apply_bind1st_jit
(
    // output:
    GB_void *Cx,
    // input:
    const GrB_Type ctype,
    const GrB_BinaryOp op,
    const GrB_Matrix A,
    const GB_void *xscalar,
    // CUDA stream and launch parameters:
    cudaStream_t stream,
    int32_t gridsz,
    int32_t blocksz
) ;

GrB_Info GB_cuda_apply_bind2nd_jit
(
    // output:
    GB_void *Cx,
    // input:
    const GrB_Type ctype,
    const GrB_BinaryOp op,
    const GrB_Matrix A,
    const GB_void *xscalar,
    // CUDA stream and launch parameters:
    cudaStream_t stream,
    int32_t gridsz,
    int32_t blocksz
) ;

#endif

