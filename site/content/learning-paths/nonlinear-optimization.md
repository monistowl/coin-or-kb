+++
title = "Nonlinear Optimization"
description = "From calculus to interior point methods and mixed-integer nonlinear programming"
template = "learning-path.html"
weight = 3

[extra]
tagline = "Master the algorithms that solve nonlinear programming problems"
duration = "~5 hours"
prereqs = "Calculus, LP Fundamentals"
steps = [
    { id = "why-nlp", title = "Why Nonlinear Optimization?", duration = "15 min" },
    { id = "kkt-conditions", title = "KKT Optimality Conditions", duration = "30 min" },
    { id = "newtons-method", title = "Newton's Method", duration = "30 min" },
    { id = "barrier-method", title = "Interior Point Methods", duration = "45 min" },
    { id = "ipopt-algorithm", title = "Inside Ipopt", duration = "45 min" },
    { id = "minlp-intro", title = "Mixed-Integer NLP", duration = "30 min" },
    { id = "spatial-bb", title = "Spatial Branch-and-Bound", duration = "45 min" },
]
+++

<div class="key-insight">

This path takes you from understanding why nonlinearity makes optimization hard, through the elegant mathematics of interior point methods, to the frontier of global optimization for nonconvex problems. By the end, you'll understand how Ipopt, Bonmin, and Couenne actually work.

</div>

## Check Your Knowledge

Before starting, make sure you're comfortable with:

- Derivatives and gradients: $\nabla f(x)$
- The chain rule
- Matrix calculus basics (Hessians)
- LP fundamentals (basis, dual, complementary slackness)

If you need a refresher on calculus, Khan Academy's [multivariable calculus](https://www.khanacademy.org/math/multivariable-calculus) is excellent.

---

<h2 id="why-nlp">1. Why Nonlinear Optimization?</h2>

Many real-world problems can't be expressed with linear functions. **Nonlinear Programming (NLP)** handles:

### Problem Types

| Feature | LP | NLP |
|---------|----|----|
| Objective | $c^Tx$ | $f(x)$ (any smooth function) |
| Constraints | $Ax = b$ | $g(x) = 0$, $h(x) \leq 0$ |
| Feasible region | Polyhedron | Curved, possibly disconnected |
| Optimal point | Always at vertex | Can be anywhere |

### Example: Portfolio Optimization

**Markowitz Model:** Minimize portfolio variance (risk) for a given return:

$$\min_w \quad w^T \Sigma w \quad \text{(quadratic)}$$
$$\text{s.t.} \quad \mu^T w \geq r_{\min}, \quad \sum_i w_i = 1, \quad w \geq 0$$

The objective $w^T \Sigma w$ is **quadratic**—not linear. We need NLP methods.

### The Challenge: Local vs Global Optima

<div class="key-insight">

**The fundamental challenge:** A point where you can't improve locally might not be the best globally.

For convex problems, local = global. For nonconvex problems, we might get stuck at local optima.

</div>

```
Convex:                          Nonconvex:
                                    ●  ← local minimum
  \        /                      /  \
   \      /                     /    \    /
    \    /                    /       \  /
     \  /                   /          ●  ← global minimum
      ●  ← unique global
```

### Why This Matters in COIN-OR

| Library | Problem Class | What It Guarantees |
|---------|---------------|-------------------|
| [Ipopt](@/libraries/ipopt/_index.md) | Continuous NLP | Local optimum |
| [Bonmin](@/libraries/bonmin/_index.md) | Convex MINLP | Global optimum |
| [Couenne](@/libraries/couenne/_index.md) | General MINLP | Global optimum |

---

<h2 id="kkt-conditions">2. KKT Optimality Conditions</h2>

The **Karush-Kuhn-Tucker (KKT)** conditions are the foundation of constrained optimization. They tell us when a point is (locally) optimal.

### The Problem

$$\min_x \quad f(x)$$
$$\text{s.t.} \quad g(x) = 0 \quad \text{(equality constraints)}$$
$$\quad h(x) \leq 0 \quad \text{(inequality constraints)}$$

### The Lagrangian

Introduce multipliers $\lambda$ (for equalities) and $\mu$ (for inequalities):

$$\mathcal{L}(x, \lambda, \mu) = f(x) + \lambda^T g(x) + \mu^T h(x)$$

### The KKT Conditions

At an optimal point $x^*$ with multipliers $\lambda^*, \mu^*$:

<div class="step-by-step">

<div class="step">
<h5>1. Stationarity</h5>

$$\nabla_x \mathcal{L} = \nabla f(x^*) + \sum_i \lambda_i^* \nabla g_i(x^*) + \sum_j \mu_j^* \nabla h_j(x^*) = 0$$

The gradient of the objective is a linear combination of constraint gradients.

</div>

<div class="step">
<h5>2. Primal Feasibility</h5>

$$g(x^*) = 0, \quad h(x^*) \leq 0$$

The point satisfies all constraints.

</div>

<div class="step">
<h5>3. Dual Feasibility</h5>

$$\mu^* \geq 0$$

Multipliers for inequalities are non-negative.

</div>

<div class="step">
<h5>4. Complementary Slackness</h5>

$$\mu_j^* h_j(x^*) = 0 \quad \forall j$$

Either the constraint is tight ($h_j = 0$) or its multiplier is zero ($\mu_j = 0$).

</div>

</div>

### Geometric Intuition

At the optimum:
- You can't improve the objective without violating a constraint
- The objective gradient is "blocked" by active constraint gradients
- Inactive constraints ($h_j < 0$) don't matter ($\mu_j = 0$)

<div class="key-insight">

**KKT as a System of Equations:** The KKT conditions form a nonlinear system. NLP algorithms essentially solve this system, finding $(x^*, \lambda^*, \mu^*)$.

</div>

<div class="code-connection">

In Ipopt, the KKT conditions are tracked throughout the algorithm. The **optimality error** measures how close we are to satisfying them. See {{ link(path="/browser/?library=Ipopt&path=src/Interfaces/IpIpoptNLP.hpp", text="IpIpoptNLP.hpp") }}.

</div>

---

<h2 id="newtons-method">3. Newton's Method</h2>

Newton's method is the workhorse of nonlinear optimization. It finds zeros of functions—including the KKT system.

### For Unconstrained Minimization

To minimize $f(x)$, we want $\nabla f(x) = 0$. Newton's method iterates:

$$x^{k+1} = x^k - [\nabla^2 f(x^k)]^{-1} \nabla f(x^k)$$

Or equivalently, solve the **Newton system**:

$$\nabla^2 f(x^k) \cdot d = -\nabla f(x^k)$$

Then update: $x^{k+1} = x^k + d$

### Why Newton Works

Near a minimum, $f(x)$ is approximately quadratic:

$$f(x^k + d) \approx f(x^k) + \nabla f(x^k)^T d + \frac{1}{2} d^T \nabla^2 f(x^k) d$$

Newton's step **exactly minimizes this quadratic approximation**.

### Convergence Properties

| Property | Rate |
|----------|------|
| Far from solution | Linear (with line search) |
| Near solution | Quadratic! |

**Quadratic convergence** means the number of correct digits roughly doubles each iteration. From 2 digits to 4 to 8 to 16 in just 3 steps!

### The Catch: Need the Hessian

Computing $\nabla^2 f(x)$ can be expensive:
- $n^2$ second derivatives
- Must be positive definite for descent direction
- Must solve $n \times n$ linear system

<div class="key-insight">

**Quasi-Newton Methods:** Approximate the Hessian from gradient information. BFGS and L-BFGS build up a Hessian approximation iteratively. Ipopt can use these when exact Hessians aren't available.

</div>

<div class="code-connection">

See {{ link(path="/browser/?library=Ipopt&path=src/Algorithm/IpRestorationPhase.hpp", text="IpRestorationPhase.hpp") }} for Newton-based restoration and {{ link(path="/browser/?library=Ipopt&path=src/Algorithm/LinearSolvers/IpLowRankAugSystemSolver.hpp", text="IpLowRankAugSystemSolver.hpp") }} for efficient linear system solving.

</div>

---

<h2 id="barrier-method">4. Interior Point Methods</h2>

How do we handle inequality constraints? The **barrier method** converts them into unconstrained problems using a logarithmic penalty.

### The Barrier Function

For constraints $h(x) \leq 0$, add a barrier term:

$$\min_x \quad f(x) - \mu \sum_j \log(-h_j(x))$$

The logarithm:
- Goes to $+\infty$ as $h_j \to 0^-$ (approaching boundary from inside)
- Is undefined for $h_j > 0$ (infeasible)
- Forces $x$ to stay strictly inside the feasible region

### The Barrier Parameter $\mu$

As $\mu \to 0$:
- Barrier penalty decreases
- Solution approaches the true constrained optimum
- But the problem becomes harder to solve

**Strategy:** Start with large $\mu$, solve, reduce $\mu$, solve again, repeat.

### Central Path

For each $\mu$, there's an optimal point $x(\mu)$. The collection of these points forms the **central path**:

```
Feasible region
    ┌────────────────┐
    │                │
    │   x(μ₁) ●────────●────●────● x(μ₄)
    │         ╲      │   ╱
    │          ╲     │  ╱
    │           ╲    │ ╱
    │            ●───●  ← optimum (μ→0)
    └────────────────┘
    Large μ → Small μ → Optimum
```

### Connection to KKT

The barrier optimality conditions are:

$$\nabla f(x) + \sum_j \frac{\mu}{-h_j(x)} \nabla h_j(x) = 0$$

Define slack $s_j = -h_j(x)$ and multiplier $\mu_j = \mu/s_j$. Then:

$$s_j \mu_j = \mu \quad \text{(perturbed complementarity)}$$

As $\mu \to 0$, we get true complementarity: $s_j \mu_j = 0$.

<div class="key-insight">

**Why Interior Point Works:** Instead of enforcing complementarity exactly (hard combinatorial problem—which constraints are active?), we relax it to $s_j \mu_j = \mu$ and gradually tighten.

</div>

<div class="code-connection">

Ipopt implements a primal-dual interior point method. The barrier parameter management is in {{ link(path="/browser/?library=Ipopt&path=src/Algorithm/IpAdaptiveMuUpdate.hpp", text="IpAdaptiveMuUpdate.hpp") }}.

</div>

---

<h2 id="ipopt-algorithm">5. Inside Ipopt</h2>

[Ipopt](@/libraries/ipopt/_index.md) (Interior Point OPTimizer) is COIN-OR's flagship NLP solver. Let's trace through how it works.

### The Primal-Dual System

For problem with equalities $g(x) = 0$ and inequalities $h(x) + s = 0$, $s > 0$:

$$\begin{pmatrix}
W + \Sigma & 0 & A^T & C^T \\
0 & \Sigma_s & 0 & -I \\
A & 0 & 0 & 0 \\
C & -I & 0 & 0
\end{pmatrix}
\begin{pmatrix} d_x \\ d_s \\ d_\lambda \\ d_\mu \end{pmatrix}
= -\begin{pmatrix}
\nabla f + A^T \lambda + C^T \mu \\
\mu - \mu s / s \\
g(x) \\
h(x) + s
\end{pmatrix}$$

Where:
- $W$ = Hessian of Lagrangian
- $\Sigma$ = regularization terms
- $A$ = Jacobian of equalities
- $C$ = Jacobian of inequalities

### Algorithm Outline

<div class="step-by-step">

<div class="step">
<h5>Step 1: Initialize</h5>

Start with $x_0$ (user-provided or default), $s_0 > 0$, $\lambda_0$, $\mu_0$. Set barrier parameter $\mu$.

</div>

<div class="step">
<h5>Step 2: Solve KKT System</h5>

Compute search direction $(d_x, d_s, d_\lambda, d_\mu)$ by solving the primal-dual system.

</div>

<div class="step">
<h5>Step 3: Line Search</h5>

Find step size $\alpha$ such that:
- Slacks stay positive: $s + \alpha d_s > 0$
- Sufficient decrease in merit function

</div>

<div class="step">
<h5>Step 4: Update</h5>

$(x, s, \lambda, \mu) \leftarrow (x, s, \lambda, \mu) + \alpha (d_x, d_s, d_\lambda, d_\mu)$

</div>

<div class="step">
<h5>Step 5: Check Convergence</h5>

If KKT error $< \epsilon$ for current $\mu$:
- If $\mu$ small enough: **Done!**
- Else: Reduce $\mu$ and continue

</div>

</div>

### Linear Algebra: The Bottleneck

The KKT system is the computational heart. Ipopt uses:

1. **Direct methods:** MA27, MA57, MUMPS, Pardiso
   - Factorize the symmetric indefinite system
   - Most reliable for general problems

2. **Iterative methods:** For very large problems
   - Conjugate gradient with preconditioning
   - Exploits problem structure

<div class="key-insight">

**Sparsity Matters:** Real NLP problems have sparse Hessians and Jacobians. Ipopt exploits this via sparse factorization. The symbolic structure is analyzed once; numerical factorization happens each iteration.

</div>

### Filter Line Search

Ipopt uses a **filter method** instead of a merit function:

- Track pairs (constraint violation, objective)
- Accept step if it improves one without worsening the other too much
- Avoids choosing penalty parameters

<div class="code-connection">

The main algorithm loop is in {{ link(path="/browser/?library=Ipopt&path=src/Algorithm/IpIpoptAlg.cpp", text="IpIpoptAlg.cpp") }}. Filter line search is in {{ link(path="/browser/?library=Ipopt&path=src/Algorithm/IpFilterLSAcceptor.hpp", text="IpFilterLSAcceptor.hpp") }}.

</div>

---

<h2 id="minlp-intro">6. Mixed-Integer Nonlinear Programming</h2>

What if some variables must be integer? **MINLP** combines NLP difficulty with combinatorial complexity.

### The Problem

$$\min_{x,y} \quad f(x, y)$$
$$\text{s.t.} \quad g(x, y) \leq 0$$
$$\quad x \in \mathbb{R}^n, \quad y \in \{0,1\}^m$$

### Why MINLP is Hard

| Aspect | MIP | NLP | MINLP |
|--------|-----|-----|-------|
| Integer variables | Yes | No | Yes |
| Nonlinear functions | No | Yes | Yes |
| LP relaxation | Fast | N/A | N/A |
| NLP relaxation | N/A | Available | Harder |

We lose the "nice" LP relaxation of MIP and must solve NLPs instead.

### Approaches in COIN-OR

**[Bonmin](@/libraries/bonmin/_index.md):** For **convex** MINLP
- NLP-based branch-and-bound
- Outer approximation
- Hybrid methods

**[Couenne](@/libraries/couenne/_index.md):** For **nonconvex** MINLP
- Spatial branch-and-bound
- Convex relaxations
- Global optimality guarantee

<div class="key-insight">

**Convexity is Everything:** For convex MINLP, the continuous relaxation gives a valid lower bound. For nonconvex MINLP, even the continuous relaxation might have multiple local optima!

</div>

### Example: Facility Location

**Given:** Customer locations, potential facility sites, costs
**Decide:** Which facilities to open ($y_j \in \{0,1\}$), how much to ship ($x_{ij} \geq 0$)

$$\min \sum_j f_j y_j + \sum_{i,j} c_{ij} x_{ij}^2 \quad \text{(quadratic shipping cost)}$$

Subject to: demand satisfaction, capacity limits, facility open/closed logic.

The quadratic term makes this MINLP.

<div class="code-connection">

Bonmin's algorithm selection is controlled in {{ link(path="/browser/?library=Bonmin&path=src/Algorithms/BonBonminSetup.hpp", text="BonBonminSetup.hpp") }}. The B-Hyb algorithm (hybrid) is often fastest.

</div>

---

<h2 id="spatial-bb">7. Spatial Branch-and-Bound</h2>

For **nonconvex** problems, we need to branch on continuous variables too. This is **spatial branch-and-bound**, implemented in Couenne.

### Why Branch on Continuous Variables?

Consider $w = xy$ (bilinear term). The **convex envelope** (tightest convex relaxation) over a rectangle is:

$$\text{McCormick:} \quad w \geq l_x y + x l_y - l_x l_y, \quad w \geq u_x y + x u_y - u_x u_y$$
$$\quad w \leq u_x y + x l_y - u_x l_y, \quad w \leq l_x y + x u_y - l_x u_y$$

The relaxation gap is proportional to $(u_x - l_x)(u_y - l_y)$.

**Key insight:** Subdividing the domain makes the envelope tighter!

```
Large domain [0,10]×[0,10]:     Subdivided to [0,5]×[0,5]:
   Wide envelope gap              Much tighter envelope
```

### The Spatial B&B Algorithm

<div class="step-by-step">

<div class="step">
<h5>Step 1: Reformulate</h5>

Introduce auxiliary variables for nonlinear terms:
- $w_1 = x^2$ becomes a new variable with $w_1 = x^2$
- Generate convex relaxation for $w_1 = x^2$

</div>

<div class="step">
<h5>Step 2: Solve Relaxation</h5>

Solve the convex relaxation to get lower bound.

</div>

<div class="step">
<h5>Step 3: Check Feasibility</h5>

Does the relaxation solution satisfy $w_i = f_i(x)$ for all auxiliaries?
- Yes: Found optimal (for this node)
- No: Need to branch

</div>

<div class="step">
<h5>Step 4: Branch</h5>

Choose a variable (integer or continuous) with the largest "infeasibility":
$$|w_i - f_i(x)| \quad \text{for auxiliary } w_i$$

Subdivide its domain.

</div>

<div class="step">
<h5>Step 5: Bound Tightening</h5>

Use FBBT and OBBT to tighten variable bounds. Prune if lower bound ≥ upper bound.

</div>

</div>

### Bound Tightening is Critical

**FBBT (Feasibility-Based):** Propagate bounds through expressions
- $w = x + y$, $x \in [1,3]$, $y \in [2,4]$ → $w \in [3,7]$
- Cheap, apply repeatedly

**OBBT (Optimization-Based):** Solve LP to find tightest bounds
- $x^L = \min x$ subject to relaxation
- Expensive but powerful

### Branching Point Selection

Where to split matters:

| Strategy | Split Point | Good For |
|----------|-------------|----------|
| Midpoint | $(l + u)/2$ | Balanced tree |
| LP solution | $x^*_{\text{LP}}$ | Follow the action |
| Min area | Minimize relaxation gap | Tight bounds |

<div class="key-insight">

**The convergence guarantee:** As domains are subdivided, convex envelopes converge to the true function. Eventually, the relaxation becomes tight enough to prove global optimality.

</div>

<div class="code-connection">

Couenne's spatial branching is in {{ link(path="/browser/?library=Couenne&path=src/branch/CouenneObject.hpp", text="CouenneObject.hpp") }}. Bound tightening is in {{ link(path="/browser/?library=Couenne&path=src/bound_tightening/twoImpliedBT/CouenneTwoImplied.hpp", text="CouenneTwoImplied.hpp") }}.

</div>

---

## What's Next?

You now understand the algorithmic foundations of nonlinear optimization! Next steps:

- **{{ link(path="/browser/?library=Ipopt", text="Browse Ipopt source") }}** - See the interior point implementation
- **{{ link(path="/browser/?library=Bonmin", text="Browse Bonmin source") }}** - Explore MINLP algorithms
- **{{ link(path="/browser/?library=Couenne", text="Browse Couenne source") }}** - Understand global optimization
- **[Algorithm index](@/algorithms/_index.md)** - Deep-dive into specific algorithms

<div class="key-insight">

**You've learned:**
- Why nonlinearity makes optimization fundamentally harder
- KKT conditions as the foundation of constrained optimization
- Newton's method and its quadratic convergence
- Interior point methods and the central path
- How Ipopt solves the primal-dual system
- MINLP and why convexity matters
- Spatial branch-and-bound for global optimization

This completes your journey from LP to global nonlinear optimization!

</div>

