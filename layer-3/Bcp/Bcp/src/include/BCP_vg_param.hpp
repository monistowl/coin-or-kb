// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_vg_param.hpp
 * @brief Variable Generator parameters for BCP
 *
 * @algorithm VG Parameters: Process Priority and Logging
 *
 * BCP_vg_par defines parameters for Variable Generator processes:
 *
 * **Character parameters:**
 * - MessagePassingIsSerial: Single-process vs. distributed mode
 * - ReportWhenDefaultIsExecuted: Debug overridable methods
 *
 * **Integer parameters:**
 * - NiceLevel: OS scheduling priority (-20 to 20)
 *
 * **String parameters:**
 * - LogFileName: Per-process logging
 *
 * @see BCP_vg.hpp for Variable Generator process
 * @see BCP_vg_user.hpp for user overridable methods
 */
#ifndef _BCP_VG_PARAM_H
#define _BCP_VG_PARAM_H

struct BCP_vg_par{
   enum chr_params{
      /** Indicates whether message passing is serial (all processes are on
	  the same processor) or not. <br>
	  Values: true (1), false (0). Default: 1. */
      MessagePassingIsSerial,
      /** Print out a message when the default version of an overridable
	  method is executed. Default: 1. */
      ReportWhenDefaultIsExecuted,
      //
      end_of_chr_params
   };
   enum int_params{
      /** The "nice" level the process should run at. On Linux and on AIX this
	  value should be between -20 and 20. The higher this value the less
	  resource the process will receive from the system. Note that
	  <ol>
	    <li> The process starts with 0 priority and it can only be
	         increased.
	    <li> If the load is low on the machine (e.g., when all other
	         processes are interactive like netscape or text editors) then
		 even with 20 priority the process will use close to 100% of
		 the cpu, and the interactive processes will be noticably more
		 responsive than they would be if this process ran with 0
		 priority.
	  </ol>
	  @see the man page of the <code>setpriority</code> system function.
      */
      NiceLevel,
      //
      end_of_int_params
   };
   enum dbl_params{
      dbl_dummy,
      //
      end_of_dbl_params
   };
   enum str_params{
      LogFileName,
      //
      end_of_str_params
   };
   enum str_array_params{
      str_array_dummy,
      //
      end_of_str_array_params
   };

};

#endif
