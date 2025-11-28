/**
 * @file SymConfig.h
 * @brief Build configuration for SYMPHONY
 *
 * Manages platform-specific configuration and symbol visibility.
 *
 * **Configuration modes:**
 * - HAVE_CONFIG_H: Uses autoconf-generated config.h
 * - Otherwise: Uses config_default.h / config_sym_default.h
 *
 * **Symbol visibility:**
 * - SYMPHONYLIB_EXPORT: DLL export on Windows
 * - __visibility__("default"): GCC visibility for -fvisibility=hidden
 *
 * **Include hierarchy:**
 * - SYMPHONYLIB_BUILD + HAVE_CONFIG_H → config.h
 * - Client + HAVE_CONFIG_H → config_sym.h
 * - SYMPHONYLIB_BUILD no autoconf → config_default.h
 * - Client no autoconf → config_sym_default.h
 *
 * @see config_default.h for package dependencies
 * @see config_sym_default.h for public API config
 */
#ifndef __SYMPHONY_CONFIG_H__
#define __SYMPHONY_CONFIG_H__

#ifdef HAVE_CONFIG_H
#ifdef SYMPHONYLIB_BUILD
#include "config.h"

/* overwrite SYMPHONYLIB_EXPORT from config.h when building SYMPHONY
 * we want it to be __declspec(dllexport) when building a DLL on Windows
 * we want it to be __attribute__((__visibility__("default"))) when building
 * with GCC, so user can compile with -fvisibility=hidden
 */
#ifdef DLL_EXPORT
#undef SYMPHONYLIB_EXPORT
#define SYMPHONYLIB_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#undef SYMPHONYLIB_EXPORT
#define SYMPHONYLIB_EXPORT __attribute__((__visibility__("default")))
#endif

#else
#include "config_sym.h"
#endif

#else /* HAVE_CONFIG_H */

#ifdef SYMPHONYLIB_BUILD
#include "config_default.h"
#else
#include "config_sym_default.h"
#endif

#endif /* HAVE_CONFIG_H */

#endif /*__SYMPHONY_CONFIG_H__*/
