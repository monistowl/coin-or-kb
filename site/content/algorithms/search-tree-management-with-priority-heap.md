+++
title = "Search Tree Management with Priority Heap"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

Maintains live (unexplored) nodes in a binary heap for efficient selection.

Node Selection Strategies (via CbcCompare):
- Best-first: Select node with best (lowest) LP bound → optimal first solution
- Depth-first: Select deepest node → memory efficient, finds solutions fast
- Best-estimate: Use pseudo-cost estimate of integer solution value
- Hybrid: Switch strategies based on incumbent, gap, or tree size

Tree Operations:
- push(node): Add to heap, O(log n) sift-up
- pop(): Remove best, O(log n) sift-down
- cleanTree(cutoff): Prune nodes with bound ≥ cutoff (fathoming)
- setComparison(): Change strategy, O(n) re-heapify

## Mathematical Formulation

<div class="math-block">

Node bound vs incumbent: If LB(node) ≥ UB (best incumbent), fathom node.
Best-first guarantees: first integer solution found is optimal.
Depth-first memory: O(depth × branching_factor) vs O(2^depth) for best-first.

</div>

## Complexity

push/pop: O(log n). cleanTree: O(n). Space: O(live_nodes).
Typical MIP: live nodes peaks at thousands to millions depending on strategy.

## Implementations

### Cbc

- **[CbcTree.hpp](/browser/?library=Cbc)** - Heap-based storage for live search tree nodes
Copyright (C) 2004, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## References

- Linderoth & Savelsbergh, "A computational study of search strategies",
     INFORMS Journal on Computing 11 (1999) 173-187
- Achterberg, "Constraint Integer Programming", PhD thesis, TU Berlin (2007)

CbcTree manages the set of live (unexplored) nodes as a priority heap.
The comparison function (CbcCompare) determines node selection strategy:
- Best-first: Select node with best bound
- Depth-first: Select deepest node
- Best-estimate: Use pseudocost estimates

Key methods:
- push(): Add node to heap
- top()/pop(): Get and remove best node
- setComparison(): Change selection strategy (re-heapifies)
- cleanTree(): Remove nodes worse than cutoff
