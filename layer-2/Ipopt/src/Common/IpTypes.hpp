// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpTypes.hpp
 * @brief Fundamental type definitions for Ipopt (C++ namespace wrapper)
 *
 * Wraps the C type definitions from IpTypes.h in the Ipopt namespace:
 * - Number (ipnumber): floating-point type for all numerical values
 * - Index (ipindex): integer type for array indices and dimensions
 *
 * Actual types depend on compile-time configuration (IPOPT_SINGLE,
 * IPOPT_INT64). Default is double for Number and int for Index.
 *
 * @see IpTypes.h for underlying C definitions
 * @see IpoptConfig.h for configuration macros
 */

#ifndef __IPTYPES_HPP__
#define __IPTYPES_HPP__

#include "IpoptConfig.h"
#include "IpTypes.h"

namespace Ipopt
{

/** Type of all numbers */
typedef ipnumber Number;

/** Type of all indices of vectors, matrices etc */
typedef ipindex Index;

/** Type of default integer
 * @deprecated Use int instead.
 */
IPOPT_DEPRECATED
typedef int Int;

} // namespace Ipopt

#endif
