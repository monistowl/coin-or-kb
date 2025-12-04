/**
 * @file GPUQREngine_SEntry.hpp
 * @brief Sparse entry tuple for GPU front assembly
 * Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * SEntry struct: (findex, value) tuple for placing sparse matrix values
 * into dense frontal matrices. findex is linear index into front, value
 * is numeric entry. Used in S assembly phase (ASSEMBLE_S state) to transfer
 * input matrix to GPU fronts via cpuS/gpuS arrays in SparseMeta.
 *
 * @see GPUQREngine_SparseMeta.hpp uses SEntry arrays
 */

// =============================================================================
// === GPUQREngine/Include/GPUQREngine_Sentry.hpp ==============================
// =============================================================================

// GPUQREngine, Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
// and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------
//
// The SEntry struct is a tuple which is used to place the numeric values from
// the input problem into the dense representation of the fronts on the GPU.
//
// =============================================================================

#ifndef GPUQRENGINE_SENTRY_HPP
#define GPUQRENGINE_SENTRY_HPP

struct SEntry
{
    long findex;        // Index into the front where the value belongs
    double value;       // The numeric value to be placed

    SEntry()
    {
        findex = 0;
        value = 0.0;
    }
};

#endif
