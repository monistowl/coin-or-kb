+++
title = "Mathematical Derivations"
description = "Step-by-step proofs and derivations for optimization algorithms"
template = "section.html"
sort_by = "weight"
+++

# Mathematical Derivations

This section provides rigorous step-by-step derivations of the key mathematical results that underpin optimization algorithms. Unlike the algorithm pages (which focus on *what* the algorithms do), these derivations explain *why* they work.

## Prerequisites

- **Linear algebra**: Matrix operations, systems of equations, eigenvalues
- **Calculus**: Gradients, Hessians, Taylor series
- **Basic optimization**: Convexity, feasibility, optimality

## Derivations

<div class="derivation-grid">

<a href="@/derivations/simplex-convergence.md" class="derivation-card">
<strong>Simplex Convergence</strong>
<span>Why moving between vertices guarantees improvement (and terminates)</span>
</a>

<a href="@/derivations/kkt-conditions.md" class="derivation-card">
<strong>KKT Conditions</strong>
<span>From Lagrangian to first-order optimality conditions</span>
</a>

<a href="@/derivations/lp-duality.md" class="derivation-card">
<strong>LP Duality</strong>
<span>Strong duality theorem and complementary slackness</span>
</a>

<a href="@/derivations/interior-point-central-path.md" class="derivation-card">
<strong>Interior Point Central Path</strong>
<span>Barrier functions, Newton steps, and polynomial convergence</span>
</a>

<a href="@/derivations/branch-and-bound-correctness.md" class="derivation-card">
<strong>Branch and Bound Correctness</strong>
<span>Why relaxation bounds guarantee global optimality</span>
</a>

</div>

---

## How to Read These Derivations

Each derivation follows a consistent structure:

1. **Setup**: The problem and notation
2. **Key Lemmas**: Building blocks for the main result
3. **Main Theorem**: The core result with proof
4. **Connection to Code**: Where this appears in COIN-OR

The goal is to bridge textbook theory and production code.
