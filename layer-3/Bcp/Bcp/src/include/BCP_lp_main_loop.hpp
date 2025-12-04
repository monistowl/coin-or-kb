// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_lp_main_loop.hpp
 * @brief BCP LP process
 *
 * LP relaxation process: solves node relaxations, generates cuts.
 */
#ifndef _BCP_LP_MAIN_LOOP_H
#define _BCP_LP_MAIN_LOOP_H

class BCP_lp_prob;

void BCP_lp_main_loop(BCP_lp_prob& p);

#endif
