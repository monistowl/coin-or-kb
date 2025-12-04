// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-09-05

/**
 * @file IpInexactRegOp.hpp
 * @brief Registration function for all inexact algorithm options
 *
 * RegisterOptions_Inexact() registers all configurable parameters
 * for the inexact Newton algorithm variant with the options system.
 *
 * @algorithm Option Registration:
 *   RegisterOptions_Inexact(roptions):
 *   1. Calls RegisterOptions() on all Inexact* classes.
 *   2. Registers termination test parameters (tcc_*, tt_*).
 *   3. Registers Pardiso iterative parameters (dropping, fill, etc.).
 *   4. Registers decomposition and line search options.
 *   Centralizes registration for clean algorithm construction.
 *
 * @see IpAlgBuilder.hpp for how options are used during construction
 */

#ifndef __IPINEXACTREGOP_HPP__
#define __IPINEXACTREGOP_HPP__

#include "IpSmartPtr.hpp"

namespace Ipopt
{

class RegisteredOptions;

void RegisterOptions_Inexact(
   const SmartPtr<RegisteredOptions>& roptions
);

} // namespace Ipopt

#endif
