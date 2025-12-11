/**
 * @file DippyDecompCut.h
 * @brief Python-compatible DecompCut for Dippy user-defined cuts
 *
 * Implements DippyDecompCut which stores cuts generated from Python
 * callbacks using simple index/element arrays. Allows Python code
 * to define cutting planes that integrate with DIP's cut management.
 *
 * @see DippyDecompApp.h for Python cut generation callback
 * @see DecompCut.h for base cut interface
 */
#ifndef DIPPY_DECOMP_CUT_H
#define DIPPY_DECOMP_CUT_H

#include "Decomp.h"
#include "DecompCut.h"
#include "UtilMacros.h"

#include <vector>
using namespace std;

class DippyDecompCut : public DecompCut {
private:
   double m_lb;
   double m_ub;
   int m_nElems;
   int* m_indices;
   double* m_elements;

public:
   DippyDecompCut(double lb, double ub, int nElems, int* indices, double* elements) :
      m_lb(lb), m_ub(ub), m_nElems(nElems), m_indices(indices), m_elements(elements) {
      setLowerBound(m_lb);
      setUpperBound(m_ub);
   }
   void expandCutToRow(CoinPackedVector* row) {
      row->setVector(m_nElems, m_indices, m_elements, false);
   }

   ~DippyDecompCut() {
      delete [] m_indices;
      delete [] m_elements;
   }
};


#endif
