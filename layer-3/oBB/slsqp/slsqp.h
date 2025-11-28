/**
 * @file slsqp.h
 * @brief SLSQP (Sequential Least Squares Programming) algorithm - bundled with oBB
 *
 * SLSQP is a gradient-based algorithm for constrained nonlinear optimization
 * using sequential quadratic programming with BFGS updates.
 *
 * **Algorithm (Kraft, 1988):**
 * 1. Solve QP subproblem: min (1/2)d'Bd + g'd s.t. linearized constraints
 * 2. Line search along direction d
 * 3. Update Hessian approximation B using BFGS
 * 4. Repeat until convergence
 *
 * **nlopt_slsqp() Parameters:**
 * - n: Number of variables
 * - f, f_data: Objective function (with gradient)
 * - m, fc: Inequality constraints (m constraints, c(x) <= 0)
 * - p, h: Equality constraints (p constraints, h(x) = 0)
 * - lb, ub: Variable bounds
 * - x: Initial point (modified in place)
 * - minf: Output - optimal objective value
 * - stop: Stopping criteria (nlopt_stopping struct)
 *
 * **Characteristics:**
 * - Local, derivative-based optimization
 * - Handles nonlinear equality and inequality constraints
 * - Efficient for smooth, medium-scale problems
 * - Used by oBB for local refinement in global optimization
 *
 * @see nlopt.h for nlopt_constraint structure
 * @see nlopt-util.h for nlopt_stopping structure
 * @see oBB for global optimization framework
 */

#ifndef SLSQP_H
#define SLSQP_H

#include "nlopt.h"
#include "nlopt-util.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

nlopt_result nlopt_slsqp(unsigned n, nlopt_func f, void *f_data,
			 unsigned m, nlopt_constraint *fc,
			 unsigned p, nlopt_constraint *h,
			 const double *lb, const double *ub,
			 double *x, double *minf,
			 nlopt_stopping *stop);
#ifdef __cplusplus
}  /* extern "C" */
#endif /* __cplusplus */

#endif
