/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file gradient.hpp
 * @brief HiGHS QP gradient maintenance
 *
 * Incremental gradient updates for QP active set method.
 *
 * @algorithm Incremental QP Gradient Update
 * @math Gradient ∇f(x) = Qx + c. After step x → x + αp:
 *       ∇f(x+αp) = Q(x+αp) + c = ∇f(x) + αQp.
 *       Update via SAXPY: gradient ← gradient + α·(Qp).
 *       Recompute periodically to prevent numerical drift.
 * @complexity O(nnz(Q)) for full recompute. O(nnz(Qp)) per update.
 */
#ifndef __SRC_LIB_GRADIENT_HPP__
#define __SRC_LIB_GRADIENT_HPP__

#include "qpvector.hpp"
#include "runtime.hpp"

class Gradient {
  Runtime& runtime;

  QpVector gradient;
  bool uptodate;
  HighsInt numupdates = 0;

 public:
  Gradient(Runtime& rt)
      : runtime(rt), gradient(QpVector(rt.instance.num_var)), uptodate(false) {}

  void recompute() {
    runtime.instance.Q.vec_mat(runtime.primal, gradient);
    gradient += runtime.instance.c;
    uptodate = true;
    numupdates = 0;
  }

  QpVector& getGradient() {
    if (!uptodate ||
        numupdates >= runtime.settings.gradientrecomputefrequency) {
      recompute();
    }
    return gradient;
  }

  void update(QpVector& buffer_Qp, double stepsize) {
    gradient.saxpy(stepsize, buffer_Qp);
    numupdates++;
  }
};

#endif
