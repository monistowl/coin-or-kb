// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-08-16

/**
 * @file IpInterfacesRegOp.hpp
 * @brief Option registration for Interfaces subsystem
 *
 * Declares RegisterOptions_Interfaces() which registers all options
 * specific to the Interfaces module with the RegisteredOptions object.
 *
 * Called during IpoptApplication initialization to register options
 * like fixed_variable_treatment, dependency_detection_with_rhs, etc.
 *
 * @see IpRegOptions.hpp for the registration framework
 */

#ifndef __IPINTERFACESREGOP_HPP__
#define __IPINTERFACESREGOP_HPP__

#include "IpSmartPtr.hpp"

namespace Ipopt
{
class RegisteredOptions;

void RegisterOptions_Interfaces(
   const SmartPtr<RegisteredOptions>& roptions
);

} // namespace Ipopt

#endif
