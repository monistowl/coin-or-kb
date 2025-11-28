/*===========================================================================*
 * This file is part of the Discrete Conic Optimization (DisCO) Solver.      *
 *                                                                           *
 * DisCO is distributed under the Eclipse Public License as part of the      *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *          Aykut Bulut, Lehigh University                                   *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Copyright (C) 2001-2018, Lehigh University, Aykut Bulut, Yan Xu, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

/**
 * @file DcoConicConGenerator.hpp
 * @brief Wrapper for conic outer approximation cut generators
 *
 * DcoConicConGenerator wraps CglConicCutGenerator to generate linear
 * cuts that approximate conic constraints (Outer Approximation).
 *
 * **Conic Cut Types (DcoConicCutType):**
 * - IPM: Interior point method based
 * - IPMInt: Integer-aware IPM cuts
 * - OA: Standard outer approximation
 * - MIR: Conic MIR cuts
 * - GD1: Gradient descent cuts
 *
 * **OA Algorithm:**
 * For a Lorentz cone ||x|| <= t, generate linear supports:
 * - At current solution point x*, generate tangent hyperplane
 * - a'x <= b where (a,b) defines supporting hyperplane
 *
 * **generateConstraints() Flow:**
 * 1. Call CglConicCutGenerator::generateCuts()
 * 2. Convert OsiConicCuts to DcoLinearConstraint objects
 * 3. Add to BcpsConstraintPool
 *
 * @see DcoConGenerator.hpp for base class
 * @see DcoLinearConGenerator.hpp for MILP cuts
 * @see DcoConicConstraint.hpp for conic constraint storage
 */

#ifndef DcoConicConGenerator_hpp_
#define DcoConicConGenerator_hpp_

#include "DcoConGenerator.hpp"

class CglConicCutGenerator;

class DcoConicConGenerator: virtual public DcoConGenerator {
  /// The CglCutGenerator object.
  CglConicCutGenerator * generator_;
public:
  ///@name Constructors and Destructor
  //@{
  /// Useful constructor.
  DcoConicConGenerator(DcoModel * model,
                       CglConicCutGenerator * generator,
                       DcoConstraintType type,
                       char const * name = NULL,
                       DcoCutStrategy strategy = DcoCutStrategyAuto,
                       int frequency = 1);
  /// Destructor.
  virtual ~DcoConicConGenerator();
  //@}


  ///@name Constraint generator functions
  //@{
  /// Generate constraints and add them to the pool.
  bool generateConstraints(BcpsConstraintPool & conPool);
  //@}

  // Get cut generator.
  CglConicCutGenerator const * generator() const { return generator_; }
private:
  /// Disable default constructor
  DcoConicConGenerator();
  /// Disable copy constructor.
  DcoConicConGenerator(DcoConicConGenerator const & other);
  /// Disable copy assignment operator.
  DcoConicConGenerator & operator=(DcoConicConGenerator const & rhs);
};

#endif
