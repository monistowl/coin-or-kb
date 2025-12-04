/*
 *
 * Name:    CouenneNauty.hpp
 * Authors: Jim Ostrowski
 * Purpose: Branching with symmetry
 * Date:    October 13, 2010
 *
 * This file is licensed under the Common Public License (CPL)
 */

/**
 * @file CouenneNauty.hpp
 * @brief Interface to nauty library for symmetry detection
 *
 * Wraps the nauty graph automorphism library to detect symmetries
 * in MINLP problems. Symmetry information enables orbital branching
 * and isomorphism pruning to reduce the search space.
 *
 * @algorithm Graph-Based Symmetry Detection (nauty):
 *   Detects problem symmetries by computing graph automorphisms:
 *   1. **Graph construction:** Build colored graph G from MINLP:
 *      - Nodes: Variables (colored by type/bounds) + constraints (colored by type)
 *      - Edges: Variable i appears in constraint j → edge (v_i, c_j)
 *   2. **Partition refinement:** color_node() partitions by variable status
 *      - Fixed variables form singleton cells
 *      - Free variables may be permuted within same orbit
 *   3. **Automorphism computation:** nauty computes Aut(G)
 *      - Returns generators of symmetry group
 *      - Orbits = equivalence classes of variables under Aut(G)
 *   4. **Application:** Orbits enable orbital branching and pruning
 *
 * @math Automorphism group:
 *   Aut(G) = {π : V → V | π(E) = E and π preserves colors}
 *   Orbit of v: Orb(v) = {π(v) : π ∈ Aut(G)}
 *   |Aut(G)| can be exponentially large, stored via generators
 *
 * @complexity O(n!) worst case, but practical: O(n²) for most graphs.
 *   nauty uses canonical labeling with partition backtracking.
 *   Preprocessing: Build graph O(nnz). Memory: O(n² + |generators|).
 *
 * @ref McKay & Piperno (2014). "Practical graph isomorphism, II".
 *      J. Symbolic Computation 60:94-112.
 *
 * **Coloring (VarStatus):**
 * - FIX_AT_ZERO, FIX_AT_ONE, FREE: Variable status for partitioning
 * - color_node(): Assign color to node for refined symmetry
 *
 * @see CouenneOrbitObj for orbital branching objects
 * @see CouenneOrbitBranchingObj for orbital branch execution
 */
#ifndef COUENNENAUTY_HPP
#define COUENNENAUTY_HPP

#include "CouenneConfig.h"

extern "C" {
#include "nauty/nauty.h"
}

#include <cstdio>
#include <map>
#include <vector>
#include <string>

class COUENNELIB_EXPORT Nauty
{

public:
  enum VarStatus { FIX_AT_ZERO, FIX_AT_ONE, FREE };

  Nauty(int n_);
  ~Nauty();

  void addElement(int ix, int jx);
  void clearPartitions();
  void computeAuto();
  void deleteElement(int ix, int jx);
  void color_node(int ix, int color) { vstat_[ix] = color; }
  void insertRHS(int rhs , int cons) {constr_rhs.insert( std::pair<int,int>(rhs,cons));}

  double getGroupSize() const;
  int getNautyCalls() const { return nautyCalls_; }
  double getNautyTime() const { return nautyTime_; }

  int getN() const { return n_; }

  int getNumGenerators() const;
  int getNumOrbits() const;

  /// Returns the orbits in a "convenient" form
  std::vector<std::vector<int> > *getOrbits() const;

  void getVstat(double *v, int nv);

  /**
   * Methods to classify orbits.  Not horribly efficient, but gets the job done
   */
  //  bool isAllFixOneOrbit(const std::vector<int> &orbit) const;
  // bool isAllFreeOrbit(const std::vector<int> &orbit) const;
  //bool isAutoComputed() const { return autoComputed_; }
  //bool isConstraintOrbit(const std::vector<int> &orbit) const;
  //bool isMixedFreeZeroOrbit(const std::vector<int> &orbit) const;
  //void makeFree(int ix) { vstat_[ix] = FREE; }

  void setWriteAutoms (const std::string &afilename);
  void unsetWriteAutoms();

private:

  Nauty ();

  // The base nauty stuff
  graph *G_;
  int *lab_;
  int *ptn_;
  set *active_;
  int *orbits_;
  optionblk *options_;
  statsblk *stats_;
  setword *workspace_;
  int worksize_;
  int m_;
  int n_;
  graph *canonG_;

  bool autoComputed_;

  int *vstat_;

  static int nautyCalls_;
  static double nautyTime_;

  std::multimap<int,int> constr_rhs;
  std::multimap<int,int>::iterator it;

  std::pair<std::multimap<int,int>::iterator,
            std::multimap<int,int>::iterator> ret;

  // File pointer for automorphism group
  FILE *afp_;

};

#endif
