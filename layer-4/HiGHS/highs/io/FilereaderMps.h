/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file io/FilereaderMps.h
 * @brief MPS format file reader/writer wrapper
 *
 * Implements Filereader interface for MPS format (industry standard).
 *
 * **FilereaderMps Class:**
 * Thin wrapper delegating to HMpsFF (free-format) or HMPSIO (fixed-format):
 * - readModelFromFile(): Detect format, parse MPS into HighsModel
 * - writeModelToFile(): Export HighsModel to MPS format
 *
 * **MPS Format Support:**
 * - Standard sections: ROWS, COLUMNS, RHS, BOUNDS, RANGES
 * - Extensions: OBJSENSE, QSECTION, SOS, integer markers
 * - Both free-format and fixed-format variants
 *
 * **Read Flow:**
 * 1. Attempts free-format parse (HMpsFF)
 * 2. Falls back to fixed-format (HMPSIO) if needed
 * 3. Handles QP and MIP extensions
 *
 * @see io/HMpsFF.h for free-format parser implementation
 * @see io/HMPSIO.h for fixed-format parser implementation
 * @see io/Filereader.h for base class interface
 */
#ifndef IO_FILEREADER_MPS_H_
#define IO_FILEREADER_MPS_H_

#include "io/Filereader.h"
#include "lp_data/HighsStatus.h"

class FilereaderMps : public Filereader {
 public:
  FilereaderRetcode readModelFromFile(const HighsOptions& options,
                                      const std::string filename,
                                      HighsModel& model);
  HighsStatus writeModelToFile(const HighsOptions& options,
                               const std::string filename,
                               const HighsModel& model);
};

#endif
