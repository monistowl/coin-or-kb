/**
 * @file BonGuessHeuristic.hpp
 * @brief Pseudocost-based initial guess heuristic for MINLP
 * Copyright (C) International Business Machines 2007. All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * GuessHeuristic: Generates initial feasible solution guesses based on
 * pseudocost information. Used early in the branch-and-bound process
 * to provide good starting points.
 *
 * Authors: Andreas Waechter, IBM
 * Date: September 1, 2007
 *
 * @see CbcHeuristic for base heuristic interface
 */

#ifndef BonGuessHeuristic_HPP
#define BonGuessHeuristic_HPP
#include "BonOsiTMINLPInterface.hpp"

#include "CbcHeuristic.hpp"

namespace Bonmin
{
  class BONMINLIB_EXPORT GuessHeuristic : public CbcHeuristic
  {
  public:
    /// Usefull constructor
    GuessHeuristic(CbcModel &model);
    ///Copy constructor
    GuessHeuristic( const GuessHeuristic &copy):
        CbcHeuristic(copy)
    {}

    /// heuristic method providing guess, based on pseudo costs
    virtual int solution(double &solutionValue, double *betterSolution);
    virtual int solution(double &solutionValue, double *betterSolution, OsiCuts & cs)
    {
      return solution(solutionValue, betterSolution);
    }
    virtual CbcHeuristic * clone()const
    {
      return new GuessHeuristic(*this);
    }
    virtual void resetModel(CbcModel*)
    {}
  private:
    /// Default constructor
    GuessHeuristic();

    /// Assignment operator
    GuessHeuristic & operator=(const GuessHeuristic& rhs);
  };
}
#endif
