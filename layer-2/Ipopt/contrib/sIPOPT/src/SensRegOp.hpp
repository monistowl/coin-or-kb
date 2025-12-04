// Copyright 2009, 2011 Hans Pirnay
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file SensRegOp.hpp
 * @brief sIPOPT registration operations for options
 *
 * SensRegOp: registers sIPOPT-specific options with Ipopt.
 * Adds sensitivity analysis parameters like n_sens_steps, sens_prefix,
 * and computation modes to Ipopt option system.
 */

#ifndef __SENSREGOP_HPP__
#define __SENSREGOP_HPP__

#include "IpSmartPtr.hpp"

namespace Ipopt
{

class RegisteredOptions;

SIPOPTLIB_EXPORT void RegisterOptions_sIPOPT(
   const SmartPtr<RegisteredOptions>& roptions
);

} // namespace Ipopt

#endif
