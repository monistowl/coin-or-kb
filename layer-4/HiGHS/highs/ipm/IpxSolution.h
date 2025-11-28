/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file ipm/IpxSolution.h
 * @brief IPX interior point solution container
 *
 * Stores primal/dual solution and basis status from IPX solver.
 *
 * **IpxSolution Struct:**
 * Solution data in IPX's native format for transfer to HiGHS:
 * - num_col, num_row: Problem dimensions
 * - ipx_col_value[], ipx_row_value[]: Primal solution (x, slacks)
 * - ipx_col_dual[], ipx_row_dual[]: Dual solution (reduced costs, duals)
 * - ipx_col_status[], ipx_row_status[]: Basis status for crossover
 *
 * **Status Values:**
 * IPX uses its own status encoding (see ipx_status.h):
 * - Basic, AtLower, AtUpper, Free for variables
 * - Converted to HighsBasisStatus in IpxWrapper
 *
 * **Usage:**
 * 1. IPX populates after solve
 * 2. IpxWrapper extracts to HighsSolution/HighsBasis
 * 3. Crossover uses basis status for simplex warm start
 *
 * @see ipm/IpxWrapper.h for solution extraction
 * @see lp_data/HighsSolution.h for HiGHS solution format
 */
#ifndef IPM_IPX_SOLUTION_H_
#define IPM_IPX_SOLUTION_H_

#include <stdint.h>

#include <vector>

#include "util/HighsInt.h"
typedef HighsInt ipxint;

struct IpxSolution {
  ipxint num_col;
  ipxint num_row;
  std::vector<double> ipx_col_value;
  std::vector<double> ipx_row_value;
  std::vector<double> ipx_col_dual;
  std::vector<double> ipx_row_dual;
  std::vector<ipxint> ipx_col_status;
  std::vector<ipxint> ipx_row_status;
};

#endif
