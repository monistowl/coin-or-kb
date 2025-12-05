/**
 * @file BonHeuristicDiveMIP.hpp
 * @brief Base class for MIP-based diving heuristics in MINLP
 * Copyright (C) 2007, International Business Machines Corporation and others.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * @algorithm MIP-Guided Diving Heuristic Framework
 * @math Uses MIP subproblem to guide diving in MINLP:
 *       Given MINLP relaxation solution x*, solve MIP:
 *         min ||x - x*||  s.t. Ax ≤ b, x_j ∈ Z (integer vars)
 *       MIP solution suggests which integers to fix and their values.
 *
 * HeuristicDiveMIP: Abstract base class for diving heuristics that solve
 * MIP subproblems during the dive. Unlike pure NLP-based diving, this
 * uses a SubMipSolver (mip_) to handle integer feasibility more robustly.
 *
 * **Key advantage over NLP diving:**
 * - MIP solver handles combinatorial structure better
 * - Can find feasible integer assignments that NLP diving misses
 * - Useful when NLP relaxation is far from integer feasible
 *
 * **Trade-off:** More expensive per iteration (MIP solve vs O(n) selection)
 * but may require fewer total iterations.
 *
 * Derived classes implement:
 * - setInternalVariables(): Setup for variable selection
 * - selectVariableToBranch(): Variable and rounding direction choice
 *
 * @complexity O(MIP) per diving step; MIP complexity depends on formulation
 * @ref Bonami, P. et al. (2008). "An algorithmic framework for convex
 *      mixed integer nonlinear programs". Discrete Optimization 5(2):186-204.
 *
 * Authors: Joao P. Goncalves, IBM
 * Date: November 12, 2007
 *
 * @see HeuristicDiveMIPFractional for fractional selection
 * @see HeuristicDiveMIPVectorLength for column-density selection
 * @see HeuristicDive for NLP-only base class
 */

#ifndef BonHeuristicDiveMIP_HPP
#define BonHeuristicDiveMIP_HPP
#include "BonOsiTMINLPInterface.hpp"
#include "BonBonminSetup.hpp"
#include "CbcHeuristic.hpp"
#include "CbcStrategy.hpp"
namespace Bonmin
{
  class SubMipSolver;
  class BONMINLIB_EXPORT HeuristicDiveMIP : public CbcHeuristic
  {
  public:
#if 0
    /// Default constructor
    HeuristicDiveMIP();
#endif

    /// Constructor with setup
    HeuristicDiveMIP(BonminSetup * setup);

    /// Copy constructor
    HeuristicDiveMIP(const HeuristicDiveMIP &copy);

    /// Destructor
    ~HeuristicDiveMIP();

    /// Assignment operator
    HeuristicDiveMIP & operator=(const HeuristicDiveMIP & rhs);

    /// Clone
    virtual CbcHeuristic * clone() const = 0;

    /// Initialize method 
    void Initialize(BonminSetup * setup);

    /// Resets stuff if model changes
    virtual void resetModel(CbcModel * model){
      setModel(model);
    }

    /** Change setup used for heuristic.*/
    virtual void setSetup(BonminSetup * setup){
      setup_ = setup;
      //      Initialize(setup_->options());
    }

    /// Performs heuristic
    virtual int solution(double &solutionValue, double *betterSolution);

    /// sets internal variables
    virtual void setInternalVariables(TMINLP2TNLP* minlp) = 0;

    /// Selects the next variable to branch on
    /** If bestColumn = -1, it means that no variable was found
    */
    virtual void selectVariableToBranch(TMINLP2TNLP* minlp,
					const vector<int> & integerColumns,
					const double* newSolution,
					int& bestColumn,
					int& bestRound) = 0;

  protected:
    /** Setup to use for local searches (will make copies).*/
    BonminSetup * setup_; 

  private:
    /// How often to do (code can change)
    int howOften_;
    /// A subsolver for MIP
    SubMipSolver * mip_;

  };
}
#endif
