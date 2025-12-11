/**
 * @file guess_basis.h
 * @brief Heuristic starting basis selection from IPM solution
 *
 * GuessBasis() constructs an initial basis from column weights,
 * preferring columns with larger weights. Used by crossover to
 * select basic variables from the interior point solution.
 *
 * The returned basis may be singular and requires repair before use.
 *
 * @see starting_basis.h for crash basis construction
 * @see crossover.h for the crossover algorithm
 */
#ifndef IPX_GUESS_BASIS_H_
#define IPX_GUESS_BASIS_H_

#include "ipm/ipx/control.h"
#include "ipm/ipx/model.h"

namespace ipx {

// Returns a vector of m column indices (m = model.rows()) as a guess for a
// basis. Columns with a larger weight are chosen preferably. The basis can be
// singular (and usually is).
//
// @colweights size n+m array (n = model.cols()) with entries in the closed
//             interval [0,INFINITY].
//
std::vector<Int> GuessBasis(const Control& control, const Model& model,
                            const double* colweights);

}  // namespace ipx

#endif // IPX_GUESS_BASIS_H_
