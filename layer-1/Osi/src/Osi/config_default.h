/**
 * @file config_default.h
 * @brief Default build configuration for Osi without autotools
 *
 * Provides configuration for builds not using the configure script.
 * Sets OSILIB_EXPORT for DLL building and includes public version macros.
 * Defines which solver interfaces are available (CPLEX, GLPK, Gurobi,
 * Mosek, SoPlex, Xpress) - uncomment the appropriate OSI_HAS_* macros.
 *
 * @see config_osi_default.h for public version macros
 * @see configall_system.h for system-specific settings
 */

/* include the COIN-OR-wide system specific configure header */
#include "configall_system.h"

/* this needs to come before the include of config_osi_default.h */
#ifndef OSILIB_EXPORT
#if defined(_WIN32) && defined(DLL_EXPORT)
#define OSILIB_EXPORT __declspec(dllexport)
#else
#define OSILIB_EXPORT
#endif
#endif

/* include the public project specific macros */
#include "config_osi_default.h"

/***************************************************************************/
/*             HERE DEFINE THE PROJECT SPECIFIC MACROS                     */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Define to 1 if the CoinUtils package is used.
 * Don't undef this unless you really know what you're doing.
 */
#define OSI_HAS_COINUTILS 1

/* Define to 1 if the Cplex package is used */
/* #define OSI_HAS_CPLEX 1 */

/* Define to 1 if the Glpk package is used */
/* #define OSI_HAS_GLPK 1 */

/* Define to 1 if the Gurobi package is used */
/* #define OSI_HAS_GUROBI 1 */

/* Define to 1 if the Mosek package is used */
/* #define OSI_HAS_MOSEK 1 */

/* Define to 1 if the SoPlex package is used */
/* #define OSI_HAS_SOPLEX 1 */

/* Define to 1 if the Xpress package is used */
/* #define OSI_HAS_XPRESS 1 */
