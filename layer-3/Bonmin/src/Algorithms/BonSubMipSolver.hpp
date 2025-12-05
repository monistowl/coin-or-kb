// (C) Copyright International Business Machines (IBM) 2006
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// P. Bonami, International Business Machines
//
// Date :  12/07/2006

/**
 * @file BonSubMipSolver.hpp
 * @brief Unified interface for solving MILP subproblems in OA decomposition
 *
 * Provides a common interface for solving MILP subproblems using either
 * Cbc (via OsiClpSolverInterface) or CPLEX (via OsiCpxSolverInterface).
 * Used by OA decomposition algorithms to solve the linearized master problem.
 *
 * @algorithm MILP Master Problem Solving:
 * Role of master problem in Outer Approximation decomposition.
 *
 * OA CONTEXT:
 *   Original MINLP: min f(x,y) s.t. g(x,y) ≤ 0, y ∈ {0,1}
 *
 *   Master MILP (this solver): min η
 *     s.t. η ≥ f(x^k) + ∇f(x^k)ᵀ(x-x^k)  for k=1..K (linearizations)
 *          0 ≥ g(x^k) + ∇g(x^k)ᵀ(x-x^k)  for k=1..K
 *          y ∈ {0,1}
 *
 *   Master provides: integer solution y* and lower bound
 *   Subproblem uses y* to generate next linearization
 *
 * @algorithm Solve Strategy Selection:
 * Trade-off between solution quality and speed.
 *
 *   FindGoodSolution:
 *     - find_good_sol(): Quick feasibility heuristics
 *     - Used in early OA iterations
 *     - Goal: Get integer point fast for NLP subproblem
 *
 *   GetOptimum:
 *     - optimize(): Full B&B to optimality
 *     - Used when bound quality matters
 *     - Provides valid lower bound for convergence check
 *
 * @algorithm Lazy Constraint Callback (CPLEX):
 * Generate OA cuts on-the-fly during MILP solve.
 *
 *   optimize_with_lazy_constraints():
 *     CPLEX calls back when integer solution found
 *     Check NLP feasibility, add OA cut if violated
 *     More efficient than iterative OA for some problems
 *
 * @complexity MILP solve dominates. Branch-and-cut complexity depends
 * on problem structure. Master grows with accumulated linearizations.
 *
 * @see OaDecompositionBase for OA algorithm using this solver
 * @see OACutGenerator2 for classical OA implementation
 */
// Code separated from BonOaDecBase to try to clarify OAs
#ifndef BonSubMipSolver_HPP
#define BonSubMipSolver_HPP
#include "BonminConfig.h"
#include "IpSmartPtr.hpp"
#include <string>
/* forward declarations.*/
class OsiSolverInterface;
class OsiClpSolverInterface;
class OsiCpxSolverInterface;
class CbcStrategy;
class CbcStrategyDefault;

#include "OsiCuts.hpp"

namespace Bonmin {
    class RegisteredOptions;
    class BabSetupBase; 
    /** A very simple class to provide a common interface for solving MIPs with Cplex and Cbc.*/
    class BONMINLIB_EXPORT SubMipSolver
    {
    public:
      enum MILP_solve_strategy{
         FindGoodSolution,
         GetOptimum};
      /** Constructor */
      SubMipSolver(BabSetupBase &b, const std::string &prefix);

      /** Copy Constructor */
      SubMipSolver(const SubMipSolver &copy);

      ~SubMipSolver();

      /** Assign lp solver. */
      void setLpSolver(OsiSolverInterface * lp);

      /** Assign a strategy. */
      void setStrategy(CbcStrategyDefault * strategy);

      /** get the solution found in last local search (return NULL if no solution). */
      const double * getLastSolution()
      {
        return integerSolution_;
      }

      double getLowerBound()
      {
        return lowBound_;
      }

      void solve(double cutoff,
          int loglevel,
          double maxTime){
         if(milp_strat_ == FindGoodSolution){
            find_good_sol(cutoff, loglevel, maxTime);
         }
         else
            optimize(cutoff, loglevel, maxTime);
      }
 

      /** update cutoff and perform a local search to a good solution. */
      void find_good_sol(double cutoff,
          int loglevel,
          double maxTime);

      /** update cutoff and optimize MIP. */
      void optimize(double cutoff,
          int loglevel,
          double maxTime);

      /** update cutoff, put OA constraints in cs as lazy constraints and optimize MIP. */
      void optimize_with_lazy_constraints(double cutoff,
          int loglevel,
          double maxTime, const OsiCuts & cs);

      /** Returns lower bound. */
      inline double lowBound()
      {
        return lowBound_;
      }

      /** returns optimality status. */
      inline bool optimal()
      {
        return optimal_;
      }

      /** Returns number of nodes in last solve.*/
      inline int nodeCount()
      {
        return nodeCount_;
      }

      /** Returns number of simplex iterations in last solve.*/
      inline int iterationCount()
      {
        return iterationCount_;
      }


      OsiSolverInterface * solver();

     /** Register options for that Oa based cut generation method. */
     static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);
    private:
      /** If lp solver is clp (then have to use Cbc) (not owned).*/
      OsiClpSolverInterface *clp_;
      /** If mip solver is cpx this is it (owned). */
      OsiCpxSolverInterface * cpx_;
      /** lower bound obtained */
      double lowBound_;
      /** Is optimality proven? */
      bool optimal_;
      /** Has an integer solution? then it is here*/
      double * integerSolution_;
      /** Strategy for solving sub mips with cbc. */
      CbcStrategyDefault * strategy_;
      /** number of nodes in last mip solved.*/
      int nodeCount_;
      /** number of simplex iteration in last mip solved.*/
      int iterationCount_;
      /** MILP search strategy.*/
      MILP_solve_strategy milp_strat_;
      /** setting for gap tolerance.*/
      double gap_tol_;
      /** say if owns copy of clp_.*/
      bool ownClp_;
    };

}

#endif

