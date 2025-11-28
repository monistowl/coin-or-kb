/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file io/FilereaderEms.h
 * @brief EMS format file reader/writer (internal HiGHS format)
 *
 * Implements Filereader interface for EMS format.
 *
 * **EMS Format:**
 * HiGHS internal text format for model serialization:
 * - Compact representation of LP/MIP data
 * - Preserves all model metadata
 * - Used for debugging and testing
 *
 * **FilereaderEms Class:**
 * - readModelFromFile(): Parse EMS file into HighsModel
 * - writeModelToFile(): Export HighsModel to EMS format
 *
 * **Compared to MPS/LP:**
 * - Less standardized but more compact
 * - Primarily for internal use
 * - Full round-trip fidelity with HighsModel
 *
 * @see io/Filereader.h for base class interface
 * @see io/FilereaderMps.h for standard MPS format
 */

#ifndef IO_FILEREADER_EMS_H_
#define IO_FILEREADER_EMS_H_

#include <list>

#include "io/Filereader.h"
#include "io/HighsIO.h"  // For messages.

class FilereaderEms : public Filereader {
 public:
  FilereaderRetcode readModelFromFile(const HighsOptions& options,
                                      const std::string filename,
                                      HighsModel& model);
  HighsStatus writeModelToFile(const HighsOptions& options,
                               const std::string filename,
                               const HighsModel& model);
};

#endif
