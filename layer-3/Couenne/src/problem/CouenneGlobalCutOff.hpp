/*
 *
 * Name:    CouenneGlobalCutOff.hpp
 * Author:  Pietro Belotti, Lehigh University
 *          Andreas Waechter, IBM
 * Purpose: a cutoff that replicates itself
 *
 * (C) Carnegie-Mellon University, 2010.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneGlobalCutOff.hpp
 * @brief Global best solution and cutoff value storage
 *
 * Manages the incumbent (best known feasible solution) and its
 * objective value across the entire B&B search.
 *
 * **Role in B&B:**
 * - Provides cutoff value for pruning nodes
 * - Stores best solution found so far
 * - Updated when heuristics or B&B find improvements
 *
 * **Members:**
 * - cutoff_: Objective value of best solution (upper bound for min)
 * - sol_: Variable values of best solution
 * - valid_: Whether stored solution corresponds to cutoff
 *
 * **Thread safety note:**
 * In parallel environments, this would need synchronization.
 * Currently assumes sequential access.
 *
 * **setCutOff():**
 * Updates cutoff and optionally stores the solution vector.
 * Requires CouenneProblem pointer for size information.
 *
 * @see CouenneProblem which owns the GlobalCutOff
 * @see CouenneFeasPump which updates cutoff when finding solutions
 */
#ifndef COUENNE_GLOBAL_CUTOFF_HPP
#define COUENNE_GLOBAL_CUTOFF_HPP

#include "CouenneConfig.h"
#include "CouenneProblem.hpp"

namespace Couenne {

  class COUENNELIB_EXPORT GlobalCutOff {

  private:

    GlobalCutOff (const GlobalCutOff&);

    double  cutoff_; ///< Value of the best solution
    double *sol_;    ///< Best solution
    int     size_;   ///< Size of the vector stored in sol (should be #var of reformulation)
    bool    valid_;  ///< Stored solution corresponds to cutoff

  public:

    GlobalCutOff ();
    GlobalCutOff (double c, const double *s=NULL, int n=0);
    ~GlobalCutOff ();

    void setCutOff (const CouenneProblem *p, double cutoff, const double *s=NULL);

    inline double  getCutOff    () const {return cutoff_;}
    inline double *getCutOffSol () const {return sol_;}
  };
}

#endif
