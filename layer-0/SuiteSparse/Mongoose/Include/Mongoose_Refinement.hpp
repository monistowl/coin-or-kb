/**
 * @file Mongoose_Refinement.hpp
 * @brief Partition projection during uncoarsening phase
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Refinement projects partition from coarse to fine graph during
 * uncoarsening. Maps coarse partition to fine vertices via inverse
 * matchmap, then applies FM/QP improvement (waterdance) at each level
 * for high-quality final partition.
 *
 * @see Mongoose_Coarsening.hpp for forward coarsening phase
 * @see Mongoose_Waterdance.hpp for partition improvement at each level
 */

/* ========================================================================== */
/* === Include/Mongoose_Refinement.hpp ====================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_REFINEMENT_HPP
#define MONGOOSE_REFINEMENT_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

EdgeCutProblem *refine(EdgeCutProblem *, const EdgeCut_Options *);

} // end namespace Mongoose

#endif
