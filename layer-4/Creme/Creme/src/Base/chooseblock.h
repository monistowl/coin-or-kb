/*
 * Name:    chooseblock.h
 * Author:  Pietro Belotti
 *
 * This code is published under the Eclipse Public License (EPL).
 * See http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * @file Base/chooseblock.h
 * @brief Constraint block selection for Creme RTR algorithm
 *
 * choose_block(): Select a block of constraints for randomized
 * rounding based on violation and satisfaction status.
 *
 * @see rtr.h for randomized rounding algorithm
 * @see sparse.h for LP data structure
 */

#ifndef CHOOSEBLOCK_H
#define CHOOSEBLOCK_H

void choose_block (sparseLP *, int *, char *, int, int, double *, double);

#endif
