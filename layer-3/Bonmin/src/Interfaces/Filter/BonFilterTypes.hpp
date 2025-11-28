/**
 * @file BonFilterTypes.hpp
 * @brief Fortran type definitions for FilterSQP interface
 *
 * Defines type aliases for interfacing with the Fortran FilterSQP library.
 * Uses FORTRAN_INTEGER_TYPE from Ipopt's configuration for portability
 * across different Fortran compilers (32-bit vs 64-bit integers).
 *
 * @see BonFilterSolver.hpp for the FilterSQP wrapper
 */
#ifndef BonFilterTypes_H
#define BonFilterTypes_H
#include "IpoptConfig.h"
namespace FilterTypes {
    /** Fortran type for integer used in filter. */
    typedef FORTRAN_INTEGER_TYPE fint;
    /** Fortran type for double.used in filter */
    typedef double real;
}
#endif
