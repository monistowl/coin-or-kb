// Copyright (C) 2010, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CglZeroHalf.hpp
 * @brief Zero-half ({0,1/2}) cutting planes
 *
 * Generates {0,1/2}-cuts by taking mod-2 combinations of constraint rows.
 * Based on Andreello, Caprara, Fischetti (INFORMS J. Computing, 2007).
 *
 * Theory: If we combine constraints with {0, 1/2} multipliers such that
 * all LHS coefficients become even, we get a valid cut by dividing by 2
 * and rounding down the RHS.
 *
 * Algorithm outline:
 * 1. Convert constraint matrix to integers (scaling)
 * 2. Reduce coefficients mod 2 (0-1 matrix)
 * 3. Find combinations where LHS sums to 0 mod 2 per column
 * 4. These yield valid {0,1/2}-cuts when RHS is odd
 *
 * Internal representation:
 * - mr_, mc_, mnz_: Matrix dimensions and nonzeros
 * - mtbeg_, mtcnt_, mtind_, mtval_: Sparse row storage
 * - vlb_, vub_: Variable bounds (integer scaled)
 * - Cgl012Cut cutInfo_: Separation algorithm state
 *
 * Uses Dijkstra shortest path (cglShortestPath) for separation.
 *
 * @algorithm {0,1/2}-Chvátal-Gomory Cuts via Mod-2 Separation:
 * Working over GF(2), find row combinations that zero out LHS coefficients:
 * 1. Scale and round matrix to integers
 * 2. Reduce all coefficients mod 2 → binary (0-1) matrix A'
 * 3. Find subset S of rows where Σ_{i∈S} A'_{ij} ≡ 0 (mod 2) for all j
 * 4. If Σ_{i∈S} b_i is odd → valid cut: (1/2)Σ_{i∈S} (a_i x ≤ b_i)
 *    becomes Σ_{i∈S} ⌊a_ij/2⌋ x_j ≤ ⌊(Σb_i)/2⌋
 *
 * @math The validity comes from Chvátal-Gomory closure theory:
 * Given Ax ≤ b, x ≥ 0 integer, any combination uᵀA with u ∈ {0, 1/2}ᵐ
 * where uᵀA is integral gives valid inequality: ⌊uᵀA⌋x ≤ ⌊uᵀb⌋
 *
 * The separation problem reduces to finding odd cycles in an auxiliary
 * graph, solved via shortest-path algorithms. The graph encodes:
 * - Nodes: variables and their complements
 * - Edges: constraints linking variable parities
 *
 * @complexity Separation via shortest path: O(V + E log V) per source.
 * Graph construction: O(m·n) where m = rows, n = columns.
 * Heuristic enumeration may be polynomial in practice.
 *
 * @ref Andreello, Caprara & Fischetti (2007). "Embedding Cuts in a Branch
 *   and Cut Framework: a Computational Study with {0,1/2}-Cuts".
 *   INFORMS J. Computing 19(2):229-238. [Implementation reference]
 * @ref Caprara & Fischetti (1996). "{0,1/2}-Chvátal-Gomory Cuts".
 *   Mathematical Programming 74:221-235. [Theory foundation]
 *
 * @see Cgl012cut.hpp for internal separation machinery
 * @see CglGomory for related MIP cutting plane approach
 */

#ifndef CglZeroHalf_H
#define CglZeroHalf_H

#include <string>

#include "CglCutGenerator.hpp"
#include "CoinPackedMatrix.hpp"
#include "Cgl012cut.hpp" 

/** Zero Half Cut Generator Class

 This class generates zero half cuts via the following method:

 See - 

G. Andreello, A. Caprara, M. Fischetti,
 “Embedding Cuts in a Branch and Cut Framework: a Computational Study 
  with {0,1/2}-Cuts”, INFORMS Journal on Computing 19(2), 229-238, 2007.
 
*/

class CGLLIB_EXPORT CglZeroHalf : public CglCutGenerator {
   friend CGLLIB_EXPORT void CglZeroHalfUnitTest(const OsiSolverInterface * siP,
					 const std::string mpdDir );
 
public:

  /**@name Generate Cuts */
  //@{
  /** Generate zero half cuts for the model accessed through the solver interface. 
  Insert generated cuts into the cut set cs.
  */
  virtual void generateCuts( const OsiSolverInterface & si, OsiCuts & cs,
			     const CglTreeInfo info = CglTreeInfo());
  //@}

  /**@name Sets and Gets */
  //@{
  /// Get flags
  inline int getFlags() const
  { return flags_;}
  /// Set flags
  inline void setFlags(int value)
  { flags_ = value;}
  //@}

  /**@name Constructors and destructors */
  //@{
  /// Default constructor 
  CglZeroHalf ();
 
  /// Copy constructor 
  CglZeroHalf (
    const CglZeroHalf &);

  /// Clone
  virtual CglCutGenerator * clone() const;

  /// Assignment operator 
  CglZeroHalf &
    operator=(
    const CglZeroHalf& rhs);
  
  /// Destructor 
  virtual
    ~CglZeroHalf ();
  /// Create C++ lines to get to current state
  virtual std::string generateCpp( FILE * fp);
  /// This can be used to refresh any information
  virtual void refreshSolver(OsiSolverInterface * solver);
  //@}

private:
  
  // Private member methods
   
  /**@name Private methods */
  //@{
  //@}
  
  
  /**@name Private member data */
  //@{
  /// number of rows in the ILP matrix 
  int mr_;
  /// number of columns in the ILP matrix 
  int mc_;
  /// number of nonzero's in the ILP matrix 
  int mnz_;
  /// starting position of each row in arrays mtind and mtval 
  int *mtbeg_;
  /// number of entries of each row in arrays mtind and mtval 
  int *mtcnt_;
  /// column indices of the nonzero entries of the ILP matrix 
  int *mtind_;
  /// values of the nonzero entries of the ILP matrix 
  int *mtval_;
  /// lower bounds on the variables 
  int *vlb_;
  /// upper bounds on the variables 
  int *vub_;
  /// right hand sides of the constraints 
  int *mrhs_;
  /// senses of the constraints: 'L', 'G' or 'E' 
  char *msense_;
  /// Cgl012Cut object to make thread safe
  Cgl012Cut cutInfo_;
  /** Flags
      1 bit - global cuts 
  */
  int flags_;
  //@}
};
/// A simple Dijkstra shortest path - make better later
CGLLIB_EXPORT
#ifndef CGL_NEW_SHORT
void cglShortestPath(cgl_graph * graph, int source, int maximumLength);
#else
void cglShortestPath(auxiliary_graph * graph, int source, int maximumLength);
#endif
//#############################################################################
/** A function that tests the methods in the CglZeroHalf class. The
    only reason for it not to be a member method is that this way it doesn't
    have to be compiled into the library. And that's a gain, because the
    library should be compiled with optimization on, but this method should be
    compiled with debugging. */
CGLLIB_EXPORT
void CglZeroHalfUnitTest(const OsiSolverInterface * siP,
			       const std::string mpdDir );
  
#endif
