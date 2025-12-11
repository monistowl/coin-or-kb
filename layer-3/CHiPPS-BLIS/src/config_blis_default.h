/**
 * @file config_blis_default.h
 * @brief Public BLIS version macros for non-autotools builds
 *
 * Defines version information (BLIS_VERSION, BLIS_VERSION_MAJOR/MINOR/RELEASE)
 * for client code. This is the public header included by users of the BLIS
 * library when not using autotools.
 *
 * @see config_default.h for internal build configuration
 * @see BlisConfig.h for unified configuration entry point
 */
/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
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
 * Copyright (C) 2001-2023, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

/***************************************************************************/
/*           HERE DEFINE THE PROJECT SPECIFIC PUBLIC MACROS                */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Version number of project */
#define BLIS_VERSION "devel"

/* Major Version number of project */
#define BLIS_VERSION_MAJOR   9999

/* Minor Version number of project */
#define BLIS_VERSION_MINOR   9999

/* Release Version number of project */
#define BLIS_VERSION_RELEASE 9999

