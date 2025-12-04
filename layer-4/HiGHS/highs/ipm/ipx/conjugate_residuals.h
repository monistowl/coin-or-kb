/**
 * @file ipm/ipx/conjugate_residuals.h
 * @brief Conjugate Residuals Method for Symmetric Positive Definite Systems
 *
 * Implements preconditioned Conjugate Residuals (CR) for iteratively solving
 * the KKT system in interior point methods.
 *
 * @algorithm Conjugate Residuals (CR):
 * A Krylov subspace method for solving Cx = b where C is symmetric positive
 * definite.
 *
 * KEY DIFFERENCE FROM CG:
 * - CG minimizes ‖x - x*‖_C (error in C-norm)
 * - CR minimizes ‖Cx - b‖₂ (residual in 2-norm)
 * CR is preferred when monitoring residual convergence directly.
 *
 * UNPRECONDITIONED CR:
 *   r₀ = b - C·x₀
 *   p₀ = r₀, s₀ = C·r₀
 *   for k = 0, 1, 2, ...
 *     α = (rₖ, sₖ) / (sₖ, sₖ)
 *     xₖ₊₁ = xₖ + α·pₖ
 *     rₖ₊₁ = rₖ - α·C·pₖ
 *     sₖ₊₁ = C·rₖ₊₁
 *     β = (rₖ₊₁, sₖ₊₁) / (rₖ, sₖ)
 *     pₖ₊₁ = rₖ₊₁ + β·pₖ
 *
 * PRECONDITIONED CR (with preconditioner P ≈ C⁻¹):
 *   Effectively solves: P^{1/2}·C·P^{1/2}·y = P^{1/2}·b, x = P^{1/2}·y
 *   - Apply P to residual: z = P·r
 *   - Update formulas modified to use preconditioned vectors
 *
 * TERMINATION CRITERION:
 * - Without scaling: ‖rₖ‖_∞ ≤ tol
 * - With scaling: ‖D·rₖ‖_∞ ≤ tol where D = diag(resscale)
 *
 * The scaled criterion is important for IPM where different components
 * have vastly different magnitudes.
 *
 * @math Convergence analysis:
 * After k iterations: ‖rₖ‖ ≤ 2·((√κ-1)/(√κ+1))^k·‖r₀‖
 * where κ = cond(C) = λ_max/λ_min
 *
 * Preconditioning reduces effective condition number:
 * κ_eff = cond(P·C) << κ
 *
 * For IPM: C is the reduced KKT system (normal equations form),
 * P is basis-based preconditioner using approximate LU factors.
 *
 * @complexity
 * - Per iteration: 1 mat-vec with C + 1 preconditioner apply (if used)
 * - Typical iterations: O(√κ) or O(√κ_eff) with preconditioning
 * - Total: O(k · nnz) for k iterations
 *
 * @ref Saad (2003). "Iterative Methods for Sparse Linear Systems", 2nd ed.
 *   Algorithm 6.20.
 * @ref Schork (2018). "Basis Preconditioning in Interior Point Methods".
 *   PhD thesis, Section 6.3.
 *
 * @see kkt_solver.h for iterative KKT solver using this method
 * @see linear_operator.h for matrix/preconditioner interface
 */
#ifndef IPX_CONJUGATE_RESIDUALS_H_
#define IPX_CONJUGATE_RESIDUALS_H_

#include "ipm/ipx/control.h"
#include "ipm/ipx/linear_operator.h"

namespace ipx {

class ConjugateResiduals {
public:
    // Constructs a ConjugateReisdual object. The object does not have any
    // memory allocated between calls to Solve().
    // @control for InterruptCheck() and Debug(). No parameters are accessed.
    ConjugateResiduals(const Control& control);

    // Solves C*lhs = rhs. @lhs has initial iterate on entry, solution on
    // return. The method terminates when reaching the accuracy criterion
    //
    //   Infnorm(residual) <= tol               (if resscale == NULL), or
    //   Infnorm(resscale.*residual) <= tol     (if resscale != NULL).
    //
    // In the latter case, @resscale must be an array of dimension @rhs.size().
    // The method also stops after @maxiter iterations. If @maxiter < 0, a
    // maximum of @rhs.size()+100 iterations is performed. (In exact arithmetic
    // the solution would be found after @rhs.size() iterations. It happened on
    // some LP models with m << n, e.g. "rvb-sub" from MIPLIB2010, that the CR
    // method did not reach the termination criterion within m iterations,
    // causing the IPM to fail. Giving the CR method 100 extra iterations
    // resolved the issue on all LP models from our test set where it occurred.)
    //
    // If the @P argument is given, it is used as preconditioner (which
    // approximates inverse(C)) and must be symmetric positive definite.
    //
    void Solve(LinearOperator& C, const Vector& rhs,
               double tol, const double* resscale, Int maxiter, Vector& lhs);
    void Solve(LinearOperator& C, LinearOperator& P, const Vector& rhs,
               double tol, const double* resscale, Int maxiter, Vector& lhs);

    // Returns 0 if the last call to Solve() terminated successfully (i.e.
    // the system was solved to the required accuracy). Otherwise returns
    // IPX_ERROR_cr_iter_limit          if iteration limit was reached
    // IPX_ERROR_cr_matrix_not_posdef   if v'*C*v <= 0 for some vector v
    // IPX_ERROR_cr_precond_not_posdef  if v'*P*v <= 0 for some vector v
    // IPX_ERROR_cr_inf_or_nan          if overflow occurred
    // IPX_ERROR_cr_no_progress         if no progress due to round-off errors
    // IPX_ERROR_user_interrupt         if interrupted by user in control
    // IPX_ERROR_time_interrupt         if interrupted by time limit in control
    Int errflag() const;

    // Returns the # iterations in the last call to Solve().
    Int iter() const;

    // Returns the runtime of the last call to Solve().
    double time() const;

private:
    const Control& control_;
    Int errflag_{0};
    Int iter_{0};
    double time_{0.0};
};

}  // namespace ipx

#endif  // IPX_CONJUGATE_RESIDUALS_H_
