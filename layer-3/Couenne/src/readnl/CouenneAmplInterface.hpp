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
 * @file CouenneAmplInterface.hpp
 * @brief AMPL .nl file reader for Couenne
 *
 * Reads optimization problems from AMPL Solver Library (ASL)
 * format and converts to Couenne's expression DAG representation.
 *
 * **Key methods:**
 * - getCouenneProblem(): Parse .nl file → CouenneProblem
 * - getTMINLP(): Wrap as Bonmin TMINLP for NLP solves
 * - writeSolution(): Write .sol file back to AMPL
 *
 * **Internal conversion:**
 * - readASLfg(): Read using ASL fg (function/gradient) reader
 * - readnl(): Alternative .nl parsing
 * - nl2e(): Convert ASL expr* to Couenne expression*
 *
 * **ASL integration:**
 * Uses the AMPL Solver Library (ASL) C structures to parse
 * the binary .nl format. The nl2e() method recursively converts
 * ASL expression trees to Couenne expression nodes.
 *
 * @see CouenneUserInterface base class
 * @see CouenneProblem the target representation
 */
#ifndef COUENNEAMPLINTERFACE_HPP_
#define COUENNEAMPLINTERFACE_HPP_

#include "CouenneUserInterface.hpp"
#include "BonRegisteredOptions.hpp"

struct ASL;
struct expr;

namespace Couenne {

class expression;

class CouenneAmplInterface : public CouenneUserInterface {
private:
	CouenneProblem*                  problem;
	Ipopt::SmartPtr<Bonmin::TMINLP>  tminlp;
	
	Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions;
	struct ASL*                      asl;
	
	bool readASLfg();
	bool readnl();
	expression* nl2e(expr *e);
	
public:
	static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);
	
	CouenneAmplInterface(Ipopt::SmartPtr<Ipopt::OptionsList> options_, Ipopt::SmartPtr<Ipopt::Journalist> jnlst_)
	: CouenneUserInterface(options_, jnlst_), problem(NULL), asl(NULL)
	{ }
	
	~CouenneAmplInterface();
	
	CouenneProblem* getCouenneProblem();
	
	Ipopt::SmartPtr<Bonmin::TMINLP> getTMINLP();
	
	bool writeSolution(Bonmin::Bab& bab);
	
	void setRegisteredOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions_)
	{ roptions = roptions_; }
	
};

}

#endif /*COUENNEAMPLINTERFACE_HPP_*/
