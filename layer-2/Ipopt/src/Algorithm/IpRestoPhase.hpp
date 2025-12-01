// Copyright (C) 2004, 2009 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpRestoPhase.hpp
 * @brief Strategy interface for restoration phase fallback
 *
 * RestorationPhase is the abstract base for the fallback mechanism
 * when the line search cannot make progress. The restoration phase
 * minimizes constraint violation to find a feasible point.
 *
 * Triggered when:
 * - Line search step size becomes too small
 * - No search direction can be computed (singular KKT system)
 * - Algorithm explicitly requests fallback (ActivateFallbackMechanism)
 *
 * Exceptions thrown on restoration failure:
 * - RESTORATION_CONVERGED_TO_FEASIBLE_POINT: Success, found feasible point
 * - RESTORATION_FAILED: Could not reduce infeasibility
 * - RESTORATION_MAXITER_EXCEEDED: Hit iteration limit
 * - RESTORATION_USER_STOP: User callback requested stop
 *
 * Main implementation: RestoIterationOutput minimizes ||c(x)||^2 + ||d(x)-s||^2
 * using the interior point method on a modified feasibility problem.
 *
 * @algorithm Restoration Phase (Feasibility Recovery):
 * When line search fails to find acceptable step, switch to minimizing
 * constraint violation using a modified interior point subproblem:
 * 1. Detect line search failure (step too small or filter blocking)
 * 2. Formulate feasibility problem: min Σ(p+n) s.t. c(x) = p-n, p,n ≥ 0
 * 3. Solve using nested Ipopt with modified NLP (RestoIpoptNLP)
 * 4. Return to original problem when feasible point found
 *
 * @math Restoration problem formulation:
 *   min_{x,p,n} ρ·(Σp_i + Σn_i) + ζ·||x - x_R||²
 *   s.t. c(x) - p + n = 0,  p ≥ 0, n ≥ 0
 * where x_R is reference point, ρ penalizes infeasibility,
 * ζ prevents wandering far from current iterate.
 *
 * For inequality-constrained problems:
 *   min Σ(p+n) s.t. c(x) = p-n, d_L ≤ d(x) ≤ d_U
 *
 * @complexity Same as main Ipopt: O(n³) per iteration for linear algebra.
 * May require many iterations to find feasible point. Worst case: problem
 * is infeasible and restoration certifies infeasibility.
 *
 * @ref Wächter & Biegler (2006). "On the implementation of an interior-point
 *   filter line-search algorithm for large-scale nonlinear programming".
 *   Mathematical Programming 106(1):25-57. [Section 3.3: Restoration phase]
 *
 * @see IpRestoMinC_1Nrm.hpp for the main implementation
 * @see IpRestoIpoptNLP.hpp for restoration phase NLP formulation
 * @see IpBacktrackingLineSearch.hpp for restoration phase trigger
 */

#ifndef __IPRESTOPHASE_HPP__
#define __IPRESTOPHASE_HPP__

#include "IpAlgStrategy.hpp"
#include "IpIpoptNLP.hpp"
#include "IpIpoptData.hpp"
#include "IpIpoptCalculatedQuantities.hpp"

namespace Ipopt
{

/** @name Exceptions */
///@{
/** Exception RESTORATION_FAILED for all trouble with the
 *  restoration phase.
 */
DECLARE_STD_EXCEPTION(RESTORATION_CONVERGED_TO_FEASIBLE_POINT);
DECLARE_STD_EXCEPTION(RESTORATION_FAILED);
DECLARE_STD_EXCEPTION(RESTORATION_MAXITER_EXCEEDED);
DECLARE_STD_EXCEPTION(RESTORATION_CPUTIME_EXCEEDED);
/// @since 3.14.0
DECLARE_STD_EXCEPTION(RESTORATION_WALLTIME_EXCEEDED);
DECLARE_STD_EXCEPTION(RESTORATION_USER_STOP);
///@}

/** Base class for different restoration phases.
 *
 *  The restoration phase is part of the FilterLineSearch.
 */
class RestorationPhase: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   RestorationPhase()
   { }

   /** Destructor */
   virtual ~RestorationPhase()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Method called to perform restoration for the filter line
    *  search method.
    */
   virtual bool PerformRestoration() = 0;

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   RestorationPhase(
      const RestorationPhase&
   );

   /** Default Assignment Operator */
   void operator=(
      const RestorationPhase&
   );
   ///@}
};

} // namespace Ipopt

#endif
