/**
 * @file SuiteSparse_GPURuntime.hpp
 * @brief Version information for SuiteSparse GPU runtime library
 * Copyright (c) 2013-2016, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * Version macros for SuiteSparse_GPURuntime shared GPU infrastructure.
 * Current version 4.3.4 (June 2024). Provides common GPU utilities used
 * by GPUQREngine and other SuiteSparse GPU components.
 */

// =============================================================================
// === SuiteSparse_GPURuntime/Include/SuiteSparse_GPURuntime.hpp ===============
// =============================================================================

// SuiteSparse_GPURuntime, Copyright (c) 2013-2016, Timothy A Davis,
// Sencer Nuri Yeralan, and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------

#ifndef SUITESPARSE_GPURUNTIME_HPP
#define SUITESPARSE_GPURUNTIME_HPP

// Version information:
#define SUITESPARSE_GPURUNTIME_DATE "June 20, 2024"
#define SUITESPARSE_GPURUNTIME_MAIN_VERSION   4
#define SUITESPARSE_GPURUNTIME_SUB_VERSION    3
#define SUITESPARSE_GPURUNTIME_SUBSUB_VERSION 4

#define SUITESPARSE_GPURUNTIME_VER_CODE(main,sub) \
    SUITESPARSE_VER_CODE(main,sub)
#define SUITESPARSE_GPURUNTIME_VERSION \
    SUITESPARSE_GPURUNTIME_VER_CODE(SUITESPARSE_GPURUNTIME_MAIN_VERSION,SUITESPARSE_GPURUNTIME_SUB_VERSION)

#endif
