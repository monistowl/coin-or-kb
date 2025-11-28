/**
 * @file CbcParamUtils.hpp
 * @brief Utility functions for parameter handling in cbc-generic
 * Copyright (C) 2007, Lou Hafer, IBM Corporation and others.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcParamUtils namespace: Callback functions for parameter processing.
 * These are invoked when parameters are set via the command line.
 *
 * Solution I/O:
 * - saveSolution(): Write solution to file
 * - readSolution(): Load solution from file
 *
 * Action handlers (doXxxParam):
 * - doBaCParam(): Execute branch-and-cut solve
 * - doImportParam(): Load problem from file
 * - doSolutionParam(): Write/print solution
 * - doHelpParam(): Display help information
 * - doExitParam(): Exit the program
 *
 * Push functions (pushCbcSolverXxxParam):
 * - Transfer parameter values to solver/model
 * - Separate handlers for Dbl, Int, Kwd, Str, Bool types
 * - Special handlers for Cut and Heur parameters
 *
 * Model parameter handlers:
 * - pushCbcModelDblParam/IntParam(): Set CbcModel parameters
 * - setCbcModelDefaults(): Initialize model with default values
 *
 * @see CbcParam for parameter definitions
 * @see CbcParameters for parameter storage
 */

#ifndef CbcParamUtils_H
#define CbcParamUtils_H

#include "CoinParam.hpp"

#include "OsiSolverInterface.hpp"

namespace CbcParamUtils {

void saveSolution(const OsiSolverInterface *osi, std::string fileName);
bool readSolution(std::string fileName, int &numRows, int &numCols,
                  double &objVal, double **rowActivity, double **dualVars,
                  double **primalVars, double **reducedCosts);

int doBaCParam(CoinParam &param);
int doDebugParam(CoinParam &param);
int doExitParam(CoinParam &param);
int doHelpParam(CoinParam &param);
int doImportParam(CoinParam &param);
int doPrintMaskParam(CoinParam &param);
int doOutputPrecisionParam(CoinParam &param);
int doNothingParam(CoinParam &param);
int doSolutionParam(CoinParam &param);
int doUnimplementedParam(CoinParam &param);
int doVersionParam(CoinParam &param);

int pushCbcSolverDblParam(CoinParam &param);
int pushCbcSolverIntParam(CoinParam &param);
int pushCbcSolverKwdParam(CoinParam &param);
int pushCbcSolverStrParam(CoinParam &param);
int pushCbcSolverBoolParam(CoinParam &param);

int pushCbcSolverHeurParam(CoinParam &param);
int pushCbcSolverCutParam(CoinParam &param);

int pushCbcModelDblParam(CoinParam &param);
int pushCbcModelIntParam(CoinParam &param);

void setCbcModelDefaults(CbcModel *model);

} // namespace CbcParamUtils

#endif
