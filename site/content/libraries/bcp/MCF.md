+++
title = "Multi-Commodity Flow Examples"
description = "Network flow decomposition with three variants demonstrating BCP branching patterns"
template = "class.html"

[extra]
library = "bcp"
header = "Bcp/examples/MCF-*/include/"
+++

# Multi-Commodity Flow: Branching Pattern Variants

The MCF examples demonstrate three different approaches to implementing branch-and-bound in BCP. All solve the same problem but handle branching state differently, illustrating key BCP design patterns.

---

## Problem Definition

**Given:**
- A network $G = (N, A)$ with arc capacities $u_a$ and costs $c_a$
- $K$ commodities, each with source $s_k$, sink $t_k$, and demand $d_k$

**Find:** Flow routing for all commodities minimizing total cost:

$$\min \sum_{k} \sum_{a} c_a f_a^k$$

Subject to:
- **Flow conservation:** $\sum_{a \in \delta^+(i)} f_a^k - \sum_{a \in \delta^-(i)} f_a^k = b_i^k \quad \forall i, k$
- **Bundle capacity:** $\sum_k f_a^k \leq u_a \quad \forall a$
- **Integrality:** $f_a^k \in \mathbb{Z}_+$

Where $b_i^k = d_k$ if $i = s_k$, $-d_k$ if $i = t_k$, else $0$.

<div class="key-insight">

**Key insight:** Without bundle constraints, the problem decomposes into $K$ independent shortest-path problems. The coupling constraints make it hard, but we can exploit this structure via Dantzig-Wolfe decomposition.

</div>

---

## Data Structures

All three variants share common data definitions:

```cpp
struct arc {
    int tail;
    int head;
    int lb;      // Lower bound
    int ub;      // Upper bound (capacity)
    double weight; // Cost
};

struct commodity {
    int source;
    int sink;
    int demand;
};

struct branch_decision {
    int arc_index;
    int lb;
    int ub;
};
```

---

## Variant Comparison

| Feature | MCF-1 | MCF-2 | MCF-3 |
|---------|-------|-------|-------|
| Branch history | Global | Delta encoded | User data |
| Parallel safety | No | Partial | Yes |
| Communication | Low | Medium | Higher |
| Complexity | Simplest | Intermediate | Most robust |

---

## MCF-1: Basic Approach

The simplest implementation stores branch decisions globally.

### Key Characteristics
- Branch history maintained as a simple vector
- Each node reconstructs full state from root
- Works well for sequential execution
- Not parallel-safe (shared state issues)

```cpp
class MCF1_lp : public BCP_lp_user {
    std::vector<MCF1_branch_decision> branch_history;

    void initialize_new_search_tree_node(...) {
        // Reconstruct bounds from full branch history
        for (const auto& decision : branch_history) {
            apply_bound_change(decision);
        }
    }
};
```

---

## MCF-2: Delta Encoding

Uses BCP's delta encoding to transmit only changes from parent.

### Key Characteristics
- `BCP_obj_change` tracks what changed since parent
- Reduced communication overhead
- Better memory efficiency
- Still requires careful state management

```cpp
// Parent node transmits only the new branching decision
void create_children(...) {
    // BCP handles encoding changes as deltas
    // Children receive parent state + delta
}
```

---

## MCF-3: User Data Pattern

The most robust approach using `BCP_user_data` for parallel-safe state.

### Key Characteristics
- Each node carries its own branch history
- `set_user_data_for_children` propagates state
- Parallel-safe: no shared mutable state
- Recommended for production use

```cpp
class MCF3_user : public BCP_user_data {
    std::vector<MCF3_branch_decision> branch_history;

    void pack(BCP_buffer& buf) const {
        // Serialize branch history for distribution
        buf.pack(branch_history.size());
        for (const auto& bd : branch_history) {
            buf.pack(bd.arc_index).pack(bd.lb).pack(bd.ub);
        }
    }
};

class MCF3_lp : public BCP_lp_user {
    void set_user_data_for_children(
        BCP_presolved_lp_brobj* best,
        const int selected) {
        // Create user_data for each child with updated history
        for (int i = 0; i < best->child_num; ++i) {
            auto* child_data = new MCF3_user(current_history);
            child_data->add_decision(branch_decisions[i]);
            best->user_data[i] = child_data;
        }
    }
};
```

<div class="key-insight">

**Why MCF-3 matters:** In parallel BCP, multiple LP processes work on different nodes simultaneously. If they share mutable state (like MCF-1's global history), race conditions occur. MCF-3's `user_data` pattern ensures each node is self-contained.

</div>

---

## Branching on Aggregate Flow

All variants branch on aggregate arc flow:

$$\text{aggregate}_a = \sum_k f_a^k$$

When $\text{aggregate}_a$ is fractional:
- **Left child:** $\text{aggregate}_a \leq \lfloor \text{value} \rfloor$
- **Right child:** $\text{aggregate}_a \geq \lceil \text{value} \rceil$

This affects all commodities using that arc, not just one.

---

## Column Generation (Price-and-Branch)

The MCF examples can use column generation:

1. **Master problem:** Select commodity paths to meet demand
2. **Pricing:** Find improving paths via shortest path
3. **Variables:** Each variable is a commodity-specific path

```cpp
void generate_vars_in_lp(...) {
    // For each commodity, solve shortest path with current duals
    for (int k = 0; k < numcommodities; ++k) {
        // Compute arc costs = original_cost - dual_value
        // Find shortest path from source[k] to sink[k]
        // If reduced cost < 0, add path as new variable
    }
}
```

---

## Source Files

### MCF-1 (Basic)
| File | Description |
|------|-------------|
| [MCF1_data.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-1/include/MCF1_data.hpp) | Network and commodity data |
| [MCF1_lp.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-1/include/MCF1_lp.hpp) | LP process with global history |
| [MCF1_var.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-1/include/MCF1_var.hpp) | Flow variables |

### MCF-2 (Delta)
| File | Description |
|------|-------------|
| [MCF2_data.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-2/include/MCF2_data.hpp) | Network data |
| [MCF2_lp.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-2/include/MCF2_lp.hpp) | LP with delta encoding |

### MCF-3 (User Data)
| File | Description |
|------|-------------|
| [MCF3_data.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-3/include/MCF3_data.hpp) | Network data |
| [MCF3_lp.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-3/include/MCF3_lp.hpp) | LP with user_data pattern |
| [MCF3_var.hpp](/browser/?library=Bcp&path=Bcp/examples/MCF-3/include/MCF3_var.hpp) | Path variables |

---

## When to Use Each Pattern

- **MCF-1 style:** Prototyping, sequential execution, simple problems
- **MCF-2 style:** When communication bandwidth is constrained
- **MCF-3 style:** Production parallel code, complex branching logic

---

## References

- Barnhart, C., et al. (2000). "Using Branch-and-Price-and-Cut to Solve Origin-Destination Integer Multicommodity Flow Problems", Operations Research
- Ahuja, R.K., Magnanti, T.L., Orlin, J.B. (1993). "Network Flows: Theory, Algorithms, and Applications", Prentice Hall

