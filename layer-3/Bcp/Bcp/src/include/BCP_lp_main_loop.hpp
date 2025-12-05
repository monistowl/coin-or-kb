// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_lp_main_loop.hpp
 * @brief LP process main loop entry point
 *
 * @algorithm LP Main Loop: Node Processing Cycle
 *
 * BCP_lp_main_loop() is the top-level driver for LP process execution:
 *
 * 1. Wait for node from Tree Manager
 * 2. Reconstruct node (apply deltas to get vars/cuts/warmstart)
 * 3. Solve LP relaxation
 * 4. Generate cuts/variables
 * 5. Check for integer feasibility
 * 6. Branch or fathom
 * 7. Report results to TM
 * 8. Repeat until termination message
 *
 * @see BCP_lp.hpp for BCP_lp_prob state
 * @see BCP_lp_user.hpp for user callbacks invoked during loop
 */
#ifndef _BCP_LP_MAIN_LOOP_H
#define _BCP_LP_MAIN_LOOP_H

class BCP_lp_prob;

void BCP_lp_main_loop(BCP_lp_prob& p);

#endif
