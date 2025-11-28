/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file io/Filereader.h
 * @brief Abstract file reader/writer interface for optimization models
 *
 * Polymorphic I/O with format detection from file extension.
 *
 * **Supported Formats:**
 * - MPS: Mathematical Programming System (fixed/free format)
 * - LP: CPLEX LP format (human-readable)
 * - EMS: HiGHS extended model format
 *
 * **Factory Pattern:**
 * - getFilereader(): Returns appropriate reader for extension
 *   - ".mps", ".mps.gz" → FilereaderMps
 *   - ".lp" → FilereaderLp
 *   - ".ems" → FilereaderEms
 *
 * **Return Codes:**
 * - kOk: Success
 * - kFileNotFound: File doesn't exist
 * - kParserError: Malformed input
 * - kNotImplemented: Format not supported for operation
 * - kTimeout: Read exceeded time limit
 *
 * @see io/FilereaderMps.h for MPS format
 * @see io/FilereaderLp.h for LP format
 * @see io/HMpsFF.h for free-format MPS parser
 */
#ifndef IO_FILEREADER_H_
#define IO_FILEREADER_H_

#include "io/HighsIO.h"
#include "lp_data/HighsOptions.h"
#include "model/HighsModel.h"

enum class FilereaderRetcode {
  kOk = 0,
  kWarning = 1,
  kFileNotFound = 2,
  kParserError = 3,
  kNotImplemented = 4,
  kTimeout
};

void interpretFilereaderRetcode(const HighsLogOptions& log_options,
                                const std::string filename,
                                const FilereaderRetcode code);
std::string extractModelName(const std::string filename);

class Filereader {
 public:
  virtual FilereaderRetcode readModelFromFile(const HighsOptions& options,
                                              const std::string filename,
                                              HighsModel& model) = 0;
  virtual HighsStatus writeModelToFile(const HighsOptions& options,
                                       const std::string filename,
                                       const HighsModel& model) = 0;
  static Filereader* getFilereader(const HighsLogOptions& log_options,
                                   const std::string filename);

  virtual ~Filereader(){};
};
#endif
