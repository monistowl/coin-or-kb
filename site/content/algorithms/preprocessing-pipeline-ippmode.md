+++
title = "Preprocessing Pipeline (IPPMode)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Controls integer preprocessing before B&C:
    - Probing: fix variables by logical implication
    - Clique detection: identify mutual exclusion constraints
    - Coefficient strengthening: tighten constraint coefficients
    - SOS extraction: identify special ordered sets from structure

## Implementations

### Cbc

- **[CbcParameters.hpp](/coin-or-kb/browser/?library=Cbc)** - Central parameter collection for Cbc algorithm control
Copyright (C) 2007, Lou Hafer, IBM Corporation and others.
This code is licensed under the terms of the Eclipse Public License (EPL).

CbcParameters: Master class holding all Cbc solver parameters.
Used by cbc-generic to configure and control the MIP solver.

Major subsystems configured:
- Cut generators: Gomory, MIR, Probing, Clique, FlowCover, etc.
- Heuristics: FPump, RINS, RENS, DINS, Diving variants, VND, etc.
- Search strategy: Node selection, preprocessing, orbital branching
- Limits: Time, nodes, gap tolerance, solution count

Includes instances of CGL cut generators and Cbc heuristics.
Links to ClpParameters for underlying LP solver control.

Key methods:
- init(): Initialize with strategy preset
- setModel(): Associate with CbcModel
- Various getters/setters for each parameter category

Strategy presets provide common configurations:
- Default aggressive cutting at root
- Balanced cut/heuristic emphasis
- Heuristic-focused for quick solutions

## References

- Margot, F. (2002). "Pruning by isomorphism in branch-and-cut".
    Math. Programming 94:71-90. (Orbital branching foundations)
