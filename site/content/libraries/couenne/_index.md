+++
title = "Couenne"
description = "Convex Over and Under ENvelopes for Nonlinear Estimation - global optimizer for nonconvex MINLP"
template = "library.html"
sort_by = "title"

[extra]
layer = 3
+++

# Couenne: Global Optimization for Nonconvex MINLP

Couenne (Convex Over and Under ENvelopes for Nonlinear Estimation) solves **nonconvex** mixed-integer nonlinear programs to **global optimality**. Unlike Bonmin (which assumes convexity), Couenne can prove that it has found the globally optimal solution even for nonconvex problems.

**Layer 3** | 32 annotated files | Global Optimization

---

## Problem Class

Couenne handles the most general class of MINLP:

$$\min_{x,y} \quad f(x, y)$$

Subject to:
$$g(x, y) \leq 0$$
$$x \in \mathbb{R}^n, \quad y \in \{0,1\}^m$$

Where $f$ and $g$ can be **nonconvex** functions including:
- Bilinear and multilinear terms ($xy$, $xyz$)
- Polynomial expressions ($x^2$, $x^3$, $x^{0.5}$)
- Trigonometric functions ($\sin$, $\cos$)
- Exponentials and logarithms

<div class="key-insight">

**Bonmin vs. Couenne:** If your problem is convex, use Bonmin—it's faster. If your problem is nonconvex (or you don't know), use Couenne—it guarantees global optimality but takes longer.

</div>

---

## Spatial Branch-and-Bound

Couenne extends branch-and-bound from integer variables to continuous domains:

```
Standard B&B:     Branch on integer variables
Spatial B&B:      Branch on continuous variables too
```

### Why Branch on Continuous Variables?

For nonconvex functions, the convex relaxation may be weak:

```
                    True nonconvex function
                   /
    ┌─────────────●─────────────┐
    │            ╱ ╲            │
    │           ╱   ╲           │  ← Large gap between
    │──────────●─────●──────────│     function and envelope
    │         ╱       ╲         │
    │        ╱         ╲        │
    └───────●───────────●───────┘
            │           │
            lb          ub
```

By subdividing the domain `[lb, ub]` into smaller intervals, the convex envelope becomes tighter:

```
    ┌─────●─────┐     ┌─────●─────┐
    │    ╱╲     │     │    ╱╲     │
    │───●──●────│     │───●──●────│  ← Tighter envelopes
    │  ╱    ╲   │     │  ╱    ╲   │     on smaller domains
    │ ╱      ╲  │     │ ╱      ╲  │
    └●────────●─┘     └●────────●─┘
     lb    mid         mid    ub
```

---

## Reformulation via Auxiliary Variables

Couenne transforms complex expressions into simple forms using auxiliary variables:

### Standardization Process

**Original:** $\min f(g(h(x)))$

**Reformulated:**
$$w_1 = h(x) \quad \text{(innermost)}$$
$$w_2 = g(w_1)$$
$$w_3 = f(w_2) \quad \text{(objective)}$$

### Benefits of Reformulation

1. **Simpler convexification:** Each $w_i = f_i(\ldots)$ is a simple expression with known convex envelope
2. **Structured propagation:** Bound tightening through DAG is systematic
3. **Modular cuts:** Add cuts for each simple relation independently

### Expression Ranking

Variables are ranked by depth in the expression DAG:

```cpp
rank(original_var) = 1
rank(w = f(x)) = rank(x) + 1
rank(w = f(x1,...,xk)) = 1 + max{rank(xi)}
```

Higher rank means deeper in DAG → branching has more propagation impact.

---

## Bound Tightening Techniques

Couenne implements multiple bound tightening strategies:

### Feasibility-Based Bound Tightening (FBBT)

Propagate bounds through expression DAG:

For $w = x \cdot y$ with $x \in [l_x, u_x]$, $y \in [l_y, u_y]$:

$$w^L = \min\{l_x l_y, l_x u_y, u_x l_y, u_x u_y\}$$
$$w^U = \max\{l_x l_y, l_x u_y, u_x l_y, u_x u_y\}$$

### Optimization-Based Bound Tightening (OBBT)

Solve LPs to find tightest bounds:

$$x^L_i = \min x_i \quad \text{s.t. convex relaxation}$$
$$x^U_i = \max x_i \quad \text{s.t. convex relaxation}$$

### Two-Implied Bound Tightening

Combine pairs of constraints for tighter bounds than single-constraint FBBT:

**Example:**
- $x + y \geq 2$
- $x - y \geq 1$
- With $x \in [0,4]$, $y \in [0,1]$

Single-constraint FBBT gives $x \geq 1$. Adding the constraints gives $2x \geq 3$, so $x \geq 1.5$.

---

## Branching Strategies

### Spatial Branching Objects

For auxiliary variable $w = f(x)$, infeasibility is:

$$\text{infeasibility}(w) = |w_{\text{current}} - f(x_{\text{current}})|$$

This measures the **relaxation gap**—how far the LP solution is from satisfying the true nonlinear constraint.

### Branching Point Selection

| Strategy | Description | Best For |
|----------|-------------|----------|
| **MID_INTERVAL** | $\alpha \cdot l + (1-\alpha) \cdot x^* + \alpha \cdot u$ | Safe default |
| **MIN_AREA** | Minimize total envelope area | Tight relaxations |
| **LP_CENTRAL** | Branch at LP solution $x^*$ | When LP is informative |
| **LP_CLAMPED** | LP solution clamped away from bounds | Avoid tiny subproblems |
| **BALANCED** | Balance improvement on both branches | Balanced trees |

### Three-Way Branching

For some expressions, three-way branching is effective:
- Left: $x \leq b_1$
- Center: $b_1 \leq x \leq b_2$
- Right: $x \geq b_2$

---

## Convexification Cuts

### Expression-Specific Envelopes

Each expression type has tailored convex relaxations:

| Expression | Lower Envelope | Upper Envelope |
|------------|----------------|----------------|
| $x^2$ | Secant line | Parabola itself (convex) |
| $xy$ (bilinear) | McCormick underestimators | McCormick overestimators |
| $\log(x)$ | Secant | Tangent lines |
| $e^x$ | Tangent lines | Secant |

### McCormick Envelopes for Bilinear Terms

For $w = xy$ with $x \in [l_x, u_x]$, $y \in [l_y, u_y]$:

**Underestimators:**
$$w \geq l_x y + x l_y - l_x l_y$$
$$w \geq u_x y + x u_y - u_x u_y$$

**Overestimators:**
$$w \leq u_x y + x l_y - u_x l_y$$
$$w \leq l_x y + x u_y - l_x u_y$$

### Cross-Convexification

Exploits algebraic identities between auxiliary variables:

**Example:** If $w_3 = \log(x_1)$, $w_4 = \log(x_2)$, $w_5 = x_1 \cdot x_2$:

Then $w_3 + w_4 = \log(w_5)$ provides a valid cut from algebraic identity.

---

## Key Components

### Core Classes

| Class | Purpose |
|-------|---------|
| `CouenneProblem` | Problem representation with expression DAG |
| `exprAux` | Auxiliary variable $w = f(x)$ |
| `CouenneObject` | Branching object for spatial B&B |
| `CouenneChooseVariable` | Variable selection for branching |

### Bound Tightening

| Class | Description |
|-------|-------------|
| `CouenneFixPoint` | FBBT through expression DAG |
| `CouenneAggrProbing` | OBBT via LP optimization |
| `CouenneTwoImplied` | Two-constraint implied bounds |
| `CouenneMultiVarProbe` | Multi-variable probing |

### Cut Generators

| Class | Description |
|-------|-------------|
| `CouenneCutGenerator` | Main convexification cuts |
| `CouenneCrossConv` | Cuts from algebraic identities |
| `CouenneDisjCuts` | Disjunctive cuts |

### Heuristics

| Class | Description |
|-------|-------------|
| `BonNlpHeuristic` | NLP heuristic for feasible solutions |
| `CouenneIterativeRounding` | Iterative rounding heuristic |

---

## Usage Example

```cpp
#include "BonCouenneSetup.hpp"
#include "BonCbc.hpp"

// Couenne extends Bonmin's interface
int main() {
    Couenne::CouenneSetup couenne;
    couenne.InitializeCouenne();

    // Load problem (e.g., from AMPL .nl file)
    couenne.readProblem("problem.nl");

    // Configure spatial B&B
    couenne.options()->SetStringValue("branching_object", "expr_obj");
    couenne.options()->SetStringValue("branch_pt_select", "mid_interval");

    // Set bound tightening options
    couenne.options()->SetStringValue("feasibility_bt", "yes");
    couenne.options()->SetStringValue("optimality_bt", "yes");

    // Solve
    Bonmin::Bab bb;
    bb(couenne);

    // Global optimum found (if successful)
    if (bb.bestSolution()) {
        // Solution is provably globally optimal
    }
}
```

---

## Source Files

### Core Infrastructure
| File | Description |
|------|-------------|
| [CouenneProblem.hpp](/browser/?library=Couenne&path=src/problem/CouenneProblem.hpp) | Problem representation |
| [CouenneExprAux.hpp](/browser/?library=Couenne&path=src/expression/CouenneExprAux.hpp) | Auxiliary variables |
| [CouenneExpression.hpp](/browser/?library=Couenne&path=src/expression/CouenneExpression.hpp) | Expression base class |

### Branching
| File | Description |
|------|-------------|
| [CouenneObject.hpp](/browser/?library=Couenne&path=src/branch/CouenneObject.hpp) | Spatial branching objects |
| [CouenneChooseVariable.hpp](/browser/?library=Couenne&path=src/branch/CouenneChooseVariable.hpp) | Variable selection |
| [CouenneVarObject.hpp](/browser/?library=Couenne&path=src/branch/CouenneVarObject.hpp) | Variable-based branching |

### Bound Tightening
| File | Description |
|------|-------------|
| [CouenneTwoImplied.hpp](/browser/?library=Couenne&path=src/bound_tightening/twoImpliedBT/CouenneTwoImplied.hpp) | Two-constraint FBBT |
| [CouenneMultiVarProbe.hpp](/browser/?library=Couenne&path=src/bound_tightening/CouenneMultiVarProbe.hpp) | Multi-variable probing |

### Cuts
| File | Description |
|------|-------------|
| [CouenneCrossConv.hpp](/browser/?library=Couenne&path=src/cut/crossconv/CouenneCrossConv.hpp) | Cross-convexification cuts |
| [CouenneDisjCuts.hpp](/browser/?library=Couenne&path=src/disjunctive/CouenneDisjCuts.hpp) | Disjunctive cuts |

---

## Dependencies

- **Bonmin:** MINLP infrastructure (Couenne extends Bonmin)
- **Ipopt:** NLP solver for continuous relaxations
- **Cbc:** Branch-and-bound framework
- **CoinUtils:** Sparse matrix infrastructure

---

## Comparison: Convex vs. Global Optimization

| Aspect | Bonmin (Convex) | Couenne (Global) |
|--------|-----------------|------------------|
| Problem class | Convex MINLP | Any MINLP |
| Guarantee | Global (by convexity) | Global (proven) |
| Relaxation | LP/NLP | Convex envelope |
| Branching | Integer only | Integer + continuous |
| Speed | Faster | Slower |
| Typical use | Engineering design | Process synthesis |

---

## References

- Belotti, P., et al. (2009). "Branching and bounds tightening techniques for non-convex MINLP", Optimization Methods and Software 24(4-5):597-634
- Tawarmalani, M., Sahinidis, N.V. (2005). "A polyhedral branch-and-cut approach to global optimization", Mathematical Programming 103(2):225-249
- McCormick, G.P. (1976). "Computability of global solutions to factorable nonconvex programs", Mathematical Programming 10:147-175

