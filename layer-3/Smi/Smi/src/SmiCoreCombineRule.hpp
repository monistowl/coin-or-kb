// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
//
// SmiCoreCombineRule.hpp: interface for the SmiCoreCombineRule classes.
//
//
// Alan King
// 9 March 2004
//////////////////////////////////////////////////////////////////////

/**
 * @file SmiCoreCombineRule.hpp
 * @brief Rules for combining core and stochastic data in SMPS
 *
 * In SMPS, stochastic data is a "diff" from the core problem. This file
 * defines how to apply that diff (combine core + stochastic → scenario).
 *
 * **SmiCoreCombineRule (Abstract Base):**
 * Virtual interface for combination rules:
 * - Process(d1, offset, cpv): Modify dense array d1 using sparse cpv
 * - Process(cpv1, cpv2): Combine two sparse vectors
 *
 * **SmiCoreCombineReplace (Singleton):**
 * Default SMPS rule - stochastic values REPLACE core values:
 * - scenario[i] = stochastic[i] if defined, else core[i]
 * - Use case: Changing a coefficient value entirely
 *
 * **SmiCoreCombineAdd (Singleton):**
 * Alternative rule - stochastic values ADD to core values:
 * - scenario[i] = core[i] + stochastic[i]
 * - Use case: Perturbations, additive uncertainty
 *
 * **Singleton Pattern:**
 * Both concrete rules use singleton pattern for efficiency:
 * - SmiCoreCombineReplace::Instance()
 * - SmiCoreCombineAdd::Instance()
 *
 * **Usage:**
 * Rules are passed to generateScenario() or readSmps() to control
 * how scenario data is constructed from core + stochastic inputs.
 *
 * @see SmiScnModel.hpp::generateScenario() for usage
 * @see SmiSmpsIO.hpp::readStochFile() for SMPS parsing
 * @see SmiScnData.hpp::SmiNodeData for node-level application
 */

#if !defined(SmiCoreCombineRule_HPP)
#define SmiCoreCombineRule_HPP

#include "CoinPragma.hpp"
#include "CoinPackedVector.hpp"

/** This deals with combining Core and Stochastic data.

	In the Stochastic MPS standard, stochastic data updates
	the underlying core lp data.  To specify a new scenario,
	one only has to identify those data that are different.
	So, in a sense, the stochastic data is really a "diff" between
	the scenario and the core data. This class specifies how
	to perform the "undiff", that is, how to combine core
	and stochastic data.

	And of course, a complete implementation specifies the
	"diff" part as well.  Now during a fit of original confusion
	in the birth of the SMPS standard, we decided to make
	default combine rule "replace", which has a rather special
	"diff", but we've learned to live with it.

	There only needs to be one of these classes. so they're
	singletons.
	*/
class SmiCoreCombineRule
{
public:
  /**@name Virtual Functions: Process and Diff */
  //@{
  /// Process
	virtual void Process(double *d1, int o1, const CoinPackedVector &cpv2, char *type=0)=0;
	virtual void Process(double *d1, int o1, const int len, const int* inds, const double *dels, char *type=0)=0;
	virtual CoinPackedVector * Process(CoinPackedVector *cpv1, CoinPackedVector *cpv2, char *type=0)=0;
	virtual int Process(double *dr,const int dr_len,CoinPackedVector *cpv,double *dels,int *indx)=0;
	virtual int Process(double *dr,const int dr_len,const int cpv_nels,const int* cpv_ind,const double *cpv_els,double *dels,int *indx)=0;
	virtual ~SmiCoreCombineRule(){}
};

//////////////////////////////////////////////////////////////////////
// SmiCoreCombineReplace
// -- concrete "replace" rule -- singleton pattern
//////////////////////////////////////////////////////////////////////
class SmiCoreCombineReplace : public SmiCoreCombineRule
{
public:
	static SmiCoreCombineReplace * Instance();
	static void ClearInstance();
	//Replace values in d1 with values from cpv2, where o1 is the offset to apply to d1
	virtual void Process(double *d1, int o1, const CoinPackedVector &cpv2, char *type=0);
	virtual void Process(double *d1, int o1, const int len, const int* inds, const double *dels, char *type=0);
	virtual CoinPackedVector * Process(CoinPackedVector *cpv1, CoinPackedVector *cpv2, char *type=0);
	virtual int Process(double *dr,const int dr_len,CoinPackedVector *cpv,double *dels,int *indx);
	virtual int Process(double *dr,const int dr_len,const int nels, const int* cpv_ind,const double *cpv_els,double *dels,int *indx);
protected:
	SmiCoreCombineReplace(){}
private:
	static SmiCoreCombineReplace * _instance;
};

//////////////////////////////////////////////////////////////////////
// SmiCoreCombineAdd
// -- concrete "add" rule -- singleton pattern
//////////////////////////////////////////////////////////////////////
class SmiCoreCombineAdd : public SmiCoreCombineRule
{
public:
	static SmiCoreCombineAdd * Instance();
	static void ClearInstance();
	virtual void Process(double *d1, int o1, const CoinPackedVector &cpv2, char* type=0);
	virtual void Process(double *d1, int o1, const int len, const int* inds, const double *dels, char *type=0);
	virtual CoinPackedVector * Process(CoinPackedVector *cpv1, CoinPackedVector *cpv2, char* type=0);
	virtual int Process(double *dr,const int dr_len,CoinPackedVector *cpv,double *dels,int *indx);
	virtual int Process(double *dr,const int dr_len,const int nels, const int* cpv_ind,const double *cpv_els,double *dels,int *indx);
protected:
	SmiCoreCombineAdd(){}
private:
	static SmiCoreCombineAdd * _instance;
};


#endif // !defined(SmiCoreCombineRule_HPP)
