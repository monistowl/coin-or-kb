/**
 * @file GPUQREngine_SuiteSparse.hpp
 * @brief Public SuiteSparse API for GPU QR factorization
 * Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * Main entry point for SPQR GPU support. QREngineResultCode enum: SUCCESS,
 * OUTOFMEMORY, GPUERROR. GPUQREngine template functions: dense (fronts only)
 * and sparse (with Parent/Childp/Child tree). GPUQREngine_FindStaircase
 * computes staircase for block zero exploitation.
 *
 * @see GPUQREngine_Internal.hpp for implementation details
 */

// =============================================================================
// GPUQREngine/Include/GPUQREngine_SuiteSparse.hpp
// =============================================================================

// GPUQREngine, Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
// and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------
//
// This is the main include file for use in SuiteSparse itself
//
// =============================================================================

#ifndef GPUQRENGINE_SUITESPARSE_HPP
#define GPUQRENGINE_SUITESPARSE_HPP

#include "SuiteSparseGPU_internal.hpp"
#include "GPUQREngine_Front.hpp"
#include "GPUQREngine_Stats.hpp"

enum QREngineResultCode
{
    QRENGINE_SUCCESS,           // GPU QR was successful
    QRENGINE_OUTOFMEMORY,       // GPU QR ran out of memory
    QRENGINE_GPUERROR           // failed to communicated with the GPU
};

// Use C++ Polymorphism to provide many different function signatures and
// call patterns.
template <typename Int = int64_t>
QREngineResultCode GPUQREngine
(
    size_t gpuMemorySize,
    Front <Int> *userFronts,
    Int numFronts,
    QREngineStats <Int> *stats = NULL
);

template <typename Int = int64_t>
QREngineResultCode GPUQREngine
(
    size_t gpuMemorySize,
    Front <Int> *userFronts,
    Int numFronts,
    Int *Parent,
    Int *Childp,
    Int *Child,
    QREngineStats <Int> *stats = NULL
);

template <typename Int = int64_t>
Int *GPUQREngine_FindStaircase
(
    Front <Int> *front                // The front whose staircase we are computing
);

// Version information:
#include "GPUQREngine.hpp"

#endif
