// (C) Copyright International Business Machines Corporation 2007
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// Pierre Bonami, International Business Machines Corporation
//
// Date : 04/13/2007

/**
 * @file BonBonminSetup.hpp
 * @brief Main Bonmin algorithm configuration and initialization
 *
 * Extends BabSetupBase with Bonmin-specific algorithm selection and
 * initialization for all MINLP algorithms.
 *
 * **Algorithm enum:**
 * - B_BB (0): NLP-based branch-and-bound
 * - B_OA (1): Pure Outer Approximation decomposition
 * - B_QG (2): Quesada-Grossmann branch-and-cut
 * - B_Hyb (3): Hybrid OA with NLP at nodes (default)
 * - B_Ecp (4): Extended Cutting Plane (FilMINT-style)
 * - B_IFP (5): Iterated Feasibility Pump
 *
 * **Initialization:**
 * - initializeBBB(): Pure B&B with NLP at every node
 * - initializeBHyb(): Hybrid with OA cuts + occasional NLP
 *
 * @algorithm MINLP Solver Framework:
 * Bonmin implements multiple algorithms for convex MINLP:
 * min f(x,y) s.t. g(x,y) ≤ 0, x ∈ ℝⁿ, y ∈ {0,1}ᵐ
 *
 * B_BB: Solve NLP relaxation at every B&B node. Most robust, slowest.
 * B_OA: Outer Approximation - alternates MILP master and NLP subproblems.
 * B_QG: Single-tree OA - generates OA cuts within one B&B tree.
 * B_Hyb: Hybrid - OA cuts + NLP solves at key nodes (default, often fastest).
 * B_Ecp: Extended Cutting Plane - linear cuts only, no NLP solves in tree.
 *
 * @math Outer Approximation generates cuts from NLP solutions x*:
 * For convex constraint g(x) ≤ 0 at point x*:
 *   g(x*) + ∇g(x*)ᵀ(x - x*) ≤ 0
 * This linearization is valid for convex g. Collect cuts from multiple
 * NLP solves to approximate the feasible region from outside.
 *
 * @complexity Per-node: O(NLP) for B_BB, O(LP) for B_Ecp.
 * Hybrid reduces total NLP solves while maintaining solution quality.
 * Total complexity problem-dependent; convex MINLP is NP-hard.
 *
 * @ref Bonami et al. (2008). "An algorithmic framework for convex mixed
 *   integer nonlinear programs". Discrete Optimization 5(2):186-204.
 * @ref Duran & Grossmann (1986). "An outer-approximation algorithm for
 *   a class of mixed-integer nonlinear programs". Math. Prog. 36:307-339.
 *
 * @see BabSetupBase for common configuration
 * @see BonminAmplSetup for AMPL-based initialization
 */
#ifndef BonminSetup_H
#define BonminSetup_H
#include "BonBabSetupBase.hpp"
namespace Bonmin
{
  /** Type of algorithms which can be used.*/
  enum Algorithm{
    Dummy=-1/** Dummy value before initialization.*/,
    B_BB=0/** Bonmin's Branch-and-bound.*/,
    B_OA=1/** Bonmin's Outer Approximation Decomposition.*/,
    B_QG=2/** Bonmin's Quesada & Grossmann branch-and-cut.*/,
    B_Hyb=3/** Bonmin's hybrid outer approximation.*/,
    B_Ecp=4/** Bonmin's implemantation of ecp cuts based branch-and-cut a la FilMINT.*/,
    B_IFP=5/** Bonmin's implemantation of iterated feasibility pump for MINLP.*/
  };
  /* Bonmin algorithm setup. */
  class BONMINLIB_EXPORT BonminSetup : public BabSetupBase
  {
  public:
    /** Default constructor. */
    BonminSetup(const CoinMessageHandler * handler = NULL);
    /** Copy constructor. */
    BonminSetup(const BonminSetup & other);

    /** Copy but uses an other nlp.*/
    BonminSetup(const BonminSetup &setup,
                OsiTMINLPInterface &nlp);

    /** Copy but uses another nlp and algorithm.*/
    BonminSetup(const BonminSetup &setup,
                OsiTMINLPInterface &nlp,
                const std::string & prefix);
    /** virtual copy constructor. */
    virtual BabSetupBase * clone() const
    {
      return new BonminSetup(*this);
    }
    /** Make a copy with solver replace by one passed .*/
    //    virtual BabSetupBase *clone(OsiTMINLPInterface&nlp)const{
    //      return new BonminSetup(*this, nlp);
    //    }
    /** Make a copy with solver replace by one passed .*/
    BonminSetup *clone(OsiTMINLPInterface&nlp)const{
      return new BonminSetup(*this, nlp);
    }
    /** Make a copy but take options with different prefix.*/
    BonminSetup *clone(OsiTMINLPInterface &nlp, const std::string & prefix)const{
      return new BonminSetup(*this, nlp, prefix);
    }
    virtual ~BonminSetup()
    {}
    /** @name Methods to instantiate: Registering and retrieving options and initializing everything. */
    /** @{ */
    /** Register all the options for this algorithm instance.*/
    virtual void registerOptions();
    /** Setup the defaults options for this algorithm. */
    virtual void setBabDefaultOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> /*roptions*/)
    {}
    /** @} */
    /** Register all bonmin type executable options.*/
    static void registerAllOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);
    /** Initialize, read options and create appropriate bonmin setup.*/
    void initialize(Ipopt::SmartPtr<TMINLP> tminlp, bool createContinuousSolver = true);
    /** Initialize, read options and create appropriate bonmin setup.*/
    void initialize(const OsiTMINLPInterface& nlpSi, bool createContinuousSolver = true);
    /** Get the algorithm used.*/
    Bonmin::Algorithm getAlgorithm();

    void addCutGenerator(CuttingMethod & cg){
      BabSetupBase::addCutGenerator(cg);
    }
  protected:
    /** Register standard MILP cut generators. */
    static void registerMilpCutGenerators(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);
    /** Add milp cut generators according to options.*/
    void addMilpCutGenerators();
    /** Initialize a plain branch-and-bound.*/
    void initializeBBB();
    /** Initialize a branch-and-cut with some OA.*/
    void initializeBHyb(bool createContinuousSolver = false);
  private:
    Algorithm algo_;
  };
}/** end namespace Bonmin*/

#endif

