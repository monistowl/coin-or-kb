/**
 * @file Analyse.h
 * @brief Symbolic analysis phase for sparse Cholesky factorization
 *
 * Computes fill-reducing ordering and symbolic factorization structure
 * before numerical factorization in HiGHS interior point solver.
 *
 * @algorithm Symbolic Cholesky Analysis:
 *   Compute non-zero structure of L before numerical factorization:
 *   @math 1. getPermutation(): Fill-reducing ordering via Metis
 *         2. eTree(): Compute elimination tree parent[j] for each column
 *         3. postorder(): Topological sort of elimination tree
 *         4. colCount(): Count non-zeros per column of L
 *         5. fundamentalSupernodes(): Identify dense column blocks
 *   Elimination tree enables efficient symbolic and numeric phases.
 *   @complexity O(nnz) for tree, O(nnz·α(n)) for column counts
 *   @ref Liu, J. (1990). "The role of elimination trees in sparse
 *        factorization". SIAM J. Matrix Anal. Appl. 11(1):134-172.
 *
 * @algorithm Supernodal Factorization Structure:
 *   Group columns into supernodes for BLAS-3 efficiency:
 *   @math fundamentalSupernodes(): Columns j,j+1 in same supernode if:
 *           - parent[j] = j+1 in elimination tree
 *           - L[:,j] and L[:,j+1] have same sparsity below diagonal
 *         relaxSupernodes(): Merge small supernodes accepting fill-in
 *         snPattern(): Compute row indices for each supernode
 *   Dense supernode columns enable efficient matrix-matrix operations.
 *   @complexity O(nnz_L) for supernode identification
 *   @ref Ng, E. and Peyton, B. (1993). "Block sparse Cholesky algorithms
 *        on advanced uniprocessor computers". SIAM SISC 14(5):1034-1056.
 *
 * @algorithm Relative Index Computation:
 *   Map between supernode and global indices:
 *   @math relativeIndCols(): Map original columns to L positions
 *         relativeIndClique(): Map update positions in Schur complement
 *   Enables O(1) lookup during numeric factorization updates.
 *
 * @see Symbolic.h for output symbolic factorization structure
 * @see Factorise.h for numerical factorization using this analysis
 */
#ifndef FACTORHIGHS_ANALYSE_H
#define FACTORHIGHS_ANALYSE_H

#include <algorithm>
#include <vector>

#include "DataCollector.h"
#include "Symbolic.h"
#include "ipm/hipo/auxiliary/IntConfig.h"
#include "ipm/hipo/auxiliary/Log.h"

namespace hipo {

// Class to perform the analyse phase of the factorisation.
// The final symbolic factorisation is stored in an object of type Symbolic.
class Analyse {
  bool ready_ = false;

  // Matrix to be factorised, stored in upper and lower triangular format
  std::vector<Int> rows_upper_{};
  std::vector<Int> ptr_upper_{};
  std::vector<Int> rows_lower_{};
  std::vector<Int> ptr_lower_{};

  // info about matrix and factor
  Int n_{};
  Int nz_{};
  int64_t nz_factor_{};
  double dense_ops_{};
  double dense_ops_norelax_{};
  double sparse_ops_{};
  double critical_ops_{};
  std::vector<Int> signs_{};

  // Permutation and inverse permutation from Metis
  std::vector<Int> perm_{};
  std::vector<Int> iperm_{};

  // Elimination tree
  std::vector<Int> parent_{};

  // postorder of the elimination tree
  std::vector<Int> postorder_{};

  // number of entries in each column of L
  std::vector<Int> col_count_{};

  // sparsity pattern of supernodes of L
  std::vector<Int> rows_sn_{};
  std::vector<Int> ptr_sn_{};

  std::vector<Int> sn_indices_{};

  // fundamental supernodes information
  Int sn_count_{};
  int64_t artificial_nz_{};
  std::vector<Int> sn_belong_{};
  std::vector<Int> sn_start_{};
  std::vector<Int> sn_parent_{};

  // temporary storage for relaxing supernodes
  std::vector<Int> fake_nz_{};
  std::vector<Int> merged_into_{};
  Int merged_sn_{};

  // relative indices of original columns wrt L columns
  std::vector<Int> relind_cols_{};

  // relative indices of clique wrt parent
  std::vector<std::vector<Int>> relind_clique_{};

  // information about consecutive indices in relindClique
  std::vector<std::vector<Int>> consecutive_sums_{};

  // estimate of maximum storage
  double serial_storage_{};

  std::vector<std::vector<Int>> clique_block_start_{};

  // block size
  Int nb_{};

  const Log* log_;
  DataCollector& data_;

  // Functions to perform analyse phase
  Int getPermutation();
  void permute(const std::vector<Int>& iperm);
  void eTree();
  void postorder();
  void colCount();
  void fundamentalSupernodes();
  void relaxSupernodes();
  void relaxSupernodesSize();
  void afterRelaxSn();
  void snPattern();
  void relativeIndCols();
  void relativeIndClique();
  void reorderChildren();
  void computeStorage();
  void computeStorage(Int fr, Int sz, double& fr_entries,
                      double& cl_entries) const;
  void computeCriticalPath();
  void computeBlockStart();

 public:
  // Constructor: matrix must be in lower triangular format
  Analyse(const std::vector<Int>& rows, const std::vector<Int>& ptr,
          const std::vector<Int>& signs, Int nb, const Log* log,
          DataCollector& data);

  // Run analyse phase and save the result in Symbolic object S
  Int run(Symbolic& S);
};

}  // namespace hipo

#endif