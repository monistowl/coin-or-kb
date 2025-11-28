// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-08-16

/**
 * @file IpLinearSolversRegOp.hpp
 * @brief Registration of all linear solver options
 *
 * Declares RegisterOptions_LinearSolvers(), which registers options
 * for all available linear solvers (MA27, MA57, MA77, MA86, MA97,
 * MUMPS, Pardiso, WSMP, SPRAL, etc.).
 *
 * Called during Ipopt initialization to make solver-specific options
 * available through the OptionsList mechanism. Each solver interface
 * has its own RegisterOptions() method that is invoked here.
 *
 * Options typically include:
 * - Pivot tolerance bounds
 * - Ordering method selection
 * - Scaling options
 * - Memory allocation factors
 * - Parallelism settings (thread counts)
 *
 * @see IpAlgRegOp.hpp for algorithm options registration
 * @see IpInterfacesRegOp.hpp for interface options
 */

#ifndef __IPLINEARSOLVERSREGOP_HPP__
#define __IPLINEARSOLVERSREGOP_HPP__

#include "IpSmartPtr.hpp"

namespace Ipopt
{
class RegisteredOptions;

void RegisterOptions_LinearSolvers(
   const SmartPtr<RegisteredOptions>& roptions
);

} // namespace Ipopt

#endif
