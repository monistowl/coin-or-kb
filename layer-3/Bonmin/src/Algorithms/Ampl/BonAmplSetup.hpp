// (C) Copyright International Business Machines Corporation 2007
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// Pierre Bonami, International Business Machines Corporation
//
// Date : 04/15/2007

/**
 * @file BonAmplSetup.hpp
 * @brief AMPL-specific Bonmin setup and initialization
 *
 * Extends BonminSetup to initialize from AMPL command-line arguments
 * and .nl files. Handles reading options and model from AMPL.
 *
 * **Initialization methods:**
 * - initialize(argv): Read from command line and files
 * - initialize(argv, opt_content, nl_content): Read from strings (for Bcp)
 * - fillOsiInterface(): Initialize existing interface from strings
 *
 * @see BonminSetup for algorithm configuration
 * @see AmplInterface for the solver interface
 */
#ifndef BonAmplSetup_H
#define BonAmplSetup_H
#include "BonBonminSetup.hpp"
#include "BonAmplInterface.hpp"

namespace Bonmin
{
  class BONMINAMPLINTERFACELIB_EXPORT BonminAmplSetup: public BonminSetup
  {
  public:
    /** initialize bonmin with ampl model using the command line arguments.*/
    void initialize(char **& argv);
    /** initialize bonmin with ampl model using the command line arguments and an existing OsiTMINLPInterface.*/
    void initialize(AmplInterface &toFill, char **& argv);
    /** initialize bonmin with ampl model using the command line arguments reading options and nl file from strings.*/
    void initialize(char **& argv, std::string& opt_file_content, std::string& nl_file_content, bool createContinuousSolver /*= false*/);
    /** initialize bonmin with ampl model using the command line arguments and an existing OsiTMINLPInterface reading options and nl file from strings.*/
    void initialize(AmplInterface &toFill, char **& argv, std::string& opt_file_content, std::string& nl_file_content, bool createContinuousSolver = true);
    /** For Bcp. Initialize the passed OsiTMINLP interface with ampl model using the options and nl files contained in two strings.*/
    void fillOsiInterface(AmplInterface &toFill, char **& argv, std::string & options, std::string & nl, bool createContinuousSolver = true);
  };
}
#endif
