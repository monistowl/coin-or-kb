+++
title = "Cmpl"
description = "Coliop Mathematical Programming Language with automatic linearization"
template = "library.html"
sort_by = "title"

[extra]
layer = 4
+++

# Cmpl

**Coliop Mathematical Programming Language** - a modeling language for linear and integer programming with automatic reformulation of nonlinear constructs. Developed at the Technical University of Applied Sciences Wildau.

**Layer 4** | 100 files | 4 with algorithm annotations

## Key Features

### Automatic Linearization

Cmpl automatically transforms common nonlinear modeling constructs into linear form:

- **Variable products** → Glover linearization, McCormick envelopes
- **Logical constraints** → Big-M indicator constraints
- **Conditional expressions** → Implication linearization
- **SOS constraints** → Binary variable formulations

### Linearization Algorithms

| Construct | Algorithm | Reference |
|-----------|-----------|-----------|
| $b \cdot x$ (binary × continuous) | Glover linearization | Glover (1975) |
| $x \cdot y$ (real × real) | McCormick envelopes | McCormick (1976) |
| Integer products | Binary decomposition | — |
| $p \Rightarrow q$ | Big-M method | Nemhauser-Wolsey (1988) |
| OR constraints | Binary selection | — |
| SOS1/SOS2 | Beale-Tomlin | Beale-Tomlin (1970) |

## Annotated Components

| Component | Description |
|-----------|-------------|
| `Extensions/Remodel/LinearVarProd.hh` | Variable product linearization |
| `Extensions/Remodel/LinearLogCon.hh` | Logical constraint linearization |
| `Extensions/Remodel/LinearSos.hh` | SOS1/SOS2 constraint handling |
| `Extensions/Remodel/LinearConditional.hh` | If-then constraint linearization |

## Linearization Examples

### Glover Linearization
For $w = b \cdot x$ where $b \in \{0,1\}$ and $x \in [L, U]$:

$$\begin{aligned}
w &\leq U \cdot b \\
w &\geq L \cdot b \\
w &\leq x - L \cdot (1-b) \\
w &\geq x - U \cdot (1-b)
\end{aligned}$$

### McCormick Envelopes
For $w = x \cdot y$ where $x \in [L_x, U_x]$, $y \in [L_y, U_y]$:

$$\begin{aligned}
w &\geq L_x y + x L_y - L_x L_y \\
w &\geq U_x y + x U_y - U_x U_y \\
w &\leq U_x y + x L_y - U_x L_y \\
w &\leq L_x y + x U_y - L_x U_y
\end{aligned}$$

### SOS2 for Piecewise-Linear
Given breakpoints $a_1 < a_2 < \ldots < a_n$ and function values $f(a_i)$:

$$z = \sum_{i=1}^{n} \lambda_i \cdot a_i, \quad f(z) = \sum_{i=1}^{n} \lambda_i \cdot f(a_i)$$

with $\sum \lambda_i = 1$, $\lambda_i \geq 0$, and $\lambda$ is SOS2 (at most two consecutive nonzeros).

## Solver Integration

Cmpl outputs standard MPS/LP format and integrates with:
- **Cbc** (COIN-OR branch-and-cut)
- **GLPK** (GNU Linear Programming Kit)
- **HiGHS**
- **CPLEX**, **Gurobi**, **SCIP**

## References

- Glover (1975). "Improved Linear Integer Programming Formulations"
- McCormick (1976). "Computability of global solutions to factorable programs"
- Beale & Tomlin (1970). "Special facilities for non-convex problems"
- Nemhauser & Wolsey (1988). "Integer and Combinatorial Optimization"
