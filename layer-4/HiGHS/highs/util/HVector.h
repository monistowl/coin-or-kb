/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file util/HVector.h
 * @brief Sparse vector types for HiGHS simplex operations
 *
 * Type aliases for HVectorBase with different precision.
 *
 * **Types:**
 * - HVector: HVectorBase<double> - Standard precision sparse vector
 * - HVectorQuad: HVectorBase<HighsCDouble> - Quad precision for accuracy
 * - HVector_ptr, HVectorQuad_ptr: Pointer types for array storage
 *
 * **HVectorBase Features (from HVectorBase.h):**
 * - Sparse representation: index[] + array[] with count
 * - Dense operations: clear(), setup(), collectDense()
 * - SAXPY: Add scalar multiple of another vector
 * - Packed format for BLAS-style operations
 *
 * @see util/HVectorBase.h for implementation details
 * @see util/HighsCDouble.h for quad precision type
 */
#ifndef UTIL_HVECTOR_H_
#define UTIL_HVECTOR_H_

#include "util/HVectorBase.h"
#include "util/HighsCDouble.h"

using HVector = HVectorBase<double>;
using HVectorQuad = HVectorBase<HighsCDouble>;
using HVector_ptr = HVector*;
using HVectorQuad_ptr = HVectorQuad*;

#endif /* UTIL_HVECTOR_H_ */
