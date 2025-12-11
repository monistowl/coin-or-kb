/**
 * @file OsiXprConfig.h
 * @brief Configuration header for OsiXpr (FICO Xpress interface)
 *
 * Provides build configuration for the Osi adapter to FICO Xpress-MP
 * Optimizer. Defines OSIXPRLIB_EXPORT for DLL import/export based on build
 * environment and platform. Requires separate Xpress installation and license.
 *
 * @see OsiXprSolverInterface.h for Xpress adapter class
 * @see OsiConfig.h for main Osi configuration
 */
/* Copyright (C) 2011
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * Include file for the configuration of OsiCommonTest.
 *
 * On systems where the code is configured with the configure script
 * (i.e., compilation is always done with HAVE_CONFIG_H defined), this
 * header file includes the automatically generated header file.
 *
 * On systems that are compiled in other ways (e.g., with the
 * Developer Studio), a header file is included to define those
 * macros that depend on the operating system and the compiler.  The
 * macros that define the configuration of the particular user setting
 * (e.g., presence of other COIN-OR packages or third party code) are set
 * by the files config_*default.h. The project maintainer needs to remember
 * to update these files and choose reasonable defines.
 * A user can modify the default setting by editing the config_*default.h
 * files.
 */

#ifndef __OSIXPRCONFIG_H__
#define __OSIXPRCONFIG_H__

#ifdef HAVE_CONFIG_H
#ifdef OSIXPRLIB_BUILD

#ifdef DLL_EXPORT
# define OSIXPRLIB_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define OSIXPRLIB_EXPORT __attribute__((__visibility__("default")))
#else
# define OSIXPRLIB_EXPORT
#endif

#else
#include "config_osixpr.h"
#endif

#else /* HAVE_CONFIG_H */


#ifndef OSIXPRLIB_EXPORT
# if defined(_WIN32) && defined(DLL_EXPORT)
#  ifdef OSIXPRLIB_BUILD
#   define OSIXPRLIB_EXPORT __declspec(dllexport)
#  else
#   define OSIXPRLIB_EXPORT __declspec(dllimport)
#  endif
# elif defined(__GNUC__) && __GNUC__ >= 4
#  define OSIXPRLIB_EXPORT __attribute__((__visibility__("default")))
# else
#  define OSIXPRLIB_EXPORT
# endif
#endif


#endif /* HAVE_CONFIG_H */

#endif /*__OSIXPRCONFIG_H__*/
