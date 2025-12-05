// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CglCutGenerator.hpp
 * @brief Abstract base class for all CGL cutting plane generators
 *
 * Defines the interface that all cut generators must implement. In MIP
 * branch-and-cut, cutting planes tighten the LP relaxation to cut off
 * fractional solutions while keeping all integer-feasible points.
 *
 * @algorithm Cutting Plane Separation:
 * Find violated inequalities that cut off the current LP solution.
 *
 * SEPARATION PROBLEM:
 *   Given: LP solution x* (fractional)
 *   Find: Valid inequality a'x <= b such that a'x* > b
 *
 *   The inequality must be valid (satisfied by all integer solutions)
 *   but violated by x*.
 *
 * VALIDITY REQUIREMENT:
 *   A cut a'x <= b is valid for MIP {min c'x : Ax <= b, x_j integer}
 *   if every integer-feasible point satisfies a'x <= b.
 *
 * CUT-AND-BRANCH FRAMEWORK:
 *   1. Solve LP relaxation -> x*
 *   2. if x* integer-feasible: DONE (optimal)
 *   3. Call cut generators: generateCuts(x*, cs)
 *   4. if violated cuts found:
 *        Add to LP, goto 1
 *   5. else: Branch on fractional variable
 *
 * @algorithm Global vs Local Cuts:
 * Cuts can have different validity scopes.
 *
 * GLOBAL CUTS:
 *   - Valid throughout entire B&B tree
 *   - Derived from original problem structure
 *   - canDoGlobalCuts_ = true
 *
 * LOCAL CUTS:
 *   - Valid only in current subtree (depend on branching decisions)
 *   - Often stronger but must be managed carefully
 *   - Example: Gomory cuts from current LP basis
 *
 * @algorithm Aggressiveness Control:
 * Balance cut quality vs. generation cost.
 *
 *   aggressive_ = 0:   Minimal cuts (fastest)
 *   aggressive_ = 50:  Normal effort
 *   aggressive_ = 100: Root node intensive search
 *
 * Pure virtual interface:
 * - generateCuts(): Main entry point - examines LP solution and adds violated cuts
 * - clone(): Deep copy for use in parallel B&C
 *
 * Configuration:
 * - aggressive_: Hint for cut generation intensity (0=minimal, 100=root node default)
 * - canDoGlobalCuts_: Whether cuts are valid globally (requires no general integers)
 * - originalSolver_: Some generators need unpreprocessed model
 *
 * Integration with branch-and-cut:
 * - mayGenerateRowCutsInTree(): Whether to call at tree nodes (affects matrix structure)
 * - needsOptimalBasis(): Whether LP must be solved to optimality first
 * - maximumLengthOfCutInTree(): Limits cut density for efficiency
 *
 * Derived classes implement specific separation algorithms:
 * - Gomory, MIR, knapsack covers (general MIP)
 * - Clique, odd hole, zero-half (0-1 structure)
 * - Flow cover, lift-and-project (specialized)
 *
 * @complexity Separation is typically NP-hard in general, but polynomial
 *   heuristics work well in practice.
 *
 * @ref Cornuejols (2008). "Valid Inequalities for Mixed Integer Linear Programs".
 *   Math. Programming 112(1):3-44.
 *
 * @see OsiCuts for the cut collection interface
 * @see CglTreeInfo for branch-and-cut context
 */

#ifndef CglCutGenerator_H
#define CglCutGenerator_H

#include "OsiCuts.hpp"
#include "OsiSolverInterface.hpp"
#include "CglConfig.h"
#include "CglTreeInfo.hpp"

//-------------------------------------------------------------------
//
// Abstract base class for generating cuts.
//
//-------------------------------------------------------------------
///
/** Cut Generator Base Class

This is an abstract base class for generating cuts.  A specific cut
generator will inherit from this class.
*/
class CGLLIB_EXPORT CglCutGenerator {

public:
  /**@name Generate Cuts */
  //@{
  /** Generate cuts for the model data contained in si.
  The generated cuts are inserted into and returned in the
  collection of cuts cs.
  */
  virtual void generateCuts(const OsiSolverInterface &si, OsiCuts &cs,
    const CglTreeInfo info = CglTreeInfo())
    = 0;
  //@}

  /**@name Constructors and destructors */
  //@{
  /// Default constructor
  CglCutGenerator();

  /// Copy constructor
  CglCutGenerator(const CglCutGenerator &);

  /// Clone
  virtual CglCutGenerator *clone() const = 0;

  /// Assignment operator
  CglCutGenerator &operator=(const CglCutGenerator &rhs);

  /// Destructor
  virtual ~CglCutGenerator();

  /** Create C++ lines to set the generator in the current state.
      The output must be parsed by the calling code, as each line
      starts with a key indicating the following:<BR>
      0: must be kept (for #includes etc)<BR>
      3: Set to changed (not default) values<BR>
      4: Set to default values (redundant)<BR>

      Keys 1, 2, 5, 6, 7, 8 are defined, but not applicable to 
      cut generators.
  */
  virtual std::string generateCpp(FILE *) { return ""; }

  /// This can be used to refresh any information
  virtual void refreshSolver(OsiSolverInterface *) {}
  //@}

  /**@name Gets and Sets */
  //@{
  /**
     Get Aggressiveness - 0 = neutral, 100 is normal root node.
     Really just a hint to cut generator
  */
  inline int getAggressiveness() const
  {
    return aggressive_;
  }

  /**
     Set Aggressiveness - 0 = neutral, 100 is normal root node.
     Really just a hint to cut generator
  */
  inline void setAggressiveness(int value)
  {
    aggressive_ = value;
  }
  /// Set whether can do global cuts
  inline void setGlobalCuts(bool trueOrFalse)
  {
    canDoGlobalCuts_ = trueOrFalse;
  }
  /// Say whether can do global cuts
  inline bool canDoGlobalCuts() const
  {
    return canDoGlobalCuts_;
  }
  /// Returns original solver
  inline OsiSolverInterface * originalSolver() const
  { return originalSolver_;}
  /// swap original solvers
  inline OsiSolverInterface * swapOriginalSolver(OsiSolverInterface * solver)
  {
    OsiSolverInterface * swap = originalSolver_;
    originalSolver_ = solver;
    return swap;
  }
  /**
     Returns true if may generate Row cuts in tree (rather than root node).
     Used so know if matrix will change in tree.  Really
     meant so column cut generators can still be active
     without worrying code.
     Default is true
  */
  virtual bool mayGenerateRowCutsInTree() const;
  /// Return true if needs optimal basis to do cuts
  virtual bool needsOptimalBasis() const;
  /// Return true if needs original model with the corr. solution (not preprocessed)
  virtual bool needsOriginalModel() const;
  /// Return maximum length of cut in tree
  virtual int maximumLengthOfCutInTree() const
  {
    return COIN_INT_MAX;
  }
  //@}

  // test this class
  //static void unitTest();

  // private:

  /// Original solver (not used by all - but by enough)
  OsiSolverInterface * originalSolver_;
  /**
     Aggressiveness - 0 = neutral, 100 is normal root node.
     Really just a hint to cut generator
  */
  int aggressive_;
  /// True if can do global cuts i.e. no general integers
  bool canDoGlobalCuts_;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
