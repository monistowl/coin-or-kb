+++
title = "Bonmin"
description = "Basic Open-source Nonlinear Mixed INteger programming solver for convex MINLP"
template = "library.html"
sort_by = "title"

[extra]
layer = 3
+++

# Bonmin: Convex MINLP Solver

Bonmin (Basic Open-source Nonlinear Mixed INteger programming) solves **convex** mixed-integer nonlinear programs. It implements multiple algorithms that combine integer programming techniques with continuous NLP solvers.

**Layer 3** | 35 annotated files | Convex MINLP

---

## Problem Class

Bonmin solves problems of the form:

$$\min_{x,y} \quad f(x, y)$$

Subject to:
$$g(x, y) \leq 0$$
$$x \in \mathbb{R}^n, \quad y \in \{0,1\}^m$$

Where $f$ and $g$ are **convex** functions.

<div class="key-insight">

**Convexity requirement:** Bonmin assumes the continuous relaxation is convex. For nonconvex problems, use [Couenne](/libraries/couenne/) instead. Violating convexity may cause Bonmin to find suboptimal solutions or miss feasible regions.

</div>

---

## Algorithm Selection

Bonmin implements six algorithms, selectable via the `algorithm` option:

| Algorithm | Code | Description | When to Use |
|-----------|------|-------------|-------------|
| **B-BB** | 0 | NLP-based Branch-and-Bound | Most robust, slower |
| **B-OA** | 1 | Outer Approximation | Large MILPs, few nonlinear constraints |
| **B-QG** | 2 | Quesada-Grossmann single-tree | Balanced problems |
| **B-Hyb** | 3 | Hybrid OA + NLP (default) | Usually fastest |
| **B-Ecp** | 4 | Extended Cutting Plane | Highly nonlinear objectives |
| **B-IFP** | 5 | Iterated Feasibility Pump | Finding feasible solutions |

### Algorithm Details

**B-BB (NLP Branch-and-Bound):**
- Solves full NLP relaxation at every node
- Uses Ipopt for continuous subproblems
- Most reliable but computationally expensive

**B-OA (Outer Approximation):**
- Alternates between MILP master and NLP subproblems
- MILP provides lower bound, NLP provides feasible points
- Generates linearization cuts from NLP solutions

**B-QG (Quesada-Grossmann):**
- Single B&B tree with OA cuts generated during search
- Adds cuts at integer-feasible nodes
- Often faster than pure OA

**B-Hyb (Hybrid - Default):**
- Combines OA cuts with occasional NLP solves
- Solves NLP at "important" nodes (root, promising candidates)
- Typically best performance across problem classes

---

## Outer Approximation Cuts

For a convex constraint $g(x) \leq 0$ at solution point $x^*$:

$$g(x^*) + \nabla g(x^*)^T (x - x^*) \leq 0$$

This **linear outer approximation** is valid because $g$ is convex. Collecting cuts from multiple NLP solutions progressively tightens the approximation.

```
                    True feasible region (convex)
                   /
     ─────────────●─────────────  ← OA cut from x₁*
                 ╱ ╲
     ──────────●───●────────────  ← OA cuts tighten
              ╱     ╲
     ────────●───────●──────────  ← More cuts → better approximation
            (MILP feasible region shrinks toward true region)
```

---

## Key Components

### Solver Interfaces

| Class | Purpose |
|-------|---------|
| `BonminSetup` | Algorithm configuration and initialization |
| `OsiTMINLPInterface` | Osi wrapper around TMINLP problems |
| `TNLPSolver` | Abstract NLP solver interface |
| `IpoptSolver` | Ipopt-based NLP solver |
| `FilterSolver` | FilterSQP-based NLP solver |

### Heuristics

| Class | Description |
|-------|-------------|
| `HeuristicFPump` | Feasibility pump for finding initial solutions |
| `HeuristicDive` | Diving heuristics (fractional, vector length) |
| `HeuristicRINS` | Relaxation Induced Neighborhood Search |
| `HeuristicLocalBranching` | Local branching around incumbent |
| `MilpRounding` | Round MILP solution to MINLP feasibility |

### Cut Generators

| Class | Description |
|-------|-------------|
| `OACutGenerator2` | Main OA cut generator |
| `EcpCuts` | Extended cutting plane cuts |
| `LinearCutsGenerator` | Linear cuts from quadratic constraints |
| `OaFeasChecker` | Feasibility checking for OA |

---

## Feasibility Pump

The Feasibility Pump finds integer-feasible solutions by alternating:

1. **Round:** $\tilde{y} = \text{round}(y^*)$ for integer variables
2. **Project:** Solve NLP to minimize distance to $\tilde{y}$

$$\min_{x,y} \quad \|y - \tilde{y}\|_p \quad \text{s.t.} \quad g(x,y) \leq 0$$

3. **Check:** If $y^* = \tilde{y}$, found feasible solution
4. **Repeat:** Otherwise, iterate with cycle detection

---

## Branching Strategies

### Strong Branching
Solve NLP subproblems for candidate variables to estimate bound improvement:

```cpp
class QpBranchingSolver {
    // Solve QP approximation for fast strong branching
    // Much faster than full NLP strong branching
};
```

### Pseudocost Branching
Track historical bound changes per variable:
- `BonPseudoCosts`: Maintain pseudocost statistics
- Blend with strong branching via reliability branching

---

## Usage Example

```cpp
#include "BonBonminSetup.hpp"
#include "BonCbc.hpp"

// Define your MINLP problem (inherit from TMINLP)
class MyMINLP : public Bonmin::TMINLP {
    // ... implement eval_f, eval_g, eval_grad_f, etc.
};

int main() {
    Bonmin::BonminSetup bonmin;
    bonmin.initializeOptionsAndJournalist();

    // Set algorithm (default is B-Hyb)
    bonmin.options()->SetStringValue("algorithm", "B-Hyb");

    // Initialize with your problem
    SmartPtr<MyMINLP> tminlp = new MyMINLP();
    bonmin.initialize(tminlp);

    // Solve
    Bonmin::Bab bb;
    bb(bonmin);

    // Get solution
    if (bb.bestSolution()) {
        // Access optimal values
    }
}
```

---

## Source Files

### Core Setup
| File | Description |
|------|-------------|
| [BonBonminSetup.hpp](/browser/?library=Bonmin&path=src/Algorithms/BonBonminSetup.hpp) | Algorithm selection and initialization |
| [BonBabSetupBase.hpp](/browser/?library=Bonmin&path=src/Algorithms/BonBabSetupBase.hpp) | Base B&B configuration |
| [BonTMINLP.hpp](/browser/?library=Bonmin&path=src/Interfaces/BonTMINLP.hpp) | Problem interface |

### Algorithms
| File | Description |
|------|-------------|
| [BonOACutGenerator2.hpp](/browser/?library=Bonmin&path=src/Algorithms/OaGenerators/BonOACutGenerator2.hpp) | Outer approximation cuts |
| [BonEcpCuts.hpp](/browser/?library=Bonmin&path=src/Algorithms/OaGenerators/BonEcpCuts.hpp) | Extended cutting plane |
| [BonOuterApprox.hpp](/browser/?library=Bonmin&path=src/Algorithms/QuadCuts/BonOuterApprox.hpp) | Quadratic OA |

### Heuristics
| File | Description |
|------|-------------|
| [BonHeuristicFPump.hpp](/browser/?library=Bonmin&path=src/CbcBonmin/Heuristics/BonHeuristicFPump.hpp) | Feasibility pump |
| [BonHeuristicDive.hpp](/browser/?library=Bonmin&path=src/CbcBonmin/Heuristics/BonHeuristicDive.hpp) | Diving heuristics |
| [BonHeuristicRINS.hpp](/browser/?library=Bonmin&path=src/CbcBonmin/Heuristics/BonHeuristicRINS.hpp) | RINS heuristic |

---

## Dependencies

- **Cbc:** Branch-and-cut MILP solver for master problems
- **Ipopt:** Interior point NLP solver for continuous subproblems
- **CoinUtils:** Sparse matrix infrastructure
- **Osi:** Solver interface abstraction

---

## References

- Bonami, P., et al. (2008). "An algorithmic framework for convex mixed integer nonlinear programs", Discrete Optimization 5(2):186-204
- Duran, M.A., Grossmann, I.E. (1986). "An outer-approximation algorithm for a class of mixed-integer nonlinear programs", Mathematical Programming 36:307-339
- Quesada, I., Grossmann, I.E. (1992). "An LP/NLP based branch and bound algorithm for convex MINLP optimization problems", Computers & Chemical Engineering 16:937-947

