/**
 * @file DcoBranchStrategyRel.hpp
 * @brief DisCO reliability branching
 *
 * @algorithm Reliability Branching
 * @math Hybrid strategy combining strong and pseudocost branching:
 *       - If observations(j) < η_rel (reliability threshold): strong branch
 *       - If observations(j) ≥ η_rel: use pseudocost estimate
 *       Default η_rel = 4-8 observations before trusting pseudocosts.
 *
 * Reliability branching combines strong branching initialization
 * with pseudocost-based selection after reliability threshold.
 *
 * **Rationale:** Strong branching is accurate but expensive. Pseudocosts
 * are cheap but need calibration. Reliability branching uses strong
 * branching to initialize pseudocosts, then switches to cheap estimation.
 *
 * **Algorithm:**
 * 1. For unreliable variables (few observations), do strong branching
 * 2. Update pseudocost estimates from strong branching results
 * 3. Once reliable (η_rel observations), use pseudocost scoring
 *
 * @complexity O(N·LP) early in tree, O(n) per node after warmup
 * @ref Achterberg, T. et al. (2005). "Branching rules revisited".
 *      Operations Research Letters 33(1):42-54.
 *
 * @see DcoBranchStrategyStrong.hpp for pure strong branching
 * @see DcoBranchStrategyPseudo.hpp for pure pseudocost branching
 */
/*===========================================================================*
 * This file is part of the Discrete Conic Optimization (DisCO) Solver.      *
 *                                                                           *
 * DisCO is distributed under the Eclipse Public License as part of the      *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *          Aykut Bulut, Lehigh University                                   *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Copyright (C) 2001-2018, Lehigh University, Aykut Bulut, Yan Xu, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/
