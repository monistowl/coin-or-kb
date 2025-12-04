// (C) Copyright Carnegie Mellon University 2005, 2006
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// P. Bonami, Carnegie Mellon University
//
// Date :  05/26/2005

/**
 * @file BonOaNlpOptim.hpp
 * @brief NLP-based outer approximation cut generator
 *
 * Generates OA cuts by solving NLP relaxations at B&B nodes, rather than
 * at integer feasible points (as in classical OA). More expensive per cut,
 * but can improve bounds at fractional nodes.
 *
 * @algorithm NLP-based OA Cut Generation:
 *   Strengthens LP relaxation by solving NLP at fractional B&B nodes:
 *   1. At B&B node (depth ≤ maxDepth_): get LP solution x_LP
 *   2. Solve continuous NLP relaxation: min f(x) s.t. g(x) ≤ 0
 *   3. At NLP solution x*: generate OA cuts g(x*) + ∇g(x*)ᵀ(x-x*) ≤ 0
 *   4. Filter: keep only cuts violated by x_LP (if addOnlyViolated_)
 *   5. Add cuts as global (valid in subtree) or local
 *
 * @math Cut validity:
 *   For convex g: linearization at any x* gives valid cut
 *   Not restricted to integer points like classical OA
 *   More cuts = tighter LP relaxation, but more NLP solves
 *
 * @complexity O(NLP) per node up to maxDepth_ levels.
 *   Trade-off: expensive per-node work vs. fewer total nodes.
 *   Controlled by maxDepth_ and solves_per_level_.
 *
 * @ref Bonami et al. (2008). "An algorithmic framework for convex MINLP".
 *      Discrete Optimization 5:186-204.
 *
 * **Parameters:**
 * - maxDepth_: Maximum tree depth for NLP solves (default 10)
 * - addOnlyViolated_: Only add cuts violated by LP solution
 * - global_: Add cuts globally (valid throughout tree)
 * - solves_per_level_: Control NLP solve frequency
 *
 * @see OaDecompositionBase for the classical OA algorithm
 * @see CglCutGenerator for the cut generator interface
 */
#ifndef BonOaNlpOptim_HPP
#define BonOaNlpOptim_HPP
#include "CglCutGenerator.hpp"
#include "BonOsiTMINLPInterface.hpp"
#include "BonOAMessages.hpp"
#include "BonBabSetupBase.hpp"
namespace Bonmin
{
  /** Generate cuts for the nlp corresponding to continuous relaxation at a node.*/
  class BONMINLIB_EXPORT OaNlpOptim : public CglCutGenerator
  {
  public:
    /// Default constructor
    OaNlpOptim(OsiTMINLPInterface * si = NULL,
        int maxDepth = 10, bool addOnlyViolated = false,
        bool globalCuts = true);

    /// Constructor with basic setup
    OaNlpOptim(BabSetupBase &b);
    /// Copy constructor
    OaNlpOptim(const OaNlpOptim &copy)
        :
        CglCutGenerator(copy),
        nlp_(copy.nlp_),
        maxDepth_(copy.maxDepth_),
        nSolve_(0),
        addOnlyViolated_(copy.addOnlyViolated_),
        global_(copy.global_),
	solves_per_level_(copy.solves_per_level_)
    {
      handler_ = new CoinMessageHandler();
      handler_ -> setLogLevel(copy.handler_->logLevel());
      messages_ = OaMessages();
    }
    void passInMessageHandler(const CoinMessageHandler * handler)
    {
      delete handler_;
      handler_ = handler->clone();
    }
    ///Abstract constructor
    virtual CglCutGenerator * clone() const
    {
      return new OaNlpOptim(*this);
    }

    /** Desctructor */
    virtual ~OaNlpOptim()
    {
      if (handler_)
        delete handler_;
    }

    /// Assign an OsiTMINLPInterface
    void assignInterface(OsiTMINLPInterface * si);
    /// cut generation method
    virtual void generateCuts( const OsiSolverInterface & si, OsiCuts & cs,
        const CglTreeInfo info);



    inline void setMaxDepth(int value)
    {
      maxDepth_ = value;
    }
    inline void setAddOnlyViolated(bool yesno)
    {
      addOnlyViolated_ = yesno;
    }
    inline void setGlobalCuts(bool yesno)
    {
      global_ = yesno;
    }
    inline int getNSolve()
    {
      return nSolve_;
    }
    /**set log level */
    void setLogLevel(int value)
    {
      handler_->setLogLevel(value);
    }

    /** Register OaNlpOptim options.*/
    static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

  private:
    /// Pointer to the Ipopt interface
    OsiTMINLPInterface * nlp_;

    /** maximum depth at which generate cuts*/
    int maxDepth_;

    ///Number of NLP resolution done
    mutable int nSolve_;
    /** messages handler. */
    CoinMessageHandler * handler_;
    /** handler */
    CoinMessages messages_;
    /** Add only violated cuts?*/
    bool addOnlyViolated_;
    /** Add cuts as global?*/
    bool global_;
    /** Average number of nodes per level in tree */
    double solves_per_level_;
  };
}
#endif
