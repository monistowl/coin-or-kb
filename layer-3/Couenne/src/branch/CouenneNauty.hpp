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
 * **Nauty integration:**
 * The problem is represented as a graph where:
 * - Nodes: Variables and constraints
 * - Edges: Connections based on problem structure
 * Nauty computes the automorphism group of this graph.
 *
 * **Key methods:**
 * - addElement(): Add edge to graph
 * - computeAuto(): Compute automorphism group
 * - getOrbits(): Get variable orbits (symmetry equivalence classes)
 * - getGroupSize(): Size of symmetry group
 * - getNumGenerators(): Number of group generators
 *
 * **Coloring (VarStatus):**
 * - FIX_AT_ZERO, FIX_AT_ONE, FREE: Variable status for partitioning
 * - color_node(): Assign color to node for refined symmetry
 *
 * **Performance tracking:**
 * - nautyCalls_: Number of calls to nauty
 * - nautyTime_: Time spent in nauty computations
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
