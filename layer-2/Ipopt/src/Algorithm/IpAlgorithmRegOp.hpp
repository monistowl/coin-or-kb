// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-08-16

/**
 * @file IpAlgorithmRegOp.hpp
 * @brief Registration function for all Algorithm module options
 *
 * Declares RegisterOptions_Algorithm() which registers all options
 * for the Ipopt algorithm components with the RegisteredOptions system.
 *
 * This function is called during IpoptApplication initialization to
 * make all algorithm options available. It aggregates option registration
 * from numerous strategy classes.
 *
 * Registered option categories include:
 * - Main algorithm options (IpoptAlgorithm)
 * - Line search options (BacktrackingLineSearch, FilterLSAcceptor)
 * - Barrier parameter options (MonotoneMuUpdate, AdaptiveMuUpdate)
 * - Linear solver options (PDFullSpaceSolver, AugSystemSolver)
 * - Initialization options (DefaultIterateInitializer)
 * - Scaling options (NLPScaling, GradientScaling)
 * - Convergence options (OptimalityErrorConvergenceCheck)
 * - Output options (OrigIterationOutput)
 *
 * @see IpRegOptions.hpp for the options registration framework
 * @see IpoptApplication::RegisterAllOptions
 */

#ifndef __IPALGORITHMREGOP_HPP__
#define __IPALGORITHMREGOP_HPP__

#include "IpSmartPtr.hpp"

namespace Ipopt
{
class RegisteredOptions;

void RegisterOptions_Algorithm(
   const SmartPtr<RegisteredOptions>& roptions
);

} // namespace Ipopt

#endif
