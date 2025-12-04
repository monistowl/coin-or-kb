/**
 * @file GB_cuda_timer.hpp
 * @brief CUDA event-based GPU timer class
 * Copyright (c) 2017-2025, Timothy A. Davis. Apache-2.0 license.
 * NVIDIA CORPORATION contributions (c) 2024-2025.
 *
 * GpuTimer class: Start() records start event, Stop() records stop event,
 * Elapsed() synchronizes and returns milliseconds between. Uses cudaEvent_t
 * for precise GPU timing. Useful for kernel performance measurement.
 */

//------------------------------------------------------------------------------
// GraphBLAS/CUDA/test/GB_cuda_timer.hpp
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2025, All Rights Reserved.
// This file: Copyright (c) 2024-2025, NVIDIA CORPORATION. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

#ifndef GB_CUDA_TIMER_HPP
#define GB_CUDA_TIMER_HPP

#include <cuda_runtime.h>
struct GpuTimer
{
    cudaEvent_t start;
    cudaEvent_t stop;

    GpuTimer()
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
    }

    ~GpuTimer()
    {
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }
         
    void Start()
    {
        cudaEventRecord(start, 0);
    }
               
    void Stop()
    {
        cudaEventRecord(stop, 0);
    }
                     
    float Elapsed()
    {
        float elapsed;
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&elapsed, start, stop);
        return elapsed;
    }
} ;

#endif

