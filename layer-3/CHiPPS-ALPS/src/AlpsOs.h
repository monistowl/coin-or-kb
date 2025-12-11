/**
 * @file AlpsOs.h
 * @brief Platform detection and routing for ALPS
 *
 * Detects the current operating system and includes the appropriate
 * platform-specific header. Supports Linux (AlpsLinux.h), Cygwin
 * (AlpsCygwin.h), AIX 4.3 (AlpsAix43.h), SunOS (AlpsSunos.h), and
 * macOS/Darwin (AlpsMACH.h).
 *
 * @see AlpsLinux.h for Linux-specific definitions
 * @see AlpsCygwin.h for Cygwin-specific definitions
 */
/*===========================================================================*
 * This file is part of the Abstract Library for Parallel Search (ALPS).     *
 *                                                                           *
 * ALPS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Aykut Bulut, Lehigh University                                   *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2023, Lehigh University, Yan Xu, Aykut Bulut, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/


#ifndef AlpsOs_h_
#define AlpsOs_h_

// AlpsOs.h is modified from BCP_os.hpp
// This file is fully docified.
// There's nothing to docify...

#if (defined(__GNUC__) && defined(__linux__))
#  include "AlpsLinux.h"
#endif

#if defined(__CYGWIN__) && defined(__GNUC__)
#  include "AlpsCygwin.h"
#endif

#if defined(_AIX43)
#  include "AlpsAix43.h"
#endif

#if defined(__GNUC__) && defined(__sparc) && defined(__sun)
#  include "AlpsSunos.h"
#endif

#if defined(__MACH__) && defined(__GNUC__)
#  include "AlpsMACH.h"
#endif

#endif
