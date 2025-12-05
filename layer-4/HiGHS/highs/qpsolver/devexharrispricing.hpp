/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file devexharrispricing.hpp
 * @brief HiGHS Devex-Harris hybrid pricing
 *
 * Combined Devex and Harris ratio test for QP pricing.
 * Balances accuracy and numerical stability.
 *
 * @algorithm Devex-Harris Pricing for QP
 * @math Select leaving variable: p = argmax_i λ_i²/w_i (weighted DSE-like).
 *       Weight update: w_i ← max(w_i, (a_q[i]/a_q[p])² · w_p²).
 *       Approximates steepest edge without full recomputation.
 *       Reset weights when they grow too large (> 10⁷).
 * @complexity O(|active set|) per pricing. O(n) per weight update.
 * @ref Harris (1973). Devex pricing for numerical stability.
 */
#ifndef __SRC_LIB_PRICING_DEVEXHARRISPRICING_HPP__
#define __SRC_LIB_PRICING_DEVEXHARRISPRICING_HPP__

#include "qpsolver/basis.hpp"
#include "qpsolver/pricing.hpp"
#include "qpsolver/runtime.hpp"

// 44839, 78965849.088174, 559, 138.681866, 0.000671, 7998

class DevexHarrisPricing : public Pricing {
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
  DevexHarrisPricing(Runtime& rt, Basis& bas, ReducedCosts& rc)
      : runtime(rt),
        basis(bas),
        redcosts(rc),
        weights(std::vector<double>(rt.instance.num_var, 1.0)){};

  HighsInt price(const QpVector& x, const QpVector& gradient) {
    HighsInt minidx = chooseconstrainttodrop(redcosts.getReducedCosts());
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
        weights[i] =
            1 / (aq.value[rowindex_p] * aq.value[rowindex_p]) * weight_p;
      } else {
        weights[i] =
            max(weights[i], (aq.value[i] * aq.value[i]) /
                                (aq.value[rowindex_p] * aq.value[rowindex_p]) *
                                weight_p * weight_p);
      }
      if (weights[i] > 1e7) {
        weights[i] = 1.0;
      }
    }
  }
};

#endif
