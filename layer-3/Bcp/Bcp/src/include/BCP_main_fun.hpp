// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_main_fun.hpp
 * @brief Process entry point functions for BCP
 *
 * @algorithm Process Entry Points: Main Functions per Process Type
 *
 * Entry point functions for each BCP process type. Called by message
 * environment when spawning workers:
 *
 * - BCP_tm_main(): Tree Manager (coordinator, command line parsing)
 * - BCP_tmstorage_main(): Tree Storage (external node storage)
 * - BCP_lp_main(): LP worker (relaxation solving)
 * - BCP_cg_main(): Cut Generator (separation)
 * - BCP_vg_main(): Variable Generator (pricing)
 *
 * **Parameters:**
 * - msg_env: Message passing environment
 * - user_init: User's initialization object
 * - my_id: Process identifier
 * - parent: Parent process ID
 * - ub: Initial upper bound
 *
 * **Return:**
 * BCP_process_t indicating process type or termination reason.
 *
 * @see BCP_USER.hpp for USER_initialize
 * @see bcp_main() for top-level entry
 */
#ifndef _BCP_MAIN_FUN_H
#define _BCP_MAIN_FUN_H

#include "BCP_enum_process_t.hpp"

class BCP_message_environment;
class USER_initialize;

void BCP_tm_main(BCP_message_environment* msg_env,
		 USER_initialize* user_init,
		 const int argnum, const char* const * arglist);

BCP_process_t BCP_tmstorage_main(BCP_message_environment* msg_env,
				 USER_initialize* user_init,
				 int my_id, int parent, double ub);

BCP_process_t BCP_lp_main(BCP_message_environment* msg_env,
			  USER_initialize* user_init,
			  int my_id, int parent, double ub);

#if 0
BCP_process_t BCP_cp_main(BCP_message_environment* msg_env,
			  USER_initialize* user_init,
			  int my_id, int parent, double ub);

BCP_process_t BCP_vp_main(BCP_message_environment* msg_env,
			  USER_initialize* user_init,
			  int my_id, int parent, double ub);
#endif

BCP_process_t BCP_cg_main(BCP_message_environment* msg_env,
			  USER_initialize* user_init,
			  int my_id, int parent, double ub);

BCP_process_t BCP_vg_main(BCP_message_environment* msg_env,
			  USER_initialize* user_init,
			  int my_id, int parent, double ub);

#endif
