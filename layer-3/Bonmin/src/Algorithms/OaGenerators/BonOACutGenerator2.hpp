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
 * **Algorithm:**
 * 1. Solve initial NLP relaxation to get y0
 * 2. Generate OA cuts: g(y0) + ∇g(y0)ᵀ(x - y0) ≤ 0
 * 3. Solve MILP with cuts → integer solution x*
 * 4. Fix integers, solve NLP → new point y*
 * 5. Add cuts at y*, update bounds, repeat
 *
 * **Convergence:**
 * - For convex problems: finite convergence to global optimum
 * - For nonconvex: heuristic, may find local optima
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
