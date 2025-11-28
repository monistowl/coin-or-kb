/**
 * @file CbcGenMessages.hpp
 * @brief Message IDs for cbc-generic standalone solver
 * Copyright (C) 2007, Lou Hafer, IBM Corporation and others.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcGenMsgCode: Enum of message IDs for the cbc-generic application.
 * These are distinct from CbcMessage (library messages) and are used
 * only by the standalone command-line solver.
 *
 * Message codes:
 * - CBCGEN_TEST_MSG: Test/debug message
 * - CBCGEN_NEW_SOLVER: Solver change notification
 * - CBCGEN_CONFUSION: Error/confusion state
 *
 * The actual message text is defined in CbcGenMessages.cpp.
 *
 * @see CbcMessage for library-level messages
 * @see CoinMessageHandler for message infrastructure
 */

#ifndef CbcGenMessages_H
#define CbcGenMessages_H

/*
*/

/*
  There's arguably not enough content here to justify a separate file, but it
  maintains the common pattern for COIN code.
*/

/*! \brief Symbolic names for cbc-generic messages

  These are the `internal IDs' for cbc-generic messages.
*/

typedef enum {
  CBCGEN_TEST_MSG = 1,
  CBCGEN_NEW_SOLVER,
  CBCGEN_CONFUSION,
  CBCGEN_DUMMY_END
} CbcGenMsgCode;

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
