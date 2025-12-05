// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file MC_init.hpp
 * @brief Max-cut BCP initialization
 *
 * @algorithm Max-Cut Init: Process Factory Methods
 *
 * USER_initialize subclass for max-cut application.
 * Creates MC_tm and MC_lp instances when BCP spawns processes.
 *
 * **Factory methods:**
 * - tm_init(): Creates MC_tm, reads problem file
 * - lp_init(): Creates MC_lp for node processing
 *
 * @see BCP_USER.hpp for initialization interface
 */
#ifndef _MC_INIT_H
#define _MC_INIT_H

#include "BCP_USER.hpp"

class MC_initialize : public USER_initialize {
  // Declare this function if not the default single process communication is
  // wanted
  //   BCP_message_environment * msgenv_init();

   BCP_tm_user * tm_init(BCP_tm_prob& p,
			 const int argnum, const char * const * arglist);
   BCP_lp_user * lp_init(BCP_lp_prob& p);
};

#endif
