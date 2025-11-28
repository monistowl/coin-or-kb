/* Copyright (C) 2006 International Business Machines and others.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * Authors:  Andreas Waechter               IBM    2006-03-01
 */

/**
 * @file IpReturnCodes.hpp
 * @brief C++ namespace wrapper for Ipopt return codes
 *
 * Wraps IpReturnCodes_inc.h in Ipopt namespace for C++ usage.
 * Defines ApplicationReturnStatus enum used by IpoptApplication:
 *
 * - Solve_Succeeded: Optimal solution found
 * - Solved_To_Acceptable_Level: Acceptable tolerance met
 * - Infeasible_Problem_Detected: Locally infeasible
 * - Maximum_Iterations_Exceeded, Maximum_CpuTime_Exceeded
 * - Restoration_Failed, Error_In_Step_Computation
 * - Invalid_Option, Invalid_Number_Detected
 * - Not_Enough_Degrees_Of_Freedom, Internal_Error
 *
 * @see IpReturnCodes_inc.h for actual enum definitions
 * @see IpIpoptApplication.hpp for usage context
 */

#ifndef __IPRETURNCODES_HPP__
#define __IPRETURNCODES_HPP__

/* include from a common include file */

namespace Ipopt
{
#include "IpReturnCodes_inc.h"
}

#endif
