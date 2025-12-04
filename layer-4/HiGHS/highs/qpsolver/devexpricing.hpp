/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file devexpricing.hpp
 * @brief HiGHS Devex pricing for QP active set method
 *
 * Devex pricing strategy: approximate steepest edge using
 * reference framework with periodic weight updates.
 *
 * @algorithm Devex (Approximate Steepest Edge) for QP:
 *   Maintains approximate edge weights for efficient pricing:
 *   1. Initialize weights w_i = 1 for all constraints
 *   2. Select constraint s = argmax_i { λ_i² / w_i } with λ_i > threshold
 *   3. After active set change, update: w_s' = actual weight, w_i' = max(w_i, update²)
 *   4. Periodically reset weights to 1 (reference framework restart)
 *
 * @math Devex weight update (Harris, 1973):
 *   Entering constraint gets exact weight: w_s' = ||∇_s h(x)||²
 *   Other active: w_i' = max(w_i, (γ_i/γ_s)² · w_s')
 *   where γ is the pivot element contribution.
 *   Approximate weights converge to exact weights over iterations.
 *
 * @complexity O(|active_set|) per pricing operation.
 *   Weight update: O(|active_set|) per iteration (vs O(m²) for exact).
 *   Typically 80-90% as effective as steepest edge at lower cost.
 *
 * @ref Harris (1973). "Pivot selection methods of the Devex LP code".
 *      Mathematical Programming 5:1-28.
 *
 * @see Pricing for the base pricing interface
 * @see SteepestEdgePricing for exact weights (fewer iterations but more expensive)
 */
#ifndef __SRC_LIB_PRICING_DEVEXPRICING_HPP__
#define __SRC_LIB_PRICING_DEVEXPRICING_HPP__

#include "qpsolver/basis.hpp"
#include "qpsolver/pricing.hpp"
#include "qpsolver/reducedcosts.hpp"
#include "qpsolver/runtime.hpp"

// 42726, 78965776.391299, 559, 104.321553, 0.000669, 7937

class DevexPricing : public Pricing {
 private:
  Runtime& runtime;
  Basis& basis;
  ReducedCosts& redcosts;

  std::vector<double> weights;

  HighsInt chooseconstrainttodrop(const QpVector& lambda) {
    auto active_constraint_index = basis.getactive();
    auto constraintindexinbasisfactor = basis.getindexinfactor();

    HighsInt minidx = -1;
    double maxabslambda = 0.0;
    for (size_t i = 0; i < active_constraint_index.size(); i++) {
      HighsInt indexinbasis =
          constraintindexinbasisfactor[active_constraint_index[i]];
      if (indexinbasis == -1) {
        printf("error\n");
      }
      assert(indexinbasis != -1);

      double val = lambda.value[indexinbasis] * lambda.value[indexinbasis] /
                   weights[indexinbasis];
      if (val > maxabslambda && fabs(lambda.value[indexinbasis]) >
                                    runtime.settings.lambda_zero_threshold) {
        if (basis.getstatus(active_constraint_index[i]) ==
                BasisStatus::kActiveAtLower &&
            -lambda.value[indexinbasis] > 0) {
          minidx = active_constraint_index[i];
          maxabslambda = val;
        } else if (basis.getstatus(active_constraint_index[i]) ==
                       BasisStatus::kActiveAtUpper &&
                   lambda.value[indexinbasis] > 0) {
          minidx = active_constraint_index[i];
          maxabslambda = val;
        } else {
          // TODO
        }
      }
    }

    return minidx;
  }

 public:
  DevexPricing(Runtime& rt, Basis& bas, ReducedCosts& rc)
      : runtime(rt),
        basis(bas),
        redcosts(rc),
        // clang-format off
        weights(std::vector<double>(rt.instance.num_var, 1.0)) {};
  // clang-format on

  // B lambda = g
  // lambda = inv(B)g
  // lambda = Z'g == reduced gradient ??
  // no: lambda = Y'g !!
  // dual values updated as:
  // c_N^T  += alpha_D * a_p^T (pivotal row)
  // alpha_D = -c_q / a_pq
  HighsInt price(const QpVector& x, const QpVector& gradient) {
    QpVector& lambda = redcosts.getReducedCosts();
    HighsInt minidx = chooseconstrainttodrop(lambda);
    return minidx;
  }

  void recompute() {
    // do nothing
  }

  void update_weights(const QpVector& aq, const QpVector& ep, HighsInt p,
                      HighsInt q) {
    HighsInt rowindex_p = basis.getindexinfactor()[p];
    double weight_p = weights[rowindex_p];
    for (HighsInt i = 0; i < runtime.instance.num_var; i++) {
      if (i == rowindex_p) {
        weights[i] = weight_p / (aq.value[rowindex_p] * aq.value[rowindex_p]);
      } else {
        weights[i] += (aq.value[i] * aq.value[i]) /
                      (aq.value[rowindex_p] * aq.value[rowindex_p]) * weight_p *
                      weight_p;
      }
      if (weights[i] > 1e7) {
        weights[i] = 1.0;
      }
    }
  }
};

#endif
