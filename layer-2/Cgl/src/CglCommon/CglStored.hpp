// Copyright (C) 2005, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CglStored.hpp
 * @brief Cut generator that stores and replays previously found cuts
 *
 * Instead of computing cuts, CglStored maintains a collection of cuts
 * from prior solves or other sources, and adds violated ones to the LP.
 *
 * Use cases:
 * - Warm-starting branch-and-cut with cuts from a similar problem
 * - Cut pool management across nodes in the search tree
 * - Importing cuts computed externally or in a preprocessing phase
 * - Debugging by replaying a known cut sequence
 *
 * Cut selection:
 * - Only adds cuts violated by more than requiredViolation_ (default 1e-5)
 * - Violation = constraint LHS evaluated at current LP solution
 * - Avoids adding nearly-satisfied cuts that waste basis updates
 *
 * Can also store:
 * - Best known solution (for primal bounds)
 * - Tight variable bounds (from probing/preprocessing)
 * - Probing implication information (CglTreeProbingInfo)
 *
 * @see CglCutGenerator for the base interface
 * @see CglTreeProbingInfo for implication data from probing
 * @see OsiCuts for the cut collection interface
 */

#ifndef CglStored_H
#define CglStored_H

#include <string>

#include "CglCutGenerator.hpp"

class CoinWarmStartBasis;
class CglTreeProbingInfo;
/** Stored Cut Generator Class */
class CGLLIB_EXPORT CglStored : public CglCutGenerator {

public:
  /**@name Generate Cuts */
  //@{
  /** Generate Mixed Integer Stored cuts for the model of the 
      solver interface, si.

      Insert the generated cuts into OsiCut, cs.

      This generator just looks at previously stored cuts
      and inserts any that are violated by enough
  */
  virtual void generateCuts(const OsiSolverInterface &si, OsiCuts &cs,
    const CglTreeInfo info = CglTreeInfo());
  //@}

  /**@name Change criterion on whether to include cut.
   Violations of more than this will be added to current cut list
  (default 1.0e-5) */
  //@{
  /// Set
  inline void setRequiredViolation(double value)
  {
    requiredViolation_ = value;
  }
  /// Get
  inline double getRequiredViolation() const
  {
    return requiredViolation_;
  }
  /// Takes over ownership of probing info
  inline void setProbingInfo(CglTreeProbingInfo *info)
  {
    probingInfo_ = info;
  }
  //@}

  /**@name Cut stuff */
  //@{
  /// Add cuts
  void addCut(const OsiCuts &cs);
  /// Add a row cut
  void addCut(const OsiRowCut &cut);
  /// Add a row cut from a packed vector
  void addCut(double lb, double ub, const CoinPackedVector &vector);
  /// Add a row cut from elements
  void addCut(double lb, double ub, int size, const int *colIndices, const double *elements);
  inline int sizeRowCuts() const
  {
    return cuts_.sizeRowCuts();
  }
  const OsiRowCut *rowCutPointer(int index) const
  {
    return cuts_.rowCutPtr(index);
  }
  /// Save stuff
  void saveStuff(double bestObjective, const double *bestSolution,
    const double *lower, const double *upper);
  /// Best solution (or NULL)
  inline const double *bestSolution() const
  {
    return bestSolution_;
  }
  /// Best objective
  double bestObjective() const;
  /// Tight lower bounds
  const double *tightLower() const
  {
    return bounds_;
  }
  /// Tight upper bounds
  const double *tightUpper() const
  {
    return bounds_ + numberColumns_;
  }
  //@}

  /**@name Constructors and destructors */
  //@{
  /// Default constructor
  CglStored(int numberColumns = 0);

  /// Copy constructor
  CglStored(const CglStored &rhs);

  /// Constructor from file
  CglStored(const char *fileName);

  /// Clone
  virtual CglCutGenerator *clone() const;

  /// Assignment operator
  CglStored &
  operator=(const CglStored &rhs);

  /// Destructor
  virtual ~CglStored();
  //@}

protected:
  // Protected member methods

  // Protected member data

  /**@name Protected member data */
  //@{
  /// Only add if more than this requiredViolation
  double requiredViolation_;
  /// Pointer to probing information
  CglTreeProbingInfo *probingInfo_;
  /// Cuts
  OsiCuts cuts_;
  /// Number of columns in model
  int numberColumns_;
  /// Best solution (objective at end)
  double *bestSolution_;
  /// Tight bounds
  double *bounds_;
  //@}
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
