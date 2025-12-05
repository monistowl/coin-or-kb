+++
title = "Hot-Start Optimization for Strong Branching"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

1. markHotStart(): Save current basis, factorization, solution
  2. Modify bounds (single variable typically)
  3. solveFromHotStart(): Resolve with warm start (few iterations)
  4. Repeat steps 2-3 for each branching candidate
  5. unmarkHotStart(): Release saved state
  This avoids full refactorization for each strong branching LP.

## Complexity

Most operations O(1) delegations to ClpSimplex
  initialSolve/resolve: O(m·n·iterations) for underlying simplex
  Hot-start resolve: O(k·m) where k = iterations to re-optimize (typically small)
  getBInvARow/getBInvACol: O(nnz(B^{-1})) per call

@invariant basis_ synchronized with modelPtr_->status arrays after each solve
@invariant fakeMinInSimplex_ == true implies linearObjective_ is negated copy
@invariant smallModel_ != NULL implies hot-start state is active

## Implementations

### Clp

- **[OsiClpSolverInterface.hpp](/browser/?library=Clp)** - 

## References

- Lougee-Heimer, R., et al. (2003). "The Common Optimization INterface for
  Operations Research: Promoting open-source software in the operations
  research community". IBM J. Res. Dev. 47(1):57-66.
