// (C) Copyright CNRS
// This code is published under the Eclipse Public License.
//
// Authors :
// Pierre Bonami, LIF Université de la Méditérannée-CNRS
//
// Date : 06/18/2008

/**
 * @file BonFixAndSolveHeuristic.hpp
 * @brief Fix-and-Solve heuristic for MINLP
 *
 * Simple heuristic that fixes some integer variables to their current
 * values and solves the resulting smaller MINLP subproblem.
 *
 * **Algorithm:**
 * 1. Select subset of integer variables to fix (based on LP solution)
 * 2. Fix selected variables to their current integer values
 * 3. Solve reduced MINLP with remaining variables
 * 4. If feasible and improved, update incumbent
 *
 * Simpler than RINS (doesn't require incumbent for comparison).
 *
 * @see LocalSolverBasedHeuristic for base class
 * @see HeuristicRINS for more sophisticated fixing strategy
 */
#ifndef BonFixAndSolveHeuristic_H
#define BonFixAndSolveHeuristic_H
#include "BonLocalSolverBasedHeuristic.hpp"

namespace Bonmin {
  class BONMINLIB_EXPORT FixAndSolveHeuristic : public LocalSolverBasedHeuristic {
    public:
     /** Default constructor*/
     FixAndSolveHeuristic();
    /** Constructor with setup.*/
    FixAndSolveHeuristic(BonminSetup * setup);

     /** Copy constructor.*/
     FixAndSolveHeuristic(const FixAndSolveHeuristic &other);
     /** Virtual constructor.*/
     virtual CbcHeuristic * clone() const{
      return new FixAndSolveHeuristic(*this);
     }

     /** Destructor*/
     virtual ~FixAndSolveHeuristic();

     /** Runs heuristic*/
     int solution(double & objectiveValue,
                  double * newSolution);
   /** Register the options common to all local search based heuristics.*/
   static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

   /** Initiaize using passed options.*/
   void Initialize(Ipopt::SmartPtr<Ipopt::OptionsList> options);
  };

}/* Ends Bonmin namepace.*/
#endif

