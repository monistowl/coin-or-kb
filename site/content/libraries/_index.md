+++
title = "Libraries"
description = "COIN-OR optimization libraries organized by dependency layer"
template = "libraries.html"
+++

# COIN-OR Library Stack

The COIN-OR project is organized into **dependency layers**, where each layer builds on the ones below it. Lower layers provide foundational utilities; higher layers implement complete solvers and applications.

---

<div class="library-layers">

## Layer 0: Foundation
<p class="layer-desc">Core utilities and sparse linear algebra that all other libraries depend on.</p>

<div class="library-grid">

<div class="library-card documented">
<h3><a href="/coin-or-kb/libraries/coinutils/">CoinUtils</a></h3>
<p class="brief">Foundation utilities: sparse matrices, I/O (MPS/LP), presolve, warm starting</p>
<div class="meta">
<span class="badge documented">122 classes documented</span>
<span class="headers">65 headers</span>
</div>
<div class="topics">
<span>Sparse Matrix</span>
<span>LU Factorization</span>
<span>Presolve</span>
<span>File I/O</span>
<span>Warm Start</span>
</div>
</div>

<div class="library-card external">
<h3><a href="/coin-or-kb/browser/?library=SuiteSparse">SuiteSparse</a></h3>
<p class="brief">Sparse direct solvers (CHOLMOD, UMFPACK, AMD) for linear algebra</p>
<div class="meta">
<span class="badge external">External library</span>
</div>
<div class="topics">
<span>Cholesky</span>
<span>LU</span>
<span>Ordering</span>
</div>
</div>

</div>

---

## Layer 1: LP & Cuts
<p class="layer-desc">Linear programming solvers, solver interfaces, and cut generation basics.</p>

<div class="library-grid">

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Clp">Clp</a></h3>
<p class="brief">COIN-OR LP solver: dual/primal simplex, interior point methods</p>
<div class="meta">
<span class="badge headers">90 headers</span>
</div>
<div class="topics">
<span>Simplex</span>
<span>Interior Point</span>
<span>Presolve</span>
<span>Factorization</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Osi">Osi</a></h3>
<p class="brief">Open Solver Interface: common API for LP/MIP solvers</p>
<div class="meta">
<span class="badge headers">35 headers</span>
</div>
<div class="topics">
<span>Solver API</span>
<span>Branching</span>
<span>Cuts</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=CppAD">CppAD</a></h3>
<p class="brief">C++ algorithmic differentiation for automatic derivatives</p>
<div class="meta">
<span class="badge headers">4 headers</span>
</div>
<div class="topics">
<span>Autodiff</span>
<span>Gradients</span>
<span>Hessians</span>
</div>
</div>

<div class="library-card external">
<h3><a href="/coin-or-kb/browser/?library=qpOASES">qpOASES</a></h3>
<p class="brief">Online active set QP solver for model predictive control</p>
<div class="meta">
<span class="badge external">External library</span>
</div>
<div class="topics">
<span>QP</span>
<span>Active Set</span>
<span>MPC</span>
</div>
</div>

</div>

---

## Layer 2: MIP & NLP
<p class="layer-desc">Mixed-integer programming and nonlinear optimization solvers.</p>

<div class="library-grid">

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Cbc">Cbc</a></h3>
<p class="brief">COIN-OR branch-and-cut MIP solver with parallelization</p>
<div class="meta">
<span class="badge headers">90 headers</span>
</div>
<div class="topics">
<span>Branch & Cut</span>
<span>Heuristics</span>
<span>Parallel</span>
<span>SOS</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Cgl">Cgl</a></h3>
<p class="brief">Cut Generator Library: Gomory, MIR, lift-and-project cuts</p>
<div class="meta">
<span class="badge headers">40 headers</span>
</div>
<div class="topics">
<span>Gomory</span>
<span>MIR</span>
<span>Clique</span>
<span>Probing</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Ipopt">Ipopt</a></h3>
<p class="brief">Interior Point OPTimizer for large-scale nonlinear programming</p>
<div class="meta">
<span class="badge headers">95 headers</span>
</div>
<div class="topics">
<span>Interior Point</span>
<span>NLP</span>
<span>Large-scale</span>
<span>Filter</span>
</div>
</div>

<div class="library-card external">
<h3><a href="/coin-or-kb/browser/?library=ADOL-C">ADOL-C</a></h3>
<p class="brief">Automatic differentiation via operator overloading</p>
<div class="meta">
<span class="badge external">External library</span>
</div>
<div class="topics">
<span>Autodiff</span>
<span>Tape-based</span>
</div>
</div>

</div>

---

## Layer 3: MINLP
<p class="layer-desc">Mixed-integer nonlinear programming and advanced decomposition methods.</p>

<div class="library-grid">

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Bonmin">Bonmin</a></h3>
<p class="brief">Basic Open-source Nonlinear Mixed INteger programming</p>
<div class="meta">
<span class="badge headers">45 headers</span>
</div>
<div class="topics">
<span>MINLP</span>
<span>B&B</span>
<span>OA</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Couenne">Couenne</a></h3>
<p class="brief">Convex Over and Under ENvelopes for MINLP with spatial B&B</p>
<div class="meta">
<span class="badge headers">70 headers</span>
</div>
<div class="topics">
<span>Global</span>
<span>Spatial B&B</span>
<span>Convexification</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=SYMPHONY">SYMPHONY</a></h3>
<p class="brief">Single- or Multi-Process Optimization over Networks (parallel B&C)</p>
<div class="meta">
<span class="badge headers">4 headers</span>
</div>
<div class="topics">
<span>Parallel</span>
<span>Distributed</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Alps">CHiPPS-ALPS</a></h3>
<p class="brief">Abstract Library for Parallel Search tree algorithms</p>
<div class="meta">
<span class="badge headers">35 headers</span>
</div>
<div class="topics">
<span>Parallel</span>
<span>Search Tree</span>
<span>Framework</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Blis">CHiPPS-BLIS</a></h3>
<p class="brief">Branch-and-cut with Lp-Based Intelligent Search</p>
<div class="meta">
<span class="badge headers">27 headers</span>
</div>
<div class="topics">
<span>Branch & Cut</span>
<span>Pseudocost</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=DisCO">DisCO</a></h3>
<p class="brief">Distributed Combinatorial Optimization for parallel MIP</p>
<div class="meta">
<span class="badge headers">27 headers</span>
</div>
<div class="topics">
<span>Conic</span>
<span>SOCP</span>
<span>Parallel</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Bcp">Bcp</a></h3>
<p class="brief">Branch-Cut-Price framework for column generation</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>Column Gen</span>
<span>Pricing</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Dip">Dip</a></h3>
<p class="brief">Decomposition for Integer Programming (Dantzig-Wolfe, Lagrangean)</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>Decomposition</span>
<span>D-W</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Smi">Smi</a></h3>
<p class="brief">Stochastic Modelling Interface for stochastic programming</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>Stochastic</span>
<span>Two-stage</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=oBB">oBB</a></h3>
<p class="brief">Optimality-Based Branch-and-Bound for nonconvex MINLP</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>Nonconvex</span>
<span>Global</span>
</div>
</div>

</div>

---

## Layer 4: Applications
<p class="layer-desc">Modeling tools, solver interfaces, and application-specific systems.</p>

<div class="library-grid">

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=SHOT">SHOT</a></h3>
<p class="brief">Supporting Hyperplane Optimization Toolkit for convex MINLP</p>
<div class="meta">
<span class="badge headers">85 headers</span>
</div>
<div class="topics">
<span>ECP</span>
<span>ESH</span>
<span>Convex MINLP</span>
</div>
</div>

<div class="library-card external">
<h3><a href="/coin-or-kb/browser/?library=HiGHS">HiGHS</a></h3>
<p class="brief">High-performance LP/MIP solver (simplex, IPM, B&B)</p>
<div class="meta">
<span class="badge external">External library</span>
</div>
<div class="topics">
<span>LP</span>
<span>MIP</span>
<span>High-perf</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=GAMSlinks">GAMSlinks</a></h3>
<p class="brief">Interfaces to GAMS optimization modeling system</p>
<div class="meta">
<span class="badge headers">25 headers</span>
</div>
<div class="topics">
<span>GAMS</span>
<span>Modeling</span>
<span>Integration</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Gravity">Gravity</a></h3>
<p class="brief">High-performance optimization modeling in C++</p>
<div class="meta">
<span class="badge headers">2 headers</span>
</div>
<div class="topics">
<span>Modeling</span>
<span>QCQP</span>
<span>SDP</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Sonnet">Sonnet</a></h3>
<p class="brief">.NET optimization modeling wrapper</p>
<div class="meta">
<span class="badge headers">24 headers</span>
</div>
<div class="topics">
<span>.NET</span>
<span>C#</span>
<span>Wrapper</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=Cmpl">Cmpl</a></h3>
<p class="brief">COLIOP Mathematical Programming Language modeling system</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>Modeling</span>
<span>Language</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=OS">OS</a></h3>
<p class="brief">Optimization Services: Web services for optimization</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>Web Services</span>
<span>OSiL</span>
</div>
</div>

<div class="library-card">
<h3><a href="/coin-or-kb/browser/?library=cuopt">cuopt</a></h3>
<p class="brief">CUDA-accelerated optimization</p>
<div class="meta">
<span class="badge headers">Headers only</span>
</div>
<div class="topics">
<span>GPU</span>
<span>CUDA</span>
</div>
</div>

</div>

</div>

---

## Documentation Status

| Layer | Libraries | Documented | In Progress |
|-------|-----------|------------|-------------|
| Layer 0 | 2 | **CoinUtils** (122 classes) | - |
| Layer 1 | 4 | - | Clp, Osi |
| Layer 2 | 4 | - | Cbc, Cgl, Ipopt |
| Layer 3 | 10 | - | Bonmin, Couenne |
| Layer 4 | 12 | - | SHOT |

**Total:** 30 libraries, 1 fully documented, ~600 headers indexed

---

## Using the Source Browser

All 30 libraries are indexed in the [Source Browser](/coin-or-kb/browser/), which provides:

- **File tree navigation** across all layers
- **Header listings** with class information
- **Quick links** to documented classes
- **Search** across the entire codebase

The browser loads data from the JSON API, making it easy for both humans and AI agents to explore the codebase structure.
