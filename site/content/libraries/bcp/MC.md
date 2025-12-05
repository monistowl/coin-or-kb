+++
title = "Max-Cut Example"
description = "Graph partitioning via branch-and-cut with cycle inequalities"
template = "class.html"

[extra]
library = "bcp"
header = "Applications/MaxCut/include/"
+++

# Max-Cut: Graph Partitioning Optimization

The Max-Cut example demonstrates how to solve NP-hard combinatorial optimization problems using BCP's branch-and-cut framework with problem-specific cutting planes.

---

## Problem Definition

**Given:** An undirected graph $G = (V, E)$ with edge weights $w_e$

**Find:** A partition of vertices into sets $S$ and $T = V \setminus S$ that maximizes the total weight of edges crossing the cut:

$$\max \sum_{e = (i,j): i \in S, j \in T} w_e$$

### LP Relaxation

For each edge $e = (i,j)$, let $x_e \in [0,1]$ indicate whether the edge crosses the cut:

$$\max \sum_e w_e x_e$$

Subject to: cycle inequalities (see below)

<div class="key-insight">

**Why Max-Cut is hard:** The LP relaxation is weak without cutting planes. A triangle with all $x_e = 0.5$ has LP value $1.5w$ but no integer solution can achieve more than $w$ (at most 2 of 3 edges can cross any cut).

</div>

---

## Cycle Inequalities

The key insight: **In any cycle, the number of edges crossing the cut must be even.**

For a cycle $C$ with $|C|$ edges, if all edges had $x_e = 1$ (all cross the cut), that would require an odd number of crossings around the cycle, which is impossible.

### Mathematical Formulation

For any cycle $C$ in the graph:

$$\sum_{e \in C^+} x_e - \sum_{e \in C^-} x_e \leq |C^+| - 1$$

Where $C^+$ and $C^-$ partition the cycle edges based on their orientation.

In the simplest form (odd cycle inequality):

$$\sum_{e \in C} x_e \leq |C| - 1$$

This is violated when the LP solution assigns total value $> |C| - 1$ to cycle edges.

---

## Separation Algorithms

The example implements two cycle separation strategies:

### MST-Based Separation (`MC_mst_cutgen`)

1. Build auxiliary graph with edge weights based on LP solution
2. Compute MST using Kruskal's algorithm
3. For each non-tree edge, find fundamental cycle
4. Check if cycle inequality is violated
5. Add most violated cuts to LP

```cpp
// Edge ordering affects which cycles are found
enum MC_EdgeOrdering {
    MC_MstEdgeOrderingPreferZero,    // Prefer edges with x ≈ 0
    MC_MstEdgeOrderingPreferOne,     // Prefer edges with x ≈ 1
    MC_MstEdgeOrderingPreferExtreme  // Prefer edges with x ≈ 0 or x ≈ 1
};
```

### Shortest-Path Separation (`MC_generate_shortest_path_cycles`)

For more thorough separation:
1. Build graph with transformed weights
2. Find shortest paths from each node
3. Each back-edge creates a cycle
4. Enumerate all violated odd cycles

---

## Local Search Heuristics

The example includes multiple heuristics to find good integer solutions:

### Switch Heuristic (`switch_improve`)
Flip individual nodes between $S$ and $T$ while improvement is possible.
- **Complexity:** $O(n \cdot m)$ per pass

### Edge-Switch Heuristic (`edge_switch_improve`)
Swap pairs of adjacent nodes simultaneously.
- Escapes local optima that switch cannot

### Lin-Kernighan Style (`lk_switch_improve`)
Variable-depth search allowing temporarily worsening moves.
- Most powerful but slowest

### Structure-Specific (`structure_switch_improve`)
For Ising problems on regular grids:
- Exploits four-cycle and triangle structure
- Domain-specific moves for physics problems

---

## Implementation Structure

### Data Structures

| Class | Purpose |
|-------|---------|
| `MC_problem` | Graph representation (nodes, edges, adjacency) |
| `MC_solution` | Partition (node signs) and cut value |
| `MC_cycle_cut` | Cycle inequality with memory pooling |
| `MC_feas_sol` | Initial feasible solution |

### BCP Integration

| Class | BCP Base | Role |
|-------|----------|------|
| `MC_tm` | `BCP_tm_user` | Tree manager: setup, display |
| `MC_lp` | `BCP_lp_user` | LP worker: cuts, heuristics |
| `MC_packer` | `BCP_user_pack` | Serialize cuts for distribution |

---

## Source Files

| File | Description |
|------|-------------|
| {{ link(path="/browser/?library=Bcp&path=Applications/MaxCut/include/MC.hpp", text="MC.hpp") }} | Problem data structures |
| {{ link(path="/browser/?library=Bcp&path=Applications/MaxCut/include/MC_cut.hpp", text="MC_cut.hpp") }} | Cycle inequalities and separation |
| {{ link(path="/browser/?library=Bcp&path=Applications/MaxCut/include/MC_solution.hpp", text="MC_solution.hpp") }} | Solution with local search |
| {{ link(path="/browser/?library=Bcp&path=Applications/MaxCut/include/MC_lp.hpp", text="MC_lp.hpp") }} | LP process with cut generation |
| {{ link(path="/browser/?library=Bcp&path=Applications/MaxCut/include/MC_tm.hpp", text="MC_tm.hpp") }} | Tree manager setup |

---

## Ising Problem Variant

The implementation supports **Ising spin glass** problems from physics:
- Nodes are spins (+1 or -1)
- Edges represent interaction energies
- Goal: Find ground state configuration

Special structures exploited:
- **Four-cycles:** Square grid patterns
- **Triangles:** With external magnetic field

---

## References

- Barahona, F., et al. (1988). "An Application of Combinatorial Optimization to Statistical Physics and Circuit Layout Design", Operations Research
- Poljak, S., Tuza, Z. (1995). "Maximum Cuts and Large Bipartite Subgraphs", DIMACS Series

