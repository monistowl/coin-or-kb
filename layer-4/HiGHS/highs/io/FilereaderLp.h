/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file io/FilereaderLp.h
 * @brief CPLEX LP format file reader/writer
 *
 * Implements Filereader interface for LP format (human-readable).
 *
 * **LP Format:**
 * CPLEX-style format with sections:
 * - Minimize/Maximize: Objective function
 * - Subject To: Linear constraints
 * - Bounds: Variable bounds
 * - General/Binary: Integer/binary declarations
 * - End: File terminator
 *
 * **FilereaderLp Class:**
 * - readModelFromFile(): Parse LP file into HighsModel
 * - writeModelToFile(): Export HighsModel to LP format
 *
 * **Writing Utilities:**
 * - writeToFile(): Buffered output with line-length management
 * - writeToFileValue(): Format numeric coefficients
 * - writeToFileVar(): Output variable names (quotes if needed)
 * - writeToFileMatrixRow(): Output constraint row
 *
 * **Constants:**
 * - LP_MAX_LINE_LENGTH (560): Maximum line length
 * - LP_MAX_NAME_LENGTH (255): Maximum identifier length
 *
 * @see io/Filereader.h for base class interface
 * @see io/HMpsFF.h for MPS format alternative
 */

#ifndef IO_FILEREADER_LP_H_
#define IO_FILEREADER_LP_H_

#include <list>

#include "io/Filereader.h"
#include "io/HighsIO.h"

#define BUFFERSIZE 561
#define LP_MAX_LINE_LENGTH 560
#define LP_MAX_NAME_LENGTH 255

#define LP_COMMENT_FILESTART ("File written by HiGHS .lp file handler")

class FilereaderLp : public Filereader {
 public:
  FilereaderRetcode readModelFromFile(const HighsOptions& options,
                                      const std::string filename,
                                      HighsModel& model);

  HighsStatus writeModelToFile(const HighsOptions& options,
                               const std::string filename,
                               const HighsModel& model);

 private:
  // functions to write files
  HighsInt linelength;
  void writeToFile(FILE* file, const char* format, ...);
  void writeToFileLineEnd(FILE* file);
  void writeToFileValue(FILE* file, const double value,
                        const bool force_plus = true);
  void writeToFileVar(FILE* file, const std::string var_name);
  void writeToFileMatrixRow(FILE* file, const HighsInt iRow,
                            const HighsSparseMatrix ar_matrix,
                            const std::vector<string> col_names);
};

#endif
