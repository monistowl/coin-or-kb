+++
title = "SolutionStrategyNLP"
description = "Direct NLP solver for continuous problems"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/SolutionStrategy/SolutionStrategyNLP.h"
+++

Direct NLP solver for continuous problems

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

## Algorithm

<div class="algorithm-card">

Direct interior point NLP solve

</div>

## See Also

- NLPSolver/NLPSolverIpoptBase.h for Ipopt wrapper

## Source

Header file: {{ link(path="/browser/?library=SHOT&file=src/SolutionStrategy/SolutionStrategyNLP.h", text="`src/SolutionStrategy/SolutionStrategyNLP.h`") }}

