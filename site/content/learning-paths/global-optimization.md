+++
title = "Global Optimization"
description = "From convex to nonconvex: spatial branch-and-bound and MINLP"
template = "learning-path.html"
weight = 4

[extra]
tagline = "Find global optima in nonconvex problems"
duration = "~5 hours"
prereqs = "MIP Journey, Nonlinear Optimization"
steps = [
    { id = "convex-vs-nonconvex", title = "Convex vs. Nonconvex Optimization", duration = "25 min" },
    { id = "minlp-intro", title = "Introduction to MINLP", duration = "30 min" },
    { id = "spatial-bb", title = "Spatial Branch-and-Bound", duration = "45 min" },
    { id = "convexification", title = "Convexification and Relaxations", duration = "40 min" },
    { id = "outer-approximation", title = "Outer Approximation", duration = "35 min" },
    { id = "bonmin-couenne", title = "Bonmin and Couenne in Practice", duration = "40 min" },
]
+++

<div class="key-insight">

This path brings together MIP and NLP to tackle the hardest class of optimization problems: finding **global** optima when the problem is nonconvex. You'll learn why local methods can get stuck, how spatial branch-and-bound guarantees global optimality, and how solvers like Bonmin and Couenne make this practical.

</div>

## Prerequisites

You should have completed:
- [MIP Journey](/learning-paths/mip-journey/) — Branch-and-bound, cutting planes, LP relaxations
- [Nonlinear Optimization](/learning-paths/nonlinear-optimization/) — Newton's method, interior point, KKT conditions

Or be comfortable with:
- Branch-and-bound trees and bounding
- Nonlinear optimization and KKT conditions
- Why convexity matters for optimization

---

<h2 id="convex-vs-nonconvex">1. Convex vs. Nonconvex Optimization</h2>

The distinction between convex and nonconvex problems is **the** fundamental divide in optimization.

### What is Convexity?

A function $f: \mathbb{R}^n \to \mathbb{R}$ is **convex** if:
$$f(\lambda x + (1-\lambda) y) \leq \lambda f(x) + (1-\lambda) f(y) \quad \forall x, y, \; \lambda \in [0,1]$$

Visually: the line segment between any two points on the graph lies above the graph.

<div class="concept-box">
<h4>The Golden Property of Convexity</h4>

For convex problems, **every local minimum is a global minimum**.

This means any descent algorithm that finds a local optimum has solved the problem completely. Newton's method, gradient descent, interior point — they all work reliably on convex problems.
</div>

### Examples

| Convex | Nonconvex |
|--------|-----------|
| $x^2$ | $\sin(x)$ |
| $e^x$ | $x^2 - x^4$ |
| $\|x\|$ | $x_1 x_2$ (bilinear) |
| LP, QP (with PSD $Q$) | General polynomials |

### The Nonconvex Challenge

For nonconvex problems:
- Multiple local minima exist
- Local methods find *a* local minimum, not *the* global minimum
- No polynomial-time algorithm is known (NP-hard in general)

<div class="code-connection">

In COIN-OR:
- **Ipopt** finds local optima (assumes convexity or accepts local solutions)
- **Bonmin** handles convex MINLP (integer + convex nonlinear)
- **Couenne** handles nonconvex MINLP (global optimization)

</div>

---

<h2 id="minlp-intro">2. Introduction to MINLP</h2>

**Mixed-Integer Nonlinear Programming (MINLP)** combines the challenges of MIP and NLP:

$$\min_{x,y} \quad f(x, y)$$
$$\text{s.t.} \quad g(x, y) \leq 0$$
$$\quad\quad h(x, y) = 0$$
$$\quad\quad x \in \mathbb{R}^n, \; y \in \mathbb{Z}^p$$

Where $f$, $g$, and $h$ may be nonlinear.

### Why MINLP?

Real problems often have both:
- **Discrete decisions**: Build a reactor or not, choose among designs
- **Nonlinear physics**: Chemical equilibria, pressure-flow relations, economies of scale

<div class="concept-box">
<h4>The MINLP Landscape</h4>

| Problem Class | Difficulty | Solvers |
|---------------|------------|---------|
| LP | Polynomial | Clp, simplex |
| Convex NLP | Polynomial | Ipopt, interior point |
| MIP (linear) | NP-hard | Cbc, branch-and-cut |
| Convex MINLP | NP-hard | Bonmin |
| Nonconvex MINLP | Very hard | Couenne, SCIP, BARON |

Nonconvex MINLP is the hardest class — it combines combinatorial explosion (integers) with nonconvexity (local optima).
</div>

### Applications

- **Process design**: Chemical plant configuration with physics constraints
- **Network design**: Routing with nonlinear costs
- **Pooling problems**: Blending with quality constraints
- **Unit commitment**: Power generation scheduling

---

<h2 id="spatial-bb">3. Spatial Branch-and-Bound</h2>

Standard branch-and-bound branches on integer variables. **Spatial branch-and-bound** extends this to branch on continuous variables too — enabling global optimization of nonconvex problems.

### The Key Idea

For nonconvex problems, LP relaxation isn't enough. Even with integer variables fixed, the nonlinear relaxation may have multiple local optima.

**Solution**: Branch on *continuous variables* to partition the domain until the problem becomes "easy enough" to solve globally.

### The Algorithm

```
Initialize:
  - Root node = original problem
  - Global upper bound = +∞ (best solution found)
  - Global lower bound = -∞ (best possible)

While nodes remain:
  1. SELECT a node
  2. SOLVE a convex relaxation (underestimator of the original)
  3. If relaxation infeasible: PRUNE
  4. If relaxation bound ≥ upper bound: PRUNE
  5. If solution is feasible for original problem:
       UPDATE upper bound
       PRUNE
  6. Else:
       Choose variable to BRANCH (integer or continuous)
       Create children with tighter bounds
```

### Continuous Branching

For a continuous variable $x_j$ with bounds $[l_j, u_j]$, branch at some point $\hat{x}_j$:
- Left child: $x_j \in [l_j, \hat{x}_j]$
- Right child: $x_j \in [\hat{x}_j, u_j]$

**Why this helps**: Tighter bounds → tighter convex relaxations → better lower bounds → more pruning.

<div class="key-insight">

Spatial B&B converges to global optimum because:
1. Each branch tightens variable bounds
2. Convex relaxations become tighter as bounds shrink
3. In the limit (infinitely small boxes), relaxation equals original problem

</div>

### Branching Strategies

| Strategy | Description |
|----------|-------------|
| Widest range | Branch on variable with largest $u_j - l_j$ |
| Most violated | Branch on variable with largest relaxation gap |
| Reliability | Use history of bound improvement |
| Violation transfer | Branch to reduce maximum constraint violation |

<div class="code-connection">

In Couenne (`CouenneProblem.cpp`):
```cpp
// Spatial branching considers both integer and continuous variables
// The branching object encodes bounds for the new subproblems
```

</div>

---

<h2 id="convexification">4. Convexification and Relaxations</h2>

The quality of spatial B&B depends entirely on the quality of the convex relaxations. **Convexification** creates convex underestimators of nonconvex functions.

### McCormick Envelopes

For a bilinear term $w = x_1 x_2$ with $x_1 \in [l_1, u_1]$ and $x_2 \in [l_2, u_2]$:

The **McCormick envelope** provides the tightest convex relaxation using four linear inequalities:

$$w \geq l_1 x_2 + l_2 x_1 - l_1 l_2$$
$$w \geq u_1 x_2 + u_2 x_1 - u_1 u_2$$
$$w \leq u_1 x_2 + l_2 x_1 - u_1 l_2$$
$$w \leq l_1 x_2 + u_2 x_1 - l_1 u_2$$

<div class="concept-box">
<h4>Why McCormick Works</h4>

At the corner points $(l_1, l_2)$, $(l_1, u_2)$, $(u_1, l_2)$, $(u_1, u_2)$, the envelope is exact ($w = x_1 x_2$).

Between corners, the envelope provides a convex underestimator. As bounds tighten, the envelope becomes tighter — eventually exact when the box shrinks to a point.
</div>

### Other Convexifications

| Function Type | Relaxation |
|---------------|------------|
| $x^2$ | Already convex (no relaxation needed) |
| $x^k$ (odd $k$) | Secant relaxation |
| $\sin(x)$, $\cos(x)$ | Linear underestimators over bounded domain |
| $e^x$ | Secant (concave over-approximation) |
| $\log(x)$ | Secant (convex under-approximation) |
| $x_1 / x_2$ | Reformulate as $x_1 = w \cdot x_2$, then McCormick |

### Factorable Functions

A key insight: Most nonlinear functions can be **factored** into elementary operations:
$$f(x) = x_1^2 + \sin(x_2) + x_1 x_3$$

Introduce auxiliary variables:
- $w_1 = x_1^2$ (convex, no relaxation)
- $w_2 = \sin(x_2)$ (bounded relaxation)
- $w_3 = x_1 x_3$ (McCormick)
- $f = w_1 + w_2 + w_3$ (linear)

This systematic approach enables automatic convexification.

<div class="code-connection">

Couenne builds an **expression tree** for each constraint, then generates relaxations for each node:
```cpp
// CouenneExprMul.cpp handles multiplication
// exprMul::generateCuts() creates McCormick cuts
```

</div>

---

<h2 id="outer-approximation">5. Outer Approximation</h2>

For **convex** MINLP, there's a more efficient approach than spatial B&B: **Outer Approximation (OA)** alternates between an MILP master problem and NLP subproblems.

### The Idea

Instead of branching on continuous variables, use linear cuts to approximate the nonlinear feasible region from outside.

### The Algorithm

```
Initialize: Set of linearizations L = {}

Repeat:
  1. MILP MASTER: Solve
       min  c^T x + d^T y
       s.t. linearizations in L
            y ∈ Z^p
     Get solution (x*, y*)

  2. NLP SUBPROBLEM: Fix integers y = y*, solve
       min  c^T x + d^T y*
       s.t. g(x, y*) ≤ 0, h(x, y*) = 0
     Get solution x̂ (or infeasibility certificate)

  3. ADD LINEARIZATIONS:
     - At x̂: g(x̂) + ∇g(x̂)^T (x - x̂) ≤ 0
     - If infeasible: feasibility cuts

Until: MILP and NLP solutions match
```

### Why It Works (for Convex Problems)

<div class="key-insight">

For convex $g$, the linearization $g(x̂) + \nabla g(x̂)^T(x - x̂) \leq 0$ is a **valid inequality** — it never cuts off any feasible point.

After finitely many iterations, enough linearizations accumulate to identify the optimal integer assignment.
</div>

### Bonmin's Modes

Bonmin implements several OA variants:

| Mode | Description |
|------|-------------|
| B-OA | Pure outer approximation |
| B-BB | NLP-based branch-and-bound |
| B-QG | Quesada-Grossmann single-tree |
| B-Hyb | Hybrid (combines above) |

The hybrid mode is often fastest — it uses OA for quick bounds and B&B for difficult nodes.

<div class="code-connection">

```cpp
// BonOaDecBase.cpp implements the OA decomposition
// Each NLP solve generates cuts added to the MILP
```

</div>

---

<h2 id="bonmin-couenne">6. Bonmin and Couenne in Practice</h2>

COIN-OR provides two MINLP solvers that build on the foundation libraries:

### Bonmin (Basic Open-source Nonlinear Mixed INteger programming)

**For**: Convex MINLP

**Architecture**:
- Uses **Cbc** for MILP (master problem, branch-and-bound)
- Uses **Ipopt** for NLP (subproblems)
- Uses **Cgl** for cutting planes

**Strengths**:
- Efficient for convex problems
- Multiple algorithm modes
- Warm-starting between solves

**Limitations**:
- May find local (not global) optima for nonconvex problems
- Assumes constraint qualification holds

### Couenne (Convex Over and Under ENvelopes for Nonlinear Estimation)

**For**: Nonconvex MINLP (global optimization)

**Architecture**:
- Uses **Cbc** for the branch-and-bound tree
- Uses **Ipopt** for local NLP solves (upper bounds)
- Implements spatial branching and automatic convexification

**Key Features**:
- **Expression decomposition**: Breaks complex functions into simple operations
- **Bound tightening**: FBBT and OBBT to tighten variable domains
- **Cut generation**: McCormick, disjunctive cuts, and more
- **Branching strategies**: On both integer and continuous variables

**Global Optimality Guarantee**: Couenne proves a solution is globally optimal when the gap between upper and lower bounds closes.

### When to Use Which

| Scenario | Solver |
|----------|--------|
| Convex MINLP | Bonmin (faster) |
| Nonconvex, need proof of optimality | Couenne |
| Nonconvex, good solution is enough | Ipopt + heuristics |
| Very large problems | Decomposition methods |

### Practical Tips

1. **Provide good bounds**: Tighter variable bounds = faster convergence
2. **Good starting point**: Help local solvers find good upper bounds
3. **Reformulate if possible**: Convex formulations are much faster
4. **Monitor gap**: The optimality gap shows progress
5. **Use presolve**: Can dramatically reduce problem size

<div class="code-connection">

Example Couenne call:
```cpp
// Set up OsiSolverInterface with the MINLP
CouenneProblem problem;
problem.readNl("myProblem.nl");

// Solve globally
CouenneSolver solver(&problem);
solver.solve();

// Get gap
double gap = solver.getOptimumBound() - solver.getBestFeasible();
```

</div>

---

## Summary

| Concept | Key Point |
|---------|-----------|
| Convexity | Local = global for convex problems |
| MINLP | Combines integer and nonlinear challenges |
| Spatial B&B | Branch on continuous variables for global optimization |
| Convexification | Create convex relaxations (McCormick, etc.) |
| Outer Approximation | Efficient for convex MINLP |
| Bonmin | Convex MINLP solver |
| Couenne | Global (nonconvex) MINLP solver |

Global optimization is computationally expensive but sometimes necessary — when local optima aren't good enough and you need a guarantee of global optimality.

## Next Steps

- Explore [Couenne source](/browser/?library=Couenne) in the browser
- Try the [derivation of branch-and-bound correctness](/derivations/branch-and-bound-correctness/)
- Read about [McCormick envelopes](/algorithms/mccormick-envelopes/) in detail
