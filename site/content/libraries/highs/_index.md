+++
title = "HiGHS"
description = "High-performance LP/MIP solver with PDLP first-order methods"
template = "library.html"
sort_by = "title"

[extra]
layer = 4
+++

# HiGHS

High-performance open-source solver for linear programming (LP), mixed-integer programming (MIP), and quadratic programming (QP). Originally developed at the University of Edinburgh.

**Layer 4** | 240 files | 47 with algorithm annotations

## Key Algorithms

### Simplex Method
- **Dual simplex** with steepest-edge pricing (Forrest-Goldfarb weights)
- **Primal simplex** with Devex pricing
- **LU factorization** with Markowitz pivoting and Forrest-Tomlin updates
- **Presolve** techniques: doubleton elimination, forcing constraints, implied bounds

### MIP Solver
- **Branch-and-bound** with depth-first search and plunging heuristics
- **Reliability branching** with pseudocost estimation
- **Cut generation**: GMI cuts, MIR cuts, clique cuts
- **Primal heuristics**: RINS, feasibility pump, rounding

### PDLP First-Order LP Solver
- **PDHG** (Primal-Dual Hybrid Gradient) algorithm (Chambolle-Pock 2011)
- **Adaptive restart** strategies (O'Donoghue-Candes 2015)
- **Ruiz equilibration** for matrix scaling
- **Malitsky-Pock** adaptive step sizes
- GPU acceleration via CUDA (cuPDLP)

### Interior Point Method
- Integration with **IPX** interior point solver
- **HiPO** (HiGHS Interior Point Optimizer) with supernodal Cholesky

### Analysis Tools
- **IIS** (Irreducible Infeasible Set) computation
- **Sensitivity analysis** (ranging) for objective coefficients and RHS

## Annotated Components

| Component | Description |
|-----------|-------------|
| `simplex/` | Dual/primal simplex, pricing, ratio tests |
| `mip/` | Branch-and-bound, cuts, pseudocosts, heuristics |
| `pdlp/cupdlp/` | PDHG algorithm, scaling, restart strategies |
| `presolve/` | Problem reduction, symmetry detection |
| `ipm/` | Interior point, factorization |
| `util/` | Data structures (Union-Find, Red-Black trees, HAMT) |
| `parallel/` | Work-stealing task executor |

## References

- Huangfu & Hall (2018). "Parallelizing the dual revised simplex method"
- Chambolle & Pock (2011). "A first-order primal-dual algorithm"
- Applegate et al. (2021). "Practical Large-Scale LP using PDHG"

