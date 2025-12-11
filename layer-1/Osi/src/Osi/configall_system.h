/**
 * @file configall_system.h
 * @brief Compiler-specific configuration router for non-autotools builds
 *
 * Routes to the appropriate compiler-specific configuration header based
 * on the detected compiler. Currently supports MSVC via configall_system_msc.h.
 * Used by *Config.h headers when HAVE_CONFIG_H is not defined.
 *
 * @see configall_system_msc.h for MSVC-specific settings
 * @see OsiConfig.h for main Osi configuration
 */
/*
 * This header file is included by the *Config.h in the individual
 * COIN packages when the code is compiled in a setting that doesn't
 * use the configure script (i.e., HAVE_CONFIG_H is not defined).
 * This header file includes the system and compile dependent header
 * file defining macros that depend on what compiler is used.
 */

#ifdef _MSC_VER
# include "configall_system_msc.h"
#else
# error "Trying to use configall_system for unknown compiler."
#endif
