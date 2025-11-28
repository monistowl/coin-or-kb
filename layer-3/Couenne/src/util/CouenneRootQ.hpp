/*
 *
 * Name:    rootQ.hpp
 * Author:  Pietro Belotti
 * Purpose: find roots of polynomial Q^k(x) (see Liberti and Pantelides, 2003)
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneRootQ.hpp
 * @brief Root finding for Q^k(x) polynomials in power convexification
 *
 * Finds roots of the polynomial Q^k(x) = Σᵢ₌₁^{2k} i·x^{i-1} used in
 * convexification of odd powers. Based on Liberti & Pantelides (2003).
 *
 * **Mathematical background:**
 * For odd power expressions w = x^k, the convex/concave envelope
 * requires finding specific points where tangent lines from the
 * boundary touch the curve. The Q^k polynomial characterizes these.
 *
 * **Usage:**
 * - rootQ(k): Computes root for exponent 2k+1
 * - Qroot class: Caches computed roots in static map for efficiency
 *
 * **Implementation:**
 * - Odd k: Computed via Newton's method, cached in Qmap
 * - Even k (2,4,6,8,10): Hardcoded analytical values
 *   - k=2: -(√2 - 1) ≈ -0.414
 *   - k=4: ≈ -0.560
 *   - k=6: ≈ -0.641
 *   - etc.
 *
 * @see CouenneExprOddPow which uses these roots
 * @see CouenneExprSignPow for signed power convexification
 */
#ifndef CouenneRootQ_hpp
#define CouenneRootQ_hpp

#include "CouenneTypes.hpp"
#include "CouenneConfig.h"
#include <map>
#include <iostream>

namespace Couenne
{

/// Find roots of polynomial $Q^k(x) = \f$\sum_{i=1}^{2k} i x^{i-1}\f$. Used
/// in convexification of powers with odd exponent
COUENNELIB_EXPORT
CouNumber rootQ (int k);


/// class that stores result of previous calls to rootQ into a map for
/// faster access

class COUENNELIB_EXPORT Qroot {

 protected:

  /// Maps an integer k with the root of \f$Q^k(x)\f$.

  static std::map <int, CouNumber> Qmap;

 public:

  /// Empty constructor -- we only need the method to work on the static
  /// structure.
  Qroot  () {}

  /// Empty destructor.
  ~Qroot () {}

  /// Retrieve root of Q with order = k. If no such computation has
  /// been performed yet, do it here

  inline CouNumber operator () (int k) {

    std::map <int, CouNumber>:: iterator pos;
    CouNumber root;

    if( k % 2 == 1 )
    {
       k /= 2; // becomes true index

       if ((pos = Qmap.find (k)) == Qmap.end()) {

          std::pair <int, CouNumber> newpair;

          newpair.first  = k;
          newpair.second = (root = rootQ (k));

          Qmap.insert (newpair);
       }
       else
          root = pos -> second;
    }
    else
    {
       switch(k) {
          case 2: return -(sqrt(2.0) - 1.0);
          case 4: return -0.56042566045031785945;
          case 6: return -0.64146546982884663257;
          case 8: return -0.69428385661425826738;
          case 10: return -0.73192937842370733350;
          default:
             std::cerr << "Need to implement root finding for even k" << std::endl;
             throw -1;
       }
    }

    return root;
  }
};

}

#endif
