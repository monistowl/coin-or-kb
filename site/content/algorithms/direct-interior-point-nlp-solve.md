+++
title = "Direct interior point NLP solve"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Interior Point Methods"
implementation_count = 1
+++

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="SolutionStrategyNLP.h") }}** - Direct NLP solver for continuous problems

Bypasses ESH for purely continuous NLP problems.

**SolutionStrategyNLP Class:**
- initializeStrategy(): Configure for direct NLP solve
- solveProblem(): Single NLP solver call (Ipopt)

**Use Case:**
- Problems with no integer variables
- Convex NLP where outer approximation is unnecessary
- Falls back to standard NLP solvers (Ipopt)

**When Selected:**
- Problem type is NLP (no discrete variables)
- Simpler than ESH for continuous problems
