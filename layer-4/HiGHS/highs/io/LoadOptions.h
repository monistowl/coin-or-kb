/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file io/LoadOptions.h
 * @brief Load solver options from file
 *
 * Parses options files into HighsOptions structure.
 *
 * **HighsLoadOptionsStatus:**
 * - kError: Parse failure or invalid option
 * - kOk: Options loaded successfully
 * - kEmpty: File exists but contains no options
 *
 * **loadOptionsFromFile():**
 * Reads option file with key=value pairs:
 * - Recognizes all HighsOptions fields
 * - Validates option names and value types
 * - Logs warnings for unknown options
 *
 * **File Format:**
 * Simple text format with one option per line:
 * ```
 * presolve = on
 * time_limit = 3600.0
 * mip_rel_gap = 0.01
 * ```
 *
 * @see lp_data/HighsOptions.h for option definitions
 * @see Highs::readOptions() for user-facing API
 */

#ifndef IO_LOAD_OPTIONS_H_
#define IO_LOAD_OPTIONS_H_

#include "lp_data/HighsOptions.h"

enum class HighsLoadOptionsStatus { kError = -1, kOk = 0, kEmpty = 1 };

// For extended options to be parsed from filename
HighsLoadOptionsStatus loadOptionsFromFile(
    const HighsLogOptions& report_log_options, HighsOptions& options,
    const std::string filename);

#endif
