// (C) Copyright International Business Machines (IBM) 2006, 2007
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// P. Bonami, International Business Machines
//
// Date :  12/20/2006

/**
 * @file BonEcpCuts.hpp
 * @brief Extended Cutting Plane (ECP) cut generator for MINLP
 *
 * Generates OA cuts iteratively at LP solution points, refining the
 * linear approximation without requiring NLP solves at every iteration.
 *
 * @algorithm Extended Cutting Plane (ECP) Method:
 * Iterative linearization without explicit NLP solves:
 * 1. Solve LP relaxation → x^k
 * 2. Evaluate nonlinear constraints: vᵢ = gᵢ(x^k) for all i
 * 3. Find most violated: i* = argmax{vᵢ : vᵢ > 0}
 * 4. If max violation < abs_violation_tol_: STOP (feasible)
 * 5. Add OA cut at x^k for constraint i*:
 *    gᵢ*(x^k) + ∇gᵢ*(x^k)ᵀ(x - x^k) ≤ 0
 * 6. k ← k+1; if k < numRounds_: goto step 1
 *
 * Randomization via beta_:
 * - Skip cut with probability (1 - β^violation_count)
 * - Prevents overgeneration on nearly feasible constraints
 *
 * @math Convergence for convex constraints:
 * LP optimal value z^k → NLP optimal value z* as k → ∞
 * (since linear underestimators converge to convex envelope)
 *
 * @complexity O(k · LP_solve + k · nnz(∇g)) where k = numRounds_.
 * Much cheaper than OA since no NLP solves during iterations.
 *
 * @ref Kelley (1960). "The cutting-plane method for solving convex programs".
 *   Journal of the SIAM 8(4):703-712.
 *
 * @see OaDecompositionBase for base class
 * @see LpBranchingSolver for use in strong branching
 */
#ifndef BonECPCuts_HPP
#define BonECPCuts_HPP

#include "BonOaDecBase.hpp"
#include "CglCutGenerator.hpp"
namespace Bonmin
{
  class BONMINLIB_EXPORT EcpCuts: public OaDecompositionBase
  {
  public:
    EcpCuts(BabSetupBase & b);

    /// Copy constructor
    EcpCuts(const EcpCuts & copy):
        OaDecompositionBase(copy),
        objValue_(copy.objValue_),
        numRounds_(copy.numRounds_),
        abs_violation_tol_(copy.abs_violation_tol_),
        rel_violation_tol_(copy.rel_violation_tol_),
        beta_(copy.beta_)
    {}

    /// clone
    CglCutGenerator * clone() const
    {
      return new EcpCuts(*this);
    }

    /// Destructor
    virtual ~EcpCuts()
    {}
    /** Standard cut generation methods. */
    virtual void generateCuts(const OsiSolverInterface &si,  OsiCuts & cs,
        const CglTreeInfo info = CglTreeInfo());
    double doEcpRounds(OsiSolverInterface &si,
        bool leaveSiUnchanged,
        double* violation = NULL);

    void setNumRounds(int value)
    {
      numRounds_ = value;
    }

    void setPropabilityFactor(double value)
    {
      beta_ = value;
    }

    void setAbsViolationTolerance(double value)
    {
      abs_violation_tol_ = value;
    }
    void setRelViolationTolerance(double value)
    {
      rel_violation_tol_ = value;
    }

    /** Register ecp cuts options.*/
    static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

  protected:
    /// virtual method which performs the OA algorithm by modifying lp and nlp.
    virtual double performOa(OsiCuts & cs, solverManip &lpManip,
                   BabInfo * babInfo, double &cutoff, const CglTreeInfo &info) const
    {
      throw -1;
    }
    /// virutal method to decide if local search is performed
    virtual bool doLocalSearch(BabInfo * babInfo) const
    {
      return 0;
    }
  private:
    /** Record obj value at final point of Ecp. */
    mutable double objValue_;
    /** Record NLP infeasibility at final point of Ecp */
    mutable double violation_;
    /** maximum number of iterations of generation. */
    int numRounds_;
    /** absolute tolerance for NLP constraint violation to stop ECP rounds */
    double abs_violation_tol_;
    /** relative tolerance for NLP constraint violation to stop ECP rounds */
    double rel_violation_tol_;
    /** Factor for probability for skipping cuts */
    double beta_;
  };
} /* end namespace Bonmin.*/
#endif
