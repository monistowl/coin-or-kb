/**
 * @file SuiteSparseGPU_macros.hpp
 * @brief Common macros for SuiteSparse GPU components
 * Copyright (c) 2013-2016, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * IMPLIES(p,q) logical implication macro: true unless p is true and q is false.
 * Includes debug level macros and workspace accessor macros. Used throughout
 * GPURuntime and GPUQREngine.
 *
 * @see SuiteSparseGPU_debug.hpp for debug level definitions
 */

// =============================================================================
// === SuiteSparse_GPURuntime/Include/SuiteSparseGPU_macros.hpp ================
// =============================================================================

// SuiteSparse_GPURuntime, Copyright (c) 2013-2016, Timothy A Davis,
// Sencer Nuri Yeralan, and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------

#ifndef SUITESPARSE_GPURUNTIME_MACROS_HPP
#define SUITESPARSE_GPURUNTIME_MACROS_HPP

#ifndef IMPLIES
#define IMPLIES(p,q)    (!(p) || ((p) && (q)))
#endif

#include "SuiteSparseGPU_debug.hpp"
#include "SuiteSparseGPU_workspace_macros.hpp"

#endif
