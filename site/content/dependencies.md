+++
title = "Third-Party Dependencies"
description = "Optional dependencies for building COIN-OR solvers with full functionality"
template = "page.html"
+++

# Third-Party Dependencies

The COIN-OR ecosystem uses several third-party libraries for specialized functionality. These are **optional** — solvers work without them, but with reduced capabilities.

---

## Dependency Architecture

```
                    ┌─────────────────────────────────────────────────────────┐
                    │                    COIN-OR Solvers                      │
                    └─────────────────────────────────────────────────────────┘
                                              │
          ┌───────────────┬─────────────┬─────┴─────┬─────────────┐
          ▼               ▼             ▼           ▼             ▼
       Bonmin          Couenne       Ipopt      SYMPHONY        Cbc
          │               │             │           │             │
          └───────┬───────┴─────────────┤           │             │
                  │                     │           │             │
                  ▼                     ▼           ▼             ▼
              ThirdParty-ASL     ┌──────────┐   ThirdParty-    Osi
              (AMPL interface)   │  Linear  │     Glpk       (solver
                                 │  Solvers │                interface)
                                 └────┬─────┘
                    ┌─────────────────┼─────────────────┐
                    ▼                 ▼                 ▼
             ThirdParty-HSL    ThirdParty-Mumps   SuiteSparse
             (MA27/57/77/86/97)    (MUMPS)       (included)
                    │                 │
                    └────────┬────────┘
                             ▼
                    ┌────────────────┐
                    │  ThirdParty-   │
                    │    Metis       │
                    └────────┬───────┘
                             │
               ┌─────────────┴─────────────┐
               ▼                           ▼
        ThirdParty-Blas            ThirdParty-Lapack
```

---

## Build Infrastructure

| Package | Purpose |
|---------|---------|
| **coinbrew** | COIN-OR fetch/build/install helper script — the standard way to build COIN-OR from source |
| **COIN-OR-OptimizationSuite** | Meta-project that builds all COIN-OR solvers together |
| **Data-Sample** | Test problem instances (MPS, LP files) for solver validation |

---

## Linear Algebra Dependencies

| Package | Purpose | Used By |
|---------|---------|---------|
| **ThirdParty-Blas** | Basic Linear Algebra Subprograms | Most solvers (matrix operations) |
| **ThirdParty-Lapack** | Linear Algebra Package | Ipopt, HSL, MUMPS (dense linear algebra) |
| **ThirdParty-Metis** | Graph partitioning (METIS 4/5) | HSL, MUMPS, Ipopt (sparse matrix ordering) |

---

## Sparse Direct Solvers (for Ipopt)

These provide the symmetric indefinite factorization required by Ipopt's interior point method.

| Package | Purpose | License |
|---------|---------|---------|
| **ThirdParty-HSL** | Harwell Subroutine Library wrapper | Academic/Commercial |
| **ThirdParty-Mumps** | MUMPS sparse direct solver wrapper | Public domain |

### HSL Solvers

HSL provides the highest-performance linear solvers for Ipopt:

| Solver | Type | Best For |
|--------|------|----------|
| MA27 | Multifrontal | Small-medium problems (free in archive) |
| MA57 | Multifrontal | Medium problems |
| MA77 | Out-of-core | Very large problems |
| MA86 | Multi-threaded | Parallel solve |
| MA97 | Multi-threaded | Modern replacement for MA57 |

**Getting HSL:**
- Academic: [STFC Licences](https://licences.stfc.ac.uk/product/coin-hsl)
- Archive (free, MA27/28/MC19 only): [HSL Archive](https://licences.stfc.ac.uk/product/coin-hsl-archive)

### MUMPS

MUMPS (MUltifrontal Massively Parallel Sparse direct Solver) is a freely available alternative:

- CeCILL-C license (LGPL-compatible)
- MPI parallel support
- Good performance on medium-large problems
- Included in most Linux package managers

---

## LP/MIP Solver Interfaces

| Package | Purpose | License |
|---------|---------|---------|
| **ThirdParty-Glpk** | GNU Linear Programming Kit wrapper | GPL |
| **ThirdParty-SoPlex** | ZIB SoPlex LP solver wrapper | ZIB Academic |
| **ThirdParty-SCIP** | ZIB SCIP MIP solver wrapper | ZIB Academic |

These allow COIN-OR solvers to use external LP/MIP engines as subsolvers.

---

## NLP Components

| Package | Purpose | Used By |
|---------|---------|---------|
| **ThirdParty-ASL** | AMPL Solver Library (expression parsing) | Ipopt, Bonmin, Couenne (AMPL interface) |
| **ThirdParty-FilterSQP** | FilterSQP NLP solver wrapper | Bonmin (alternative to Ipopt) |

---

## Installation

Most ThirdParty-* packages are **build wrappers** that download source code on demand:

```bash
# Example: Building MUMPS for Ipopt
cd ThirdParty-Mumps
./get.Mumps          # Downloads MUMPS source
./configure
make && make install
```

### Using coinbrew (Recommended)

The easiest way to build COIN-OR with dependencies:

```bash
# Fetch and build Ipopt with MUMPS
./coinbrew fetch Ipopt --no-prompt
./coinbrew build Ipopt --prefix=/usr/local --no-prompt

# Or build everything
./coinbrew fetch COIN-OR-OptimizationSuite --no-prompt
./coinbrew build COIN-OR-OptimizationSuite --prefix=/usr/local --no-prompt
```

coinbrew automatically handles dependency resolution and downloads third-party packages as needed.

---

## Performance Impact

| Solver | Without Dependencies | With HSL | With MUMPS |
|--------|---------------------|----------|------------|
| **Ipopt** | Uses internal MA27 (slow) | 5-10x faster (MA57/97) | 2-5x faster |
| **Bonmin** | Basic NLP | Faster NLP subproblems | Faster NLP subproblems |
| **Couenne** | Basic NLP | Faster node processing | Faster node processing |

For production use with Ipopt, **HSL MA57 or MA97** is strongly recommended.

---

## See Also

- [COIN-OR Installation Guide](https://coin-or.github.io/user_introduction.html)
- [Ipopt Documentation](https://coin-or.github.io/Ipopt/)
- [HSL for Ipopt](https://github.com/coin-or-tools/ThirdParty-HSL)
