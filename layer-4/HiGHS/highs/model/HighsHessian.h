/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file model/HighsHessian.h
 * @brief Sparse Hessian matrix for QP objective
 *
 * **HighsHessian Class:**
 * Stores quadratic objective term Q for QP: min 0.5*x'Qx + c'x
 *
 * **Sparse Storage (CSC-like):**
 * - dim_: Number of variables (Q is dim_ x dim_)
 * - format_: kTriangular (lower triangle) or kSquare (full matrix)
 * - start_[]: Column start indices
 * - index_[]: Row indices
 * - value_[]: Non-zero values
 *
 * **Operations:**
 * - product(): Compute Qx (Hessian-vector product)
 * - objectiveValue(): Compute 0.5*x'Qx
 * - objectiveCDoubleValue(): High-precision objective using HighsCDouble
 * - deleteCols(): Remove columns/rows for presolve
 *
 * @see HighsModel.h for combined LP+Hessian model
 * @see HConst.h for HessianFormat enum
 */
#ifndef MODEL_HIGHS_HESSIAN_H_
#define MODEL_HIGHS_HESSIAN_H_

#include <vector>

#include "lp_data/HConst.h"
#include "util/HighsCDouble.h"
#include "util/HighsUtils.h"

// class HighsHessian;

class HighsHessian {
 public:
  HighsHessian() { clear(); }
  HighsInt dim_;
  HessianFormat format_;
  std::vector<HighsInt> start_;
  std::vector<HighsInt> index_;
  std::vector<double> value_;
  bool operator==(const HighsHessian& hessian) const;
  void product(const std::vector<double>& solution,
               std::vector<double>& product) const;
  double objectiveValue(const std::vector<double>& solution) const;
  HighsCDouble objectiveCDoubleValue(const std::vector<double>& solution) const;
  void exactResize();
  void deleteCols(const HighsIndexCollection& index_collection);
  void clear();
  bool formatOk() const {
    return (this->format_ == HessianFormat::kTriangular ||
            this->format_ == HessianFormat::kSquare);
  };
  bool scaleOk(const HighsInt cost_scale, const double small_matrix_value,
               const double large_matrix_value) const;
  HighsInt numNz() const;

  void print() const;
};

#endif
