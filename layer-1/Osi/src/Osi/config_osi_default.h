/**
 * @file config_osi_default.h
 * @brief Public Osi version macros for non-autotools builds
 *
 * Defines version information and OSILIB_EXPORT macro for client code.
 * This is the public header included by users of the Osi library, while
 * config_default.h is used internally when building Osi itself.
 *
 * @see config_default.h for internal build configuration
 * @see OsiConfig.h for unified configuration entry point
 */

/***************************************************************************/
/*           HERE DEFINE THE PROJECT SPECIFIC PUBLIC MACROS                */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Version number of project */
#define OSI_VERSION      "trunk"

/* Major Version number of project */
#define OSI_VERSION_MAJOR   9999

/* Minor Version number of project */
#define OSI_VERSION_MINOR   9999

/* Release Version number of project */
#define OSI_VERSION_RELEASE 9999

#ifndef OSILIB_EXPORT
#if defined(_WIN32) && defined(DLL_EXPORT)
#define OSILIB_EXPORT __declspec(dllimport)
#else
#define OSILIB_EXPORT
#endif
#endif
