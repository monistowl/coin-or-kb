/**
 * @file GB_cuda_ewise.hpp
 * @brief CUDA JIT kernel launchers for GraphBLAS element-wise operations
 * SPDX-License-Identifier: Apache-2.0
 *
 * GPU element-wise scaling: GB_cuda_rowscale_jit (C = D.*B row scaling),
 * GB_cuda_colscale_jit (C = A.*D column scaling). Both support flipxy for
 * operand order and take stream/grid/block parameters.
 *
 * @see GB_cuda.hpp for common CUDA utilities
 */

//------------------------------------------------------------------------------
// GB_cuda_ewise.hpp: CPU definitions for CUDA ewise operations
//------------------------------------------------------------------------------

// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

#ifndef GB_CUDA_EWISE_H
#define GB_CUDA_EWISE_H

#include "GB_cuda.hpp"

GrB_Info GB_cuda_rowscale_jit
(
    // output:
    GrB_Matrix C,
    // input:
    GrB_Matrix D,
    GrB_Matrix B,
    GrB_BinaryOp binaryop,
    bool flipxy,
    // CUDA stream and launch parameters:
    cudaStream_t stream,
    int32_t gridsz,
    int32_t blocksz
) ;

GrB_Info GB_cuda_colscale_jit
(
    // output:
    GrB_Matrix C,
    // input:
    GrB_Matrix A,
    GrB_Matrix D,
    GrB_BinaryOp binaryop,
    bool flipxy,
    // CUDA stream and launch parameters:
    cudaStream_t stream,
    int32_t gridsz,
    int32_t blocksz
) ;

#endif

