// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinError.hpp
 * @brief Exception class and assertion macros for COIN-OR error handling
 *
 * Provides CoinError, a rich exception class that captures context about
 * where and why an error occurred, plus assertion macros that can optionally
 * throw CoinError instead of calling abort().
 *
 * @see CoinMessage.hpp for message handling without exceptions
 */

#ifndef CoinError_H
#define CoinError_H

#include <string>
#include <iostream>
#include <cassert>
#include <cstring>

#include "CoinUtilsConfig.h"
#include "CoinPragma.hpp"

/**
 * @brief Disable Windows crash dialog popups
 *
 * Calls SetErrorMode to prevent Windows from showing popup dialogs
 * when the application crashes. Useful for automated testing and
 * batch processing. No-op on non-Windows platforms.
 */
COINUTILSLIB_EXPORT
void WindowsErrorPopupBlocker();

//-------------------------------------------------------------------
//
// Error class used to throw exceptions
//
// Errors contain:
//
//-------------------------------------------------------------------

/**
 * @brief Exception class carrying context about where and why an error occurred
 *
 * CoinError is thrown by COIN-OR code when an error condition is detected.
 * It captures rich context for debugging:
 *   - message: Description of what went wrong
 *   - method: Name of the function that detected the error
 *   - class: Name of the class (or a hint string for assertions)
 *   - file: Source file name (for assertions)
 *   - lineNumber: Source line (for assertions, -1 otherwise)
 *
 * Typical usage:
 * @code
 *   throw CoinError("Matrix is singular", "solve", "CoinFactorization");
 * @endcode
 *
 * @see CoinAssert macros for assertion-based error reporting
 */
class COINUTILSLIB_EXPORT CoinError  {
  friend void CoinErrorUnitTest();

private:
  CoinError()
    : message_()
    , method_()
    , class_()
    , file_()
    , lineNumber_()
  {
    // nothing to do here
  }

public:
  //-------------------------------------------------------------------
  // Get methods
  //-------------------------------------------------------------------
  /**@name Get error attributes */
  //@{
  /**
   * @brief Get the error message text
   * @return Description of what went wrong
   */
  inline const std::string &message() const
  {
    return message_;
  }
  /**
   * @brief Get the name of the method that threw this error
   * @return Method/function name string
   */
  inline const std::string &methodName() const
  {
    return method_;
  }
  /**
   * @brief Get the class name or hint string
   * @return Class name for regular errors, hint for assertions
   */
  inline const std::string &className() const
  {
    return class_;
  }
  /**
   * @brief Get the source file name (assertions only)
   * @return File name where assertion failed, empty for regular errors
   */
  inline const std::string &fileName() const
  {
    return file_;
  }
  /**
   * @brief Get the source line number (assertions only)
   * @return Line number where assertion failed, -1 for regular errors
   */
  inline int lineNumber() const
  {
    return lineNumber_;
  }
  /**
   * @brief Print error details to stdout
   * @param doPrint If false, do nothing (default true)
   */
  inline void print(bool doPrint = true) const
  {
    if (!doPrint)
      return;
    if (lineNumber_ < 0) {
      std::cout << message_ << " in " << class_ << "::" << method_ << std::endl;
    } else {
      std::cout << file_ << ":" << lineNumber_ << " method " << method_
                << " : assertion \'" << message_ << "\' failed." << std::endl;
      if (class_ != "")
        std::cout << "Possible reason: " << class_ << std::endl;
    }
  }
  //@}

  /**@name Constructors and destructors */
  //@{
  /**
   * @brief Construct a CoinError with full context
   * @param message__ Description of the error condition
   * @param methodName__ Name of the method detecting the error
   * @param className__ Name of the class (or hint string for assertions)
   * @param fileName_ Source file name (optional, for assertions)
   * @param line Source line number (optional, -1 if not an assertion)
   */
  CoinError(
    std::string message__,
    std::string methodName__,
    std::string className__,
    std::string fileName_ = std::string(),
    int line = -1)
    : message_(message__)
    , method_(methodName__)
    , class_(className__)
    , file_(fileName_)
    , lineNumber_(line)
  {
    print(printErrors_);
  }

  /**
   * @brief Copy constructor
   * @param source CoinError to copy from
   */
  CoinError(const CoinError &source)
    : message_(source.message_)
    , method_(source.method_)
    , class_(source.class_)
    , file_(source.file_)
    , lineNumber_(source.lineNumber_)
  {
    // nothing to do here
  }

  /**
   * @brief Assignment operator
   * @param rhs CoinError to copy from
   * @return Reference to this object
   */
  CoinError &operator=(const CoinError &rhs)
  {
    if (this != &rhs) {
      message_ = rhs.message_;
      method_ = rhs.method_;
      class_ = rhs.class_;
      file_ = rhs.file_;
      lineNumber_ = rhs.lineNumber_;
    }
    return *this;
  }

  /// Destructor
  virtual ~CoinError()
  {
    // nothing to do here
  }
  //@}

private:
  /**@name Private member data */
  //@{
  /// message test
  std::string message_;
  /// method name
  std::string method_;
  /// class name or hint
  std::string class_;
  /// file name
  std::string file_;
  /// Line number
  int lineNumber_;
  //@}

public:
  /**
   * @brief Global flag controlling automatic error printing
   *
   * When true, CoinError constructor prints the error to stdout.
   * Defaults to false. Set to true for debugging.
   */
  static bool printErrors_;
};

#ifndef __STRING
#define __STRING(x) #x
#endif

#ifndef __GNUC_PREREQ
#define __GNUC_PREREQ(maj, min) (0)
#endif

#ifndef COIN_ASSERT
#define CoinAssertDebug(expression) assert(expression)
#define CoinAssertDebugHint(expression, hint) assert(expression)
#define CoinAssert(expression) assert(expression)
#define CoinAssertHint(expression, hint) assert(expression)
#else
#ifdef NDEBUG
#define CoinAssertDebug(expression) \
  {                                 \
  }
#define CoinAssertDebugHint(expression, hint) \
  {                                           \
  }
#else
#if defined(__GNUC__) && __GNUC_PREREQ(2, 6)
#define CoinAssertDebug(expression)                              \
  {                                                              \
    if (!(expression)) {                                         \
      throw CoinError(__STRING(expression), __PRETTY_FUNCTION__, \
        "", __FILE__, __LINE__);                                 \
    }                                                            \
  }
#define CoinAssertDebugHint(expression, hint)                    \
  {                                                              \
    if (!(expression)) {                                         \
      throw CoinError(__STRING(expression), __PRETTY_FUNCTION__, \
        hint, __FILE__, __LINE__);                               \
    }                                                            \
  }
#else
#define CoinAssertDebug(expression)             \
  {                                             \
    if (!(expression)) {                        \
      throw CoinError(__STRING(expression), "", \
        "", __FILE__, __LINE__);                \
    }                                           \
  }
#define CoinAssertDebugHint(expression, hint)   \
  {                                             \
    if (!(expression)) {                        \
      throw CoinError(__STRING(expression), "", \
        hint, __FILE__, __LINE__);              \
    }                                           \
  }
#endif
#endif
#if defined(__GNUC__) && __GNUC_PREREQ(2, 6)
#define CoinAssert(expression)                                   \
  {                                                              \
    if (!(expression)) {                                         \
      throw CoinError(__STRING(expression), __PRETTY_FUNCTION__, \
        "", __FILE__, __LINE__);                                 \
    }                                                            \
  }
#define CoinAssertHint(expression, hint)                         \
  {                                                              \
    if (!(expression)) {                                         \
      throw CoinError(__STRING(expression), __PRETTY_FUNCTION__, \
        hint, __FILE__, __LINE__);                               \
    }                                                            \
  }
#else
#define CoinAssert(expression)                  \
  {                                             \
    if (!(expression)) {                        \
      throw CoinError(__STRING(expression), "", \
        "", __FILE__, __LINE__);                \
    }                                           \
  }
#define CoinAssertHint(expression, hint)        \
  {                                             \
    if (!(expression)) {                        \
      throw CoinError(__STRING(expression), "", \
        hint, __FILE__, __LINE__);              \
    }                                           \
  }
#endif
#endif

//#############################################################################
/**
 * @brief Unit test function for CoinError class
 *
 * Tests the CoinError class methods. Declared as a free function
 * rather than a member so it doesn't need to be compiled into the
 * optimized library.
 *
 * @see CoinError
 */
void CoinErrorUnitTest();

#ifdef __LINE__
#define CoinErrorFL(x, y, z) CoinError((x), (y), (z), __FILE__, __LINE__)
#endif

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
