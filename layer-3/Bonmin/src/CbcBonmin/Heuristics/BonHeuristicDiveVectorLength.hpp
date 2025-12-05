/**
 * @file BonHeuristicDiveVectorLength.hpp
 * @brief NLP-based diving heuristic selecting by constraint participation
 * Copyright (C) 2007, International Business Machines Corporation and others.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * @algorithm Vector Length Diving Heuristic
 * @math Variable selection combines fractionality and column density:
 *       score(x_j) = min(f_j, 1-f_j) · columnLength_j
 *       where columnLength_j = number of constraints containing x_j.
 *       Selects variable with maximum score (fractional AND high-impact).
 *
 * HeuristicDiveVectorLength: Diving heuristic for MINLP that solves
 * NLP subproblems during diving. Variable selection based on column
 * length (number of constraints containing the variable).
 *
 * **Rationale:** Variables appearing in many constraints have higher
 * impact when fixed. By weighting fractionality by column length,
 * we prioritize fixing variables that propagate more information.
 *
 * **Algorithm:**
 * 1. Precompute columnLength_j for all integer variables
 * 2. For each fractional x_j, compute score = min(f_j, 1-f_j) · columnLength_j
 * 3. Select j* = argmax_j score(x_j)
 * 4. Round towards nearest integer
 *
 * @complexity O(n) per diving step; O(nnz) one-time setup for column lengths
 * @ref Achterberg, T. (2007). "Constraint Integer Programming".
 *      PhD thesis, TU Berlin. Section 7.4.
 *
 * Authors: Joao P. Goncalves, IBM
 * Date: November 12, 2007
 *
 * @see HeuristicDive for base NLP-diving class
 * @see HeuristicDiveMIPVectorLength for MIP-based variant
 */

#ifndef BonHeuristicDiveVectorLength_H
#define BonHeuristicDiveVectorLength_H

#include "BonBonminSetup.hpp"
#include "BonHeuristicDive.hpp"

/** DiveVectorLength class
 */

namespace Bonmin
{
  class BONMINLIB_EXPORT HeuristicDiveVectorLength : public HeuristicDive {
  public:
    /// Default Constructor 
    HeuristicDiveVectorLength ();

    /// Constructor with setup
    HeuristicDiveVectorLength(BonminSetup * setup);

    /// Copy constructor
    HeuristicDiveVectorLength(const HeuristicDiveVectorLength &copy);

    /// Destructor
    ~HeuristicDiveVectorLength() 
    {
      delete [] columnLength_;
    }

    /// Assignment operator
    HeuristicDiveVectorLength & operator=(const HeuristicDiveVectorLength & rhs);

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

  private:
    /// the number of nonzero elements in each column
    int* columnLength_;

  };
}
#endif
