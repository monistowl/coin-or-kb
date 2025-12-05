// BCP_message_mpi.hpp is adeclaration of BCP_message_mpi
// Sonya Marcarelli & Igor Vasil'ev (vil@icc.ru)
// All Rights Reserved.

/**
 * @file BCP_message_mpi.hpp
 * @brief MPI message passing for BCP
 *
 * @algorithm MPI Backend: BCP_mpi_environment Implementation
 *
 * MPI implementation of BCP_message_environment interface.
 * Requires COIN_HAS_MPI to be defined.
 *
 * **Key methods:**
 * - is_mpi(): Detects MPI environment and process count
 * - send/receive(): Point-to-point messaging with tags
 * - multicast(): Broadcast to multiple targets
 * - start_processes(): Spawn workers on machines
 * - probe(): Non-blocking message check
 *
 * **Process management:**
 * Tracks process IDs, handles initialization/finalization,
 * checks liveness of remote processes.
 *
 * @see BCP_message.hpp for abstract interface
 * @see BCP_message_pvm.hpp for PVM backend
 */
#ifndef _BCP_MESSAGE_MPI_H
#define _BCP_MESSAGE_MPI_H

#include "BcpConfig.h"

#if defined(COIN_HAS_MPI)

#include "BCP_message.hpp"

//#############################################################################

class BCP_mpi_environment : public BCP_message_environment {
private:
    static int seqproc;
    static int num_proc;
    static bool mpi_init_called;
   
private:
    void check_error(const int code, const char* str) const;

public:
    /** Function that determines whether we are running in an mpi environment.
	Returns the mpi id of the process if we are *and* there are more than 1
	processes. Otherwise returns -1 */
    static int is_mpi(int argc, char *argv[]);

    /** Constructor will initialize the MPI environment */
    BCP_mpi_environment(int argc,char *argv[]);
    ~BCP_mpi_environment();

    int num_procs();

    int register_process(USER_initialize* user_init);
    int parent_process();

    bool alive(const int pid); 
    const int* alive(int num, const int* pids);

    void send(const int target, const BCP_message_tag tag);
    void send(const int target,
	      const BCP_message_tag tag, const BCP_buffer& buf);

    void multicast(int num, const int* targets,
    		   const BCP_message_tag tag);
    void multicast(int num, const int* targets,
    		   const BCP_message_tag tag, const BCP_buffer& buf);

    void receive(const int source,
    		 const BCP_message_tag tag, BCP_buffer& buf,
    		 const double timeout);
    bool probe(const int source, const BCP_message_tag tag);

    int start_process(const BCP_string& exe,
    		      const bool debug);
    int start_process(const BCP_string& exe,
    		      const BCP_string& machine,
    		      const bool debug);
    bool start_processes(const BCP_string& exe,
			 const int proc_num,
			 const bool debug,
			 int* ids);
    bool start_processes(const BCP_string& exe,
			 const int proc_num,
			 const BCP_vec<BCP_string>& machines,
			 const bool debug,
			 int* ids);

//    void stop_process(const int process);
//    void stop_processes(const BCP_proc_array* processes);
};

int MPIDI_BGLTS_get_num_messages();

#endif /* COIN_HAS_MPI */

#endif
