/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file lp_data/HighsStatus.h
 * @brief Return status enum for HiGHS API calls
 *
 * **HighsStatus enum:**
 * - kError (-1): Operation failed
 * - kOk (0): Operation succeeded
 * - kWarning (1): Operation succeeded with warnings
 *
 * **Functions:**
 * - highsStatusToString(): Convert status to string
 * - interpretCallStatus(): Combine call and return status with logging
 * - worseStatus(): Return max(status0, status1) for status propagation
 *
 * @see HConst.h for HighsModelStatus (solver termination status)
 */
#ifndef LP_DATA_HIGHS_STATUS_H_
#define LP_DATA_HIGHS_STATUS_H_

#include <string>

#include "io/HighsIO.h"

enum class HighsStatus { kError = -1, kOk = 0, kWarning = 1 };

// Return a string representation of HighsStatus.
std::string highsStatusToString(HighsStatus status);

// Return the maximum of two HighsStatus and possibly report on
// call_status not being HighsStatus::kOk
HighsStatus interpretCallStatus(const HighsLogOptions log_options,
                                const HighsStatus call_status,
                                const HighsStatus from_return_status,
                                const std::string& message = "");

// Return the maximum of two HighsStatus
HighsStatus worseStatus(HighsStatus status0, HighsStatus status1);
#endif
