/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file model/HighsModel.h
 * @brief Combined LP/QP model container
 *
 * **HighsModel Class:**
 * Combines HighsLp (linear constraints/objective) with HighsHessian (quadratic terms).
 *
 * **Data Members:**
 * - lp_: Linear program data (constraints, bounds, linear objective)
 * - hessian_: Quadratic objective term Q for QP: min 0.5*x'Qx + c'x
 *
 * **Model Type Detection:**
 * - isQp(): Returns true if hessian_.dim_ != 0
 * - isMip(): Delegates to lp_.isMip() (checks integrality constraints)
 * - isEmpty(): True if num_col_ == 0 and num_row_ == 0
 *
 * **Objective Evaluation:**
 * - objectiveValue(): Compute c'x + 0.5*x'Qx
 * - objectiveGradient(): Compute c + Qx
 *
 * @see HighsLp.h for LP data structure
 * @see HighsHessian.h for Hessian matrix
 */
#ifndef MODEL_HIGHS_MODEL_H_
#define MODEL_HIGHS_MODEL_H_

#include <vector>

#include "lp_data/HighsLp.h"
#include "model/HighsHessian.h"

class HighsModel;

class HighsModel {
 public:
  HighsLp lp_;
  HighsHessian hessian_;
  bool operator==(const HighsModel& model) const;
  bool equalButForNames(const HighsModel& model) const;
  bool isQp() const { return (this->hessian_.dim_ != 0); }
  bool isMip() const { return this->lp_.isMip(); }
  bool isEmpty() const {
    return (this->lp_.num_col_ == 0 && this->lp_.num_row_ == 0);
  }
  bool needsMods(const double infinite_cost) const {
    return this->lp_.needsMods(infinite_cost);
  }
  bool hasMods() const { return this->lp_.hasMods(); }
  void clear();
  double objectiveValue(const std::vector<double>& solution) const;
  void objectiveGradient(const std::vector<double>& solution,
                         std::vector<double>& gradient) const;
};

#endif
