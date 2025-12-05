+++
title = "LP Fundamentals"
description = "From linear algebra to understanding the simplex method"
template = "learning-path.html"
weight = 1

[extra]
tagline = "Master the core algorithms that power linear programming solvers"
duration = "~4 hours"
prereqs = "Linear algebra basics"
steps = [
    { id = "what-is-lp", title = "What is Linear Programming?", duration = "15 min" },
    { id = "sparse-matrices", title = "Sparse Matrix Storage", duration = "30 min" },
    { id = "lu-factorization", title = "LU Factorization", duration = "45 min" },
    { id = "simplex-overview", title = "The Simplex Method", duration = "45 min" },
    { id = "worked-example", title = "Worked Example", duration = "30 min" },
    { id = "dual-simplex", title = "Dual Simplex", duration = "30 min" },
    { id = "presolve", title = "Presolve: Making Problems Easier", duration = "30 min" },
]
+++

<div class="key-insight">

This path will take you from understanding what LP solvers do to being able to trace through the actual COIN-OR source code. By the end, terms like "reduced cost", "basis matrix", and "Forrest-Tomlin update" will make sense.

</div>

## Check Your Knowledge

Before starting, make sure you're comfortable with:

- Matrix multiplication: $Ax = b$
- Solving linear systems (at least conceptually)
- What "optimization" means (finding best values)

If you need a refresher, Khan Academy's [linear algebra course](https://www.khanacademy.org/math/linear-algebra) is excellent.

---

<h2 id="what-is-lp">1. What is Linear Programming?</h2>

Linear Programming (LP) finds the best value of a linear objective subject to linear constraints.

### The Standard Form

Every LP can be written as:

$$\min_{x} \quad c^T x \quad \text{subject to} \quad Ax = b, \quad x \geq 0$$

Where:
- $x$ is the vector of decision variables
- $c$ is the cost/objective vector
- $A$ is the constraint matrix
- $b$ is the right-hand side

### A Concrete Example

**Problem:** A factory makes chairs and tables. Each chair needs 2 hours carpentry, 1 hour finishing, and profits \$20. Each table needs 1 hour carpentry, 2 hours finishing, and profits \$30. With 40 hours carpentry and 50 hours finishing available, how many of each should they make?

**Formulation:**
$$\max \quad 20x_1 + 30x_2$$
$$\text{s.t.} \quad 2x_1 + x_2 \leq 40 \quad \text{(carpentry)}$$
$$\quad x_1 + 2x_2 \leq 50 \quad \text{(finishing)}$$
$$\quad x_1, x_2 \geq 0$$

<div class="key-insight">

**Why "Linear"?** Both the objective and constraints are linear functions - no $x^2$, no $xy$, no $\sin(x)$. This special structure enables fast algorithms.

</div>

### Why LP Matters

LP solvers handle problems with millions of variables. They're used for:
- Supply chain optimization
- Financial portfolio allocation
- Airline crew scheduling
- Power grid management
- As subproblems in integer programming

<div class="code-connection">

In COIN-OR, LP problems are represented by the `ClpSimplex` class in [Clp](/libraries/clp/). The constraint matrix $A$ is stored as a `CoinPackedMatrix` in [CoinUtils](/libraries/coinutils/).

</div>

---

<h2 id="sparse-matrices">2. Sparse Matrix Storage</h2>

Real LP problems have matrices with millions of entries, but most are zero. **Sparsity** is the key to efficiency.

### Dense vs Sparse

A dense 1000×1000 matrix stores 1,000,000 numbers. But in LP, typically only 0.1-1% are nonzero - storing all those zeros wastes memory and computation.

### Compressed Sparse Column (CSC) Format

COIN-OR uses CSC format. For a matrix:

$$A = \begin{pmatrix} 1 & 0 & 2 \\ 3 & 0 & 0 \\ 0 & 4 & 5 \end{pmatrix}$$

We store:
- **values**: `[1, 3, 4, 2, 5]` (nonzeros by column)
- **row indices**: `[0, 1, 2, 0, 2]` (which row each value is in)
- **column starts**: `[0, 2, 3, 5]` (where each column begins in values array)

Column 0 has values at positions 0-1, column 1 at position 2, column 2 at positions 3-4.

<div class="try-it">

**Exercise:** Write out the CSC representation for:
$$B = \begin{pmatrix} 5 & 0 \\ 0 & 6 \\ 7 & 8 \end{pmatrix}$$

Answer: values=`[5,7,6,8]`, rows=`[0,2,1,2]`, starts=`[0,2,4]`

</div>

### Why This Matters

Sparse operations only touch nonzeros:
- Dense matrix-vector multiply: $O(mn)$ operations
- Sparse matrix-vector multiply: $O(\text{nnz})$ operations

For a 10,000×10,000 matrix with 50,000 nonzeros, that's 50,000 vs 100,000,000 operations!

<div class="code-connection">

See `CoinPackedMatrix` in [CoinUtils](/browser/?library=CoinUtils). The `getVectorStarts()`, `getIndices()`, and `getElements()` methods give you the CSC arrays.

</div>

---

<h2 id="lu-factorization">3. LU Factorization</h2>

The simplex method needs to solve systems like $Bx = b$ at every iteration, where $B$ is the **basis matrix**. LU factorization makes this fast.

### What is LU Factorization?

Factor a matrix into lower and upper triangular parts:
$$B = LU$$

Then solve $Bx = b$ in two easy steps:
1. Solve $Ly = b$ (forward substitution)
2. Solve $Ux = y$ (backward substitution)

Triangular systems are fast because you can solve one variable at a time.

### Markowitz Pivot Selection

When factoring sparse matrices, pivot choice matters enormously. A bad pivot creates **fill-in** (zeros become nonzeros).

The **Markowitz criterion** picks the pivot that minimizes expected fill-in:

$$\text{cost}(i,j) = (r_i - 1)(c_j - 1)$$

Where $r_i$ is the number of nonzeros in row $i$, and $c_j$ is the number in column $j$.

<div class="key-insight">

**Why Markowitz works:** If row $i$ has few nonzeros, eliminating it affects few other rows. If column $j$ has few nonzeros, the pivot column spreads to few rows. The product estimates total new nonzeros created.

</div>

### Updating vs Refactoring

After a simplex pivot, $B$ changes by one column. Instead of refactoring from scratch ($O(m^3)$ worst case), we **update** the factorization ($O(m^2)$ typical).

COIN-OR uses **Forrest-Tomlin updates**: maintain $L$ and modify $U$ by eliminating a "spike" in the structure.

<div class="code-connection">

The `CoinFactorization` class in [CoinUtils](/libraries/coinutils/CoinFactorization/) implements LU with Markowitz pivoting. Key methods:
- `factorize()` - Initial factorization
- `updateColumnFT()` - FTRAN (solve $Bx=b$)
- `updateColumnTranspose()` - BTRAN (solve $B^Ty=c$)
- `replaceColumn()` - Forrest-Tomlin update

</div>

---

<h2 id="simplex-overview">4. The Simplex Method</h2>

The simplex method walks along edges of the feasible polytope, improving the objective at each step, until reaching an optimal vertex.

### Basic and Non-Basic Variables

At any vertex, some variables are **basic** (can be nonzero) and others are **non-basic** (fixed at bounds).

If we have $m$ constraints and $n$ variables, exactly $m$ variables are basic. The **basis matrix** $B$ is the $m \times m$ submatrix of $A$ for basic columns.

### The Simplex Tableau (Conceptually)

Partition variables into basic ($x_B$) and non-basic ($x_N$):

$$Ax = Bx_B + Nx_N = b$$
$$x_B = B^{-1}b - B^{-1}Nx_N$$

The **reduced costs** tell us if we can improve:
$$\bar{c}_N = c_N - N^T(B^{-T}c_B)$$

If all $\bar{c}_j \geq 0$ for minimization, we're optimal.

### The Primal Simplex Algorithm

<div class="diagram-container">
<img src="../diagrams/simplex-flowchart.svg" alt="Simplex algorithm flowchart" class="algorithm-diagram">
</div>

<div class="step-by-step">

<div class="step">
<h5>Step 1: Pricing</h5>

Find a non-basic variable $x_j$ with $\bar{c}_j < 0$ (can improve objective). If none exists, we're **optimal**.

</div>

<div class="step">
<h5>Step 2: FTRAN</h5>

Compute the pivot column: $d = B^{-1}a_j$ where $a_j$ is column $j$ of $A$.

</div>

<div class="step">
<h5>Step 3: Ratio Test</h5>

Find which basic variable $x_{B[i]}$ hits its bound first:
$$\theta = \min_{d_i > 0} \frac{x_{B[i]}}{d_i}$$

The winner leaves the basis.

</div>

<div class="step">
<h5>Step 4: Pivot</h5>

Update the basis: swap entering variable $j$ with leaving variable $B[i]$. Update factorization.

</div>

<div class="step">
<h5>Step 5: Update Solution</h5>

$x_B \leftarrow x_B - \theta \cdot d$ and $x_j \leftarrow \theta$.

</div>

</div>

<div class="key-insight">

**Why this works:** Each pivot moves to an adjacent vertex with better (or equal) objective. Since there are finitely many vertices, we eventually reach optimum (with anti-cycling rules).

</div>

<div class="code-connection">

The primal simplex is implemented in `ClpSimplexPrimal` in [Clp](/libraries/clp/). The main iteration loop is in `whileIterating()`.

</div>

---

<h2 id="worked-example">5. Worked Example</h2>

Let's trace through a complete simplex solve on a small problem.

### The Problem

$$\min \quad -2x_1 - 3x_2$$
$$\text{s.t.} \quad x_1 + x_2 + s_1 = 4$$
$$\quad x_1 + 2x_2 + s_2 = 6$$
$$\quad x_1, x_2, s_1, s_2 \geq 0$$

Initial basis: $\{s_1, s_2\}$ (slack variables), so $B = I$.

**Initial solution:** $x_B = (s_1, s_2) = (4, 6)$, $x_N = (x_1, x_2) = (0, 0)$. Objective = 0.

### Iteration 1

**Pricing:** Reduced costs for non-basic variables:
- $\bar{c}_1 = -2 - (0,0) \cdot (1,1)^T = -2$
- $\bar{c}_2 = -3 - (0,0) \cdot (1,2)^T = -3$

Both negative. Choose $x_2$ (most negative) to enter.

**FTRAN:** $d = B^{-1}a_2 = I \cdot (1, 2)^T = (1, 2)^T$

**Ratio test:**
- $s_1$: $4/1 = 4$
- $s_2$: $6/2 = 3$ ← winner

$s_2$ leaves, $x_2$ enters. $\theta = 3$.

**Update:** $x_2 = 3$, $s_1 = 4 - 1 \cdot 3 = 1$, $s_2 = 0$. Objective = $-9$.

### Iteration 2

New basis: $\{s_1, x_2\}$.

$$B = \begin{pmatrix} 1 & 1 \\ 0 & 2 \end{pmatrix}, \quad B^{-1} = \begin{pmatrix} 1 & -0.5 \\ 0 & 0.5 \end{pmatrix}$$

**Pricing:** $\bar{c}_1 = -2 - (-3) \cdot (0.5) = -0.5$ (negative), $\bar{c}_{s_2} = 0 - (-3) \cdot 0.5 = 1.5$ (positive)

Enter $x_1$.

**FTRAN:** $d = B^{-1}(1, 1)^T = (0.5, 0.5)^T$

**Ratio test:**
- $s_1$: $1/0.5 = 2$ ← winner
- $x_2$: $3/0.5 = 6$

$s_1$ leaves. $\theta = 2$.

**Update:** $x_1 = 2$, $x_2 = 3 - 0.5 \cdot 2 = 2$. Objective = $-2(2) - 3(2) = -10$.

### Iteration 3

New basis: $\{x_1, x_2\}$.

**Pricing:** All reduced costs ≥ 0. **Optimal!**

**Solution:** $x_1 = 2$, $x_2 = 2$, objective = $-10$.

<div class="try-it">

**Exercise:** Verify the final solution satisfies the constraints:
- $x_1 + x_2 = 2 + 2 = 4$ ✓
- $x_1 + 2x_2 = 2 + 4 = 6$ ✓

</div>

---

<h2 id="dual-simplex">6. Dual Simplex</h2>

The dual simplex maintains **dual feasibility** (reduced costs have correct signs) while working toward **primal feasibility** (variable bounds satisfied).

### When to Use Dual Simplex

Dual simplex is preferred when:
- Starting from a dual-feasible solution (common after adding cuts)
- The problem has many more rows than columns
- Re-optimizing after bound changes

Most modern solvers use dual simplex as the default.

### The Algorithm

<div class="step-by-step">

<div class="step">
<h5>Step 1: Choose Leaving Variable</h5>

Find a basic variable violating its bounds (primal infeasible). If none, we're **optimal**.

</div>

<div class="step">
<h5>Step 2: BTRAN</h5>

Compute the pivot row: $\rho^T = e_i^T B^{-1}$ where $i$ is the leaving row.

</div>

<div class="step">
<h5>Step 3: Ratio Test (Dual)</h5>

Find entering variable that maintains dual feasibility:
$$\text{min ratio of } |\bar{c}_j / \rho_j|$$

</div>

<div class="step">
<h5>Step 4: Pivot</h5>

Swap variables and update factorization.

</div>

</div>

<div class="key-insight">

**Dual simplex intuition:** We start with a "good" objective bound but infeasible solution. Each iteration fixes one infeasibility while maintaining the objective bound's validity. When all infeasibilities are fixed, we've proven optimality.

</div>

<div class="code-connection">

See `ClpSimplexDual` in [Clp](/browser/?library=Clp). The [dual simplex algorithm page](/algorithms/dual-simplex-method/) has the full algorithm documentation.

</div>

---

<h2 id="presolve">7. Presolve: Making Problems Easier</h2>

Before solving, **presolve** transforms the problem into an equivalent but smaller/easier form.

### Common Presolve Reductions

| Reduction | What it does |
|-----------|--------------|
| Fixed variable removal | If $l_j = u_j$, substitute $x_j = l_j$ |
| Singleton row | Row with one variable → bound tightening |
| Singleton column | Column in one constraint → substitute out |
| Forcing constraint | All variables at bounds → fix them |
| Dominated column | Variable never useful → fix at bound |
| Doubleton equality | Two variables in equation → substitute |

### Example: Singleton Row

If constraint is $3x_1 = 6$, then $x_1 = 2$ is forced. Remove $x_1$ from the problem.

### Why Presolve Matters

- Reduces problem size (fewer pivots needed)
- Detects infeasibility/unboundedness early
- Tightens bounds (helps branch-and-bound later)
- Improves numerical stability

A good presolve can reduce solve time by 10-100x on real problems!

<div class="code-connection">

CoinUtils provides `CoinPresolveAction` and its subclasses for each reduction type. Clp's `ClpPresolve` orchestrates multiple passes. See [presolve algorithms](/algorithms/lp-presolve-preprocessing/).

</div>

---

## What's Next?

You now understand the core LP algorithms! Next steps:

- **[MIP Journey](/learning-paths/mip-journey/)** - Add integer variables and learn branch-and-bound
- **[Browse the source](/browser/)** - Explore the actual implementations
- **[Algorithm index](/algorithms/)** - Deep-dive into specific algorithms

<div class="key-insight">

**You've learned:**
- LP standard form and why linearity matters
- How sparse matrices make large problems tractable
- LU factorization and Markowitz pivot selection
- Both primal and dual simplex algorithms
- How presolve transforms problems

This foundation applies across all COIN-OR solvers!

</div>
