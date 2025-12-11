/**
 * @file ipx_config.h
 * @brief IPX integer type configuration
 *
 * Defines ipxint as alias for HighsInt, enabling 32-bit or 64-bit
 * integer support based on build configuration.
 *
 * @see ipx_internal.h for internal type definitions using ipxint
 */
#ifndef IPX_CONFIG_H_
#define IPX_CONFIG_H_

#include <stdint.h>

#include "util/HighsInt.h"
typedef HighsInt ipxint;

#endif /* IPX_CONFIG_H_ */
