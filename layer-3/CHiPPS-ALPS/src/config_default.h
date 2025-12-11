/**
 * @file config_default.h
 * @brief Default build configuration for Alps without autotools
 *
 * Provides configuration for builds not using the configure script.
 * Includes system-specific settings via configall_system.h and public
 * version macros. Defines debug levels (COIN_ALPS_CHECKLEVEL, VERBOSITY)
 * and package dependencies (ALPS_HAS_COINUTILS, ALPS_HAS_CLP).
 *
 * @see config_alps_default.h for public version macros
 * @see AlpsConfig.h for unified configuration entry point
 */

/* include the COIN-OR-wide system specific configure header */
#include "configall_system.h"

/* include the public project specific macros */
#include "config_alps_default.h"

/***************************************************************************/
/*             HERE DEFINE THE PROJECT SPECIFIC MACROS                     */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Define to the debug sanity check level (0 is no test) */
#define COIN_ALPS_CHECKLEVEL 0

/* Define to the debug verbosity level (0 is no output) */
#define COIN_ALPS_VERBOSITY 0

/* Define to 1 if the CoinUtils package is used */
#define ALPS_HAS_COINUTILS 1

/* Define to 1 if the Clp package is used */
#define ALPS_HAS_CLP 1
