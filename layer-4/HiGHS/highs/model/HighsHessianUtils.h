/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file model/HighsHessianUtils.h
 * @brief Utility functions for Hessian matrix manipulation
 *
 * Free functions for validating, transforming, and operating on Hessian matrices.
 *
 * **Validation:**
 * - assessHessian(): Comprehensive Hessian validation
 * - assessHessianDimensions(): Check dimension consistency
 * - okHessianDiagonal(): Verify positive diagonal for convexity
 *
 * **Transformation:**
 * - normaliseHessian(): Standardize Hessian format
 * - extractTriangularHessian(): Convert to lower-triangular storage
 * - triangularToSquareHessian(): Expand to full symmetric matrix
 * - completeHessianDiagonal(): Add missing diagonal entries
 * - completeHessian(): Extend to full variable dimension
 *
 * **Scaling:**
 * - userScaleHessian(): Apply/remove user-provided scaling factors
 *
 * **Reporting:**
 * - reportHessian(): Print Hessian structure and values
 *
 * @see model/HighsHessian.h for Hessian data structure
 * @see model/HighsModel.h for combined LP+QP model
 */
#ifndef MODEL_HIGHSHESSIANUTILS_H_
#define MODEL_HIGHSHESSIANUTILS_H_

#include <vector>

#include "lp_data/HighsOptions.h"
#include "lp_data/HighsStatus.h"
#include "model/HighsHessian.h"

// class HighsHessian;
// class HighsOptions;

using std::vector;

HighsStatus assessHessian(HighsHessian& hessian, const HighsOptions& options);
HighsStatus assessHessianDimensions(const HighsOptions& options,
                                    HighsHessian& hessian);
void completeHessianDiagonal(const HighsOptions& options,
                             HighsHessian& hessian);
bool okHessianDiagonal(const HighsOptions& options, HighsHessian& hessian,
                       const ObjSense sense = ObjSense::kMinimize);
HighsStatus normaliseHessian(const HighsOptions& options,
                             HighsHessian& hessian);
HighsStatus extractTriangularHessian(const HighsOptions& options,
                                     HighsHessian& hessian);
void triangularToSquareHessian(const HighsHessian& hessian,
                               vector<HighsInt>& start, vector<HighsInt>& index,
                               vector<double>& value);
void completeHessian(const HighsInt full_dim, HighsHessian& hessian);

void reportHessian(const HighsLogOptions& log_options, const HighsInt dim,
                   const HighsInt num_nz, const HighsInt* start,
                   const HighsInt* index, const double* value);

void userScaleHessian(HighsHessian& hessian, HighsUserScaleData& data,
                      const bool apply = true);
#endif  // MODEL_HIGHSHESSIANUTILS_H_
