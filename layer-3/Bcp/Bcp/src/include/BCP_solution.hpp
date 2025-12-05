// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file BCP_solution.hpp
 * @brief Solution representation for BCP Branch-Cut-Price
 *
 * @algorithm MIP Solution Storage and Upper Bound Tracking
 *
 * Defines how MIP feasible solutions are stored and transmitted:
 *
 * **Class hierarchy:**
 * - BCP_solution: Abstract base with objective_value() pure virtual
 * - BCP_solution_generic: Default implementation storing (var, value) pairs
 *
 * **BCP_solution_generic:**
 * - _objective: Objective function value
 * - _vars: Vector of variables at nonzero level
 * - _values: Corresponding values
 * - _delete_vars: Whether to delete vars on destruction
 *
 * **Usage flow:**
 * 1. LP process finds integer feasible solution
 * 2. BCP_lp_user::pack_feasible_solution() serializes it
 * 3. Sent to Tree Manager
 * 4. BCP_tm_user::unpack_feasible_solution() deserializes
 * 5. Best solution tracked for upper bound
 *
 * Users can derive from BCP_solution for custom solution
 * storage (e.g., to include dual values).
 *
 * @see BCP_lp_user for packing interface
 * @see BCP_tm_user for unpacking interface
 */

#ifndef _BCP_SOLUTION_H
#define _BCP_SOLUTION_H

#include "BCP_vector.hpp"
#include "BCP_var.hpp"

// This file is fully docified.

/** This is the abstract base class for a solution to a Mixed Integer
    Programming problem. */

class BCP_solution {
public:
  /** The virtual destructor ensures that the correct destructor is invoked. */
  virtual ~BCP_solution() {}
  /** The method returning the objective value of the solution. */
  virtual double objective_value() const = 0;
};

//#############################################################################

/** This class holds a MIP feasible primal solution. 

    The default BCP_lp_user::pack_feasible_solution() uses this class to pack
    an MIP feasible solution, but the user can use this class (instead of
    using BCP_solution as a base class
    to derive a different solution holder. (This might be necessary if, for
    example, the dual values are of importance as well.) The virtual
    destructor and virtual member functions make this easy. */

class BCP_solution_generic : public BCP_solution { 
public:
  /**@name Data members */
  /*@{*/
    /** The objective value of the solution. */
    double _objective;
    /** An indicator to show whether the pointers in \c _vars should be
	deleted upon destruction or not. By default they are not. */
    bool _delete_vars;
    /** Vector of variables that are at nonzero level in the solution. */
    BCP_vec<BCP_var*> _vars;
    /** Values of these variables in the solution. */
    BCP_vec<double> _values;
  /*@}*/

public:
  /** The default constructor creates a solution with zero objective value. */ 
  BCP_solution_generic(bool delvars = true) :
     _objective(0), _delete_vars(delvars), _vars(), _values() {}
  /** The destructor deletes the data members. Note that it purges
      \c _vars (i.e., deletes the variables the pointers
      in \c _vars point to) only if the \c _delete_vars member is true. */
  virtual ~BCP_solution_generic() {
     if (_delete_vars)
	purge_ptr_vector(_vars);
  }

  /** Return the objective value of the solution. */
  inline virtual double objective_value() const { return _objective; }

  /** Set the objective value of the solution. */
  inline void set_objective_value(double v) { _objective = v; }

  /** Display the solution. */
  void display() const;

  /** Append a variable and the corresponding value to the end of the
      appropriate vectors. This method is used when unpacking the solution. */
  void add_entry(BCP_var* var, double value) {
    _vars.push_back(var);
    _values.push_back(value);
    _objective += value * var->obj();
  }
};

#endif
