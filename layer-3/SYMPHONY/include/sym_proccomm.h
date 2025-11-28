/*===========================================================================*/
/*                                                                           */
/* This file is part of the SYMPHONY MILP Solver Framework.                  */
/*                                                                           */
/* SYMPHONY was jointly developed by Ted Ralphs (ted@lehigh.edu) and         */
/* Laci Ladanyi (ladanyi@us.ibm.com).                                        */
/*                                                                           */
/* (c) Copyright 2000-2022 Ted Ralphs. All Rights Reserved.                  */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file sym_proccomm.h
 * @brief Process communication abstraction for parallel SYMPHONY
 *
 * Wrapper functions for PVM (Parallel Virtual Machine) communication.
 * Provides portable inter-process communication in distributed mode.
 *
 * **PVM integration:**
 * - __PVM__ flag enables PVM3 library
 * - DataInPlace = PvmDataRaw for efficient packing
 * - PROCESS_OK = PvmOk for status checks
 *
 * **Process management:**
 * - register_process(): Join PVM
 * - spawn(): Start remote processes
 * - pstat(): Check process status
 * - kill_proc(): Terminate process
 * - comm_exit(): Leave PVM
 *
 * **Message sending:**
 * - init_send(): Initialize send buffer
 * - send_char/int/dbl/float_array(): Pack arrays
 * - send_str(): Pack string
 * - send_msg(): Send to one recipient
 * - msend_msg(): Multicast to multiple recipients
 *
 * **Message receiving:**
 * - receive_msg(): Blocking receive
 * - treceive_msg(): Timed receive
 * - nreceive_msg(): Non-blocking receive
 * - receive_char/int/dbl/float_array(): Unpack arrays
 * - receive_str(): Unpack string
 *
 * **Buffer management:**
 * - bufinfo(): Get buffer metadata
 * - freebuf(): Release buffer
 * - setsbuf(), setrbuf(): Set active buffers
 *
 * @see sym_messages.h for message tags
 * @see sym_tm.h for tree manager using communication
 */
#ifndef _PROCCOMM_H
#define _PROCCOMM_H

#include "sym_proto.h"
#include "sym_timemeas.h"

#ifdef __PVM__
#include <pvm3.h>
#define DataInPlace PvmDataRaw
#define TaskHost PvmTaskHost
#define PROCESS_OK PvmOk
#define PVM_FUNC(info, func)   if ((info = func) < 0) PVM_ERROR(info);
#else
#define PROCESS_OK 1
#define DataInPlace 0
#define TaskHost 0
#endif

int register_process PROTO((void));
int init_send PROTO((int data_packing));
int send_char_array PROTO((char *array, int size));
int send_int_array PROTO((int *array, int size));
int send_dbl_array PROTO((double *array, int size));
int send_float_array PROTO((float *array, int size));
int send_str PROTO((char *str));
int send_msg PROTO((int recipient, int msgtag));
int msend_msg PROTO((int *recipients, int number, int msgtag));
int receive_msg PROTO((int who, int what));
int treceive_msg PROTO((int who, int what, struct timeval *timeout));
int nreceive_msg PROTO((int who, int what));
int bufinfo PROTO((int r_bufid, int *bytes, int *msgtag, int *sender));
int freebuf PROTO((int bufid));
int receive_char_array PROTO((char *array, int size));
int receive_int_array PROTO((int *array, int size));
int receive_dbl_array PROTO((double *array, int size));
int receive_float_array PROTO((float *array, int size));
int receive_str PROTO((char *str));
int spawn PROTO((char *task, char **argv, int flag, char *where, int ntask,
		 int *tids));
int pstat PROTO((int tid));
void kill_proc PROTO((int tid));
void comm_exit PROTO((void));
void setsbuf PROTO((int sbufid));
void setrbuf PROTO((int rbufid));
     
void PVM_ERROR(int info);

#endif
