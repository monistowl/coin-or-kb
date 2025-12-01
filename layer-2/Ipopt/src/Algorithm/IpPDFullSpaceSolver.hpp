// Copyright (C) 2004, 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpPDFullSpaceSolver.hpp
 * @brief Full-space primal-dual system solver with inertia correction
 *
 * PDFullSpaceSolver is the main implementation of PDSystemSolver.
 * It reduces the 8x8 primal-dual system to the 4x4 augmented system
 * by eliminating bound multiplier equations:
 *   d_z = S^{-1}(rhs_z - Z*P^T*d_x)
 *
 * Key features:
 * - Iterative refinement with quality monitoring (residual_ratio)
 * - Inertia correction via PDPerturbationHandler (adds delta_x, delta_c)
 * - Automatic retries with increased pivot tolerance
 * - Handles singular systems by adding regularization
 *
 * Parameters:
 * - min/max_refinement_steps: Iterative refinement bounds
 * - residual_ratio_max: Acceptable solution quality threshold
 * - neg_curv_test_tol: Tolerance for inertia heuristics
 *
 * @algorithm Full-Space Primal-Dual System Solver:
 * Reduces 8×8 KKT system to 4×4 augmented system by variable elimination:
 * 1. Eliminate bound multipliers: Δz = S⁻¹(r_z - Z·Pᵀ·Δx)
 * 2. Form augmented system with diagonal Σ = S⁻¹Z in (1,1) block
 * 3. Factor augmented system (via AugSystemSolver)
 * 4. Recover full solution by back-substitution
 *
 * @math Variable elimination for bound multipliers:
 * From complementarity rows: Z·Pᵀ·Δx + S·Δz = r_z
 * Solve: Δz = S⁻¹(r_z - Z·Pᵀ·Δx)
 *
 * Augmented system after elimination:
 * [W + Σ   Aᵀ ] [Δx]   [r_x - Pᵀ·S⁻¹·r_z]
 * [  A   -δ_c·I] [Δy] = [r_c              ]
 * where Σ = Pᵀ·S⁻¹·Z·P is diagonal and δ_c is constraint regularization.
 *
 * Iterative refinement: solve, compute residual r = b - Ax̂,
 * solve for correction, repeat until ||r||/||b|| < tol.
 *
 * @complexity Dominated by augmented system factorization:
 * O(n³) dense, O(nnz + n·fill) sparse. Iterative refinement adds
 * O(n²) per step for residual computation.
 *
 * @ref Wächter & Biegler (2006). "On the implementation of an interior-point
 *   filter line-search algorithm for large-scale nonlinear programming".
 *   Mathematical Programming 106(1):25-57. [Section 3.1: Linear algebra]
 *
 * @see IpPDSystemSolver.hpp for the interface
 * @see IpAugSystemSolver.hpp for the reduced system solver
 * @see IpPDPerturbationHandler.hpp for inertia correction
 */

#ifndef __IPPDFULLSPACESOLVER_HPP__
#define __IPPDFULLSPACESOLVER_HPP__

#include "IpPDSystemSolver.hpp"
#include "IpAugSystemSolver.hpp"
#include "IpPDPerturbationHandler.hpp"

namespace Ipopt
{

/** This is the implementation of the Primal-Dual System, using the
 *  full space approach with a direct linear solver.
 *
 *  A note on the iterative refinement: We perform at least
 *  min_refinement_steps number of iterative refinement steps.  If after
 *  one iterative refinement the quality of the solution (defined in
 *  ResidualRatio) does not improve or the maximal number of
 *  iterative refinement steps is exceeded before the tolerance
 *  residual_ratio_max_ is satisfied, we first ask the linear solver
 *  to solve the system more accurately (e.g. by increasing the
 *  pivot tolerance).  If that doesn't help or is not possible, we
 *  treat the system, as if it is singular (i.e. increase delta's).
 */
class PDFullSpaceSolver: public PDSystemSolver
{
public:
   /** @name /Destructor */
   ///@{
   /** Constructor that takes in the Augmented System solver that
    *  is to be used inside
    */
   PDFullSpaceSolver(
      AugSystemSolver&       augSysSolver,
      PDPerturbationHandler& perturbHandler
   );

   /** Default destructor */
   virtual ~PDFullSpaceSolver();
   ///@}

   /* overloaded from AlgorithmStrategyObject */
   bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Solve the primal dual system, given one right hand side.
    */
   virtual bool Solve(
      Number                alpha,
      Number                beta,
      const IteratesVector& rhs,
      IteratesVector&       res,
      bool                  allow_inexact = false,
      bool                  improve_solution = false
   );

   /** Methods for IpoptType */
   ///@{
   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );
   ///@}

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Default Constructor */
   PDFullSpaceSolver();

   /** Default Assignment Operator */
   PDFullSpaceSolver& operator=(
      const PDFullSpaceSolver&
   );
   ///@}

   /** @name Strategy objects to hold on to. */
   ///@{
   /** Pointer to the Solver for the augmented system */
   SmartPtr<AugSystemSolver> augSysSolver_;

   /** Pointer to the Perturbation Handler. */
   SmartPtr<PDPerturbationHandler> perturbHandler_;
   ///@}

   /**@name Data about the correction made to the system */
   ///@{
   /** A dummy cache to figure out if the deltas are still up to date */
   CachedResults<void*> dummy_cache_;

   /** Flag indicating if for the current matrix the solution quality
    *  of the augmented system solver has already been increased.
    */
   bool augsys_improved_;
   ///@}

   /** @name Parameters */
   ///@{
   /** Minimal number of iterative refinement performed per backsolve */
   Index min_refinement_steps_;

   /** Maximal number of iterative refinement performed per backsolve */
   Index max_refinement_steps_;

   /** Maximal allowed ratio of the norm of the residual over the
    *  norm of the right hand side and solution.
    */
   Number residual_ratio_max_;

   /** If the residual_ratio is larger than this value after trying
    *  to improve the solution, the linear system is assumed to be
    *  singular and modified.
    */
   Number residual_ratio_singular_;

   /** Factor defining require improvement to consider iterative
    *  refinement successful.
    */
   Number residual_improvement_factor_;

   /** Tolerance for heuristic to ignore wrong inertia */
   Number neg_curv_test_tol_;

   /** Do curvature test with primal regularization */
   bool neg_curv_test_reg_;
   ///@}

   /** Internal function for a single backsolve (which will be used
    *  for iterative refinement on the outside).
    *
    *  @return false, if for some reason the linear system
    *  could not be solved (e.g. when the regularization parameter
    *  becomes too large)
    */
   bool SolveOnce(
      bool                  resolve_unmodified,
      bool                  pretend_singular,
      const SymMatrix&      W,
      const Matrix&         J_c,
      const Matrix&         J_d,
      const Matrix&         Px_L,
      const Matrix&         Px_U,
      const Matrix&         Pd_L,
      const Matrix&         Pd_U,
      const Vector&         z_L,
      const Vector&         z_U,
      const Vector&         v_L,
      const Vector&         v_U,
      const Vector&         slack_x_L,
      const Vector&         slack_x_U,
      const Vector&         slack_s_L,
      const Vector&         slack_s_U,
      const Vector&         sigma_x,
      const Vector&         sigma_s,
      Number                alpha,
      Number                beta,
      const IteratesVector& rhs,
      IteratesVector&       res
   );

   /** Internal function for computing the residual (resid) given the
    * right hand side (rhs) and the solution of the system (res).
    */
   void ComputeResiduals(
      const SymMatrix&      W,
      const Matrix&         J_c,
      const Matrix&         J_d,
      const Matrix&         Px_L,
      const Matrix&         Px_U,
      const Matrix&         Pd_L,
      const Matrix&         Pd_U,
      const Vector&         z_L,
      const Vector&         z_U,
      const Vector&         v_L,
      const Vector&         v_U,
      const Vector&         slack_x_L,
      const Vector&         slack_x_U,
      const Vector&         slack_s_L,
      const Vector&         slack_s_U,
      const Vector&         sigma_x,
      const Vector&         sigma_s,
      Number                alpha,
      Number                beta,
      const IteratesVector& rhs,
      const IteratesVector& res,
      IteratesVector&       resid
   );

   /** Internal function for computing the ratio of the residual
    *  compared to the right hand side and solution.
    *
    *  The smaller this value, the better the solution.
    */
   Number ComputeResidualRatio(
      const IteratesVector& rhs,
      const IteratesVector& res,
      const IteratesVector& resid
   );

   /** @name Auxiliary functions */
   ///@{
   /** Compute \f$ x = S^{-1}(r + \alpha Z P^T d)\f$ */
   void SinvBlrmZPTdBr(
      Number        alpha,
      const Vector& S,
      const Vector& R,
      const Vector& Z,
      const Matrix& P,
      const Vector& g,
      Vector&       X
   );
   ///@}
};

} // namespace Ipopt

#endif
