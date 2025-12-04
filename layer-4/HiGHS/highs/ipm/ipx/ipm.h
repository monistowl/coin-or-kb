/**
 * @file ipm/ipx/ipm.h
 * @brief Mehrotra's Predictor-Corrector Interior Point Method
 *
 * Implements an interior point method (IPM) for linear programming using
 * Mehrotra's predictor-corrector technique with two KKT solves per iteration.
 *
 * @algorithm Mehrotra's Predictor-Corrector IPM:
 * A two-stage Newton method that achieves superlinear convergence in practice.
 *
 * PRIMAL-DUAL FORMULATION:
 * LP: min c'x  s.t. Ax = b, l ≤ x ≤ u
 * Introducing slacks: xl = x - l, xu = u - x (both ≥ 0)
 *
 * KKT conditions with barrier:
 *   Ax = b                    (primal feasibility)
 *   A'y + zl - zu = c         (dual feasibility)
 *   Xl·Zl = μe                (complementarity, xl ∘ zl = μ)
 *   Xu·Zu = μe                (complementarity, xu ∘ zu = μ)
 *   xl, xu, zl, zu ≥ 0        (non-negativity)
 *
 * PREDICTOR STEP (Affine Scaling):
 * Solve Newton system with μ = 0 (pure Newton toward boundary):
 *   [G   A'] [Δx]   [rb - A'Δy - Δzl + Δzu]
 *   [A   0 ] [Δy] = [rc]
 *   Δzl = -zl - (Zl/Xl)·Δxl
 *   Δzu = -zu - (Zu/Xu)·Δxu
 *
 * CORRECTOR STEP (Centering + Higher-order):
 * Based on predictor's step length α_aff, choose target:
 *   μ_target = σ · μ,  σ = (μ_aff / μ)³
 * Add correction terms for better centrality:
 *   sl = σμe - ΔXl_aff · ΔZl_aff
 *   su = σμe - ΔXu_aff · ΔZu_aff
 *
 * STEP SIZE SELECTION:
 * α_primal = max{α : x + α·Δx ≥ 0} · 0.9995
 * α_dual   = max{α : z + α·Δz ≥ 0} · 0.9995
 *
 * @math Convergence behavior:
 * - Theoretical: O(√n · log(1/ε)) iterations for ε-optimality
 * - Practical: 20-60 iterations regardless of problem size
 * - Superlinear convergence in terminal phase (σ → 0)
 *
 * Centering parameter σ ∈ [0,1]:
 * - σ = 0: Pure Newton (fast but may leave feasible region)
 * - σ = 1: Pure centering (stays centered but slow)
 * - Mehrotra: σ = (μ_aff/μ)³ adapts to iterate quality
 *
 * @complexity
 * - Per iteration: O(KKT_solve) = O(m²n) for dense, O(nnz · fill) for sparse
 * - Two KKT solves per iteration (predictor + corrector)
 * - Total: O(√n · log(1/ε) · KKT_solve) theoretical, much less in practice
 *
 * @ref Mehrotra (1992). "On the Implementation of a Primal-Dual Interior
 *   Point Method". SIAM Journal on Optimization 2(4):575-601.
 * @ref Wright (1997). "Primal-Dual Interior-Point Methods". SIAM.
 *
 * @see kkt_solver.h for linear system solver interface
 * @see crossover.h for converting IPM solution to basic solution
 * @see iterate.h for iterate data structure
 */
#ifndef IPX_IPM_H_
#define IPX_IPM_H_

#include "ipm/ipx/control.h"
#include "ipm/ipx/kkt_solver.h"
#include "ipm/ipx/iterate.h"

namespace ipx {

class IPM {
public:
    explicit IPM(const Control& control);

    // Initializes @iterate with a starting point for Driver(). The KKT solver
    // must allow Factorize(NULL, info) (see kkt_solver.h).
    // On return info->status_ipm is
    // IPX_STATUS_not_run    if successful,
    // IPX_STATUS_time_limit if the KKT solver was interrupted by time limit,
    // IPX_STATUS_failed     if the KKT solver failed with info->errflag.
    // If the method did not terminate successfully, @iterate is unchanged.
    void StartingPoint(KKTSolver* kkt, Iterate* iterate, Info* info);

    // Updates @iterate by interior point iterations. On return ipm_status is
    // IPX_STATUS_optimal       if iterate->term_crit_reached() is true,
    // IPX_STATUS_iter_limit    if info->iter >= maxiter(),
    // IPX_STATUS_no_progress   if no progress over a number of iterations,
    // IPX_STATUS_time_limit    if interrupted by time limit,
    // IPX_STATUS_failed        if the KKT solver failed with info->errflag.
    void Driver(KKTSolver* kkt, Iterate* iterate, Info* info);

    Int maxiter() const { return maxiter_; }
    void maxiter(Int i) { maxiter_ = i; }

private:
    struct Step;
    // IPM terminates when the complementarity gap of the current iterate
    // exceeds kDivergeTol times the smallest complementarity gap of all
    // iterates so far.
    static constexpr double kDivergeTol = 1e6;

    void ComputeStartingPoint();
    void Predictor(Step& step);
    void AddCorrector(Step& step);
    void Centring(Step& step, double mu_to_use);
    void AssessCentrality(const Vector& xl, const Vector& xu, const Vector& zl, 
                          const Vector& zu,double mu, bool print = true);
    bool EvaluateCentringStep(const Step& step, double prev_ratio, Int prev_bad);
    void StepSizes(const Step& step, bool isCentring = false);
    void MakeStep(const Step& step, bool isCentring = false);
    // Reduces the following linear system to KKT form:
    //  [ AI                 ] [dx ]    [rb]
    //  [ I  -I              ] [dxl] =  [rl]
    //  [ I      I           ] [dxu]    [ru]
    //  [          AI'  I -I ] [dy ]    [rc]
    //  [    Zl        Xl    ] [dzl]    [sl]
    //  [       Zu        Xu ] [dzu]    [su]
    // Each of @rb, @rc, @rl and @ru can be NULL, in which case its entries are
    // assumed to be 0.0. This is currently not used, but was implemented for
    // computing centrality correctors.
    void SolveNewtonSystem(const double* rb, const double* rc,
                           const double* rl, const double* ru,
                           const double* sl, const double* su, Step& lhs);
    void PrintHeader();
    void PrintOutput();

    const Control& control_;
    KKTSolver* kkt_{nullptr};
    Iterate* iterate_{nullptr};
    Info* info_{nullptr};

    double step_primal_{0.0}, step_dual_{0.0};
    // Counts the # bad iterations since the last good iteration. An iteration
    // is bad if the primal or dual step size is < 0.05.
    Int num_bad_iter_{0};
    // Smallest complementarity gap of all iterates so far.
    double best_complementarity_{0.0};

    Int maxiter_{-1};

    // indicators of centrality for centring steps
    double centring_ratio{0.0};
    Int bad_products{0};
};

}  // namespace ipx

#endif  // IPX_IPM_H_
