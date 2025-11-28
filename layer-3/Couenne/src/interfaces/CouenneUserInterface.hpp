//
// (C) Copyright XXX 2009
// All Rights Reserved.
// This code is published under the Eclipse Public License (EPL).
//
// Authors :
// Pietro Belotti, Lehigh University
// Stefan Vigerske, Humboldt University
//
// Date : 07/18/2009

/**
 * @file CouenneUserInterface.hpp
 * @brief Abstract base class for Couenne user interfaces
 *
 * Defines the interface contract for problem input sources.
 * Concrete implementations read from AMPL, OSInstance, or custom formats.
 *
 * **Required methods (pure virtual):**
 * - getCouenneProblem(): Return symbolic problem representation
 * - getTMINLP(): Return Bonmin TMINLP interface for NLP solves
 *
 * **Optional hooks:**
 * - setupJournals(): Configure output streams (default: stdout)
 * - addBabPlugins(): Add cut generators, heuristics, bound tighteners
 * - writeSolution(): Output final solution
 *
 * **Usage pattern:**
 * ```cpp
 * CouenneAmplInterface interface(options, journalist);
 * CouenneProblem* prob = interface.getCouenneProblem();
 * // ... solve ...
 * interface.writeSolution(bab);
 * ```
 *
 * @see CouenneAmplInterface for AMPL .nl file input
 * @see CouenneOSInterface for Optimization Services input
 */
#ifndef COUENNEUSERINTERFACE_HPP_
#define COUENNEUSERINTERFACE_HPP_

//#include "CouenneConfig.h"
#include "IpOptionsList.hpp"
#include "IpJournalist.hpp"

namespace Bonmin {
class TMINLP;
class Bab;
}

namespace Couenne {

class CouenneProblem;
class CouenneBaB;

/* abstract base class of an interface for Couenne users
 */
class CouenneUserInterface {
protected:
	Ipopt::SmartPtr<Ipopt::OptionsList> options;
	Ipopt::SmartPtr<Ipopt::Journalist>  jnlst;
	
public:
	CouenneUserInterface(Ipopt::SmartPtr<Ipopt::OptionsList> options_, Ipopt::SmartPtr<Ipopt::Journalist> jnlst_)
	: options(options_), jnlst(jnlst_)
	{ }
	
	virtual ~CouenneUserInterface() { }
	
	/** Setup journals for printing.
	 * Default is to have one journal that prints to stdout.
	 */
	virtual bool setupJournals() {
		Ipopt::SmartPtr<Ipopt::Journal> stdout_jrnl = jnlst->AddFileJournal("console", "stdout", Ipopt::J_ITERSUMMARY);
		stdout_jrnl->SetPrintLevel(Ipopt::J_DBG, Ipopt::J_NONE);
		return true;
	}
	
	/** Should return the problem to solve in algebraic form.
	 * NOTE: Couenne is (currently) going to modify this problem!
	 */
	virtual CouenneProblem* getCouenneProblem() = 0;
	
	/** Should return the problem to solve as TMINLP.
	 */
	virtual Ipopt::SmartPtr<Bonmin::TMINLP> getTMINLP() = 0;
	
	/** Called after B&B object is setup.
	 * User should add plugins like cut generators, bound tighteners, or heuristics here.
	 */
  virtual bool addBabPlugins(Bonmin::Bab& bab) {
  	//  CutGenerator1   myCutGenerator   (problem, optionList);
  	//  BoundTightener1 myBoundTightener (problem, optionList);
  	//  Heuristic       myHeuristic      (problem, optionList);

  	//  bab.addCutGenerator   (myCutGenerator);
  	//  bab.addBoundTightener (myBoundTightener);
  	//  bab.addHeuristic      (myHeur1);
  	//  bab.addJournalist     (myJour);
  	return true;
  }

  /** Called after B&B finished. Should write solution information.
   */
	virtual bool writeSolution(Bonmin::Bab& bab) {
		return true;
	}
};

}

#endif /*COUENNEUSERINTERFACE_HPP_*/
