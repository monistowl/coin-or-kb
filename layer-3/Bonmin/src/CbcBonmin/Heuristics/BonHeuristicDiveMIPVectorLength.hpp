/**
 * @file BonHeuristicDiveMIPVectorLength.hpp
 * @brief MIP-based diving heuristic selecting by constraint participation
 * Copyright (C) 2007, International Business Machines Corporation and others.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * HeuristicDiveMIPVectorLength: Diving heuristic for MINLP that solves
 * MIP subproblems during diving. Variable selection based on column
 * length (number of constraints containing the variable).
 *
 * Prioritizes high-density columns for faster constraint propagation.
 * Uses columnLength_ array for efficient lookup.
 *
 * Authors: Joao P. Goncalves, IBM
 * Date: November 12, 2007
 *
 * @see HeuristicDiveMIP for base MIP-diving class
 * @see HeuristicDiveVectorLength for NLP-based variant
 */

#ifndef BonHeuristicDiveMIPVectorLength_H
#define BonHeuristicDiveMIPVectorLength_H

#include "BonBonminSetup.hpp"
#include "BonHeuristicDiveMIP.hpp"

/** DiveMIPVectorLength class
 */

namespace Bonmin
{
  class BONMINLIB_EXPORT HeuristicDiveMIPVectorLength : public HeuristicDiveMIP {
  public:
    /// Default Constructor 
    HeuristicDiveMIPVectorLength ();

    /// Constructor with setup
    HeuristicDiveMIPVectorLength(BonminSetup * setup);

    /// Copy constructor
    HeuristicDiveMIPVectorLength(const HeuristicDiveMIPVectorLength &copy);

    /// Destructor
    ~HeuristicDiveMIPVectorLength() 
    {
      delete [] columnLength_;
    }

    /// Assignment operator
    HeuristicDiveMIPVectorLength & operator=(const HeuristicDiveMIPVectorLength & rhs);

    /// Clone
    virtual CbcHeuristic * clone() const;

    /** Change setup used for heuristic.*/
    virtual void setSetup(BonminSetup * setup){
      HeuristicDiveMIP::setSetup(setup);
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
