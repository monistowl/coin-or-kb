/*
 *
 * Name:    CouenneMultiVarProbe.hpp
 * Author:  Pietro Belotti
 * Purpose: Bound tightening using more than one variable
 *
 * (C) Pietro Belotti, 2010.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneMultiVarProbe.hpp
 * @brief Multi-variable probing for bound tightening
 *
 * @algorithm Multi-Variable Probing for OBBT
 *
 * Extension of single-variable probing that considers multiple
 * variables simultaneously for bound tightening. Can detect
 * implications that single-variable probing would miss.
 *
 * **Multi-variable probing:**
 * Instead of fixing one variable at a time, considers combinations
 * of variable settings to derive stronger implied bounds.
 *
 * **Example:**
 * Single-variable probing on x1 and x2 separately might not tighten bounds,
 * but probing x1=lb AND x2=ub together might prove infeasibility or
 * derive new bounds.
 *
 * **Parameters:**
 * - maxTime_: Maximum time for probing
 * - numCols_: Number of columns to consider
 *
 * @see CouenneAggrProbing for single-variable OBBT
 * @see CouenneFixPoint for FBBT
 */
#ifndef COUENNEMULTIVARPROBE_HPP
#define COUENNEMULTIVARPROBE_HPP

#include "BonRegisteredOptions.hpp"

#include "BonOaDecBase.hpp"
#include "CglCutGenerator.hpp"
#include "OsiColCut.hpp"
#include "OsiSolverInterface.hpp"
#include "CouenneProblem.hpp"
#include "BonCouenneSetup.hpp"

namespace Couenne {

  class CouenneMultiVarProbe: public CglCutGenerator {

  public:

    /// Constructor
    CouenneMultiVarProbe(CouenneSetup* couenne,
		       const Ipopt::SmartPtr<Ipopt::OptionsList> options);

    /// Copy constructor
    CouenneMultiVarProbe(const CouenneMultiVarProbe& rhs);

    /// Destructor
    ~CouenneMultiVarProbe();

    /// Clone method (necessary for the abstract CglCutGenerator class)
    CouenneMultiVarProbe *clone () const
    {return new CouenneMultiVarProbe (*this);}

    /// The main CglCutGenerator; not implemented yet
    void generateCuts(const OsiSolverInterface & solver,
		      OsiCuts& cuts,
		      const CglTreeInfo = CglTreeInfo ()) const;

  protected:

    /// Pointer to the CouenneProblem representation
    CouenneSetup* couenne_;

    /// Number of columns (want to have this handy)
    int numCols_;

    /// Maximum time to probe one variable
    double maxTime_;
  };
}

#endif
