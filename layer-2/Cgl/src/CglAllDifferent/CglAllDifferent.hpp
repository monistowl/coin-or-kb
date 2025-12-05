// Copyright (C) 2005, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CglAllDifferent.hpp
 * @brief All-different constraint propagation for CSP-style constraints
 *
 * Propagates all-different constraints: variables in a set must all
 * take different integer values. Common in constraint satisfaction
 * problems (CSP) mapped to MIP.
 *
 * @algorithm All-Different Constraint Propagation:
 * Domain filtering based on value exclusion.
 *
 * CONSTRAINT SEMANTICS:
 *   AllDifferent(x_1, x_2, ..., x_k) means:
 *     x_i != x_j for all pairs i != j
 *
 * VALUE EXCLUSION:
 *   When variable x_i is fixed to value v:
 *     For all j != i in same set:
 *       Remove v from domain(x_j)
 *
 *   If domain(x_j) becomes {v}: fix x_j = v
 *   If domain(x_j) becomes empty: infeasible
 *
 * PROPAGATION LOOP:
 *   queue = all_fixed_variables
 *   while (queue not empty):
 *     x_i = dequeue()
 *     v = value(x_i)
 *     for each x_j in same AllDiff set:
 *       if v in domain(x_j):
 *         remove v from domain(x_j)
 *         if |domain(x_j)| == 1: enqueue(x_j)
 *         if |domain(x_j)| == 0: return INFEASIBLE
 *
 * @math Hall's theorem gives stronger propagation (not implemented here):
 *   If |{x_i : domain(x_i) subset S}| > |S|, infeasible.
 *
 * This is a column cut generator (fixes/tightens variable bounds),
 * not a row cut generator. mayGenerateRowCutsInTree() returns false.
 *
 * Each set defines: x_i != x_j for all i,j in the set.
 *
 * Constructor takes:
 * - numberSets: How many all-different sets
 * - starts: Start indices into which array (size numberSets+1)
 * - which: Variable indices for all sets (referenced via starts)
 *
 * @complexity O(k^2 * d) per propagation where k = set size, d = domain size
 *
 * @ref van Hoeve (2001). "The alldifferent Constraint: A Survey".
 *
 * @see CglProbing for more general variable fixing via implications
 */

#ifndef CglAllDifferent_H
#define CglAllDifferent_H

#include <string>

#include "CglCutGenerator.hpp"

/** AllDifferent Cut Generator Class 
    This has a number of sets.  All the members in each set are general integer
    variables which have to be different from all others in the set.

    At present this only generates column cuts

    At present it is very primitive compared to proper CSP implementations
 */
class CGLLIB_EXPORT CglAllDifferent : public CglCutGenerator {
 
public:
    
  
  /**@name Generate Cuts */
  //@{
  /** This fixes (or reduces bounds) on sets of all different variables
  */
  virtual void generateCuts( const OsiSolverInterface & si, OsiCuts & cs,
			     const CglTreeInfo info = CglTreeInfo());
  //@}


  /**@name Constructors and destructors */
  //@{
  /// Default constructor 
  CglAllDifferent ();

  /// Useful constructot
  CglAllDifferent(int numberSets, const int * starts, const int * which);
 
  /// Copy constructor 
  CglAllDifferent (
    const CglAllDifferent &);

  /// Clone
  virtual CglCutGenerator * clone() const;

  /// Assignment operator 
  CglAllDifferent &
    operator=(
    const CglAllDifferent& rhs);
  
  /// Destructor 
  virtual
    ~CglAllDifferent ();
  /// Create C++ lines to get to current state
  virtual std::string generateCpp( FILE * fp);

  /// This can be used to refresh any inforamtion
  virtual void refreshSolver(OsiSolverInterface * solver);
  /**
     Returns true if may generate Row cuts in tree (rather than root node).
     Used so know if matrix will change in tree.  Really
     meant so column cut generators can still be active
     without worrying code.
     Default is true
  */
  virtual bool mayGenerateRowCutsInTree() const
  { return false;}
  //@}
  /**@name Sets and Gets */
  //@{
  /// Set log level
  inline void setLogLevel(int value)
  { logLevel_=value;}
  /// Get log level
  inline int getLogLevel() const
  { return logLevel_;}
  /// Set Maximum number of sets to look at at once
  inline void setMaxLook(int value)
  { maxLook_=value;}
  /// Get Maximum number of sets to look at at once
  inline int getMaxLook() const
  { return maxLook_;}
  //@}
      
private:
  
 // Private member methods
  /**@name  */
  //@{
  //@}

  // Private member data

  /**@name Private member data */
  //@{
  /// Number of sets
  int numberSets_;
  /// Total number of variables in all different sets
  int numberDifferent_;
  /// Maximum number of sets to look at at once
  int maxLook_;
  /// Log level - 0 none, 1 - a bit, 2 - more details
  int logLevel_;
  /// Start of each set
  int * start_;
  /// Members (0,1,....) not as in original model
  int * which_;
  /// Original members
  int * originalWhich_;
  //@}
};
#endif
