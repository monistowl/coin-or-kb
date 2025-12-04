/**
 * @file BonFpForMinlp.hpp
 * @brief Feasibility Pump for MINLP via Outer Approximation
 * Copyright (C) CNRS 2008. All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * MinlpFeasPump: Feasibility Pump implementation for MINLP using OA
 * decomposition. Alternates between solving MIP with distance-to-integer
 * objective and NLP with fixed integers to find feasible solutions.
 *
 * @algorithm Feasibility Pump for MINLP (OA-based):
 *   Heuristic to find MINLP-feasible solutions via alternating projections:
 *   1. Solve NLP relaxation → get (x*, y*) with y* fractional integers
 *   2. Set MIP objective: min Σ_j |y_j - round(y_j*)| (distance to integrality)
 *   3. Solve MIP with OA cuts → get integer ŷ
 *   4. Fix integers: y = ŷ, solve NLP(y) for continuous x
 *   5. If feasible: done. Else: add OA cuts, goto 2
 *   6. Perturb objective if cycling detected
 *
 * @math Distance-to-integer objective:
 *   Δ(y, ŷ) = Σ_j (y_j - ŷ_j)² or L1 norm Σ_j |y_j - ŷ_j|
 *   For binary: Δ = Σ_{ŷ_j=0} y_j + Σ_{ŷ_j=1} (1 - y_j)
 *   OA linearization: g(x*) + ∇g(x*)ᵀ(x - x*) ≤ 0
 *
 * @complexity O(k · (MIP + NLP)) where k = iterations until feasible.
 *   Typically 5-50 iterations. Each MIP uses OA approximation.
 *
 * @ref Bonami, Cornuéjols, Lodi, Margot (2009). "A Feasibility Pump for
 *      Mixed Integer Nonlinear Programs". Math. Programming 119:331-352.
 *
 * Authors: Pierre Bonami, CNRS
 * Date: February 13, 2009
 *
 * @see OaDecompositionBase for base OA framework
 * @see PumpForMinlp for alternative FP implementation
 */

#ifndef BonFpForMinlp_H
#define BonFpForMinlp_H
#include "BonOaDecBase.hpp"

namespace Bonmin{
  class MinlpFeasPump : public OaDecompositionBase{
   public:
    /// Constructor with basic setup
    MinlpFeasPump(BabSetupBase & b);

    /// Copy constructor
    MinlpFeasPump(const MinlpFeasPump &copy)
        :
        OaDecompositionBase(copy),
        subMip_(new SubMipSolver(*copy.subMip_)),
        passBound_(copy.passBound_)
    {}
    /// Destructor
    ~MinlpFeasPump();

    void setStrategy(const CbcStrategy & strategy)
    {
      parameters_.setStrategy(strategy);
    }

    virtual CglCutGenerator * clone() const
    {
      return new MinlpFeasPump(*this);
    }
    /** Register OA options.*/
    static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

  protected:
    /// virtual method which performs the OA algorithm by modifying lp and nlp.
    virtual double performOa(OsiCuts & cs, solverManip &lpManip,
                   BabInfo * babInfo, double &cutoff, const CglTreeInfo & info) const;
    /// virutal method to decide if local search is performed
    virtual bool doLocalSearch(BabInfo * babInfo) const;
    /** Put objective of MIP according to FP scheme. */
    void set_fp_objective(OsiSolverInterface &si, const double * colsol) const;
    
  private:
    SubMipSolver * subMip_;
    /** Wether or not to pass bound to master algorithm.*/
    int passBound_;
  };

}/* End Namespace.*/

#endif


