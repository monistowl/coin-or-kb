/*
 * Name:   locsrch.h
 * Author: Pietro Belotti
 *
 * This code is published under the Eclipse Public License (EPL).
 * See http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * @file Base/locsrch.h
 * @brief Local search algorithm for Creme LP solver
 *
 * Implements locsrch() with dvar (delta variable) and frontier structures.
 *
 * @see rtr.h for randomized rounding alternative
 * @see sparse.h for LP data structure
 */

#ifndef LOCSRCH_H
#define LOCSRCH_H

#include "sparse.h"

typedef struct _dvar {

  int    nsi, index;
  double delta;

} dvar;

typedef struct _pass {

  double thres;
  char   sense;

} frontier;


int locsrch (sparseLP *, double *, double *, char *, double *);

#endif
