/*
 * Name:   move.h
 * Author: Pietro Belotti
 *
 * This code is published under the Eclipse Public License (EPL).
 * See http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * @file Base/move.h
 * @brief Variable move operation for Creme local search
 *
 * move(): Perform a single variable update in local search,
 * adjusting primal values and updating constraint satisfaction.
 *
 * @see locsrch.h for local search algorithm
 * @see linopt.h for one-opt improvement
 */

#ifndef MOVE_H
#define MOVE_H

#include "sparse.h"

int move (sparseLP *, double *, double *, int *, char *, double, double *);

#endif
