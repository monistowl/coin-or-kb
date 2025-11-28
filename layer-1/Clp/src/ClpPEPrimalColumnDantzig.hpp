/**
 * @file ClpPEPrimalColumnDantzig.hpp
 * @brief Positive Edge enhanced Dantzig pricing for primal simplex
 * @author Jeremy Omer, Mehdi Towhidi
 *
 * Combines classic Dantzig pricing (most negative reduced cost) with
 * Positive Edge compatibility checking. Prioritizes compatible columns
 * that can make real progress on degenerate problems.
 *
 * Uses bi-dimensional pricing: candidates are scored by both reduced cost
 * and compatibility, weighted by psi parameter (default 0.5).
 *
 * @see ClpPESimplex for the compatibility framework
 * @see ClpPrimalColumnDantzig for the base pricing rule
 * @see ClpPEPrimalColumnSteepest for steepest edge variant
 */

#ifndef ClpPEPrimalColumnDantzig_H
#define ClpPEPrimalColumnDantzig_H

#include "ClpPrimalColumnDantzig.hpp"
#include "ClpPrimalColumnPivot.hpp"
#include "ClpSimplex.hpp"
#include "CoinIndexedVector.hpp"
#include "ClpFactorization.hpp"
#include "ClpNonLinearCost.hpp"
#include "ClpSimplexPrimal.hpp"
#include "ClpPackedMatrix.hpp"
#include "ClpPESimplex.hpp"

class CLPLIB_EXPORT ClpPEPrimalColumnDantzig : public ClpPrimalColumnDantzig {

public:
  /** constructors */
  ClpPEPrimalColumnDantzig(double psi = 0.5);
  ClpPEPrimalColumnDantzig(const ClpPEPrimalColumnDantzig &); //copy constructor

  /** destructor */
  ~ClpPEPrimalColumnDantzig();

  /** assignment operator */
  ClpPEPrimalColumnDantzig &operator=(const ClpPEPrimalColumnDantzig &rhs);

  /** clone */
  ClpPrimalColumnPivot *clone(bool copyData = true) const;

  virtual int pivotColumn(CoinIndexedVector *updates,
    CoinIndexedVector *spareRow1,
    CoinIndexedVector *spareRow2,
    CoinIndexedVector *spareColumn1,
    CoinIndexedVector *spareColumn2);

  //@}
  /** Save weights - this may initialize weights as well
	 This is as parent but may initialize ClpPESimplex
     */
  virtual void saveWeights(ClpSimplex *model, int mode);
  //---------------------------------------------------------------------------
private:
  /* this PESimplex object is used to identify the compatible variables */
  ClpPESimplex *modelPE_;

  /* psi is the factor used in the bi-dimensional pricing, it is < 1 and
       1/psi grows with the priority given to compatible variables */
  double psi_;

  /* useful counters for the update of the set of compatible variables */
  int iCurrent_;
  int iInterval_;

  /* record if previous iterations concluded that compatibles should not be checked */
  int coDegenCompatibles_;
  int coConsecutiveCompatibles_;
  bool updateCompatibles_;
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
