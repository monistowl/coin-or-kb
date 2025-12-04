// Copyright (C) 2004, 2009 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpConvCheck.hpp
 * @brief Strategy interface for checking algorithm termination
 *
 * ConvergenceCheck is the abstract base for convergence testing
 * strategies. Called each iteration to determine if optimization
 * should continue, has converged, or has failed.
 *
 * @algorithm Convergence Testing for Interior Point Methods:
 *   Check scaled optimality conditions at each iteration:
 *   1. Primal feasibility: ||c(x)||∞ / s_c ≤ tol_feas.
 *   2. Dual feasibility: ||∇f - J^T y - z||∞ / s_d ≤ tol_dual.
 *   3. Complementarity: ||XZe||∞ / s_c ≤ tol_compl.
 *   4. Scaling: s_c = max(1, ||c||), s_d = max(1, ||∇f||, ||y||, ||z||).
 *   Acceptable point: same conditions with looser acceptable_tol.
 *   After n_acceptable iterations at acceptable level → stop.
 *
 * @math Optimality conditions (KKT) being checked:
 *   ∇f(x) - J_c^T y_c - J_d^T y_d - z_L + z_U = 0 (stationarity)
 *   c(x) = 0 (equality constraints)
 *   d_L ≤ d(x) ≤ d_U (inequality constraints)
 *   x_L ≤ x ≤ x_U, z_L ≥ 0, z_U ≤ 0 (bounds + sign)
 *   (x - x_L)·z_L = 0, (x_U - x)·z_U = 0 (complementarity)
 *
 * @complexity O(n + m) per convergence check (norms of vectors).
 *   Called once per iteration, negligible vs. linear solve cost.
 *
 * @see IpOptErrorConvCheck.hpp for the main implementation
 * @see IpRestoConvCheck.hpp for restoration phase convergence
 */

#ifndef __IPCONVCHECK_HPP__
#define __IPCONVCHECK_HPP__

#include "IpAlgStrategy.hpp"

namespace Ipopt
{

/** Base class for checking the algorithm termination criteria. */
class IPOPTLIB_EXPORT ConvergenceCheck: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   ConvergenceCheck()
   { }

   /** Destructor */
   virtual ~ConvergenceCheck()
   { }
   ///@}

   /** Convergence return enum */
   enum ConvergenceStatus
   {
      CONTINUE,
      CONVERGED,
      CONVERGED_TO_ACCEPTABLE_POINT,
      MAXITER_EXCEEDED,
      CPUTIME_EXCEEDED,
      WALLTIME_EXCEEDED,  ///< @since 3.14.0
      DIVERGING,
      USER_STOP,
      FAILED
   };

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Pure virtual method for performing the convergence test.
    *
    *  If call_intermediate_callback is true, the user callback method
    *  in the NLP should be called in order to see if the user
    *  requests an early termination.
    */
   virtual ConvergenceStatus CheckConvergence(
      bool call_intermediate_callback = true
   ) = 0;

   /** Method for testing if the current iterate is considered to
    *  satisfy the "acceptable level" of accuracy.
    *
    *  The idea is that if the desired convergence tolerance cannot
    *  be achieved, the algorithm might stop after a number of
    *  acceptable points have been encountered.
    */
   virtual bool CurrentIsAcceptable() = 0;

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
   //    ConvergenceCheck();
   /** Copy Constructor */
   ConvergenceCheck(
      const ConvergenceCheck&
   );

   /** Default Assignment Operator */
   void operator=(
      const ConvergenceCheck&
   );
   ///@}

};

} // namespace Ipopt

#endif
