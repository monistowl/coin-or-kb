/**
 * @file Factorise.h
 * @brief Numerical phase of sparse LDL^T factorization
 *
 * Supernodal numerical factorization for symmetric indefinite matrices
 * arising in interior point method normal equations.
 *
 * @algorithm Supernodal LDL^T Factorization:
 *   Factor PAP^T = LDL^T using dense BLAS-3 operations on supernodes:
 *   @math For each supernode sn in topological order:
 *         1. Assemble: Gather updates from children into schur_contribution_
 *         2. Factor: Dense LDL^T on frontal matrix (supernode + clique)
 *         3. Scatter: Store L columns in sn_columns_, D on diagonal
 *   processSupernode() handles assembly, factorization, and scatter.
 *   @complexity O(nnz_L · supernode_width²) dominated by dense operations
 *   @ref Ashcraft, C. and Grimes, R. (1999). "SPOOLES: An object-oriented
 *        sparse matrix library". PPSC.
 *
 * @algorithm Bunch-Kaufman Pivoting:
 *   Handle indefinite matrices via 1x1 and 2x2 pivots:
 *   @math At each step, choose 1x1 pivot if |a_kk| ≥ α·max_offdiag
 *         Otherwise use 2x2 pivot with largest off-diagonal
 *         pivot_2x2_ stores off-diagonal elements of 2x2 inverse
 *         swaps_ records column interchanges within supernodes
 *   Bounded element growth ensures numerical stability.
 *   @ref Bunch, J. and Kaufman, L. (1977). "Some stable methods for
 *        calculating inertia and solving symmetric linear systems".
 *
 * @algorithm Static Regularization:
 *   Add diagonal perturbation for near-singular systems:
 *   @math If |d_kk| < threshold: d_kk += sign(d_kk) · regul_value
 *         total_reg_ tracks cumulative regularization per column
 *   Prevents breakdown on ill-conditioned IPM systems.
 *   @complexity O(n) diagonal checks
 *
 * @see Analyse.h for symbolic phase producing Symbolic structure
 * @see Numeric.h for output numerical factorization
 */
#ifndef FACTORHIGHS_FACTORISE_H
#define FACTORHIGHS_FACTORISE_H

#include <cmath>

#include "Numeric.h"
#include "Symbolic.h"
#include "ipm/hipo/auxiliary/IntConfig.h"
#include "ipm/hipo/auxiliary/Log.h"

namespace hipo {

class Factorise {
 public:
  // matrix to factorise
  std::vector<Int> rowsA_{};
  std::vector<Int> ptrA_{};
  std::vector<double> valA_{};
  Int n_{};
  Int nzA_{};

  // symbolic factorisation
  const Symbolic& S_;

  // children in supernodal elimination tree
  std::vector<Int> first_child_{};
  std::vector<Int> next_child_{};

  // reverse linked lists of chidlren
  std::vector<Int> first_child_reverse_{};
  std::vector<Int> next_child_reverse_{};

  // generated elements, aka Schur complements.
  std::vector<std::vector<double>> schur_contribution_{};

  // columns of L, stored as dense supernodes
  // This memory is managed outside of Factorise, so that it can be reused for
  // all ipm iterations.
  std::vector<std::vector<double>>& sn_columns_;

  // swaps of columns for each supernode, ordered locally within a block
  std::vector<std::vector<Int>> swaps_{};

  // Information about 2x2 pivots.
  // If pivot_2x2[sn][i] == 0, 1x1 pivot was used.
  // If pivot_2x2[sn][i] != 0, 2x2 pivot was used and pivot_2x2[sn][i] stores
  //  the off-diagonal pivot entry (of the 2x2 inverse).
  std::vector<std::vector<double>> pivot_2x2_{};

  // largest diagonal element in the original matrix and norms of columns
  double max_diag_{};
  double min_diag_{};
  double A_norm1_{};
  std::vector<double> one_norm_cols_{};
  std::vector<double> inf_norm_cols_{};

  // regularisation
  std::vector<double> total_reg_{};

  // values for static regularisation
  const Regul& regul_;

  // flag to stop computation
  bool flag_stop_ = false;

  const Log* log_;
  DataCollector& data_;

 public:
  void permute(const std::vector<Int>& iperm);
  void processSupernode(Int sn);

 public:
  Factorise(const Symbolic& S, const std::vector<Int>& rowsA,
            const std::vector<Int>& ptrA, const std::vector<double>& valA,
            const Regul& regul, const Log* log, DataCollector& data,
            std::vector<std::vector<double>>& sn_columns);

  bool run(Numeric& num);
};

}  // namespace hipo

#endif