/**
 * @file config_alps_default.h
 * @brief Public Alps version macros for non-autotools builds
 *
 * Defines version information (ALPS_VERSION, ALPS_VERSION_MAJOR/MINOR/RELEASE)
 * and optional MPI availability (COIN_HAS_MPI). This is the public header
 * included by users of the Alps library when not using autotools.
 *
 * @see config_default.h for internal build configuration
 * @see AlpsConfig.h for unified configuration entry point
 */
/*===========================================================================*
 * This file is part of the Abstract Library for Parallel Search (ALPS).     *
 *                                                                           *
 * ALPS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Aykut Bulut, Lehigh University                                   *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2023, Lehigh University, Yan Xu, Aykut Bulut, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/


/***************************************************************************/
/*           HERE DEFINE THE PROJECT SPECIFIC PUBLIC MACROS                */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Version number of project */
#define ALPS_VERSION "trunk"

/* Major Version number of project */
#define ALPS_VERSION_MAJOR   9999

/* Minor Version number of project */
#define ALPS_VERSION_MINOR   9999

/* Release Version number of project */
#define ALPS_VERSION_RELEASE 9999

/* Define to 1 if the Mpi package is used */
/* #define COIN_HAS_MPI 1 */
