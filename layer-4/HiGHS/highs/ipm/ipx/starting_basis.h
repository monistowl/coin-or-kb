/**
 * @file starting_basis.h
 * @brief Initial basis construction from interior point iterates
 *
 * Constructs a starting basis for crossover using interior point scaling
 * factors as column weights. Handles special cases:
 * - Free variables (lb=-∞, ub=+∞): BASIC_FREE or NONBASIC_FIXED
 * - Fixed slacks (lb=ub): BASIC_FREE or NONBASIC_FIXED
 * - Fixed structural: NONBASIC_FIXED
 * - Others: BASIC or NONBASIC
 *
 * Linear dependencies among free variables or equality constraints
 * are resolved by fixing dependent variables at zero.
 *
 * @algorithm IPM-to-Basis Conversion:
 *   Use interior point scaling factors as basis selection weights:
 *   @math weight[j] = x[j]/z[j] (primal/dual slack ratio from IPM)
 *         Large weight → variable likely basic (away from bound)
 *         Small weight → variable likely nonbasic (near bound)
 *   Calls ConstructBasisFromWeights() with these weights.
 *   @complexity O(m · nnz) for weighted crash procedure
 *
 * @algorithm Dependency Resolution:
 *   Handle free variables and equality constraints:
 *   @math Free vars: columns may be linearly dependent → fix some at zero
 *         Equality rows: may have dependent columns → fix slack
 *   Dependent variables get BASIC_FREE or NONBASIC_FIXED status.
 *   Maintains primal/dual residual invariance during fixing.
 *   @note TODO: check for primal/dual infeasibility after resolution
 *
 * @see guess_basis.h for basis construction from weights
 * @see iterate.h for interior point state
 */
#ifndef IPX_STARTING_BASIS_H_
#define IPX_STARTING_BASIS_H_

#include "ipm/ipx/basis.h"
#include "ipm/ipx/iterate.h"

namespace ipx {

// Constructs a basis with the following properties:
//
// If lb[j]=-inf and ub[j]=inf, then the variable becomes either
// - basic with status BASIC_FREE, or
// - nonbasic with status NONBASIC_FIXED.                         (1)
//
// If lb[j]==ub[j] and j is a slack variable, then it becomes either
// - basic with status BASIC_FREE, or                             (2)
// - nonbasic with status NONBASIC_FIXED.
//
// If lb[j]==ub[j] and j is not a slack variable, then it becomes
// - nonbasic with status NONBASIC_FIXED.
//
// All other variables get status BASIC or NONBASIC.
//
// In case (1) the columns corresponding to free variables are linearly
// dependent. In case (2) the rows to equality constraints are linearly
// dependent. In each case the dependent variables are moved to zero without
// altering the primal or dual residual.
// TODO: we need to check for primal/dual infeasibility here.
//
// The method calls ConstructBasisFromWeights() using the interior point
// scaling factors as column weights. If a variable gets status BASIC_FREE or
// NONBASIC_FIXED, then its state in @iterate is changed accordingly to free or
// fixed. On return info->errflag is nonzero if an error occured.
//
void StartingBasis(Iterate* iterate, Basis* basis, Info* info);

}  // namespace ipx

#endif  // IPX_STARTING_BASIS_H_
