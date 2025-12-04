/**
 * @file Mongoose_Random.hpp
 * @brief Random number generation for Mongoose algorithms
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Simple random number interface: random() returns Int, setRandomSeed()
 * initializes generator. Used by random matching, random initial cuts,
 * and tie-breaking in algorithms. Seed set via EdgeCut_Options::random_seed.
 *
 * @algorithm Reproducible Randomization:
 * Provides deterministic pseudo-random sequence for algorithm reproducibility:
 *
 * Usage in Mongoose:
 * - Random matching: select random neighbor when ties occur
 * - Random initial cut: assign vertices randomly at coarsest level
 * - Tie-breaking: deterministic choice when gains are equal
 *
 * Reproducibility: Same seed → same random sequence → identical partitions.
 * Set via EdgeCut_Options::random_seed to enable reproducible experiments.
 *
 * @complexity O(1) per random number generation.
 *
 * @see Mongoose_EdgeCutOptions.hpp for random_seed option
 * @see Mongoose_Matching.hpp for random matching strategy
 */

/* ========================================================================== */
/* === Include/Mongoose_Random.hpp ========================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_RANDOM_HPP
#define MONGOOSE_RANDOM_HPP

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

Int random();
void setRandomSeed(Int seed);

} // end namespace Mongoose

#endif
