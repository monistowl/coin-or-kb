/**
 * @file GPUQREngine_GraphVizHelper.hpp
 * @brief Debug visualization for bucket list state
 * Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * GPUQREngine_RenderBuckets function generates GraphViz output for
 * BucketList visualization. Only compiled when GPUQRENGINE_RENDER defined.
 * Used for debugging factorization scheduling and tile progression.
 *
 * @see GPUQREngine_BucketList.hpp for rendered data structure
 */

// =============================================================================
// === GPUQREngine/Include/GPUQREngine_GraphVisHelper.hpp ======================
// =============================================================================

// GPUQREngine, Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
// and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------
//
// GraphVisHelper wraps logic to render the contents of a bucket list.
//   This is used primarilly in debugging efforts.
//
// =============================================================================

#ifndef GPUQRENGINE_GRAPHVIZHELPER_HPP
#define GPUQRENGINE_GRAPHVIZHELPER_HPP

#ifdef GPUQRENGINE_RENDER
#include "GPUQREngine_BucketList.hpp"

void GPUQREngine_RenderBuckets(BucketList *buckets);

#endif
#endif
