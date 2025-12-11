/**
 * @file config_sym_default.h
 * @brief Default SYMPHONY configuration for non-autoconf builds
 *
 * Provides version macros and DLL export definitions when building
 * without autotools/configure. Used on Windows with Visual Studio
 * or other environments without autoconf.
 *
 * **Macros Defined:**
 * - SYMPHONY_VERSION: Version string
 * - SYMPHONY_VERSION_MAJOR/MINOR/RELEASE: Numeric version components
 * - SYMPHONYLIB_EXPORT: DLL import/export decoration
 *
 * @see SymConfig.h for autoconf-generated configuration
 */
/***************************************************************************/
/*           HERE DEFINE THE PROJECT SPECIFIC PUBLIC MACROS                */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Version number of project */
#define SYMPHONY_VERSION         "trunk"

/* Major Version number of project */
#define SYMPHONY_VERSION_MAJOR   9999

/* Minor Version number of project */
#define SYMPHONY_VERSION_MINOR   9999

/* Release Version number of project */
#define SYMPHONY_VERSION_RELEASE 9999

#ifndef SYMPHONYLIB_EXPORT
#if defined(_WIN32) && defined(DLL_EXPORT)
#define SYMPHONYLIB_EXPORT __declspec(dllimport)
#else
#define SYMPHONYLIB_EXPORT
#endif
#endif
