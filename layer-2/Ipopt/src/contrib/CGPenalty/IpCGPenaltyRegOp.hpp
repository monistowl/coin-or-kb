// Copyright (C) 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter        IBM       2007-06-01

/**
 * @file IpCGPenaltyRegOp.hpp
 * @brief Registration of Chen-Goldfarb penalty method options
 *
 * Declares RegisterOptions_CGPenalty(), which registers all options
 * specific to the Chen-Goldfarb penalty function globalization
 * strategy.
 *
 * Options include:
 * - Penalty parameter initialization and bounds
 * - PLPF (piecewise linear penalty function) parameters
 * - Fast direction control parameters
 * - Armijo and sufficient decrease factors
 * - Perturbation handling parameters
 *
 * Called when Ipopt is configured to use the CG penalty method
 * instead of the default filter line search.
 *
 * @see IpAlgRegOp.hpp for main algorithm options
 * @see IpCGPenaltyLSAcceptor.hpp for option usage
 */

#ifndef __IPCGPENALTYREGOP_HPP__
#define __IPCGPENALTYREGOP_HPP__

#include "IpSmartPtr.hpp"

namespace Ipopt
{
class RegisteredOptions;

void RegisterOptions_CGPenalty(
   const SmartPtr<RegisteredOptions>& roptions
);

} // namespace Ipopt

#endif
