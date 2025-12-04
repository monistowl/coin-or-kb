/**
 * @file GraphBLAS_cuda.hpp
 * @brief Main GraphBLAS CUDA include with C++ complex type definitions
 * Copyright (c) 2017-2025, Timothy A. Davis. Apache-2.0 license.
 *
 * CUDA-compatible GraphBLAS header. Defines C++ complex types: GxB_FC32_t
 * (std::complex<float>), GxB_FC64_t (std::complex<double>). Macros GxB_CMPLXF,
 * GxB_CMPLX for construction. Includes GB_cuda_geometry.hpp. Used by JIT
 * kernels requiring complex arithmetic.
 *
 * @see GB_cuda.hpp for host-side CUDA utilities
 */

//------------------------------------------------------------------------------
// GraphBLAS/CUDA/GraphBLAS_cuda.hpp
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2025, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

extern "C"
{ 
    // definitions that modify GraphBLAS.h
    #include "include/GB_dev.h"
    #include "include/GB_compiler.h"
    #include "include/GB_warnings.h"
}

#ifndef GXB_COMPLEX_H
#define GXB_COMPLEX_H

    // C++ complex types for CUDA
    #include <cmath>
    #include <complex>
    typedef std::complex<float>  GxB_FC32_t ;
    typedef std::complex<double> GxB_FC64_t ;
    #define GxB_CMPLXF(r,i) GxB_FC32_t(r,i)
    #define GxB_CMPLX(r,i)  GxB_FC64_t(r,i)
    #define GB_HAS_CMPLX_MACROS 1

#endif

#undef GRAPHBLAS_VANILLA
#define GB_CUDA_FOLDER
#include "GraphBLAS.h"
#undef I

#define restrict GB_restrict

extern "C"
{ 
    #include "include/GB_abort.h"
}

#include "include/GB_cuda_geometry.hpp"

