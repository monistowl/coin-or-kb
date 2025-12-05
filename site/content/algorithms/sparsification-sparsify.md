+++
title = "Sparsification (sparsify)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Combine rows to create zeros in dense columns:
  For equation row i with coefficient a_ij in column j:
  - For each row k with coefficient a_kj:
    - Add scaled row i to row k: row_k += (−a_kj/a_ij) * row_i
    - If fill-in acceptable, apply permanently

## Mathematical Formulation

<div class="math-block">

Compute implied lower bound on x_k:
    x_k >= (L - sum_{j≠k}(a_j * u_j if a_j>0 else a_j * l_j)) / a_k
  If tighter than current l_k, update and propagate.
  Dual analog: implied dual bounds from reduced cost constraints.

</div>

## Complexity

Matrix access: O(1) amortized via splay trees (row) and linked lists (col)
  Singleton elimination: O(nnz) per pass
  Probing: O(#binaries * propagation_depth)
  Full presolve: typically O(nnz * #passes), bounded by reductionLimit

## Implementations

### HiGHS

- **{{ link(path="/browser/?library=HiGHS", text="HPresolve.h") }}** - LP/MIP presolve engine

**HPresolve Class:**
Reduces problem size and tightens bounds before solving.

**Matrix Storage:**
Triplet format with linked list (column) and splay tree (row) for fast access:
- Avalue[], Arow[], Acol[]: Non-zero storage
- colhead[], Anext[], Aprev[]: Column-wise linked list
- rowroot[], ARleft[], ARright[]: Row-wise splay tree
- rowsize[], colsize[]: Current row/column lengths

**Bound Tracking:**
- implColLower[]/implColUpper[]: Implied variable bounds
- rowDualLower[]/rowDualUpper[]: Dual bounds
- impliedRowBounds, impliedDualRowBounds: Row activity bounds

**Presolve Techniques (Result enum):**
- singletonRow()/singletonCol(): Remove singleton rows/columns
- emptyCol(): Remove columns with no constraints
- doubletonEq(): Eliminate doubleton equalities
- dominatedColumns(): Remove dominated variables
- aggregator(): Aggregate rows/columns
- runProbing(): Probing for integer variables
- sparsify(): Reduce matrix density
- detectParallelRowsAndCols(): Remove parallel constraints/variables

## References

- Savelsbergh, M.W.P. (1994). "Preprocessing and probing techniques
       for mixed integer programming problems". ORSA J. Computing 6(4).
- Achterberg, T. et al. (2020). "Presolve reductions in mixed
       integer programming". INFORMS J. Computing 32(2).
