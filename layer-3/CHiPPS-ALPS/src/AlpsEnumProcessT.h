/**
 * @file AlpsEnumProcessT.h
 * @brief Process type enumeration for parallel search
 *
 * Defines AlpsProcessType enum identifying roles in distributed computing:
 * Serial (single process), Master (coordinator), Hub (cluster manager),
 * Worker (search executor), and specialized generators (CG/VG cut/variable,
 * CP/VP constraint/variable pool managers).
 *
 * @see AlpsKnowledgeBrokerMPI.h for MPI process management
 * @see AlpsMessageTag.h for inter-process communication
 */
/*===========================================================================*
 * This file is part of the Abstract Library for Parallel Search (ALPS).     *
 *                                                                           *
 * ALPS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Aykut Bulut, Lehigh University                                   *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2023, Lehigh University, Yan Xu, Aykut Bulut, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/


#ifndef AlpsEnumProcessT_H
#define AlpsEnumProcessT_H

//#############################################################################

/** This enumerative constant describes the various process types. */

enum AlpsProcessType {
    /** Serial */
  AlpsProcessTypeSerial = 1,
  /** Master process */
  AlpsProcessTypeMaster,
  /** */
  AlpsProcessTypeHub,
  /** */
  AlpsProcessTypeWorker,
  /** */
  AlpsProcessTypeCG,
  /** */
  AlpsProcessTypeVG,
  /** */
  AlpsProcessTypeCP,
  /** */
  AlpsProcessTypeVP,
  /** */
  AlpsProcessTypeAny
};

#endif
