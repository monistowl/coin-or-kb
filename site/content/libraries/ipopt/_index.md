+++
title = "Ipopt"
description = "Layer 2 - Interior Point Optimizer for Nonlinear Programming"
template = "library.html"
sort_by = "title"

[extra]
layer = 2
+++

# Ipopt — Interior Point Optimizer

Ipopt (Interior Point OPTimizer) is a state-of-the-art solver for large-scale nonlinear programming (NLP). It finds local optima of nonconvex problems and global optima of convex problems, using a primal-dual interior point algorithm with a filter line search.

**Layer 2** | 142 files | 1 with algorithm annotations

---

## Why Ipopt Matters

When your optimization problem has nonlinear functions (quadratic, trigonometric, exponential, etc.), linear solvers can't help. Ipopt handles:

- **Nonlinear objectives**: $\min f(x)$ where $f$ is nonlinear
- **Nonlinear constraints**: $g(x) \leq 0$, $h(x) = 0$
- **Large-scale problems**: Exploits sparsity in Hessians and Jacobians
- **General bounds**: $l \leq x \leq u$

Ipopt is used as the NLP engine inside:
- **Bonmin** for convex MINLP
- **Couenne** for global (nonconvex) MINLP
- Many engineering and scientific applications

---

## The Algorithm

Ipopt implements a **primal-dual interior point method** with **filter line search**:

### 1. Barrier Subproblems

Replace inequality constraints with barrier terms:
$$\min_x \quad f(x) - \mu \sum_i \ln(s_i) \quad \text{s.t.} \quad g(x) + s = 0, \; h(x) = 0$$

where $\mu > 0$ is the barrier parameter that decreases toward zero.

### 2. Newton Steps

At each iteration, solve the KKT system:
$$\begin{pmatrix} W & 0 & J_g^T & J_h^T \\ 0 & \Sigma & I & 0 \\ J_g & I & 0 & 0 \\ J_h & 0 & 0 & 0 \end{pmatrix} \begin{pmatrix} \Delta x \\ \Delta s \\ \Delta \lambda \\ \Delta \nu \end{pmatrix} = -\begin{pmatrix} \nabla f + J_g^T \lambda + J_h^T \nu \\ \lambda - \mu S^{-1} e \\ g + s \\ h \end{pmatrix}$$

where $W$ is the Hessian of the Lagrangian.

### 3. Filter Line Search

Accept steps that either:
- Improve the objective, or
- Reduce constraint violation

The filter mechanism prevents cycling and ensures global convergence.

### 4. Barrier Parameter Update

Reduce $\mu$ when the current subproblem is solved sufficiently well, following the central path toward the optimal solution.

---

## Key Classes

| Class | Purpose |
|-------|---------|
| [IpIpoptApplication](/browser/?library=Ipopt) | Main application interface |
| [IpIpoptAlg](/browser/?library=Ipopt) | Core algorithm implementation |
| [IpOrigIpoptNLP](/browser/?library=Ipopt) | NLP problem representation |
| [IpFilterLSAcceptor](/browser/?library=Ipopt) | Filter line search |
| [SymLinearSolver](/browser/?library=Ipopt) | Linear solver interface |
| [IpTNLPAdapter](/browser/?library=Ipopt) | Adapter for TNLP interface |

---

## Architecture

Ipopt separates the optimization algorithm from the linear algebra:

```
Application Layer
      |
  IpoptAlg         <- Main algorithm loop
      |
  NLP Interface    <- Problem definition (TNLP or AMPL)
      |
  Linear Solver    <- Solve KKT system (MA27, MA57, MUMPS, etc.)
      |
  Matrix Storage   <- Sparse matrices (SymMatrix, etc.)
```

This modularity lets you swap linear solvers without changing the algorithm.

---

## Usage Example

```cpp
#include "IpIpoptApplication.hpp"
#include "IpTNLP.hpp"

// Define your NLP by inheriting from TNLP
class MyNLP : public Ipopt::TNLP {
public:
    bool get_nlp_info(Index& n, Index& m, ...) override;
    bool get_bounds_info(...) override;
    bool get_starting_point(...) override;
    bool eval_f(Index n, const Number* x, bool new_x, Number& obj_value) override;
    bool eval_grad_f(...) override;
    bool eval_g(...) override;
    bool eval_jac_g(...) override;
    bool eval_h(...) override;  // Hessian (optional)
};

// Solve
SmartPtr<IpoptApplication> app = IpoptApplicationFactory();
app->Options()->SetStringValue("linear_solver", "ma57");
app->Initialize();

SmartPtr<TNLP> mynlp = new MyNLP();
app->OptimizeTNLP(mynlp);
```

---

## Linear Solver Options

The linear solver is the computational bottleneck. Ipopt supports:

| Solver | License | Best For |
|--------|---------|----------|
| MA27 | HSL (free academic) | Small to medium problems |
| MA57 | HSL (free academic) | Medium problems, out-of-core |
| MA86 | HSL (free academic) | Large problems, parallel |
| MUMPS | Open source | Large problems, good default |
| Pardiso | Intel MKL or Pardiso Project | Very large, parallel |

For best performance, obtain an HSL license (free for academic use) and use MA57 or MA86.

---

## Important Options

| Option | Description | Default |
|--------|-------------|---------|
| `linear_solver` | Which linear solver | `ma27` |
| `tol` | Convergence tolerance | `1e-8` |
| `max_iter` | Maximum iterations | 3000 |
| `mu_strategy` | Barrier update strategy | `adaptive` |
| `print_level` | Output verbosity | 5 |
| `hessian_approximation` | Use L-BFGS instead of exact | `exact` |

---

## When to Use Ipopt

| Scenario | Recommendation |
|----------|----------------|
| Convex NLP | Ipopt finds global optimum |
| Nonconvex NLP | Ipopt finds local optimum (run from multiple starts) |
| Large sparse problems | Ipopt with good linear solver |
| MINLP (via Bonmin/Couenne) | Ipopt handles NLP subproblems |
| Need derivatives | Provide exact or use AD |

---

## Derivative Information

Ipopt needs first and second derivatives for efficiency:

- **Gradient** $\nabla f$: Required
- **Jacobian** $J_g$, $J_h$: Required
- **Hessian** $\nabla^2_{xx} L$: Optional (can use L-BFGS approximation)

**Options for providing derivatives:**
1. Hand-code (most efficient)
2. Automatic differentiation (CppAD, ADOL-C)
3. Finite differences (slow, numerical issues)
4. L-BFGS Hessian approximation (no second derivatives needed)

---

## Related Resources

- [Nonlinear Optimization Learning Path](/learning-paths/nonlinear-optimization/) — NLP from scratch
- [Interior Point Central Path Derivation](/derivations/interior-point-central-path/) — Barrier method theory
- [KKT Conditions Derivation](/derivations/kkt-conditions/) — Optimality conditions
- [Global Optimization Learning Path](/learning-paths/global-optimization/) — Beyond local optima
