/*
 * Name:   linopt.h
 * Author: Pietro Belotti
 *
 * This code is published under the Eclipse Public License (EPL).
 * See http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * @file Base/linopt.h
 * @brief One-variable local optimization for Creme
 *
 * Implements one_opt() for single-variable neighborhood search.
 *
 * @see sparse.h for LP data structure
 */

#ifndef LINOPT_H
#define LINOPT_H

#include "sparse.h"

int compare_abs (const void *one, const void *two);

double one_opt (sparseLP *, double *, double *, double);

#endif
