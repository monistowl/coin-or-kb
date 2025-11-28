// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file SmiMessage.hpp
 * @brief Message handler and codes for Smi logging
 *
 * SmiMessage extends CoinMessages to provide structured logging
 * for the stochastic programming interface.
 *
 * **SMI_Message Enum:**
 * - SMI_SCENARIO_FINISHED: Scenario processing complete
 * - SMI_DUMMY_END: End marker
 *
 * **SmiMessage Class:**
 * CoinMessages-based message handler:
 * - Constructor sets up message text templates
 * - Supports multiple languages (default us_en)
 *
 * @see SmiScnModel.hpp for message handler usage
 * @see CoinMessages, CoinMessageHandler (CoinUtils) for base classes
 */

#ifndef SmiMessage_H
#define SmiMessage_H


#include "CoinPragma.hpp"

// This deals with Smi messages (as against Osi messages etc)

#include "CoinMessageHandler.hpp"
enum SMI_Message
{
  SMI_SCENARIO_FINISHED,
  SMI_DUMMY_END
};

/** This deals with Clp messages (as against Osi messages etc)
 */
class SmiMessage : public CoinMessages {

public:

  /**@name Constructors etc */
  //@{
  /** Constructor */
  SmiMessage(Language language=us_en);
  //@}

};

#endif
