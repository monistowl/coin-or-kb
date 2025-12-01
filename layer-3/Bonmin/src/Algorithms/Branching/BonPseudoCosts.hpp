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
 * @algorithm Pseudo-Cost Branching:
 * Learn branching quality from history to avoid repeated strong branching:
 * 1. Initialize: ψ⁺ᵢ = ψ⁻ᵢ = default_cost (or from first strong branch)
 * 2. After branching on xᵢ with fractional part fᵢ:
 *    - Up branch (xᵢ ≥ ⌈xᵢ⌉): record Δobj⁺, update ψ⁺ᵢ
 *    - Down branch (xᵢ ≤ ⌊xᵢ⌋): record Δobj⁻, update ψ⁻ᵢ
 * 3. Update formula:
 *    ψ⁺ᵢ = (Σ Δobj⁺) / count(up branches)
 *    ψ⁻ᵢ = (Σ Δobj⁻) / count(down branches)
 * 4. Score variable: score(i) = w·min(ψ⁺ᵢ·(1-fᵢ), ψ⁻ᵢ·fᵢ)
 *                              + (1-w)·max(ψ⁺ᵢ·(1-fᵢ), ψ⁻ᵢ·fᵢ)
 *
 * @math Pseudo-cost per unit change:
 *   ψ⁺ᵢ ≈ E[Δobj | branch up on xᵢ] / (1 - fᵢ)
 *   ψ⁻ᵢ ≈ E[Δobj | branch down on xᵢ] / fᵢ
 * where fᵢ = xᵢ - ⌊xᵢ⌋ is the fractional part.
 *
 * @complexity O(1) per variable selection (no solving needed).
 * Compare to O(LP_solve) for strong branching per candidate.
 *
 * @ref Benichou et al. (1971). "Experiments in mixed-integer linear programming".
 *   Mathematical Programming 1(1):76-94.
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
