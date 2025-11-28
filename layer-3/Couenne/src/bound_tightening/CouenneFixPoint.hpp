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
 * **Algorithm:**
 * 1. For each constraint g(x) <= 0, propagate bounds forward (x → g)
 * 2. Propagate bounds backward (g bounds → x bounds) via implied bounds
 * 3. Repeat until fixpoint (no bound changes) or iteration limit
 *
 * **Extended model option (extendedModel_):**
 * Creates additional LP rows for tighter propagation.
 *
 * **Performance tracking:**
 * - nTightened_: Count of bounds tightened
 * - CPUtime_: Time spent in FBBT
 * - perfIndicator_: Detailed performance metrics
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
