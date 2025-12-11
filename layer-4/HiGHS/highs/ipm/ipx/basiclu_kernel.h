/**
 * @file basiclu_kernel.h
 * @brief BasicLU implementation of LuFactorization interface
 *
 * Implements LuFactorization using the BasicLU library for sparse
 * LU factorization with Markowitz pivoting.
 *
 * @see lu_factorization.h for the interface
 * @see basiclu.h for the underlying library
 */
#ifndef IPX_BASICLU_KERNEL_H_
#define IPX_BASICLU_KERNEL_H_

#include "ipm/ipx/lu_factorization.h"

namespace ipx {

class BasicLuKernel : public LuFactorization {
private:
    void _Factorize(Int dim, const Int* Bbegin, const Int* Bend,
                    const Int* Bi, const double* Bx, double pivottol,
                    bool strict_abs_pivottol,
                    SparseMatrix* L, SparseMatrix* U,
                    std::vector<Int>* rowperm, std::vector<Int>* colperm,
                    std::vector<Int>* dependent_cols) override;
};

}  // namespace ipx

#endif  // IPX_BASICLU_KERNEL_H_
