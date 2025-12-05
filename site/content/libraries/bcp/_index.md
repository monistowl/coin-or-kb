+++
title = "BCP (Branch-Cut-Price)"
description = "Parallel framework for branch-cut-price algorithms with column and cut generation"
template = "library.html"
sort_by = "title"

[extra]
layer = 3
+++

# BCP: Branch-Cut-Price Framework

BCP is a parallel framework for implementing branch-cut-price algorithms. It handles the complexity of coordinating tree search across multiple processes while you focus on problem-specific logic.

**Layer 3** | 125 annotated files | Column generation + cutting planes

---

## Why BCP Matters

Branch-Cut-Price combines three powerful techniques:
- **Branch-and-Bound**: Systematic tree search for integer solutions
- **Cutting Planes**: Strengthen LP relaxations by adding violated inequalities
- **Column Generation**: Handle exponentially many variables via pricing

BCP provides the parallel infrastructure so you can implement these techniques without writing distributed systems code.

<div class="key-insight">

**When to use BCP:** Problems with special structure where standard MIP solvers struggle. Classic examples: vehicle routing, crew scheduling, cutting stock, network design. If your problem has a natural decomposition or exponentially many variables, BCP may outperform Cbc.

</div>

---

## Architecture Overview

BCP uses a master-worker architecture with specialized process types:

```
┌─────────────────────────────────────────────────────────────┐
│                    Tree Manager (TM)                        │
│  - Manages search tree and node selection                   │
│  - Tracks global upper/lower bounds                         │
│  - Schedules work to LP processes                           │
│  - Stores variables/cuts locally and distributed            │
└─────────────────────┬───────────────────────────────────────┘
                      │ assigns nodes
        ┌─────────────┼─────────────┐
        ▼             ▼             ▼
┌───────────┐   ┌───────────┐   ┌───────────┐
│  LP (0)   │   │  LP (1)   │   │  LP (n)   │
│           │   │           │   │           │
│ Solves LP │   │ Solves LP │   │ Solves LP │
│ relaxation│   │ relaxation│   │ relaxation│
└─────┬─────┘   └─────┬─────┘   └─────┬─────┘
      │               │               │
      ▼               ▼               ▼
┌───────────┐   ┌───────────┐   ┌───────────┐
│    CG     │   │    CG     │   │    VG     │
│ Cut Gen   │   │ Cut Gen   │   │ Var Gen   │
└───────────┘   └───────────┘   └───────────┘
```

### Process Types

| Process | Role | Key Class |
|---------|------|-----------|
| **TM** (Tree Manager) | Coordinator: manages tree, bounds, scheduling | `BCP_tm_prob` |
| **LP** (Linear Programming) | Worker: solves relaxations, applies cuts/columns | `BCP_lp_prob` |
| **CG** (Cut Generator) | Separation: finds violated inequalities | `BCP_cg_user` |
| **VG** (Variable Generator) | Pricing: generates improving columns | `BCP_vg_user` |

---

## User Customization

You implement problem-specific logic by subclassing user classes:

```cpp
// Tree Manager customization
class MyTM : public BCP_tm_user {
    void create_root(BCP_vec<BCP_var*>& vars,
                     BCP_vec<BCP_cut*>& cuts);  // Initial formulation
    void display_feasible_solution(const BCP_solution* sol);
};

// LP process customization
class MyLP : public BCP_lp_user {
    OsiSolverInterface* initialize_solver_interface();
    BCP_solution* test_feasibility(const BCP_vec<BCP_var*>& vars);
    void generate_cuts_in_lp(BCP_vec<BCP_cut*>& cuts);
    void generate_vars_in_lp(BCP_vec<BCP_var*>& vars);
    BCP_branching_decision select_branching_candidates(...);
};
```

---

## Included Applications

BCP ships with complete example applications demonstrating different algorithmic techniques:

### [Max-Cut](MC.md)
Graph partitioning to maximize cut weight. Demonstrates:
- **Cycle inequalities** for LP strengthening
- MST-based and shortest-path separation algorithms
- Local search heuristics (switch, edge-switch, Lin-Kernighan)

### [Cutting Stock (CSP)](CSP.md)
1D bin packing via Dantzig-Wolfe decomposition. Demonstrates:
- **Column generation** with knapsack pricing subproblems
- Horowitz-Sahni exact knapsack algorithm
- Pattern enumeration and perturbation for diversity

### [Multi-Commodity Flow (MCF)](MCF.md)
Network flow with multiple commodities. Three variants demonstrate:
- MCF-1: Basic decomposition approach
- MCF-2: Branching with delta encoding
- MCF-3: Parallel-safe branching with `BCP_user_data`

### Branch-and-Cut Template (BAC)
Generic B&C skeleton showing indexed vs algorithmic cuts.

---

## Key Concepts

### Delta Encoding
BCP transmits node changes rather than full descriptions:
- `BCP_obj_change`: What variables/cuts changed from parent
- `BCP_node_change`: Full node delta for reconstruction
- Dramatically reduces communication in parallel execution

### Indexed vs Algorithmic Objects
Two ways to represent variables and cuts:

| Type | Storage | Use Case |
|------|---------|----------|
| **Indexed** | Just an index, coefficients computed from problem data | When structure allows reconstruction |
| **Algorithmic** | Full coefficient vector stored | General cuts/variables |

### Warm Starting
`BCP_warmstart_basis` stores simplex basis status for efficient re-optimization after branching. Supports both local storage and distributed checkpointing.

---

## Source Files

### Core Framework (`Bcp/src/include/`)

| File | Description |
|------|-------------|
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_tm.hpp", text="BCP_tm.hpp") }} | Tree Manager: parallel B&B coordinator |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_lp.hpp", text="BCP_lp.hpp") }} | LP Worker: relaxation solving |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_cg.hpp", text="BCP_cg.hpp") }} | Cut Generator process |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_vg.hpp", text="BCP_vg.hpp") }} | Variable Generator process |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_branch.hpp", text="BCP_branch.hpp") }} | Branching decision structures |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_cut.hpp", text="BCP_cut.hpp") }} | Cut representation (core/indexed/algo) |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_var.hpp", text="BCP_var.hpp") }} | Variable representation |

### User Interface Classes

| File | Description |
|------|-------------|
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_tm_user.hpp", text="BCP_tm_user.hpp") }} | TM customization hooks |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_lp_user.hpp", text="BCP_lp_user.hpp") }} | LP customization hooks |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_cg_user.hpp", text="BCP_cg_user.hpp") }} | Cut generator hooks |
| {{ link(path="/browser/?library=Bcp&path=Bcp/src/include/BCP_vg_user.hpp", text="BCP_vg_user.hpp") }} | Variable generator hooks |

---

## Getting Started

1. **Study an example**: Start with Max-Cut (simplest) or CSP (column generation)
2. **Subclass user classes**: Implement `BCP_tm_user` and `BCP_lp_user` at minimum
3. **Define your objects**: Create `BCP_var` and `BCP_cut` subclasses for your problem
4. **Implement USER_initialize**: Factory method to create your user objects

```cpp
// Minimal entry point
class My_init : public USER_initialize {
    BCP_tm_user* tm_init(BCP_tm_prob& p, ...) { return new MyTM; }
    BCP_lp_user* lp_init(BCP_lp_prob& p) { return new MyLP; }
};

int main(int argc, char* argv[]) {
    My_init init;
    return bcp_main(argc, argv, &init);
}
```

---

## References

- Ralphs, T., Ladányi, L. (2001). "COIN/BCP User's Manual"
- Barnhart, C., et al. (1998). "Branch-and-Price: Column Generation for Solving Huge Integer Programs", Operations Research 46(3)
- Padberg, M., Rinaldi, G. (1991). "A Branch-and-Cut Algorithm for the Resolution of Large-Scale Symmetric Traveling Salesman Problems", SIAM Review

