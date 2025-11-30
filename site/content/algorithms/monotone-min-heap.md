+++
title = "Monotone Min-Heap"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Binary heap with decreasing-key only (no arbitrary updates).
  Heap property: parent.cost ≤ children.cost
  Operations:
  - update(node, newCost): decrease key, bubble up (newCost < oldCost)
  - removeFirst(): extract minimum, bubble down replacement
  - isEmpty(): check if all nodes at infinity

## Mathematical Formulation

<div class="math-block">

Used in Dijkstra where distances only decrease.
  Monotonicity allows simpler implementation than general heap.
  Position array enables O(1) node lookup for decrease-key.

</div>

## Complexity

update: O(log n) for bubble-up
  removeFirst: O(log n) for bubble-down
  isEmpty: O(1)
  Space: O(n) for heap + position array

## Implementations

### CoinUtils

- **[CoinNodeHeap.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Monotone min-heap for Dijkstra's algorithm
