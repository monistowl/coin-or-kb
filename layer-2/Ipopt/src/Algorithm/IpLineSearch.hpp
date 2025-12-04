// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpLineSearch.hpp
 * @brief Strategy interface for globalization via line search
 *
 * LineSearch is the abstract base for all line search strategies
 * in Ipopt's globalization framework. Given a search direction
 * (from IpData.delta()), finds an acceptable trial point.
 *
 * @algorithm Backtracking Line Search with Globalization:
 *   Given direction Δw from Newton step:
 *   1. Initialize α = 1 (full Newton step).
 *   2. Compute trial point: w_trial = w + α·Δw.
 *   3. Apply fraction-to-boundary: α ← min(α, τ·α_max) to stay positive.
 *   4. Check acceptance criterion (filter or merit function).
 *   5. If rejected: α ← ρ·α (backtrack, ρ ≈ 0.5) and goto 3.
 *   6. If α < α_min: activate fallback (restoration phase).
 *
 * @math Filter-based acceptance (Wächter-Biegler):
 *   Accept w_trial if it improves either objective φ(w) OR constraint
 *   violation θ(w) = ||c(x)||, and is not dominated by filter entries.
 *   Filter F = {(θ_i, φ_i)}: reject if θ(w_trial) ≥ θ_i AND φ(w_trial) ≥ φ_i.
 *   Switching condition: use Armijo on φ when θ is small enough.
 *
 * @complexity O(n_backtrack · eval_cost) where n_backtrack typically O(1)-O(10).
 *   Each trial requires function/constraint evaluation.
 *   Filter operations O(|F|) comparisons, |F| typically small.
 *
 * @see IpBacktrackingLineSearch.hpp for the main implementation
 * @see IpFilterLSAcceptor.hpp for filter-based acceptance
 * @see IpRestoPhase.hpp for the fallback restoration mechanism
 */

#ifndef __IPLINESEARCH_HPP__
#define __IPLINESEARCH_HPP__

#include "IpAlgStrategy.hpp"
#include "IpIpoptCalculatedQuantities.hpp"

namespace Ipopt
{

/** Base class for line search objects. */
class IPOPTLIB_EXPORT LineSearch: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   LineSearch()
   { }

   /** Destructor */
   virtual ~LineSearch()
   { }
   ///@}

   /** Perform the line search.
    *
    *  As search direction the delta in the data object is used.
    */
   virtual void FindAcceptableTrialPoint() = 0;

   /** Reset the line search.
    *
    *  This function should be called if all previous information
    *  should be discarded when the line search is performed the
    *  next time.  For example, this method should be called after
    *  the barrier parameter is changed.
    */
   virtual void Reset() = 0;

   /** Set flag indicating whether a very rigorous line search should
    *  be performed.
    *
    *  If this flag is set to true, the line search
    *  algorithm might decide to abort the line search and not to
    *  accept a new iterate.  If the line search decided not to
    *  accept a new iterate, the return value of
    *  CheckSkippedLineSearch() is true at the next call.  For
    *  example, in the non-monotone barrier parameter update
    *  procedure, the filter algorithm should not switch to the
    *  restoration phase in the free mode; instead, the algorithm
    *  should switch to the fixed mode.
    */
   virtual void SetRigorousLineSearch(
      bool rigorous
   ) = 0;

   /** Check if the line search procedure didn't accept a new iterate
    *  during the last call of FindAcceptableTrialPoint().
    */
   virtual bool CheckSkippedLineSearch() = 0;

   /** This method should be called if the optimization process
    *  requires the line search object to switch to some fallback
    *  mechanism (like the restoration phase), when the regular
    *  optimization procedure cannot be continued (for example,
    *  because the search direction could not be computed).
    *
    *  This will cause the line search object to immediately proceed
    *  with this mechanism when FindAcceptableTrialPoint() is call.
    *
    *  @return false, if no fallback mechanism is available.
    */
   virtual bool ActivateFallbackMechanism() = 0;

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
   /** Copy Constructor */
   LineSearch(
      const LineSearch&
   );

   void operator=(
      const LineSearch&
   );
   ///@}

};

} // namespace Ipopt

#endif
