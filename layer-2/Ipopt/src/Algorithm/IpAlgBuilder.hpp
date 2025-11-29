// Copyright (C) 2004, 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-09-29

/**
 * @file IpAlgBuilder.hpp
 * @brief Builder pattern for constructing configured IpoptAlgorithm
 *
 * AlgorithmBuilder assembles a complete IpoptAlgorithm from components
 * based on user options. This implements the Builder design pattern,
 * centralizing the complex construction logic.
 *
 * Build order (with dependency chain):
 * 1. SymLinearSolver (MA27/57/77/86/97, MUMPS, Pardiso, WSMP, etc.)
 * 2. AugSystemSolver (wraps SymLinearSolver for augmented system)
 * 3. PDSystemSolver (solves full primal-dual system)
 * 4. SearchDirectionCalculator, EqMultiplierCalculator
 * 5. IterateInitializer, LineSearch, MuUpdate, ConvergenceCheck
 *
 * Customization: Subclass and override virtual Build* methods,
 * or provide custom_solver in constructor.
 *
 * @algorithm Primal-Dual Interior Point Method (assembled algorithm):
 *   Solves NLP: min f(x) s.t. c(x)=0, x >= 0
 *   @math Perturbed KKT system (barrier with parameter μ):
 *     ∇f - A'y - z = 0  (stationarity)
 *     c(x) = 0          (primal feasibility)
 *     XZe = μe          (complementarity)
 *     x,z >= 0          (bounds)
 *   Each iteration solves the Newton system for (Δx, Δy, Δz).
 *
 * @algorithm Augmented System Formulation (AugSystemSolver):
 *   Reduce the full (n+m+n) system to symmetric (n+m) system:
 *   @math [W + Σ  A'] [Δx]   [r_x]
 *         [A      0 ] [Δy] = [r_c]
 *   where W = ∇²L (Hessian of Lagrangian), Σ = X⁻¹Z (diagonal),
 *   A = ∇c(x)' (Jacobian). Solve via sparse symmetric factorization.
 *   @ref Nocedal, J. and Wright, S.J. (2006). "Numerical Optimization".
 *        Springer, Chapter 19 (Interior-Point Methods).
 *
 * @algorithm Barrier Parameter Update (MuUpdate):
 *   - Monotone (Fiacco-McCormick): μ_{k+1} = σ * μ_k with σ < 1
 *   - Adaptive: Quality function or probing oracle to choose μ
 *   - Mehrotra predictor-corrector: Probe with affine step to set μ
 *   @ref Fiacco, A.V. and McCormick, G.P. (1968). "Nonlinear Programming:
 *        Sequential Unconstrained Minimization Techniques". Wiley.
 *   @ref Mehrotra, S. (1992). "On the implementation of a primal-dual
 *        interior point method". SIAM J. Optimization 2(4):575-601.
 *
 * @algorithm Filter Line Search (LineSearch):
 *   Globalization via filter method with restoration phase:
 *   1. Backtrack until (θ, φ) acceptable to filter (θ=infeasibility, φ=objective)
 *   2. If no acceptable point found, enter restoration phase (minimize θ)
 *   3. On success, add (θ, φ) to filter to prevent cycling
 *   @ref Wächter, A. and Biegler, L.T. (2006). "On the implementation
 *        of an interior-point filter line-search algorithm for large-scale
 *        nonlinear programming". Math. Programming 106(1):25-57.
 *
 * @algorithm Linear Solver Selection (SymLinearSolverFactory):
 *   HSL solvers (preferred): MA27/57 (multifrontal), MA77/86/97 (out-of-core)
 *   Alternatives: MUMPS (parallel), Pardiso (MKL/project), WSMP, SPRAL
 *   Key requirement: handle indefinite symmetric matrices with inertia detection.
 *
 * @complexity Per iteration: O(n³) for dense, O(nnz^{1.5-2}) for sparse
 *   Total: O(iterations × linear_solve_cost) where iterations ~ O(√n) typical
 *
 * @see IpIpoptAlg.hpp for resulting algorithm
 * @see IpIpoptApplication.hpp for high-level usage
 */

#ifndef __IPALGBUILDER_HPP__
#define __IPALGBUILDER_HPP__

#include "IpIpoptAlg.hpp"
#include "IpReferenced.hpp"
#include "IpAugSystemSolver.hpp"
#include "IpPDSystemSolver.hpp"
#include "IpLibraryLoader.hpp"

namespace Ipopt
{

// forward declarations
class IterationOutput;
class HessianUpdater;
class ConvergenceCheck;
class SearchDirectionCalculator;
class EqMultiplierCalculator;
class IterateInitializer;
class LineSearch;
class MuUpdate;

/** Builder for creating a complete IpoptAlg object.
 *
 *  This object contains all subelements (such as line search objects
 *  etc).  How the resulting IpoptAlg object is built can be influenced
 *  by the options.
 *
 *  More advanced customization can be achieved by subclassing this
 *  class and overloading the virtual methods that build the
 *  individual parts. The advantage of doing this is that it allows
 *  one to reuse the extensive amount of options processing that
 *  takes place, for instance, when generating the symmetric linear
 *  system solver. Another method for customizing the algorithm is
 *  using the optional custom_solver argument, which allows the
 *  expert user to provide a specialized linear solver for the
 *  augmented system (e.g., type GenAugSystemSolver), possibly for
 *  user-defined matrix objects. The optional custom_solver constructor
 *  argument is likely obsolete, however, as more control over this
 *  this process can be achieved by implementing a subclass of this
 *  AlgBuilder (e.g., by overloading the AugSystemSolverFactory method).
 */
class IPOPTLIB_EXPORT AlgorithmBuilder: public ReferencedObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   AlgorithmBuilder(
      SmartPtr<AugSystemSolver> custom_solver = NULL,           /**< custom linear solver interface object */
      const std::string& custom_solver_name   = std::string()   /**< name of custom linear solver (since 3.14.12) */
   );

   /** Destructor */
   virtual ~AlgorithmBuilder()
   { }

   ///@}

   /** Methods for IpoptTypeInfo */
   ///@{
   /** register the options used by the algorithm builder */
   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );
   ///@}

   /** @name Convenience methods for building solvers without having
    *  to duplicate the significant amount of preprocessor flag and
    *  option checking that takes place. These solvers are used to
    *  create a number of core algorithm components across the
    *  different Build* methods, but depending on what options are
    *  chosen, the first method requiring the solver to be used can
    *  vary. Therefore, each of the Factory methods below is paired
    *  with a Getter method, which is called by all parts of this
    *  algorithm builder to ensure the Factory is only called once. */
   ///@{
   /** Create a solver that can be used to solve a symmetric linear
    *  system.
    *  Dependencies: None
    */
   virtual SmartPtr<SymLinearSolver> SymLinearSolverFactory(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Get the symmetric linear system solver for this
    *  algorithm. This method will call the SymLinearSolverFactory
    *  exactly once (the first time it is used), and store its
    *  instance on SymSolver_ for use in subsequent calls.
    */
   SmartPtr<SymLinearSolver> GetSymLinearSolver(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Create a solver that can be used to solve an
    *  augmented system.
    *  Dependencies:
    *     -> GetSymLinearSolver()
    *         -> SymLinearSolverFactory()
    *     -> custom_solver_
    */
   virtual SmartPtr<AugSystemSolver> AugSystemSolverFactory(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Get the augmented system solver for this algorithm. This
    *  method will call the AugSystemSolverFactory exactly once (the
    *  first time it is used), and store its instance on AugSolver_
    *  for use in subsequent calls.
    */
   SmartPtr<AugSystemSolver> GetAugSystemSolver(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Create a solver that can be used to solve a
    *  primal-dual system.
    *  Dependencies:
    *     -> GetAugSystemSolver()
    *         -> AugSystemSolverFactory()
    *             -> GetSymLinearSolver()
    *                 -> SymLinearSolverFactory()
    *             -> custom_solver_
    */
   virtual SmartPtr<PDSystemSolver> PDSystemSolverFactory(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Get the primal-dual system solver for this algorithm. This
    *  method will call the PDSystemSolverFactory exactly once (the
    *  first time it is used), and store its instance on PDSolver_
    *  for use in subsequent calls.
    */
   SmartPtr<PDSystemSolver> GetPDSystemSolver(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );
   ///@}

   /** @name Methods to build parts of the algorithm */
   ///@{
   /** Allocates memory for the IpoptNLP, IpoptData, and
    *  IpoptCalculatedQuanties arguments.
    *  Dependencies: None
    */
   virtual void BuildIpoptObjects(
      const Journalist&                    jnlst,
      const OptionsList&                   options,
      const std::string&                   prefix,
      const SmartPtr<NLP>&                 nlp,
      SmartPtr<IpoptNLP>&                  ip_nlp,
      SmartPtr<IpoptData>&                 ip_data,
      SmartPtr<IpoptCalculatedQuantities>& ip_cq
   );

   /** Creates an instance of the IpoptAlgorithm class by building
    *  each of its required constructor arguments piece-by-piece. The
    *  default algorithm can be customized by overloading this method
    *  or by overloading one or more of the Build* methods called in
    *  this method's default implementation. Additional control can
    *  be achieved by overloading any of the *SolverFactory methods.
    *  This method will call (in this order):
    *     -> BuildIterationOutput()
    *     -> BuildHessianUpdater()
    *     -> BuildConvergenceCheck()
    *     -> BuildSearchDirectionCalculator()
    *     -> BuildEqMultiplierCalculator()
    *     -> BuildIterateInitializer()
    *     -> BuildLineSearch()
    *     -> BuildMuUpdate()
    */
   virtual SmartPtr<IpoptAlgorithm> BuildBasicAlgorithm(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the IterationOutput class. This method
    *  is called in the default implementation of
    *  BuildBasicAlgorithm. It can be overloaded to customize that
    *  portion the default algorithm.
    *  Dependencies: None
    */
   virtual SmartPtr<IterationOutput> BuildIterationOutput(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the HessianUpdater class. This method
    *  is called in the default implementation of
    *  BuildBasicAlgorithm.  It can be overloaded to customize that
    *  portion the default algorithm.
    *  Dependencies: None
    */
   virtual SmartPtr<HessianUpdater> BuildHessianUpdater(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the ConvergenceCheck class. This method
    *  is called in the default implementation of
    *  BuildBasicAlgorithm.  It can be overloaded to customize that
    *  portion the default algorithm.
    *  Dependencies: None
    */
   virtual SmartPtr<ConvergenceCheck> BuildConvergenceCheck(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the SearchDirectionCalculator
    *  class. This method is called in the default implementation of
    *  BuildBasicAlgorithm.  It can be overloaded to customize that
    *  portion the default algorithm.
    *  Dependencies:
    *     -> GetPDSystemSolver()
    *         -> PDSystemSolverFactory()
    *             -> GetAugSystemSolver()
    *                 -> AugSystemSolverFactory()
    *                     -> GetSymLinearSolver()
    *                         -> SymLinearSolverFactory()
    *                     -> custom_solver_
    */
   virtual SmartPtr<SearchDirectionCalculator> BuildSearchDirectionCalculator(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the EqMultiplierCalculator class. This
    *  method is called in the default implementation of
    *  BuildBasicAlgorithm.  It can be overloaded to customize that
    *  portion the default algorithm.
    *  Dependencies:
    *     -> GetAugSystemSolver()
    *         -> AugSystemSolverFactory()
    *             -> GetSymLinearSolver()
    *                 -> SymLinearSolverFactory()
    *             -> custom_solver_
    */
   virtual SmartPtr<EqMultiplierCalculator> BuildEqMultiplierCalculator(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the IterateInitializer class. This
    *  method is called in the default implementation of
    *  BuildBasicAlgorithm.  It can be overloaded to customize that
    *  portion the default algorithm.
    *  Dependencies:
    *     -> EqMultCalculator_
    *     -> GetAugSystemSolver()
    *         -> AugSystemSolverFactory()
    *             -> GetSymLinearSolver()
    *                 -> SymLinearSolverFactory()
    *             -> custom_solver_
    */
   virtual SmartPtr<IterateInitializer> BuildIterateInitializer(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the LineSearch class. This method is
    *  called in the default implementation of BuildBasicAlgorithm.
    *  It can be overloaded to customize that portion the default
    *  algorithm.
    *  Dependencies:
    *     -> EqMultCalculator_
    *     -> ConvCheck_
    *     -> GetAugSystemSolver()
    *         -> AugSystemSolverFactory()
    *             -> GetSymLinearSolver()
    *                 -> SymLinearSolverFactory()
    *             -> custom_solver_
    *     -> GetPDSystemSolver()
    *         -> PDSystemSolverFactory()
    *             -> GetAugSystemSolver()
    *                 -> AugSystemSolverFactory()
    *                     -> GetSymLinearSolver()
    *                         -> SymLinearSolverFactory()
    *                     -> custom_solver_
    */
   virtual SmartPtr<LineSearch> BuildLineSearch(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );

   /** Creates an instance of the MuUpdate class. This method is
    *  called in the default implementation of BuildBasicAlgorithm.
    *  It can be overloaded to customize that portion the default
    *  algorithm.
    *  Dependencies:
    *     -> LineSearch_
    *         -> EqMultCalculator_
    *         -> ConvCheck_
    *     -> GetPDSystemSolver()
    *         -> PDSystemSolverFactory()
    *             -> GetAugSystemSolver()
    *                 -> AugSystemSolverFactory()
    *                     -> GetSymLinearSolver()
    *                         -> SymLinearSolverFactory()
    *                     -> custom_solver_
    */
   virtual SmartPtr<MuUpdate> BuildMuUpdate(
      const Journalist&  jnlst,
      const OptionsList& options,
      const std::string& prefix
   );
   ///@}

protected:
   /// Gives Library Loader for HSL library if not all HSL routines are linked in
   ///
   /// Creates new loader if not existing yet.
   /// @since 3.14.0
   SmartPtr<LibraryLoader> GetHSLLoader(
      const OptionsList& options,
      const std::string& prefix
   );

   /// Gives Library Loader for Pardiso library from pardiso-project.org.
   ///
   /// Creates new loader if not existing yet.
   /// @since 3.14.0
   SmartPtr<LibraryLoader> GetPardisoLoader(
      const OptionsList& options,
      const std::string& prefix
   );

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called. */
   ///@{
   /** Default Constructor */
   //AlgorithmBuilder();

   /** Copy Constructor */
   AlgorithmBuilder(
      const AlgorithmBuilder&
   );

   /** Default Assignment Operator */
   void operator=(
      const AlgorithmBuilder&
   );
   ///@}

   /** @name IpoptAlgorithm constructor arguments.
    *  These components are built in separate Build
    *  methods in the order defined by BuildBasicAlgorithm.
    *  A single core component may require one or more
    *  other core components in its constructor, so the
    *  this class holds pointers to each component for use
    *  between the separate Build methods. */
   ///@{
   SmartPtr<IterationOutput> IterOutput_;
   SmartPtr<HessianUpdater> HessUpdater_;
   SmartPtr<ConvergenceCheck> ConvCheck_;
   SmartPtr<SearchDirectionCalculator> SearchDirCalc_;
   SmartPtr<EqMultiplierCalculator> EqMultCalculator_;
   SmartPtr<IterateInitializer> IterInitializer_;
   SmartPtr<LineSearch> LineSearch_;
   SmartPtr<MuUpdate> MuUpdate_;
   ///@}

   /** @name Commonly used solver components
    *  for building core algorithm components. Each
    *  of these members is paired with a Factory/Getter
    *  method. */
   ///@{
   SmartPtr<SymLinearSolver> SymSolver_;
   SmartPtr<AugSystemSolver> AugSolver_;
   SmartPtr<PDSystemSolver> PDSolver_;
   ///@}

   /** Optional pointer to AugSystemSolver.  If this is set in the
    *  constructor, we will use this to solve the linear systems. */
   SmartPtr<AugSystemSolver> custom_solver_;
   std::string custom_solver_name_;

   /// name of linear solver constructed in SymLinearSolverFactory
   std::string linear_solver;

   /// loader of HSL library (at runtime)
   SmartPtr<LibraryLoader> hslloader;
   /// loader of Pardiso library (at runtime)
   SmartPtr<LibraryLoader> pardisoloader;

};
} // namespace Ipopt

#endif
