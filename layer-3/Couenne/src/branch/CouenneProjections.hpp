/*
 *
 * Name:    projections.hpp
 * Authors: Pietro Belotti, Carnegie Mellon University
 * Purpose: tools for projecting points on lines/planes
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneProjections.hpp
 * @brief Point-to-segment projection utilities
 *
 * Geometric utilities for projecting points onto line segments,
 * used in convexification cut generation and branching point selection.
 *
 * @algorithm Point-to-Segment Projection:
 *   Projects point p = (x₀,y₀) onto line segment S:
 *   1. Compute foot of perpendicular to line: ax + by + c = 0
 *      q = p - [(ap + c)/(a² + b²)]·(a,b)ᵀ (orthogonal projection)
 *   2. If q_x ∈ [lb, ub]: projection is q (on segment interior)
 *   3. Else: projection is nearest endpoint (lb,y(lb)) or (ub,y(ub))
 *   4. Return Euclidean distance ||p - projection||
 *
 * @math Projection formula:
 *   Line L: ax + by + c = 0, point p = (x₀,y₀)
 *   Distance to line: d = |ax₀ + by₀ + c|/√(a² + b²)
 *   Projection: (xp,yp) = (x₀,y₀) - d·(a,b)/||(a,b)||
 *   Segment clipping: xp = max(lb, min(ub, xp))
 *
 * @complexity O(1) per projection - constant time operations
 *   Used extensively in convexification and branching heuristics
 *
 * **Usage in branching:**
 * Helps compute optimal branching points by finding closest
 * feasible points to current LP solution.
 *
 * @see CouenneBranchingObject for branching point selection
 */
#ifndef CouenneProjections_hpp
#define CouenneProjections_hpp

#include <stdio.h>

#include "CouenneConfig.h"
#include "CouennePrecisions.hpp"

namespace Couenne {

/** Compute projection of point (x0, y0) on the segment defined by
 *  line ax + by + c <>= 0 (sign provided by parameter sign) and
 *  bounds [lb, ub] on x. Return distance from segment, 0 if satisfied
 */

COUENNELIB_EXPORT
CouNumber project (CouNumber a,   CouNumber b, CouNumber c,
		   CouNumber x0,  CouNumber y0,
		   CouNumber lb,  CouNumber ub,
		   int sign,
		   CouNumber *xp = NULL, CouNumber *yp = NULL);

/** Compute projection of point (x0, y0) on the segment defined by two
 *  points (x1,y1), (x2, y2) -- sign provided by parameter
 *  sign. Return distance from segment, 0 if on it.
 */

COUENNELIB_EXPORT
CouNumber projectSeg (CouNumber x0,  CouNumber y0,
		      CouNumber x1,  CouNumber y1,
		      CouNumber x2,  CouNumber y2,
		      int sign,
		      CouNumber *xp = NULL, CouNumber *yp = NULL);
}

#endif
