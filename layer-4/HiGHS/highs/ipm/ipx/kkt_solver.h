/**
 * @file ipm/ipx/kkt_solver.h
 * @brief KKT System Solver Interface for Interior Point Methods
 *
 * Defines the interface for solving the augmented system (KKT system) that
 * arises in each iteration of primal-dual interior point methods.
 *
 * @algorithm KKT System in IPM:
 * The Newton step in interior point methods requires solving:
 *
 *   [ G   A' ] [Δx]   [a]
 *   [ A   0  ] [Δy] = [b]
 *
 * where:
 * - G = diagonal matrix with G[j,j] = zl[j]/xl[j] + zu[j]/xu[j]
 * - A = m×(n+m) constraint matrix [A | -I]
 * - (a,b) = right-hand side from Newton linearization
 *
 * SOLUTION APPROACHES:
 *
 * 1. AUGMENTED SYSTEM (Direct):
 *    Factor and solve the full (n+m+m) × (n+m+m) symmetric indefinite system.
 *    Uses LDL' or similar factorization with pivoting.
 *
 * 2. NORMAL EQUATIONS (Direct):
 *    Eliminate Δx: A·G⁻¹·A'·Δy = b - A·G⁻¹·a
 *    Smaller system (m×m) but squares condition number.
 *
 * 3. ITERATIVE (Krylov):
 *    Use CG/MINRES with preconditioner. The residual tolerance must satisfy:
 *    ‖D·res‖_∞ ≤ tol, where D[i,i] = √(1/G[i,i]) or 1 if G[i,i] = 0
 *
 * REGULARIZATION:
 * Near-optimal iterates have G[j,j] → ∞ for variables at bounds, causing
 * ill-conditioning. Regularization adds small ε to diagonal:
 * - Primal regularization: G + εP·I
 * - Dual regularization: zero block becomes -εD·I
 *
 * @math Condition number analysis:
 * - cond(KKT) ≈ max(G)/min(G) · cond(A)
 * - Near optimum: max(G)/min(G) → ∞ (ill-conditioned)
 * - Regularization bounds condition: max ≈ 1/ε
 * - Normal equations: cond(A·G⁻¹·A') ≈ cond(KKT)²
 *
 * @complexity
 * - Direct (augmented): O((n+m)³) dense, O(nnz · fill²) sparse
 * - Direct (normal): O(m³) dense, O(m · nnz + m² · fill) sparse
 * - Iterative: O(k · nnz) where k = iterations to convergence
 *
 * @ref Benzi, Golub & Liesen (2005). "Numerical Solution of Saddle Point
 *   Problems". Acta Numerica 14:1-137.
 * @ref Nocedal & Wright (2006). "Numerical Optimization", Chapter 16.
 *
 * @see ipm.h for interior point method using this interface
 * @see kkt_solver_basis.h for basis-based implementation
 */
#ifndef IPX_KKT_SOLVER_H_
#define IPX_KKT_SOLVER_H_

#include "ipm/ipx/basis.h"
#include "ipm/ipx/iterate.h"

namespace ipx {

class KKTSolver {
public:
    KKTSolver& operator=(const KKTSolver&) = delete;
    KKTSolver& operator=(KKTSolver&&) = delete;
    virtual ~KKTSolver() {}

    // Factorizes the KKT matrix (direct solver) or prepares preconditioner
    // (iterative solver). The diagonal matrix G is built from @iterate.
    // The implementation is allowed to change variable statuses to eliminate
    // close-to-converged variables from the IPM solve. Some implementations
    // allow @iterate to be NULL, in which case G is assumed to be the identity
    // matrix.
    void Factorize(Iterate* iterate, Info* info);

    // Solves KKT system. If an iterative method is used, @tol is the required
    // tolerance for the residual in (2) as specified above.
    void Solve(const Vector& a, const Vector& b, double tol,
               Vector& x, Vector& y, Info* info);

    // If an iterative method is used, returns the # iterations in all Solve()
    // calls since the last call to Factorize(). A direct solver returns the #
    // iterative refinement steps.
    Int iter() const;

    // If a basis matrix is maintained, returns the # basis changes in the last
    // call to Factorize(). Otherwise returns 0.
    Int basis_changes() const;

    // If a basis matrix is maintained, returns a pointer to it.
    // Otherwise returns NULL.
    const Basis* basis() const;

private:
    virtual void _Factorize(Iterate* iterate, Info* info) = 0;
    virtual void _Solve(const Vector& a, const Vector& b, double tol,
                         Vector& x, Vector& y, Info* info) = 0;
    virtual Int _iter() const = 0;
    virtual Int _basis_changes() const { return 0; }
    virtual const Basis* _basis() const { return nullptr; }
};

}  // namespace ipx

#endif  // IPX_KKT_SOLVER_H_
