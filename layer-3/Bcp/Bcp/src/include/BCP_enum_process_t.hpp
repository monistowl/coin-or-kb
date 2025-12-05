// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_enum_process_t.hpp
 * @brief Process type enumeration for BCP
 *
 * @algorithm Process Type Enum: TM, LP, CG, VG, TS Identifiers
 *
 * BCP_process_t enumerates all BCP process types:
 * - Any: Wildcard for message receiving
 * - TM: Tree Manager (coordinator)
 * - TS: Tree Storage (external node storage)
 * - LP: Linear Programming worker
 * - CG: Cut Generator
 * - VG: Variable Generator
 * - CP: Cut Pool (future)
 * - VP: Variable Pool (future)
 * - EndProcess: Termination indicator
 *
 * @see BCP_process.hpp for process base class
 */
#ifndef _BCP_ENUM_PROCESS_T_H
#define _BCP_ENUM_PROCESS_T_H

//-----------------------------------------------------------------------------

/** This enumerative constant describes the various process types. */

enum BCP_process_t {
   /** */
   BCP_ProcessType_Any,
   /** */
   BCP_ProcessType_TM,
   /** */
   BCP_ProcessType_TS, // TM storage
   /** */
   BCP_ProcessType_LP,
   /** */
   BCP_ProcessType_CG,
   /** */
   BCP_ProcessType_VG,
   /** */
   BCP_ProcessType_CP,
   /** */
   BCP_ProcessType_VP,
   /** */
   BCP_ProcessType_EndProcess
};

#endif
