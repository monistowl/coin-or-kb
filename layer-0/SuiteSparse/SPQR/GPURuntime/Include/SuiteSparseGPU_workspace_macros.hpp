/**
 * @file SuiteSparseGPU_workspace_macros.hpp
 * @brief Convenience macros for accessing Workspace CPU/GPU pointers
 * Copyright (c) 2013-2016, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * GPU_REFERENCE(ws, TYPE): safely get GPU pointer from Workspace with NULL check.
 * CPU_REFERENCE(ws, TYPE): safely get CPU pointer from Workspace with NULL check.
 * Both cast to TYPE and handle NULL workspace gracefully.
 *
 * @see SuiteSparseGPU_Workspace.hpp for Workspace class
 */

// =============================================================================
// SuiteSparse_GPURuntime/Include/SuiteSparseGPU_workspace_macros.hpp
// =============================================================================

// SuiteSparse_GPURuntime, Copyright (c) 2013-2016, Timothy A Davis,
// Sencer Nuri Yeralan, and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------

#ifndef SUITESPARSE_GPURUNTIME_WORKSPACE_MACROS_HPP
#define SUITESPARSE_GPURUNTIME_WORKSPACE_MACROS_HPP

#ifndef GPU_REFERENCE
#define GPU_REFERENCE(WORKSPACE, TYPE) \
    ((TYPE) (WORKSPACE != NULL ? (WORKSPACE)->gpu() : NULL))
#endif

#ifndef CPU_REFERENCE
#define CPU_REFERENCE(WORKSPACE, TYPE) \
    ((TYPE) (WORKSPACE != NULL ? (WORKSPACE)->cpu() : NULL))
#endif

#endif
