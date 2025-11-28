// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file MyEventHandler.hpp
 * @brief Example event handler demonstrating callback customization
 *
 * Sample implementation of ClpEventHandler showing how users can
 * intercept simplex events for custom processing. Used in unit tests.
 *
 * To create your own handler:
 * 1. Inherit from ClpEventHandler
 * 2. Override event() method
 * 3. Return 0 to continue, non-zero to stop
 * 4. Attach via ClpSimplex::passInEventHandler()
 *
 * Available events (see ClpEventHandler::Event):
 * - endOfIteration: After each pivot
 * - endOfFactorization: After basis refactorization
 * - endOfValuesPass: After crash/values pass
 * - node: During B&B (if used with Cbc)
 *
 * The model_ pointer gives access to full solver state including
 * current solution, basis, and objective value.
 *
 * @see ClpEventHandler for the event types and interface
 * @see ClpSimplex::passInEventHandler() to install
 */

#ifndef MyEventHandler_H
#define MyEventHandler_H

#include "ClpEventHandler.hpp"

/** This is so user can trap events and do useful stuff.
    This is used in Clp/Test/unitTest.cpp

    ClpSimplex model_ is available as well as anything else you care
    to pass in
*/

class MyEventHandler : public ClpEventHandler {

public:
  /**@name Overrides */
  //@{
  virtual int event(Event whichEvent);
  //@}

  /**@name Constructors, destructor etc*/
  //@{
  /** Default constructor. */
  MyEventHandler();
  /// Constructor with pointer to model (redundant as setEventHandler does)
  MyEventHandler(ClpSimplex *model);
  /** Destructor */
  virtual ~MyEventHandler();
  /** The copy constructor. */
  MyEventHandler(const MyEventHandler &rhs);
  /// Assignment
  MyEventHandler &operator=(const MyEventHandler &rhs);
  /// Clone
  virtual ClpEventHandler *clone() const;
  //@}

protected:
  // data goes here
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
