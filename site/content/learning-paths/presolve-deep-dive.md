+++
title = "Presolve Deep Dive"
description = "The hidden algorithms that make optimization fast"
template = "learning-path.html"
weight = 5

[extra]
tagline = "Understand the transformations that shrink problems before solving"
duration = "~3 hours"
prereqs = "LP Fundamentals basics"
steps = [
    { id = "why-presolve", title = "Why Presolve Matters", duration = "15 min" },
    { id = "architecture", title = "The Presolve/Postsolve Architecture", duration = "20 min" },
    { id = "simple-reductions", title = "Simple Reductions", duration = "30 min" },
    { id = "substitution", title = "Variable Substitution", duration = "35 min" },
    { id = "bound-propagation", title = "Bound Propagation", duration = "30 min" },
    { id = "advanced", title = "Advanced Techniques", duration = "25 min" },
    { id = "practice", title = "Presolve in Practice", duration = "25 min" },
]
+++

<div class="key-insight">

Presolve is the unsung hero of optimization solvers. Before a single simplex pivot or interior point iteration runs, presolve can shrink your problem by 50-90% — making the "hard work" much easier. This path reveals the elegant mathematics and engineering behind these transformations.

</div>

## Why This Path?

Most optimization courses jump straight to simplex or interior point. But in production solvers, presolve often dominates the performance impact. Understanding presolve helps you:

- **Debug modeling issues** — Presolve detects infeasibility and unboundedness before solving
- **Improve formulations** — Knowing what presolve does helps you write better models
- **Understand solver output** — Logs often show dramatic reduction statistics
- **Appreciate the engineering** — Presolve is a beautiful example of algorithmic "pre-processing"

---

<h2 id="why-presolve">1. Why Presolve Matters</h2>

Consider a real-world LP: 100,000 variables, 50,000 constraints. That's a lot of work for the simplex method! But what if:

- 30% of variables are fixed by their bounds?
- 20% of constraints are redundant?
- Many constraints can be combined or eliminated?

**Presolve** applies these transformations automatically.

### The Impact

| Metric | Before Presolve | After Presolve | Reduction |
|--------|-----------------|----------------|-----------|
| Variables | 100,000 | 25,000 | 75% |
| Constraints | 50,000 | 12,000 | 76% |
| Nonzeros | 500,000 | 80,000 | 84% |
| **Solve time** | **60 seconds** | **3 seconds** | **95%** |

The last row is the magic: simplex complexity often grows super-linearly with problem size. A 75% reduction in size can mean 95% reduction in solve time.

### What Presolve Does

Presolve transforms a problem into an equivalent but simpler one:

1. **Remove redundant elements** — empty rows/columns, fixed variables
2. **Substitute variables** — eliminate variables using equality constraints
3. **Tighten bounds** — propagate implications through constraints
4. **Detect structure** — find infeasibility, unboundedness, or trivial optima

All transformations must be **reversible**: after solving the reduced problem, we need to recover the solution to the original problem.

<div class="code-connection">

In COIN-OR, presolve is implemented in [CoinUtils](@/libraries/coinutils/_index.md) with the `CoinPresolve*` classes. Clp wraps this in [ClpPresolve](@/libraries/clp/ClpPresolve.md). The framework applies a sequence of `CoinPresolveAction` transforms.

</div>

---

<h2 id="architecture">2. The Presolve/Postsolve Architecture</h2>

The elegant insight: every presolve transformation is paired with a **postsolve** operation that undoes it.

### The Workflow

```
Original Problem
      ↓
   Presolve  ─────┐
      ↓          │ (save transformation info)
Reduced Problem   │
      ↓          │
    Solve        │
      ↓          │
Reduced Solution  │
      ↓          │
   Postsolve  ←──┘ (apply reverse transformations)
      ↓
Original Solution
```

### The Action List

Each transformation creates an **action object** containing:
- What was done (which variables/constraints affected)
- Parameters needed to reverse it (coefficients, bounds, etc.)

Actions are stored as a linked list. During postsolve, we walk the list **in reverse order**.

<div class="key-insight">

**Stack discipline**: Transformations are applied in order and reversed in opposite order. If transformation A creates structure that transformation B exploits, we must undo B before undoing A.

</div>

### Example: Fixed Variable

**Presolve**: Variable $x_3$ has bounds $[5, 5]$ (it's fixed).
- Record: "x_3 was fixed at 5"
- Remove $x_3$ from the problem
- Adjust RHS: $b_i \leftarrow b_i - a_{i3} \cdot 5$ for each constraint

**Postsolve**: Given solution to reduced problem:
- Set $x_3 = 5$ in the original solution
- Dual values unchanged (we recorded coefficients)

<div class="code-connection">

The base class is [CoinPresolveAction](@/libraries/coinutils/CoinPresolveAction.md). Each reduction inherits from it:
- `make_fixed_action` — fixed variables
- `doubleton_action` — two-variable equations
- `forcing_constraint_action` — forcing constraints
- etc.

The `postsolve()` method reverses the transformation.

</div>

---

<h2 id="simple-reductions">3. Simple Reductions</h2>

Let's start with the easiest transformations — ones that simply remove unnecessary elements.

### Empty Rows and Columns

**Empty row**: A constraint $0 \leq b$ with all zero coefficients.
- If $b \geq 0$: constraint always satisfied → remove it
- If $b < 0$: problem is infeasible

**Empty column**: A variable $x_j$ that appears in no constraints.
- If $c_j \geq 0$ (minimization): set $x_j$ to lower bound
- If $c_j < 0$: set $x_j$ to upper bound (or unbounded!)

```
Before:          After:
min 3x + 2y      min 3x + 2y
    x + y ≤ 4        x + y ≤ 4
    0 ≤ 5       ←── removed (empty row)
    z ≤ 10      ←── z removed, set z=0 (empty column with c_z=0)
```

### Fixed Variables

Variable $x_j$ with $l_j = u_j = v$ is fixed.

**Action**:
1. Substitute $x_j = v$ everywhere
2. Update RHS: $b_i \leftarrow b_i - a_{ij} v$
3. Update objective: $z_0 \leftarrow z_0 + c_j v$
4. Remove column $j$

This is $O(\text{nnz in column } j)$ work and eliminates one column.

### Free Column Singleton

A variable $x_j$ that:
- Appears in exactly one constraint (singleton column)
- Has no bounds ($-\infty < x_j < \infty$)

The constraint can be satisfied by choosing $x_j$ appropriately. Remove both the variable and the constraint.

<div class="code-connection">

See `drop_empty_rows_action`, `drop_empty_cols_action`, `make_fixed_action`, and `slack_singleton_action` in CoinUtils.

</div>

---

<h2 id="substitution">4. Variable Substitution</h2>

The most powerful presolve reductions eliminate variables by **substitution** from equality constraints.

### Singleton Row (One Variable)

Equality constraint: $a_j x_j = b$

**Action**: Solve for $x_j = b / a_j$, then:
1. Fix $x_j$ at this value
2. Propagate through all constraints containing $x_j$
3. Remove the row and column

This is the simplest substitution — the variable has a unique feasible value.

### Doubleton Row (Two Variables)

Equality constraint: $a x + b y = c$ with exactly two variables.

**Action**: Solve for $y$:
$$y = \frac{c - ax}{b}$$

Then substitute $y$ everywhere:
1. In objective: $c_y y \to c_y \cdot \frac{c - ax}{b}$
2. In each constraint with $y$: replace $d_{iy} y$ with $d_{iy} \cdot \frac{c - ax}{b}$
3. Transfer bounds on $y$ to bounds on $x$

<div class="step-by-step">

<div class="step">
<h5>Example: Doubleton Elimination</h5>

**Before**:
$$\min\ 3x + 2y$$
$$x + 2y = 6 \quad \text{(doubleton)}$$
$$x + y \leq 5$$
$$x, y \geq 0$$

**Solve for y**: $y = (6-x)/2 = 3 - x/2$

**Substitute in objective**: $3x + 2(3 - x/2) = 3x + 6 - x = 2x + 6$

**Substitute in constraint**: $x + (3 - x/2) = x/2 + 3 \leq 5 \Rightarrow x \leq 4$

**Bounds on x from y ≥ 0**: $3 - x/2 \geq 0 \Rightarrow x \leq 6$

**After**:
$$\min\ 2x + 6$$
$$x \leq 4, \quad x \leq 6, \quad x \geq 0$$

Simplified to: $\min\ 2x$ with $0 \leq x \leq 4$. Optimal: $x = 0$.

**Postsolve**: $y = 3 - 0/2 = 3$. Original solution: $(x, y) = (0, 3)$.

</div>

</div>

### Tripleton and Beyond

The same logic extends to rows with more variables, but:
- More variables = more fill-in when substituting
- CoinUtils implements `tripleton_action` for three-variable rows
- Beyond that, fill-in often exceeds the benefit

<div class="key-insight">

**The fill-in trade-off**: Substitution eliminates one variable but may add nonzeros when we replace $y$ in other constraints. Presolve tracks when fill-in is excessive and skips those cases.

</div>

<div class="code-connection">

See [doubleton_action](@/libraries/coinutils/doubleton_action.md) and `tripleton_action`. The fill-in heuristics are in `CoinPresolveDoubleton.cpp`.

</div>

---

<h2 id="bound-propagation">5. Bound Propagation</h2>

Bounds on variables imply bounds on constraint activities. These implications can tighten other bounds.

### Activity Bounds

For constraint $\sum_j a_{ij} x_j \leq b_i$, compute:

**Lower bound on activity** (assuming all variables at their worst):
$$L_i = \sum_{a_{ij} > 0} a_{ij} l_j + \sum_{a_{ij} < 0} a_{ij} u_j$$

**Upper bound on activity**:
$$U_i = \sum_{a_{ij} > 0} a_{ij} u_j + \sum_{a_{ij} < 0} a_{ij} l_j$$

### Useless Constraints

If $U_i \leq b_i$ (upper bound on activity is below RHS), the constraint can never be violated.

**Action**: Remove the constraint — it's redundant.

### Forcing Constraints

If $L_i = b_i$ (lower bound equals RHS), every variable must be at its bound:
- Variables with $a_{ij} > 0$ must be at lower bound
- Variables with $a_{ij} < 0$ must be at upper bound

**Action**: Fix all variables in the constraint, then remove it.

<div class="step-by-step">

<div class="step">
<h5>Example: Forcing Constraint</h5>

Constraint: $2x + 3y \leq 8$ with $x \in [0, 2]$, $y \in [0, 1]$

Activity bounds:
- $L = 2(0) + 3(0) = 0$
- $U = 2(2) + 3(1) = 7$

Since $U = 7 \leq 8$, this constraint is **useless** — it can never be violated.

**Alternative**: $2x + 3y \leq 3$
- $L = 0$, $U = 7 > 3$ (constraint is active)
- But if RHS were 0: $2x + 3y \leq 0$ with $L = 0 = \text{RHS}$
- **Forcing**: both $x$ and $y$ must be 0.

</div>

</div>

### Implied Variable Bounds

If we know $L_i$ and $U_i$, we can bound individual variables.

From $\sum_j a_{ij} x_j \leq b_i$:
- Contribution of $x_k$: $a_{ik} x_k$
- Contribution of others: $L_i - a_{ik} l_k$ (if $a_{ik} > 0$)

For $a_{ik} > 0$:
$$a_{ik} x_k \leq b_i - (L_i - a_{ik} l_k) \Rightarrow x_k \leq \frac{b_i - L_i + a_{ik} l_k}{a_{ik}}$$

If this bound is tighter than $u_k$, update it!

<div class="key-insight">

**Cascading effects**: Tightening one bound may enable further tightening elsewhere. Presolve iterates until no more progress. This is why presolve runs multiple passes.

</div>

<div class="code-connection">

See `do_tighten_action` for bound tightening. The iteration logic is in `ClpPresolve::presolvedModel()` which calls reductions in a loop.

</div>

---

<h2 id="advanced">6. Advanced Techniques</h2>

Beyond the basics, presolve includes sophisticated techniques for special structures.

### Duplicate Rows and Columns

**Duplicate columns**: $x_i$ and $x_j$ have identical constraint coefficients.
- If same objective coefficient: merge into one variable
- If different: keep better one, bound worse one

**Duplicate rows**: Constraints with proportional coefficients.
- Keep the tighter one, remove the redundant one

<div class="code-connection">

See [dupcol_action](@/libraries/coinutils/dupcol_action.md) and `duprow_action` in CoinUtils.

</div>

### Implied Free Variables

A variable $x_j$ may have explicit bounds $[l_j, u_j]$, but constraints may imply tighter bounds that make the explicit bounds redundant.

If the implied bounds make $x_j$ effectively free within the feasible region, we can treat it as unbounded for presolve purposes — enabling more substitutions.

### Probing (MIP Presolve)

For integer variables, **probing** temporarily fixes a variable and propagates:

1. Set $x_j = 0$, propagate bounds
2. Set $x_j = 1$, propagate bounds
3. Compare results:
   - Bounds that hold in **both** cases are valid globally
   - If either case is infeasible, the variable is fixed

This is expensive but powerful for MIP.

### Coefficient Strengthening

For MIP with binary variables, constraints can sometimes be strengthened:

$$5x_1 + 3x_2 + 4x_3 \leq 7$$

The coefficient 5 on $x_1$ can be reduced to 4:
$$4x_1 + 3x_2 + 4x_3 \leq 6$$

This is valid because setting $x_1 = 1$ forces $x_2 = x_3 = 0$.

---

<h2 id="practice">7. Presolve in Practice</h2>

### Reading Solver Output

When you run Clp or Cbc, you'll see presolve statistics:

```
Presolve 2189 (-2156) rows, 4522 (-3887) columns and 12847 (-18562) elements
```

This means:
- Started with 4345 rows, reduced to 2189 (removed 2156)
- Started with 8409 columns, reduced to 4522 (removed 3887)
- Started with 31409 nonzeros, reduced to 12847 (removed 18562)

### When Presolve Finds Problems

Presolve is excellent at detecting issues:

- **Infeasibility detected in presolve**: A constraint can't be satisfied
- **Unbounded in presolve**: A free variable with favorable objective coefficient
- **Optimal in presolve**: All variables fixed, nothing to solve!

### Presolve Controls

Most solvers let you control presolve:

| Option | Effect |
|--------|--------|
| Presolve off | Skip presolve (rarely useful) |
| Presolve iterations | Limit passes (default ~5) |
| Presolve level | Control aggressiveness |

For debugging, turning off presolve can help isolate whether an issue is in the original model or introduced during transformation.

### The Postsolve Challenge

Postsolve must produce a **valid dual solution** for the original problem, not just the primal solution. This is trickier than it sounds:

- Dual values for eliminated constraints must be computed
- Reduced costs for eliminated variables must satisfy optimality
- Numerical precision matters — accumulated errors can cause issues

<div class="code-connection">

The postsolve logic in [CoinPostsolveMatrix](@/libraries/coinutils/CoinPostsolveMatrix.md) handles dual reconstruction. `ClpPresolve::postsolve()` orchestrates the reverse pass.

</div>

---

## What's Next?

You now understand the core presolve algorithms! Next steps:

- **[Interactive Presolve Example](@/learning-paths/presolve-example.md)** — Step through transformations on a concrete problem
- **[Browse CoinPresolve source](@/browser.md)** — See the actual implementation
- **[LP Fundamentals](@/learning-paths/lp-fundamentals.md)** — Understand what presolve prepares for

<div class="key-insight">

**You've learned:**
- Why presolve has huge practical impact (50-90% size reduction)
- The presolve/postsolve architecture with reversible actions
- Simple reductions: empty rows, fixed variables, singletons
- Substitution: doubleton and tripleton elimination
- Bound propagation: activity bounds, forcing constraints
- Advanced techniques: duplicates, implied free, probing

Presolve is invisible to most users, but now you know what's happening before "Optimal solution found"!

</div>

