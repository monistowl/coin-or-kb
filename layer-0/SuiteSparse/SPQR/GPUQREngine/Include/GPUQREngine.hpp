/**
 * @file GPUQREngine.hpp
 * @brief Version information for GPUQREngine CUDA library
 * Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * Version macros for GPUQREngine GPU-accelerated QR factorization.
 * Current version 4.3.4 (June 2024). Part of SuiteSparse SPQR.
 */

// =============================================================================
// === GPUQREngine/Include/GPUQREngine.hpp =====================================
// =============================================================================

// GPUQREngine, Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
// and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

// =============================================================================

#ifndef GPUQRENGINE_HPP
#define GPUQRENGINE_HPP

// Version information:
#define GPUQRENGINE_DATE "June 20, 2024"
#define GPUQRENGINE_MAIN_VERSION   4
#define GPUQRENGINE_SUB_VERSION    3
#define GPUQRENGINE_SUBSUB_VERSION 4

#define GPUQRENGINE_VER_CODE(main,sub) SUITESPARSE_VER_CODE(main,sub)
#define GPUQRENGINE_VERSION \
    GPUQRENGINE_VER_CODE(GPUQRENGINE_MAIN_VERSION,GPUQRENGINE_SUB_VERSION)

#endif
