/**
 * @file BonDummyPump.hpp
 * @brief Placeholder/testing heuristic for feasibility pump
 * Copyright (C) CNRS
 * This code is published under the Eclipse Public License.
 *
 * DummyPump: Simple placeholder heuristic extending LocalSolverBasedHeuristic.
 * Used for testing or as template for new heuristics.
 *
 * Provides minimal implementation of solution() method.
 *
 * Authors: Pierre Bonami, LIF Université de la Méditerranée-CNRS
 * Date: 06/18/2008
 *
 * @see LocalSolverBasedHeuristic for base class
 * @see PumpForMinlp for full feasibility pump implementation
 */

#ifndef BonDummyPump_H
#define BonDummyPump_H
#include "BonLocalSolverBasedHeuristic.hpp"

namespace Bonmin {
  class BONMINLIB_EXPORT DummyPump : public LocalSolverBasedHeuristic {
    public:
     /** Default constructor*/
     DummyPump();
    /** Constructor with setup.*/
    DummyPump(BonminSetup * setup);

     /** Copy constructor.*/
     DummyPump(const DummyPump &other);
     /** Virtual constructor.*/
     virtual CbcHeuristic * clone() const{
      return new DummyPump(*this);
     }

     /** Destructor*/
     virtual ~DummyPump();

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

