// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_os.hpp
 * @brief OS abstraction layer for BCP
 *
 * @algorithm OS Utilities: Memory and Process Info
 *
 * Cross-platform wrappers for system-level operations:
 *
 * **Process management:**
 * - setpriority(): Process scheduling priority (Unix)
 * - gethostname(): Machine identification
 * - GETPID macro: Process ID abstraction
 *
 * **Memory monitoring:**
 * - BCP_free_mem(): System free RAM via sysinfo()
 * - BCP_used_heap(): Heap usage via mallinfo()
 *
 * Returns -1 on platforms without required APIs.
 * Used for dynamic load balancing and memory-aware scheduling.
 */
#ifndef _BCP_OS_H
#define _BCP_OS_H

#include <cstdio>
#include "BcpConfig.h"

//-----------------------------------------------------------------------------
#ifdef HAVE_SYS_RESOURCE_H
#  include <sys/resource.h>
#else
#  define setpriority(x,y,z)
#endif
//-----------------------------------------------------------------------------
#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif

#ifdef HAVE_PROCESS_H
#  include <process.h>
#endif

#ifndef HAVE_GETHOSTNAME
#  define gethostname(x,y)
#endif

#ifdef HAVE_GETPID
#  define GETPID (getpid())
#else
#  define GETPID (0)
#endif
//-----------------------------------------------------------------------------

#ifdef HAVE_SYS_SYSINFO_H
#include <sys/sysinfo.h>
#endif
static inline long BCP_free_mem()
{
#ifdef HAVE_SYSINFO
  struct sysinfo info;
  sysinfo(&info);
  return info.mem_unit*info.freeram;
#else
  return -1;
#endif
}
//-----------------------------------------------------------------------------

#ifdef HAVE_MALLINFO
#include <malloc.h>
#endif

static inline long BCP_used_heap()
{
#ifdef HAVE_MALLINFO
  struct mallinfo info = mallinfo();
  return info.usmblks + info.uordblks;;
#else
  return -1;
#endif
}
//-----------------------------------------------------------------------------

#endif
