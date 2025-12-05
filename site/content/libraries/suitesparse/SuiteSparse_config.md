+++
title = "SuiteSparse_config"
description = "Central configuration and utility header for all SuiteSparse libraries"
template = "page.html"

[extra]
layer = 0
library = "SuiteSparse"
header_file = "SuiteSparse_config/SuiteSparse_config.h"
+++

Central configuration and utility header for all SuiteSparse libraries

This file provides the shared foundation for the entire SuiteSparse
collection of sparse matrix algorithms. Key features include:

- Compiler and platform detection (GCC, Clang, MSVC, ICC, NVCC)
- Configurable memory management with replaceable malloc/calloc/realloc/free
- Portable BLAS/LAPACK interface handling Fortran name mangling and integer sizes
- OpenMP detection and thread-safe timing utilities
- Complex number type definitions for C/C++ interoperability

@note Applications can customize memory allocation by calling the
      SuiteSparse_config_*_set functions before using any SuiteSparse library.

## Mathematics

<div class="math">

Implements the hypot function: sqrt(x^2 + y^2) using a numerically
stable algorithm that avoids intermediate overflow/underflow.

</div>

## See Also

- amd.h, colamd.h, cholmod.h, umfpack.h, klu.h for library-specific headers
- SuiteSparse_finish()
- SuiteSparse_start()
- SuiteSparse_calloc(), SuiteSparse_free()
- SuiteSparse_malloc(), SuiteSparse_free()
- SuiteSparse_malloc(), SuiteSparse_free()
- SuiteSparse_malloc(), SuiteSparse_calloc()
- SuiteSparse_toc(), SuiteSparse_time()
- SuiteSparse_tic()

## Source

Header file: [`SuiteSparse_config/SuiteSparse_config.h`](/browser/?library=SuiteSparse&file=SuiteSparse_config/SuiteSparse_config.h)

