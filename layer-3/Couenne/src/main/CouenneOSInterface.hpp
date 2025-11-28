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
 * @file CouenneOSInterface.hpp
 * @brief Optimization Services (OS) interface for Couenne
 *
 * Reads optimization problems from OSInstance format (COIN-OR
 * Optimization Services) and converts to Couenne representation.
 *
 * **OSInstance format:**
 * XML-based representation for optimization problems defined by
 * the Optimization Services project. Supports linear, quadratic,
 * and nonlinear constraints with expression trees.
 *
 * **Key methods:**
 * - getCouenneProblem(): Convert OSInstance → CouenneProblem
 * - getTMINLP(): Wrap as Bonmin TMINLP
 * - writeSolution(): Output in OS solution format
 *
 * **Usage:**
 * Alternative to AMPL interface for problems defined via
 * Optimization Services XML or programmatic APIs.
 *
 * @see CouenneUserInterface base class
 * @see CouenneAmplInterface alternative AMPL input
 */
#ifndef COUENNEOSINTERFACE_HPP_
#define COUENNEOSINTERFACE_HPP_

#include "CouenneUserInterface.hpp"
#include "BonRegisteredOptions.hpp"

namespace Bonmin {
  class RegisteredOptions;
  class TMINLP;
  class Bab;
}

namespace Ipopt {
  class OptionsList;
  class Journalist;
}

using Ipopt::SmartPtr;

class OSInstance;

namespace Couenne {

class CouenneOSInterface : public CouenneUserInterface {
private:
	CouenneProblem*                  problem;
	Ipopt::SmartPtr<Bonmin::TMINLP>  tminlp;
	
	OSInstance*                      osinstance;
	
public:
	static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);
	
	CouenneOSInterface(Ipopt::SmartPtr<Ipopt::OptionsList> options_, Ipopt::SmartPtr<Ipopt::Journalist> jnlst_)
	: CouenneUserInterface(options_, jnlst_), problem(NULL), osinstance(NULL)
	{ }
	
	~CouenneOSInterface();
	
	CouenneProblem* getCouenneProblem();
	
	Ipopt::SmartPtr<Bonmin::TMINLP> getTMINLP();
	
	bool writeSolution(Bonmin::Bab& bab);
};

}

#endif
