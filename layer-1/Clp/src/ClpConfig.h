/**
 * @file ClpConfig.h
 * @brief Clp configuration and platform detection
 *
 * Handles build configuration for cross-platform compatibility:
 * - HAVE_CONFIG_H: Uses autoconf-generated config.h
 * - CLPLIB_BUILD: Building the library vs. using it
 * - DLL_EXPORT: Windows DLL export declarations
 * - GCC visibility: Hidden visibility with explicit exports
 *
 * Defines CLPLIB_EXPORT macro for public API symbols.
 *
 * Configuration precedence:
 * 1. config.h (autoconf) when HAVE_CONFIG_H defined
 * 2. config_clp.h for configured installations
 * 3. config_clp_default.h for manual builds
 */

/* Copyright (C) 2011
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 */

#ifndef __CLPCONFIG_H__
#define __CLPCONFIG_H__

#ifdef HAVE_CONFIG_H
#ifdef CLPLIB_BUILD
#include "config.h"

/* overwrite CLPLIB_EXPORT from config.h when building Clp
 * we want it to be __declspec(dllexport) when building a DLL on Windows
 * we want it to be __attribute__((__visibility__("default"))) when building with GCC,
 *   so user can compile with -fvisibility=hidden
 */
#ifdef DLL_EXPORT
#undef CLPLIB_EXPORT
#define CLPLIB_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#undef CLPLIB_EXPORT
#define CLPLIB_EXPORT __attribute__((__visibility__("default")))
#endif

#else
#include "config_clp.h"
#endif

#else /* HAVE_CONFIG_H */

#ifdef CLPLIB_BUILD
#include "config_default.h"
#else
#include "config_clp_default.h"
#endif

#endif /* HAVE_CONFIG_H */

#endif /*__CLPCONFIG_H__*/
