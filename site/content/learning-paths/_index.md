+++
title = "Learning Paths"
description = "Guided journeys through optimization algorithms and COIN-OR implementation"
template = "learning-paths-index.html"
sort_by = "weight"
+++

# Learning Paths

Welcome! These guided paths will take you from foundational concepts to understanding real optimization solver implementations.

## Choose Your Journey

<div class="path-grid">

<div class="path-card path-lp">
<h3>LP Fundamentals</h3>
<p class="path-tagline">From linear algebra to the simplex method</p>
<p>Master the core algorithms that power linear programming solvers. You'll learn how sparse matrices work, understand LU factorization, and trace through the simplex method step by step.</p>
<div class="path-meta">
<span class="duration">~4 hours</span>
<span class="prereqs">Linear algebra basics</span>
</div>
<a href="lp-fundamentals/" class="path-start">Start Learning →</a>
</div>

<div class="path-card path-mip">
<h3>MIP Journey</h3>
<p class="path-tagline">From LP relaxation to branch-and-cut</p>
<p>Understand how integer programming solvers work. You'll explore branch-and-bound trees, cutting planes, and the heuristics that make modern MIP solvers practical.</p>
<div class="path-meta">
<span class="duration">~6 hours</span>
<span class="prereqs">LP Fundamentals path</span>
</div>
<a href="mip-journey/" class="path-start">Start Learning →</a>
</div>

<div class="path-card path-nlp">
<h3>Nonlinear Optimization</h3>
<p class="path-tagline">Interior point methods and beyond</p>
<p>Dive into nonlinear programming with Ipopt. Learn Newton's method, barrier functions, and how automatic differentiation enables efficient gradient computation.</p>
<div class="path-meta">
<span class="duration">~5 hours</span>
<span class="prereqs">Calculus, LP Fundamentals</span>
</div>
<a href="nonlinear-optimization/" class="path-start">Start Learning →</a>
</div>

<div class="path-card path-global">
<h3>Global Optimization</h3>
<p class="path-tagline">From convex to nonconvex: spatial branch-and-bound</p>
<p>Learn how to find global optima in nonconvex problems. Master spatial branch-and-bound, convexification techniques, and MINLP solvers Bonmin and Couenne.</p>
<div class="path-meta">
<span class="duration">~5 hours</span>
<span class="prereqs">MIP Journey, NLP path</span>
</div>
<a href="global-optimization/" class="path-start">Start Learning →</a>
</div>

</div>

## How These Paths Work

Each learning path follows a consistent structure:

1. **Concepts** - Understand the mathematical foundations
2. **Algorithms** - See the step-by-step procedures with worked examples
3. **Code** - Explore the actual COIN-OR implementation
4. **Practice** - Try modifications and see what happens

You don't need to complete paths in order, but **LP Fundamentals** provides the foundation for everything else.

## Prerequisites

Before starting, you should be comfortable with:

- **Linear algebra**: Vectors, matrices, solving $Ax = b$
- **Basic calculus**: Derivatives, gradients (for NLP path)
- **Programming**: Reading C++ code (you don't need to write it)

Not sure if you're ready? Each path has a "check your knowledge" section at the start.
