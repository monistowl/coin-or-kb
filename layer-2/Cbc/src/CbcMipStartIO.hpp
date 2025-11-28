/**
 * @file CbcMipStartIO.hpp
 * @brief Read MIP starting solutions from files
 *
 * CbcMipStartIO: Utilities for reading partial or complete MIP solutions.
 * Warm-starting B&C with a known solution can dramatically speed up solving.
 *
 * read(): Parses solution file in format: varname value
 * - Returns 0 on success, 1 on failure
 * - Fills colValues with (name, value) pairs
 * - Reports objective value if available
 *
 * computeCompleteSolution(): Extends partial solution to all variables.
 * - extraActions controls how unmentioned integers are set:
 *   - 0: Default handling
 *   - 1: Set to lower bound
 *   - 2: Set to upper bound
 *   - 3,5: Without costs as 1,2; with costs to cheapest
 *   - 4,6: Without costs as 1,2; with costs to expensive
 *
 * Use case: Providing initial solutions from heuristics, previous runs,
 * or domain knowledge to accelerate MIP solving.
 *
 * @see CbcModel::setBestSolution for using solutions
 * @see CbcHeuristic for algorithmic solution generation
 */

#ifndef MIPSTARTIO_HPP_INCLUDED
#define MIPSTARTIO_HPP_INCLUDED

#include <vector>
#include <string>
#include <utility>

#include "CbcConfig.h"

class CbcModel;
class OsiSolverInterface;
class CoinMessageHandler;
class CoinMessages;

class CBCLIB_EXPORT CbcMipStartIO{
public:  
/* tries to read mipstart (solution file) from
   fileName, filling colValues and obj
   returns 0 with success,
   1 otherwise */
static int read(OsiSolverInterface *solver, const char *fileName,
  std::vector< std::pair< std::string, double > > &colValues,
  double &solObj, CoinMessageHandler *messHandler, CoinMessages *pcoinmsgs);

/* from a partial list of variables tries to fill the
   remaining variable values.
   extraActions 0 -default, otherwise set integers not mentioned
   1 - to lower bound, 2 - to upper bound
   3,5 ones without costs as 1,2 - ones with costs to cheapest
   4,6 ones without costs as 1,2 - ones with costs to expensive
*/
static int computeCompleteSolution(CbcModel *model, OsiSolverInterface *solver,
  const std::vector< std::string > colNames,
  const std::vector< std::pair< std::string, double > > &colValues,
  double *sol, double &obj, int extraActions, CoinMessageHandler *messHandler, CoinMessages *pmessages);
  
};


#endif // MIPSTARTIO_HPP_INCLUDED

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
