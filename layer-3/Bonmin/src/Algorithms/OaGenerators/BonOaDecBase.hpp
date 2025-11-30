// (C) Copyright International Business Machines (IBM) 2006
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// P. Bonami, International Business Machines
//
// Date :  12/07/2006

/**
 * @file BonOaDecBase.hpp
 * @brief Base class for Outer Approximation (OA) decomposition algorithms
 *
 * Implements the foundation for OA-based MINLP algorithms. OA iterates between
 * solving MILP subproblems and NLP subproblems, generating linear outer
 * approximations of the nonlinear constraints.
 *
 * **OA algorithm outline:**
 * 1. Solve MILP relaxation → get integer solution x*
 * 2. Fix integers to x*, solve NLP → get nonlinear solution y*
 * 3. Generate linearization cuts at y* (gradient-based)
 * 4. Add cuts to MILP, repeat until convergence
 *
 * **Key components:**
 * - solverManip: RAII helper to save/restore solver state
 * - performOa(): Virtual method implementing specific OA variant
 * - post_nlp_solve(): Handle NLP solution and update bounds
 *
 * **Parameters:**
 * - global_: Add cuts globally (valid at all nodes)
 * - addOnlyViolated_: Only add cuts violated by current solution
 * - maxLocalSearch_: Limit on local search iterations
 *
 * @algorithm Outer Approximation (OA) Decomposition:
 * Benders-style decomposition for convex MINLP. Master problem is MILP
 * containing linearizations of nonlinear constraints. Subproblem is NLP
 * with integers fixed. Iterate until master and sub agree.
 *
 * Key insight: For convex MINLP, linearization at any feasible point
 * provides valid outer approximation. Accumulating cuts from multiple
 * NLP solves progressively tightens the MILP approximation.
 *
 * @math Given convex MINLP: min f(x,y) s.t. g(x,y) ≤ 0, y ∈ {0,1}
 *
 * OA Master (MILP): min η s.t. η ≥ f(x^k) + ∇f(x^k)ᵀ(x-x^k) ∀k
 *                            0 ≥ g(x^k) + ∇g(x^k)ᵀ(x-x^k) ∀k
 *
 * NLP Sub (y=y*): min f(x,y*) s.t. g(x,y*) ≤ 0
 *
 * Convergence: For convex problems, finite ε-convergence. Each NLP solve
 * either provides improving incumbent or cut proving master solution
 * infeasible. MILP bound increases monotonically.
 *
 * @complexity #iterations typically small (tens to hundreds).
 * Per iteration: O(MILP) + O(NLP). MILP grows with accumulated cuts.
 * Total: problem-dependent, but often beats pure B&B for structured problems.
 *
 * @ref Duran & Grossmann (1986). "An outer-approximation algorithm for
 *   a class of mixed-integer nonlinear programs". Math. Prog. 36:307-339.
 * @ref Fletcher & Leyffer (1994). "Solving mixed integer nonlinear programs
 *   by outer approximation". Math. Prog. 66:327-349.
 * @ref Quesada & Grossmann (1992). "An LP/NLP based branch and bound
 *   algorithm for convex MINLP". Comp. & Chem. Eng. 16:937-947.
 *
 * @see OACutGenerator2 for classical OA implementation
 * @see BonOaNlpOptim for NLP-based OA variant
 * @see CglCutGenerator for the cut generator interface
 */
#ifndef BonOaDecBase_HPP
#define BonOaDecBase_HPP
#include "BonSubMipSolver.hpp"
#include "CglCutGenerator.hpp"
#include "BonBabSetupBase.hpp"
#include "BonOAMessages.hpp"
#include "CbcModel.hpp"

#include "CbcStrategy.hpp"

#include "CoinTime.hpp"
#include "OsiAuxInfo.hpp"
#include "OsiBranchingObject.hpp"
#include <iostream>
#include "BonBabInfos.hpp"
namespace Bonmin
{
  /** Base class for OA algorithms.*/
  class BONMINLIB_EXPORT OaDecompositionBase : public CglCutGenerator
  {
  public:


    /** Small class to manipulatee various things in an OsiSolverInterface and restore them.
        The OsiSolverInterface manipulated may already exist or may be cloned from another one.*/
    class solverManip
    {
    public:
      /** Constructor. */
      solverManip(OsiSolverInterface *si , bool saveNumRows=true,
          bool saveBasis=true, bool saveBounds=false,
          bool saveCutoff = false, bool resolve=true);

      /** Constructor which clone an other interface. */
      solverManip(const OsiSolverInterface & si);
      /** Destructor. */
      ~solverManip();
      /** Restore solver. */
      void restore();
      
      /** Get pointer to solver interface. */
      OsiSolverInterface * si()
      {
        return si_;
      }

      /** Set objects.*/
      void setObjects(OsiObject ** objects, int nObjects)
      {
        objects_ = objects;
        nObjects_ = nObjects;
      }

    private:
      /** Interface saved. */
      OsiSolverInterface * si_;
      /** Initial number of rows (-1 if don't save). */
      int initialNumberRows_;

      /** Initial lower bounds. */
      double * colLower_;

      /** Initial Upper bounds.*/
      double * colUpper_;

      /** Inital basis. */
      CoinWarmStart * warm_;

      /** Initial cutoff. */
      double cutoff_;

      /** delete si_ ? */
      bool deleteSolver_;

      /// Some objects the feasiblitiy of which to verify.
      OsiObject * * objects_;
      /// Number of objects.*/
      int nObjects_;
      /** \name Cached info from solver interface.*/
      /** @{ */
      /** Number of columns. */
      int numcols_;
      /** Number of rows. */
      int numrows_;
      /** Lower bounds on variables.*/
      const double * siColLower_;
      /** Upper bounds on variables. */
      const double * siColUpper_;

      void getCached();
      /** @} */
    };

    /// New usefull constructor
    OaDecompositionBase(BabSetupBase &b, bool leaveSiUnchanged,
        bool reassignLpsolver);

    /// Copy constructor
    OaDecompositionBase(const OaDecompositionBase & copy);


    /// Destructor
    virtual ~OaDecompositionBase();

    /** Standard cut generation methods. */
    virtual void generateCuts(const OsiSolverInterface &si,  OsiCuts & cs,
        const CglTreeInfo info = CglTreeInfo());

    /// Assign an OsiTMINLPInterface
    void assignNlpInterface(OsiTMINLPInterface * nlp)
    {
      nlp_ = nlp;
    }

    /// Assign an OsiTMINLPInterface
    void assignLpInterface(OsiSolverInterface * si)
    {
      lp_ = si;
    }

    bool reassignLpsolver()
    {
      return reassignLpsolver_;
    }
    /** Set objects.*/
    void setObjects(OsiObject ** objects, int nObjects)
    {
      objects_ = objects;
      nObjects_ = nObjects;
    }
    /// Set whether to leave the solverinterface unchanged
    inline void setLeaveSiUnchanged(bool yesno)
    {
      leaveSiUnchanged_ = yesno;
    }

    /** Parameters for algorithm. */
    struct Parameters
    {
      /// Add cuts as global
      bool global_;
      /// Add only violated OA inequalities
      bool addOnlyViolated_;
      /// cutoff min increase (has to be intialized trhough Cbc)
      double cbcCutoffIncrement_;
      /// integer tolerance (has to be the same as Cbc's)
      double cbcIntegerTolerance_; 
      /** setting for gap tolerance.*/
      double gap_tol_;
      ///Total max number of local searches
      int maxLocalSearch_;
      /// maximum time for local searches
      double maxLocalSearchTime_;
      /** sub milp log level.*/
      int subMilpLogLevel_;
      /** maximum number of solutions*/
      int maxSols_;
      /** Frequency of log. */
      double logFrequency_;
     
      
      /** Constructor with default values */
      Parameters();

      /** Copy constructor */
      Parameters(const Parameters & other);

      /** Destructor */
      ~Parameters()
      {
        if (strategy_) delete strategy_;
      }

      /** Strategy to apply when using Cbc as MILP sub-solver.*/
      void setStrategy(const CbcStrategy & strategy)
      {
        if (strategy_) delete strategy_;
        strategy_ = strategy.clone();
      }

      const CbcStrategy * strategy() const
      {
        return strategy_;
      }

private:
      /** Strategy to apply when using Cbc as MILP sub-solver.*/
      CbcStrategy * strategy_;

    };

    Parameters& parameter()
    {
      return parameters_;
    }

    const Parameters& parameter()const
    {
      return parameters_;
    }

    void setLogLevel(int level)
    {
      handler_->setLogLevel(level);
    }

    void setReassignLpSolver(bool v){
      reassignLpsolver_ = v;
    }
    void passInMessageHandler(CoinMessageHandler * handler);
  protected:
      void setupMipSolver(BabSetupBase &b, const std::string &prefix);
    /// \name Protected helper functions
    /**@{ */

    /** Solve the nlp and do output.
        \return true if feasible*/
    bool post_nlp_solve(BabInfo * babInfo, double cutoff) const;
    /** @} */

    /// virtual method which performs the OA algorithm by modifying lp and nlp.
    virtual double performOa(OsiCuts &cs, solverManip &lpManip,
                             BabInfo * babInfo, double &, const CglTreeInfo & info) const = 0;
    /// virutal method to decide if local search is performed
    virtual bool doLocalSearch(BabInfo * babInfo) const = 0;

    /// \name Protected members
    /** @{ */
    /// Pointer to nlp interface
    mutable OsiTMINLPInterface * nlp_;
    /// Pointer to setup
    BabSetupBase * s_;
    ///Number of nlp solved done
    mutable int nSolve_;
    /// A linear solver
    mutable OsiSolverInterface * lp_;
    /// Some objects the feasiblitiy of which to verify.
    OsiObject * * objects_;
    /// Number of objects.*/
    int nObjects_;
    ///number of local searches performed
    mutable int nLocalSearch_;
    /** messages handler. */
    CoinMessageHandler * handler_;
    /** Messages for OA */
    CoinMessages messages_;
    /** Wether or not we should remove cuts at the end of the procedure */
    bool leaveSiUnchanged_;
    /** Do we need to reassign the lp solver with Cbc.*/
    bool reassignLpsolver_;
    /** time of construction*/
    double timeBegin_;
    /** number of solutions found by OA_decomposition.*/
    mutable int numSols_;
    
    /** Parameters.*/
    Parameters parameters_;

      /** Saved cuts: in some cases when using OA to check feasible solution algorithm may loop because Cbc removes inactive cuts.
          To overcome this we can impose that no OA cut can be discarded by Cbc but this consumes too much memory in some cases.
          Here we do it another way: cuts generated at current node are saved if algorithm seems to enter a loop we impose the needed cuts to be kept.*/
    mutable OsiCuts savedCuts_;
      /** Store the current node number.*/
    mutable int currentNodeNumber_;
    /** @} */

#ifdef OA_DEBUG
    class OaDebug
    {
      public:
      bool checkInteger(const OsiSolverInterface&nlp, std::ostream & os) const;

      void printEndOfProcedureDebugMessage(const OsiCuts &cs,
          bool foundSolution,
          double solValue,
          double milpBound,
          bool isInteger,
          bool feasible,
          std::ostream & os) const;
    };

    /** debug object. */
    OaDebug debug_;

#endif
  };
}
#endif

