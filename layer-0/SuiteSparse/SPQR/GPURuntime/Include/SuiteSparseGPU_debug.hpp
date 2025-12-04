/**
 * @file SuiteSparseGPU_debug.hpp
 * @brief Debug verbosity levels for SuiteSparse GPU runtime
 * Copyright (c) 2013-2016, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * Debug levels: OFF (0), ERRORONLY (1), CASUAL (2), VERBOSE (3), EXTREME (4).
 * GPURUNTIME_DLEVEL set based on NDEBUG: CASUAL when debugging, OFF otherwise.
 * Convenience macros: DEBUG_ATLEAST_ERRORONLY/CASUAL/VERBOSE/EXTREME.
 * GPURUNTIME_LOGFILE_PATH defaults to "SuiteSparse_GPURuntime-logfile.txt".
 */

// =============================================================================
// === SuiteSparse_GPURuntime/Include/SuiteSparseGPU_debug.hpp =================
// =============================================================================

// SuiteSparse_GPURuntime, Copyright (c) 2013-2016, Timothy A Davis,
// Sencer Nuri Yeralan, and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------

#ifndef SUITESPARSE_GPURUNTIME_DEBUG_HPP
#define SUITESPARSE_GPURUNTIME_DEBUG_HPP

#define GPURUNTIME_DLEVEL_OFF         0
#define GPURUNTIME_DLEVEL_ERRORONLY   1
#define GPURUNTIME_DLEVEL_CASUAL      2
#define GPURUNTIME_DLEVEL_VERBOSE     3
#define GPURUNTIME_DLEVEL_EXTREME     4

//------------------------------------------------------------------------------
// force debugging off
//------------------------------------------------------------------------------

#ifndef NDEBUG
#define NDEBUG
#endif

// uncomment this line to turn on debugging
// #undef NDEBUG

//------------------------------------------------------------------------------

#ifndef NDEBUG
#define GPURUNTIME_DLEVEL       GPURUNTIME_DLEVEL_CASUAL
#else
// no debugging
#define GPURUNTIME_DLEVEL       GPURUNTIME_DLEVEL_OFF
#endif

#define DEBUG_ATLEAST_ERRORONLY (GPURUNTIME_DLEVEL >= GPURUNTIME_DLEVEL_ERRORONLY)
#define DEBUG_ATLEAST_CASUAL    (GPURUNTIME_DLEVEL >= GPURUNTIME_DLEVEL_CASUAL)
#define DEBUG_ATLEAST_VERBOSE   (GPURUNTIME_DLEVEL >= GPURUNTIME_DLEVEL_VERBOSE)
#define DEBUG_ATLEAST_EXTREME   (GPURUNTIME_DLEVEL >= GPURUNTIME_DLEVEL_EXTREME)

#ifndef GPURUNTIME_LOGFILE_PATH
#define GPURUNTIME_LOGFILE_PATH "SuiteSparse_GPURuntime-logfile.txt"
#endif

#endif
