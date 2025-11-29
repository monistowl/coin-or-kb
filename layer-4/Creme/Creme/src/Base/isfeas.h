/*
 * Name:    isfeas.h
 * Author:  Pietro Belotti
 *
 * This code is published under the Eclipse Public License (EPL).
 * See http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * @file Base/isfeas.h
 * @brief Feasibility checking for Creme LP solutions
 *
 * isFeas(): Verify if a point satisfies LP constraints.
 * Returns number of satisfied constraints and updates satisfaction flags.
 *
 * @see locsrch.h for local search that uses feasibility checks
 * @see sparse.h for LP data structure
 */

#ifndef ISFEAS_H
#define ISFEAS_H

#include "sparse.h"

int isFeas (sparseLP *,    /* sparse LP data                          */
	    char     *,    /* alleged fulfilled constraints           */
	    double   *,    /* current point                           */
            int      *);   /* alleged number of constraints satisfied */

#endif
