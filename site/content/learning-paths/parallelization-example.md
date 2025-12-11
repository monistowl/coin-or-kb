+++
title = "Interactive Parallel Branch-and-Bound"
description = "Watch workers solve nodes simultaneously with bound synchronization"
template = "parallelization-interactive.html"
weight = 55
+++

This interactive example demonstrates **parallel branch-and-bound** with three workers. Step through to see how nodes are distributed, bounds propagate, and synchronization affects efficiency.

## The Problem

A small integer program (maximization):

$$\max \quad 5x_1 + 4x_2$$

Subject to:
$$x_1 + x_2 \leq 5$$
$$10x_1 + 6x_2 \leq 45$$
$$x_1, x_2 \geq 0 \text{ and integer}$$

The LP relaxation gives fractional solutions that require branching.

## What This Visualization Shows

### The Worker Panel (Left)

Three workers process nodes in parallel:
- **Active** (green): Currently solving an LP relaxation
- **Idle** (gray): Waiting for work

### The Search Tree (Center)

Nodes represent subproblems:
- **Gray (unexplored)**: In queue, not yet processed
- **Cyan (exploring)**: Worker currently solving
- **Blue (explored)**: LP solved, children created
- **Green (integer)**: Found feasible integer solution
- **Red (pruned)**: Bound cannot improve incumbent

### The Node Queue (Right)

Nodes waiting for workers, sorted by bound (best-first).

## Key Parallel Concepts

### 1. Work Distribution

When multiple nodes are available, workers grab them simultaneously:

```
Time 3:
  Worker 0 → Node N1 (bound 23.5)
  Worker 1 → Node N2 (bound 22.0)
  Worker 2 → idle (no more nodes)
```

### 2. Bound Synchronization Delay

In parallel B&B, workers may not immediately see updated incumbents:

```
Worker 1 finds incumbent = 21
Worker 0 still processing (doesn't know yet)
Worker 0 creates N4 with bound 20.5 < 21
  → This work is "wasted" but unavoidable
```

### 3. Pruning After Sync

When workers synchronize, nodes with bounds worse than incumbent are pruned:

```
After sync: incumbent = 21
N4 has bound 20.5 ≤ 21
  → N4 pruned (can't improve best known)
```

## Connection to COIN-OR

### BCP Master-Worker Architecture

The visualization mirrors [BCP's](@/libraries/bcp/_index.md) design:

| Visualization | BCP Component |
|---------------|---------------|
| Queue management | Tree Manager (TM) |
| LP solving | LP Worker processes |
| Bound updates | TM broadcasts to workers |
| Node creation | Children sent to TM queue |

### Cbc Thread Pool

[Cbc](@/libraries/cbc/_index.md) uses a simpler shared-memory model:

```cpp
CbcModel model(solver);
model.setNumberThreads(3);  // Use 3 worker threads
model.branchAndBound();
```

Internally, Cbc maintains:
- A shared node pool with mutex protection
- Per-thread LP solvers
- Periodic bound synchronization

### Communication Patterns

**BCP (distributed memory):**
```
TM → LP: "Process node N1"
LP → TM: "N1 solved, children: N3, N4"
TM → LP: "New incumbent: 21"
```

**Cbc (shared memory):**
```
Worker checks shared incumbent before branching
Worker atomically updates incumbent if better
Lock-free node stealing from shared queue
```

<div class="code-connection">

**Code connections:**
- `CbcModel::branchAndBound()` — Main parallel B&B loop
- `BCP_tm_prob` — Tree Manager state in BCP
- `BCP_lp_prob::process_node()` — Worker node processing
- [HEkkDual](@/libraries/highs/HEkkDual.md) — Parallel simplex strategies in HiGHS

</div>

## Parallel Efficiency Trade-offs

### What We Gain

- **Wall-clock speedup**: 2 nodes at time 3 vs. sequential processing
- **Earlier incumbents**: Finding solutions faster enables more pruning

### What We Lose

- **Wasted work**: N4 created before sync (would have been pruned serially)
- **Communication overhead**: Synchronizing bounds takes time
- **Load imbalance**: Late in search, some workers idle (time 7)

### When Parallel Helps Most

| Scenario | Parallel Benefit |
|----------|-----------------|
| Wide, balanced tree | High (many independent nodes) |
| Deep, narrow tree | Low (few parallel opportunities) |
| Frequent integer solutions | Medium (more sync points) |
| Hard LP relaxations | Lower (LP time dominates) |

## Try It Below

Use **Next Step** to walk through the parallel search:

- Watch **workers activate** when assigned nodes
- See **parallel processing** at step 4 (two nodes at once)
- Notice the **sync delay** causing N4 creation
- Observe **pruning** after bound synchronization
- Track the **incumbent** improving from 21 to 22

