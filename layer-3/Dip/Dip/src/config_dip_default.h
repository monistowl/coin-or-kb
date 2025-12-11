/**
 * @file config_dip_default.h
 * @brief Public DIP version macros and solver availability flags
 *
 * Defines DIP_VERSION, DIP_VERSION_MAJOR/MINOR/RELEASE and flags
 * for optional solver availability (DIP_HAS_CLP, DIP_HAS_CBC).
 * Used when building without autotools configure.
 *
 * @see config_default.h for internal build configuration
 * @see DecompConfig.h for unified configuration header
 */
//===========================================================================//
// This file is part of the DIP Solver Framework.                            //
//                                                                           //
// DIP is distributed under the Eclipse Public License as part of the        //
// COIN-OR repository (http://www.coin-or.org).                              //
//                                                                           //
// Authors: Matthew Galati, SAS Institute Inc. (matthew.galati@sas.com)      //
//          Ted Ralphs, Lehigh University (ted@lehigh.edu)                   //
//          Jiadong Wang, Lehigh University (jiw408@lehigh.edu)              //
//                                                                           //
// Copyright (C) 2002-2019, Lehigh University, Matthew Galati, Ted Ralphs    //
// All Rights Reserved.                                                      //
//===========================================================================//

/***************************************************************************/
/*           HERE DEFINE THE PROJECT SPECIFIC PUBLIC MACROS                */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Version number of project */
#define DIP_VERSION "trunk"

/* Major Version number of project */
#define DIP_VERSION_MAJOR   9999

/* Minor Version number of project */
#define DIP_VERSION_MINOR   9999

/* Release Version number of project */
#define DIP_VERSION_RELEASE 9999

/* Define to 1 if the Clp package is available */
#define DIP_HAS_CLP 1

/* Define to 1 if the Cbc package is available */
#define DIP_HAS_CBC 1

