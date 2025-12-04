/**
 * @file BonDummyHeuristic.hpp
 * @brief Simple placeholder heuristic wrapping NLP solver
 * Copyright (C) Carnegie Mellon University 2005. All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * DummyHeuristic: Minimal heuristic that calls NLP solver to provide
 * solutions. Used for testing or as template for new heuristics.
 * Always reports ready to run (shouldHeurRun returns true).
 *
 * Authors: Pierre Bonami, Carnegie Mellon University
 * Date: May 26, 2005
 *
 * @see CbcHeuristic for base heuristic interface
 * @see OsiTMINLPInterface for NLP solver interface
 */

#ifndef BonDummyHeuristic_HPP
#define BonDummyHeuristic_HPP
#include "BonOsiTMINLPInterface.hpp"

#include "CbcHeuristic.hpp"
namespace Bonmin
{
  class BONMINLIB_EXPORT DummyHeuristic : public CbcHeuristic
  {
  public:
    /// Default constructor
    DummyHeuristic(OsiTMINLPInterface * si = NULL);
    /// Usefull constructor
    DummyHeuristic(CbcModel &model, OsiTMINLPInterface * si = NULL);
    ///Copy constructor
    DummyHeuristic( const DummyHeuristic &copy):
        CbcHeuristic(copy),
        nlp_(copy.nlp_),
        knowsSolution(copy.knowsSolution)
    {}
    /// Set nlp_
    void setNlp(OsiTMINLPInterface * si);
    /// heuristic method
    virtual int solution(double &solutionValue, double *betterSolution);
    virtual int solution(double &solutionValue, double *betterSolution, OsiCuts & cs)
    {
      return solution(solutionValue, betterSolution);
    }
    virtual CbcHeuristic * clone()const
    {
      return new DummyHeuristic(*this);
    }
    virtual void resetModel(CbcModel*)
    {}
  virtual bool shouldHeurRun(int whereFrom){
     return true;}
  private:
    /// Pointer to the Ipopt interface
    OsiTMINLPInterface * nlp_;
    /// Do I have a solution?
    bool knowsSolution;
  };
}
#endif
