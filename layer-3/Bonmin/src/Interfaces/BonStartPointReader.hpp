/**
 * @file BonStartPointReader.hpp
 * @brief Reader for Ipopt initialization point files
 * Copyright (C) Carnegie Mellon University 2005. All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * StartPointReader: Reads .initP files containing starting point
 * information for Ipopt initialization. File format is: number of
 * primals, number of duals, then values. Variables ordered as:
 * primals, dual lower bounds, dual upper bounds, constraint duals.
 *
 * Authors: Pierre Bonami, Carnegie Mellon University
 * Date: May 26, 2005
 *
 * @see OsiTMINLPInterface for applying the starting point
 */

#ifndef _BONSTARTPOINTREADER_H_
#define _BONSTARTPOINTREADER_H_
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include "BonOsiTMINLPInterface.hpp"



namespace Bonmin {
/** This class reads a file with a starting point for Ipopt initalization. File format is number of primals number of duals then values one after another
 * Numbering of variables is first variables, then duals on lower bounds duals on upper bounds and to finish duals on constraints */
class BONMINLIB_EXPORT StartPointReader
{
public:
  /** Constructor with fileName_ given by a string (and default) */
  StartPointReader(std::string fileName = ""):
      fileName_(fileName),
      primals_(NULL),
      duals_(NULL)
  {}
  /** Constructor with fileName_ given by a const char * */
  StartPointReader(const char * fileName):
      fileName_(fileName),
      primals_(NULL),
      duals_(NULL)
  {}

  /** Reads the .initP file*/
  bool readFile();
  /** Reads the .initP file fileName*/
  bool readFile(const std::string &fileName)
  {
    fileName_=fileName;
    return readFile();
  }
  /** Read warmstart info and apply to an IpoptInterface */
  bool readAndApply(OsiTMINLPInterface * solver);
  ~StartPointReader()
  {
    gutsOfDestructor();
  }


  /// Dealocate arrays
  void gutsOfDestructor()
  {
    if(primals_!=NULL)
      delete[] primals_;
    if(duals_!=NULL)
      delete[] duals_;
  }

  /// Access primal variables values.
  const double * getPrimals()
  {
    return primals_;
  }
  /// Access dual variables values.
  const double * getDuals()
  {
    return duals_;
  }
private:
  /** Name of the file with initial point */
  std::string fileName_;

  /// Primal variables values.
  double * primals_;
  /// Dual variables values.
  double * duals_;
};

}
#endif /*_IPCBCINITPOINTREADER_H_*/
