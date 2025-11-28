/*
  Copyright (C) 2007, Lou Hafer, International Business Machines Corporation
  and others.  All Rights Reserved.

  This code is licensed under the terms of the Eclipse Public License (EPL).

*/

/**
 * @file ClpParamUtils.hpp
 * @brief Parameter handler callback functions for ClpParam
 * @author Lou Hafer
 *
 * Implements the push/pull functions that transfer values between
 * ClpParam objects and ClpSimplex solver state. These callbacks are
 * invoked when parameters are modified via the command-line interface.
 *
 * Action handlers (doXxxParam):
 * - doDebugParam(): Enable debug output
 * - doExitParam(): Terminate solver
 * - doHelpParam(): Display help text
 * - doImportParam(): Read MPS/LP file
 * - doPrintMaskParam(): Set print filter pattern
 * - doSolutionParam(): Write solution file
 * - doVersionParam(): Print version info
 *
 * Push handlers (pushClpXxxParam):
 * Transfer parameter values from ClpParam to ClpSimplex:
 * - pushClpDblParam(): Double parameters
 * - pushClpIntParam(): Integer parameters
 * - pushClpKwdParam(): Keyword (enum) parameters
 * - pushClpStrParam(): String parameters
 * - pushClpBoolParam(): Boolean parameters
 *
 * Solution I/O:
 * - saveSolution()/restoreSolution(): Serialize solution state
 *
 * @see ClpParam for the parameter definition class
 * @see ClpParameters for the parameter container
 */

#ifndef ClpParamUtils_H
#define ClpParamUtils_H

#include "CoinParam.hpp"
#include "ClpSimplex.hpp"

/*
  Declare the utility functions.
*/

namespace ClpParamUtils {
   
int doDebugParam(CoinParam &param);
int doExitParam(CoinParam &param);
int doHelpParam(CoinParam &param);
int doImportParam(CoinParam &param);
int doPrintMaskParam(CoinParam &param);
int doNothingParam(CoinParam &param);
int doSolutionParam(CoinParam &param);
int doUnimplementedParam(CoinParam &param);
int doVersionParam(CoinParam &param);

int pushClpDblParam(CoinParam &param);
int pushClpIntParam(CoinParam &param);
int pushClpKwdParam(CoinParam &param);
int pushClpStrParam(CoinParam &param);
int pushClpBoolParam(CoinParam &param);

CLPLIB_EXPORT
void restoreSolution(ClpSimplex *lpSolver, std::string fileName, int mode);
CLPLIB_EXPORT
void saveSolution(const ClpSimplex *lpSolver, std::string fileName);
   
} // namespace ClpParamUtils

#endif
