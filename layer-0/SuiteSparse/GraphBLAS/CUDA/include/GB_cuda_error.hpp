/**
 * @file GB_cuda_error.hpp
 * @brief CUDA error checking macro for GraphBLAS GPU operations
 * Copyright (c) 2017-2025, Timothy A. Davis. Apache-2.0 license.
 *
 * CUDA_OK macro: wraps CUDA API calls with error checking. On failure,
 * maps cudaErrorMemoryAllocation to GrB_OUT_OF_MEMORY, other errors to
 * GxB_GPU_ERROR. Prints error info via printf and GBURBLE, calls GB_FREE_ALL.
 *
 * @see GB_cuda.hpp for CUDA utilities using this macro
 */

//------------------------------------------------------------------------------
// GraphBLAS/CUDA/GB_cuda_error.hpp: call a cuda method and check its result
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2025, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

#ifndef GB_CUDA_ERROR_HPP
#define GB_CUDA_ERROR_HPP

//------------------------------------------------------------------------------
// CUDA_OK: like GB_OK but for calls to cuda* methods
//------------------------------------------------------------------------------

// FIXME: remove printfs

#define CUDA_OK(cudaMethod)                                                 \
{                                                                           \
    cudaError_t cuda_error = cudaMethod ;                                   \
    if (cuda_error != cudaSuccess)                                          \
    {                                                                       \
        printf ("cuda_error is %d\n", cuda_error) ; \
        GrB_Info info = (cuda_error == cudaErrorMemoryAllocation) ?         \
            GrB_OUT_OF_MEMORY : GxB_GPU_ERROR ;                             \
        printf ("(cuda failed: %d:%s file:%s line:%d)\n", (int) cuda_error, \
            cudaGetErrorString (cuda_error), __FILE__, __LINE__) ;          \
        GBURBLE ("(cuda failed: %d:%s file:%s line:%d)\n", (int) cuda_error, \
            cudaGetErrorString (cuda_error), __FILE__, __LINE__) ;          \
        GB_FREE_ALL ;                                                       \
        return (info) ;                                                     \
    }                                                                       \
}

#endif

