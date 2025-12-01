// (C) Copyright Carnegie Mellon University 2005
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// P. Bonami, Carnegie Mellon University
//
// Date :  05/26/2005

/**
 * @file BonOACutGenerator2.hpp
 * @brief Classical Outer Approximation cut generator for MINLP
 *
 * Implements the standard OA algorithm of Duran & Grossmann (1986) for convex
 * MINLP. Generates linearization cuts by Taylor expansion of nonlinear
 * constraints at NLP solutions.
 *
 * @algorithm Outer Approximation (Duran-Grossmann):
 * Decomposition method for convex MINLP via MILP master + NLP subproblems:
 * 1. Solve NLP relaxation: y⁰ = argmin{f(x): g(x) ≤ 0, x ∈ X}
 * 2. Generate OA cuts for each constraint i:
 *    gᵢ(y⁰) + ∇gᵢ(y⁰)ᵀ(x - y⁰) ≤ 0  (linearization)
 * 3. Solve MILP master: min{cᵀx : OA cuts, x_I ∈ Z}
 * 4. Fix integers at x*: solve NLP(x*_I) → new point y*
 * 5. Add OA cuts at y*, update upper/lower bounds
 * 6. Terminate when UB - LB < ε or iteration limit
 *
 * @math OA cut derivation (convex g):
 * For convex gᵢ: gᵢ(x) ≥ gᵢ(y) + ∇gᵢ(y)ᵀ(x-y)  (first-order condition)
 * Cut: ∇gᵢ(y)ᵀx ≤ ∇gᵢ(y)ᵀy - gᵢ(y)  (valid for feasible region)
 *
 * @complexity O(k·(MILP + NLP)) where k = iterations.
 * Finite convergence for convex MINLP. Typically k = O(2^|I|) worst case,
 * but often polynomial in practice for well-structured problems.
 *
 * @ref Duran, Grossmann (1986). "An outer-approximation algorithm for a class
 *   of mixed-integer nonlinear programs". Mathematical Programming 36:307-339.
 *
 * @see OaDecompositionBase for the base class
 * @see SubMipSolver for MILP subproblem solving
 */
#ifndef BonOACutGenerator2_HPP
#define BonOACutGenerator2_HPP
#include "BonOaDecBase.hpp"

namespace Bonmin
{
  /** Class to perform OA in its classical form.*/
  class BONMINLIB_EXPORT OACutGenerator2 : public OaDecompositionBase
  {
  public:
    /// Constructor with basic setup
    OACutGenerator2(BabSetupBase & b);

    /// Copy constructor
    OACutGenerator2(const OACutGenerator2 &copy)
        :
        OaDecompositionBase(copy),
        subMip_(new SubMipSolver (*copy.subMip_))
    {}
    /// Destructor
    ~OACutGenerator2();

    void setStrategy(const CbcStrategy & strategy)
    {
      parameters_.setStrategy(strategy);
    }

    virtual CglCutGenerator * clone() const
    {
      return new OACutGenerator2(*this);
    }
    /** Register OA options.*/
    static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

  protected:
    /// virtual method which performs the OA algorithm by modifying lp and nlp.
    virtual double performOa(OsiCuts & cs, solverManip &lpManip,
               BabInfo * babInfo, double &cutoff, const CglTreeInfo & info) const;
    /// virutal method to decide if local search is performed
    virtual bool doLocalSearch(BabInfo * babInfo) const;

  private:
    SubMipSolver * subMip_;
  };
}
#endif
