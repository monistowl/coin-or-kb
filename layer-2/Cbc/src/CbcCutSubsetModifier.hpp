/**
 * @file CbcCutSubsetModifier.hpp
 * @brief Cut modifier that filters cuts based on variable indices
 * Copyright (C) 2003, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcCutSubsetModifier: Filters cuts to exclude those involving certain variables.
 * Used in decomposition-style approaches where only a subset of variables
 * should appear in cuts.
 *
 * Primary use case:
 * - Remove cuts that reference variables >= firstOdd_
 * - Useful when auxiliary variables shouldn't appear in cuts
 * - Can weaken cuts instead of deleting (future enhancement)
 *
 * modify() return values:
 * - 0: Cut unchanged
 * - 1: Cut strengthened
 * - 2: Cut weakened
 * - 3: Cut deleted (set to NULL)
 *
 * @see CbcCutModifier for base class
 * @see CbcCutGenerator for cut generation
 */
// Edwin 11/25/09 carved out of CbcCutGenerator

#ifndef CbcCutSubsetModifier_H
#define CbcCutSubsetModifier_H

#include "OsiSolverInterface.hpp"
#include "OsiCuts.hpp"
#include "CglCutGenerator.hpp"
#include "CbcCutModifier.hpp"

class CbcModel;
class OsiRowCut;
class OsiRowCutDebugger;
/** Simple cut modifier base class

    In exotic circumstances - cuts may need to be modified
    a) strengthened - changed
    b) weakened - changed
    c) deleted - set to NULL
    d) unchanged

    initially get rid of cuts with variables >= k
    could weaken
*/

class CBCLIB_EXPORT CbcCutSubsetModifier : public CbcCutModifier {
public:
  /// Default Constructor
  CbcCutSubsetModifier();

  /// Useful Constructor
  CbcCutSubsetModifier(int firstOdd);

  // Copy constructor
  CbcCutSubsetModifier(const CbcCutSubsetModifier &);

  /// Destructor
  virtual ~CbcCutSubsetModifier();

  /// Assignment
  CbcCutSubsetModifier &operator=(const CbcCutSubsetModifier &rhs);
  /// Clone
  virtual CbcCutModifier *clone() const;

  /** Returns
        0 unchanged
        1 strengthened
        2 weakened
        3 deleted
    */
  virtual int modify(const OsiSolverInterface *solver, OsiRowCut &cut);
  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *) {}

protected:
  /// data
  /// First odd variable
  int firstOdd_;
};

#endif //CbcCutSubsetModifier_H

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
