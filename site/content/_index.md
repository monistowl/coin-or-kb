+++
title = "COIN-OR Knowledge Base"
description = "Machine-readable documentation for optimization solver libraries"
template = "index.html"
+++

# COIN-OR Knowledge Base

Annotated documentation for the COIN-OR ecosystem of optimization solvers.

## For AI Agents

Machine-readable JSON API available at [`/api/index.json`](/api/index.json).

## Libraries by Layer

### Layer 0 - Foundation
- **CoinUtils** - Core utilities, sparse matrices, I/O

### Layer 1 - Core Solvers
- **Clp** - Simplex LP solver
- **Osi** - Open Solver Interface

### Layer 2 - Advanced
- **Cbc** - Branch-and-cut MIP solver
- **Cgl** - Cut generation library
- **Ipopt** - Interior point NLP solver

### Layer 3 - Specialized
- **Bonmin** - MINLP solver
- **Couenne** - Global optimization
- **SYMPHONY** - Parallel MIP

### Layer 4 - High-Level
- **HiGHS** - High-performance LP/MIP
- **SHOT** - Global MINLP

## Algorithms Index

Browse implementations by algorithm type:
- [Simplex Methods](/algorithms/simplex/)
- [Interior Point](/algorithms/interior-point/)
- [Branch and Bound](/algorithms/branch-and-bound/)
- [Presolve](/algorithms/presolve/)
