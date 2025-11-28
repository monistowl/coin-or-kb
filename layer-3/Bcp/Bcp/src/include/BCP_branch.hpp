// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file BCP_branch.hpp
 * @brief Internal branching object for BCP Branch-Cut-Price
 *
 * Represents the result of a branching decision as bound changes
 * on variables and cuts across children nodes.
 *
 * **BCP_internal_brobj:**
 * Created AFTER any cuts/variables from branching are added.
 * Stores only bound changes, not the branching object itself.
 *
 * **Data structure:**
 * - _child_num: Number of children (typically 2 for binary branching)
 * - _var_positions: Indices of variables with changed bounds
 * - _cut_positions: Indices of cuts with changed bounds
 * - _var_bounds: New [lb, ub] pairs for each child × each affected var
 * - _cut_bounds: New [lb, ub] pairs for each child × each affected cut
 *
 * **Memory layout:**
 * Bounds are stored as: child0_var0_lb, child0_var0_ub, child0_var1_lb, ...
 * then child1_var0_lb, child1_var0_ub, ...
 * Total length: 2 × child_num × var_positions.size()
 *
 * **Usage:**
 * - apply_child_bounds(): Modify LP solver for child's bounds
 * - pack()/unpack(): Serialize for sending to TM
 *
 * @see BCP_lp_branch.hpp for LP-side branching object
 * @see BCP_enum_branch.hpp for branching enumerations
 * @see BCP_lp_user::select_branching_candidates() for branching logic
 */

#ifndef _BCP_BRANCH_H
#define _BCP_BRANCH_H

// This file is fully docified.

#include "BCP_vector.hpp"

class OsiSolverInterface;
class BCP_buffer;
class BCP_lp_branching_object;

//#############################################################################

/**
   This class is the internal representation of a branching object. We
   document it only for the sake of completness, the user need not worry about
   it.

   An internal branching object is created AFTER all the cuts/variables the
   branching object wanted to add the relaxation are already added, thus only
   the bound changes on affected variables are specified.

   NOTE: There are only two ways to set up an internal branching object. One
   is through a constructor that passes on the data members, the second is to
   set it up with the default constructor then unpack its content from a
   buffer.
*/

class BCP_internal_brobj {
private:
   /**@name Disabled methods */
   /*@{*/
   /** The copy constructor is declared but not defined to disable it. */
   BCP_internal_brobj(const BCP_internal_brobj&);
   /** The assignment operator is declared but not defined to disable it. */
   BCP_internal_brobj& operator=(const BCP_internal_brobj&);
   /*@}*/
   
private:
   /**@name Data members */
   /*@{*/
   /** The number of children in the branching object. */
   int _child_num;
   /** The positions of variables whose bounds are affected by the branching.
       Affected means that in at least one child the lower and/or upper bound
       of the variable changes. */ 
   BCP_vec<int> _var_positions;
   /** The positions of cuts whose bounds are affected by the branching. */
   BCP_vec<int> _cut_positions;
   /** Lower/upper bound pairs for the variables affected by the branching.
       The bound pairs are listed in the first child for all the affected
       variables, then the same data for the second child, etc. Thus the
       vector is of length <code>2*_child_num *_var_positions.size()</code>. */
   BCP_vec<double> _var_bounds; // 2*_child_num*_var_positions.size()
   /** Lower/upper bound pairs for the cuts affected by the branching. */
   BCP_vec<double> _cut_bounds;
   /*@}*/

public:
   /**@name Constructors and destructor */
   /*@{*/
   /** The default constructor creates an empty internal branching object
       (which can be filled later by unpacking a buffer). */
   BCP_internal_brobj() : _child_num(0),
      _var_positions(), _cut_positions(), _var_bounds(), _cut_bounds() {}
   /** This constructor sets the number of children and copies the contents of
       the positions and bounds of the forced changes to the positions and
       bounds of the newly created internal branching object. */
   BCP_internal_brobj(BCP_lp_branching_object& candidate);
   /** The desctructor deletes all data members. */
   ~BCP_internal_brobj() {}
   /*@}*/

   /**@name Query methods */
   /*@{*/
   /** Return the number of children. */
   inline int child_num() const { return _child_num; }
   /** Return the number of affected variables. */
   inline int affected_varnum() const { return _var_positions.size(); }
   /** Return the number of affected cuts. */
   inline int affected_cutnum() const { return _cut_positions.size(); }

   /** Return a <code>const</code> reference to the vector of positions of
       variables affected by the branching. */
   inline const BCP_vec<int>& var_positions() const { return _var_positions; }
   /** Return a <code>const</code> reference to the vector of positions of
       cuts affected by the branching. */
   inline const BCP_vec<int>& cut_positions() const { return _cut_positions; }

   /** Return a <code>const</code> iterator within <code>_var_bounds</code> to
       the location where the bound pairs for the <code>index</code>-th child
       start. */
   inline
   BCP_vec<double>::const_iterator var_bounds_child(const int index) const {
      return _var_bounds.entry(2 * _var_positions.size() * index);
   }
   /** Return a <code>const</code> iterator within <code>_cut_bounds</code> to
       the location where the bound pairs for the <code>index</code>-th child
       start. */
   inline
   BCP_vec<double>::const_iterator cut_bounds_child(const int index) const {
      return _cut_bounds.entry(2 * _cut_positions.size() * index);
   }
   /*@}*/

   /**@name Interaction with the LP solver */
   /*@{*/
   /** Modify the bounds in the LP solver by applying the changes specified for
       the <code>child_ind</code>-th child. */
   void apply_child_bounds(OsiSolverInterface* lp, int child_ind) const;
   /*@}*/

   /**@name Packing and unpacking */
   /*@{*/
   /** Pack the internal branching object into the buffer. */
   void pack(BCP_buffer& buf) const;
   /** Unpack an internal branching object from the buffer. */
   void unpack(BCP_buffer& buf);
   /*@}*/
};

#endif

