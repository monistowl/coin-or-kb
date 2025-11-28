// (C) Copyright International Business Machines Corporation 2007
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// Pierre Bonami, International Business Machines Corporation
//
// Date : 04/12/2007

/**
 * @file BonPseudoCosts.hpp
 * @brief Pseudo-cost storage and update for MINLP branching
 *
 * Extends OsiPseudoCosts to track branching history for integer variables.
 * Pseudo-costs estimate the objective change per unit change in a variable,
 * enabling efficient branching decisions without expensive strong branching.
 *
 * **Pseudo-cost formula:**
 * - upPseudoCost[i] = sum(upChange) / count(upBranches)
 * - downPseudoCost[i] = sum(downChange) / count(downBranches)
 * - Expected change = pseudoCost * distance_to_integer
 *
 * **Update via addInfo():**
 * - Called after each branching decision resolves
 * - Records objective change and infeasibility change
 * - Status indicates: optimal, infeasible, or not finished
 *
 * @see BonChooseVariable for usage in branching decisions
 * @see OsiPseudoCosts for the base class
 */
#ifndef BonPseudoCosts_H
#define BonPseudoCosts_H

#include "BonminConfig.h"
#include "OsiChooseVariable.hpp"
namespace Bonmin
{

  class BONMINLIB_EXPORT PseudoCosts: public OsiPseudoCosts
  {
  public:
    /** Default constructor.*/
    PseudoCosts();

    /** Copy constructor.*/
    PseudoCosts(const PseudoCosts & rhs);

    /** Assignment operator const version.*/
    PseudoCosts & operator=(const PseudoCosts&rhs);
#if 0
    /** Acces upTotalChange.*/
    inline double * upTotalChange()
    {
      return upTotalChange_;
    }

    /** Acces downTotalChange.*/
    inline double * downTotalChange()
    {
      return downTotalChange_;
    }

    /** Acces upNumber.*/
    inline int * upNumber()
    {
      return upNumber_;
    }

    /** Acces downNumber.*/
    inline int * downNumber()
    {
      return downNumber_;
    }

    /** Acces upTotalChange.*/
    inline const double * upTotalChange() const
    {
      return upTotalChange_;
    }

    /** Acces downTotalChange.*/
    inline const double * downTotalChange() const
    {
      return downTotalChange_;
    }

    /** Acces upNumber.*/
    inline const int * upNumber() const
    {
      return upNumber_;
    }

    /** Acces downNumber.*/
    inline const int * downNumber() const
    {
      return downNumber_;
    }

    /** Access number objects.*/
    inline int numberObjects() const
    {
      return numberObjects_;
    }
#endif
    /** Add a pseudo cost information.*/
    void addInfo(int way, double originalObj, double originalInfeas,
        double newObj, double newInfeas, int status);

  };

}/* End Bonmin namespace.*/

#endif
