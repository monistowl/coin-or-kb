// Copyright (C) 2005, 2009 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2005-10-13

/**
 * @file IpPDSearchDirCalc.hpp
 * @brief Newton search direction computation via primal-dual system
 *
 * PDSearchDirCalculator is the standard SearchDirectionCalculator
 * implementation that computes the Newton step by solving the
 * primal-dual KKT system.
 *
 * @algorithm Primal-Dual Newton Direction:
 *   ComputeSearchDirection():
 *   1. Assemble RHS from current residuals: r = (r_x, r_s, r_c, r_d, r_zL, ...).
 *   2. Call PDSystemSolver::Solve(KKT, rhs) → delta.
 *   3. Store result: IpData::delta() = (Δx, Δs, Δy_c, Δy_d, Δz_L, ...).
 *   4. If mehrotra_algorithm_: Use predictor-corrector centering.
 *   5. If fast_step_computation_: Skip residual verification.
 *
 * @math KKT system solved:
 *   [W + Σ,  0, J_c^T, J_d^T] [Δx  ]   [r_x]
 *   [  0,    Σ_s,  0,   -I  ] [Δs  ] = [r_s]
 *   [ J_c,   0,    0,    0  ] [Δy_c]   [r_c]
 *   [ J_d,  -I,    0,    0  ] [Δy_d]   [r_d]
 *   Where Σ, Σ_s are barrier/bound terms.
 *
 * ComputeSearchDirection():
 * 1. Assembles right-hand side from current residuals
 * 2. Calls PDSystemSolver::Solve() to get direction
 * 3. Stores result in IpData::delta()
 *
 * Algorithm options:
 * - fast_step_computation_: Skip residual verification (trust solver)
 * - mehrotra_algorithm_: Mehrotra predictor-corrector mode
 *   - Forces specific settings for adaptive mu
 *   - Disables various globalization features
 *
 * The PDSolver() accessor allows other components (e.g., second-order
 * correction in line search) to compute additional Newton solves.
 *
 * Direction stored in delta:
 * - delta_x, delta_s: Primal steps
 * - delta_y_c, delta_y_d: Equality multiplier steps
 * - delta_z_L, delta_z_U, delta_v_L, delta_v_U: Bound multiplier steps
 *
 * @see IpSearchDirCalculator.hpp for base interface
 * @see IpPDSystemSolver.hpp for the system solver interface
 * @see IpPDFullSpaceSolver.hpp for full-space implementation
 */

#ifndef __IPPDSEARCHDIRCALC_HPP__
#define __IPPDSEARCHDIRCALC_HPP__

#include "IpSearchDirCalculator.hpp"
#include "IpPDSystemSolver.hpp"

namespace Ipopt
{

/** Implementation of the search direction calculator that computes
 *  the pure primal dual step for the current barrier parameter.
 */
class IPOPTLIB_EXPORT PDSearchDirCalculator: public SearchDirectionCalculator
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   PDSearchDirCalculator(
      const SmartPtr<PDSystemSolver>& pd_solver
   );

   /** Destructor */
   virtual ~PDSearchDirCalculator();
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for computing the search direction.
    *
    *  The computed direction is stored in IpData().delta().
    */
   virtual bool ComputeSearchDirection();

   static void RegisterOptions(
      const SmartPtr<RegisteredOptions>& roptions
   );

   /** Returns the pd_solver for additional processing. */
   SmartPtr<PDSystemSolver> PDSolver()
   {
      return pd_solver_;
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
   /** Default Constructor */
   PDSearchDirCalculator();

   /** Copy Constructor */
   PDSearchDirCalculator(
      const PDSearchDirCalculator&
   );

   /** Default Assignment Operator */
   void operator=(
      const PDSearchDirCalculator&
   );
   ///@}

   /** @name Strategy objects */
   ///@{
   SmartPtr<PDSystemSolver> pd_solver_;
   ///@}

   /** @name Algorithmic parameters */
   ///@{
   /** Flag indicating that we trust that the steps from the linear
    *  solver are very good and that we don't need any residual
    *  checks. */
   bool fast_step_computation_;

   /** Flag indicating if we want to do Mehrotras's algorithm.
    *
    *  This means that a number of options are ignored, or have
    *  to be set (or are automatically set) to certain values.
    */
   bool mehrotra_algorithm_;
   ///@}

};

} // namespace Ipopt

#endif
