// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CglLiftAndProject.hpp
 * @brief Lift-and-project cuts for 0-1 programming
 *
 * Implements lift-and-project cuts based on Balas, Ceria, and Cornuejols.
 * Creates cuts by "lifting" the problem into higher dimensions where
 * the LP relaxation is tighter, then "projecting" back.
 *
 * @algorithm Lift-and-Project Cut Generation (Balas):
 *   Generates cuts from simple disjunctions x_j ∈ {0,1}:
 *   1. For fractional x_j*, consider disjunction (x_j=0) ∨ (x_j=1)
 *   2. Lift: Create extended formulation in higher dimension
 *      - Variables: (x⁰,x¹,λ) where x = λx¹ + (1-λ)x⁰
 *      - Constraints: Ax⁰ ≤ b, Ax¹ ≤ b, x⁰_j = 0, x¹_j = 1, λ ∈ [0,1]
 *   3. Optimize: Find deepest cut separating x* from lifted polytope
 *      max (α'x* - β) s.t. α'x ≤ β valid for lifted set
 *   4. Project: Cut α'x ≤ β is valid in original space
 *
 * @math Lift-and-project formulation (Balas, Ceria, Cornuéjols 1993):
 *   P = {x : Ax ≤ b, 0 ≤ x ≤ 1}
 *   Disjunction D_j: (x_j = 0) ∨ (x_j = 1)
 *   Lifted set: conv(P ∩ D_j) via higher-dimensional representation
 *   Normalization: β = ±1 (parameter) determines cut family
 *
 * @complexity O(n³) per cut for solving the LP in lifted space.
 *   Each disjunction variable requires a separate LP solve.
 *   Computationally expensive; typically limited to root node.
 *
 * @ref Balas, Ceria, Cornuéjols (1993). "A lift-and-project cutting plane
 *      algorithm for mixed 0-1 programs". Math. Programming 58:295-324.
 *
 * For a disjunction x_j = 0 OR x_j = 1:
 * - Create two copies of constraints: one with x_j=0, one with x_j=1
 * - Convexify the union of these two polyhedra
 * - Project back to original space
 * - The projection gives a valid cut
 *
 * Normalization:
 * - beta_ = +1 or -1 controls the normalization constraint
 * - Choice affects which cuts are generated
 *
 * This is a foundational method - computationally expensive but
 * theoretically powerful. Modern implementations often use
 * specialized variants like split cuts.
 *
 * @see CglLandP for related Lift-and-Project implementation (Bonami)
 * @see CglGomory which can be viewed as a special case
 */

#ifndef CglLiftAndProject_H
#define CglLiftAndProject_H

#include <string>

#include "CglCutGenerator.hpp"

/** Lift And Project Cut Generator Class */
class CGLLIB_EXPORT CglLiftAndProject : public CglCutGenerator {
   friend CGLLIB_EXPORT void CglLiftAndProjectUnitTest(const OsiSolverInterface * siP,
					const std::string mpdDir );

public:
  /**@name Generate Cuts */
  //@{
  /** Generate lift-and-project cuts for the 
      model of the solver interface, si. 
      Insert the generated cuts into OsiCut, cs.
  */
  virtual void generateCuts(const OsiSolverInterface & si, OsiCuts & cs,
			    const CglTreeInfo info = CglTreeInfo());

  /** Get the normalization : Either beta=+1 or beta=-1.
  */

  double getBeta() const {
    return beta_;
  }

  /** Set the normalization : Either beta=+1 or beta=-1.
      Default value is 1.
  */
  void setBeta(int oneOrMinusOne){
    if (oneOrMinusOne==1 || oneOrMinusOne==-1){
      beta_= static_cast<double>(oneOrMinusOne);
    }
    else {
      throw CoinError("Unallowable value. Beta must be 1 or -1",
		      "cutGeneration","CglLiftAndProject");
    }
  }

  //@}

  /**@name Constructors and destructors */
  //@{
  /// Default constructor 
  CglLiftAndProject ();
 
  /// Copy constructor 
  CglLiftAndProject (
    const CglLiftAndProject &);

  /// Clone
  virtual CglCutGenerator * clone() const;

  /// Assignment operator 
  CglLiftAndProject &
    operator=(
    const CglLiftAndProject& rhs);
  
  /// Destructor 
  virtual
    ~CglLiftAndProject ();
  /// Create C++ lines to get to current state
  virtual std::string generateCpp( FILE * fp);
  //@}

private:
  
 // Private member methods

  /**@name Private methods */
  //@{

  //@}

  // Private member data

  /**@name Private member data */
  //@{
  /// The normalization is beta_=1 or beta_=-1
  double beta_;  
  /// epsilon
  double epsilon_;  
  /// 1-epsilon
  double onetol_;  
  //@}
};

//#############################################################################
/** A function that tests the methods in the CglLiftAndProject class. The
    only reason for it not to be a member method is that this way it doesn't
    have to be compiled into the library. And that's a gain, because the
    library should be compiled with optimization on, but this method should be
    compiled with debugging. */
CGLLIB_EXPORT
void CglLiftAndProjectUnitTest(const OsiSolverInterface * siP,
			      const std::string mpdDir );
  
#endif
