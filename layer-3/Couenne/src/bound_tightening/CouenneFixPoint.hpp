/*
 *
 * Name:    CouenneFixPoint.hpp
 * Author:  Pietro Belotti
 * Purpose: A bound tightener based on fixpoint computation
 *
 * (C) Pietro Belotti, 2010.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneFixPoint.hpp
 * @brief Fixpoint-based bound tightening via constraint propagation
 *
 * Implements Feasibility-Based Bound Tightening (FBBT) using fixpoint
 * iteration. Propagates bounds through expression DAG until no further
 * tightening is possible.
 *
 * @algorithm Feasibility-Based Bound Tightening (FBBT):
 * Propagate variable bounds through constraint DAG to fixpoint:
 * 1. Initialize: [l⁰, u⁰] from problem definition
 * 2. Forward propagation for each expression w = f(x):
 *    - Compute [w_L, w_U] from [x_L, x_U] using interval arithmetic
 * 3. Backward propagation (implied bounds):
 *    - For w = f(x) with [w_L, w_U], derive tighter [x_L, x_U]
 *    - Example: w = x·y, w_U = 10, y ∈ [2,5] ⟹ x ≤ 10/2 = 5
 * 4. Iterate until fixpoint: [l^k, u^k] = [l^{k-1}, u^{k-1}] or k > limit
 *
 * extendedModel_ creates auxiliary LP rows for tighter propagation.
 *
 * @math Interval arithmetic rules (forward):
 *   [a,b] + [c,d] = [a+c, b+d]
 *   [a,b] · [c,d] = [min(ac,ad,bc,bd), max(ac,ad,bc,bd)]
 *   exp([a,b]) = [exp(a), exp(b)]  (monotone functions)
 *
 * @complexity O(k · |V| · |E|) where k = iterations, |V| = variables,
 * |E| = expression nodes. Typically k = O(1) to O(depth of DAG).
 *
 * @ref Belotti et al. (2009). "Branching and bounds tightening techniques for
 *   non-convex MINLP". Optimization Methods & Software 24(4-5):597-634.
 *
 * @see CouenneProblem::boundTightening() for main bound tightening entry
 * @see expression::impliedBound() for backward propagation
 */
#ifndef COUENNEFIXPOINT_HPP
#define COUENNEFIXPOINT_HPP

#include "BonRegisteredOptions.hpp"

#include "BonOaDecBase.hpp"
#include "CglConfig.h"
#include "CglCutGenerator.hpp"
#include "OsiRowCut.hpp"
#include "OsiSolverInterface.hpp"

#include "CouenneBTPerfIndicator.hpp"

namespace Couenne {

  class CouenneProblem;

  /// Cut Generator for FBBT fixpoint

  class COUENNELIB_EXPORT CouenneFixPoint: public CglCutGenerator {

  public:

    /// constructor
    CouenneFixPoint (CouenneProblem *,
		     const Ipopt::SmartPtr<Ipopt::OptionsList>);

    /// copy constructor
    CouenneFixPoint  (const CouenneFixPoint &);

    /// destructor
    ~CouenneFixPoint ();

    /// clone method (necessary for the abstract CglCutGenerator class)
    CouenneFixPoint *clone () const
    {return new CouenneFixPoint (*this);}

    /// the main CglCutGenerator
    void generateCuts (const OsiSolverInterface &,
		       OsiCuts &,
		       const CglTreeInfo = CglTreeInfo ())
#if CGL_VERSION_MAJOR == 0 && CGL_VERSION_MINOR <= 57
    const
#endif
    ;

    /// Add list of options to be read from file
    static void registerOptions (Ipopt::SmartPtr <Bonmin::RegisteredOptions> roptions);

  protected:

    /// should we use an extended model or a more compact one?
    bool extendedModel_;

    /// pointer to the CouenneProblem representation
    CouenneProblem *problem_;

    /// Is this the first call?
    mutable bool firstCall_;

    /// CPU time
    mutable double CPUtime_;

    /// Number of bounds tightened
    mutable int nTightened_;

    /// Level at which to stop
    int levelStop_;

    /// Create a single cut
    void createRow (int, int,
		    int,
		    OsiSolverInterface *,
		    const int    *,
		    const double *,
		    const double,
		    const int,
		    bool,
		    int, int) const;

    /// Performance indicator
    CouenneBTPerfIndicator perfIndicator_;
  };
}

#endif
