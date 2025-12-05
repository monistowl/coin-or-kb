/**
 * @file BonHeuristicDiveFractional.hpp
 * @brief NLP-based diving heuristic selecting most fractional variable
 * Copyright (C) 2007, International Business Machines Corporation and others.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * @algorithm Most Fractional Diving Heuristic
 * @math Variable selection score: s(x_j) = min(f_j, 1-f_j) where f_j = x_j - ⌊x_j⌋
 *       The variable with largest s(x_j) (closest to 0.5) is selected.
 *       Rounding direction: ceil if f_j ≥ 0.5, floor otherwise.
 *
 * HeuristicDiveFractional: Diving heuristic for MINLP that solves
 * NLP subproblems during diving. Variable selection based on
 * fractionality - picks integer variable closest to 0.5.
 *
 * **Algorithm:**
 * 1. Compute fractional part f_j = x_j - ⌊x_j⌋ for each integer variable
 * 2. Select j* = argmax_j min(f_j, 1-f_j)
 * 3. Round towards nearest integer (ceil if f_j ≥ 0.5)
 * 4. Fix variable and resolve NLP
 *
 * @complexity O(n) per diving step for variable selection
 * @ref Berthold, T. (2006). "Primal Heuristics for Mixed Integer Programs".
 *      Diploma thesis, TU Berlin.
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
