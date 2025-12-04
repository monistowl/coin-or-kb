/**
 * @file BonHeuristicDiveFractional.hpp
 * @brief NLP-based diving heuristic selecting most fractional variable
 * Copyright (C) 2007, International Business Machines Corporation and others.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * HeuristicDiveFractional: Diving heuristic for MINLP that solves
 * NLP subproblems during diving. Variable selection based on
 * fractionality - picks integer variable closest to 0.5.
 *
 * Extends HeuristicDive with most-fractional variable selection.
 * Simpler than MIP variant but may require more NLP solves.
 *
 * Authors: Joao P. Goncalves, IBM
 * Date: November 12, 2007
 *
 * @see HeuristicDive for base NLP-diving class
 * @see HeuristicDiveMIPFractional for MIP-based variant
 */

#ifndef BonHeuristicDiveFractional_H
#define BonHeuristicDiveFractional_H

#include "BonBonminSetup.hpp"
#include "BonHeuristicDive.hpp"

/** DiveFractional class
 */

namespace Bonmin
{
  class BONMINLIB_EXPORT HeuristicDiveFractional : public HeuristicDive {
  public:
    /// Default Constructor 
    HeuristicDiveFractional ();

    /// Constructor with setup
    HeuristicDiveFractional(BonminSetup * setup);

    /// Copy constructor
    HeuristicDiveFractional(const HeuristicDiveFractional &copy);

    /// Destructor
    ~HeuristicDiveFractional() {}

    /// Assignment operator
    HeuristicDiveFractional & operator=(const HeuristicDiveFractional & rhs);

    /// Clone
    virtual CbcHeuristic * clone() const;

    /** Change setup used for heuristic.*/
    virtual void setSetup(BonminSetup * setup){
      HeuristicDive::setSetup(setup);
      Initialize(setup->options());
    }

    /// sets internal variables
    virtual void setInternalVariables(TMINLP2TNLP* minlp);

    /// Selects the next variable to branch on
    /** If bestColumn = -1, it means that no variable was found
    */
    virtual void selectVariableToBranch(TMINLP2TNLP* minlp,
					const vector<int> & integerColumns,
					const double* newSolution,
					int& bestColumn,
					int& bestRound);

    /** Register the options common to all local search based heuristics.*/
    static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);
    
    /** Initiaize using passed options.*/
    void Initialize(Ipopt::SmartPtr<Ipopt::OptionsList> options);

  };
}
#endif
