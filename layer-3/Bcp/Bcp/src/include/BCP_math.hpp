// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_math.hpp
 * @brief Mathematical constants for BCP
 *
 * @algorithm Math Constants: BCP_DBL_MAX
 *
 * Defines BCP_DBL_MAX = 1e100 as "infinity" for optimization bounds.
 * Used instead of DBL_MAX to avoid numerical issues with infinity
 * arithmetic in LP solvers.
 */
#ifndef _BCP_MATH_H
#define _BCP_MATH_H

#define BCP_DBL_MAX 1e100

#endif
