/**
 * @file power_method.h
 * @brief Power iteration for maximum eigenvalue estimation
 *
 * Template function implementing power method to estimate λ_max of
 * a symmetric positive semi-definite linear operator.
 *
 * **Algorithm:**
 * 1. Start with v = [1, 1/2, 1/3, ...] normalized
 * 2. Iterate: v ← f(v)/‖f(v)‖, λ ← ‖f(v)‖
 * 3. Converge when |λ_new - λ_old| ≤ 10⁻³·λ
 *
 * Maximum 100 iterations. Returns λ_max estimate and eigenvector in v.
 * Used for condition number estimation in maxvolume algorithm.
 *
 * @see maxvolume.h for usage in basis analysis
 */
#ifndef IPX_POWER_METHOD_H_
#define IPX_POWER_METHOD_H_

#include <cmath>
#include "ipm/ipx/ipx_internal.h"
#include "ipm/ipx/utils.h"

namespace ipx {

// Power method for estimating the maximum eigenvalue of a linear operator f.
// @func: function object that is called by func(v,fv) to evaluate fv=f(v).
// @v: vector of dimension of the linear operator. On return holds an
//     approximate eigenvector corresponding to the maximum eigenvalue of f.
// Returns an estimate for the maximum eigenvalue of f.

template <typename F>
double PowerMethod(F func, Vector& v) {
    const Int maxiter = 100;
    const double tol = 1e-3;
    const Int dim = v.size();
    Vector fv(dim);

    // Construct starting vector and normalize.
    for (Int i = 0; i < dim; i++)
        v[i] = 1.0 + 1.0/(i+1);
    v /= Twonorm(v);

    // Run power method
    double lambda = 0.0;
    Int iter = 0;
    while (iter++ < maxiter) {
        func(v, fv);
        double lambda_old = lambda;
        lambda = Twonorm(fv);
        v = fv/lambda;
        if (std::abs(lambda-lambda_old) <= tol*lambda)
            break;
    }
    return lambda;
}

}  // namespace ipx

#endif // IPX_POWER_METHOD_H_
