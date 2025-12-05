// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_error.hpp
 * @brief Fatal error handling for BCP
 *
 * @algorithm Error Handling: BCP_fatal_error Class
 *
 * Simple error handling via BCP_fatal_error exception-like class.
 * Construction triggers error message output and optional abort().
 *
 * **Behavior:**
 * - Prints formatted error message to stdout
 * - Flushes all buffers
 * - Calls abort() if abort_on_error is true (creates core dump)
 *
 * **Control:**
 * - BCP_fatal_error::abort_on_error: Static flag to enable/disable abort
 *
 * @note Not a proper C++ exception - uses abort() for distributed debugging.
 */
#ifndef _BCP_ERROR_H
#define _BCP_ERROR_H

// This file is fully docified.

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

/** 
    Currently there isn't any error handling in BCP. When an object of this
    type is created, the string stored in the character array of the argument
    is printed out and execution is aborted with <code>abort()</code> (thus a
    core dump is created).
*/
    
class BCP_fatal_error{
public:
   static bool abort_on_error;

public:
   /** The constructor prints out the error message, flushes the stdout buffer
       and aborts execution. */
#if 0
   BCP_fatal_error(const char * error) {
      printf("%s", error);
      fflush(0);
      abort();
   }
#endif
   BCP_fatal_error(const std::string& str) {
      printf("%s", str.c_str());
      fflush(0);
      if (abort_on_error)
	 abort();
   }
   BCP_fatal_error(const char * format, ...) {
      va_list valist;
      va_start(valist,format);
      vprintf(format, valist);
      va_end(valist);
      fflush(0);
      if (abort_on_error)
	 abort();
   }
   /** The destructor exists only because it must. */
   ~BCP_fatal_error() {}
};

#endif
