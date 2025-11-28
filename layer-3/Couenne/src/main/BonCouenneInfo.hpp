/* */
// (C) Copyright International Business Machines Corporation 2008
// All Rights Reserved.
// This code is published under the Eclipse Public License (EPL).
//
// Authors :
// Andreas Waechter, International Business Machines Corporation
//
// Date : 02/10/2008

/**
 * @file BonCouenneInfo.hpp
 * @brief Information passing between B&B components
 *
 * Extends Bonmin's BabInfo with Couenne-specific information,
 * particularly storage of NLP solutions found during search.
 *
 * **NlpSolution class:**
 * Reference-counted storage for NLP solutions:
 * - n_: Number of variables
 * - sol_[]: Variable values
 * - objVal_: Objective function value
 *
 * **CouenneInfo:**
 * - nlpSols_: List of all NLP solutions found
 * - addSolution(): Record a new NLP solution
 * - NlpSolutions(): Access stored solutions
 *
 * **Usage:**
 * When Couenne finds feasible NLP solutions (from heuristics
 * or at B&B nodes), they are stored here for incumbent tracking
 * and warm-starting purposes.
 *
 * @see Bonmin::BabInfo base class
 * @see CouenneFeasPump which generates NLP solutions
 */
#ifndef BonCouenneInfos_H
#define BonCouenneInfos_H

#include "BonBabInfos.hpp"
#include "BonCbc.hpp"
#include "IpSmartPtr.hpp"
#include "CouenneConfig.h"

#include <list>

namespace Couenne {

  /** Bonmin class for passing info between components of branch-and-cuts.*/
  class COUENNELIB_EXPORT CouenneInfo : public Bonmin::BabInfo
  {
  public:
    /** Class for storing an Nlp Solution */
    class COUENNELIB_EXPORT NlpSolution: public Ipopt::ReferencedObject
    {
    public:
      // meaningful constructor
      NlpSolution(int n, const double* sol, double objval);

      // destructor
      ~NlpSolution();

      /** @name Accessor methods */
      //@{
      const double* solution() const
      {
	return sol_;
      }
      double objVal() const
      {
	return objVal_;
      }
      int nVars() const
      {
	return n_;
      }
      //@}

    private:
      //@{
      NlpSolution();
      NlpSolution(const NlpSolution&);
      void operator=(const NlpSolution&);
      //@}
      /** number of variables */
      int n_;
      /** values of the stored solution */
      double* sol_;
      /** objective function of stored solution */
      double objVal_;
    };

    /** Default constructor.*/
    CouenneInfo(int type);

    /** Constructor from OsiBabSolver.*/
    CouenneInfo(const OsiBabSolver &other);

    /** Copy constructor.*/
    CouenneInfo(const CouenneInfo &other);

    /** Destructor.*/
    virtual ~CouenneInfo();

    /** Virtual copy constructor.*/
    virtual OsiAuxInfo * clone() const;

    /** List of all stored NLP solutions */
    const std::list<Ipopt::SmartPtr<const NlpSolution> >& NlpSolutions() const {
      return nlpSols_;
    }

    /** Add a new NLP solution */
    void addSolution(Ipopt::SmartPtr<const NlpSolution> newSol)
    {
      nlpSols_.push_back(newSol);
    }

    protected:
    std::list<Ipopt::SmartPtr<const NlpSolution> > nlpSols_;
  };
}

#endif
