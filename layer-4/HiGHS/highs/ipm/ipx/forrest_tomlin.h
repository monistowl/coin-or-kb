/**
 * @file ipm/ipx/forrest_tomlin.h
 * @brief Forrest-Tomlin LU Update for Basis Maintenance
 *
 * Implements the Forrest-Tomlin update to maintain LU factorization when
 * a single column of the basis matrix changes (basis exchange/pivot).
 *
 * @algorithm Forrest-Tomlin LU Update:
 * Efficiently updates LU factors after column replacement without full
 * refactorization.
 *
 * SETUP:
 * Given factorization: B = L·U with permutations
 * After replacing column j: B' differs from B in one column
 *
 * KEY INSIGHT:
 * Instead of refactorizing B' = L'·U', compute update matrices:
 *   B' = L · R₁ · R₂ · ... · Rₖ · U'
 * where Rᵢ are "row eta" matrices (identity plus one off-diagonal element).
 *
 * UPDATE PROCESS:
 * 1. FTRAN (Forward transformation):
 *    Compute spike = L⁻¹·b where b is the new column
 *    Append spike to U
 *
 * 2. BTRAN (Backward transformation):
 *    Compute eta = eₚ'·U⁻¹ where p is position of leaving column
 *    Append eta to R (row eta matrix)
 *
 * 3. Permutation update:
 *    Track which columns have been replaced
 *
 * SOLVE WITH UPDATES:
 * To solve B'·x = rhs after k updates:
 *   x = U'⁻¹ · Rₖ⁻¹ · ... · R₁⁻¹ · L⁻¹ · rhs
 *
 * @math Fill-in analysis:
 * - Spike column: O(m) nonzeros worst case
 * - Row eta: O(m) nonzeros worst case
 * - After k updates: O(k²) additional work per solve
 * - Refactorize when k > √m or fill exceeds threshold
 *
 * Memory layout optimization:
 * L, U stored in compressed form with permuted indices for contiguous
 * memory access during dense solves (unlike BASICLU which needs
 * re-permutation).
 *
 * @complexity
 * - Single update: O(m²) worst case, O(nnz) typical
 * - Solve after k updates: O(m·k) additional work
 * - Trade-off: update cost vs refactorization cost
 *
 * @ref Forrest & Tomlin (1972). "Updated Triangular Factors of the Basis
 *   to Maintain Sparsity in the Product Form Simplex Method".
 *   Mathematical Programming 2:263-278.
 *
 * @see lu_update.h for base class interface
 * @see basis.h for usage in basis maintenance
 */
#ifndef IPX_FORREST_TOMLIN_H_
#define IPX_FORREST_TOMLIN_H_

#include <memory>
#include <vector>
#include "ipm/ipx/control.h"
#include "ipm/ipx/lu_factorization.h"
#include "ipm/ipx/lu_update.h"

namespace ipx {

class ForrestTomlin : public LuUpdate {
public:
    // Constructor takes ownership of the LuFactorization object by a move from
    // @lu.
    ForrestTomlin(const Control& control, Int dim,
                  std::unique_ptr<LuFactorization>& lu);
    ~ForrestTomlin() = default;

private:
    Int _Factorize(const Int* Bbegin, const Int* Bend, const Int* Bi,
                   const double* Bx, bool strict_abs_pivottol) override;
    void _GetFactors(SparseMatrix* L, SparseMatrix* U, Int* rowperm,
                     Int* colperm, std::vector<Int>* dependent_cols) override;
    void _SolveDense(const Vector& rhs, Vector& lhs, char trans) override;
    void _FtranForUpdate(Int nz, const Int* bi, const double* bx) override;
    void _FtranForUpdate(Int nz, const Int* bi, const double* bx,
                         IndexedVector& lhs) override;
    void _BtranForUpdate(Int j) override;
    void _BtranForUpdate(Int j, IndexedVector& lhs) override;
    Int _Update(double pivot) override;
    bool _NeedFreshFactorization() override;
    double _fill_factor() const override;
    double _pivottol() const override;
    void _pivottol(double new_pivottol) override;

    // Maximum # updates before refactorization is required.
    static constexpr Int kMaxUpdates = 5000;

    // Solves a linear system with the basis matrix. On entry @x holds the
    // permuted right-hand side, on return it holds the permuted solution.
    // @x must have dimension at least dim_ + # computed updates; the additional
    // components are used as workspace.
    // @trans: 't' or 'T' for transposed system.
    void SolvePermuted(Vector& x, char trans);

    // Computes the spike column for the FT update from
    //   R_k^{-1} * ... * R_1^{-1} * L^{-1} * b
    // and stores it in compressed form at the end of U. The spike is also
    // returned as a full vector in work_.
    // @nb, @bi, @bx: b in compressed form.
    void ComputeSpike(Int nb, const Int* bi, const double* bx);

    // Computes the partial BTRAN solution r = ep' * U^{-1}, where ep is the
    // p-th unit vector and p the position of column @j in the pivot sequence.
    // The row eta vector -r/r[p] without the unit diagonal entry is stored in
    // compressed form at end of R. r is returned as a full vector in work_.
    void ComputeEta(Int j);

    const Control& control_;
    const Int dim_;
    std::unique_ptr<LuFactorization> lu_;

    std::vector<Int> rowperm_;     // row permutation from factorization
    std::vector<Int> colperm_;     // col permutation from factorization
    std::vector<Int> rowperm_inv_; // inverse permutation of rowperm_
    std::vector<Int> colperm_inv_; // inverse permutation of colperm_
    std::vector<Int> dependent_cols_;
                             // passed trough from _Factorize() to _GetFactors()

    SparseMatrix L_;            // L from factorization
    SparseMatrix U_;            // U from factorization with spike cols appended
    SparseMatrix R_;            // cols of R build row eta matrices from updates

    // replaced_[k] == p if update k replaced position p in pivot sequence.
    // replaced_.size() is the # updates performed.
    std::vector<Int> replaced_;
    Int replace_next_;          // position to be replaced in next update
    bool have_btran_{false};    // true if row eta has been computed
    bool have_ftran_{false};    // true if spike has been computed
    double fill_factor_{0.0};   // fill factor from last factorization
    double pivottol_{0.1};      // LU pivot tolerance for next factorization
    Vector work_;               // size dim_ + kMaxUpdates workspace
};

}  // namespace ipx

#endif  // IPX_FORREST_TOMLIN_H_
