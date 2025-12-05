/**
 * @file CbcCutModifier.hpp
 * @brief Abstract base class for cut modification
 *
 * @algorithm Cut Post-Processing Interface
 * Copyright (C) 2003, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcCutModifier: Allows post-processing of generated cuts.
 * Called after cut generation to strengthen, weaken, or remove cuts.
 *
 * modify() return codes:
 * - 0: Unchanged
 * - 1: Strengthened (tightened)
 * - 2: Weakened (loosened)
 * - 3: Deleted (should be discarded)
 *
 * Use cases:
 * - Strengthen cuts using problem-specific knowledge
 * - Remove cuts that are too dense or weak
 * - Apply numerical cleanup
 *
 * @see CbcCutGenerator for cut generation framework
 * @see CbcCutSubsetModifier for subset-specific modification
 *
 * Edwin 11/25/09 carved out of CbcCutGenerator
 */

#ifndef CbcCutModifier_H
#define CbcCutModifier_H

#include "OsiSolverInterface.hpp"
#include "OsiCuts.hpp"
#include "CglCutGenerator.hpp"
#include "CbcConfig.h"

class CbcModel;
class OsiRowCut;
class OsiRowCutDebugger;
/** Abstract cut modifier base class

    In exotic circumstances - cuts may need to be modified
    a) strengthened - changed
    b) weakened - changed
    c) deleted - set to NULL
    d) unchanged
*/

class CBCLIB_EXPORT CbcCutModifier {
public:
  /// Default Constructor
  CbcCutModifier();

  // Copy constructor
  CbcCutModifier(const CbcCutModifier &);

  /// Destructor
  virtual ~CbcCutModifier();

  /// Assignment
  CbcCutModifier &operator=(const CbcCutModifier &rhs);
  /// Clone
  virtual CbcCutModifier *clone() const = 0;

  /** Returns
        0 unchanged
        1 strengthened
        2 weakened
        3 deleted
    */
  virtual int modify(const OsiSolverInterface *solver, OsiRowCut &cut) = 0;
  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *) {}

protected:
};

#endif //CbcCutModifier_H

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
