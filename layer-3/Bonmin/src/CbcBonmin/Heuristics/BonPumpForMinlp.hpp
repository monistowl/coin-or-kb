/**
 * @file BonPumpForMinlp.hpp
 * @brief Feasibility Pump heuristic adapted for MINLP
 * Copyright (C) CNRS
 * This code is published under the Eclipse Public License.
 *
 * PumpForMinlp: Feasibility Pump heuristic for nonlinear mixed-integer
 * programming. Extends the MIP Feasibility Pump to handle nonlinear
 * constraints by using NLP subproblem solves.
 *
 * Alternates between:
 * - Rounding current NLP solution to integer
 * - Solving NLP with objective minimizing distance to rounded point
 *
 * Authors: Pierre Bonami, LIF Université de la Méditerranée-CNRS
 * Date: 02/18/2009
 *
 * @see LocalSolverBasedHeuristic for base class
 * @see CbcHeuristicFPump for MIP feasibility pump
 */

#ifndef BonPumpForMinlp_H
#define BonPumpForMinlp_H
#include "BonLocalSolverBasedHeuristic.hpp"

namespace Bonmin {
  class BONMINLIB_EXPORT PumpForMinlp : public LocalSolverBasedHeuristic {
    public:
     /** Default constructor*/
     PumpForMinlp();
    /** Constructor with setup.*/
    PumpForMinlp(BonminSetup * setup);

     /** Copy constructor.*/
     PumpForMinlp(const PumpForMinlp &other);
     /** Virtual constructor.*/
     virtual CbcHeuristic * clone() const{
      return new PumpForMinlp(*this);
     }

     /** Destructor*/
     virtual ~PumpForMinlp();

     /** Runs heuristic*/
     int solution(double & objectiveValue,
                  double * newSolution);
   /** Register the options common to all local search based heuristics.*/
   static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

   /** Setup the defaults.*/
   virtual void setupDefaults(Ipopt::SmartPtr<Ipopt::OptionsList> options);
   /** Initiaize using passed options.*/
   void Initialize(Ipopt::SmartPtr<Ipopt::OptionsList> options);
  };

}/* Ends Bonmin namepace.*/
#endif

