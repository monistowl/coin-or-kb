// Copyright (C) 2008, 2011 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-09-19

/**
 * @file IpInexactPDTerminationTester.hpp
 * @brief Termination tests for primal-dual iterative solves
 *
 * InexactPDTerminationTester implements the termination criteria for
 * iterative solvers computing the primal-dual (tangential) step.
 *
 * @algorithm Primal-Dual Termination Tests:
 *   TestTermination(sol, resid, iter) evaluates:
 *   - TEST_1: ||r|| ≤ κ₁·||rhs|| (relative residual tolerance).
 *   - TEST_2: ||Δy|| ≤ κ₂ + ε₂·||∇φ + A^T·y|| (dual update small).
 *   - TEST_3: ||r|| ≤ ε₃·||rhs||^exp (superlinear forcing sequence).
 *   - TCC: ||A·u_t||₂ ≤ ψ·θ·μ^exp (tangential component condition).
 *   - MODIFY_HESSIAN: Iteration count exceeded without progress.
 *   Early termination critical for inexact Newton efficiency.
 *
 * @math Termination test theory:
 *   Inexact Newton: solve F'(x)·d = -F(x) with ||r|| ≤ η·||F(x)||.
 *   Forcing sequence {η_k}: η_k → 0 for superlinear convergence.
 *   TCC ensures tangential step stays in null(J) approximately.
 *   Parameters: tcc_psi (ψ), tcc_theta (θ), tt_kappa1/2, tt_eps2/3.
 *
 * @complexity O(n) per test (norm computations).
 *   Precomputes curr_Av_*, curr_tt*_norm for efficiency.
 *
 * @see IpIterativeSolverTerminationTester.hpp for base interface
 * @see IpInexactPDSolver.hpp for the solver using these tests
 */

#ifndef __IPINEXACTPDTERMINATIONTESTER_HPP__
#define __IPINEXACTPDTERMINATIONTESTER_HPP__

#include "IpIterativeSolverTerminationTester.hpp"

namespace Ipopt
{

/** This class implements the termination tests for the primal-dual
 *  system.
 */
class InexactPDTerminationTester: public IterativeSolverTerminationTester
{
public:
   /** @name Constructor/Destructor */
   ///@{
   /** Default constructor
    */
   InexactPDTerminationTester();

   /** Destructor */
   virtual ~InexactPDTerminationTester();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

   /** Method for initializing for the next iterative solve.
    *
    *  This must be call before the test methods are called.
    */
   virtual bool InitializeSolve();

   /** This method checks if the current solution of the iterative
    *  linear solver is good enough (by returning the corresponding
    *  satisfied termination test), or if the Hessian should be
    *  modified.
    *
    *  The input is the dimension of the augmented system,
    *  the current solution vector of the augmented system, the
    *  current residual vector.
    */
   virtual ETerminationTest TestTermination(
      Index         ndim,
      const Number* sol,
      const Number* resid,
      Index         iter,
      Number        norm2_rhs
   );

   /** This method can be called after the Solve is over and we can
    *  delete anything that has been allocated to free memory.
    */
   virtual void Clear();

   /** Return the number of iterative solver iteration from the most
    *  recent solve.
    */
   virtual Index GetSolverIterations() const
   {
      return last_iter_;
   }

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
   /** Overloaded Assignment Operator */
   InexactPDTerminationTester& operator=(
      const InexactPDTerminationTester&
   );
   ///@}

   /** @name Algorithmic options */
   ///@{
   /** Psi factor in the tangential component condition */
   Number tcc_psi_;
   /** theta factor in the tangential component condition */
   Number tcc_theta_;
   /** mu exponent when multiplied to theta in the tangential
    *  component condition
    */
   Number tcc_theta_mu_exponent_;
   /** zeta factor in the tangential component condition */
   Number tcc_zeta_;
   /** kappa_1 factor in termination test 1 */
   Number tt_kappa1_;
   /** kappa_2 factor in termination test 2 */
   Number tt_kappa2_;
   /** eps_2 constant in termination test 2 */
   Number tt_eps2_;
   /** eps_3 constant in termination test 3 */
   Number tt_eps3_;
   /** rho constant from penalty parameter update.
    *
    *  This is called \f$\tau_{\pi}\f$ in MIPS paper.
    */
   Number rho_;
   /** Desired reduction of residual */
   Number inexact_desired_pd_residual_;
   /** Number of iterations allowed for desired pd residual */
   Index inexact_desired_pd_residual_iter_;
   /** Is set to true if the linear system is scaled via slacks. */
   bool requires_scaling_;
   ///@}

   /** @name Quantities that are identical for all tests and can be
    *  precomputed.
    */
   ///@{
   SmartPtr<const Vector> curr_Av_c_;
   SmartPtr<const Vector> curr_Av_d_;
   Number c_norm_;
   Number c_plus_Av_norm_;
   Number v_norm_scaled_;
   SmartPtr<const Vector> curr_grad_barrier_obj_x_;
   SmartPtr<const Vector> curr_grad_barrier_obj_s_; // in original space
   SmartPtr<const Matrix> curr_jac_c_;
   SmartPtr<const Matrix> curr_jac_d_;
   SmartPtr<const Vector> curr_scaling_slacks_;
   SmartPtr<Vector> curr_nabla_phi_plus_ATy_x_;
   SmartPtr<Vector> curr_nabla_phi_plus_ATy_s_; // in scaled space
   Number curr_Av_norm_;
   Number curr_tt1_norm_;
   Number curr_tt2_norm_;
   SmartPtr<const Vector> curr_Wv_x_;
   SmartPtr<const Vector> curr_Wv_s_; // in original space
   bool try_tt2_;
   ///@}

   /** @name Quantities from previous iteration required in the tests */
   ///@{
   Number last_Av_norm_;
   Number last_tt1_norm_;
   ///@}

   /** Last iterative solver iteration counter */
   Index last_iter_;
};

} // namespace Ipopt

#endif
