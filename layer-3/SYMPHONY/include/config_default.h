/**
 * @file config_default.h
 * @brief Default build configuration for SYMPHONY library
 *
 * Defines package dependencies when not using autoconf.
 * Edit this file to enable/disable optional solver backends.
 *
 * **Required packages (always enabled):**
 * - COIN_HAS_CGL: CGL cut generators
 * - COIN_HAS_CLP: CLP linear solver
 * - COIN_HAS_COINUTILS: CoinUtils foundation
 * - COIN_HAS_OSI: OSI solver interface
 *
 * **Optional packages (commented by default):**
 * - COIN_HAS_CBC: Cbc MIP solver
 * - COIN_HAS_VOL: Volume algorithm
 * - COIN_HAS_CPX: CPLEX
 * - COIN_HAS_GLPK: GLPK
 * - COIN_HAS_MSK: Mosek
 * - COIN_HAS_XPR: Xpress
 * - COIN_DEBUG: Runtime sanity checks
 *
 * @see SymConfig.h for configuration selection
 */
/* include the COIN-OR-wide system specific configure header */
#include "configall_system.h"

/* include the public project specific macros */
#include "config_sym_default.h"

/***************************************************************************/
/*             HERE DEFINE THE PROJECT SPECIFIC MACROS                     */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* If defined, debug sanity checks are performed during runtime */
/* #define COIN_DEBUG 1 */

/* Define to 1 if the Cbc package is used */
/* #define COIN_HAS_CBC 1 */

/* Define to 1 if the Cgl package is used */
#define COIN_HAS_CGL 1

/* Define to 1 if the Clp package is used */
#define COIN_HAS_CLP 1

/* Define to 1 if the CoinUtils package is used */
#define COIN_HAS_COINUTILS 1

/* Define to 1 if the Osi package is used */
#define COIN_HAS_OSI 1

/* Define to 1 if the Osi package is used */
#define COIN_HAS_OSITESTS 1

/* Define to 1 if the Vol package is used */
/* #define COIN_HAS_VOL 1 */

/* Define to 1 if the Cplex package is used */
/* #define COIN_HAS_CPX 1 */

/* Define to 1 if the Dylp package is used */
/* #undef COIN_HAS_DYLP */

/* Define to 1 if the FortMP package is used */
/* #undef COIN_HAS_FMP */

/* Define to 1 if the Glpk package is used */
/* #undef COIN_HAS_GLPK */

/* Define to 1 if the Mosek package is used */
/* #undef COIN_HAS_MSK */

/* Define to 1 if the Osl package is used */
/* #undef COIN_HAS_OSL */

/* Define to 1 if the Soplex package is used */
/* #undef COIN_HAS_SPX */

/* Define to 1 if the Sym package is used */
/* #undef COIN_HAS_SYM */

/* Define to 1 if the Xpress package is used */
/* #undef COIN_HAS_XPR */

