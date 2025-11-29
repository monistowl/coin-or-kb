/*
 * Name:   lpio.h
 * Author: Pietro Belotti
 *
 * This code is published under the Eclipse Public License (EPL).
 * See http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * @file Base/lpio.h
 * @brief LP file I/O functions for Creme solver
 *
 * read_problem(): Parse LP problem from file into sparseLP structure.
 * printLP(): Display LP problem contents.
 * clearLP(): Deallocate LP memory.
 *
 * @see sparse.h for sparseLP data structure
 */

#ifndef LPIO_H
#define LPIO_H

#include "sparse.h"

int  read_problem (sparseLP *, char **);

void printLP      (int   *, sparseLP *);
void clearLP               (sparseLP *);

#endif
