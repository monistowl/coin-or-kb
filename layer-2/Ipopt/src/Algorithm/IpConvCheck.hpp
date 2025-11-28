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
 * ConvergenceStatus enum values:
 * - CONTINUE: Keep iterating
 * - CONVERGED: Optimal solution found (tol satisfied)
 * - CONVERGED_TO_ACCEPTABLE_POINT: Acceptable solution (acceptable_tol)
 * - MAXITER_EXCEEDED, CPUTIME_EXCEEDED, WALLTIME_EXCEEDED: Limits hit
 * - DIVERGING: Objective unbounded or iterates diverging
 * - USER_STOP: User callback requested termination
 * - FAILED: Unrecoverable error
 *
 * Also provides CurrentIsAcceptable() for early termination logic.
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
